// Copyright Chema Luque. Plugin Framework2DTerrain.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Framework2DTerrainTypes.h"
#include "Framework2DProcGenTypes.h"
#include "Framework2DTileSet.generated.h"

class UTexture2D;

/** Un tile del tileset. Su posicion en la lista Tiles es su numero en el atlas. */
USTRUCT(BlueprintType)
struct FFramework2DTileDef
{
	GENERATED_BODY()

	// Material de este tile (de la lista Materials del tileset). "None" = el tile no es
	// terreno: en una capa normal no pone nada; en una capa de fondo se ve igual.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D", meta = (GetOptions = "GetMaterialNameOptions"))
	FName MaterialName = NAME_None;

	// Colision de este tile en todos los mapas. Automatica = la del dibujo y su material.
	// Celda a celda se puede cambiar con el pincel de colision del modo Framework2D Tiles.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	EFramework2DCollisionShape Collision = EFramework2DCollisionShape::Auto;

	// Marca un tile "interior" (sin hierba ni bordes): las celdas de su material que el
	// jugador COLOCA se pintan con este dibujo, alineado a la rejilla de tiles.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	bool bFillPattern = false;

	// OBSOLETO (v2.0): los flipbooks ahora viven en la lista Flipbooks del tileset y ya no
	// pisan el tile. Al cargar se migran solos (PostLoad) y estos campos quedan vacios.
	UPROPERTY()
	TArray<int32> AnimationFrames;

	UPROPERTY()
	float AnimationFPS = 8.0f;
};

/**
 * Un FLIPBOOK (tile animado). Vive aparte de los tiles del atlas: crearlo no cambia ningun
 * tile. En el mapa se pinta como un tile mas (desde la seccion Flipbooks de la paleta).
 */
USTRUCT(BlueprintType)
struct FFramework2DFlipbook
{
	GENERATED_BODY()

	// Nombre que se ve en la paleta.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	FName Name = TEXT("Flipbook");

	// Identificador estable que guardan los mapas. No lo cambies a mano.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Framework2D")
	int32 Id = 0;

	// Fotogramas: numeros de tile del atlas, en orden (se cuentan desde 0, de izquierda a
	// derecha y de arriba abajo).
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	TArray<int32> Frames;

	// Fotogramas por segundo.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D", meta = (ClampMin = "0.1", ClampMax = "60.0"))
	float FPS = 8.0f;

	// Material de terreno del flipbook. Agua, hierba... suelen ser Decoration (no colisiona).
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D", meta = (GetOptions = "GetMaterialNameOptions"))
	FName MaterialName = NAME_None;

	// Colision del flipbook (como la de un tile).
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	EFramework2DCollisionShape Collision = EFramework2DCollisionShape::Auto;
};

/**
 * Una PAGINA de atlas extra: otra imagen con tiles del mismo tamano (otro entorno: cueva,
 * bosque, desierto...). En la paleta sale como una pestana mas del atlas.
 */
USTRUCT(BlueprintType)
struct FFramework2DAtlasPage
{
	GENERATED_BODY()

	// Nombre de la pestana en la paleta.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	FName Name = TEXT("Atlas");

	// Identificador estable que guardan los mapas. No lo cambies a mano.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Framework2D")
	int32 Id = 0;

	// La imagen, con tiles del mismo tamano que el atlas principal (Tile Width x Tile Height).
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	TObjectPtr<UTexture2D> Texture = nullptr;

	// Un tile por cada hueco de la imagen (se crean solos).
	UPROPERTY(EditAnywhere, BlueprintReadOnly, EditFixedSize, Category = "Framework2D", meta = (TitleProperty = "MaterialName"))
	TArray<FFramework2DTileDef> Tiles;

	UPROPERTY(VisibleAnywhere, Category = "Framework2D")
	int32 Columns = 0;

	UPROPERTY(VisibleAnywhere, Category = "Framework2D")
	int32 Rows = 0;

