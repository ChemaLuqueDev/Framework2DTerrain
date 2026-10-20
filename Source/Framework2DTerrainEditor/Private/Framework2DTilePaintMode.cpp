// Copyright Chema Luque. Plugin Framework2DTerrain (modulo Editor).

#include "Framework2DTilePaintMode.h"

#include "SFramework2DTilePalette.h"
#include "Framework2DEditorStyle.h"
#include "Framework2DProcGen.h"
#include "Framework2DTerrainWorld.h"
#include "Framework2DTileMapAsset.h"
#include "Framework2DTileSet.h"

#include "CanvasItem.h"
#include "CanvasTypes.h"
#include "Editor.h"
#include "EditorModeManager.h"
#include "EditorViewportClient.h"
#include "Engine/Engine.h"
#include "Engine/Font.h"
#include "Engine/Selection.h"
#include "Engine/Texture.h"
#include "Engine/Texture2D.h"
#include "EngineUtils.h"
#include "HAL/PlatformTime.h"
#include "SceneManagement.h"
#if __has_include("GlobalRenderResources.h")
#include "GlobalRenderResources.h" // GWhiteTexture (5.2+)
#else
#include "RenderUtils.h"           // GWhiteTexture (5.0/5.1)
#endif
#include "SceneView.h"
#include "ScopedTransaction.h"
#include "Toolkits/BaseToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "UnrealClient.h"
#include "UObject/Package.h"
#include "AssetToolsModule.h"
#include "AutomatedAssetImportData.h"
#include "IAssetTools.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/PackageName.h"
#include "Misc/Paths.h"

#define LOCTEXT_NAMESPACE "Framework2DTilePaintMode"

const FEditorModeID FFramework2DTilePaintMode::ModeId(TEXT("EM_Framework2DTilePaint"));

// =====================================================================
//  Toolkit: el panel de la izquierda del modo
// =====================================================================
class FFramework2DTilePaintToolkit : public FModeToolkit
{
public:
	explicit FFramework2DTilePaintToolkit(FFramework2DTilePaintMode* InMode) : Mode(InMode) {}

	virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost) override
	{
		Palette = SNew(SFramework2DTilePalette, Mode);
		FModeToolkit::Init(InitToolkitHost);
	}
	virtual FName GetToolkitFName() const override { return FName("Framework2DTilePaint"); }
	virtual FText GetBaseToolkitName() const override { return LOCTEXT("ToolkitName", "Framework2D Tiles"); }
	virtual FEdMode* GetEditorMode() const override { return Mode; }
	virtual TSharedPtr<SWidget> GetInlineContent() const override { return Palette; }

private:
	FFramework2DTilePaintMode* Mode = nullptr;
	TSharedPtr<SFramework2DTilePalette> Palette;
};

// =====================================================================
//  Ayudantes (nombres con prefijo: el modulo se compila en unity build)
// =====================================================================

// Limites de seguridad del dibujo en el viewport.
static constexpr int32 Framework2DModeMaxGhostTiles = 4096;
static constexpr int32 Framework2DModeMaxCollisionRects = 20000;

/** Patron del pincel ya resuelto: evita buscar terreno y tileset por cada tile de un trazo. */
struct FFramework2DModeBrushPattern
{
	int32 W = 1;
	int32 H = 1;
	int32 Cols = 1;
	int32 PageId = 0;
	FIntPoint Origin = FIntPoint(0, 0);
	int32 SingleValue = INDEX_NONE; // flipbook o generador: todo el patron es ese valor

	int32 At(int32 Dx, int32 Dy) const
	{
		if (SingleValue != INDEX_NONE) { return SingleValue; }
		const int32 Mx = ((Dx % W) + W) % W;
		const int32 My = ((Dy % H) + H) % H;
		return Framework2D::MakeTileValue(PageId, (Origin.Y + My) * Cols + (Origin.X + Mx));
	}
};

static FFramework2DModeBrushPattern Framework2DModeMakePattern(const FFramework2DTilePaintMode& Mode)
{
	FFramework2DModeBrushPattern P;
	if (Mode.IsGeneratorBrush())
	{
		P.SingleValue = Framework2D::MakeGeneratorValue(Mode.BrushGeneratorId);
		return P;
	}
	if (Mode.IsFlipbookBrush())
	{
		P.SingleValue = Framework2D::MakeFlipbookValue(Mode.BrushFlipbookId);
		return P;
	}
	P.W = FMath::Max(1, Mode.BrushRect.Max.X - Mode.BrushRect.Min.X + 1);
	P.H = FMath::Max(1, Mode.BrushRect.Max.Y - Mode.BrushRect.Min.Y + 1);
	P.Cols = Mode.GetPageColumns(Mode.BrushPage);
	P.PageId = Mode.BrushPage;
	P.Origin = Mode.BrushRect.Min;
	return P;
}

/** Rectangulo del plano XZ local (L..R en X, B..T en Z) en la profundidad Depth, con lineas. */
static void Framework2DModeDrawLocalRect(FPrimitiveDrawInterface* PDI, const FTransform& Xf, float L, float R, float B, float T,
	float Depth, const FLinearColor& Color, float Thickness)
{
	const FVector P[4] = {
		Xf.TransformPosition(FVector(L, Depth, B)), Xf.TransformPosition(FVector(R, Depth, B)),
		Xf.TransformPosition(FVector(R, Depth, T)), Xf.TransformPosition(FVector(L, Depth, T)) };
	for (int32 i = 0; i < 4; ++i)
	{
		PDI->DrawLine(P[i], P[(i + 1) % 4], Color, SDPG_Foreground, Thickness);
	}
}

static void Framework2DDrawTileRect(FPrimitiveDrawInterface* PDI, const FTransform& Xf, float TS, int32 MapH, float Depth,
	int32 X0, int32 Y0, int32 X1, int32 Y1, const FLinearColor& Color, float Thickness)
{
	// Tiles [X0..X1] x [Y0..Y1] (fila 0 arriba) -> rectangulo en el plano de la capa.
	Framework2DModeDrawLocalRect(PDI, Xf, X0 * TS, (X1 + 1) * TS, (MapH - 1 - Y1) * TS, (MapH - Y0) * TS, Depth, Color, Thickness);
}

/** Un quad en espacio LOCAL del actor (L..R en X, B..T en Z, a la profundidad Y). UV0 arriba-izquierda. */
struct FFramework2DModeQuad
{
	float L, R, B, T, Y;
	FVector2f UV0, UV1;
	FColor Color;
};

static void Framework2DModeAddQuad(TArray<FFramework2DModeQuad>& Out, float L, float R, float B, float T, float Y,
	const FVector2f& UV0, const FVector2f& UV1, const FColor& Color)
{
	Out.Add(FFramework2DModeQuad{ L, R, B, T, Y, UV0, UV1, Color });
}

/**
 * Dibuja los quads en el lienzo del viewport, proyectando sus esquinas. Va por el HUD y no
 * como malla del modo porque el editor descarta las mallas translucidas de los modos cuyo
 * material se pinta despues del DOF (como los sprites de Paper2D): asi se ve siempre, encima.
 */
static void Framework2DModeDrawQuads(FCanvas* Canvas, const FSceneView* View, const FTransform& Xf,
	const TArray<FFramework2DModeQuad>& Quads, const FTexture* Texture)
{
	if (!Canvas || !View || !Texture || Quads.Num() == 0) { return; }
	const float InvDPI = 1.0f / FMath::Max(0.1f, Canvas->GetDPIScale()); // pixeles de render -> unidades del lienzo
	TArray<FCanvasUVTri> Tris;
	Tris.Reserve(Quads.Num() * 2);
	for (const FFramework2DModeQuad& Q : Quads)
	{
		const FVector Corners[4] = { FVector(Q.L, Q.Y, Q.T), FVector(Q.R, Q.Y, Q.T), FVector(Q.R, Q.Y, Q.B), FVector(Q.L, Q.Y, Q.B) };
		FVector2D P[4];
		bool bVisible = true;
		for (int32 k = 0; k < 4 && bVisible; ++k)
		{
			// WorldToPixel no avisa de lo que queda detras de la camara (lo devuelve en espejo).
			const FVector4 Screen = View->WorldToScreen(Xf.TransformPosition(Corners[k]));
			bVisible = Screen.W > KINDA_SMALL_NUMBER && View->ScreenToPixel(Screen, P[k]);
			P[k] *= InvDPI;
		}
		if (!bVisible) { continue; }

		const FVector2D UV[4] = { FVector2D(Q.UV0.X, Q.UV0.Y), FVector2D(Q.UV1.X, Q.UV0.Y), FVector2D(Q.UV1.X, Q.UV1.Y), FVector2D(Q.UV0.X, Q.UV1.Y) };
		const FLinearColor C(Q.Color);
		for (int32 t = 0; t < 2; ++t)
		{
			const int32 I1 = t == 0 ? 1 : 2;
			const int32 I2 = t == 0 ? 2 : 3;
			FCanvasUVTri Tri;
			Tri.V0_Pos = P[0];  Tri.V0_UV = UV[0];  Tri.V0_Color = C;
			Tri.V1_Pos = P[I1]; Tri.V1_UV = UV[I1]; Tri.V1_Color = C;
			Tri.V2_Pos = P[I2]; Tri.V2_UV = UV[I2]; Tri.V2_Color = C;
			Tris.Add(Tri);
		}
	}
	if (Tris.Num() == 0) { return; }
	FCanvasTriangleItem Item(Tris, Texture);
	Item.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(Item);
}

/** Tramos (en pixeles del tile, Y=0 arriba) de una forma a medida, unidos por filas iguales. */
static void Framework2DModeShapeRuns(EFramework2DCollisionShape Shape, int32 Size, TArray<FIntRect>& Out)
{
	Out.Reset();
	for (int32 Cy = 0; Cy < Size; ++Cy)
	{
		int32 Cx = 0;
		while (Cx < Size)
		{
			if (!Framework2D::ShapeCovers(Shape, Cx, Cy, Size)) { ++Cx; continue; }
			const int32 Start = Cx;
			while (Cx < Size && Framework2D::ShapeCovers(Shape, Cx, Cy, Size)) { ++Cx; }
			const int32 End = Cx - 1;

			// Si la fila de arriba tenia el mismo tramo, se alarga (mitades y bloques = un quad).
			bool bMerged = false;
			for (FIntRect& Prev : Out)
			{
				if (Prev.Max.Y == Cy - 1 && Prev.Min.X == Start && Prev.Max.X == End)
				{
					Prev.Max.Y = Cy;
					bMerged = true;
					break;
				}
			}
			if (!bMerged) { Out.Add(FIntRect(Start, Cy, End, Cy)); }
		}
	}
}

/** Pastilla (rectangulo con los extremos redondos) para el HUD, en unidades logicas del lienzo. */
static void Framework2DModeDrawPill(FCanvas* Canvas, float X, float Y, float W, float H, float DPIScale, const FLinearColor& Color)
{
	auto DrawRect = [Canvas, &Color](float RX, float RY, float RW, float RH)
	{
		if (RW <= 0.0f || RH <= 0.0f) { return; }
		FCanvasTileItem Item(FVector2D(RX, RY), FVector2D(RW, RH), Color);
		Item.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(Item);
	};

	const float Radius = FMath::Min(H * 0.5f, W * 0.5f);
	DrawRect(X + Radius, Y, W - 2.0f * Radius, H);

	// Extremos: columnas de un pixel fisico cuya altura sigue el semicirculo. Sin solapes,
	// asi la transparencia queda uniforme.
	const int32 Steps = FMath::Max(1, FMath::CeilToInt(Radius * DPIScale));
	const float StepW = Radius / Steps;
	for (int32 i = 0; i < Steps; ++i)
	{
		const float Dx = Radius - (i + 0.5f) * StepW;
		const float Half = FMath::Sqrt(FMath::Max(0.0f, Radius * Radius - Dx * Dx));
		const float ColY = Y + H * 0.5f - Half;
		DrawRect(X + i * StepW, ColY, StepW, 2.0f * Half);
		DrawRect(X + W - (i + 1) * StepW, ColY, StepW, 2.0f * Half);
	}
}

/** Descripcion del paso de deshacer de un trazo. */
static FText Framework2DModeStrokeName(EFramework2DTileTool InTool)
{
	switch (InTool)
	{
	case EFramework2DTileTool::Paint:     return LOCTEXT("StrokePaint", "Paint tiles");
	case EFramework2DTileTool::Erase:     return LOCTEXT("StrokeErase", "Erase tiles");
	case EFramework2DTileTool::Fill:      return LOCTEXT("StrokeFill", "Fill area");
	case EFramework2DTileTool::Rect:      return LOCTEXT("StrokeRect", "Fill rectangle");
	case EFramework2DTileTool::Pick:      return LOCTEXT("StrokePick", "Eyedropper");
	case EFramework2DTileTool::Collision: return LOCTEXT("StrokeCollision", "Paint collision");
	}
	return FText::GetEmpty();
}

// =====================================================================
//  Ciclo de vida
// =====================================================================
FFramework2DTilePaintMode::FFramework2DTilePaintMode()
{
}

