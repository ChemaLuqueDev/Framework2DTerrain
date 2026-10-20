// Copyright Chema Luque. Plugin Framework2DTerrain.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/CollisionProfile.h"
#include "Framework2DTerrainTypes.h"
#include "Framework2DTileSet.h" // FFramework2DGenerator (generadores preparados)
#include "Framework2DTerrainWorld.generated.h"

class UProceduralMeshComponent;
class UTexture2D;
class UMaterialInterface;
class UMaterialInstanceDynamic;
class UFramework2DTileMapAsset;
class UFramework2DTileSet;
class UFramework2DCollisionChunkComponent;
class UFramework2DBackdropComponent;

/** Un pixel de escombro en vuelo, en coordenadas de celda (Y hacia abajo). Interno. */
struct FFramework2DDebris
{
	float X = 0.0f;
	float Y = 0.0f;
	float VX = 0.0f;
	float VY = 0.0f;
	float Age = 0.0f;
	float Life = 1.0f;
	FColor Color = FColor::White;
	TWeakObjectPtr<AActor> Target; // si es valido, vuela hacia el
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFramework2DOnTerrainMined, const FFramework2DDigResult&, Result);

/**
 * AFramework2DTerrainWorld
 * =================================================================
 * El terreno destructible pixel a pixel (estilo KYORA). Lo colocas en el nivel, le asignas
 * un Tile Map y ya esta: en el editor ves tu nivel tal cual y al dar a Play se puede picar,
 * explotar y reconstruir pixel a pixel, con colision.
 *
 * Como funciona por dentro:
 *   - Cada PIXEL del dibujo de cada tile es una celda (1 byte = id de material).
 *   - El render copia las celdas a una textura (solo los trozos que cambian).
 *   - La colision es una rejilla de componentes de cajas (solo se rehacen los trozos tocados).
 *   - El terreno vive en el plano XZ del actor: X a la derecha, Z hacia arriba.
 */
UCLASS(Blueprintable, meta = (DisplayName = "Framework2D Terrain"))
class FRAMEWORK2DTERRAIN_API AFramework2DTerrainWorld : public AActor
{
	GENERATED_BODY()

public:
	AFramework2DTerrainWorld();

	//======================================================================
	// LO BASICO
	//======================================================================

	/** El nivel a mostrar y romper. Pintalo con el modo "Framework2D Tiles". */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	TObjectPtr<UFramework2DTileMapAsset> TileMap = nullptr;