	// Copia CPU de la imagen para el juego empaquetado (se rellena al guardar).
	UPROPERTY()
	TArray<FColor> PixelCache;

	UPROPERTY()
	int32 CacheWidth = 0;

	UPROPERTY()
	int32 CacheHeight = 0;
};

/** Un sprite que puede sacar un generador: un trozo del atlas (uno o varios tiles). */
USTRUCT(BlueprintType)
struct FFramework2DScatterSprite
{
	GENERATED_BODY()

	// Tile de arriba-izquierda del sprite (valor de tile: pagina + numero).
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	int32 Tile = 0;

	// Tamano del sprite en tiles (un arbusto de 2x2, un junco de 1x2...).
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D", meta = (ClampMin = "1", ClampMax = "16"))
	int32 WidthInTiles = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D", meta = (ClampMin = "1", ClampMax = "16"))
	int32 HeightInTiles = 1;

	// Probabilidad relativa de salir frente a los demas sprites del generador.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D", meta = (ClampMin = "0.0"))
	float Weight = 1.0f;
};

/**
 * Un GENERADOR de vegetacion (o rocas, setas...). Se pinta en una casilla de cualquier capa
 * como si fuera un tile y, al hornear, reparte por ella sprites del atlas con variacion de
 * posicion, escala, volteo y tinte. Lo generado son pixeles de terreno de esa capa: se ven en
 * el editor al momento y el jugador los rompe como lo demas. Siempre sale igual (semilla).
 */
USTRUCT(BlueprintType)
struct FFramework2DGenerator
{
	GENERATED_BODY()

	// Nombre que se ve en la paleta.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	FName Name = TEXT("Generador");

	// Identificador estable que guardan los mapas. No lo cambies a mano.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Framework2D")
	int32 Id = 0;

	// Sprites que puede sacar (se eligen al azar segun su peso).
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D", meta = (TitleProperty = "Tile"))
	TArray<FFramework2DScatterSprite> Sprites;

	// Sprites por casilla (media). 0.5 = uno cada dos casillas; 3 = tres por casilla.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D", meta = (ClampMin = "0.0", ClampMax = "16.0"))
	float Density = 1.0f;

	// Variacion horizontal al azar (pixeles, a cada lado). Se reparten por la casilla y se mueven esto.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D", meta = (ClampMin = "0.0", ClampMax = "256.0"))
	float JitterX = 6.0f;

	// Variacion vertical al azar (pixeles, arriba o abajo).
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D", meta = (ClampMin = "0.0", ClampMax = "256.0"))
	float JitterY = 0.0f;

	// Desplazamiento vertical fijo (pixeles; positivo = hacia abajo, se hunde en el suelo).
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D", meta = (ClampMin = "-256.0", ClampMax = "256.0"))
	float OffsetY = 1.0f;

	// Escala minima y maxima de cada sprite (1 = tamano del atlas; con pixel art, mejor 1).
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D", meta = (ClampMin = "0.1", ClampMax = "8.0"))
	float ScaleMin = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D", meta = (ClampMin = "0.1", ClampMax = "8.0"))
	float ScaleMax = 1.0f;

	// Voltea en horizontal la mitad de los sprites, al azar.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	bool bRandomFlip = true;

	// Cada sprite se tine con un color al azar entre Tint A y Tint B (blanco = sin tinte).
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	FLinearColor TintA = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	FLinearColor TintB = FLinearColor::White;

	// Variacion de brillo al azar (0.15 = hasta un 15 % mas claro u oscuro).
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float BrightnessVariation = 0.1f;

	// Apoya cada sprite en el primer suelo que choca debajo de su punto (si no hay suelo, no sale).
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	bool bSnapToGround = true;

	// Cuelga cada sprite del primer techo que choca ENCIMA de su punto (lianas, raices, rocas bajo
	// una isla o un saliente). Si no hay techo cerca, no sale. Gana a "Apoyar en el suelo".
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	bool bHangFromCeiling = false;