void FFramework2DTilePaintMode::Enter()
{
	FEdMode::Enter();
	if (!Toolkit.IsValid())
	{
		Toolkit = MakeShareable(new FFramework2DTilePaintToolkit(this));
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FFramework2DTilePaintMode::Exit()
{
	if (bStrokeActive) { EndStroke(); }
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}
	CachedCollisionRects.Reset();
	CachedCollisionRevision = MAX_uint32;
	CachedCollisionTarget.Reset();
	bDraggingSeparation = false;
	FEdMode::Exit();
}

// =====================================================================
//  Textos de la interfaz
// =====================================================================
FText FFramework2DTilePaintMode::GetToolName(EFramework2DTileTool InTool)
{
	switch (InTool)
	{
	case EFramework2DTileTool::Paint:     return LOCTEXT("ToolPaint", "Brush");
	case EFramework2DTileTool::Erase:     return LOCTEXT("ToolErase", "Eraser");
	case EFramework2DTileTool::Fill:      return LOCTEXT("ToolFill", "Bucket");
	case EFramework2DTileTool::Rect:      return LOCTEXT("ToolRect", "Rectangle");
	case EFramework2DTileTool::Pick:      return LOCTEXT("ToolPick", "Eyedropper");
	case EFramework2DTileTool::Collision: return LOCTEXT("ToolCollision", "Collision");
	}
	return FText::GetEmpty();
}

FText FFramework2DTilePaintMode::GetToolShortcut(EFramework2DTileTool InTool)
{
	switch (InTool)
	{
	case EFramework2DTileTool::Paint:     return FText::FromString(TEXT("B"));
	case EFramework2DTileTool::Erase:     return FText::FromString(TEXT("E"));
	case EFramework2DTileTool::Fill:      return FText::FromString(TEXT("G"));
	case EFramework2DTileTool::Rect:      return FText::FromString(TEXT("R"));
	case EFramework2DTileTool::Pick:      return FText::FromString(TEXT("I"));
	case EFramework2DTileTool::Collision: return FText::FromString(TEXT("C"));
	}
	return FText::GetEmpty();
}

FText FFramework2DTilePaintMode::GetToolHelp(EFramework2DTileTool InTool)
{
	switch (InTool)
	{
	case EFramework2DTileTool::Paint:     return LOCTEXT("HelpPaint", "Paints the chosen tile, block or flipbook. Drag to keep painting.");
	case EFramework2DTileTool::Erase:     return LOCTEXT("HelpErase", "Erases the tiles of the active layer under the brush footprint.");
	case EFramework2DTileTool::Fill:      return LOCTEXT("HelpFill", "Fills the connected area of matching tiles with the chosen pattern.");
	case EFramework2DTileTool::Rect:      return LOCTEXT("HelpRect", "Drag to fill a rectangle with the chosen pattern.");
	case EFramework2DTileTool::Pick:      return LOCTEXT("HelpPick", "Copies the tile or flipbook under the mouse and makes it the brush.");
	case EFramework2DTileTool::Collision: return LOCTEXT("HelpCollision", "Paints collision shapes tile by tile, shared by all layers. Automatic = remove.");
	}
	return FText::GetEmpty();
}

FText FFramework2DTilePaintMode::GetShapeName(EFramework2DCollisionShape Shape)
{
	switch (Shape)
	{
	case EFramework2DCollisionShape::Auto:       return LOCTEXT("ShapeAuto", "Automatic");
	case EFramework2DCollisionShape::None:       return LOCTEXT("ShapeNone", "No collision");
	case EFramework2DCollisionShape::Pixels:     return LOCTEXT("ShapePixels", "Drawing pixels");
	case EFramework2DCollisionShape::Full:       return LOCTEXT("ShapeFull", "Full block");
	case EFramework2DCollisionShape::TopHalf:    return LOCTEXT("ShapeTopHalf", "Top half");
	case EFramework2DCollisionShape::BottomHalf: return LOCTEXT("ShapeBottomHalf", "Bottom half");
	case EFramework2DCollisionShape::LeftHalf:   return LOCTEXT("ShapeLeftHalf", "Left half");
	case EFramework2DCollisionShape::RightHalf:  return LOCTEXT("ShapeRightHalf", "Right half");
	case EFramework2DCollisionShape::SlopeUp:    return LOCTEXT("ShapeSlopeUp", "Rising ramp");
	case EFramework2DCollisionShape::SlopeDown:  return LOCTEXT("ShapeSlopeDown", "Falling ramp");
	case EFramework2DCollisionShape::Platform:   return LOCTEXT("ShapePlatform", "Thin platform");
	}
	return FText::GetEmpty();
}

FText FFramework2DTilePaintMode::GetShapeHelp(EFramework2DCollisionShape Shape)
{
	switch (Shape)
	{
	case EFramework2DCollisionShape::Auto:       return LOCTEXT("ShapeHelpAuto", "The default: the drawing's pixels collide when their material collides. With the collision brush, removes the painted shape.");
	case EFramework2DCollisionShape::None:       return LOCTEXT("ShapeHelpNone", "Nothing in this tile collides.");
	case EFramework2DCollisionShape::Pixels:     return LOCTEXT("ShapeHelpPixels", "Every pixel of the drawing collides, even if its material does not.");
	case EFramework2DCollisionShape::Full:       return LOCTEXT("ShapeHelpFull", "The whole tile collides, drawn or not (invisible wall).");
	case EFramework2DCollisionShape::TopHalf:    return LOCTEXT("ShapeHelpTopHalf", "The top half of the tile collides.");
	case EFramework2DCollisionShape::BottomHalf: return LOCTEXT("ShapeHelpBottomHalf", "The bottom half of the tile collides.");
	case EFramework2DCollisionShape::LeftHalf:   return LOCTEXT("ShapeHelpLeftHalf", "The left half of the tile collides.");
	case EFramework2DCollisionShape::RightHalf:  return LOCTEXT("ShapeHelpRightHalf", "The right half of the tile collides.");
	case EFramework2DCollisionShape::SlopeUp:    return LOCTEXT("ShapeHelpSlopeUp", "Ramp rising to the right.");
	case EFramework2DCollisionShape::SlopeDown:  return LOCTEXT("ShapeHelpSlopeDown", "Ramp falling to the right.");
	case EFramework2DCollisionShape::Platform:   return LOCTEXT("ShapeHelpPlatform", "Thin strip at the top of the tile (a quarter of its height).");
	}
	return FText::GetEmpty();
}

// =====================================================================
//  Objetivo: que terreno / tilemap se pinta
// =====================================================================
AFramework2DTerrainWorld* FFramework2DTilePaintMode::GetTarget() const
{
	UWorld* World = GetWorld();
	if (!World) { return nullptr; }

	// 1) El terreno seleccionado en el nivel.
	if (GEditor)
	{
		for (FSelectionIterator It(GEditor->GetSelectedActorIterator()); It; ++It)
		{
			if (AFramework2DTerrainWorld* Selected = Cast<AFramework2DTerrainWorld>(*It))
			{
				CachedTarget = Selected;
				return Selected;
			}
		}
	}
	// 2) El ultimo con el que se pinto.
	if (CachedTarget.IsValid() && CachedTarget->GetWorld() == World) { return CachedTarget.Get(); }
	// 3) El primero del nivel.
	for (TActorIterator<AFramework2DTerrainWorld> It(World); It; ++It)
	{
		CachedTarget = *It;
		return *It;
	}
	return nullptr;
}

UFramework2DTileMapAsset* FFramework2DTilePaintMode::GetTileMap() const
{
	AFramework2DTerrainWorld* Target = GetTarget();
	return Target ? Target->TileMap.Get() : nullptr;
}

UFramework2DTileSet* FFramework2DTilePaintMode::GetTileSet() const
{
	UFramework2DTileMapAsset* Map = GetTileMap();
	return Map ? Map->TileSet.Get() : nullptr;
}

// =====================================================================
//  Raton -> tile
// =====================================================================
bool FFramework2DTilePaintMode::CursorToTile(FEditorViewportClient* ViewportClient, FViewport* Viewport, int32& OutTx, int32& OutTy) const
{
	AFramework2DTerrainWorld* Target = GetTarget();
	UFramework2DTileMapAsset* Map = Target ? Target->TileMap.Get() : nullptr;
	if (!Map || !ViewportClient || !Viewport || Target->TileSize <= 0.0f) { return false; }

	FSceneViewFamilyContext ViewFamily(FSceneViewFamily::ConstructionValues(Viewport, ViewportClient->GetScene(), ViewportClient->EngineShowFlags)
		.SetRealtimeUpdate(ViewportClient->IsRealtime()));
	FSceneView* View = ViewportClient->CalcSceneView(&ViewFamily);
	if (!View) { return false; }
	FVector Origin, Dir;
	View->DeprojectFVector2D(FVector2D(Viewport->GetMouseX(), Viewport->GetMouseY()), Origin, Dir);

	// Cada capa vive en su propio plano XZ local (normal = eje Y del actor): se apunta al plano
	// de la capa activa, para que el tile bajo el raton sea el que se ve en ella.
	const FTransform Xf = Target->GetActorTransform();
	const int32 Layer = FMath::Clamp(ActiveLayer, 0, FMath::Max(0, Map->GetNumLayers() - 1));
	const FVector PlanePoint = Xf.TransformPosition(FVector(0.0, Target->GetLayerDepth(Layer), 0.0));
	const FVector PlaneN = Xf.GetUnitAxis(EAxis::Y);
	const double Denom = FVector::DotProduct(Dir, PlaneN);
	if (FMath::IsNearlyZero(Denom)) { return false; }
	const double T = FVector::DotProduct(PlanePoint - Origin, PlaneN) / Denom;
	if (T < 0.0) { return false; }

	const FVector Local = Xf.InverseTransformPosition(Origin + Dir * T);
	const int32 Tx = FMath::FloorToInt((float)(Local.X / Target->TileSize));
	const int32 Ty = (Map->Height - 1) - FMath::FloorToInt((float)(Local.Z / Target->TileSize)); // fila 0 arriba
	if (Tx < 0 || Tx >= Map->Width || Ty < 0 || Ty >= Map->Height) { return false; }
	OutTx = Tx;
	OutTy = Ty;
	return true;
}

// =====================================================================
//  Input
// =====================================================================
bool FFramework2DTilePaintMode::InputKey(FEditorViewportClient* ViewportClient, FViewport* Viewport, FKey Key, EInputEvent Event)
{
	if (Key == EKeys::LeftMouseButton)
	{
		if (Event == IE_Pressed || Event == IE_DoubleClick)
		{
			if (bStrokeActive) { return true; }
			int32 Tx, Ty;
			if (CursorToTile(ViewportClient, Viewport, Tx, Ty))
			{
				BeginStroke(Tx, Ty);
				return true; // consumido: ni seleccion, ni camara, ni recuadro de seleccion
			}
			return false;    // fuera del mapa: el editor se comporta normal
		}
		if (Event == IE_Released && bStrokeActive)
		{
			EndStroke();
			Viewport->SetPreCaptureMousePosFromSlateCursor();
			return true;
		}
		return bStrokeActive;
	}

	// Atajos de herramienta (sin modificadores y sin navegar con la camara).
	const bool bNavigating = Viewport->KeyState(EKeys::RightMouseButton) || Viewport->KeyState(EKeys::MiddleMouseButton);
	const bool bModifiers = Viewport->KeyState(EKeys::LeftControl) || Viewport->KeyState(EKeys::RightControl) ||
		Viewport->KeyState(EKeys::LeftAlt) || Viewport->KeyState(EKeys::RightAlt) ||
		Viewport->KeyState(EKeys::LeftShift) || Viewport->KeyState(EKeys::RightShift);
	if (Event == IE_Pressed && !bNavigating && !bModifiers && !bStrokeActive)
	{
		if (Key == EKeys::B) { Tool = EFramework2DTileTool::Paint;     return true; }
		if (Key == EKeys::E) { Tool = EFramework2DTileTool::Erase;     return true; }
		if (Key == EKeys::G) { Tool = EFramework2DTileTool::Fill;      return true; }
		if (Key == EKeys::R) { Tool = EFramework2DTileTool::Rect;      return true; }
		if (Key == EKeys::I) { Tool = EFramework2DTileTool::Pick;      return true; }
		if (Key == EKeys::C) { Tool = EFramework2DTileTool::Collision; return true; }
	}
	return false;
}

void FFramework2DTilePaintMode::TrackMouse(FEditorViewportClient* ViewportClient, FViewport* Viewport)
{
	// Un trazo que perdio el boton (Alt+Tab, otra ventana...) se cierra: si no, seguiria
	// pintando al pasar el raton y con su transaccion abierta.
	if (bStrokeActive && Viewport && !Viewport->KeyState(EKeys::LeftMouseButton)) { EndStroke(); }

	if (!CursorToTile(ViewportClient, Viewport, HoverTx, HoverTy))
	{
		HoverTx = HoverTy = -1;
		// Fuera del mapa a mitad de trazo: al volver a entrar no se une con una linea por donde
		// el raton no ha pasado (el rectangulo si conserva su ultima esquina).
		if (bStrokeActive && Tool != EFramework2DTileTool::Rect) { LastTile = FIntPoint(-1, -1); }
	}
	else if (bStrokeActive)
	{
		ContinueStroke(HoverTx, HoverTy);
	}
}

bool FFramework2DTilePaintMode::MouseMove(FEditorViewportClient* ViewportClient, FViewport* Viewport, int32 X, int32 Y)
{
	TrackMouse(ViewportClient, Viewport);
	return false;
}

bool FFramework2DTilePaintMode::CapturedMouseMove(FEditorViewportClient* ViewportClient, FViewport* Viewport, int32 X, int32 Y)
{
	TrackMouse(ViewportClient, Viewport);
	return bStrokeActive;
}

bool FFramework2DTilePaintMode::LostFocus(FEditorViewportClient* ViewportClient, FViewport* Viewport)
{
	if (bStrokeActive) { EndStroke(); }
	return FEdMode::LostFocus(ViewportClient, Viewport);
}

bool FFramework2DTilePaintMode::MouseLeave(FEditorViewportClient* ViewportClient, FViewport* Viewport)
{
	HoverTx = HoverTy = -1;
	return FEdMode::MouseLeave(ViewportClient, Viewport);
}

// =====================================================================
//  Trazos (cada trazo = un paso de deshacer)
// =====================================================================
void FFramework2DTilePaintMode::BeginStroke(int32 Tx, int32 Ty)
{
	UFramework2DTileMapAsset* Map = GetTileMap();
	if (!Map || !GEditor) { return; }

	bStrokeActive = true;
	bStrokeChanged = false;
	LastTile = FIntPoint(Tx, Ty);
	RectStart = FIntPoint(Tx, Ty);
	StrokeOrigin = FIntPoint(Tx, Ty);

	if (Tool == EFramework2DTileTool::Pick)
	{
		PickAt(Tx, Ty);
		return;
	}

	TransactionIndex = GEditor->BeginTransaction(TEXT("Framework2DTiles"), Framework2DModeStrokeName(Tool), Map);
	ActiveLayer = FMath::Clamp(ActiveLayer, 0, FMath::Max(0, Map->GetNumLayers() - 1));

	if (Tool == EFramework2DTileTool::Paint || Tool == EFramework2DTileTool::Erase || Tool == EFramework2DTileTool::Collision)
	{
		ApplyAt(Tx, Ty);
	}
	else if (Tool == EFramework2DTileTool::Fill)
	{
		FloodFillPattern(Tx, Ty);
	}
	FlushPreview();
}

void FFramework2DTilePaintMode::ContinueStroke(int32 Tx, int32 Ty)
{
	// El cuentagotas no abre transaccion: arrastrarlo no debe pintar (no se podria deshacer).
	if (TransactionIndex == INDEX_NONE) { return; }
	if (LastTile.X < 0)
	{
		// Volvio a entrar en el mapa: el trazo sigue desde aqui, sin linea desde donde salio.
		LastTile = FIntPoint(Tx, Ty);
		ApplyAt(Tx, Ty);
		FlushPreview();
		return;
	}
	if (FIntPoint(Tx, Ty) == LastTile) { return; }
	if (Tool == EFramework2DTileTool::Paint || Tool == EFramework2DTileTool::Erase || Tool == EFramework2DTileTool::Collision)
	{
		// Linea desde el ultimo tile para no dejar huecos al mover rapido (Bresenham).
		int32 X = LastTile.X, Y = LastTile.Y;
		const int32 DX = FMath::Abs(Tx - X), DY = -FMath::Abs(Ty - Y);
		const int32 SX = X < Tx ? 1 : -1, SY = Y < Ty ? 1 : -1;
		int32 Err = DX + DY;
		while (true)
		{
			ApplyAt(X, Y);
			if (X == Tx && Y == Ty) { break; }
			const int32 E2 = 2 * Err;
			if (E2 >= DY) { Err += DY; X += SX; }
			if (E2 <= DX) { Err += DX; Y += SY; }
		}
		FlushPreview();
	}
	LastTile = FIntPoint(Tx, Ty);
}

void FFramework2DTilePaintMode::EndStroke()
{
	UFramework2DTileMapAsset* Map = GetTileMap();
	if (Map && Tool == EFramework2DTileTool::Rect && TransactionIndex != INDEX_NONE)
	{
		const FIntRect R(FMath::Min(RectStart.X, LastTile.X), FMath::Min(RectStart.Y, LastTile.Y),
			FMath::Max(RectStart.X, LastTile.X), FMath::Max(RectStart.Y, LastTile.Y));
		const FFramework2DModeBrushPattern Pattern = Framework2DModeMakePattern(*this);
		for (int32 Y = R.Min.Y; Y <= R.Max.Y; ++Y)
		{
			for (int32 X = R.Min.X; X <= R.Max.X; ++X)
			{
				const int32 Value = Pattern.At(X - R.Min.X, Y - R.Min.Y); // el patron arranca en la esquina
				if (Map->GetTile(ActiveLayer, X, Y) == Value) { continue; }
				PrepareChange();
				if (Map->SetTile(ActiveLayer, X, Y, Value)) { TouchRect(FIntRect(X, Y, X, Y)); }
			}
		}
		FlushPreview();
	}

	if (TransactionIndex != INDEX_NONE && GEditor)
	{
		if (bStrokeChanged) { GEditor->EndTransaction(); }
		else { GEditor->CancelTransaction(TransactionIndex); } // no cambio nada: sin paso de deshacer vacio
	}
	TransactionIndex = INDEX_NONE;
	bStrokeActive = false;
}

void FFramework2DTilePaintMode::PrepareChange()
{
	// Una sola foto del asset por trazo, ANTES del primer cambio.
	if (bStrokeChanged) { return; }
	if (UFramework2DTileMapAsset* Map = GetTileMap())
	{
		Map->SetFlags(RF_Transactional);
		Map->Modify();
		bStrokeChanged = true;
	}
}

void FFramework2DTilePaintMode::ApplyAt(int32 Tx, int32 Ty)
{
	UFramework2DTileMapAsset* Map = GetTileMap();
	if (!Map) { return; }

	// Colision: un tile cada vez; la forma es comun a todas las capas (vive en el mapa).
	if (Tool == EFramework2DTileTool::Collision)
	{
		if (Tx < 0 || Ty < 0 || Tx >= Map->Width || Ty >= Map->Height) { return; }
		if (Map->GetCollisionOverride(Tx, Ty) == CollisionBrush) { return; }
		PrepareChange();
		if (Map->SetCollisionOverride(Tx, Ty, CollisionBrush)) { TouchRect(FIntRect(Tx, Ty, Tx, Ty)); }
		return;
	}

	// La huella del pincel es el bloque seleccionado (W x H). El patron se ancla al inicio
	// del trazo: arrastrar repite el bloque sin descuadrarse.
	const FFramework2DModeBrushPattern Pattern = Framework2DModeMakePattern(*this);
	const int32 W = BrushWidth();
	const int32 H = BrushHeight();
	for (int32 Dy = 0; Dy < H; ++Dy)
	{
		for (int32 Dx = 0; Dx < W; ++Dx)
		{
			const int32 X = Tx + Dx;
			const int32 Y = Ty + Dy;
			if (X < 0 || Y < 0 || X >= Map->Width || Y >= Map->Height) { continue; }
			const int32 Value = (Tool == EFramework2DTileTool::Erase) ? -1 : Pattern.At(X - StrokeOrigin.X, Y - StrokeOrigin.Y);
			if (Map->GetTile(ActiveLayer, X, Y) == Value) { continue; }
			PrepareChange();
			if (Map->SetTile(ActiveLayer, X, Y, Value)) { TouchRect(FIntRect(X, Y, X, Y)); }
		}
	}
}

void FFramework2DTilePaintMode::PickAt(int32 Tx, int32 Ty)
{
	UFramework2DTileMapAsset* Map = GetTileMap();
	if (!Map) { return; }
	// Primero la capa activa; si ahi no hay nada, la capa visible mas al frente con algo.
	int32 Value = Map->GetTile(ActiveLayer, Tx, Ty);
	for (int32 L = Map->GetNumLayers() - 1; Value < 0 && L >= 0; --L)
	{
		Value = Map->At(L, Tx, Ty);
		if (Value >= 0) { ActiveLayer = L; }
	}
	if (Value < 0) { return; }

	if (Framework2D::IsGeneratorValue(Value))
	{
		SelectGenerator(Framework2D::GeneratorIdFromValue(Value));
		return;
	}
	if (Framework2D::IsFlipbookValue(Value))
	{
		// Un flipbook se copia como flipbook (no su fotograma de ahora).
		SelectFlipbook(Framework2D::FlipbookIdFromValue(Value));
		return;
	}
	// Un tile: su pagina pasa a verse en la paleta y queda elegido.
	SetActivePage(Framework2D::TilePageOf(Value));
	const int32 Local = Framework2D::TileLocalOf(Value);
	const int32 Cols = GetAtlasColumns();
	SelectAtlasRect(FIntRect(Local % Cols, Local / Cols, Local % Cols, Local / Cols));
	Tool = EFramework2DTileTool::Paint;
}

void FFramework2DTilePaintMode::TouchRect(const FIntRect& TileRect)
{
	if (!bHasPendingDirty) { PendingDirty = TileRect; bHasPendingDirty = true; }
	else
	{
		PendingDirty.Min.X = FMath::Min(PendingDirty.Min.X, TileRect.Min.X);
		PendingDirty.Min.Y = FMath::Min(PendingDirty.Min.Y, TileRect.Min.Y);
		PendingDirty.Max.X = FMath::Max(PendingDirty.Max.X, TileRect.Max.X);
		PendingDirty.Max.Y = FMath::Max(PendingDirty.Max.Y, TileRect.Max.Y);
	}
}

void FFramework2DTilePaintMode::FlushPreview()
{
	if (!bHasPendingDirty) { return; }
	bHasPendingDirty = false;
	if (AFramework2DTerrainWorld* Target = GetTarget())
	{
		// Rehornea dibujo y formas de colision de esos tiles.
		Target->RefreshPreviewTiles(PendingDirty);
	}
}

void FFramework2DTilePaintMode::FloodFillPattern(int32 Tx, int32 Ty)
{
	// Cubo con patron: la zona contigua de tiles iguales se rellena con el bloque elegido,
	// anclado en el punto del clic.
	UFramework2DTileMapAsset* Map = GetTileMap();
	if (!Map || Tx < 0 || Ty < 0 || Tx >= Map->Width || Ty >= Map->Height) { return; }
	const int32 Target = Map->GetTile(ActiveLayer, Tx, Ty);
	TArray<uint8> Seen;
	Seen.SetNumZeroed(Map->Width * Map->Height);
	TArray<FIntPoint> Stack, Region;
	Stack.Add(FIntPoint(Tx, Ty));
	Seen[Ty * Map->Width + Tx] = 1;
	while (Stack.Num() > 0)
	{
		const FIntPoint P = Stack.Pop();
		Region.Add(P);
		static const int32 DX[4] = { 1, -1, 0, 0 };
		static const int32 DY[4] = { 0, 0, 1, -1 };
		for (int32 k = 0; k < 4; ++k)
		{
			const int32 X = P.X + DX[k], Y = P.Y + DY[k];
			if (X < 0 || Y < 0 || X >= Map->Width || Y >= Map->Height || Seen[Y * Map->Width + X]) { continue; }
			if (Map->GetTile(ActiveLayer, X, Y) != Target) { continue; }
			Seen[Y * Map->Width + X] = 1;
			Stack.Add(FIntPoint(X, Y));
		}
	}
	const FFramework2DModeBrushPattern Pattern = Framework2DModeMakePattern(*this);
	for (const FIntPoint& P : Region)
	{
		const int32 Value = Pattern.At(P.X - Tx, P.Y - Ty);
		if (Map->GetTile(ActiveLayer, P.X, P.Y) == Value) { continue; }
		PrepareChange();
		if (Map->SetTile(ActiveLayer, P.X, P.Y, Value)) { TouchRect(FIntRect(P.X, P.Y, P.X, P.Y)); }
	}
}

// =====================================================================
//  Capas (desde el panel)
// =====================================================================
void FFramework2DTilePaintMode::ChangeLayers(const FText& Description, TFunctionRef<void(UFramework2DTileMapAsset*)> Change)
{
	UFramework2DTileMapAsset* Map = GetTileMap();
	if (!Map) { return; }
	{
		const FScopedTransaction Transaction(Description);
		Map->SetFlags(RF_Transactional);
		Map->Modify();
		Change(Map);
	}
	ActiveLayer = FMath::Clamp(ActiveLayer, 0, FMath::Max(0, Map->GetNumLayers() - 1));
	RefreshPreview();
}

void FFramework2DTilePaintMode::AddLayer()
{
	ChangeLayers(LOCTEXT("AddLayer", "Add layer"), [this](UFramework2DTileMapAsset* Map)
	{
		ActiveLayer = Map->AddLayer(FName(*FString::Printf(TEXT("Layer %d"), Map->GetNumLayers())));
	});
}

void FFramework2DTilePaintMode::RemoveActiveLayer()
{
	UFramework2DTileMapAsset* Map = GetTileMap();
	if (!Map || Map->GetNumLayers() <= 1 || !Map->Layers.IsValidIndex(ActiveLayer)) { return; } // siempre queda una
	ChangeLayers(LOCTEXT("RemoveLayer", "Remove layer"), [this](UFramework2DTileMapAsset* InMap) { InMap->RemoveLayer(ActiveLayer); });
}

void FFramework2DTilePaintMode::MoveActiveLayer(int32 Delta)
{
	UFramework2DTileMapAsset* Map = GetTileMap();
	if (!Map || !Map->Layers.IsValidIndex(ActiveLayer)) { return; }
	const int32 From = ActiveLayer;
	const int32 To = FMath::Clamp(From + Delta, 0, Map->GetNumLayers() - 1);
	if (To == From) { return; }
	// La capa activa viaja con la capa movida.
	ChangeLayers(LOCTEXT("MoveLayer", "Move layer"), [this, From, To](UFramework2DTileMapAsset* InMap)
	{
		if (InMap->MoveLayer(From, To)) { ActiveLayer = To; }
	});
}

void FFramework2DTilePaintMode::RenameLayer(int32 Layer, const FText& NewName)
{
	UFramework2DTileMapAsset* Map = GetTileMap();
	if (!Map || !Map->Layers.IsValidIndex(Layer)) { return; }
	const FString Clean = NewName.ToString().TrimStartAndEnd();
	if (Clean.IsEmpty() || Map->Layers[Layer].Name.ToString().Equals(Clean, ESearchCase::CaseSensitive)) { return; }
	// El nombre no cambia el terreno: no hace falta rehornear.
	const FScopedTransaction Transaction(LOCTEXT("RenameLayer", "Rename layer"));
	Map->SetFlags(RF_Transactional);
	Map->Modify();
	Map->Layers[Layer].Name = FName(*Clean);
}

void FFramework2DTilePaintMode::SetLayerVisible(int32 Layer, bool bVisible)
{
	UFramework2DTileMapAsset* Map = GetTileMap();
	if (!Map || !Map->Layers.IsValidIndex(Layer) || Map->Layers[Layer].bVisible == bVisible) { return; }
	ChangeLayers(LOCTEXT("LayerVisible", "Layer visibility"), [Layer, bVisible](UFramework2DTileMapAsset* InMap)
	{
		if (InMap->Layers.IsValidIndex(Layer)) { InMap->Layers[Layer].bVisible = bVisible; }
	});
}

void FFramework2DTilePaintMode::SetLayerBackground(int32 Layer, bool bBackground)
{
	UFramework2DTileMapAsset* Map = GetTileMap();
	if (!Map || !Map->Layers.IsValidIndex(Layer) || Map->Layers[Layer].bBackground == bBackground) { return; }
	ChangeLayers(LOCTEXT("LayerBackground", "Background layer"), [Layer, bBackground](UFramework2DTileMapAsset* InMap)
	{
		if (InMap->Layers.IsValidIndex(Layer)) { InMap->Layers[Layer].bBackground = bBackground; }
	});
}

void FFramework2DTilePaintMode::SetLayerCollides(int32 Layer, bool bCollides)
{
	UFramework2DTileMapAsset* Map = GetTileMap();
	if (!Map || !Map->Layers.IsValidIndex(Layer) || Map->Layers[Layer].bCollides == bCollides) { return; }
	ChangeLayers(LOCTEXT("LayerCollides", "Layer collision"), [Layer, bCollides](UFramework2DTileMapAsset* InMap)
	{
		if (InMap->Layers.IsValidIndex(Layer)) { InMap->Layers[Layer].bCollides = bCollides; }
	});
}

void FFramework2DTilePaintMode::SetLayerBreakable(int32 Layer, bool bBreakable)
{
	UFramework2DTileMapAsset* Map = GetTileMap();
	if (!Map || !Map->Layers.IsValidIndex(Layer) || Map->Layers[Layer].bBreakable == bBreakable) { return; }
	ChangeLayers(LOCTEXT("LayerBreakable", "Breakable layer"), [Layer, bBreakable](UFramework2DTileMapAsset* InMap)
	{
		if (InMap->Layers.IsValidIndex(Layer)) { InMap->Layers[Layer].bBreakable = bBreakable; }
	});
}

float FFramework2DTilePaintMode::GetLayerSeparation() const
{
	const AFramework2DTerrainWorld* Target = GetTarget();
	return Target ? Target->LayerSeparation : 0.0f;
}

void FFramework2DTilePaintMode::SetLayerSeparation(float Separation, bool bFinal)
{
	AFramework2DTerrainWorld* Target = GetTarget();
	if (!Target) { bDraggingSeparation = false; return; }
	const float NewValue = FMath::Max(0.0f, Separation);

	if (!bFinal)
	{
		// Mientras se arrastra: se ve en vivo, sin pasos de deshacer. Se recuerda el valor de
		// partida para que el paso final (Ctrl+Z) vuelva a el.
		if (!bDraggingSeparation)
		{
			bDraggingSeparation = true;
			SeparationBeforeDrag = Target->LayerSeparation;
		}
		if (Target->LayerSeparation != NewValue)
		{
			Target->LayerSeparation = NewValue;
			Target->UpdateLayerDepths();
		}
		return;
	}

	const float Before = bDraggingSeparation ? SeparationBeforeDrag : Target->LayerSeparation;
	bDraggingSeparation = false;
	if (FMath::IsNearlyEqual(Before, NewValue))
	{
		// Volvio al valor de partida: sin paso de deshacer, solo se deja como estaba.
		if (Target->LayerSeparation != NewValue)
		{
			Target->LayerSeparation = NewValue;
			Target->UpdateLayerDepths();
		}
		return;
	}
	{
		const FScopedTransaction Transaction(LOCTEXT("LayerSeparation", "Layer separation"));
		Target->LayerSeparation = Before; // la foto del deshacer guarda el valor de antes de arrastrar
		Target->Modify();
		Target->LayerSeparation = NewValue;
	}
	Target->UpdateLayerDepths();
}

void FFramework2DTilePaintMode::RefreshPreview()
{
	if (AFramework2DTerrainWorld* Target = GetTarget()) { Target->RebuildPreview(); }
}

// =====================================================================
//  Seleccion del atlas y patrones
// =====================================================================
int32 FFramework2DTilePaintMode::GetPageColumns(int32 PageId) const
{
	const UFramework2DTileSet* Set = GetTileSet();
	int32 Cols = 0, Rows = 0;
	return (Set && Set->GetPageGrid(PageId, Cols, Rows)) ? FMath::Max(1, Cols) : 1;
}

int32 FFramework2DTilePaintMode::GetPageRows(int32 PageId) const
{
	const UFramework2DTileSet* Set = GetTileSet();
	int32 Cols = 0, Rows = 0;
	return (Set && Set->GetPageGrid(PageId, Cols, Rows)) ? FMath::Max(1, Rows) : 1;
}

int32 FFramework2DTilePaintMode::GetAtlasColumns() const
{
	return GetPageColumns(ActivePage);
}

int32 FFramework2DTilePaintMode::GetAtlasRows() const
{
	return GetPageRows(ActivePage);
}

void FFramework2DTilePaintMode::SetActivePage(int32 PageId)
{
	const UFramework2DTileSet* Set = GetTileSet();
	ActivePage = (Set && Set->FindPageIndex(PageId) != INDEX_NONE) ? PageId : 0;
}

void FFramework2DTilePaintMode::SelectAtlasRect(const FIntRect& AtlasRect)
{
	// La seleccion es de la pagina que se ve en la paleta.
	SetActivePage(ActivePage);
	const int32 Cols = GetAtlasColumns();
	const int32 Rows = GetAtlasRows();
	BrushRect.Min.X = FMath::Clamp(FMath::Min(AtlasRect.Min.X, AtlasRect.Max.X), 0, Cols - 1);
	BrushRect.Min.Y = FMath::Clamp(FMath::Min(AtlasRect.Min.Y, AtlasRect.Max.Y), 0, Rows - 1);
	BrushRect.Max.X = FMath::Clamp(FMath::Max(AtlasRect.Min.X, AtlasRect.Max.X), 0, Cols - 1);
	BrushRect.Max.Y = FMath::Clamp(FMath::Max(AtlasRect.Min.Y, AtlasRect.Max.Y), 0, Rows - 1);
	BrushPage = ActivePage;
	SelectedTile = Framework2D::MakeTileValue(BrushPage, BrushRect.Min.Y * Cols + BrushRect.Min.X);
	BrushFlipbookId = INDEX_NONE; // el pincel vuelve a ser el atlas
	BrushGeneratorId = INDEX_NONE;
	// Elegir algo que pintar con una herramienta que no pinta tiles pasa al pincel.
	if (Tool == EFramework2DTileTool::Erase || Tool == EFramework2DTileTool::Pick || Tool == EFramework2DTileTool::Collision)
	{
		Tool = EFramework2DTileTool::Paint;
	}
}

bool FFramework2DTilePaintMode::IsFlipbookBrush() const
{
	if (BrushFlipbookId == INDEX_NONE || BrushGeneratorId != INDEX_NONE) { return false; }
	const UFramework2DTileSet* Set = GetTileSet();
	return Set && Set->FindFlipbookIndex(BrushFlipbookId) != INDEX_NONE;
}

bool FFramework2DTilePaintMode::IsGeneratorBrush() const
{
	if (BrushGeneratorId == INDEX_NONE) { return false; }
	const UFramework2DTileSet* Set = GetTileSet();
	return Set && Set->FindGeneratorIndex(BrushGeneratorId) != INDEX_NONE;
}

void FFramework2DTilePaintMode::GetSelectionTileValues(TArray<int32>& OutValues) const
{
	OutValues.Reset();
	const UFramework2DTileSet* Set = GetTileSet();
	const TArray<FFramework2DTileDef>* PageTiles = Set ? Set->GetPageTiles(BrushPage) : nullptr;
	if (!PageTiles) { return; }
	const int32 Cols = GetPageColumns(BrushPage);
	for (int32 Y = BrushRect.Min.Y; Y <= BrushRect.Max.Y; ++Y)
	{
		for (int32 X = BrushRect.Min.X; X <= BrushRect.Max.X; ++X)
		{
			const int32 Local = Y * Cols + X;
			if (Local >= 0 && Local < PageTiles->Num()) { OutValues.Add(Framework2D::MakeTileValue(BrushPage, Local)); }
		}
	}
}

int32 FFramework2DTilePaintMode::BrushWidth() const
{
	return IsSpecialBrush() ? 1 : FMath::Max(1, BrushRect.Max.X - BrushRect.Min.X + 1);
}

int32 FFramework2DTilePaintMode::BrushHeight() const
{
	return IsSpecialBrush() ? 1 : FMath::Max(1, BrushRect.Max.Y - BrushRect.Min.Y + 1);
}

int32 FFramework2DTilePaintMode::BrushTile(int32 Dx, int32 Dy) const
{
	return Framework2DModeMakePattern(*this).At(Dx, Dy);
}

// =====================================================================
//  Paginas del atlas
// =====================================================================
int32 FFramework2DTilePaintMode::AddAtlasPage(UTexture2D* Texture)
{
	int32 NewId = INDEX_NONE;
	ChangeTileSet(LOCTEXT("AddAtlasPage", "Add atlas"), [Texture, &NewId](UFramework2DTileSet* InSet)
	{
		NewId = InSet->AddAtlasPage(Texture);
	});
	if (NewId != INDEX_NONE) { ActivePage = NewId; }
	return NewId;
}

void FFramework2DTilePaintMode::RemoveAtlasPage(int32 PageId)
{
	UFramework2DTileSet* Set = GetTileSet();
	if (!Set || PageId == 0 || Set->FindPageIndex(PageId) == INDEX_NONE) { return; }
	UFramework2DTileMapAsset* Map = GetTileMap();

	// Solo se ensucia el mapa si de verdad tiene tiles de esa pagina.
	bool bMapUsesIt = false;
	if (Map)
	{
		for (const FFramework2DTileLayer& Layer : Map->Layers)
		{
			for (const int32 Cell : Layer.Tiles)
			{
				if (Framework2D::IsAtlasTileValue(Cell) && Framework2D::TilePageOf(Cell) == PageId) { bMapUsesIt = true; break; }
			}
			if (bMapUsesIt) { break; }
		}
	}
	{
		// Un solo paso de deshacer para el tileset y el mapa.
		const FScopedTransaction Transaction(LOCTEXT("RemoveAtlasPage", "Remove atlas"));
		Set->SetFlags(RF_Transactional);
		Set->Modify();
		if (bMapUsesIt)
		{
			Map->SetFlags(RF_Transactional);
			Map->Modify();
			Map->ClearAtlasPage(PageId);
		}
		Set->RemoveAtlasPage(PageId);
	}
	if (ActivePage == PageId) { ActivePage = 0; }
	if (BrushPage == PageId)
	{
		BrushPage = 0;
		BrushRect = FIntRect(0, 0, 0, 0);
		SelectedTile = 0;
	}

	if (UWorld* World = GetWorld())
	{
		for (TActorIterator<AFramework2DTerrainWorld> It(World); It; ++It)
		{
			if (It->UsesAsset(Set) || (Map && It->UsesAsset(Map))) { It->RebuildPreview(); }
		}
	}
}

void FFramework2DTilePaintMode::SetPageTexture(int32 PageId, UTexture2D* Texture)
{
	UFramework2DTileSet* Set = GetTileSet();
	if (!Set || Set->FindPageIndex(PageId) == INDEX_NONE || Set->GetPageTexture(PageId) == Texture) { return; }
	ChangeTileSet(LOCTEXT("PageTexture", "Atlas image"), [PageId, Texture](UFramework2DTileSet* InSet)
	{
		const int32 Index = InSet->FindPageIndex(PageId);
		if (Index == 0)
		{
			InSet->Atlas = Texture;
		}
		else if (Index != INDEX_NONE)
		{
			FFramework2DAtlasPage& Page = InSet->ExtraAtlases[Index - 1];
			Page.Texture = Texture;
			// Una pagina sin nombre propio toma el de su imagen.
			if (Texture && (Page.Name.IsNone() || Page.Name == FName(TEXT("Atlas")))) { Page.Name = Texture->GetFName(); }
		}
		InSet->RefreshTilesFromAtlas();
	});
}

void FFramework2DTilePaintMode::RenamePage(int32 PageId, const FText& NewName)
{
	UFramework2DTileSet* Set = GetTileSet();
	const int32 Index = Set ? Set->FindPageIndex(PageId) : INDEX_NONE;
	if (Index <= 0) { return; } // la principal se llama siempre "Principal"
	const FString Clean = NewName.ToString().TrimStartAndEnd();
	if (Clean.IsEmpty() || Set->ExtraAtlases[Index - 1].Name.ToString().Equals(Clean, ESearchCase::CaseSensitive)) { return; }
	// El nombre solo se ve en la paleta: no hace falta rehornear.
	const FScopedTransaction Transaction(LOCTEXT("RenameAtlasPage", "Rename atlas"));
	Set->SetFlags(RF_Transactional);
	Set->Modify();
	Set->ExtraAtlases[Index - 1].Name = FName(*Clean);
}

// =====================================================================
//  Propiedades de la seleccion (se guardan en el TileSet)
// =====================================================================
FName FFramework2DTilePaintMode::GetSelectionMaterial(bool& bOutMixed) const
{
	bOutMixed = false;
	const UFramework2DTileSet* Set = GetTileSet();
	if (!Set) { return NAME_None; }
	if (IsGeneratorBrush())
	{
		const FFramework2DGenerator* Generator = Set->FindGeneratorByValue(Framework2D::MakeGeneratorValue(BrushGeneratorId));
		return Generator ? Generator->MaterialName : NAME_None;
	}
	if (IsFlipbookBrush())
	{
		const FFramework2DFlipbook* Flipbook = Set->FindFlipbookByValue(Framework2D::MakeFlipbookValue(BrushFlipbookId));
		return Flipbook ? Flipbook->MaterialName : NAME_None;
	}
	TArray<int32> Values;
	GetSelectionTileValues(Values);
	if (Values.Num() == 0) { return NAME_None; }
	const FName First = Set->GetTileMaterial(Values[0]);
	for (const int32 Value : Values)
	{
		if (Set->GetTileMaterial(Value) != First) { bOutMixed = true; break; }
	}
	return First;
}

void FFramework2DTilePaintMode::SetSelectionMaterial(FName Material)
{
	if (IsGeneratorBrush())
	{
		ChangeGenerator(BrushGeneratorId, LOCTEXT("GeneratorMaterial", "Generator material"),
			[Material](FFramework2DGenerator& Generator) { Generator.MaterialName = Material; });
		return;
	}
	if (IsFlipbookBrush())
	{
		SetFlipbookMaterial(BrushFlipbookId, Material);
		return;
	}
	UFramework2DTileSet* Set = GetTileSet();
	if (!Set) { return; }
	TArray<int32> Values;
	GetSelectionTileValues(Values);
	bool bAnyChange = false;
	for (const int32 Value : Values)
	{
		if (Set->GetTileMaterial(Value) != Material) { bAnyChange = true; break; }
	}
	if (!bAnyChange) { return; } // sin paso de deshacer vacio
	ChangeTileSet(LOCTEXT("SelectionMaterial", "Tile material"), [&Values, Material](UFramework2DTileSet* InSet)
	{
		for (const int32 Value : Values)
		{
			if (FFramework2DTileDef* Def = InSet->FindTileDefMutable(Value)) { Def->MaterialName = Material; }
		}
	});
}

EFramework2DCollisionShape FFramework2DTilePaintMode::GetSelectionCollision(bool& bOutMixed) const
{
	bOutMixed = false;
	const UFramework2DTileSet* Set = GetTileSet();
	if (!Set || IsGeneratorBrush()) { return EFramework2DCollisionShape::Auto; } // lo generado choca segun su material
	if (IsFlipbookBrush())
	{
		const FFramework2DFlipbook* Flipbook = Set->FindFlipbookByValue(Framework2D::MakeFlipbookValue(BrushFlipbookId));
		return Flipbook ? Flipbook->Collision : EFramework2DCollisionShape::Auto;
	}
	TArray<int32> Values;
	GetSelectionTileValues(Values);
	if (Values.Num() == 0) { return EFramework2DCollisionShape::Auto; }
	const EFramework2DCollisionShape First = Set->GetTileCollision(Values[0]);
	for (const int32 Value : Values)
	{
		if (Set->GetTileCollision(Value) != First) { bOutMixed = true; break; }
	}
	return First;
}

void FFramework2DTilePaintMode::SetSelectionCollision(EFramework2DCollisionShape Shape)
{
	if (IsGeneratorBrush()) { return; }
	if (IsFlipbookBrush())
	{
		SetFlipbookCollision(BrushFlipbookId, Shape);
		return;
	}
	UFramework2DTileSet* Set = GetTileSet();
	if (!Set) { return; }
	TArray<int32> Values;
	GetSelectionTileValues(Values);
	bool bAnyChange = false;
	for (const int32 Value : Values)
	{
		if (Set->GetTileCollision(Value) != Shape) { bAnyChange = true; break; }
	}
	if (!bAnyChange) { return; }
	ChangeTileSet(LOCTEXT("SelectionCollision", "Tile collision"), [&Values, Shape](UFramework2DTileSet* InSet)
	{
		for (const int32 Value : Values)
		{
			if (FFramework2DTileDef* Def = InSet->FindTileDefMutable(Value)) { Def->Collision = Shape; }
		}
	});
}

// =====================================================================
//  Flipbooks (lista propia del TileSet; no tocan los tiles del atlas)
// =====================================================================
void FFramework2DTilePaintMode::ChangeTileSet(const FText& Description, TFunctionRef<void(UFramework2DTileSet*)> Change)
{
	UFramework2DTileSet* Set = GetTileSet();
	if (!Set) { return; }
	{
		const FScopedTransaction Transaction(Description);
		Set->SetFlags(RF_Transactional);
		Set->Modify();
		Change(Set);
	}
	// El tileset puede estar en varios terrenos del nivel: se rehacen todos los que lo usan.
	bool bRebuiltTarget = false;
	AFramework2DTerrainWorld* Target = GetTarget();
	if (UWorld* World = GetWorld())
	{
		for (TActorIterator<AFramework2DTerrainWorld> It(World); It; ++It)
		{
			if (It->UsesAsset(Set))
			{
				It->RebuildPreview();
				bRebuiltTarget |= (*It == Target);
			}
		}
	}
	if (!bRebuiltTarget) { RefreshPreview(); }
}

int32 FFramework2DTilePaintMode::CreateFlipbookFromSelection()
{
	UFramework2DTileSet* Set = GetTileSet();
	if (!Set || !CanCreateFlipbook()) { return INDEX_NONE; }

	// Fotogramas en orden de lectura de la seleccion (de su pagina). Ningun tile del atlas cambia.
	TArray<int32> Frames;
	GetSelectionTileValues(Frames);
	if (Frames.Num() < 2) { return INDEX_NONE; }

	int32 NewId = INDEX_NONE;
	ChangeTileSet(LOCTEXT("CreateFlipbook", "Create flipbook"), [&Frames, &NewId](UFramework2DTileSet* InSet)
	{
		NewId = InSet->AddFlipbook(Frames);
	});
	if (NewId != INDEX_NONE) { SelectFlipbook(NewId); }
	return NewId;
}

void FFramework2DTilePaintMode::SelectFlipbook(int32 FlipbookId)
{
	const UFramework2DTileSet* Set = GetTileSet();
	if (!Set || Set->FindFlipbookIndex(FlipbookId) == INDEX_NONE) { return; }
	BrushFlipbookId = FlipbookId;
	BrushGeneratorId = INDEX_NONE;
	if (Tool == EFramework2DTileTool::Erase || Tool == EFramework2DTileTool::Pick || Tool == EFramework2DTileTool::Collision)
	{
		Tool = EFramework2DTileTool::Paint;
	}
}

void FFramework2DTilePaintMode::DeleteFlipbook(int32 FlipbookId)
{
	UFramework2DTileSet* Set = GetTileSet();
	if (!Set || Set->FindFlipbookIndex(FlipbookId) == INDEX_NONE) { return; }
	UFramework2DTileMapAsset* Map = GetTileMap();

	// Solo se ensucia el mapa si de verdad tiene celdas con ese flipbook.
	bool bMapUsesIt = false;
	if (Map)
	{
		const int32 Value = Framework2D::MakeFlipbookValue(FlipbookId);
		for (const FFramework2DTileLayer& Layer : Map->Layers)
		{
			if (Layer.Tiles.Contains(Value)) { bMapUsesIt = true; break; }
		}
	}

	{
		// Un solo paso de deshacer para el tileset y el mapa.
		const FScopedTransaction Transaction(LOCTEXT("DeleteFlipbook", "Delete flipbook"));
		Set->SetFlags(RF_Transactional);
		Set->Modify();
		if (bMapUsesIt)
		{
			Map->SetFlags(RF_Transactional);
			Map->Modify();
			Map->ClearFlipbook(FlipbookId);
		}
		Set->RemoveFlipbook(FlipbookId);
	}
	if (BrushFlipbookId == FlipbookId) { BrushFlipbookId = INDEX_NONE; }

	if (UWorld* World = GetWorld())
	{
		for (TActorIterator<AFramework2DTerrainWorld> It(World); It; ++It)
		{
			if (It->UsesAsset(Set) || (Map && It->UsesAsset(Map))) { It->RebuildPreview(); }
		}
	}
}

void FFramework2DTilePaintMode::RenameFlipbook(int32 FlipbookId, const FText& NewName)
{
	UFramework2DTileSet* Set = GetTileSet();
	FFramework2DFlipbook* Flipbook = Set ? Set->FindFlipbookById(FlipbookId) : nullptr;
	if (!Flipbook) { return; }
	const FString Clean = NewName.ToString().TrimStartAndEnd();
	if (Clean.IsEmpty() || Flipbook->Name.ToString().Equals(Clean, ESearchCase::CaseSensitive)) { return; }
	// El nombre solo se ve en la paleta: no hace falta rehornear.
	const FScopedTransaction Transaction(LOCTEXT("RenameFlipbook", "Rename flipbook"));
	Set->SetFlags(RF_Transactional);
	Set->Modify();
	Flipbook->Name = FName(*Clean);
}

void FFramework2DTilePaintMode::SetFlipbookFPS(int32 FlipbookId, float FPS)
{
	UFramework2DTileSet* Set = GetTileSet();
	FFramework2DFlipbook* Flipbook = Set ? Set->FindFlipbookById(FlipbookId) : nullptr;
	if (!Flipbook) { return; }
	const float Clamped = FMath::Clamp(FPS, 0.1f, 60.0f);
	if (FMath::IsNearlyEqual(Flipbook->FPS, Clamped)) { return; }
	// El terreno lee los FPS en cada frame: no hace falta rehornear.
	const FScopedTransaction Transaction(LOCTEXT("FlipbookFPS", "Flipbook speed"));
	Set->SetFlags(RF_Transactional);
	Set->Modify();
	Flipbook->FPS = Clamped;
	Set->MarkPackageDirty();
}

void FFramework2DTilePaintMode::SetFlipbookMaterial(int32 FlipbookId, FName Material)
{
	UFramework2DTileSet* Set = GetTileSet();
	const FFramework2DFlipbook* Flipbook = Set ? Set->FindFlipbookById(FlipbookId) : nullptr;
	if (!Flipbook || Flipbook->MaterialName == Material) { return; }
	ChangeTileSet(LOCTEXT("FlipbookMaterial", "Flipbook material"), [FlipbookId, Material](UFramework2DTileSet* InSet)
	{
		if (FFramework2DFlipbook* Found = InSet->FindFlipbookById(FlipbookId)) { Found->MaterialName = Material; }
	});
}

void FFramework2DTilePaintMode::SetFlipbookCollision(int32 FlipbookId, EFramework2DCollisionShape Shape)
{
	UFramework2DTileSet* Set = GetTileSet();
	const FFramework2DFlipbook* Flipbook = Set ? Set->FindFlipbookById(FlipbookId) : nullptr;
	if (!Flipbook || Flipbook->Collision == Shape) { return; }
	ChangeTileSet(LOCTEXT("FlipbookCollision", "Flipbook collision"), [FlipbookId, Shape](UFramework2DTileSet* InSet)
	{
		if (FFramework2DFlipbook* Found = InSet->FindFlipbookById(FlipbookId)) { Found->Collision = Shape; }
	});
}

void FFramework2DTilePaintMode::SetFlipbookFramesFromSelection(int32 FlipbookId)
{
	UFramework2DTileSet* Set = GetTileSet();
	const FFramework2DFlipbook* Flipbook = Set ? Set->FindFlipbookById(FlipbookId) : nullptr;
	if (!Flipbook) { return; }

	// La seleccion del atlas (aunque el pincel sea un flipbook, BrushRect sigue ahi).
	TArray<int32> Frames;
	GetSelectionTileValues(Frames);
	if (Frames.Num() == 0 || Frames == Flipbook->Frames) { return; }
	ChangeTileSet(LOCTEXT("FlipbookFrames", "Flipbook frames"), [FlipbookId, &Frames](UFramework2DTileSet* InSet)
	{
		if (FFramework2DFlipbook* Found = InSet->FindFlipbookById(FlipbookId)) { Found->Frames = Frames; }
	});
}

// =====================================================================
//  Generadores de vegetacion (lista propia del TileSet)
// =====================================================================
const FFramework2DGenerator* FFramework2DTilePaintMode::GetGenerator(int32 GeneratorId) const
{
	const UFramework2DTileSet* Set = GetTileSet();
	return Set ? Set->FindGeneratorByValue(Framework2D::MakeGeneratorValue(GeneratorId)) : nullptr;
}

// Sprites de la seleccion del atlas: uno por tile con dibujo, o el bloque entero como uno solo.
static void Framework2DModeSelectionSprites(const FFramework2DTilePaintMode& Mode, bool bAsOneSprite, TArray<FFramework2DScatterSprite>& Out)
{
	Out.Reset();
	TArray<int32> Values;
	Mode.GetSelectionTileValues(Values);
	if (Values.Num() == 0) { return; }
	if (bAsOneSprite)
	{
		FFramework2DScatterSprite Sprite;
		Sprite.Tile = Values[0];
		Sprite.WidthInTiles = FMath::Clamp(Mode.BrushRect.Max.X - Mode.BrushRect.Min.X + 1, 1, 16);
		Sprite.HeightInTiles = FMath::Clamp(Mode.BrushRect.Max.Y - Mode.BrushRect.Min.Y + 1, 1, 16);
		Out.Add(Sprite);
		return;
	}
	for (const int32 Value : Values)
	{
		FFramework2DScatterSprite Sprite;
		Sprite.Tile = Value;
		Out.Add(Sprite);
	}
}

int32 FFramework2DTilePaintMode::CreateGeneratorFromSelection()
{
	UFramework2DTileSet* Set = GetTileSet();
	if (!Set) { return INDEX_NONE; }
	TArray<FFramework2DScatterSprite> Sprites;
	if (CanUseSelectionAsSprites()) { Framework2DModeSelectionSprites(*this, /*bAsOneSprite*/ false, Sprites); }

	int32 NewId = INDEX_NONE;
	ChangeTileSet(LOCTEXT("CreateGenerator", "Create generator"), [&Sprites, &NewId](UFramework2DTileSet* InSet)
	{
		NewId = InSet->AddGenerator();
		if (FFramework2DGenerator* Generator = InSet->FindGeneratorById(NewId)) { Generator->Sprites = Sprites; }
	});
	if (NewId != INDEX_NONE) { SelectGenerator(NewId); }
	return NewId;
}

void FFramework2DTilePaintMode::SelectGenerator(int32 GeneratorId)
{
	const UFramework2DTileSet* Set = GetTileSet();
	if (!Set || Set->FindGeneratorIndex(GeneratorId) == INDEX_NONE) { return; }
	BrushGeneratorId = GeneratorId;
	BrushFlipbookId = INDEX_NONE;
	if (Tool == EFramework2DTileTool::Erase || Tool == EFramework2DTileTool::Pick || Tool == EFramework2DTileTool::Collision)
	{
		Tool = EFramework2DTileTool::Paint;
	}
}

void FFramework2DTilePaintMode::DeleteGenerator(int32 GeneratorId)
{
	UFramework2DTileSet* Set = GetTileSet();
	if (!Set || Set->FindGeneratorIndex(GeneratorId) == INDEX_NONE) { return; }
	UFramework2DTileMapAsset* Map = GetTileMap();

	bool bMapUsesIt = false;
	if (Map)
	{
		const int32 Value = Framework2D::MakeGeneratorValue(GeneratorId);
		for (const FFramework2DTileLayer& Layer : Map->Layers)
		{
			if (Layer.Tiles.Contains(Value)) { bMapUsesIt = true; break; }
		}
	}
	{
		// Un solo paso de deshacer para el tileset y el mapa.
		const FScopedTransaction Transaction(LOCTEXT("DeleteGenerator", "Delete generator"));
		Set->SetFlags(RF_Transactional);
		Set->Modify();
		if (bMapUsesIt)
		{
			Map->SetFlags(RF_Transactional);
			Map->Modify();
			Map->ClearGenerator(GeneratorId);
		}
		Set->RemoveGenerator(GeneratorId);
	}
	if (BrushGeneratorId == GeneratorId) { BrushGeneratorId = INDEX_NONE; }

	if (UWorld* World = GetWorld())
	{
		for (TActorIterator<AFramework2DTerrainWorld> It(World); It; ++It)
		{
			if (It->UsesAsset(Set) || (Map && It->UsesAsset(Map))) { It->RebuildPreview(); }
		}
	}
}

void FFramework2DTilePaintMode::RenameGenerator(int32 GeneratorId, const FText& NewName)
{
	UFramework2DTileSet* Set = GetTileSet();
	FFramework2DGenerator* Generator = Set ? Set->FindGeneratorById(GeneratorId) : nullptr;
	if (!Generator) { return; }
	const FString Clean = NewName.ToString().TrimStartAndEnd();
	if (Clean.IsEmpty() || Generator->Name.ToString().Equals(Clean, ESearchCase::CaseSensitive)) { return; }
	// El nombre solo se ve en la paleta: no hace falta rehornear.
	const FScopedTransaction Transaction(LOCTEXT("RenameGenerator", "Rename generator"));
	Set->SetFlags(RF_Transactional);
	Set->Modify();
	Generator->Name = FName(*Clean);
}

void FFramework2DTilePaintMode::AddSelectionToGenerator(int32 GeneratorId, bool bAsOneSprite)
{
	if (!CanUseSelectionAsSprites() || !GetGenerator(GeneratorId)) { return; }
	TArray<FFramework2DScatterSprite> Sprites;
	Framework2DModeSelectionSprites(*this, bAsOneSprite, Sprites);
	if (Sprites.Num() == 0) { return; }
	ChangeGenerator(GeneratorId, LOCTEXT("AddGeneratorSprites", "Add sprites to the generator"), [&Sprites](FFramework2DGenerator& Generator)
	{
		Generator.Sprites.Append(Sprites);
	});
}

void FFramework2DTilePaintMode::RemoveGeneratorSprite(int32 GeneratorId, int32 SpriteIndex)
{
	const FFramework2DGenerator* Generator = GetGenerator(GeneratorId);
	if (!Generator || !Generator->Sprites.IsValidIndex(SpriteIndex)) { return; }
	ChangeGenerator(GeneratorId, LOCTEXT("RemoveGeneratorSprite", "Remove sprite from the generator"), [SpriteIndex](FFramework2DGenerator& InGenerator)
	{
		if (InGenerator.Sprites.IsValidIndex(SpriteIndex)) { InGenerator.Sprites.RemoveAt(SpriteIndex); }
	});
}

void FFramework2DTilePaintMode::ChangeGenerator(int32 GeneratorId, const FText& Description, TFunctionRef<void(FFramework2DGenerator&)> Change)
{
	UFramework2DTileSet* Set = GetTileSet();
	FFramework2DGenerator* Generator = Set ? Set->FindGeneratorById(GeneratorId) : nullptr;
	if (!Generator) { return; }

	// Se prueba el cambio en una copia: si no cambia nada, ni paso de deshacer ni rehorneado.
	FFramework2DGenerator Edited = *Generator;
	Change(Edited);
	const UScriptStruct* Struct = FFramework2DGenerator::StaticStruct();
	if (Struct->CompareScriptStruct(Generator, &Edited, PPF_None)) { return; }

	ChangeTileSet(Description, [GeneratorId, &Edited](UFramework2DTileSet* InSet)
	{
		if (FFramework2DGenerator* Found = InSet->FindGeneratorById(GeneratorId)) { *Found = Edited; }
	});
}

// =====================================================================
//  Generacion procedural (pestana "Generar"): biomas, receta y generar
// =====================================================================

/** Deja en el informe que no se pudo generar y por que (el panel lo ensena con un aviso). */
static void Framework2DModeGenSetProblem(FFramework2DTilePaintMode& Mode, const FText& Problem)
{
	FFramework2DProcGenReport Report;
	Report.bSuccess = false;
	Report.Message = Problem.ToString();
	Mode.LastGenerateReport = Report;
	Mode.bHasGenerateReport = true;
}

/**
 * Indice nuevo de la capa que estaba en OldIndex. Generar solo INSERTA capas (Fondo detras de
 * Terreno, Decoracion y Agua delante) con nombres que no existian: las de antes siguen en el
 * mismo orden, asi que basta con recorrer las dos listas a la par.
 */
static int32 Framework2DModeGenRemapLayer(const TArray<FName>& OldNames, const UFramework2DTileMapAsset& Map, int32 OldIndex)
{
	if (OldNames.Num() == Map.Layers.Num() || !OldNames.IsValidIndex(OldIndex)) { return OldIndex; }
	int32 Old = 0;
	for (int32 New = 0; New < Map.Layers.Num() && Old < OldNames.Num(); ++New)
	{
		if (Map.Layers[New].Name != OldNames[Old]) { continue; } // capa recien creada
		if (Old == OldIndex) { return New; }
		++Old;
	}
	return OldIndex;
}

/**
 * Genera el mapa con su receta DENTRO de la transaccion ya abierta (quien llama ya hizo
 * Map->Modify()). Guarda el informe y sigue a la capa activa aunque se creen capas nuevas.
 */
static bool Framework2DModeGenRun(FFramework2DTilePaintMode& Mode, UFramework2DTileMapAsset* Map)
{
	TArray<FName> OldNames;
	OldNames.Reserve(Map->Layers.Num());
	for (const FFramework2DTileLayer& Layer : Map->Layers) { OldNames.Add(Layer.Name); }

	Mode.LastGenerateReport = UFramework2DProcGenLibrary::GenerateMap(Map);
	Mode.bHasGenerateReport = true;
	if (!Mode.LastGenerateReport.bSuccess)
	{
		if (Mode.LastGenerateReport.Message.IsEmpty())
		{
			Mode.LastGenerateReport.Message = LOCTEXT("GenFailed", "The map could not be generated.").ToString();
		}
		return false;
	}
	Mode.ActiveLayer = FMath::Clamp(Framework2DModeGenRemapLayer(OldNames, *Map, Mode.ActiveLayer), 0, FMath::Max(0, Map->GetNumLayers() - 1));
	return true;
}

/**
 * "Regenerar al cambiar": regenera dentro de la transaccion abierta por el ajuste que cambio
 * (un solo Ctrl+Z deshace el ajuste y el mapa a la vez). Si algo impide generar (un bioma a
 * medio hacer, sin el centro), el mapa no se toca y el informe dice por que.
 */
static bool Framework2DModeGenAuto(FFramework2DTilePaintMode& Mode, UFramework2DTileMapAsset* Map)
{
	if (!Map) { return false; }
	const FText Problem = Mode.GetGenerateProblem();
	if (!Problem.IsEmpty())
	{
		Framework2DModeGenSetProblem(Mode, Problem);
		return false;
	}
	Map->SetFlags(RF_Transactional);
	Map->Modify();
	return Framework2DModeGenRun(Mode, Map);
}

/** Rehace la vista previa de los terrenos del nivel que usan esos assets (un mapa puede estar en varios). */
static void Framework2DModeGenRebuild(FFramework2DTilePaintMode& Mode, const UObject* AssetA, const UObject* AssetB = nullptr)
{
	AFramework2DTerrainWorld* Target = Mode.GetTarget();
	bool bRebuiltTarget = false;
	if (UWorld* World = Mode.GetWorld())
	{
		for (TActorIterator<AFramework2DTerrainWorld> It(World); It; ++It)
		{
			if (It->UsesAsset(AssetA) || It->UsesAsset(AssetB))
			{
				It->RebuildPreview();
				bRebuiltTarget |= (*It == Target);
			}
		}
	}
	if (!bRebuiltTarget) { Mode.RefreshPreview(); }
}

/** Otra semilla (0..999999), siempre distinta de la de ahora. */
static int32 Framework2DModeGenNewSeed(int32 OldSeed)
{
	int32 NewSeed = (int32)(HashCombine((uint32)OldSeed, FPlatformTime::Cycles()) % 1000000u);
	if (NewSeed == OldSeed) { NewSeed = (NewSeed + 1) % 1000000; }
	return NewSeed;
}

/** La receta dentro de sus limites (los mismos que en Details). Una capa sin nombre se queda con el de antes. */
static void Framework2DModeGenClampSettings(FFramework2DProcGenSettings& S, const FFramework2DProcGenSettings& Before)
{
	S.Levels              = FMath::Clamp(S.Levels, 1, 16);
	S.LevelHeight         = FMath::Clamp(S.LevelHeight, 1, 16);
	S.BaseHeight          = FMath::Clamp(S.BaseHeight, 1, 256);
	S.PlateauMinWidth     = FMath::Clamp(S.PlateauMinWidth, 1, 128);
	S.PlateauMaxWidth     = FMath::Clamp(S.PlateauMaxWidth, 1, 256);
	S.MaxLevelStep        = FMath::Clamp(S.MaxLevelStep, 1, 15);
	S.RampChance          = FMath::Clamp(S.RampChance, 0.0f, 1.0f);
	S.GentleRampChance    = FMath::Clamp(S.GentleRampChance, 0.0f, 1.0f);
	S.PitChance           = FMath::Clamp(S.PitChance, 0.0f, 1.0f);
	S.PitDepth            = FMath::Clamp(S.PitDepth, 1, 16);
	S.LakeChance          = FMath::Clamp(S.LakeChance, 0.0f, 1.0f);
	S.WaterfallChance     = FMath::Clamp(S.WaterfallChance, 0.0f, 1.0f);
	S.PlatformChance      = FMath::Clamp(S.PlatformChance, 0.0f, 1.0f);
	S.PlatformMinLength   = FMath::Clamp(S.PlatformMinLength, 1, 64);
	S.PlatformMaxLength   = FMath::Clamp(S.PlatformMaxLength, 1, 64);
	S.DecorationDensity   = FMath::Clamp(S.DecorationDensity, 0.0f, 1.0f);
	S.DecorationSpacing   = FMath::Clamp(S.DecorationSpacing, 0, 16);
	S.CenterVariantChance = FMath::Clamp(S.CenterVariantChance, 0.0f, 1.0f);
	S.BackgroundRise      = FMath::Clamp(S.BackgroundRise, 0, 64);
	if (S.TerrainLayer.IsNone())    { S.TerrainLayer = Before.TerrainLayer; }
	if (S.BackgroundLayer.IsNone()) { S.BackgroundLayer = Before.BackgroundLayer; }
	if (S.WaterLayer.IsNone())      { S.WaterLayer = Before.WaterLayer; }
	if (S.DecorationLayer.IsNone()) { S.DecorationLayer = Before.DecorationLayer; }
}

/** True si los dos generadores sacan los mismos sprites (mismo tile y tamano, en el mismo orden). */
static bool Framework2DModeGenSameSprites(const TArray<FFramework2DScatterSprite>& A, const TArray<FFramework2DScatterSprite>& B)
{
	if (A.Num() != B.Num()) { return false; }
	for (int32 i = 0; i < A.Num(); ++i)
	{
		if (A[i].Tile != B[i].Tile || A[i].WidthInTiles != B[i].WidthInTiles || A[i].HeightInTiles != B[i].HeightInTiles) { return false; }
	}
	return true;
}

/** Si el tileset ya no tiene ese material de serie (lo borraron), lo vuelve a anadir. */
static void Framework2DModeGenEnsureMaterial(UFramework2DTileSet& Set, FName MaterialName)
{
	for (const FFramework2DMaterial& Existing : Set.Materials)
	{
		if (Existing.Name == MaterialName) { return; }
	}
	for (const FFramework2DMaterial& Default : Framework2D::MakeDefaultMaterials())
	{
		if (Default.Name == MaterialName) { Set.Materials.Add(Default); return; }
	}
}

int32 FFramework2DTilePaintMode::GetBrushValue() const
{
	const UFramework2DTileSet* Set = GetTileSet();
	if (!Set) { return -1; }
	// El mismo orden que el patron del pincel: generador, flipbook y, si no, el atlas.
	if (IsGeneratorBrush()) { return Framework2D::MakeGeneratorValue(BrushGeneratorId); }
	if (IsFlipbookBrush()) { return Framework2D::MakeFlipbookValue(BrushFlipbookId); }
	return Set->IsValidValue(SelectedTile) ? SelectedTile : -1;
}

//---------------------- Biomas ----------------------

const FFramework2DBiome* FFramework2DTilePaintMode::GetActiveBiome() const
{
	const UFramework2DTileMapAsset* Map = GetTileMap();
	const UFramework2DTileSet* Set = Map ? Map->TileSet.Get() : nullptr;
	return Set ? Set->ResolveBiome(Map->ProcGen.BiomeId) : nullptr;
}

int32 FFramework2DTilePaintMode::GetActiveBiomeId() const
{
	const FFramework2DBiome* Biome = GetActiveBiome();
	return Biome ? Biome->Id : INDEX_NONE;
}

void FFramework2DTilePaintMode::SetActiveBiome(int32 BiomeId)
{
	UFramework2DTileMapAsset* Map = GetTileMap();
	const UFramework2DTileSet* Set = GetTileSet();
	if (!Map || !Set || !Set->FindBiomeById(BiomeId) || Map->ProcGen.BiomeId == BiomeId) { return; }

	// Si la receta apuntaba a un bioma borrado, el activo ya era el primero: elegirlo solo
	// arregla la receta, el nivel no cambia (no hace falta regenerar).
	const bool bRegenerate = bAutoGenerate && GetActiveBiomeId() != BiomeId;
	bool bGenerated = false;
	{
		const FScopedTransaction Transaction(LOCTEXT("BiomeSetActive", "Choose biome"));
		Map->SetFlags(RF_Transactional);
		Map->Modify();
		Map->ProcGen.BiomeId = BiomeId;
		if (bRegenerate) { bGenerated = Framework2DModeGenAuto(*this, Map); }
	}
	if (bGenerated) { Framework2DModeGenRebuild(*this, Map); }
}

int32 FFramework2DTilePaintMode::CreateBiome()
{
	UFramework2DTileSet* Set = GetTileSet();
	if (!Set) { return INDEX_NONE; }
	UFramework2DTileMapAsset* Map = GetTileMap();

	// Nace vacio (no se puede generar con el): sin regenerar, solo se deja activo.
	int32 NewId = INDEX_NONE;
	{
		const FScopedTransaction Transaction(LOCTEXT("BiomeCreate", "Create biome"));
		Set->SetFlags(RF_Transactional);
		Set->Modify();
		NewId = Set->AddBiome();
		if (Map)
		{
			Map->SetFlags(RF_Transactional);
			Map->Modify();
			Map->ProcGen.BiomeId = NewId;
		}
	}
	return NewId;
}

void FFramework2DTilePaintMode::DeleteBiome(int32 BiomeId)
{
	UFramework2DTileSet* Set = GetTileSet();
	if (!Set || Set->FindBiomeIndex(BiomeId) == INDEX_NONE) { return; }
	UFramework2DTileMapAsset* Map = GetTileMap();
	const bool bWasActive = GetActiveBiomeId() == BiomeId;

	// Un solo paso de deshacer para el tileset y la receta. El mapa ya generado se queda como
	// esta (borrar un bioma no debe cambiar el nivel).
	const FScopedTransaction Transaction(LOCTEXT("BiomeDelete", "Delete biome"));
	Set->SetFlags(RF_Transactional);
	Set->Modify();
	Set->RemoveBiome(BiomeId);
	if (Map && (bWasActive || Map->ProcGen.BiomeId == BiomeId))
	{
		// La receta pasa al primero que quede (o a 0 si no queda ninguno).
		const int32 NewActive = Set->Biomes.Num() > 0 ? Set->Biomes[0].Id : 0;
		if (Map->ProcGen.BiomeId != NewActive)
		{
			Map->SetFlags(RF_Transactional);
			Map->Modify();
			Map->ProcGen.BiomeId = NewActive;
		}
	}
}

void FFramework2DTilePaintMode::RenameBiome(int32 BiomeId, const FText& NewName)
{
	UFramework2DTileSet* Set = GetTileSet();
	FFramework2DBiome* Biome = Set ? Set->FindBiomeByIdMutable(BiomeId) : nullptr;
	if (!Biome) { return; }
	const FString Clean = NewName.ToString().TrimStartAndEnd();
	if (Clean.IsEmpty() || Biome->Name.ToString().Equals(Clean, ESearchCase::CaseSensitive)) { return; }
	// El nombre solo se ve en el panel: ni rehornear ni regenerar.
	const FScopedTransaction Transaction(LOCTEXT("BiomeRename", "Rename biome"));
	Set->SetFlags(RF_Transactional);
	Set->Modify();
	Biome->Name = FName(*Clean);
}

void FFramework2DTilePaintMode::ChangeBiome(int32 BiomeId, const FText& Description, TFunctionRef<void(FFramework2DBiome&)> Change)
{
	UFramework2DTileSet* Set = GetTileSet();
	const FFramework2DBiome* Biome = Set ? Set->FindBiomeById(BiomeId) : nullptr;
	if (!Biome) { return; }

	// Se prueba el cambio en una copia: si no cambia nada, ni paso de deshacer ni regenerar.
	FFramework2DBiome Edited = *Biome;
	Change(Edited);
	Edited.Id = Biome->Id; // el Id lo guardan las recetas de los mapas: no se toca desde aqui
	if (FFramework2DBiome::StaticStruct()->CompareScriptStruct(Biome, &Edited, PPF_None)) { return; }

	// Los biomas no cambian lo que se ve: sin rehornear. Salvo con "Regenerar al cambiar" en el
	// bioma activo: entonces el mapa se regenera en ESTE mismo paso de deshacer.
	UFramework2DTileMapAsset* Map = GetTileMap();
	const bool bRegenerate = bAutoGenerate && Map && GetActiveBiomeId() == BiomeId;
	// Los fondos parallax del bioma activo se ven ya en el mapa (sin esperar a generar).
	const UScriptStruct* BackdropStruct = FFramework2DBackdropLayer::StaticStruct();
	bool bBackdropsChanged = Edited.Backdrops.Num() != Biome->Backdrops.Num();
	for (int32 i = 0; i < Edited.Backdrops.Num() && !bBackdropsChanged; ++i)
	{
		bBackdropsChanged = !BackdropStruct->CompareScriptStruct(&Edited.Backdrops[i], &Biome->Backdrops[i], PPF_None);
	}
	const bool bSyncBackdrops = bBackdropsChanged && Map && GetActiveBiomeId() == BiomeId;
	bool bGenerated = false;
	{
		const FScopedTransaction Transaction(Description);
		Set->SetFlags(RF_Transactional);
		Set->Modify();
		if (bSyncBackdrops)
		{
			Map->SetFlags(RF_Transactional);
			Map->Modify();
			Map->Backdrops = Edited.Backdrops;
		}
		if (FFramework2DBiome* Found = Set->FindBiomeByIdMutable(BiomeId)) { *Found = Edited; }
		if (bRegenerate) { bGenerated = Framework2DModeGenAuto(*this, Map); }
	}
	if (bGenerated) { Framework2DModeGenRebuild(*this, Map); }
	else if (bSyncBackdrops) { RefreshPreview(); }
}

void FFramework2DTilePaintMode::SetBiomePropTexture(int32 BiomeId, int32 Index, UTexture2D* Texture)
{
	UFramework2DTileSet* Set = GetTileSet();
	const FFramework2DBiome* Biome = Set ? Set->FindBiomeById(BiomeId) : nullptr;
	if (!Biome || !Biome->Props.IsValidIndex(Index)) { return; }
	const FFramework2DPropDef* Current = Set->FindPropById(Biome->Props[Index].PropId);
	if (Current && Current->Texture == Texture) { return; }

	// La imagen es un objeto del TileSet (se reutiliza si ya existe) y el bioma apunta a su Id.
	UFramework2DTileMapAsset* Map = GetTileMap();
	const bool bRegenerate = bAutoGenerate && Map && GetActiveBiomeId() == BiomeId;
	bool bGenerated = false;
	{
		const FScopedTransaction Transaction(LOCTEXT("BiomePropTexture", "Large object image"));
		Set->SetFlags(RF_Transactional);
		Set->Modify();
		const int32 PropId = Texture ? Set->FindOrAddProp(Texture) : 0;
		if (FFramework2DBiome* Found = Set->FindBiomeByIdMutable(BiomeId))
		{
			if (Found->Props.IsValidIndex(Index)) { Found->Props[Index].PropId = PropId; }
		}
		if (bRegenerate) { bGenerated = Framework2DModeGenAuto(*this, Map); }
	}
	if (bGenerated) { Framework2DModeGenRebuild(*this, Map); }
	else
	{
		// Los objetos ya colocados con esa imagen se ven al rehornear.
		RefreshPreview();
	}
}

void FFramework2DTilePaintMode::SetBiomeSlot(int32 BiomeId, EFramework2DBiomeSlot Slot, int32 Value)
{
	const UFramework2DTileSet* Set = GetTileSet();
	if (!Set || Slot >= EFramework2DBiomeSlot::Count) { return; }
	const int32 Piece = Value < 0 ? -1 : Value;
	if (Piece >= 0 && !Set->IsValidValue(Piece)) { return; } // un valor que no existe no se guarda
	ChangeBiome(BiomeId, Piece < 0 ? LOCTEXT("BiomeClearSlot", "Clear biome piece") : LOCTEXT("BiomeSetSlot", "Choose biome piece"),
		[Slot, Piece](FFramework2DBiome& InBiome)
		{
			if (int32* Ref = Framework2D::BiomeSlotRef(InBiome, Slot)) { *Ref = Piece; }
		});
}

void FFramework2DTilePaintMode::SetBiome3x3FromBlock(int32 BiomeId, bool bBackground, int32 TopLeftTileValue)
{
	const UFramework2DTileSet* Set = GetTileSet();
	if (!Set || !Framework2D::IsAtlasTileValue(TopLeftTileValue)) { return; }

	// Columnas de la pagina del tile (cada pagina tiene su propia imagen).
	const int32 PageId = Framework2D::TilePageOf(TopLeftTileValue);
	int32 Cols = 0, Rows = 0;
	if (!Set->GetPageGrid(PageId, Cols, Rows)) { return; }
	const int32 Local = Framework2D::TileLocalOf(TopLeftTileValue);
	const int32 Col = Local % Cols;
	const int32 Row = Local / Cols;
	if (Col + 2 >= Cols || Row + 2 >= Rows) { return; } // el bloque se sale de la pagina

	TArray<int32, TInlineAllocator<FFramework2DTile3x3::Num>> Pieces;
	for (int32 i = 0; i < FFramework2DTile3x3::Num; ++i)
	{
		const int32 Piece = Framework2D::MakeTileValue(PageId, (Row + i / 3) * Cols + (Col + i % 3));
		if (!Set->IsValidValue(Piece)) { return; }
		Pieces.Add(Piece);
	}
	ChangeBiome(BiomeId, bBackground ? LOCTEXT("BiomeBackground3x3", "Biome background 3×3") : LOCTEXT("BiomeGround3x3", "Biome terrain 3×3"),
		[&Pieces, bBackground](FFramework2DBiome& InBiome)
		{
			FFramework2DTile3x3& Block = bBackground ? InBiome.Background : InBiome.Ground;
			for (int32 i = 0; i < FFramework2DTile3x3::Num; ++i) { Block.Set(i, Pieces[i]); }
		});
}

bool FFramework2DTilePaintMode::CanUseSelectionAs3x3() const
{
	const UFramework2DTileSet* Set = GetTileSet();
	return Set && Set->FindPageIndex(BrushPage) != INDEX_NONE && !IsSpecialBrush() && BrushWidth() == 3 && BrushHeight() == 3;
}

void FFramework2DTilePaintMode::SetBiome3x3FromSelection(int32 BiomeId, bool bBackground)
{
	int32 TopLeft = 0, SelectionW = 0, SelectionH = 0;
	if (!CanUseSelectionAs3x3() || !GetSelectionBlock(TopLeft, SelectionW, SelectionH)) { return; }
	SetBiome3x3FromBlock(BiomeId, bBackground, TopLeft);
}

void FFramework2DTilePaintMode::SetBiome5x5FromBlock(int32 BiomeId, int32 TopLeftTileValue)
{
	const UFramework2DTileSet* Set = GetTileSet();
	if (!Set || !Framework2D::IsAtlasTileValue(TopLeftTileValue)) { return; }
	const int32 PageId = Framework2D::TilePageOf(TopLeftTileValue);
	int32 Cols = 0, Rows = 0;
	if (!Set->GetPageGrid(PageId, Cols, Rows)) { return; }
	const int32 Local = Framework2D::TileLocalOf(TopLeftTileValue);
	const int32 Col = Local % Cols;
	const int32 Row = Local / Cols;
	if (Col + 4 >= Cols || Row + 4 >= Rows) { return; } // el bloque se sale de la pagina

	TArray<int32, TInlineAllocator<25>> Pieces;
	for (int32 i = 0; i < 25; ++i)
	{
		const int32 Piece = Framework2D::MakeTileValue(PageId, (Row + i / 5) * Cols + (Col + i % 5));
		if (!Set->IsValidValue(Piece)) { return; }
		Pieces.Add(Piece);
	}
	ChangeBiome(BiomeId, LOCTEXT("BiomeGround5x5", "Biome terrain 5×5"), [&Pieces](FFramework2DBiome& InBiome)
	{
		InBiome.Ground5.Pieces.SetNum(25);
		for (int32 i = 0; i < 25; ++i) { InBiome.Ground5.Pieces[i] = Pieces[i]; }
	});
}

bool FFramework2DTilePaintMode::CanUseSelectionAs5x5() const
{
	const UFramework2DTileSet* Set = GetTileSet();
	return Set && Set->FindPageIndex(BrushPage) != INDEX_NONE && !IsSpecialBrush() && BrushWidth() == 5 && BrushHeight() == 5;
}

bool FFramework2DTilePaintMode::GetSelectionBlock(int32& OutTile, int32& OutWidth, int32& OutHeight, int32 MaxWidth, int32 MaxHeight) const
{
	const UFramework2DTileSet* Set = GetTileSet();
	int32 Cols = 0, Rows = 0;
	if (!Set || Set->FindPageIndex(BrushPage) == INDEX_NONE || IsSpecialBrush() || !Set->GetPageGrid(BrushPage, Cols, Rows)) { return false; }
	if (BrushRect.Min.X < 0 || BrushRect.Min.Y < 0 || BrushRect.Max.X >= Cols || BrushRect.Max.Y >= Rows) { return false; }
	OutTile = Framework2D::MakeTileValue(BrushPage, BrushRect.Min.Y * Cols + BrushRect.Min.X);
	OutWidth = BrushWidth();
	OutHeight = BrushHeight();
	return OutWidth <= MaxWidth && OutHeight <= MaxHeight && Set->IsValidValue(OutTile);
}

void FFramework2DTilePaintMode::SetBiome5x5FromSelection(int32 BiomeId)
{
	int32 Tile = 0, SelectionW = 0, SelectionH = 0;
	if (!CanUseSelectionAs5x5() || !GetSelectionBlock(Tile, SelectionW, SelectionH)) { return; }
	SetBiome5x5FromBlock(BiomeId, Tile);
}

void FFramework2DTilePaintMode::AddBiomeCenterVariant(int32 BiomeId, int32 Value)
{
	const UFramework2DTileSet* Set = GetTileSet();
	if (!Set || Value < 0 || !Set->IsValidValue(Value)) { return; }
	// Una variante repetida no anade nada: sin paso de deshacer.
	ChangeBiome(BiomeId, LOCTEXT("BiomeAddVariant", "Add center variant"), [Value](FFramework2DBiome& InBiome)
	{
		InBiome.CenterVariants.AddUnique(Value);
	});
}

void FFramework2DTilePaintMode::RemoveBiomeCenterVariant(int32 BiomeId, int32 Index)
{
	ChangeBiome(BiomeId, LOCTEXT("BiomeRemoveVariant", "Remove center variant"), [Index](FFramework2DBiome& InBiome)
	{
		if (InBiome.CenterVariants.IsValidIndex(Index)) { InBiome.CenterVariants.RemoveAt(Index); }
	});
}

void FFramework2DTilePaintMode::AddBiomeDecoration(int32 BiomeId, int32 Value, EFramework2DDecorPlacement Placement)
{
	const UFramework2DTileSet* Set = GetTileSet();
	if (!Set || Value < 0 || !Set->IsValidValue(Value)) { return; }
	ChangeBiome(BiomeId, LOCTEXT("BiomeAddDecoration", "Add decoration to the biome"), [Value, Placement](FFramework2DBiome& InBiome)
	{
		FFramework2DBiomeDecoration& Added = InBiome.Decorations.AddDefaulted_GetRef();
		Added.Value = Value;
		Added.Weight = 1.0f;
		Added.Placement = Placement;
	});
}

void FFramework2DTilePaintMode::RemoveBiomeDecoration(int32 BiomeId, int32 Index)
{
	ChangeBiome(BiomeId, LOCTEXT("BiomeRemoveDecoration", "Remove decoration from the biome"), [Index](FFramework2DBiome& InBiome)
	{
		if (InBiome.Decorations.IsValidIndex(Index)) { InBiome.Decorations.RemoveAt(Index); }
	});
}

//---------------------- Bioma de ejemplo ----------------------

// Imagen del ejemplo: la del proyecto si ya se importo; si no, se importa desde la carpeta
// Ejemplo del plugin con los ajustes de pixel art (sin filtro ni mipmaps).
static UTexture2D* Framework2DModeImportExampleTexture(const FString& RelativeFile)
{
	const FString BaseName = FPaths::GetBaseFilename(RelativeFile);
	const FString Folder = TEXT("/Game/Framework2D_Ejemplo");
	const FString ObjectPath = Folder / BaseName + TEXT(".") + BaseName;
	UTexture2D* Texture = LoadObject<UTexture2D>(nullptr, *ObjectPath, nullptr, LOAD_NoWarn | LOAD_Quiet);
	if (!Texture)
	{
		const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("Framework2DTerrain"));
		const FString File = Plugin.IsValid() ? FPaths::ConvertRelativePathToFull(Plugin->GetBaseDir() / TEXT("Ejemplo") / RelativeFile) : FString();
		if (File.IsEmpty() || !FPaths::FileExists(File))
		{
			UE_LOG(LogTemp, Warning, TEXT("[Framework2DTerrain] No encuentro la imagen de ejemplo '%s'."), *File);
			return nullptr;
		}
		UAutomatedAssetImportData* ImportData = NewObject<UAutomatedAssetImportData>();
		ImportData->Filenames.Add(File);
		ImportData->DestinationPath = Folder;
		ImportData->bReplaceExisting = false;
		IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
		for (UObject* Imported : AssetTools.ImportAssetsAutomated(ImportData))
		{
			if (UTexture2D* AsTexture = Cast<UTexture2D>(Imported)) { Texture = AsTexture; }
		}
		if (!Texture) { return nullptr; }
	}
	// Pixel art: nitido, sin mipmaps ni compresion que ensucie los colores.
	if (Texture->Filter != TF_Nearest || Texture->MipGenSettings != TMGS_NoMipmaps)
	{
		Texture->Modify();
		Texture->Filter = TF_Nearest;
		Texture->MipGenSettings = TMGS_NoMipmaps;
		Texture->LODGroup = TEXTUREGROUP_Pixels2D;
		Texture->CompressionSettings = TC_EditorIcon;
		Texture->PostEditChange();
		Texture->MarkPackageDirty();
	}
	return Texture;
}

