// Copyright Chema Luque. Plugin Framework2DTerrain (modulo Editor).

#pragma once

#include "CoreMinimal.h"
#include "EdMode.h"
#include "Framework2DTerrainTypes.h"
#include "Framework2DProcGenTypes.h"

class AFramework2DTerrainWorld;
class UFramework2DTileMapAsset;
class UFramework2DTileSet;
class FCanvas;
class FSceneView;
class UTexture2D;
struct FFramework2DGenerator;

/** Herramientas del modo de pintado (como las del editor de tilemaps de Unreal). */
enum class EFramework2DTileTool : uint8
{
	Paint,      // Pincel (B)
	Erase,      // Borrador (E)
	Fill,       // Cubo de relleno (G)
	Rect,       // Rectangulo (R)
	Pick,       // Cuentagotas (I)
	Collision   // Pincel de colision (C)
};

/**
 * FFramework2DTilePaintMode
 * =================================================================
 * Modo "Framework2D Tiles" de la barra de modos del editor. Con el panel de la izquierda
 * eliges herramienta, capa y tile (o flipbook); en el viewport pintas sobre el terreno
 * seleccionado (o el primero del nivel). Antes de hacer clic ves una vista previa
 * semitransparente de lo que vas a pintar. Cada trazo es un paso de Ctrl+Z.
 */
class FRAMEWORK2DTERRAINEDITOR_API FFramework2DTilePaintMode : public FEdMode
{
public:
	static const FEditorModeID ModeId;

	FFramework2DTilePaintMode();

	//~ FEdMode
	virtual void Enter() override;
	virtual void Exit() override;
	virtual bool UsesToolkits() const override { return true; }
	virtual bool InputKey(FEditorViewportClient* ViewportClient, FViewport* Viewport, FKey Key, EInputEvent Event) override;
	virtual bool MouseMove(FEditorViewportClient* ViewportClient, FViewport* Viewport, int32 X, int32 Y) override;
	virtual bool CapturedMouseMove(FEditorViewportClient* ViewportClient, FViewport* Viewport, int32 X, int32 Y) override;
	virtual bool MouseLeave(FEditorViewportClient* ViewportClient, FViewport* Viewport) override;
	virtual bool LostFocus(FEditorViewportClient* ViewportClient, FViewport* Viewport) override;
	virtual bool StartTracking(FEditorViewportClient* ViewportClient, FViewport* Viewport) override { return true; }
	virtual bool EndTracking(FEditorViewportClient* ViewportClient, FViewport* Viewport) override { return true; }
	virtual bool DisallowMouseDeltaTracking() const override { return bStrokeActive; }
	virtual bool AllowWidgetMove() override { return false; }
	virtual bool ShouldDrawWidget() const override { return false; }
	virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;
	virtual void DrawHUD(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas) override;

	//~ Estado que comparte el panel
	EFramework2DTileTool Tool = EFramework2DTileTool::Paint;
	int32 SelectedTile = 0;                       // valor del tile de arriba-izquierda de la seleccion (pagina + numero)
	FIntRect BrushRect = FIntRect(0, 0, 0, 0);    // seleccion en el atlas, en tiles (Min..Max incluidos)
	int32 BrushPage = 0;                          // pagina del atlas de BrushRect
	int32 ActivePage = 0;                         // pagina que se ve en la paleta
	int32 BrushFlipbookId = INDEX_NONE;           // flipbook elegido como pincel (si no es INDEX_NONE, manda sobre BrushRect)
	int32 BrushGeneratorId = INDEX_NONE;          // generador elegido como pincel (igual)
	EFramework2DCollisionShape CollisionBrush = EFramework2DCollisionShape::Full; // forma del pincel de colision
	int32 ActiveLayer = 0;
	bool bShowGrid = true;
	bool bShowCollision = false;                  // dibujar la colision en el viewport (siempre con la herramienta Colision)
	bool bShowGhost = true;                       // vista previa de lo que se va a pintar

	/** Terreno sobre el que se pinta: el seleccionado, si no el ultimo usado, si no el primero del nivel. */
	AFramework2DTerrainWorld* GetTarget() const;
	UFramework2DTileMapAsset* GetTileMap() const;
	UFramework2DTileSet* GetTileSet() const;

	static FText GetToolName(EFramework2DTileTool InTool);     // "Pincel"
	static FText GetToolShortcut(EFramework2DTileTool InTool); // "B"
	static FText GetToolHelp(EFramework2DTileTool InTool);     // frase para el tooltip
	static FText GetShapeName(EFramework2DCollisionShape Shape);
	static FText GetShapeHelp(EFramework2DCollisionShape Shape);