	/** Lo que mide un tile en el mundo (cm). Cada pixel del tile mide TileSize / ancho del tile. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D", meta = (ClampMin = "1.0"))
	float TileSize = 64.0f;

	/**
	 * Distancia (cm) entre los planos de las capas. Cada capa del Tile Map se dibuja en su
	 * propio plano: la primera capa visible que no es de fondo queda en el plano del actor
	 * (donde esta la colision), las anteriores detras y las siguientes delante (hacia la
	 * camara, que mira desde +Y: vista Right del editor). 0 = casi el mismo plano (medio
	 * centimetro entre capas, para que la de delante siempre gane).
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D", meta = (ClampMin = "0.0", UIMax = "200.0"))
	float LayerSeparation = 10.0f;

	/**
	 * Material con el que se dibuja. Por defecto el de sprites de Paper2D (sin luz, con el aire
	 * transparente). Si usas uno propio, ponle un parametro de textura "TerrainTexture".
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	TObjectPtr<UMaterialInterface> TerrainMaterial = nullptr;

	//======================================================================
	// ASPECTO
	//======================================================================

	/** Grosor (pixeles) del borde oscuro donde el terreno toca aire. 0 = sin borde. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D|Look", meta = (ClampMin = "0", ClampMax = "4"))
	int32 EdgeWidth = 1;

	/** Color del borde. El alfa es la fuerza de la mezcla (255 = contorno solido). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D|Look")
	FColor EdgeColor = FColor(18, 14, 22, 170);

	/** Color del borde en las caras de arriba (luz cenital). Alfa 0 = igual que el resto. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D|Look")
	FColor TopEdgeColor = FColor(255, 244, 214, 70);

	/** Brillo de las capas de fondo (0..1). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D|Look", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float BackgroundBrightness = 0.45f;

	/** Pinta el aire de un color en vez de dejarlo transparente. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D|Look")
	bool bDrawSky = false;

	/** Color del aire si Draw Sky esta activado. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D|Look", meta = (EditCondition = "bDrawSky"))
	FColor SkyColor = FColor(15, 18, 26, 255);

	/** Dibuja los fondos parallax del Tile Map (cielo, montanas...) detras de las capas. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D|Look")
	bool bShowBackdrops = true;

	/** Distancia (cm) entre la capa del Tile Map de mas atras y los fondos parallax. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D|Look", meta = (ClampMin = "1.0", UIMax = "2000.0"))
	float BackdropDistance = 100.0f;

	/** Oscurece los pixeles que se estan picando (se ve cuanto les queda). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D|Look")
	bool bShowDamage = true;

	//======================================================================
	// ROTURA
	//======================================================================

	/** Lo irregular que es el borde de los agujeros al picar y explotar (0 = circulo perfecto). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Breaking", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float BrushRoughness = 0.35f;

	/** Que hacen los pixeles que saltan al romper. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Breaking")
	EFramework2DDebrisMode DebrisMode = EFramework2DDebrisMode::ToCollector;

	/** Fraccion de pixeles rotos que saltan como escombro (0..1). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Breaking", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float DebrisChance = 0.35f;

	/** Maximo de escombros a la vez. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Breaking", AdvancedDisplay, meta = (ClampMin = "0", ClampMax = "20000"))
	int32 MaxDebris = 2000;

	/** Vida de un escombro (s). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Breaking", AdvancedDisplay, meta = (ClampMin = "0.05"))
	float DebrisLifetime = 0.9f;

	/** Velocidad de salida de los escombros (cm/s). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Breaking", AdvancedDisplay, meta = (ClampMin = "0.0"))
	float DebrisSpeed = 260.0f;

	/** Gravedad de los escombros (cm/s^2). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Breaking", AdvancedDisplay, meta = (ClampMin = "0.0"))
	float DebrisGravity = 980.0f;

	/** Velocidad con la que vuelan hacia quien pica (cm/s). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Breaking", AdvancedDisplay, meta = (ClampMin = "0.0"))
	float DebrisHomingSpeed = 1100.0f;

	//======================================================================
	// COLISION
	//======================================================================

	/** Genera colision para que el personaje pise el terreno. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D|Collision")
	bool bGenerateCollision = true;

	/** Grosor de la colision en profundidad (eje Y), a cada lado del plano. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D|Collision", meta = (ClampMin = "1.0"))
	float CollisionDepth = 50.0f;

	/** Perfil de colision (por defecto BlockAll). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D|Collision")
	FCollisionProfileName CollisionProfile = FCollisionProfileName(TEXT("BlockAll"));

	/** Lado (en pixeles) de cada trozo de colision. Picar solo rehace los trozos tocados. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D|Collision", AdvancedDisplay, meta = (ClampMin = "16", ClampMax = "512"))
	int32 CollisionChunkSize = 64;

	//======================================================================
	// EVENTOS
	//======================================================================

	/** Salta cada vez que un golpe (MineAt / Dig / Explode) rompe al menos un pixel. */
	UPROPERTY(BlueprintAssignable, Category = "Framework2D")
	FFramework2DOnTerrainMined OnTerrainMined;

	//======================================================================
	// API BLUEPRINT
	//======================================================================