int32 FFramework2DTilePaintMode::CreateExampleOutdoorBiome()
{
	UFramework2DTileSet* Set = GetTileSet();
	UFramework2DTileMapAsset* Map = GetTileMap();
	if (!Set || !Map) { return INDEX_NONE; }

	// 1) Imagenes (fuera de la transaccion: importar assets no se deshace con Ctrl+Z).
	UTexture2D* AtlasBioma = Framework2DModeImportExampleTexture(TEXT("AtlasBioma.png"));
	UTexture2D* AtlasExterior = Framework2DModeImportExampleTexture(TEXT("Exterior/AtlasExterior.png"));
	if (!AtlasBioma || !AtlasExterior) { return INDEX_NONE; }
	const TCHAR* BackdropFiles[4] = { TEXT("Exterior/Cielo.png"), TEXT("Exterior/Montanas.png"), TEXT("Exterior/BosqueLejano.png"), TEXT("Exterior/BosqueCercano.png") };
	UTexture2D* Backdrops[4] = {};
	for (int32 i = 0; i < 4; ++i) { Backdrops[i] = Framework2DModeImportExampleTexture(BackdropFiles[i]); }
	// Apoyo = el ancho del pie (tronco, base de la roca): asi caben tambien en lomas.
	struct FPropFile { const TCHAR* File; float Weight; EFramework2DPropDepth Depth; int32 Sink; int32 Footprint; };
	const FPropFile PropFiles[] =
	{
		{ TEXT("Exterior/Pino.png"), 3.0f, EFramework2DPropDepth::Behind, 2, 1 },
		{ TEXT("Exterior/Roble.png"), 1.6f, EFramework2DPropDepth::Behind, 3, 2 },
		{ TEXT("Exterior/Tocon.png"), 0.6f, EFramework2DPropDepth::Behind, 2, 1 },
		{ TEXT("Exterior/Roca.png"), 1.0f, EFramework2DPropDepth::Behind, 3, 2 },
		{ TEXT("Exterior/Arbusto.png"), 1.4f, EFramework2DPropDepth::Front, 2, 2 },
		{ TEXT("Exterior/SetaGigante.png"), 0.5f, EFramework2DPropDepth::Front, 1, 1 },
		{ TEXT("Exterior/PiedraRunica.png"), 0.35f, EFramework2DPropDepth::Behind, 3, 1 },
	};
	TArray<UTexture2D*> PropTextures;
	for (const FPropFile& Entry : PropFiles) { PropTextures.Add(Framework2DModeImportExampleTexture(Entry.File)); }

	// 2) Paginas del atlas (cada una, su paso de deshacer) y los biomas Bosque y Cueva.
	auto FindPage = [Set](const UTexture2D* Texture)
	{
		for (int32 Index = 0; Index < Set->GetNumPages(); ++Index)
		{
			const int32 Id = Set->GetPageIdAt(Index);
			if (Set->GetPageTexture(Id) == Texture) { return Id; }
		}
		return (int32)INDEX_NONE;
	};
	int32 BiomaPage = FindPage(AtlasBioma);
	if (BiomaPage == INDEX_NONE) { BiomaPage = AddAtlasPage(AtlasBioma); }
	int32 ExteriorPage = FindPage(AtlasExterior);
	if (ExteriorPage == INDEX_NONE) { ExteriorPage = AddAtlasPage(AtlasExterior); }
	if (BiomaPage == INDEX_NONE || ExteriorPage == INDEX_NONE) { return INDEX_NONE; }

	int32 ForestId = INDEX_NONE;
	for (const FFramework2DBiome& Biome : Set->Biomes)
	{
		if (Biome.Name == FName(TEXT("Forest"))) { ForestId = Biome.Id; }
	}
	if (ForestId == INDEX_NONE) { ForestId = CreateExampleBiome(BiomaPage); }
	const FFramework2DBiome* Forest = Set->FindBiomeById(ForestId);
	if (!Forest) { return INDEX_NONE; }

	int32 ExteriorCols = 0, ExteriorRows = 0;
	Set->GetPageGrid(ExteriorPage, ExteriorCols, ExteriorRows);
	auto ExTile = [ExteriorPage, ExteriorCols](int32 Row, int32 Col) { return Framework2D::MakeTileValue(ExteriorPage, Row * FMath::Max(1, ExteriorCols) + Col); };

	int32 OutdoorId = INDEX_NONE;
	{
		// 3) Todo lo demas en UN paso: generadores, objetos, bioma, receta y mapa generado.
		const FScopedTransaction Transaction(LOCTEXT("BiomeCreateOutdoor", "Create example outdoor biome"));
		Set->SetFlags(RF_Transactional);
		Set->Modify();
		Map->SetFlags(RF_Transactional);
		Map->Modify();

		// Las tablas del puente chocan (madera); lo demas de esa pagina es decoracion.
		for (int32 Col = 0; Col < 3; ++Col)
		{
			if (FFramework2DTileDef* Def = Set->FindTileDefMutable(ExTile(0, Col))) { Def->MaterialName = TEXT("Wood"); }
		}

		auto MakeGenerator = [Set](const TCHAR* Name, const TArray<FIntVector>& Sprites) // (tile, ancho, alto)
		{
			const int32 Id = Set->AddGenerator(FName(Name));
			FFramework2DGenerator* Generator = Set->FindGeneratorById(Id);
			for (const FIntVector& Sprite : Sprites)
			{
				FFramework2DScatterSprite Entry;
				Entry.Tile = Sprite.X;
				Entry.WidthInTiles = Sprite.Y;
				Entry.HeightInTiles = Sprite.Z;
				Generator->Sprites.Add(Entry);
			}
			return Generator;
		};
		// Remate de hierba: hojas que se hunden en el borde y tapan su linea recta.
		FFramework2DGenerator* Fringe = MakeGenerator(TEXT("Remate de hierba"), { FIntVector(ExTile(0, 3), 1, 1), FIntVector(ExTile(0, 4), 1, 1), FIntVector(ExTile(0, 5), 1, 1), FIntVector(ExTile(0, 6), 1, 1) });
		Fringe->Density = 2.0f;
		Fringe->JitterX = 3.0f;
		Fringe->OffsetY = 5.0f;
		Fringe->GroundSearchTiles = 1;
		Fringe->BrightnessVariation = 0.08f;
		const int32 FringeValue = Framework2D::MakeGeneratorValue(Fringe->Id);
		// Rocas y raices que cuelgan bajo islas y salientes.
		FFramework2DGenerator* Hanging = MakeGenerator(TEXT("Rocas colgantes"), { FIntVector(ExTile(0, 7), 1, 1), FIntVector(ExTile(0, 8), 1, 1), FIntVector(ExTile(0, 9), 1, 1), FIntVector(ExTile(0, 10), 1, 1) });
		Hanging->Density = 0.9f;
		Hanging->JitterX = 4.0f;
		Hanging->OffsetY = 2.0f;
		Hanging->bHangFromCeiling = true;
		Hanging->GroundSearchTiles = 1;
		const int32 HangingValue = Framework2D::MakeGeneratorValue(Hanging->Id);
		// Flores y plantas del exterior.
		FFramework2DGenerator* Flowers = MakeGenerator(TEXT("Flores del bosque"), { FIntVector(ExTile(0, 11), 1, 1), FIntVector(ExTile(0, 12), 1, 1), FIntVector(ExTile(0, 13), 1, 2), FIntVector(ExTile(0, 14), 1, 1), FIntVector(ExTile(0, 15), 1, 1) });
		Flowers->Density = 0.8f;
		Flowers->JitterX = 6.0f;
		Flowers->OffsetY = 1.0f;
		const int32 FlowersValue = Framework2D::MakeGeneratorValue(Flowers->Id);

		// El bioma: el bosque de siempre + puentes, bordes, fondos y objetos grandes.
		FFramework2DBiome Outdoor = *Set->FindBiomeById(ForestId);
		OutdoorId = Set->AddBiome(TEXT("Outdoor forest"));
		Outdoor.Id = OutdoorId;
		Outdoor.Name = TEXT("Outdoor forest");
		Outdoor.BridgeLeft = ExTile(0, 0);
		Outdoor.BridgeMiddle = ExTile(0, 1);
		Outdoor.BridgeRight = ExTile(0, 2);
		Outdoor.EdgeTop = FringeValue;
		Outdoor.EdgeBottom = HangingValue;
		FFramework2DBiomeDecoration FlowerDeco;
		FlowerDeco.Value = FlowersValue;
		FlowerDeco.Weight = 2.0f;
		Outdoor.Decorations.Add(FlowerDeco);
		// Sin colinas de fondo de tiles: el paisaje lo ponen los fondos parallax.
		const int32 BackgroundCenter = Outdoor.Background.Center;
		Outdoor.Background = FFramework2DTile3x3();
		Outdoor.Background.Center = BackgroundCenter;

		const float Parallax[4] = { 0.0f, 0.08f, 0.22f, 0.4f };
		// Por encima de las lomas mas altas (BaseHeight + 3 alturas de 3 = 15 tiles).
		const float Heights[4] = { 8.0f, 17.0f, 13.0f, 9.0f };
		const TCHAR* BackdropNames[4] = { TEXT("Sky"), TEXT("Mountains"), TEXT("Far forest"), TEXT("Near forest") };
		for (int32 i = 0; i < 4; ++i)
		{
			if (!Backdrops[i]) { continue; }
			FFramework2DBackdropLayer Layer;
			Layer.Name = BackdropNames[i];
			Layer.Texture = Backdrops[i];
			Layer.Parallax = Parallax[i];
			Layer.VerticalParallax = Parallax[i] * 0.5f;
			Layer.Height = Heights[i];
			Layer.Scale = i == 0 ? 2.0f : 1.0f;
			Layer.bFillAbove = i == 0;
			Outdoor.Backdrops.Add(Layer);
		}
		for (int32 i = 0; i < UE_ARRAY_COUNT(PropFiles); ++i)
		{
			if (!PropTextures[i]) { continue; }
			FFramework2DBiomeProp Prop;
			Prop.PropId = Set->FindOrAddProp(PropTextures[i]);
			if (const int32 PropIndex = Set->FindPropIndex(Prop.PropId); PropIndex != INDEX_NONE) { Set->Props[PropIndex].FootprintTiles = PropFiles[i].Footprint; }
			Prop.Weight = PropFiles[i].Weight;
			Prop.Depth = PropFiles[i].Depth;
			Prop.SinkPixels = PropFiles[i].Sink;
			Outdoor.Props.Add(Prop);
		}
		if (FFramework2DBiome* Stored = Set->FindBiomeByIdMutable(OutdoorId)) { *Stored = Outdoor; }

		// Receta de exterior: lomas, islas con puentes, agua y arboles.
		FFramework2DProcGenSettings& Recipe = Map->ProcGen;
		Recipe.BiomeId = OutdoorId;
		Recipe.ReliefStyle = EFramework2DReliefStyle::Hills;
		Recipe.Roughness = 0.45f;
		Recipe.Levels = 4;
		Recipe.LevelHeight = 3;
		Recipe.BaseHeight = 6;
		Recipe.RampChance = 0.9f;
		Recipe.GentleRampChance = 0.5f;
		Recipe.PitChance = 0.3f;
		Recipe.PitDepth = 3;
		Recipe.LakeChance = 0.6f;
		Recipe.WaterfallChance = 0.4f;
		Recipe.PlatformChance = 0.0f;
		Recipe.IslandChance = 0.35f;
		Recipe.IslandMinWidth = 4;
		Recipe.IslandMaxWidth = 8;
		Recipe.BridgeChance = 0.8f;
		Recipe.PropDensity = 0.45f;
		Recipe.PropSpacing = 1;
		Recipe.DecorationDensity = 0.7f;
		Recipe.BackgroundRise = 0;
		if (Map->Width < 64 || Map->Height < 32) { Map->Resize(FMath::Max(Map->Width, 120), FMath::Max(Map->Height, 48)); }

		LastGenerateReport = UFramework2DProcGenLibrary::GenerateMap(Map);
		bHasGenerateReport = true;
	}
	Framework2DModeGenRebuild(*this, Set, Map);
	return OutdoorId;
}