	//~ Capas (desde el panel; con deshacer y vista previa)
	void AddLayer();
	void RemoveActiveLayer();
	void MoveActiveLayer(int32 Delta);            // +1 = hacia delante, -1 = hacia atras
	void RenameLayer(int32 Layer, const FText& NewName);
	void SetLayerVisible(int32 Layer, bool bVisible);
	void SetLayerBackground(int32 Layer, bool bBackground);
	void SetLayerCollides(int32 Layer, bool bCollides);
	void SetLayerBreakable(int32 Layer, bool bBreakable);
	float GetLayerSeparation() const;
	void SetLayerSeparation(float Separation, bool bFinal); // bFinal=false mientras se arrastra el valor
	void RefreshPreview();

	//~ Paginas del atlas (una pestana por imagen)
	int32 GetPageColumns(int32 PageId) const;
	int32 GetPageRows(int32 PageId) const;
	void SetActivePage(int32 PageId);
	int32 AddAtlasPage(UTexture2D* Texture);           // devuelve el Id de la pagina y la deja activa
	void RemoveAtlasPage(int32 PageId);                // tambien vacia las celdas del mapa actual que la usaban
	void SetPageTexture(int32 PageId, UTexture2D* Texture);
	void RenamePage(int32 PageId, const FText& NewName);

	//~ Seleccion del atlas (pincel de varios tiles)
	int32 GetAtlasColumns() const;                     // de la pagina activa
	int32 GetAtlasRows() const;
	void SelectAtlasRect(const FIntRect& AtlasRect);   // en la pagina activa; deja de usar flipbook/generador
	bool IsFlipbookBrush() const;                      // hay un flipbook valido elegido como pincel
	bool IsGeneratorBrush() const;                     // hay un generador valido elegido como pincel
	bool IsSpecialBrush() const { return IsFlipbookBrush() || IsGeneratorBrush(); }
	/** Valores de tile (pagina + numero) de la seleccion del atlas, en orden de lectura. */
	void GetSelectionTileValues(TArray<int32>& OutValues) const;
	int32 BrushWidth() const;                          // 1 con un flipbook o un generador
	int32 BrushHeight() const;
	/** Valor del pincel para la posicion (Dx,Dy) dentro del patron (se repite con modulo). */
	int32 BrushTile(int32 Dx, int32 Dy) const;

	//~ Propiedades de los tiles seleccionados en el atlas (se guardan en el TileSet)
	FName GetSelectionMaterial(bool& bOutMixed) const;
	void SetSelectionMaterial(FName Material);
	EFramework2DCollisionShape GetSelectionCollision(bool& bOutMixed) const;
	void SetSelectionCollision(EFramework2DCollisionShape Shape);

	//~ Flipbooks (lista propia del TileSet: no tocan los tiles del atlas)
	bool CanCreateFlipbook() const { return !IsSpecialBrush() && BrushWidth() * BrushHeight() > 1; }
	int32 CreateFlipbookFromSelection();               // devuelve el Id y lo deja como pincel
	void SelectFlipbook(int32 FlipbookId);
	void DeleteFlipbook(int32 FlipbookId);             // tambien vacia las celdas del mapa actual que lo usaban
	void RenameFlipbook(int32 FlipbookId, const FText& NewName);
	void SetFlipbookFPS(int32 FlipbookId, float FPS);
	void SetFlipbookMaterial(int32 FlipbookId, FName Material);
	void SetFlipbookCollision(int32 FlipbookId, EFramework2DCollisionShape Shape);
	void SetFlipbookFramesFromSelection(int32 FlipbookId);

	//~ Generadores de vegetacion (lista propia del TileSet; se pintan como un tile)
	bool CanUseSelectionAsSprites() const { return !IsSpecialBrush(); }
	int32 CreateGeneratorFromSelection();              // un sprite por tile de la seleccion; lo deja como pincel
	void SelectGenerator(int32 GeneratorId);
	void DeleteGenerator(int32 GeneratorId);           // tambien vacia las celdas del mapa actual que lo usaban
	void RenameGenerator(int32 GeneratorId, const FText& NewName);
	/** Anade la seleccion del atlas: cada tile como un sprite, o el bloque entero como uno solo. */
	void AddSelectionToGenerator(int32 GeneratorId, bool bAsOneSprite);
	void RemoveGeneratorSprite(int32 GeneratorId, int32 SpriteIndex);
	/** Cambia un generador con un paso de deshacer y rehace la vista previa (si algo cambio). */
	void ChangeGenerator(int32 GeneratorId, const FText& Description, TFunctionRef<void(FFramework2DGenerator&)> Change);
	const FFramework2DGenerator* GetGenerator(int32 GeneratorId) const;