	// Hasta cuantas casillas por debajo se busca el suelo.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D", meta = (ClampMin = "0", ClampMax = "8", EditCondition = "bSnapToGround"))
	int32 GroundSearchTiles = 2;

	// Material de lo generado. Decoration = se ve y se rompe, pero no choca.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D", meta = (GetOptions = "GetMaterialNameOptions"))
	FName MaterialName = TEXT("Decoration");

	// Cambiala para otra distribucion al azar con los mismos ajustes.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	int32 Seed = 0;
};

/**
 * Un OBJETO GRANDE (arbol, roca, piedra runica, seta gigante...): una imagen suelta de
 * cualquier tamano. El generador procedural los reparte por el suelo y se hornean como pixeles
 * de una capa (detras o delante del terreno).
 */
USTRUCT(BlueprintType)
struct FFramework2DPropDef
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	FName Name = TEXT("Objeto");

	// Identificador estable que guardan los mapas y los biomas. No lo cambies a mano.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Framework2D")
	int32 Id = 0;

	// La imagen (con transparencia). 1 pixel de la imagen = 1 pixel del terreno.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	TObjectPtr<UTexture2D> Texture = nullptr;

	// O un trozo del ATLAS (sin imagen): tile de arriba-izquierda (con pagina) y tamano en tiles.
	// Para tilesets que traen los arboles, rocas... dentro del atlas.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	int32 AtlasTile = -1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D", meta = (ClampMin = "1", ClampMax = "64"))
	int32 AtlasWidthTiles = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D", meta = (ClampMin = "1", ClampMax = "64"))
	int32 AtlasHeightTiles = 1;

	// Material de sus pixeles. Decoration = se ve y no choca.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D", meta = (GetOptions = "GetMaterialNameOptions"))
	FName MaterialName = TEXT("Decoration");

	// Suelo llano que necesita debajo (tiles). 0 = el ancho de la imagen.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D", meta = (ClampMin = "0", ClampMax = "64"))
	int32 FootprintTiles = 0;

	// Copia CPU de la imagen para el juego empaquetado (se rellena al guardar).
	UPROPERTY()
	TArray<FColor> PixelCache;

	UPROPERTY()
	int32 CacheWidth = 0;

	UPROPERTY()
	int32 CacheHeight = 0;
};

/**
 * UFramework2DTileSet
 * =================================================================
 * Tu atlas de tiles + los materiales de terreno. Se crea con:
 *   Content Browser -> Add -> Miscellaneous -> Data Asset -> Framework2DTileSet
 *
 *   1. Asigna el Atlas (imagen con los tiles en rejilla, sin margenes) y el tamano del tile.
 *      La lista Tiles se crea sola: una fila por tile del atlas.
 *   2. En cada fila elige el material del tile (desplegable) y, si quieres, su colision.
 *   3. Ajusta los materiales si quieres (dureza, colision...). Vienen 6 de serie.
 *   4. Los flipbooks y los generadores de vegetacion se crean desde la paleta del modo
 *      Framework2D Tiles. Mas atlas (otros entornos): en "Atlas extra" o con el "+" de la paleta.
 *
 * Cada pixel del dibujo de un tile sera una celda que el jugador puede romper.
 *
 * VALOR de una celda del mapa (ver Framework2D::FlipbookTileBase): -1 vacio, tile de un atlas
 * (pagina + numero), flipbook o generador. Las funciones de abajo aceptan cualquier valor.
 */
UCLASS(BlueprintType)
class FRAMEWORK2DTERRAIN_API UFramework2DTileSet : public UDataAsset
{
	GENERATED_BODY()

public:
	UFramework2DTileSet();

	// Imagen con todos los tiles en rejilla. Da igual como la importes (comprimida o no):
	// se lee el PNG original. Consejo: Filter = Nearest para que la paleta se vea nitida.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	TObjectPtr<UTexture2D> Atlas = nullptr;

	// Ancho de un tile en pixeles del atlas. Cada pixel sera una celda pickable.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D", meta = (ClampMin = "1", ClampMax = "256"))
	int32 TileWidth = 16;