int32 FFramework2DTilePaintMode::CreateTTilesBiomes(int32 PageId)
{
	UFramework2DTileSet* Set = GetTileSet();
	if (!Set || Set->FindPageIndex(PageId) == INDEX_NONE) { return INDEX_NONE; }
	int32 Cols = 0, Rows = 0;
	if (!Set->GetPageGrid(PageId, Cols, Rows) || Cols < 25 || Rows < 25)
	{
		UE_LOG(LogTemp, Warning, TEXT("[Framework2DTerrain] La pagina %d de '%s' no tiene la distribucion de T_Tiles (25x25 tiles; tiene %dx%d)."), PageId, *Set->GetName(), Cols, Rows);
		return INDEX_NONE;
	}
	UFramework2DTileMapAsset* Map = GetTileMap();
	// (columna, fila) del atlas -> valor de tile.
	auto T = [PageId, Cols](int32 Col, int32 Row) { return Framework2D::MakeTileValue(PageId, Row * Cols + Col); };

	int32 ForestId = INDEX_NONE;
	{
		const FScopedTransaction Transaction(LOCTEXT("BiomeCreateTTiles", "Create T_Tiles biomes"));
		Set->SetFlags(RF_Transactional);
		Set->Modify();
		const TArray<FFramework2DTileDef>* PageTiles = Set->GetPageTiles(PageId);
		if (!PageTiles || PageTiles->Num() < Cols * Rows) { Set->RefreshTilesFromAtlas(); }
		for (const TCHAR* Material : { TEXT("Dirt"), TEXT("Stone"), TEXT("Wood"), TEXT("Decoration") })
		{
			Framework2DModeGenEnsureMaterial(*Set, FName(Material));
		}

		// 1) Materiales: todo decoracion salvo el terreno, el tablon, el puente y sus cantos, el
		// pedrusco, el pie de pared y la roca con matojo.
		for (int32 Index = 0; Index < Cols * Rows; ++Index)
		{
			if (FFramework2DTileDef* Def = Set->FindTileDefMutable(Framework2D::MakeTileValue(PageId, Index))) { Def->MaterialName = TEXT("Decoration"); }
		}
		auto SetMaterial = [&](int32 Col0, int32 Row0, int32 Col1, int32 Row1, const TCHAR* Material)
		{
			for (int32 Row = Row0; Row <= Row1; ++Row)
			{
				for (int32 Col = Col0; Col <= Col1; ++Col)
				{
					if (FFramework2DTileDef* Def = Set->FindTileDefMutable(T(Col, Row))) { Def->MaterialName = Material; }
				}
			}
		};
		SetMaterial(0, 0, 4, 4, TEXT("Dirt"));   // terreno de hierba
		SetMaterial(0, 5, 4, 9, TEXT("Stone"));  // terreno de roca
		SetMaterial(5, 5, 7, 6, TEXT("Wood"));   // tablon (y el canto que asoma en la fila de encima)
		SetMaterial(5, 9, 9, 9, TEXT("Wood"));   // tablas del puente
		SetMaterial(5, 3, 6, 3, TEXT("Dirt"));   // pedrusco
		SetMaterial(5, 4, 7, 4, TEXT("Dirt"));   // pie de pared de la hierba
		SetMaterial(6, 8, 8, 8, TEXT("Wood"));   // canto del puente
		SetMaterial(0, 10, 1, 11, TEXT("Stone")); // roca con matojo

		// 2) Generadores (sprites del atlas: tile de arriba-izquierda, ancho y alto en tiles).
		auto MakeGenerator = [Set](const TCHAR* Name, const TArray<FIntVector>& Sprites, const TArray<float>& Weights, float Density)
		{
			const int32 Id = Set->AddGenerator(FName(Name));
			FFramework2DGenerator* Generator = Set->FindGeneratorById(Id);
			for (int32 i = 0; i < Sprites.Num(); ++i)
			{
				FFramework2DScatterSprite Entry;
				Entry.Tile = Sprites[i].X;
				Entry.WidthInTiles = Sprites[i].Y;
				Entry.HeightInTiles = Sprites[i].Z;
				Entry.Weight = Weights.IsValidIndex(i) ? Weights[i] : 1.0f;
				Generator->Sprites.Add(Entry);
			}
			Generator->Density = Density;
			Generator->JitterX = 6.0f;
			Generator->OffsetY = 1.0f;
			return Framework2D::MakeGeneratorValue(Id);
		};
		const int32 Flowers = MakeGenerator(TEXT("Flores (T_Tiles)"),
			{ FIntVector(T(22, 17), 1, 1), FIntVector(T(15, 17), 1, 2), FIntVector(T(16, 17), 1, 1), FIntVector(T(17, 17), 1, 2) }, { 3.0f, 1.0f, 1.0f, 1.2f }, 1.2f);
		const int32 Mushrooms = MakeGenerator(TEXT("Setas (T_Tiles)"),
			{ FIntVector(T(15, 15), 1, 1), FIntVector(T(15, 16), 1, 1), FIntVector(T(20, 15), 1, 2), FIntVector(T(16, 15), 2, 2), FIntVector(T(18, 15), 2, 2) }, { 2.0f, 2.0f, 1.0f, 0.6f, 0.5f }, 0.7f);
		const int32 Reeds = MakeGenerator(TEXT("Reeds (T_Tiles)"),
			{ FIntVector(T(16, 18), 1, 2), FIntVector(T(15, 19), 1, 1), FIntVector(T(16, 20), 1, 2) }, { 1.0f, 1.0f, 1.0f }, 0.8f);
		const int32 BigPlant = MakeGenerator(TEXT("Planta grande (T_Tiles)"), { FIntVector(T(20, 22), 2, 2) }, { 1.0f }, 0.5f);

		// 3) Objetos grandes del propio atlas (detras del terreno).
		struct FAtlasProp { int32 Col, Row, W, H; float Weight; int32 Foot; int32 Sink; const TCHAR* Name; };
		const FAtlasProp ForestProps[] =
		{
			{ 17, 0, 8, 3, 1.0f, 4, 3, TEXT("Copa verde") },
			{ 17, 3, 8, 3, 0.6f, 4, 3, TEXT("Copa amarilla") },
			{ 17, 6, 8, 3, 0.8f, 4, 3, TEXT("Copa oliva") },
			{ 17, 9, 8, 3, 0.8f, 4, 3, TEXT("Copa oscura") },
			// Tres montones de roca (se tocan solo en los pixeles de abajo, que tapa la hierba).
			{ 0, 21, 5, 2, 0.4f, 5, 4, TEXT("Rocas 1") },
			{ 5, 21, 5, 2, 0.4f, 5, 4, TEXT("Rocas 2") },
			{ 10, 21, 5, 2, 0.4f, 5, 4, TEXT("Rocas 3") },
			// El monticulo de hierba: un seto detras del suelo, hundido hasta tapar sus lados rectos.
			{ 5, 0, 4, 3, 1.0f, 4, 22, TEXT("Seto") },
			{ 0, 14, 3, 3, 0.5f, 3, 3, TEXT("Arbusto oscuro") },
		};
		auto MakeProps = [&](FFramework2DBiome& Biome, std::initializer_list<int32> Which)
		{
			for (const int32 Index : Which)
			{
				const FAtlasProp& P = ForestProps[Index];
				FFramework2DBiomeProp Entry;
				Entry.PropId = Set->FindOrAddAtlasProp(T(P.Col, P.Row), P.W, P.H, FName(P.Name));
				if (const int32 PropIndex = Set->FindPropIndex(Entry.PropId); PropIndex != INDEX_NONE) { Set->Props[PropIndex].FootprintTiles = P.Foot; }
				Entry.Weight = P.Weight;
				Entry.Depth = EFramework2DPropDepth::Behind;
				Entry.SinkPixels = P.Sink;
				Biome.Props.Add(Entry);
			}
		};

		// 4) Los dos biomas.
		auto Fill = [&](FFramework2DBiome& Biome, int32 GroundRow0)
		{
			for (int32 i = 0; i < 25; ++i) { Biome.Ground5.Ref(i) = T(i % 5, GroundRow0 + i / 5); }
			Biome.PlatformLeft = T(5, 6);
			Biome.PlatformMiddle = T(6, 6);
			Biome.PlatformRight = T(7, 6);
			Biome.BridgeLeft = T(5, 9);
			Biome.BridgeMiddle = T(7, 9);
			Biome.BridgeRight = T(9, 9);
			Biome.BridgePostLeftLow = T(5, 8);
			Biome.BridgePostLeftHigh = T(5, 7);
			Biome.BridgePostRightLow = T(9, 8);
			Biome.BridgePostRightHigh = T(9, 7);
			Biome.WaterCrest = T(7, 18);
			Biome.WaterSurface = T(7, 19);
			Biome.WaterBody = T(7, 20);
			Biome.WaterfallTop = T(4, 17);
			Biome.WaterfallBody = T(4, 18);
			Biome.WaterfallBottom = T(4, 20);
			Biome.PlatformCapLeft = T(5, 5);
			Biome.PlatformCapMiddle = T(6, 5);
			Biome.PlatformCapRight = T(7, 5);
			Biome.BridgeCapLeft = T(6, 8);
			Biome.BridgeCapMiddle = T(7, 8);
			Biome.BridgeCapRight = T(8, 8);
			// La fila de debajo de la franja de rocas del 5x5 es lisa: el interior profundo.
			Biome.GroundDeep = T(2, GroundRow0 + 3);
		};
		auto Deco = [](FFramework2DBiome& Biome, int32 Value, float Weight)
		{
			FFramework2DBiomeDecoration Entry;
			Entry.Value = Value;
			Entry.Weight = Weight;
			Biome.Decorations.Add(Entry);
		};

		ForestId = Set->AddBiome(TEXT("Forest (T_Tiles)"));
		if (FFramework2DBiome* Forest = Set->FindBiomeByIdMutable(ForestId))
		{
			Fill(*Forest, 0);
			// Fondo: follaje oscuro con el arbusto redondo (0-2, 14-16) como bordes del 3x3 (las colinas
			// del fondo salen redondeadas) y el follaje con textura (2, 12) de centro.
			for (int32 i = 0; i < 9; ++i) { Forest->Background.Ref(i) = T(i % 3, 14 + i / 3); }
			Forest->Background.Center = T(2, 12);
			Deco(*Forest, Flowers, 4.0f);
			Deco(*Forest, Mushrooms, 1.5f);
			Deco(*Forest, Reeds, 1.0f);
			Deco(*Forest, BigPlant, 0.6f);
			MakeProps(*Forest, { 0, 1, 2, 3, 4, 5, 6, 7, 8 });
			// La hierba pasa por delante del pie de cada pared y se remata con el matorral.
			Forest->WallFootLeft = T(7, 4);
			Forest->WallFootLeftInner = T(6, 4);
			Forest->WallFootRight = T(7, 4);
			Forest->WallFootRightInner = T(5, 4);
		}
		const int32 RockId = Set->AddBiome(TEXT("Rock (T_Tiles)"));
		if (FFramework2DBiome* Rock = Set->FindBiomeByIdMutable(RockId))
		{
			Fill(*Rock, 5);
			// Fondo: el peñasco (6-8, 10-12) como bordes del 3x3 (colinas redondeadas) y roca con textura de centro.
			for (int32 i = 0; i < 9; ++i) { Rock->Background.Ref(i) = T(6 + i % 3, 10 + i / 3); }
			Rock->Background.Center = T(9, 11);
			Deco(*Rock, Mushrooms, 3.0f);
			Deco(*Rock, BigPlant, 0.5f);
			MakeProps(*Rock, { 4, 5, 6 });
		}
		if (Map)
		{
			Map->SetFlags(RF_Transactional);
			Map->Modify();
			Map->ProcGen.BiomeId = ForestId;
		}
	}
	return ForestId;
}