	//~ Pincel de colision
	void SetCollisionBrush(EFramework2DCollisionShape Shape); // y activa la herramienta Colision

	//~ Generacion procedural (pestana "Generar" del panel). Los biomas viven en el TileSet y la
	//~ receta en el Tile Map; cada cambio es un paso de deshacer. Con bAutoGenerate, el mapa se
	//~ regenera en ESE MISMO paso (Ctrl+Z deshace el ajuste y el mapa a la vez).
	bool bAutoGenerate = true;
	FFramework2DProcGenReport LastGenerateReport;  // lo que salio en la ultima generacion
	bool bHasGenerateReport = false;

	/** Valor de celda del pincel actual: flipbook, generador o el tile de arriba-izquierda de la seleccion. -1 si nada. */
	int32 GetBrushValue() const;

	/** Bioma que se edita = el de la receta del mapa (o el primero del TileSet). nullptr si no hay. */
	const FFramework2DBiome* GetActiveBiome() const;
	int32 GetActiveBiomeId() const;                    // INDEX_NONE si no hay
	void SetActiveBiome(int32 BiomeId);                // cambia la receta del mapa
	int32 CreateBiome();                               // vacio; lo deja activo. Devuelve su Id
	void DeleteBiome(int32 BiomeId);
	void RenameBiome(int32 BiomeId, const FText& NewName);
	/** Cambia un bioma con un paso de deshacer (solo si algo cambia). */
	void ChangeBiome(int32 BiomeId, const FText& Description, TFunctionRef<void(FFramework2DBiome&)> Change);
	void SetBiomeSlot(int32 BiomeId, EFramework2DBiomeSlot Slot, int32 Value); // -1 = vaciar
	/** Rellena el 3x3 (de terreno o de fondo) con el bloque de 3x3 tiles cuya esquina de arriba-izquierda es ese tile. */
	void SetBiome3x3FromBlock(int32 BiomeId, bool bBackground, int32 TopLeftTileValue);
	bool CanUseSelectionAs3x3() const;                 // la seleccion del atlas es un bloque de 3x3 (y no hay flipbook/generador de pincel)
	void SetBiome3x3FromSelection(int32 BiomeId, bool bBackground);
	/** Igual para el terreno 5x5 (bloque de 5x5 tiles). */
	void SetBiome5x5FromBlock(int32 BiomeId, int32 TopLeftTileValue);
	bool CanUseSelectionAs5x5() const;
	void SetBiome5x5FromSelection(int32 BiomeId);
	/** La seleccion del atlas de la pestana «Pintar» como bloque: tile de arriba-izquierda y tamano
	 *  en tiles. False sin seleccion del atlas o si es mas grande que MaxWidth x MaxHeight. */
	bool GetSelectionBlock(int32& OutTile, int32& OutWidth, int32& OutHeight, int32 MaxWidth = 64, int32 MaxHeight = 64) const;
	void AddBiomeCenterVariant(int32 BiomeId, int32 Value);
	void RemoveBiomeCenterVariant(int32 BiomeId, int32 Index);
	void AddBiomeDecoration(int32 BiomeId, int32 Value, EFramework2DDecorPlacement Placement = EFramework2DDecorPlacement::Ground);
	void RemoveBiomeDecoration(int32 BiomeId, int32 Index);
	/** Objeto grande Index del bioma: pone su imagen (crea el objeto en el TileSet si hace falta). Un paso de deshacer. */
	void SetBiomePropTexture(int32 BiomeId, int32 Index, UTexture2D* Texture);
	/**
	 * Bioma de EJEMPLO a partir de una pagina con la distribucion de Ejemplo/AtlasBioma.png:
	 * crea sus flipbooks (agua, cascada, antorcha) y generadores (hierba, rocas...), pone el
	 * material de sus tiles y lo deja activo. Un solo paso de deshacer. Devuelve su Id.
	 */
	int32 CreateExampleBiome(int32 PageId);
	/**
	 * Ejemplo de EXTERIORES (un clic): importa al proyecto (/Game/Framework2D_Ejemplo) las
	 * imagenes de Ejemplo/ del plugin (AtlasBioma, AtlasExterior, fondos parallax y objetos
	 * grandes), las pone como paginas del atlas, crea el bioma «Bosque exterior» (con puentes,
	 * bordes naturales, fondos y arboles), pone una receta de lomas e islas y genera el mapa.
	 * Devuelve el Id del bioma (INDEX_NONE si algo falla).
	 */
	int32 CreateExampleOutdoorBiome();
	/**
	 * Plantilla para un atlas con la distribucion de T_Tiles (25 x 25 tiles de 16 px): terreno 5x5
	 * de hierba (filas 0-4) y de roca (filas 5-9), agua, cascada, puente con postes, tablon, flores,
	 * setas, espadanas y objetos grandes del propio atlas (copas de arboles y rocas). Crea los biomas
	 * «Bosque (T_Tiles)» y «Roca (T_Tiles)» con la pagina PageId y deja activo el primero. Un paso
	 * de deshacer. Devuelve el Id del bosque.
	 */
	int32 CreateTTilesBiomes(int32 PageId);