	/**
	 * PICAR (estilo KYORA): suma DamageAmount a cada pixel del circulo, de borde irregular.
	 * Un pixel se rompe cuando su dano llega a la Hardness de su material. Lo roto se cuenta
	 * en el resultado y, si DebrisMode es "Hacia quien pica", vuela hacia Collector.
	 * Llamalo cada frame mientras se pica (o usa el componente Framework2D Terraform).
	 */
	UFUNCTION(BlueprintCallable, Category = "Framework2D", meta = (AdvancedDisplay = "Collector"))
	FFramework2DDigResult MineAt(FVector WorldPosition, float Radius, int32 DamageAmount = 1, AActor* Collector = nullptr);

	/** Excava un circulo exacto al instante (ignora la dureza; respeta lo indestructible). Sin escombros. */
	UFUNCTION(BlueprintCallable, Category = "Framework2D")
	FFramework2DDigResult Dig(FVector WorldPosition, float Radius);

	/** Explosion: dano que baja con la distancia (Power en el centro) y escombros en estallido. */
	UFUNCTION(BlueprintCallable, Category = "Framework2D")
	void Explode(FVector WorldPosition, float Radius, float Power = 255.0f);

	/**
	 * COLOCAR terreno: rellena con MaterialName los huecos del circulo, de dentro hacia fuera,
	 * hasta MaxCells (-1 = sin limite). Con bAvoidPawns no coloca encima de personajes.
	 * Layer = capa del Tile Map donde se coloca (-1 = la capa base). Solo rellena pixeles que
	 * no chocan. Devuelve cuantos pixeles se colocaron.
	 */
	UFUNCTION(BlueprintCallable, Category = "Framework2D", meta = (AdvancedDisplay = "Layer"))
	int32 PlaceMaterial(FVector WorldPosition, float Radius, FName MaterialName, int32 MaxCells = -1, bool bAvoidPawns = true, int32 Layer = -1);

	/** Pinta un material en un circulo de una capa, sustituyendo lo que haya (None = borrar). Layer -1 = capa base. */
	UFUNCTION(BlueprintCallable, Category = "Framework2D", meta = (AdvancedDisplay = "Layer"))
	void Paint(FVector WorldPosition, float Radius, FName MaterialName, int32 Layer = -1);

	/**
	 * Rayo pixel a pixel de Start a End. Devuelve el punto donde toca el primer pixel de
	 * terreno (dentro de ese pixel) y su material. Es el "laser" de la varita.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "Framework2D")
	bool TraceTerrain(FVector Start, FVector End, bool bOnlyCollidable, FVector& OutHitLocation, FName& OutMaterialName) const;

	/**
	 * Como Trace Terrain, pero se para solo en pixeles que se pueden picar: atraviesa las capas
	 * que no se rompen (decoracion intocable). Es el rayo de la varita.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "Framework2D")
	bool TraceBreakableTerrain(FVector Start, FVector End, FVector& OutHitLocation, FName& OutMaterialName) const;

	/** True si en ese punto hay terreno que colisiona. */
	UFUNCTION(BlueprintPure, Category = "Framework2D")
	bool IsSolidAtWorld(FVector WorldPosition) const;

	/** Material en ese punto (el de la capa de mas delante que tenga algo): None si es aire o esta fuera. */
	UFUNCTION(BlueprintPure, Category = "Framework2D")
	FName GetMaterialNameAtWorld(FVector WorldPosition) const;

	/** Material en ese punto de UNA capa del Tile Map. None si es aire, la capa esta oculta o no existe. */
	UFUNCTION(BlueprintPure, Category = "Framework2D")
	FName GetLayerMaterialNameAtWorld(FVector WorldPosition, int32 Layer) const;

	/** Cuantos pixeles de un material hay en un circulo (objetivos de juego). */
	UFUNCTION(BlueprintPure, Category = "Framework2D")
	int32 CountMaterialInRadius(FVector WorldPosition, float Radius, FName MaterialName) const;