int32 FFramework2DTilePaintMode::CreateExampleBiome(int32 PageId)
{
	// Distribucion de Ejemplo/AtlasBioma.png: 16 columnas x 10 filas de tiles (ver la
	// especificacion v2.3, seccion 5). Una pagina mas grande vale: se usan SUS columnas.
	UFramework2DTileSet* Set = GetTileSet();
	if (!Set || Set->FindPageIndex(PageId) == INDEX_NONE) { return INDEX_NONE; }
	int32 Cols = 0, Rows = 0;
	if (!Set->GetPageGrid(PageId, Cols, Rows) || Cols < 16 || Rows < 10)
	{
		UE_LOG(LogTemp, Warning, TEXT("[Framework2DTerrain] La pagina %d de '%s' no sirve para el bioma de ejemplo: necesita 16x10 tiles o mas (tiene %dx%d)."),
			PageId, *Set->GetName(), Cols, Rows);
		return INDEX_NONE;
	}
	UFramework2DTileMapAsset* Map = GetTileMap();

	// Valor del tile (fila, columna) de esa pagina.
	auto TileAt = [PageId, Cols](int32 Row, int32 Col) { return Framework2D::MakeTileValue(PageId, Row * Cols + Col); };

	const FName Dirt(TEXT("Dirt"));
	const FName Stone(TEXT("Stone"));
	const FName Wood(TEXT("Wood"));
	const FName Decoration(TEXT("Decoration"));

	int32 ForestId = INDEX_NONE;
	{
		// Todo en UN paso de deshacer: materiales, flipbooks, generadores, biomas y receta.
		const FScopedTransaction Transaction(LOCTEXT("BiomeCreateExample", "Create example biome"));
		Set->SetFlags(RF_Transactional);
		Set->Modify();

		// La lista de tiles de la pagina tiene que cubrir la imagen (por si aun no se refresco).
		const TArray<FFramework2DTileDef>* PageTiles = Set->GetPageTiles(PageId);
		if (!PageTiles || PageTiles->Num() < Cols * Rows) { Set->RefreshTilesFromAtlas(); }

		//---- 1) Materiales de los tiles ----
		Framework2DModeGenEnsureMaterial(*Set, Dirt);
		Framework2DModeGenEnsureMaterial(*Set, Stone);
		Framework2DModeGenEnsureMaterial(*Set, Wood);
		Framework2DModeGenEnsureMaterial(*Set, Decoration);
		auto SetMaterial = [Set, &TileAt](int32 Row0, int32 Col0, int32 Row1, int32 Col1, FName Material)
		{
			for (int32 R = Row0; R <= Row1; ++R)
			{
				for (int32 C = Col0; C <= Col1; ++C)
				{
					if (FFramework2DTileDef* Def = Set->FindTileDefMutable(TileAt(R, C))) { Def->MaterialName = Material; }
				}
			}
		};
		// Bosque: terreno, esquinas, variantes, fondo y rampas de tierra; la plataforma, de madera.
		SetMaterial(0, 0, 2, 2, Dirt);
		SetMaterial(0, 3, 1, 4, Dirt);
		SetMaterial(2, 3, 2, 4, Dirt);
		SetMaterial(0, 5, 2, 7, Dirt);
		SetMaterial(0, 8, 0, 13, Dirt);
		SetMaterial(0, 14, 0, 15, Dirt);
		SetMaterial(1, 8, 1, 10, Wood);
		// Cueva: todo de piedra (tambien la repisa).
		SetMaterial(7, 0, 9, 2, Stone);
		SetMaterial(7, 3, 8, 4, Stone);
		SetMaterial(9, 3, 9, 4, Stone);
		SetMaterial(7, 5, 9, 7, Stone);
		SetMaterial(7, 8, 7, 9, Stone);
		SetMaterial(8, 8, 8, 10, Stone);
		// Agua, cascadas y todo lo decorativo: se ve y se rompe, pero no choca.
		SetMaterial(1, 12, 1, 15, Decoration);  // antorcha
		SetMaterial(2, 8, 2, 15, Decoration);   // agua
		SetMaterial(3, 0, 3, 15, Decoration);   // cascada y flor
		SetMaterial(4, 0, 4, 13, Decoration);   // matas, flores, rocas, setas, cartel, caja, huesos
		SetMaterial(5, 0, 6, 3, Decoration);    // arbusto, junco y arbolito
		SetMaterial(5, 4, 5, 13, Decoration);   // colgantes, cristal y estalagmita

		//---- 2) Flipbooks (4 fotogramas seguidos en una fila) ----
		// Si ya hay uno con esos fotogramas (ejemplo creado antes), se reutiliza.
		auto MakeFlipbook = [Set, &TileAt, &Decoration](const TCHAR* Name, int32 Row, int32 Col0, float FPS)
		{
			TArray<int32> Frames;
			for (int32 i = 0; i < 4; ++i) { Frames.Add(TileAt(Row, Col0 + i)); }
			for (const FFramework2DFlipbook& Existing : Set->Flipbooks)
			{
				if (Existing.Frames == Frames) { return Framework2D::MakeFlipbookValue(Existing.Id); }
			}
			const int32 Id = Set->AddFlipbook(Frames, FName(Name));
			if (FFramework2DFlipbook* Created = Set->FindFlipbookById(Id))
			{
				Created->FPS = FPS;
				Created->MaterialName = Decoration;
			}
			return Framework2D::MakeFlipbookValue(Id);
		};
		const int32 WaterSurface   = MakeFlipbook(TEXT("Water"), 2, 8, 6.0f);
		const int32 WaterBody      = MakeFlipbook(TEXT("Water (body)"), 2, 12, 5.0f);
		const int32 WaterfallTop   = MakeFlipbook(TEXT("Cascada (arriba)"), 3, 0, 10.0f);
		const int32 WaterfallBody  = MakeFlipbook(TEXT("Cascada"), 3, 4, 12.0f);
		const int32 WaterfallFoam  = MakeFlipbook(TEXT("Cascada (espuma)"), 3, 8, 10.0f);
		const int32 TorchFlipbook  = MakeFlipbook(TEXT("Antorcha"), 1, 12, 10.0f);
		const int32 FlowerFlipbook = MakeFlipbook(TEXT("Flor"), 3, 12, 4.0f);
		const int32 CrystalFlipbook = MakeFlipbook(TEXT("Cristal"), 5, 8, 6.0f);

		//---- 3) Generadores de vegetacion ----
		auto Sprite = [&TileAt](int32 Row, int32 Col, int32 WidthInTiles, int32 HeightInTiles, float Weight)
		{
			FFramework2DScatterSprite Out;
			Out.Tile = TileAt(Row, Col);
			Out.WidthInTiles = WidthInTiles;
			Out.HeightInTiles = HeightInTiles;
			Out.Weight = Weight;
			return Out;
		};
		// Si ya hay uno que saca esos mismos sprites, se reutiliza (con los ajustes que tenga).
		auto MakeGenerator = [Set, &Decoration](const TCHAR* Name, const TArray<FFramework2DScatterSprite>& Sprites, float Density)
		{
			for (const FFramework2DGenerator& Existing : Set->Generators)
			{
				if (Framework2DModeGenSameSprites(Existing.Sprites, Sprites)) { return Framework2D::MakeGeneratorValue(Existing.Id); }
			}
			const int32 Id = Set->AddGenerator(FName(Name));
			if (FFramework2DGenerator* Created = Set->FindGeneratorById(Id))
			{
				Created->Sprites = Sprites;
				Created->Density = Density;
				Created->JitterX = 6.0f;
				Created->OffsetY = 1.0f;
				Created->MaterialName = Decoration;
			}
			return Framework2D::MakeGeneratorValue(Id);
		};
		const int32 GrassGenerator = MakeGenerator(TEXT("Hierba"), {
			Sprite(4, 0, 1, 1, 3.0f), Sprite(4, 1, 1, 1, 3.0f), Sprite(4, 2, 1, 1, 3.0f),  // matas A-C
			Sprite(4, 3, 1, 1, 1.0f), Sprite(4, 4, 1, 1, 1.0f), Sprite(4, 5, 1, 1, 1.0f) }, // flor roja, flor amarilla, helecho
			2.5f);
		const int32 RockGenerator = MakeGenerator(TEXT("Rocas"), {
			Sprite(4, 6, 1, 1, 1.0f), Sprite(4, 7, 1, 1, 1.0f), Sprite(4, 8, 1, 1, 1.0f),  // rocas A-C
			Sprite(4, 9, 1, 1, 1.0f), Sprite(4, 10, 1, 1, 1.0f) },                          // setas
			0.8f);
		const int32 BushGenerator = MakeGenerator(TEXT("Arbustos"), {
			Sprite(5, 0, 2, 2, 1.0f),   // arbusto 2x2 (un solo sprite)
			Sprite(5, 2, 1, 2, 1.0f),   // junco 1x2
			Sprite(5, 3, 1, 2, 1.0f) }, // arbolito 1x2
			0.6f);
		const int32 CaveGenerator = MakeGenerator(TEXT("Cave"), {
			Sprite(5, 12, 1, 1, 1.0f), Sprite(5, 13, 1, 1, 1.0f),                         // estalagmita, cristal
			Sprite(4, 6, 1, 1, 1.0f), Sprite(4, 7, 1, 1, 1.0f), Sprite(4, 8, 1, 1, 1.0f),  // rocas
			Sprite(4, 13, 1, 1, 1.0f) },                                                    // huesos
			0.8f);

		//---- 4) Biomas ----
		auto Fill3x3 = [&TileAt](FFramework2DTile3x3& Block, int32 Row0, int32 Col0)
		{
			for (int32 i = 0; i < FFramework2DTile3x3::Num; ++i) { Block.Set(i, TileAt(Row0 + i / 3, Col0 + i % 3)); }
		};
		auto AddDecoration = [](FFramework2DBiome& InBiome, int32 Value, float Weight, EFramework2DDecorPlacement Placement)
		{
			FFramework2DBiomeDecoration& Added = InBiome.Decorations.AddDefaulted_GetRef();
			Added.Value = Value;
			Added.Weight = Weight;
			Added.Placement = Placement;
		};
		auto SetWater = [WaterSurface, WaterBody, WaterfallTop, WaterfallBody, WaterfallFoam](FFramework2DBiome& InBiome)
		{
			InBiome.WaterSurface = WaterSurface;
			InBiome.WaterBody = WaterBody;
			InBiome.WaterfallTop = WaterfallTop;
			InBiome.WaterfallBody = WaterfallBody;
			InBiome.WaterfallBottom = WaterfallFoam;
		};
		const EFramework2DDecorPlacement Ground = EFramework2DDecorPlacement::Ground;
		const EFramework2DDecorPlacement Ceiling = EFramework2DDecorPlacement::Ceiling;

		// Bosque (cada bioma se rellena antes de anadir el siguiente: el puntero no sobrevive a otro Add).
		ForestId = Set->AddBiome(FName(TEXT("Forest")));
		if (FFramework2DBiome* Forest = Set->FindBiomeByIdMutable(ForestId))
		{
			Fill3x3(Forest->Ground, 0, 0);
			Forest->InnerCorners.TopLeft = TileAt(0, 3);
			Forest->InnerCorners.TopRight = TileAt(0, 4);
			Forest->InnerCorners.BottomLeft = TileAt(1, 3);
			Forest->InnerCorners.BottomRight = TileAt(1, 4);
			Forest->CenterVariants = { TileAt(2, 3), TileAt(2, 4), TileAt(0, 14), TileAt(0, 15) };
			Forest->RampUp = TileAt(0, 8);
			Forest->RampDown = TileAt(0, 9);
			Forest->GentleUpLow = TileAt(0, 10);
			Forest->GentleUpHigh = TileAt(0, 11);
			Forest->GentleDownHigh = TileAt(0, 12);
			Forest->GentleDownLow = TileAt(0, 13);
			Forest->PlatformLeft = TileAt(1, 8);
			Forest->PlatformMiddle = TileAt(1, 9);
			Forest->PlatformRight = TileAt(1, 10);
			Fill3x3(Forest->Background, 0, 5);
			SetWater(*Forest);
			AddDecoration(*Forest, GrassGenerator, 5.0f, Ground);
			AddDecoration(*Forest, RockGenerator, 1.5f, Ground);
			AddDecoration(*Forest, BushGenerator, 1.2f, Ground);
			AddDecoration(*Forest, TorchFlipbook, 0.25f, Ground);
			AddDecoration(*Forest, FlowerFlipbook, 0.6f, Ground);
			AddDecoration(*Forest, TileAt(4, 11), 0.12f, Ground);  // cartel
			AddDecoration(*Forest, TileAt(4, 12), 0.15f, Ground);  // caja
			AddDecoration(*Forest, TileAt(5, 4), 1.0f, Ceiling);   // liana A
			AddDecoration(*Forest, TileAt(5, 5), 1.0f, Ceiling);   // liana B
			AddDecoration(*Forest, TileAt(5, 6), 0.8f, Ceiling);   // raices
		}

		// Cueva: sus piezas de piedra (sin rampas suaves) y la misma agua.
		const int32 CaveId = Set->AddBiome(FName(TEXT("Cave")));
		if (FFramework2DBiome* Cave = Set->FindBiomeByIdMutable(CaveId))
		{
			Fill3x3(Cave->Ground, 7, 0);
			Cave->InnerCorners.TopLeft = TileAt(7, 3);
			Cave->InnerCorners.TopRight = TileAt(7, 4);
			Cave->InnerCorners.BottomLeft = TileAt(8, 3);
			Cave->InnerCorners.BottomRight = TileAt(8, 4);
			Cave->CenterVariants = { TileAt(9, 3), TileAt(9, 4) };
			Cave->RampUp = TileAt(7, 8);
			Cave->RampDown = TileAt(7, 9);
			Cave->PlatformLeft = TileAt(8, 8);
			Cave->PlatformMiddle = TileAt(8, 9);
			Cave->PlatformRight = TileAt(8, 10);
			Fill3x3(Cave->Background, 7, 5);
			SetWater(*Cave);
			AddDecoration(*Cave, CaveGenerator, 4.0f, Ground);
			AddDecoration(*Cave, CrystalFlipbook, 0.7f, Ground);
			AddDecoration(*Cave, TileAt(4, 13), 0.2f, Ground);    // huesos
			AddDecoration(*Cave, TileAt(4, 9), 0.3f, Ground);     // seta roja
			AddDecoration(*Cave, TileAt(5, 7), 1.5f, Ceiling);    // estalactita
			AddDecoration(*Cave, TileAt(5, 6), 0.5f, Ceiling);    // raices
		}

		//---- 5) Bosque queda activo en la receta del mapa ----
		if (Map)
		{
			Map->SetFlags(RF_Transactional);
			Map->Modify();
			Map->ProcGen.BiomeId = ForestId;
		}
	}

	// Los materiales cambian como se hornean los tiles: se rehacen los terrenos que usan el tileset.
	Framework2DModeGenRebuild(*this, Set, Map);
	return ForestId;
}