	// Alto de un tile en pixeles del atlas.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D", meta = (ClampMin = "1", ClampMax = "256"))
	int32 TileHeight = 16;

	// Materiales de terreno de este tileset. Los tiles los eligen por nombre.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D", meta = (TitleProperty = "Name"))
	TArray<FFramework2DMaterial> Materials;

	// Un tile por cada hueco del atlas (se crean solos al asignar el atlas).
	UPROPERTY(EditAnywhere, BlueprintReadOnly, EditFixedSize, Category = "Framework2D", meta = (TitleProperty = "MaterialName"))
	TArray<FFramework2DTileDef> Tiles;

	// Mas imagenes con tiles del mismo tamano (otros entornos: cueva, bosque, desierto...).
	// Cada una sale como una pestana en el atlas de la paleta.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D|Atlas extra", meta = (TitleProperty = "Name"))
	TArray<FFramework2DAtlasPage> ExtraAtlases;

	// Generadores de vegetacion: se pintan en una casilla como un tile y al hornear reparten
	// sprites del atlas por ella. Se crean y ajustan desde la paleta.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D|Generators", meta = (TitleProperty = "Name"))
	TArray<FFramework2DGenerator> Generators;

	// Tiles animados. Se crean desde la paleta (selecciona fotogramas en el atlas y pulsa
	// "Nuevo flipbook"); aqui puedes retocarlos.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D|Flipbooks", meta = (TitleProperty = "Name"))
	TArray<FFramework2DFlipbook> Flipbooks;

	// Biomas del generador procedural: las piezas (terreno 3x3, rampas, fondo, agua,
	// decoracion...) con las que se construye un nivel. Se editan en la pestana "Generar".
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D|Biomes", meta = (TitleProperty = "Name"))
	TArray<FFramework2DBiome> Biomes;

	// Objetos grandes (imagenes sueltas: arboles, rocas...). Se anaden desde la pestana "Generar".
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D|Objects", meta = (TitleProperty = "Name"))
	TArray<FFramework2DPropDef> Props;

	// Tiles por fila y por columna del atlas (informativo).
	UPROPERTY(VisibleAnywhere, Category = "Framework2D")
	int32 Columns = 0;

	UPROPERTY(VisibleAnywhere, Category = "Framework2D")
	int32 Rows = 0;

	// Opciones del desplegable de material de cada tile.
	UFUNCTION()
	TArray<FString> GetMaterialNameOptions() const;

	int32 GetNumTiles() const { return Tiles.Num(); }

	//---------------------- Paginas de atlas ----------------------
	// La pagina 0 es el atlas principal (Atlas + Tiles); las demas, ExtraAtlases.

	/** Cuantas paginas hay (principal + extra). */
	int32 GetNumPages() const { return 1 + ExtraAtlases.Num(); }

	/** Id de la pagina en la posicion Index (0 = principal). INDEX_NONE si no existe. */
	int32 GetPageIdAt(int32 Index) const;

	/** Posicion de la pagina con ese Id (0 = principal). INDEX_NONE si no existe. */
	int32 FindPageIndex(int32 PageId) const;

	/** Nombre para la pestana de la paleta. */
	FText GetPageDisplayName(int32 PageId) const;

	UTexture2D* GetPageTexture(int32 PageId) const;
	const TArray<FFramework2DTileDef>* GetPageTiles(int32 PageId) const;
	TArray<FFramework2DTileDef>* GetPageTilesMutable(int32 PageId);

	/** Tamano en pixeles de la imagen de la pagina (false si no hay imagen legible). */
	bool GetPageSize(int32 PageId, int32& OutWidth, int32& OutHeight) const;

	/** Columnas y filas de tiles de la pagina (segun su imagen). */
	bool GetPageGrid(int32 PageId, int32& OutColumns, int32& OutRows) const;