	/** Receta del mapa actual (nullptr sin mapa). */
	const FFramework2DProcGenSettings* GetProcGenSettings() const;
	/** Cambia la receta con un paso de deshacer (solo si algo cambia). */
	void ChangeProcGenSettings(const FText& Description, TFunctionRef<void(FFramework2DProcGenSettings&)> Change);
	/** Cambia el tamano del mapa (tiles) con deshacer. */
	void ResizeMap(int32 NewWidth, int32 NewHeight);
	/** Genera el mapa con su receta en un paso de deshacer y rehace la vista previa. bNewSeed = otra semilla antes. */
	bool GenerateMap(bool bNewSeed);
	/** Que impide generar ahora mismo (vacio = se puede). */
	FText GetGenerateProblem() const;

	/** Pruebas automaticas: simula el raton encima del tile (Tx, Ty) (-1 = fuera). */
	void SetHoverTileForTesting(int32 Tx, int32 Ty) { HoverTx = Tx; HoverTy = Ty; }

private:
	bool bStrokeActive = false;
	bool bStrokeChanged = false;
	int32 TransactionIndex = INDEX_NONE;
	int32 HoverTx = -1;
	int32 HoverTy = -1;
	FIntPoint LastTile = FIntPoint(-1, -1);
	FIntPoint RectStart = FIntPoint(-1, -1);
	FIntPoint StrokeOrigin = FIntPoint(0, 0); // ancla del patron del pincel durante el trazo
	FIntRect PendingDirty;
	bool bHasPendingDirty = false;
	mutable TWeakObjectPtr<AFramework2DTerrainWorld> CachedTarget;

	// Arrastre de la separacion de capas: valor de antes de arrastrar (para que Ctrl+Z vuelva a el).
	float SeparationBeforeDrag = 0.0f;
	bool bDraggingSeparation = false;

	// Colision dibujada en el viewport (se recalcula solo cuando cambia el terreno).
	TArray<FIntRect> CachedCollisionRects;
	uint32 CachedCollisionRevision = MAX_uint32;
	TWeakObjectPtr<AFramework2DTerrainWorld> CachedCollisionTarget;

	bool CursorToTile(FEditorViewportClient* ViewportClient, FViewport* Viewport, int32& OutTx, int32& OutTy) const;
	void TrackMouse(FEditorViewportClient* ViewportClient, FViewport* Viewport);
	void BeginStroke(int32 Tx, int32 Ty);
	void ContinueStroke(int32 Tx, int32 Ty);
	void EndStroke();
	void ApplyAt(int32 Tx, int32 Ty);
	void FloodFillPattern(int32 Tx, int32 Ty);
	void PickAt(int32 Tx, int32 Ty);
	void PrepareChange();
	void TouchRect(const FIntRect& TileRect);
	void FlushPreview();
	void ChangeLayers(const FText& Description, TFunctionRef<void(UFramework2DTileMapAsset*)> Change);
	void ChangeTileSet(const FText& Description, TFunctionRef<void(UFramework2DTileSet*)> Change);

	// Vista previa y colision: contornos en Render (3D); rellenos semitransparentes en DrawHUD.
	void DrawGhost(const FSceneView* View, FCanvas* Canvas, AFramework2DTerrainWorld* Target);
	void DrawCollisionOverlay(FPrimitiveDrawInterface* PDI, AFramework2DTerrainWorld* Target);
	void DrawCollisionFill(const FSceneView* View, FCanvas* Canvas, AFramework2DTerrainWorld* Target);
	void RefreshCollisionCache(AFramework2DTerrainWorld* Target);
	float GetCollisionOverlayDepth(const AFramework2DTerrainWorld* Target) const;
};