//---------------------- Receta y generar ----------------------

const FFramework2DProcGenSettings* FFramework2DTilePaintMode::GetProcGenSettings() const
{
	const UFramework2DTileMapAsset* Map = GetTileMap();
	return Map ? &Map->ProcGen : nullptr;
}

void FFramework2DTilePaintMode::ChangeProcGenSettings(const FText& Description, TFunctionRef<void(FFramework2DProcGenSettings&)> Change)
{
	UFramework2DTileMapAsset* Map = GetTileMap();
	if (!Map) { return; }

	// Se prueba en una copia: si no cambia nada, ni paso de deshacer ni regenerar.
	FFramework2DProcGenSettings Edited = Map->ProcGen;
	Change(Edited);
	Framework2DModeGenClampSettings(Edited, Map->ProcGen);
	const UScriptStruct* Struct = FFramework2DProcGenSettings::StaticStruct();
	if (Struct->CompareScriptStruct(&Map->ProcGen, &Edited, PPF_None)) { return; }

	// Cambiar solo los nombres de las capas no regenera: crearia capas nuevas con esos nombres y
	// dejaria las de antes con el nivel viejo encima.
	FFramework2DProcGenSettings SameLayers = Edited;
	SameLayers.TerrainLayer = Map->ProcGen.TerrainLayer;
	SameLayers.BackgroundLayer = Map->ProcGen.BackgroundLayer;
	SameLayers.WaterLayer = Map->ProcGen.WaterLayer;
	SameLayers.DecorationLayer = Map->ProcGen.DecorationLayer;
	const bool bOnlyLayerNames = Struct->CompareScriptStruct(&Map->ProcGen, &SameLayers, PPF_None);

	bool bGenerated = false;
	{
		const FScopedTransaction Transaction(Description);
		Map->SetFlags(RF_Transactional);
		Map->Modify();
		Map->ProcGen = Edited;
		if (bAutoGenerate && !bOnlyLayerNames) { bGenerated = Framework2DModeGenAuto(*this, Map); }
	}
	if (bGenerated) { Framework2DModeGenRebuild(*this, Map); }
}