	/** Tamano de un pixel de terreno en el mundo (cm). */
	UFUNCTION(BlueprintPure, Category = "Framework2D")
	float GetCellSize() const;

	/** Materiales del tileset (para inventarios, modo creativo...). */
	UFUNCTION(BlueprintPure, Category = "Framework2D")
	TArray<FFramework2DMaterial> GetMaterials() const;

	/** Vuelve a dejar el terreno como esta pintado en el Tile Map (reiniciar nivel). */
	UFUNCTION(BlueprintCallable, Category = "Framework2D")
	void ResetTerrain();

	/**
	 * GENERACION PROCEDURAL: crea un nivel nuevo con la receta del Tile Map (pestana "Generar"
	 * del modo Framework2D Tiles) y lo construye. Seed: la semilla a usar; -1 = una al azar.
	 * En juego trabaja sobre una COPIA del Tile Map (el asset no cambia: cada partida, un nivel
	 * distinto). En el editor cambia el asset (con deshacer).
	 */
	UFUNCTION(BlueprintCallable, Category = "Framework2D|Procedural")
	FFramework2DProcGenReport GenerateProceduralLevel(int32 Seed = -1);

	/** Ancho y alto del terreno en pixeles (se calculan del Tile Map). */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Transient, Category = "Framework2D")
	int32 GridWidth = 0;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Transient, Category = "Framework2D")
	int32 GridHeight = 0;

	//======================================================================
	// EDITOR (los usa el modo "Framework2D Tiles"; no hace falta llamarlos a mano)
	//======================================================================

	/** Capa base: la primera capa visible que no es de fondo (va en el plano del actor). -1 si no hay. */
	int32 GetBaseLayer() const;

	/** Profundidad (Y local, cm) del plano de una capa del Tile Map, este oculta o no. Positivo = hacia la camara. */
	float GetLayerDepth(int32 Layer) const;

	/** Pixeles (celdas) por tile. */
	int32 GetCellsPerTile() const { return CellsPerTile; }

	/** Los fondos parallax (para herramientas y pruebas). */
	UFramework2DBackdropComponent* GetBackdropComponent() const { return BackdropMesh; }

	/** Planos de render creados (uno por capa visible). */
	int32 GetNumRenderLayers() const { return RLayers.Num(); }

	/**
	 * Rectangulos de celdas (Min..Max incluidos, Y=0 arriba) que colisionan, fusionados por
	 * filas. Es lo que el modo de pintado dibuja como "colision". Funciona con la vista previa.
	 */
	void GetCollisionCellRects(TArray<FIntRect>& OutRects) const;

	/** Sube cada vez que cambia el contenido (horneado, picado...). Para cachear dibujos del editor. */
	uint32 GetContentRevision() const { return ContentRevision; }

	/** Recoloca los planos de las capas tras cambiar LayerSeparation, sin rehornear. */
	void UpdateLayerDepths();

	/** Rehace la vista previa entera (tras cambiar tileset, deshacer, etc.). */
	void RebuildPreview();

	/** Rehornea solo un rectangulo de tiles (incluido) tras pintarlos. Rapido. */
	void RefreshPreviewTiles(const FIntRect& TileRect);

	/** True si este terreno usa ese asset (tilemap, tileset o atlas). */
	bool UsesAsset(const UObject* Asset) const;

	virtual void PostRegisterAllComponents() override;
	virtual bool ShouldTickIfViewportsOnly() const override { return true; } // flipbooks animados en el editor
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	//---------------------- Componentes ----------------------
	UPROPERTY() TObjectPtr<UProceduralMeshComponent> RenderMesh;
	// Fondos parallax (una seccion por capa de fondo del Tile Map).
	UPROPERTY() TObjectPtr<UFramework2DBackdropComponent> BackdropMesh;
	// Una textura y un material por plano de capa (mismo indice que RLayers = seccion de RenderMesh).
	UPROPERTY(Transient, NonTransactional) TArray<TObjectPtr<UTexture2D>> LayerTextures;
	UPROPERTY(Transient, NonTransactional) TArray<TObjectPtr<UMaterialInstanceDynamic>> LayerMIDs;
	UPROPERTY(Transient) TArray<TObjectPtr<UFramework2DCollisionChunkComponent>> CollisionChunks;

	//---------------------- Capas ----------------------
	/**
	 * Una capa VISIBLE del Tile Map ya horneada ("slot"). Todas miden GridWidth x GridHeight.
	 * Las de fondo guardan su dibujo ya oscurecido en ArtColor y nunca se rompen ni chocan.
	 */
	struct FLayerRuntime
	{
		int32 MapLayer = 0;      // indice en TileMap->Layers
		bool bBackground = false;
		bool bCollides = true;   // capa que choca (nunca si es de fondo)
		bool bBreakable = true;  // capa que se rompe (nunca si es de fondo)
		float DepthY = 0.0f;     // Y local del plano (positivo = hacia la camara)
		TArray<uint8> Cells;     // id de material por celda (0 = aire)
		TArray<uint8> Damage;    // dano acumulado al picar (solo en juego y en capas que se rompen; vacio si no)
		TArray<FColor> ArtColor; // dibujo del tile (A==0: sin dibujo; A==1: pixel de flipbook oculto en este fotograma)
		// El color final no se guarda: se calcula al subir cada trozo a la textura (la mitad de memoria).
	};
	TArray<FLayerRuntime> RLayers; // de atras (0) a delante

	// 1 = alguna capa (que no es de fondo) tiene ahi un material con borde. Es lo que mira el borde
	// oscuro de cada pixel: asi no recorre todas las capas en cada vecino.
	TArray<uint8> SolidMask;

	// Colision por pixel, comun a todas las capas: 0 = automatica, 1 = solida, 2 = sin colision.
	// La rellenan las formas de colision (TileSet y pincel de colision) al hornear.
	TArray<uint8> CollisionMode;

	// Materiales: id = indice (0 = aire, 1.. = Materials del tileset).
	TArray<FFramework2DMaterial> ResolvedMaterials;
	TMap<FName, uint8> NameToId;
	uint8 EdgeMask[256];      // 1 = el material dibuja borde
	TArray<TArray<FColor>> FillPatterns; // por material: dibujo del tile de relleno (CPT x CPT)

	// Paginas de atlas del tileset en CPU (para hornear y rehornear trozos).
	struct FPageCPU { int32 Id = 0; TArray<FColor> Pixels; int32 W = 0; int32 H = 0; };
	TArray<FPageCPU> PagesCPU;
	int32 CellsPerTile = 16;

	// Generadores listos para hornear: sus sprites ya recortados del atlas.
	struct FPreparedSprite { TArray<FColor> Pixels; int32 W = 0; int32 H = 0; float Weight = 1.0f; };
	struct FPreparedGenerator { FFramework2DGenerator Def; TArray<FPreparedSprite> Sprites; float TotalWeight = 0.0f; uint8 MaterialId = 0; };
	TMap<int32, FPreparedGenerator> PreparedGenerators; // por Id

	// Objetos grandes listos para hornear: su imagen recortada al dibujo (el pie = su fila de abajo).
	struct FPreparedProp { TArray<FColor> Pixels; int32 W = 0; int32 H = 0; uint8 MaterialId = 0; };
	TMap<int32, FPreparedProp> PreparedProps; // por Id
	int32 GeneratorMarginTiles = 0; // lo que un sprite generado puede salirse de su casilla (en tiles)
	// Lo que hay que rehornear alrededor de una zona por los objetos apoyados en el suelo (en tiles).
	int32 PropMarginSide = 0;
	int32 PropMarginUp = 0;
	int32 PropMarginDown = 0;

	// Flipbooks horneados: un registro por celda de flipbook pintada en una capa visible.
	struct FAnimatedTile { int32 Slot = 0; int32 Tx = 0; int32 Ty = 0; int32 Value = 0; int32 ShownTile = -1; };
	TArray<FAnimatedTile> AnimatedTiles;
	double AnimTime = 0.0;

	// Trozos de render (compartidos por todas las capas: un trozo sucio se recalcula en todas).
	static constexpr int32 ChunkSize = 32;
	int32 ChunksX = 0;
	int32 ChunksY = 0;
	TArray<uint8> ChunkRebuild; // recalcular colores
	TArray<uint8> ChunkUpload;  // subir a la GPU
	TArray<int32> DebrisChunksLastFrame; // trozos con escombros el ultimo frame (hay que repintarlos sin ellos)
	TArray<FIntVector> AnimDirtyTiles;   // (slot, tx, ty) de flipbooks que cambiaron de fotograma: solo ese tile, solo esa capa

	// Trozos de colision.
	int32 CollChunksX = 0;
	int32 CollChunksY = 0;
	int32 CollChunkCells = 64;
	TArray<uint8> CollisionChunkDirty;
	TArray<FBox> CollisionBoxScratch;

	TArray<FFramework2DDebris> Debris;

	// True si TileMap es la copia de juego que crea GenerateProceduralLevel (no el asset).
	bool bOwnsRuntimeTileMap = false;

	uint32 BrushCounter = 0;
	uint32 ContentRevision = 0;
	bool bBuilt = false;          // hay terreno construido (juego o vista previa)
	bool bGameplay = false;       // construido para jugar (con colision)
	bool bCanRender = true;       // false en servidores dedicados
	bool bVisualDirty = false;
	bool bCollisionDirty = false;

	//---------------------- Construccion ----------------------
	bool BuildTerrain(bool bForGameplay);
	void ResolveMaterials(const UFramework2DTileSet* Set);
	void BakeTiles(const FIntRect& TileRect);
	void BakeCollisionShapes(const FIntRect& TileRect);
	void UpdateAnimations(float DeltaSeconds);
	void DrawAnimatedFrame(const FAnimatedTile& Anim, int32 AtlasTile);
	void BuildFillPatterns(const UFramework2DTileSet* Set);
	void ReadPages(const UFramework2DTileSet* Set);
	const FPageCPU* FindPageCPU(int32 PageId) const;
	/** Pagina en CPU y origen (px) de un tile con pagina. nullptr si no se puede dibujar. */
	const FPageCPU* TileOrigin(int32 TileValue, int32& OutX, int32& OutY) const;
	void PrepareGenerators(const UFramework2DTileSet* Set);
	/** Reparte los sprites de las casillas generador cercanas, escribiendo solo dentro de PixelClip. */
	void StampGenerators(const FIntRect& TileRect, const FIntRect& PixelClip);
	void StampGeneratorCell(int32 Slot, int32 Tx, int32 Ty, const FPreparedGenerator& Gen, const FIntRect& PixelClip);
	bool IsGroundPixel(int32 X, int32 Y) const;
	void PrepareProps(const UFramework2DTileSet* Set);
	/** Hornea los objetos grandes del Tile Map que caen dentro de PixelClip. */
	void StampProps(const FIntRect& PixelClip);
	/** Rehace los fondos parallax (Tile Map > Backdrops). */
	void RefreshBackdrops();
	void CreateRenderResources();
	void CreateLayerSection(int32 Slot);

	//---------------------- Capas ----------------------
	int32 FindSlot(int32 MapLayer) const;     // slot de una capa del Tile Map (INDEX_NONE si oculta/no existe)
	int32 ResolveEditSlot(int32 MapLayer) const; // -1 = capa base; INDEX_NONE si no vale (o es de fondo)
	int32 FrontCellSlot(int32 X, int32 Y) const; // capa no-fondo de mas delante con celda (INDEX_NONE si aire)
	bool IsCollidableAt(int32 X, int32 Y) const; // colision final del pixel (formas + capas + material)
	bool HasForegroundCell(int32 X, int32 Y) const;
	bool HasBreakableCell(int32 X, int32 Y) const;
	int32 BreakableCellSlot(int32 X, int32 Y) const; // capa que se rompe de mas delante con celda

	enum class ETraceStop : uint8 { AnyCell, Collidable, Breakable };
	bool TraceCells(const FVector& Start, const FVector& End, ETraceStop Stop, FVector& OutHitLocation, FName& OutMaterialName) const;

	//---------------------- Rotura ----------------------
	FFramework2DDigResult BreakInRadius(const FVector& WorldPosition, float Radius, int32 DamageAmount, bool bFalloff, bool bRoughEdge, bool bSpawnDebris, AActor* Collector, bool bRadialDebris);
	float RoughRadius(float Radius, int32 Dx, int32 Dy, uint32 Seed) const;
	void SetCellInternal(int32 Slot, int32 X, int32 Y, uint8 Id);
	void SpawnDebris(int32 Slot, int32 X, int32 Y, int32 Cx, int32 Cy, AActor* Collector, bool bRadial);
	void UpdateDebris(float DeltaSeconds);
	void GatherPawnCellRects(const FVector& WorldPosition, float Radius, TArray<FIntRect>& OutRects) const;

	//---------------------- Render ----------------------
	FColor BaseCellColor(int32 Slot, int32 X, int32 Y) const;
	FColor ComputeCellColor(int32 Slot, int32 X, int32 Y) const;
	int32 EdgeDistance(int32 X, int32 Y) const;
	bool IsOpenCell(int32 X, int32 Y) const;
	void FlushVisual();
	/** Calcula los colores de esos rectangulos de pixeles de una capa (en paralelo) y los sube a su textura. */
	struct FDebrisPaint { FColor Color; float Fade = 1.0f; };
	void UploadRects(int32 Slot, const TArray<FIntRect>& Rects, const TMap<int32, FDebrisPaint>* Overlay);
	/** Rehace SolidMask en un rectangulo de pixeles (incluido). */
	void RefreshSolidMask(int32 X0, int32 Y0, int32 X1, int32 Y1);
	void MarkVisualDirty(int32 X, int32 Y);
	void MarkChunkRebuild(int32 Cx, int32 Cy);
	void MarkAllDirty();

	//---------------------- Colision ----------------------
	void CreateCollisionChunks();
	void DestroyCollisionChunks();
	void RebuildDirtyCollision();
	void RebuildCollisionChunk(int32 ChunkIndex);
	void ApplyCollisionChunk(int32 ChunkIndex, const TArray<FIntRect>& Rects); // crea el componente si hace falta
	void MarkCollisionDirty(int32 X, int32 Y);
	/** Fusion de tramos por filas de la zona [X0,X0+W) x [Y0,Y0+H): rectangulos de celdas solidas. */
	void MergeCollisionRows(int32 X0, int32 Y0, int32 W, int32 H, TArray<FIntRect>& OutRects) const;

	//---------------------- Coordenadas ----------------------
	bool WorldToCell(const FVector& World, int32& OutX, int32& OutY) const;
	void WorldToCellFloat(const FVector& World, float& OutX, float& OutY) const;
	FVector CellFloatToWorld(float X, float Y) const;
	uint8 FindMaterialId(FName MaterialName) const;

	FORCEINLINE int32 Index(int32 X, int32 Y) const { return Y * GridWidth + X; }
	FORCEINLINE bool InBounds(int32 X, int32 Y) const { return X >= 0 && X < GridWidth && Y >= 0 && Y < GridHeight; }
	FORCEINLINE bool IsCollidable(uint8 Id) const { return Id != 0 && ResolvedMaterials.IsValidIndex(Id) && ResolvedMaterials[Id].bCollides; }
};