	/** Pixeles de la imagen de una pagina (como ReadAtlasPixels, que es la pagina 0). */
	bool ReadPagePixels(int32 PageId, TArray<FColor>& OutPixels, int32& OutWidth, int32& OutHeight) const;

	/** Pagina y pixel superior-izquierdo de un tile (valor con pagina). false si no se puede dibujar. */
	bool GetTileValueOrigin(int32 TileValue, int32& OutPageId, int32& OutX, int32& OutY) const;

	/** Anade una pagina con esa imagen y devuelve su Id (estable). */
	int32 AddAtlasPage(UTexture2D* Texture, FName Name = NAME_None);

	/** Quita una pagina extra (la principal no). Las celdas que la usaban quedan vacias. */
	bool RemoveAtlasPage(int32 PageId);

	/** Definicion del tile al que apunta un valor de tile (nullptr si no es un tile valido). */
	const FFramework2DTileDef* FindTileDef(int32 Value) const;
	FFramework2DTileDef* FindTileDefMutable(int32 Value);

	//---------------------- Generadores ----------------------

	/** Crea un generador vacio y devuelve su Id. */
	int32 AddGenerator(FName Name = NAME_None);

	/** Quita el generador con ese Id. Las celdas que lo usaban quedan vacias. */
	bool RemoveGenerator(int32 GeneratorId);

	int32 FindGeneratorIndex(int32 GeneratorId) const;
	const FFramework2DGenerator* FindGeneratorByValue(int32 Value) const;
	FFramework2DGenerator* FindGeneratorById(int32 GeneratorId);

	//---------------------- Biomas (generador procedural) ----------------------

	/** Crea un bioma vacio y devuelve su Id. */
	int32 AddBiome(FName Name = NAME_None);

	/** Quita el bioma con ese Id. */
	bool RemoveBiome(int32 BiomeId);

	int32 FindBiomeIndex(int32 BiomeId) const;
	const FFramework2DBiome* FindBiomeById(int32 BiomeId) const;
	FFramework2DBiome* FindBiomeByIdMutable(int32 BiomeId);

	/** El bioma con ese Id o, si no existe, el primero. nullptr si no hay ninguno. */
	const FFramework2DBiome* ResolveBiome(int32 BiomeId) const;

	/** Vacia (-1) toda pieza de bioma cuyo valor cumpla la condicion (al borrar un flipbook, un generador o una pagina). Devuelve cuantas. */
	int32 ClearBiomeValues(TFunctionRef<bool(int32)> Predicate);

	//---------------------- Objetos grandes ----------------------

	/** Id del objeto que usa esa imagen; si no hay, lo crea. INDEX_NONE sin imagen. */
	int32 FindOrAddProp(UTexture2D* Texture);

	/** Id del objeto que es ese trozo del atlas (tile de arriba-izquierda y tamano en tiles); si no hay, lo crea. */
	int32 FindOrAddAtlasProp(int32 TopLeftTile, int32 WidthTiles, int32 HeightTiles, FName Name = NAME_None);

	/** Quita el objeto (y sus usos en los biomas). Las colocaciones de los mapas dejan de verse. */
	bool RemoveProp(int32 PropId);

	int32 FindPropIndex(int32 PropId) const;
	const FFramework2DPropDef* FindPropById(int32 PropId) const;

	/** Pixeles de la imagen de un objeto (fila 0 arriba). Editor: del PNG original; juego: de la copia guardada. */
	bool ReadPropPixels(int32 PropId, TArray<FColor>& OutPixels, int32& OutWidth, int32& OutHeight) const;

	/** Tamano de la imagen de un objeto en pixeles (false si no hay imagen legible). */
	bool GetPropSize(int32 PropId, int32& OutWidth, int32& OutHeight) const;

	//---------------------- Flipbooks ----------------------

	/** Crea un flipbook con esos fotogramas y devuelve su Id. Material = el del primer fotograma. */
	int32 AddFlipbook(const TArray<int32>& Frames, FName Name = NAME_None);