void FFramework2DTilePaintMode::ResizeMap(int32 NewWidth, int32 NewHeight)
{
	UFramework2DTileMapAsset* Map = GetTileMap();
	if (!Map) { return; }
	const int32 W = FMath::Clamp(NewWidth, 1, 1024);
	const int32 H = FMath::Clamp(NewHeight, 1, 1024);
	if (W == Map->Width && H == Map->Height) { return; }
	if (bStrokeActive) { EndStroke(); } // un trazo a medias no se mezcla con este paso

	{
		const FScopedTransaction Transaction(LOCTEXT("GenResizeMap", "Change map size"));
		Map->SetFlags(RF_Transactional);
		Map->Modify();
		Map->Resize(W, H);
		if (bAutoGenerate) { Framework2DModeGenAuto(*this, Map); }
	}
	HoverTx = HoverTy = -1; // el raton se vuelve a buscar en el mapa nuevo
	Framework2DModeGenRebuild(*this, Map);
}

bool FFramework2DTilePaintMode::GenerateMap(bool bNewSeed)
{
	if (bStrokeActive) { EndStroke(); } // un trazo a medias no se mezcla con este paso

	UFramework2DTileMapAsset* Map = GetTileMap();
	const FText Problem = GetGenerateProblem();
	if (!Map || !Problem.IsEmpty())
	{
		Framework2DModeGenSetProblem(*this, Problem);
		return false;
	}

	bool bGenerated = false;
	{
		// Un solo paso de deshacer: la semilla nueva (si la hay) y el mapa generado.
		FScopedTransaction Transaction(LOCTEXT("GenerateMap", "Generate map"));
		Map->SetFlags(RF_Transactional);
		Map->Modify();
		const int32 OldSeed = Map->ProcGen.Seed;
		if (bNewSeed) { Map->ProcGen.Seed = Framework2DModeGenNewSeed(OldSeed); }
		bGenerated = Framework2DModeGenRun(*this, Map);
		if (!bGenerated)
		{
			// No deberia pasar (GetGenerateProblem lo mira antes). Si pasa, la receta vuelve a
			// estar como antes y no queda un paso de deshacer vacio.
			Map->ProcGen.Seed = OldSeed;
			Transaction.Cancel();
		}
	}
	if (bGenerated) { Framework2DModeGenRebuild(*this, Map); }
	return bGenerated;
}

FText FFramework2DTilePaintMode::GetGenerateProblem() const
{
	const AFramework2DTerrainWorld* Target = GetTarget();
	if (!Target) { return LOCTEXT("GenNoTerrain", "Place a «Framework2D Terrain» in the level (Place Actors)."); }
	const UFramework2DTileMapAsset* Map = Target->TileMap.Get();
	if (!Map) { return LOCTEXT("GenNoMap", "Assign a Tile Map to the terrain (Details panel)."); }
	const UFramework2DTileSet* Set = Map->TileSet.Get();
	if (!Set) { return LOCTEXT("GenNoSet", "Assign a Tile Set to the Tile Map."); }
	const FFramework2DBiome* Biome = Set->ResolveBiome(Map->ProcGen.BiomeId);
	if (!Biome) { return LOCTEXT("GenNoBiome", "Create a biome (or the example biome) and choose at least the center of its 3×3 terrain."); }
	const FText BiomeProblem = UFramework2DProcGenLibrary::GetBiomeProblem(Set, *Biome);
	if (!BiomeProblem.IsEmpty()) { return BiomeProblem; }
	if (Map->Width < 4 || Map->Height < 4)
	{
		return FText::Format(LOCTEXT("GenMapTooSmall", "The map is {0}×{1} tiles: generating needs at least 4×4."), Map->Width, Map->Height);
	}
	return FText::GetEmpty();
}

// =====================================================================
//  Pincel de colision
// =====================================================================
void FFramework2DTilePaintMode::SetCollisionBrush(EFramework2DCollisionShape Shape)
{
	CollisionBrush = Shape;
	Tool = EFramework2DTileTool::Collision;
}

// =====================================================================
//  Dibujado en el viewport
// =====================================================================
void FFramework2DTilePaintMode::Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI)
{
	FEdMode::Render(View, Viewport, PDI);

	// En la pasada de seleccion no se dibuja nada: asi las lineas no tapan los clics a otros actores.
	if (!PDI || PDI->IsHitTesting()) { return; }

	AFramework2DTerrainWorld* Target = GetTarget();
	UFramework2DTileMapAsset* Map = Target ? Target->TileMap.Get() : nullptr;
	if (!Map || Target->TileSize <= 0.0f) { return; }

	const FTransform Xf = Target->GetActorTransform();
	const float TS = Target->TileSize;
	const int32 MW = Map->Width;
	const int32 MH = Map->Height;
	const int32 Layer = FMath::Clamp(ActiveLayer, 0, FMath::Max(0, Map->GetNumLayers() - 1));
	const float LayerY = Target->GetLayerDepth(Layer); // todo lo del cursor va en el plano de la capa activa

	// 1) Colision (detras de todo lo demas).
	if (bShowCollision || Tool == EFramework2DTileTool::Collision)
	{
		DrawCollisionOverlay(PDI, Target);
	}

	// 2) Rejilla (si no es enorme), un pelo hacia la camara.
	if (bShowGrid && MW + MH <= 2048)
	{
		const FLinearColor GridColor(0.25f, 0.25f, 0.3f, 0.6f);
		const float GY = LayerY + 0.5f;
		for (int32 X = 1; X < MW; ++X)
		{
			PDI->DrawLine(Xf.TransformPosition(FVector(X * TS, GY, 0.0f)), Xf.TransformPosition(FVector(X * TS, GY, MH * TS)), GridColor, SDPG_Foreground);
		}
		for (int32 Y = 1; Y < MH; ++Y)
		{
			PDI->DrawLine(Xf.TransformPosition(FVector(0.0f, GY, Y * TS)), Xf.TransformPosition(FVector(MW * TS, GY, Y * TS)), GridColor, SDPG_Foreground);
		}
	}

	// 3) Borde del mapa.
	Framework2DDrawTileRect(PDI, Xf, TS, MH, LayerY + 1.0f, 0, 0, MW - 1, MH - 1, FLinearColor(0.1f, 0.8f, 1.0f), 2.0f);

	// 3b) Casillas generador de la capa activa (lo que generan ya se ve; la casilla, no).
	if (Map->Layers.IsValidIndex(Layer))
	{
		const TArray<int32>& Cells = Map->Layers[Layer].Tiles;
		const FLinearColor GeneratorColor(0.25f, 0.95f, 0.85f, 0.9f);
		int32 Marked = 0;
		for (int32 I = 0; I < Cells.Num() && I < MW * MH && Marked < Framework2DModeMaxGhostTiles; ++I)
		{
			if (!Framework2D::IsGeneratorValue(Cells[I])) { continue; }
			const int32 Tx = I % MW;
			const int32 Ty = I / MW;
			// Un rombo pequeno en el centro: distinto del contorno del cursor.
			const float Cx = (Tx + 0.5f) * TS;
			const float Cz = (MH - Ty - 0.5f) * TS;
			const float R = TS * 0.18f;
			const FVector P[4] = {
				Xf.TransformPosition(FVector(Cx - R, LayerY + 1.2f, Cz)), Xf.TransformPosition(FVector(Cx, LayerY + 1.2f, Cz + R)),
				Xf.TransformPosition(FVector(Cx + R, LayerY + 1.2f, Cz)), Xf.TransformPosition(FVector(Cx, LayerY + 1.2f, Cz - R)) };
			for (int32 k = 0; k < 4; ++k) { PDI->DrawLine(P[k], P[(k + 1) % 4], GeneratorColor, SDPG_Foreground, 1.5f); }
			++Marked;
		}
	}

	// 4) Contorno del cursor. La vista previa semitransparente se pinta en DrawHUD.
	FLinearColor CursorColor(1.0f, 0.85f, 0.1f);
	if (Tool == EFramework2DTileTool::Erase) { CursorColor = FLinearColor(1.0f, 0.25f, 0.2f); }
	else if (Tool == EFramework2DTileTool::Pick) { CursorColor = FLinearColor(0.3f, 1.0f, 1.0f); }
	else if (Tool == EFramework2DTileTool::Fill) { CursorColor = FLinearColor(0.4f, 1.0f, 0.4f); }
	else if (Tool == EFramework2DTileTool::Collision) { CursorColor = FLinearColor(0.3f, 1.0f, 0.55f); }
	const float CursorY = LayerY + 2.0f;

	if (bStrokeActive && Tool == EFramework2DTileTool::Rect)
	{
		Framework2DDrawTileRect(PDI, Xf, TS, MH, CursorY, FMath::Min(RectStart.X, LastTile.X), FMath::Min(RectStart.Y, LastTile.Y),
			FMath::Max(RectStart.X, LastTile.X), FMath::Max(RectStart.Y, LastTile.Y), CursorColor, 2.0f);
	}
	else if (HoverTx >= 0 && HoverTy >= 0 && HoverTx < MW && HoverTy < MH)
	{
		// La huella es la misma que la del fantasma: el bloque del pincel, salvo cuentagotas y colision.
		const bool bBlock = Tool == EFramework2DTileTool::Paint || Tool == EFramework2DTileTool::Erase ||
			Tool == EFramework2DTileTool::Fill || Tool == EFramework2DTileTool::Rect;
		const int32 Ex = bBlock ? FMath::Min(MW - 1, HoverTx + BrushWidth() - 1) : HoverTx;
		const int32 Ey = bBlock ? FMath::Min(MH - 1, HoverTy + BrushHeight() - 1) : HoverTy;
		Framework2DDrawTileRect(PDI, Xf, TS, MH, CursorY, HoverTx, HoverTy, Ex, Ey, CursorColor, 2.0f);
	}
}

void FFramework2DTilePaintMode::DrawGhost(const FSceneView* View, FCanvas* Canvas, AFramework2DTerrainWorld* Target)
{
	UFramework2DTileMapAsset* Map = Target ? Target->TileMap.Get() : nullptr;
	UFramework2DTileSet* Set = Map ? Map->TileSet.Get() : nullptr;
	if (!Map || !Set || !View || !Canvas || Tool == EFramework2DTileTool::Pick) { return; } // cuentagotas: solo contorno

	const int32 MW = Map->Width;
	const int32 MH = Map->Height;
	const bool bRectDrag = bStrokeActive && Tool == EFramework2DTileTool::Rect;
	const bool bHoverValid = HoverTx >= 0 && HoverTy >= 0 && HoverTx < MW && HoverTy < MH;
	if (!bRectDrag && !bHoverValid) { return; }

	const FTransform Xf = Target->GetActorTransform();
	const float TS = Target->TileSize;
	const int32 Layer = FMath::Clamp(ActiveLayer, 0, FMath::Max(0, Map->GetNumLayers() - 1));
	const float Y = Target->GetLayerDepth(Layer) + 1.5f;

	// --- Borrador: relleno rojo sobre la huella ---
	if (Tool == EFramework2DTileTool::Erase)
	{
		const int32 Ex = FMath::Min(MW - 1, HoverTx + BrushWidth() - 1);
		const int32 Ey = FMath::Min(MH - 1, HoverTy + BrushHeight() - 1);
		TArray<FFramework2DModeQuad> Quads;
		Framework2DModeAddQuad(Quads, HoverTx * TS, (Ex + 1) * TS, (MH - 1 - Ey) * TS, (MH - HoverTy) * TS, Y,
			FVector2f(0.0f, 0.0f), FVector2f(1.0f, 1.0f), FColor(255, 64, 56, 90));
		Framework2DModeDrawQuads(Canvas, View, Xf, Quads, GWhiteTexture);
		return;
	}

	// --- Colision: la forma del pincel en el tile bajo el raton ---
	if (Tool == EFramework2DTileTool::Collision)
	{
		if (!bHoverValid) { return; }
		const float L = HoverTx * TS;
		const float T = (MH - HoverTy) * TS;
		TArray<FFramework2DModeQuad> Quads;
		if (Framework2D::IsCustomShape(CollisionBrush))
		{
			// Rasterizada a la resolucion real (pixeles por tile), como la hornea el terreno.
			const int32 Size = FMath::Max(1, Target->GetCellsPerTile());
			const float Cell = TS / Size;
			TArray<FIntRect> Runs;
			Framework2DModeShapeRuns(CollisionBrush, Size, Runs);
			for (const FIntRect& Run : Runs)
			{
				Framework2DModeAddQuad(Quads, L + Run.Min.X * Cell, L + (Run.Max.X + 1) * Cell, T - (Run.Max.Y + 1) * Cell, T - Run.Min.Y * Cell, Y,
					FVector2f(0.0f, 0.0f), FVector2f(1.0f, 1.0f), FColor(70, 235, 120, 120));
			}
		}
		else
		{
			// Formas que dependen del dibujo: el tile entero tintado.
			FColor Tint(170, 170, 180, 80);                                                                 // Auto: quitar
			if (CollisionBrush == EFramework2DCollisionShape::None) { Tint = FColor(255, 70, 60, 100); }     // nada choca
			else if (CollisionBrush == EFramework2DCollisionShape::Pixels) { Tint = FColor(170, 255, 185, 90); } // el dibujo
			Framework2DModeAddQuad(Quads, L, L + TS, T - TS, T, Y, FVector2f(0.0f, 0.0f), FVector2f(1.0f, 1.0f), Tint);
		}
		Framework2DModeDrawQuads(Canvas, View, Xf, Quads, GWhiteTexture);
		return;
	}

	// --- Generador: su primer sprite, dentro de la casilla (lo que siembra sale al pintar) ---
	if (IsGeneratorBrush() && Tool != EFramework2DTileTool::Rect && Tool != EFramework2DTileTool::Fill)
	{
		if (!bHoverValid) { return; }
		const FFramework2DGenerator* Generator = Set->FindGeneratorByValue(Framework2D::MakeGeneratorValue(BrushGeneratorId));
		const float L = HoverTx * TS;
		const float T = (MH - HoverTy) * TS;
		TArray<FFramework2DModeQuad> Tint;
		Framework2DModeAddQuad(Tint, L, L + TS, T - TS, T, Y, FVector2f(0.0f, 0.0f), FVector2f(1.0f, 1.0f), FColor(70, 230, 200, 60));
		Framework2DModeDrawQuads(Canvas, View, Xf, Tint, GWhiteTexture);
		if (Generator && Generator->Sprites.Num() > 0)
		{
			const FFramework2DScatterSprite& First = Generator->Sprites[0];
			int32 PageId = 0, Px = 0, Py = 0, PW = 0, PH = 0;
			const bool bHasOrigin = Set->GetTileValueOrigin(First.Tile, PageId, Px, Py) && Set->GetPageSize(PageId, PW, PH);
			UTexture2D* PageTexture = bHasOrigin ? Set->GetPageTexture(PageId) : nullptr;
			if (PageTexture && PageTexture->GetResource())
			{
				// El sprite entero (sus tiles) encogido para caber en la casilla, apoyado abajo.
				const int32 SW = FMath::Clamp(First.WidthInTiles, 1, 16);
				const int32 SH = FMath::Clamp(First.HeightInTiles, 1, 16);
				const float Fit = 1.0f / (float)FMath::Max(SW, SH);
				const float QW = TS * SW * Fit;
				const float QH = TS * SH * Fit;
				const float QL = L + (TS - QW) * 0.5f;
				const FVector2f UV0(Px / (float)PW, Py / (float)PH);
				const FVector2f UV1(FMath::Min(PW, Px + SW * Set->TileWidth) / (float)PW, FMath::Min(PH, Py + SH * Set->TileHeight) / (float)PH);
				TArray<FFramework2DModeQuad> Sprite;
				Framework2DModeAddQuad(Sprite, QL, QL + QW, T - TS, T - TS + QH, Y, UV0, UV1, FColor(255, 255, 255, 170));
				Framework2DModeDrawQuads(Canvas, View, Xf, Sprite, PageTexture->GetResource());
			}
		}
		return;
	}

	// --- Pincel / Rectangulo / Cubo: el patron con los sprites reales del atlas (de cualquier pagina) ---
	const FFramework2DModeBrushPattern Pattern = Framework2DModeMakePattern(*this);
	FIntRect Area;
	FIntPoint Anchor;
	if (bRectDrag)
	{
		// Rectangulo arrastrando: el patron en todo el rectangulo, anclado en su esquina (como al soltar).
		Area = FIntRect(FMath::Min(RectStart.X, LastTile.X), FMath::Min(RectStart.Y, LastTile.Y),
			FMath::Max(RectStart.X, LastTile.X), FMath::Max(RectStart.Y, LastTile.Y));
		Anchor = Area.Min;
		const int64 Count = (int64)(Area.Max.X - Area.Min.X + 1) * (int64)(Area.Max.Y - Area.Min.Y + 1);
		if (Count > Framework2DModeMaxGhostTiles) { return; } // demasiado grande: solo el contorno
	}
	else
	{
		Area = FIntRect(HoverTx, HoverTy, FMath::Min(MW - 1, HoverTx + BrushWidth() - 1), FMath::Min(MH - 1, HoverTy + BrushHeight() - 1));
		// Durante un trazo del pincel, el patron sigue anclado donde empezo (como se pinta).
		Anchor = (bStrokeActive && Tool == EFramework2DTileTool::Paint) ? StrokeOrigin : FIntPoint(HoverTx, HoverTy);
	}

	const double Now = FPlatformTime::Seconds(); // los flipbooks se ven animados
	const int32 TileW = FMath::Max(1, Set->TileWidth);
	const int32 TileH = FMath::Max(1, Set->TileHeight);
	const FColor GhostColor(255, 255, 255, 150);

	// Un lote de quads por pagina (cada una es su propia textura).
	TMap<int32, TArray<FFramework2DModeQuad>> QuadsByPage;
	for (int32 Ty = Area.Min.Y; Ty <= Area.Max.Y; ++Ty)
	{
		for (int32 Tx = Area.Min.X; Tx <= Area.Max.X; ++Tx)
		{
			const int32 Value = Pattern.At(Tx - Anchor.X, Ty - Anchor.Y);
			if (Framework2D::IsGeneratorValue(Value))
			{
				// Rectangulo o cubo con un generador: la casilla tintada.
				Framework2DModeAddQuad(QuadsByPage.FindOrAdd(INDEX_NONE), Tx * TS, (Tx + 1) * TS, (MH - 1 - Ty) * TS, (MH - Ty) * TS, Y,
					FVector2f(0.0f, 0.0f), FVector2f(1.0f, 1.0f), FColor(70, 230, 200, 70));
				continue;
			}
			const int32 AtlasTile = Set->GetFrameTile(Value, Now);
			int32 PageId = 0, Px = 0, Py = 0, PW = 0, PH = 0;
			if (AtlasTile < 0 || !Set->GetTileValueOrigin(AtlasTile, PageId, Px, Py) || !Set->GetPageSize(PageId, PW, PH)) { continue; }
			const FVector2f UV0(Px / (float)PW, Py / (float)PH);
			const FVector2f UV1((Px + TileW) / (float)PW, (Py + TileH) / (float)PH);
			Framework2DModeAddQuad(QuadsByPage.FindOrAdd(PageId), Tx * TS, (Tx + 1) * TS, (MH - 1 - Ty) * TS, (MH - Ty) * TS, Y, UV0, UV1, GhostColor);
		}
	}
	for (const TPair<int32, TArray<FFramework2DModeQuad>>& Batch : QuadsByPage)
	{
		if (Batch.Key == INDEX_NONE)
		{
			Framework2DModeDrawQuads(Canvas, View, Xf, Batch.Value, GWhiteTexture);
			continue;
		}
		UTexture2D* PageTexture = Set->GetPageTexture(Batch.Key);
		if (PageTexture && PageTexture->GetResource()) { Framework2DModeDrawQuads(Canvas, View, Xf, Batch.Value, PageTexture->GetResource()); }
	}
}

void FFramework2DTilePaintMode::RefreshCollisionCache(AFramework2DTerrainWorld* Target)
{
	// Los rectangulos solo se recalculan cuando cambia el contenido del terreno.
	const uint32 Revision = Target->GetContentRevision();
	if (CachedCollisionTarget.Get() != Target || CachedCollisionRevision != Revision)
	{
		CachedCollisionRects.Reset();
		Target->GetCollisionCellRects(CachedCollisionRects);
		CachedCollisionRevision = Revision;
		CachedCollisionTarget = Target;
	}
}

float FFramework2DTilePaintMode::GetCollisionOverlayDepth(const AFramework2DTerrainWorld* Target) const
{
	// La colision vive en el plano de la capa base (el del actor), un pelo hacia la camara.
	const int32 BaseLayer = Target->GetBaseLayer();
	return (BaseLayer >= 0 ? Target->GetLayerDepth(BaseLayer) : 0.0f) + 2.0f;
}

void FFramework2DTilePaintMode::DrawCollisionFill(const FSceneView* View, FCanvas* Canvas, AFramework2DTerrainWorld* Target)
{
	if (!Target || !View || !Canvas) { return; }
	RefreshCollisionCache(Target);
	const float Cell = Target->GetCellSize();
	const int32 GH = Target->GridHeight;
	if (Cell <= 0.0f || GH <= 0 || CachedCollisionRects.Num() == 0 || CachedCollisionRects.Num() > Framework2DModeMaxCollisionRects) { return; }

	const float Y = GetCollisionOverlayDepth(Target);
	TArray<FFramework2DModeQuad> Quads;
	Quads.Reserve(CachedCollisionRects.Num());
	for (const FIntRect& R : CachedCollisionRects)
	{
		Framework2DModeAddQuad(Quads, R.Min.X * Cell, (R.Max.X + 1) * Cell, (GH - 1 - R.Max.Y) * Cell, (GH - R.Min.Y) * Cell, Y,
			FVector2f(0.0f, 0.0f), FVector2f(1.0f, 1.0f), FColor(60, 220, 110, 70));
	}
	Framework2DModeDrawQuads(Canvas, View, Target->GetActorTransform(), Quads, GWhiteTexture);
}

void FFramework2DTilePaintMode::DrawCollisionOverlay(FPrimitiveDrawInterface* PDI, AFramework2DTerrainWorld* Target)
{
	if (!Target || !PDI) { return; }
	RefreshCollisionCache(Target);

	const FTransform Xf = Target->GetActorTransform();
	const float Cell = Target->GetCellSize();
	const int32 GH = Target->GridHeight;
	const float Y = GetCollisionOverlayDepth(Target);

	if (Cell > 0.0f && GH > 0 && CachedCollisionRects.Num() > 0)
	{
		// Contornos (el relleno va en el HUD). Con demasiados rectangulos no se dibujan todos.
		const int32 Count = FMath::Min(CachedCollisionRects.Num(), Framework2DModeMaxCollisionRects);
		const FLinearColor LineColor(0.2f, 0.95f, 0.45f, 1.0f);
		for (int32 i = 0; i < Count; ++i)
		{
			const FIntRect& R = CachedCollisionRects[i];
			const float L = R.Min.X * Cell;
			const float Rt = (R.Max.X + 1) * Cell;
			const float T = (GH - R.Min.Y) * Cell;
			const float B = (GH - 1 - R.Max.Y) * Cell;
			Framework2DModeDrawLocalRect(PDI, Xf, L, Rt, B, T, Y + 0.1f, LineColor, 0.0f);
		}
	}

	// Tiles con colision pintada a mano: contorno naranja fino.
	UFramework2DTileMapAsset* Map = Target->TileMap.Get();
	if (Map && Map->HasCollisionOverrides() && Target->TileSize > 0.0f)
	{
		const FLinearColor Orange(1.0f, 0.55f, 0.1f, 1.0f);
		int32 Drawn = 0;
		for (int32 Ty = 0; Ty < Map->Height && Drawn < Framework2DModeMaxCollisionRects; ++Ty)
		{
			for (int32 Tx = 0; Tx < Map->Width && Drawn < Framework2DModeMaxCollisionRects; ++Tx)
			{
				if (Map->GetCollisionOverride(Tx, Ty) == EFramework2DCollisionShape::Auto) { continue; }
				Framework2DDrawTileRect(PDI, Xf, Target->TileSize, Map->Height, Y + 0.5f, Tx, Ty, Tx, Ty, Orange, 1.0f);
				++Drawn;
			}
		}
	}
}

// =====================================================================
//  HUD: pastilla abajo a la izquierda
// =====================================================================
void FFramework2DTilePaintMode::DrawHUD(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas)
{
	FEdMode::DrawHUD(ViewportClient, Viewport, View, Canvas);
	if (!Canvas || !Viewport || !GEngine) { return; }

	// En la pasada de seleccion no se dibuja nada: taparia los clics a los actores de debajo.
	if (Canvas->IsHitTesting()) { return; }

	// Superposiciones semitransparentes (debajo de la pastilla de texto).
	if (AFramework2DTerrainWorld* OverlayTarget = GetTarget())
	{
		if (OverlayTarget->TileMap && (bShowCollision || Tool == EFramework2DTileTool::Collision)) { DrawCollisionFill(View, Canvas, OverlayTarget); }
		if (OverlayTarget->TileMap && bShowGhost) { DrawGhost(View, Canvas, OverlayTarget); }
	}
	UFont* Font = GEngine->GetSmallFont();
	if (!Font) { return; }

	// Tres trozos: herramienta (acento), estado (blanco) y ayuda (gris).
	FText Lead, Body, Hint;
	AFramework2DTerrainWorld* Target = GetTarget();
	UFramework2DTileMapAsset* Map = Target ? Target->TileMap.Get() : nullptr;
	UFramework2DTileSet* Set = Map ? Map->TileSet.Get() : nullptr;
	if (!Target || !Map || !Set)
	{
		Lead = LOCTEXT("HudTitle", "Framework2D Tiles");
		if (!Target) { Body = LOCTEXT("HudNoTerrain", "Place a 'Framework2D Terrain' in the level (Place Actors)."); }
		else if (!Map) { Body = LOCTEXT("HudNoMap", "Assign a Tile Map to the terrain (Details panel)."); }
		else { Body = LOCTEXT("HudNoSet", "Assign a Tile Set to the Tile Map."); }
	}
	else
	{
		Lead = GetToolName(Tool);
		TArray<FText> Parts;

		// Que se pinta.
		if (Tool == EFramework2DTileTool::Collision)
		{
			Parts.Add(FText::Format(LOCTEXT("HudShape", "Shape: {0}"), GetShapeName(CollisionBrush)));
			Parts.Add(LOCTEXT("HudAllLayers", "All layers"));
		}
		else
		{
			if (Tool != EFramework2DTileTool::Pick)
			{
				const FFramework2DFlipbook* Flipbook = IsFlipbookBrush() ? Set->FindFlipbookByValue(Framework2D::MakeFlipbookValue(BrushFlipbookId)) : nullptr;
				const FFramework2DGenerator* Generator = IsGeneratorBrush() ? Set->FindGeneratorByValue(Framework2D::MakeGeneratorValue(BrushGeneratorId)) : nullptr;
				if (Tool == EFramework2DTileTool::Erase)
				{
					Parts.Add(FText::Format(LOCTEXT("HudFootprint", "Footprint {0}×{1}"), BrushWidth(), BrushHeight()));
				}
				else if (Generator)
				{
					Parts.Add(FText::Format(LOCTEXT("HudGenerator", "Generator: {0} ({1} sprites)"), FText::FromName(Generator->Name), Generator->Sprites.Num()));
				}
				else if (Flipbook)
				{
					Parts.Add(FText::Format(LOCTEXT("HudFlipbook", "Flipbook: {0} ({1} frames)"), FText::FromName(Flipbook->Name), Flipbook->Frames.Num()));
				}
				else if (BrushWidth() * BrushHeight() > 1)
				{
					Parts.Add(FText::Format(LOCTEXT("HudBlock", "Block {0}×{1}"), BrushWidth(), BrushHeight()));
				}
				else
				{
					const FName Material = Set->GetTileMaterial(SelectedTile);
					const FText MaterialText = Material.IsNone() ? LOCTEXT("HudNoMaterial", "no material") : FText::FromName(Material);
					const int32 Page = Framework2D::TilePageOf(SelectedTile);
					if (Page == 0)
					{
						Parts.Add(FText::Format(LOCTEXT("HudTile", "Tile {0} ({1})"), FText::AsNumber(Framework2D::TileLocalOf(SelectedTile)), MaterialText));
					}
					else
					{
						Parts.Add(FText::Format(LOCTEXT("HudPageTile", "{0}: tile {1} ({2})"), Set->GetPageDisplayName(Page), FText::AsNumber(Framework2D::TileLocalOf(SelectedTile)), MaterialText));
					}
				}
			}

			// En que capa.
			if (Map->Layers.IsValidIndex(ActiveLayer))
			{
				const FFramework2DTileLayer& L = Map->Layers[ActiveLayer];
				FText Suffix = FText::GetEmpty();
				if (!L.bVisible) { Suffix = LOCTEXT("HudHidden", " (hidden)"); }
				else if (L.bBackground) { Suffix = LOCTEXT("HudBackground", " (background)"); }
				Parts.Add(FText::Format(LOCTEXT("HudLayer", "Layer: {0}{1}"), FText::FromName(L.Name), Suffix));
			}
		}
		Body = FText::Join(FText::FromString(TEXT("  ·  ")), Parts);

		switch (Tool)
		{
		case EFramework2DTileTool::Paint:     Hint = LOCTEXT("HintPaint", "Click or drag to paint · Ctrl+Z undoes"); break;
		case EFramework2DTileTool::Erase:     Hint = LOCTEXT("HintErase", "Click or drag to erase · Ctrl+Z undoes"); break;
		case EFramework2DTileTool::Fill:      Hint = LOCTEXT("HintFill", "Click to fill the area · Ctrl+Z undoes"); break;
		case EFramework2DTileTool::Rect:      Hint = LOCTEXT("HintRect", "Drag to draw the rectangle · Ctrl+Z undoes"); break;
		case EFramework2DTileTool::Pick:      Hint = LOCTEXT("HintPick", "Click to copy a tile or flipbook"); break;
		case EFramework2DTileTool::Collision: Hint = LOCTEXT("HintCollision", "Click or drag to paint collision · Ctrl+Z undoes"); break;
		}
	}

	struct FHudSegment
	{
		FText Text;
		FLinearColor Color;
		int32 Width = 0;
	};
	TArray<FHudSegment, TInlineAllocator<3>> Segments;
	auto AddSegment = [&Segments](const FText& Text, const FLinearColor& Color)
	{
		FHudSegment Seg;
		Seg.Text = Text;
		Seg.Color = Color;
		Segments.Add(Seg);
	};
	AddSegment(Lead, FFramework2DEditorStyle::Accent());
	if (!Body.IsEmpty()) { AddSegment(Body, FLinearColor(0.94f, 0.94f, 0.94f, 1.0f)); }
	if (!Hint.IsEmpty()) { AddSegment(Hint, FLinearColor(0.62f, 0.62f, 0.64f, 1.0f)); }

	int32 TextH = 0;
	for (FHudSegment& Seg : Segments)
	{
		int32 W = 0, H = 0;
		StringSize(Font, W, H, *Seg.Text.ToString());
		Seg.Width = W;
		TextH = FMath::Max(TextH, H);
	}

	// Todo en unidades logicas: el lienzo ya multiplica por el DPI al dibujar.
	const float DPIScale = FMath::Max(0.1f, Canvas->GetDPIScale());
	const FIntPoint ViewSize = Viewport->GetSizeXY();
	const float ViewW = ViewSize.X / DPIScale;
	const float ViewH = ViewSize.Y / DPIScale;

	const float PadY = 6.0f;
	const float PillH = TextH + 2.0f * PadY;
	const float PadX = FMath::Max(12.0f, PillH * 0.5f);
	const float Gap = 10.0f;                 // a cada lado del separador
	const float MarginLeft = 92.0f;               // deja libre el indicador de ejes de la esquina
	const float MarginBottom = 16.0f;

	auto ContentWidth = [&Segments, Gap]()
	{
		float W = 0.0f;
		for (int32 i = 0; i < Segments.Num(); ++i) { W += Segments[i].Width + (i > 0 ? 2.0f * Gap + 1.0f : 0.0f); }
		return W;
	};
	// En un viewport estrecho sobra antes la ayuda que el estado.
	if (Segments.Num() > 2 && MarginLeft + ContentWidth() + 2.0f * PadX > ViewW - 8.0f) { Segments.RemoveAt(Segments.Num() - 1); }

	const float PillW = ContentWidth() + 2.0f * PadX;
	const float X0 = (MarginLeft + PillW > ViewW - 8.0f) ? 8.0f : MarginLeft;
	const float Y0 = ViewH - MarginBottom - PillH;
	if (Y0 < 0.0f) { return; }

	Framework2DModeDrawPill(Canvas, X0, Y0, PillW, PillH, DPIScale, FLinearColor(0.015f, 0.015f, 0.02f, 0.78f));

	float X = X0 + PadX;
	for (int32 i = 0; i < Segments.Num(); ++i)
	{
		if (i > 0)
		{
			// Separador fino entre trozos.
			X += Gap;
			FCanvasTileItem Divider(FVector2D(X, Y0 + PillH * 0.25f), FVector2D(1.0f, PillH * 0.5f), FLinearColor(1.0f, 1.0f, 1.0f, 0.18f));
			Divider.BlendMode = SE_BLEND_Translucent;
			Canvas->DrawItem(Divider);
			X += 1.0f + Gap;
		}
		FCanvasTextItem Item(FVector2D(X, Y0 + PadY), Segments[i].Text, Font, Segments[i].Color);
		Canvas->DrawItem(Item);
		X += Segments[i].Width;
	}
}

#undef LOCTEXT_NAMESPACE