	/** Quita el flipbook con ese Id. Las celdas que lo usaban quedan vacias. */
	bool RemoveFlipbook(int32 FlipbookId);

	/** Indice en Flipbooks del flipbook con ese Id (INDEX_NONE si no existe). */
	int32 FindFlipbookIndex(int32 FlipbookId) const;

	/** Flipbook al que apunta un valor de celda (nullptr si el valor es un tile o vacio). */
	const FFramework2DFlipbook* FindFlipbookByValue(int32 Value) const;
	FFramework2DFlipbook* FindFlipbookById(int32 FlipbookId);

	/** True si el valor es un flipbook que existe y tiene 2 o mas fotogramas. */
	bool IsAnimated(int32 Value) const;

	/** Tile del atlas que se ve en el instante Time (s) para ese valor (-1 si no hay). */
	int32 GetFrameTile(int32 Value, double Time) const;

	/** Primer fotograma (o el propio tile). -1 si el valor no dibuja nada. */
	int32 GetFirstFrameTile(int32 Value) const { return GetFrameTile(Value, 0.0); }

	//---------------------- Propiedades de un valor de celda ----------------------

	/** Material de un tile o flipbook (None si no tiene o el valor no es valido). */
	FName GetTileMaterial(int32 Value) const;

	/** Colision de un tile o flipbook. */
	EFramework2DCollisionShape GetTileCollision(int32 Value) const;

	/** True si el valor apunta a algo que existe (tile del atlas o flipbook). */
	bool IsValidValue(int32 Value) const;

	//---------------------- Atlas ----------------------

	/** Pixel superior-izquierdo del tile numero Index (sin pagina) dentro de una imagen de AtlasWidth px. */
	bool GetTilePixelOrigin(int32 Index, int32 AtlasWidth, int32& OutX, int32& OutY) const;

	/** Tamano del atlas en pixeles (0 si no hay atlas legible). */
	bool GetAtlasSize(int32& OutWidth, int32& OutHeight) const;

	/**
	 * Copia los pixeles del atlas (fila 0 arriba, FColor BGRA). Editor: del PNG original.
	 * Juego empaquetado: de la copia que se guarda con el tileset. false si no se pudo.
	 */
	bool ReadAtlasPixels(TArray<FColor>& OutPixels, int32& OutWidth, int32& OutHeight) const;

	/** Recalcula columnas/filas de todas las paginas y ajusta sus listas Tiles (conserva lo que habia). */
	void RefreshTilesFromAtlas();

	/** Pasa los flipbooks antiguos (AnimationFrames dentro de un tile) a la lista Flipbooks. Devuelve cuantos. */
	int32 MigrateLegacyFlipbooks();

	virtual void PostLoad() override;
	virtual void PreSave(FObjectPreSaveContext SaveContext) override;
#if WITH_EDITOR
	virtual void PreEditChange(FProperty* PropertyAboutToChange) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
#if WITH_EDITORONLY_DATA
	// Ids de los flipbooks antes de una edicion en Details (para deshacer un Id pegado).
	TArray<int32> PreEditFlipbookIds;
#endif

	// Siguiente Id libre para flipbooks (nunca se reutilizan).
	UPROPERTY()
	int32 NextFlipbookId = 1;

	// Siguientes Ids libres de paginas extra y generadores (nunca se reutilizan).
	UPROPERTY()
	int32 NextAtlasId = 1;

	UPROPERTY()
	int32 NextGeneratorId = 1;

	UPROPERTY()
	int32 NextBiomeId = 1;

	UPROPERTY()
	int32 NextPropId = 1;

	void RefreshPage(FFramework2DAtlasPage& Page);
	void FixUpIds();

	// Copia CPU del atlas para el juego empaquetado (no tiene el PNG original). Se rellena al guardar.
	UPROPERTY()
	TArray<FColor> AtlasPixelCache;

	UPROPERTY()
	int32 AtlasCacheWidth = 0;

	UPROPERTY()
	int32 AtlasCacheHeight = 0;
};
