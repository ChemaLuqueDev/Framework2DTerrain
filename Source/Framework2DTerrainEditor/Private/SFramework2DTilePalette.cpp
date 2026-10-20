// Copyright Chema Luque. Plugin Framework2DTerrain (modulo Editor).

#include "SFramework2DTilePalette.h"

#include "Framework2DEditorStyle.h"
#include "Framework2DPaletteWidgets.h"
#include "Framework2DTilePaintMode.h"
#include "SFramework2DProcGenPanel.h"
#include "Framework2DTerrainWorld.h"
#include "Framework2DTileMapAsset.h"
#include "Framework2DTileSet.h"

#include "Brushes/SlateRoundedBoxBrush.h"
#include "Editor.h"
#include "Misc/EngineVersionComparison.h"
#include "PropertyCustomizationHelpers.h"
#include "ThumbnailRendering/ThumbnailManager.h"
#include "Widgets/Colors/SColorBlock.h"
#include "Widgets/Colors/SColorPicker.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Layout/SWrapBox.h"
#include "Engine/Texture2D.h"
#include "HAL/PlatformTime.h"
#include "InputCoreTypes.h"
#include "Rendering/DrawElements.h"
#include "Styling/CoreStyle.h"
#include "Styling/SlateTypes.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Input/SSpinBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SUniformGridPanel.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/SLeafWidget.h"
#include "Widgets/SNullWidget.h"
#include "Widgets/SOverlay.h"
#include "Widgets/Text/SInlineEditableTextBlock.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "SFramework2DTilePalette"

// Las utilidades del panel (F2DPalette), la fila de lista y la miniatura del atlas viven en
// Framework2DPaletteWidgets.h: las comparte la pestaña «Generar» (SFramework2DProcGenPanel).

// =====================================================================
//  Dibujo de una forma de colision (mini-rejilla 8x8 con ShapeCovers)
// =====================================================================
class SFramework2DShapeGlyph : public SLeafWidget
{
public:
	SLATE_BEGIN_ARGS(SFramework2DShapeGlyph)
		: _Shape(EFramework2DCollisionShape::Auto)
		, _Size(24.0f)
	{}
		SLATE_ARGUMENT(EFramework2DCollisionShape, Shape)
		SLATE_ARGUMENT(float, Size)
		SLATE_ATTRIBUTE(bool, IsActive)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs)
	{
		Shape = InArgs._Shape;
		Size = InArgs._Size;
		IsActive = InArgs._IsActive;
	}

	virtual FVector2D ComputeDesiredSize(float) const override { return FVector2D(Size, Size); }

	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& Geo, const FSlateRect& Culling, FSlateWindowElementList& Out,
		int32 Layer, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override
	{
		const ESlateDrawEffect Effect = ShouldBeEnabled(bParentEnabled) ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect;
		const FVector2D Local = Geo.GetLocalSize();
		const float Cell = FMath::Max(1.0f, FMath::FloorToFloat(FMath::Min(Local.X, Local.Y) / 8.0f));
		const float Side = Cell * 8.0f;
		const float Ox = FMath::FloorToFloat((Local.X - Side) * 0.5f);
		const float Oy = FMath::FloorToFloat((Local.Y - Side) * 0.5f);

		// El color sale del boton: claro en reposo, oscuro sobre el ambar de la forma activa.
		const FLinearColor Tint = InWidgetStyle.GetColorAndOpacityTint();
		const FLinearColor Fg = InWidgetStyle.GetForegroundColor() * Tint;
		const bool bActive = IsActive.Get(false);
		const FLinearColor Solid = bActive ? Fg : FFramework2DEditorStyle::Collision() * Tint;
		const FLinearColor Faint = Fg.CopyWithNewOpacity(Fg.A * 0.14f);
		auto Cellbox = [&](float X, float Y, float W, float H, const FLinearColor& C)
		{
			F2DPalette::Box(Out, Layer, Geo, Effect, Ox + X, Oy + Y, W, H, C);
		};

		switch (Shape)
		{
		case EFramework2DCollisionShape::Auto:
			// Contorno discontinuo: "lo que diga el dibujo". La "A" la pone el boton encima.
			F2DPalette::DashedFrame(Out, Layer, Geo, Effect, Ox, Oy, Side, Side, 1.0f, FMath::Max(2.0f, Cell), Fg.CopyWithNewOpacity(Fg.A * 0.7f));
			break;

		case EFramework2DCollisionShape::None:
			// Cuadro tachado.
			Cellbox(0.0f, 0.0f, Side, Side, Faint);
			F2DPalette::Frame(Out, Layer, Geo, Effect, Ox, Oy, Side, Side, 1.0f, Fg.CopyWithNewOpacity(Fg.A * 0.5f));
			for (int32 I = 0; I < 8; ++I)
			{
				Cellbox(I * Cell, I * Cell, Cell, Cell, bActive ? Fg : FFramework2DEditorStyle::Danger() * Tint);
			}
			break;

		case EFramework2DCollisionShape::Pixels:
		{
			// Puntos con forma de "dibujo": chocan los pixeles que tienen dibujo.
			static const char* const Mask[8] =
			{
				"........",
				"..###...",
				".#####..",
				".######.",
				"########",
				".######.",
				"..##.##.",
				"........",
			};
			Cellbox(0.0f, 0.0f, Side, Side, Faint);
			const float Dot = FMath::Max(1.0f, Cell - 1.0f);
			for (int32 Cy = 0; Cy < 8; ++Cy)
			{
				for (int32 Cx = 0; Cx < 8; ++Cx)
				{
					if (Mask[Cy][Cx] == '#') { Cellbox(Cx * Cell, Cy * Cell, Dot, Dot, Solid); }
				}
			}
			break;
		}

		default:
			// Formas a medida: la misma rasterizacion que usa el terreno, a 8x8.
			Cellbox(0.0f, 0.0f, Side, Side, Faint);
			for (int32 Cy = 0; Cy < 8; ++Cy)
			{
				int32 Run = -1;
				for (int32 Cx = 0; Cx <= 8; ++Cx)
				{
					const bool bCovered = Cx < 8 && Framework2D::ShapeCovers(Shape, Cx, Cy, 8);
					if (bCovered && Run < 0) { Run = Cx; }
					if (!bCovered && Run >= 0)
					{
						Cellbox(Run * Cell, Cy * Cell, (Cx - Run) * Cell, Cell, Solid);
						Run = -1;
					}
				}
			}
			break;
		}
		return Layer;
	}

private:
	EFramework2DCollisionShape Shape = EFramework2DCollisionShape::Auto;
	float Size = 24.0f;
	TAttribute<bool> IsActive;
};

// =====================================================================
//  Selector de atlas: la pagina activa entera; clic = un tile, arrastrar = un bloque
// =====================================================================
class SFramework2DAtlasPicker : public SLeafWidget
{
public:
	SLATE_BEGIN_ARGS(SFramework2DAtlasPicker) {}
		SLATE_ATTRIBUTE(int32, Zoom)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, FFramework2DTilePaintMode* InMode)
	{
		Mode = InMode;
		Zoom = InArgs._Zoom;
	}

	virtual FVector2D ComputeDesiredSize(float) const override
	{
		int32 W = 0, H = 0;
		const UFramework2DTileSet* Set = Mode->GetTileSet();
		if (!Set || !Set->GetPageSize(Mode->ActivePage, W, H)) { return FVector2D(1.0f, 1.0f); }
		const int32 Z = FMath::Max(1, Zoom.Get());
		return FVector2D(W * Z, H * Z);
	}

	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& Geo, const FSlateRect& Culling, FSlateWindowElementList& Out,
		int32 Layer, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override
	{
		const UFramework2DTileSet* Set = Mode->GetTileSet();
		const int32 Page = Mode->ActivePage;
		UTexture2D* Texture = Set ? Set->GetPageTexture(Page) : nullptr;
		int32 AW = 0, AH = 0;
		if (!Texture || !Set->GetPageSize(Page, AW, AH)) { return Layer; }
		const ESlateDrawEffect Effect = ShouldBeEnabled(bParentEnabled) ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect;
		const float Z = (float)FMath::Max(1, Zoom.Get());
		const float TW = Set->TileWidth * Z;
		const float TH = Set->TileHeight * Z;
		const int32 Cols = Mode->GetAtlasColumns();
		const int32 Rows = Mode->GetAtlasRows();
		const FLinearColor Accent = FFramework2DEditorStyle::Accent();
		auto Box = [&](float X, float Y, float W, float H, const FLinearColor& C, int32 L)
		{
			F2DPalette::Box(Out, L, Geo, Effect, X, Y, W, H, C);
		};
		auto Frame = [&](float X, float Y, float W, float H, float T, const FLinearColor& C, int32 L)
		{
			F2DPalette::Frame(Out, L, Geo, Effect, X, Y, W, H, T, C);
		};

		// Fondo a cuadros (se ven los pixeles transparentes) y la imagen encima.
		Box(0, 0, AW * Z, AH * Z, FLinearColor(0.16f, 0.16f, 0.17f), Layer);
		const float Q = FMath::Max(4.0f, Z * 4.0f);
		for (float Y = 0; Y < AH * Z; Y += Q)
		{
			for (float X = ((int32)(Y / Q) % 2) * Q; X < AW * Z; X += 2 * Q)
			{
				Box(X, Y, FMath::Min(Q, AW * Z - X), FMath::Min(Q, AH * Z - Y), FLinearColor(0.22f, 0.22f, 0.23f), Layer);
			}
		}
		AtlasBrush.SetResourceObject(Texture);
		AtlasBrush.DrawAs = ESlateBrushDrawType::Image;
		AtlasBrush.SetImageSize(FVector2D(AW, AH));
		FSlateDrawElement::MakeBox(Out, Layer + 1, Geo.ToPaintGeometry(FVector2D(AW * Z, AH * Z), FSlateLayoutTransform(FVector2D(0, 0))),
			&AtlasBrush, Effect, InWidgetStyle.GetColorAndOpacityTint());

		// Rejilla de tiles y tiles sin material atenuados (no son terreno).
		for (int32 R = 0; R < Rows; ++R)
		{
			for (int32 C = 0; C < Cols; ++C)
			{
				if (Set->GetTileMaterial(Framework2D::MakeTileValue(Page, R * Cols + C)) == NAME_None) { Box(C * TW, R * TH, TW, TH, FLinearColor(0, 0, 0, 0.35f), Layer + 2); }
			}
		}
		for (int32 C = 1; C < Cols; ++C) { Box(C * TW, 0, 1, Rows * TH, FLinearColor(1, 1, 1, 0.18f), Layer + 2); }
		for (int32 R = 1; R < Rows; ++R) { Box(0, R * TH, Cols * TW, 1, FLinearColor(1, 1, 1, 0.18f), Layer + 2); }

		// Seleccion (si es de esta pagina). Con un flipbook o un generador como pincel, la del
		// atlas no es lo que se pinta: se apaga y se marca lo suyo (fotogramas numerados, sprites).
		const FIntRect& Sel = Mode->BrushRect;
		const float SX = Sel.Min.X * TW;
		const float SY = Sel.Min.Y * TH;
		const float SW = (Sel.Max.X - Sel.Min.X + 1) * TW;
		const float SH = (Sel.Max.Y - Sel.Min.Y + 1) * TH;
		const bool bSelectionHere = Mode->BrushPage == Page;
		if (!Mode->IsSpecialBrush())
		{
			if (bSelectionHere)
			{
				Box(SX, SY, SW, SH, Accent.CopyWithNewOpacity(0.18f), Layer + 3);
				Frame(SX, SY, SW, SH, 2.0f, Accent, Layer + 4);
			}
		}
		else
		{
			if (bSelectionHere) { F2DPalette::DashedFrame(Out, Layer + 4, Geo, Effect, SX, SY, SW, SH, 1.0f, 4.0f, FLinearColor(1, 1, 1, 0.45f)); }
			const bool bNumbers = TW >= 14.0f && TH >= 14.0f;
			const FSlateFontInfo NumberFont = F2DPalette::Font(true, 7);
			auto Mark = [&](int32 Value, int32 WTiles, int32 HTiles, int32 Number, const FLinearColor& Color)
			{
				if (!Framework2D::IsAtlasTileValue(Value) || Framework2D::TilePageOf(Value) != Page || Cols <= 0) { return; }
				const int32 Local = Framework2D::TileLocalOf(Value);
				const float FX = (Local % Cols) * TW;
				const float FY = (Local / Cols) * TH;
				Frame(FX, FY, TW * WTiles, TH * HTiles, 2.0f, Color, Layer + 4);
				if (bNumbers && Number > 0)
				{
					const FString Text = FString::FromInt(Number);
					const float LabelW = 4.0f + 5.5f * Text.Len();
					Box(FX + 2.0f, FY + 2.0f, LabelW, 11.0f, Color, Layer + 5);
					FSlateDrawElement::MakeText(Out, Layer + 6,
						Geo.ToPaintGeometry(FVector2D(LabelW, 11.0f), FSlateLayoutTransform(FVector2D(FX + 4.0f, FY + 1.5f))),
						Text, NumberFont, Effect, FFramework2DEditorStyle::OnAccent());
				}
			};
			if (Mode->IsFlipbookBrush())
			{
				const int32 Index = Set->FindFlipbookIndex(Mode->BrushFlipbookId);
				if (Index != INDEX_NONE)
				{
					const TArray<int32>& Frames = Set->Flipbooks[Index].Frames;
					for (int32 I = 0; I < Frames.Num(); ++I) { Mark(Frames[I], 1, 1, I + 1, Accent); }
				}
			}
			else if (const FFramework2DGenerator* Generator = Set->FindGeneratorByValue(Framework2D::MakeGeneratorValue(Mode->BrushGeneratorId)))
			{
				const FLinearColor Teal(0.3f, 0.9f, 0.8f, 1.0f);
				for (const FFramework2DScatterSprite& Sprite : Generator->Sprites)
				{
					Mark(Sprite.Tile, FMath::Clamp(Sprite.WidthInTiles, 1, 16), FMath::Clamp(Sprite.HeightInTiles, 1, 16), 0, Teal);
				}
			}
		}
		if (Hover.X >= 0 && !bDragging) { Frame(Hover.X * TW, Hover.Y * TH, TW, TH, 1.0f, FLinearColor(1, 1, 1, 0.8f), Layer + 6); }
		return Layer + 6;
	}

	virtual FReply OnMouseButtonDown(const FGeometry& Geo, const FPointerEvent& Event) override
	{
		if (Event.GetEffectingButton() != EKeys::LeftMouseButton) { return FReply::Unhandled(); }
		const FIntPoint T = TileAt(Geo, Event);
		if (T.X < 0) { return FReply::Unhandled(); }
		bDragging = true;
		DragStart = T;
		Mode->SelectAtlasRect(FIntRect(T, T));
		return FReply::Handled().CaptureMouse(SharedThis(this));
	}

	virtual FReply OnMouseMove(const FGeometry& Geo, const FPointerEvent& Event) override
	{
		const FIntPoint T = TileAt(Geo, Event, /*bClamp*/ bDragging);
		Hover = T;
		if (bDragging && T.X >= 0) { Mode->SelectAtlasRect(FIntRect(DragStart, T)); }
		return bDragging ? FReply::Handled() : FReply::Unhandled();
	}

	virtual FReply OnMouseButtonUp(const FGeometry& Geo, const FPointerEvent& Event) override
	{
		if (!bDragging || Event.GetEffectingButton() != EKeys::LeftMouseButton) { return FReply::Unhandled(); }
		bDragging = false;
		return FReply::Handled().ReleaseMouseCapture();
	}

	virtual void OnMouseLeave(const FPointerEvent& Event) override
	{
		SLeafWidget::OnMouseLeave(Event);
		Hover = FIntPoint(-1, -1);
	}

	virtual FCursorReply OnCursorQuery(const FGeometry&, const FPointerEvent&) const override { return FCursorReply::Cursor(EMouseCursor::Crosshairs); }

private:
	FFramework2DTilePaintMode* Mode = nullptr;
	TAttribute<int32> Zoom;
	mutable FSlateBrush AtlasBrush;
	bool bDragging = false;
	FIntPoint DragStart = FIntPoint(0, 0);
	FIntPoint Hover = FIntPoint(-1, -1);

	FIntPoint TileAt(const FGeometry& Geo, const FPointerEvent& Event, bool bClamp = false) const
	{
		const UFramework2DTileSet* Set = Mode->GetTileSet();
		if (!Set) { return FIntPoint(-1, -1); }
		const FVector2D Local = Geo.AbsoluteToLocal(Event.GetScreenSpacePosition());
		const float Z = (float)FMath::Max(1, Zoom.Get());
		int32 X = FMath::FloorToInt((float)Local.X / (Set->TileWidth * Z));
		int32 Y = FMath::FloorToInt((float)Local.Y / (Set->TileHeight * Z));
		const int32 Cols = Mode->GetAtlasColumns();
		const int32 Rows = Mode->GetAtlasRows();
		if (Cols <= 0 || Rows <= 0) { return FIntPoint(-1, -1); }
		if (bClamp) { X = FMath::Clamp(X, 0, Cols - 1); Y = FMath::Clamp(Y, 0, Rows - 1); }
		if (X < 0 || Y < 0 || X >= Cols || Y >= Rows) { return FIntPoint(-1, -1); }
		return FIntPoint(X, Y);
	}
};

// =====================================================================
//  Panel
// =====================================================================
void SFramework2DTilePalette::Construct(const FArguments& InArgs, FFramework2DTilePaintMode* InMode)
{
	Mode = InMode;

	// Las 11 formas, en el orden del enum (desplegable de colision de la seleccion).
	for (int32 S = 0; S < F2DPalette::NumCollisionShapes; ++S)
	{
		ShapeOptions.Add(MakeShared<EFramework2DCollisionShape>((EFramework2DCollisionShape)S));
	}
	RefreshMaterialOptions();

	// Cada pestaña es una columna de tarjetas; la otra queda plegada (no se pinta ni se
	// actualiza). «Pintar» es la de siempre, tal cual.
	auto TabVisibility = [this](EFramework2DPaletteTab Tab)
	{
		return TAttribute<EVisibility>::CreateLambda([this, Tab]() { return ActiveTab == Tab ? EVisibility::Visible : EVisibility::Collapsed; });
	};

	ChildSlot
	[
		SNew(SScrollBox)
		+ SScrollBox::Slot()
		.Padding(FMargin(6.0f, 6.0f, 6.0f, 12.0f))
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot().AutoHeight()                         [ MakeStatusCard() ]
			+ SVerticalBox::Slot().AutoHeight().Padding(0, 6, 0, 0)  [ MakeTabsBar() ]
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SVerticalBox)
				.Visibility(TabVisibility(EFramework2DPaletteTab::Paint))
				+ SVerticalBox::Slot().AutoHeight().Padding(0, 6, 0, 0)  [ MakeToolsCard() ]
				+ SVerticalBox::Slot().AutoHeight().Padding(0, 6, 0, 0)  [ MakeLayersCard() ]
				+ SVerticalBox::Slot().AutoHeight().Padding(0, 6, 0, 0)  [ MakeCollisionCard() ]
				+ SVerticalBox::Slot().AutoHeight().Padding(0, 6, 0, 0)  [ MakeAtlasCard() ]
				+ SVerticalBox::Slot().AutoHeight().Padding(0, 6, 0, 0)  [ MakeFlipbooksCard() ]
				+ SVerticalBox::Slot().AutoHeight().Padding(0, 6, 0, 0)  [ MakeGeneratorsCard() ]
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0, 6, 0, 0)
			[
				SAssignNew(ProcGenPanel, SFramework2DProcGenPanel, Mode)
				.Visibility(TabVisibility(EFramework2DPaletteTab::Generate))
			]
		]
	];

	RebuildLayers();
	LastLayersSignature = ComputeLayersSignature();
	RebuildFlipbooks();
	LastFlipbooksSignature = ComputeFlipbooksSignature();
	RebuildPageTabs();
	LastPagesSignature = ComputePagesSignature();
	RebuildGenerators();
	LastGeneratorsSignature = ComputeGeneratorsSignature();
}

void SFramework2DTilePalette::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);

	// Las listas solo se rehacen si cambia su forma (cuantas capas, que flipbooks); lo demas
	// (nombres, estados) lo leen las propias filas cada frame.
	const uint32 LayersSignature = ComputeLayersSignature();
	if (LayersSignature != LastLayersSignature)
	{
		LastLayersSignature = LayersSignature;
		// Tras deshacer o cambiar de mapa la capa activa puede no existir ya.
		if (const UFramework2DTileMapAsset* Map = Mode->GetTileMap())
		{
			Mode->ActiveLayer = FMath::Clamp(Mode->ActiveLayer, 0, FMath::Max(0, Map->GetNumLayers() - 1));
		}
		RebuildLayers();
	}
	const uint32 FlipbooksSignature = ComputeFlipbooksSignature();
	if (FlipbooksSignature != LastFlipbooksSignature)
	{
		LastFlipbooksSignature = FlipbooksSignature;
		RebuildFlipbooks();
	}
	const uint32 PagesSignature = ComputePagesSignature();
	if (PagesSignature != LastPagesSignature)
	{
		LastPagesSignature = PagesSignature;
		RebuildPageTabs();
	}
	// El generador elegido como pincel (desde el panel o con el cuentagotas) es el que se ajusta.
	if (Mode->IsGeneratorBrush() && Mode->BrushGeneratorId != EditedGeneratorId) { EditedGeneratorId = Mode->BrushGeneratorId; }
	const uint32 GeneratorsSignature = ComputeGeneratorsSignature();
	if (GeneratorsSignature != LastGeneratorsSignature)
	{
		LastGeneratorsSignature = GeneratorsSignature;
		RebuildGenerators();
	}
	UpdateStatefulButtons();
}

uint32 SFramework2DTilePalette::ComputeLayersSignature() const
{
	const UFramework2DTileMapAsset* Map = Mode->GetTileMap();
	uint32 H = GetTypeHash(Map);
	H = HashCombine(H, GetTypeHash(Map ? Map->GetNumLayers() : -1));
	return H;
}

uint32 SFramework2DTilePalette::ComputeFlipbooksSignature() const
{
	const UFramework2DTileSet* Set = Mode->GetTileSet();
	uint32 H = GetTypeHash(Set);
	H = HashCombine(H, GetTypeHash(Set ? Set->Flipbooks.Num() : -1));
	if (Set)
	{
		for (const FFramework2DFlipbook& Flipbook : Set->Flipbooks)
		{
			H = HashCombine(H, GetTypeHash(Flipbook.Id));
		}
	}
	return H;
}

bool SFramework2DTilePalette::IsReady() const
{
	const UFramework2DTileSet* Set = Mode->GetTileSet();
	return Mode->GetTarget() && Mode->GetTileMap() && Set && Set->Atlas && Set->GetNumTiles() > 0;
}

FText SFramework2DTilePalette::GetStatusText() const
{
	const AFramework2DTerrainWorld* Target = Mode->GetTarget();
	const UFramework2DTileMapAsset* Map = Target ? Target->TileMap.Get() : nullptr;
	const UFramework2DTileSet* Set = Map ? Map->TileSet.Get() : nullptr;
	if (!Target)
	{
		return LOCTEXT("NoTarget", "1. Drag a «Framework2D Terrain» into the level (Place Actors › search Framework2D).");
	}
	if (!Map)
	{
		return LOCTEXT("NoMap", "2. Select the terrain and assign it a Tile Map in Details (Add › Miscellaneous › Data Asset › Framework2DTileMapAsset).");
	}
	if (!Set)
	{
		return FText::Format(LOCTEXT("NoSet", "3. Open the Tile Map «{0}» and assign it a Tile Set."), FText::FromString(Map->GetName()));
	}
	if (!Set->Atlas || Set->GetNumTiles() == 0)
	{
		return FText::Format(LOCTEXT("NoAtlas", "4. Open the Tile Set «{0}» and assign it an Atlas (and the tile size)."), FText::FromString(Set->GetName()));
	}
	if (ActiveTab == EFramework2DPaletteTab::Generate)
	{
		return FText::Format(LOCTEXT("ReadyGenerate", "Generating «{0}» in «{1}». Choose a biome, adjust the recipe and press «Generate map»; Ctrl+Z undoes."),
			FText::FromString(Map->GetName()), FText::FromString(Target->GetActorLabel()));
	}
	return FText::Format(LOCTEXT("Ready", "Painting «{0}» in «{1}». Left click in the viewport to use the tool; Ctrl+Z undoes."),
		FText::FromString(Map->GetName()), FText::FromString(Target->GetActorLabel()));
}

// ---------------------------------------------------------------------
//  1. Estado
// ---------------------------------------------------------------------
TSharedRef<SWidget> SFramework2DTilePalette::MakeStatusCard()
{
	return F2DPalette::Card(
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(0.0f, 0.0f, 8.0f, 0.0f)
			[
				SNew(SImage)
				.Image(F2DPalette::Brush("F2D.Mode.Small"))
				.ColorAndOpacity(FFramework2DEditorStyle::Accent())
			]
			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.TextStyle(&F2DPalette::Text("F2D.Text.Title"))
				.Text(LOCTEXT("PanelTitle", "Framework2D Tiles"))
			]
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 6.0f, 0.0f, 0.0f)
		[
			SNew(SHorizontalBox)
			// Si falta un paso, el icono de aviso lo dice ademas del texto (no solo el color).
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Top)
			.Padding(0.0f, 0.0f, 6.0f, 0.0f)
			[
				SNew(SImage)
				.Image(F2DPalette::Brush("F2D.Icon.Info"))
				.ColorAndOpacity(FFramework2DEditorStyle::Accent())
				.Visibility_Lambda([this]() { return IsReady() ? EVisibility::Collapsed : EVisibility::Visible; })
			]
			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.TextStyle(&F2DPalette::Text("F2D.Text.Body"))
				.AutoWrapText(true)
				.Text(this, &SFramework2DTilePalette::GetStatusText)
				.ColorAndOpacity_Lambda([this]() -> FSlateColor
				{
					return IsReady() ? FFramework2DEditorStyle::ForegroundDim() : FFramework2DEditorStyle::Foreground();
				})
			]
		]);
}

// ---------------------------------------------------------------------
//  1b. Pestañas «Pintar» | «Generar» (control segmentado)
// ---------------------------------------------------------------------
TSharedRef<SWidget> SFramework2DTilePalette::MakeTabButton(EFramework2DPaletteTab Tab)
{
	const bool bPaint = Tab == EFramework2DPaletteTab::Paint;
	const FText Name = bPaint ? LOCTEXT("TabPaint", "Paint") : LOCTEXT("TabGenerate", "Generate");
	const FText Tip = bPaint
		? LOCTEXT("TabPaintTip", "Paint: tools, layers, collision, atlas, flipbooks and generators to paint the map by hand.")
		: LOCTEXT("TabGenerateTip", "Generate: creates the map procedurally from a biome (the pieces: 3×3 terrain, ramps, water, decoration...) and a recipe (heights, ramps, lakes, seed...).");

	TSharedRef<SButton> Button = SNew(SButton)
		.ButtonStyle(&F2DPalette::Button("F2D.Button.Tool"))
		.ContentPadding(FMargin(0.0f, 1.0f))
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.ToolTipText(Tip)
		.OnClicked_Lambda([this, Tab]()
		{
			ActiveTab = Tab;
			return FReply::Handled();
		})
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			[
				SNew(SBox)
				.WidthOverride(16.0f)
				.HeightOverride(16.0f)
				[
					SNew(SImage)
					.Image(F2DPalette::Brush(bPaint ? FName("F2D.Tool.Paint") : FName("F2D.Icon.Dice")))
					.ColorAndOpacity(FSlateColor::UseForeground())
				]
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(6.0f, 0.0f, 0.0f, 0.0f)
			[
				// La pestaña activa, además del fondo ámbar, va en negrita.
				SNew(STextBlock)
				.Text(Name)
				.Font_Lambda([this, Tab]() { return F2DPalette::Font(ActiveTab == Tab, 9); })
				.ColorAndOpacity(FSlateColor::UseForeground())
			]
		];

	RegisterStatefulButton(Button, [this, Tab]() { return ActiveTab == Tab; },
		&F2DPalette::Button("F2D.Button.Tool"), &F2DPalette::Button("F2D.Button.ToolActive"));
	return Button;
}

TSharedRef<SWidget> SFramework2DTilePalette::MakeTabsBar()
{
	// Dos segmentos del mismo ancho, pegados (2 px), sobre una tarjeta como el resto.
	return SNew(SBorder)
		.BorderImage(F2DPalette::Brush("F2D.Card"))
		.Padding(FMargin(4.0f))
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			[
				MakeTabButton(EFramework2DPaletteTab::Paint)
			]
			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			.Padding(2.0f, 0.0f, 0.0f, 0.0f)
			[
				MakeTabButton(EFramework2DPaletteTab::Generate)
			]
		];
}

// ---------------------------------------------------------------------
//  2. Herramientas
// ---------------------------------------------------------------------
TSharedRef<SWidget> SFramework2DTilePalette::MakeToolButton(EFramework2DTileTool InTool)
{
	const FText Name = FFramework2DTilePaintMode::GetToolName(InTool);
	const FText Tip = FText::Format(LOCTEXT("ToolTip", "{0} ({1})\n{2}"),
		Name, FFramework2DTilePaintMode::GetToolShortcut(InTool), FFramework2DTilePaintMode::GetToolHelp(InTool));

	TSharedRef<SButton> Button = SNew(SButton)
		.ButtonStyle(&F2DPalette::Button("F2D.Button.Tool"))
		.ContentPadding(FMargin(0.0f))
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.ToolTipText(Tip)
		.OnClicked_Lambda([this, InTool]()
		{
			Mode->Tool = InTool;
			F2DPalette::RedrawViewports();
			return FReply::Handled();
		})
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(HAlign_Center)
			[
				SNew(SImage)
				.Image(F2DPalette::Brush(F2DPalette::ToolIcon(InTool)))
				.ColorAndOpacity(FSlateColor::UseForeground())
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(HAlign_Center)
			.Padding(0.0f, 3.0f, 0.0f, 0.0f)
			[
				SNew(STextBlock)
				.Text(Name)
				.Font(F2DPalette::Font(false, 8))
				.ColorAndOpacity(FSlateColor::UseForeground())
				.OverflowPolicy(ETextOverflowPolicy::Ellipsis)
			]
		];

	// Activa = fondo ambar con texto oscuro (cambia el relleno, no solo el tono).
	RegisterStatefulButton(Button, [this, InTool]() { return Mode->Tool == InTool; },
		&F2DPalette::Button("F2D.Button.Tool"), &F2DPalette::Button("F2D.Button.ToolActive"));
	return Button;
}

TSharedRef<SWidget> SFramework2DTilePalette::MakeToolsCard()
{
	const EFramework2DTileTool Tools[] =
	{
		EFramework2DTileTool::Paint, EFramework2DTileTool::Erase, EFramework2DTileTool::Fill,
		EFramework2DTileTool::Rect, EFramework2DTileTool::Pick, EFramework2DTileTool::Collision
	};

	// Fila segmentada. Cada segmento recibe ancho segun lo largo de su etiqueta, asi
	// "Cuentagotas" o "Rectangulo" no se cortan a 400 px y los cortos no sobran.
	TSharedRef<SHorizontalBox> ToolRow = SNew(SHorizontalBox);
	for (int32 I = 0; I < (int32)UE_ARRAY_COUNT(Tools); ++I)
	{
		const float Weight = (float)FMath::Max(6, FFramework2DTilePaintMode::GetToolName(Tools[I]).ToString().Len()) + 3.0f;
		ToolRow->AddSlot()
			.FillWidth(Weight)
			.Padding(I == 0 ? 0.0f : 2.0f, 0.0f, 0.0f, 0.0f)
			[
				MakeToolButton(Tools[I])
			];
	}

	TSharedRef<SWidget> Refresh = F2DPalette::IconButton("F2D.Icon.Refresh",
		LOCTEXT("RefreshTip", "Refresh view: bakes the terrain preview again (in case you changed the atlas outside the editor)."),
		FOnClicked::CreateLambda([this]() { Mode->RefreshPreview(); return FReply::Handled(); }),
		TAttribute<bool>::CreateLambda([this]() { return Mode->GetTarget() != nullptr; }));

	return F2DPalette::Card(
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 0.0f, 0.0f, 8.0f)
		[
			F2DPalette::CardHeader("F2D.Tool.Paint", LOCTEXT("ToolsTitle", "Tools"))
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			ToolRow
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 8.0f, 0.0f, 0.0f)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			.VAlign(VAlign_Center)
			[
				// Fila fija (no SWrapBox): los tres caben a 380 px y asi no reserva altura de mas.
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(0.0f, 0.0f, 4.0f, 0.0f)
				[
					F2DPalette::ToggleChip("F2D.Icon.Grid", LOCTEXT("GridChip", "Grid"),
						LOCTEXT("GridChipTip", "Grid: draws the tile lines in the viewport, on the active layer's plane."),
						[this]() { return Mode->bShowGrid; },
						[this](bool bOn) { Mode->bShowGrid = bOn; F2DPalette::RedrawViewports(); })
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(0.0f, 0.0f, 4.0f, 0.0f)
				[
					F2DPalette::ToggleChip("F2D.Icon.Ghost", LOCTEXT("GhostChip", "Preview"),
						LOCTEXT("GhostChipTip", "Preview: shows what you are about to paint under the mouse, semi-transparent, before you click."),
						[this]() { return Mode->bShowGhost; },
						[this](bool bOn) { Mode->bShowGhost = bOn; F2DPalette::RedrawViewports(); })
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					F2DPalette::ToggleChip("F2D.Icon.Collide", LOCTEXT("CollisionChip", "Show collision"),
						LOCTEXT("CollisionChipTip", "Show collision: draws what collides in green. Always visible with the Collision tool."),
						[this]() { return Mode->bShowCollision; },
						[this](bool bOn) { Mode->bShowCollision = bOn; F2DPalette::RedrawViewports(); })
				]
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Top)
			.Padding(4.0f, 0.0f, 0.0f, 0.0f)
			[
				Refresh
			]
		]);
}

// ---------------------------------------------------------------------
//  3. Capas
// ---------------------------------------------------------------------
void SFramework2DTilePalette::ApplySeparation(float Value, bool bFinal)
{
	Mode->SetLayerSeparation(FMath::Clamp(Value, 0.0f, 200.0f), bFinal);
}

TSharedRef<SWidget> SFramework2DTilePalette::MakeLayersCard()
{
	auto NumLayers = [this]() -> int32
	{
		const UFramework2DTileMapAsset* Map = Mode->GetTileMap();
		return Map ? Map->GetNumLayers() : 0;
	};

	TSharedRef<SHorizontalBox> Buttons = SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			F2DPalette::IconButton("F2D.Icon.Add",
				LOCTEXT("AddLayerTip", "Add a new layer, in front of all of them."),
				FOnClicked::CreateLambda([this]() { Mode->AddLayer(); return FReply::Handled(); }),
				TAttribute<bool>::CreateLambda([this]() { return Mode->GetTileMap() != nullptr; }))
		]
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(2.0f, 0.0f, 0.0f, 0.0f)
		[
			F2DPalette::IconButton("F2D.Icon.Remove",
				LOCTEXT("RemoveLayerTip", "Remove the active layer (Ctrl+Z brings it back). At least one always remains."),
				FOnClicked::CreateLambda([this]() { Mode->RemoveActiveLayer(); return FReply::Handled(); }),
				TAttribute<bool>::CreateLambda([NumLayers]() { return NumLayers() > 1; }))
		]
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(2.0f, 0.0f, 0.0f, 0.0f)
		[
			F2DPalette::IconButton("F2D.Icon.Up",
				LOCTEXT("LayerUpTip", "Move the active layer up: further forward, closer to the camera."),
				FOnClicked::CreateLambda([this]() { Mode->MoveActiveLayer(+1); F2DPalette::RedrawViewports(); return FReply::Handled(); }),
				TAttribute<bool>::CreateLambda([this, NumLayers]() { return Mode->ActiveLayer < NumLayers() - 1; }))
		]
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(2.0f, 0.0f, 0.0f, 0.0f)
		[
			F2DPalette::IconButton("F2D.Icon.Down",
				LOCTEXT("LayerDownTip", "Move the active layer down: further back."),
				FOnClicked::CreateLambda([this]() { Mode->MoveActiveLayer(-1); F2DPalette::RedrawViewports(); return FReply::Handled(); }),
				TAttribute<bool>::CreateLambda([this, NumLayers]() { return Mode->ActiveLayer > 0 && NumLayers() > 0; }))
		];

	const FText SeparationTip = LOCTEXT("SeparationTip", "Depth distance (cm) between the layer planes. The base layer stays on the actor's plane, where the collision and the characters are; the ones above go in front (towards the camera) and the ones below, behind. 0 = almost the same plane (half a centimeter between layers, so the front one always stays in front).");

	return F2DPalette::Card(
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			F2DPalette::CardHeader("F2D.Icon.Layers", LOCTEXT("LayersTitle", "Layers"), Buttons)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 2.0f, 0.0f, 8.0f)
		[
			F2DPalette::Caption(LOCTEXT("LayersHelp", "Top = front (closer to the camera). Click: active layer · Double click: rename."))
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SAssignNew(LayersBox, SVerticalBox)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 8.0f, 0.0f, 0.0f)
		[
			SNew(SHorizontalBox)
			.IsEnabled_Lambda([this]() { return Mode->GetTarget() != nullptr; })
			.ToolTipText(SeparationTip)
			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.TextStyle(&F2DPalette::Text("F2D.Text.Body"))
				.Text(LOCTEXT("Separation", "Layer separation"))
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			[
				SNew(SBox)
				.WidthOverride(76.0f)
				[
					SNew(SSpinBox<float>)
					.MinValue(0.0f)
					.MaxValue(200.0f)
					.MinSliderValue(0.0f)
					.MaxSliderValue(200.0f)
					.Delta(0.5f)
					.MaxFractionalDigits(1)
					.ToolTipText(SeparationTip)
					.Value_Lambda([this]() { return Mode->GetLayerSeparation(); })
					.OnBeginSliderMovement_Lambda([this]()
					{
						bSeparationDragging = true;
						SeparationAtDragStart = Mode->GetLayerSeparation();
					})
					.OnValueChanged_Lambda([this](float NewValue)
					{
						// Mientras se arrastra se ve en vivo, sin pasos de deshacer.
						if (bSeparationDragging) { ApplySeparation(NewValue, false); }
					})
					.OnEndSliderMovement_Lambda([this](float NewValue)
					{
						// Siempre se cierra el arrastre: si acaba en el valor de partida (o con Esc)
						// el modo lo deja como estaba sin paso de deshacer; si no, guarda uno.
						bSeparationDragging = false;
						ApplySeparation(NewValue, true);
					})
					.OnValueCommitted_Lambda([this](float NewValue, ETextCommit::Type)
					{
						// Valor escrito a mano o con las flechas (al soltar un arrastre ya lo guarda OnEndSliderMovement).
						if (!bSeparationDragging && !FMath::IsNearlyEqual(NewValue, Mode->GetLayerSeparation()))
						{
							ApplySeparation(NewValue, true);
						}
					})
				]
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(6.0f, 0.0f, 0.0f, 0.0f)
			[
				SNew(STextBlock)
				.TextStyle(&F2DPalette::Text("F2D.Text.Caption"))
				.Text(LOCTEXT("Centimeters", "cm"))
			]
		]);
}

void SFramework2DTilePalette::RebuildLayers()
{
	LayersBox->ClearChildren();
	const UFramework2DTileMapAsset* Map = Mode->GetTileMap();
	if (!Map || Map->GetNumLayers() == 0)
	{
		LayersBox->AddSlot()
			.AutoHeight()
			[
				F2DPalette::Caption(LOCTEXT("NoLayers", "No Tile Map: assign one to the terrain to see its layers."))
			];
		return;
	}

	// La capa de mas delante arriba, como en cualquier editor de imagen.
	for (int32 L = Map->GetNumLayers() - 1; L >= 0; --L)
	{
		LayersBox->AddSlot()
			.AutoHeight()
			.Padding(0.0f, 0.0f, 0.0f, 2.0f)
			[
				MakeLayerRow(L)
			];
	}
}

TSharedRef<SWidget> SFramework2DTilePalette::MakeLayerRow(int32 L)
{
	FFramework2DTilePaintMode* M = Mode;
	auto Layer = [M, L]() -> const FFramework2DTileLayer*
	{
		const UFramework2DTileMapAsset* Map = M->GetTileMap();
		return (Map && Map->Layers.IsValidIndex(L)) ? &Map->Layers[L] : nullptr;
	};
	auto IsActive = [M, L]() { return M->ActiveLayer == L; };
	auto IsBackground = [Layer]() { const FFramework2DTileLayer* Data = Layer(); return Data && Data->bBackground; };

	TSharedPtr<SInlineEditableTextBlock> NameBlock;
	TSharedRef<SFramework2DListRow> Row = SNew(SFramework2DListRow)
		.IsActive_Lambda(IsActive)
		.OnSelected_Lambda([M, L]() { M->ActiveLayer = L; F2DPalette::RedrawViewports(); })
		[
			SNew(SHorizontalBox)
			// Barra de acento de la capa activa (forma, ademas de color).
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SBox)
				.WidthOverride(3.0f)
				.Padding(FMargin(0.0f, 6.0f))
				[
					SNew(SImage)
					.Image(F2DPalette::Brush("F2D.AccentBar"))
					.Visibility_Lambda([IsActive]() { return IsActive() ? EVisibility::Visible : EVisibility::Hidden; })
				]
			]
			// Ojo: visible / oculta (el icono cambia de forma, no solo de color).
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(4.0f, 4.0f, 2.0f, 4.0f)
			[
				SNew(SButton)
				.ButtonStyle(&F2DPalette::Button("F2D.Button.Icon"))
				.ContentPadding(FMargin(0.0f))
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				.ToolTipText_Lambda([Layer]()
				{
					const FFramework2DTileLayer* Data = Layer();
					return (Data && Data->bVisible)
						? LOCTEXT("LayerVisibleTip", "Visible: shown and collides. Click to hide it.")
						: LOCTEXT("LayerHiddenTip", "Hidden: neither shown nor collides. Click to show it.");
				})
				.OnClicked_Lambda([M, L, Layer]()
				{
					const FFramework2DTileLayer* Data = Layer();
					if (Data) { M->SetLayerVisible(L, !Data->bVisible); }
					return FReply::Handled();
				})
				[
					SNew(SImage)
					.ColorAndOpacity(FSlateColor::UseForeground())
					.Image_Lambda([Layer]()
					{
						const FFramework2DTileLayer* Data = Layer();
						return F2DPalette::Brush((Data && Data->bVisible) ? FName("F2D.Icon.Eye") : FName("F2D.Icon.EyeOff"));
					})
				]
			]
			// Nombre (doble clic o F2 para renombrar). Negrita = activa; atenuado = oculta.
			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			.VAlign(VAlign_Center)
			.Padding(4.0f, 0.0f, 4.0f, 0.0f)
			[
				SAssignNew(NameBlock, SInlineEditableTextBlock)
				.ToolTipText(LOCTEXT("LayerNameTip", "Click: active layer (the one you paint on). Double click or F2: rename."))
				.Text_Lambda([Layer]()
				{
					const FFramework2DTileLayer* Data = Layer();
					return Data ? FText::FromName(Data->Name) : FText::GetEmpty();
				})
				.Font_Lambda([IsActive]() { return F2DPalette::Font(IsActive(), 9); })
				.ColorAndOpacity_Lambda([Layer]() -> FSlateColor
				{
					const FFramework2DTileLayer* Data = Layer();
					return (Data && Data->bVisible) ? FFramework2DEditorStyle::Foreground() : FFramework2DEditorStyle::ForegroundDim();
				})
				.OnVerifyTextChanged_Lambda([](const FText& InText, FText& OutError) { return F2DPalette::VerifyName(InText, OutError); })
				.OnTextCommitted_Lambda([M, L](const FText& NewText, ETextCommit::Type Commit)
				{
					if (Commit != ETextCommit::OnCleared) { M->RenameLayer(L, NewText); }
				})
			]
			// "base": la capa que va en el plano del actor.
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(0.0f, 0.0f, 6.0f, 0.0f)
			[
				SNew(STextBlock)
				.TextStyle(&F2DPalette::Text("F2D.Text.Caption"))
				.Text(LOCTEXT("BaseLayer", "base"))
				.ToolTipText(LOCTEXT("BaseLayerTip", "Base layer: on the actor's plane, where the collision and the characters are. The ones above stay in front and the ones below, behind."))
				.Visibility_Lambda([M, L]()
				{
					const AFramework2DTerrainWorld* Target = M->GetTarget();
					return (Target && Target->GetBaseLayer() == L) ? EVisibility::Visible : EVisibility::Collapsed;
				})
			]
			// Chips: Colisiona, Se rompe, Fondo.
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(1.0f, 0.0f)
			[
				F2DPalette::ToggleChip("F2D.Icon.Collide", FText::GetEmpty(),
					TAttribute<FText>::CreateLambda([Layer, IsBackground]()
					{
						if (IsBackground()) { return LOCTEXT("CollidesBgTip", "Collides: background layers never collide."); }
						const FFramework2DTileLayer* Data = Layer();
						return (Data && Data->bCollides)
							? LOCTEXT("CollidesOnTip", "Collides: yes. Characters collide with this layer. Click to turn it off.")
							: LOCTEXT("CollidesOffTip", "Collides: no. Nothing collides with it (decoration). Click to turn it on.");
					}),
					[Layer]() { const FFramework2DTileLayer* Data = Layer(); return Data && Data->bCollides && !Data->bBackground; },
					[M, L](bool bOn) { M->SetLayerCollides(L, bOn); },
					TAttribute<bool>::CreateLambda([IsBackground]() { return !IsBackground(); }))
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(1.0f, 0.0f)
			[
				F2DPalette::ToggleChip("F2D.Icon.Break", FText::GetEmpty(),
					TAttribute<FText>::CreateLambda([Layer, IsBackground]()
					{
						if (IsBackground()) { return LOCTEXT("BreakBgTip", "Breaks: background layers do not break."); }
						const FFramework2DTileLayer* Data = Layer();
						return (Data && Data->bBreakable)
							? LOCTEXT("BreakOnTip", "Breaks: yes. Digging and explosions break it. Click to turn it off.")
							: LOCTEXT("BreakOffTip", "Breaks: no. Digging does not touch it (untouchable decoration). Click to turn it on.");
					}),
					[Layer]() { const FFramework2DTileLayer* Data = Layer(); return Data && Data->bBreakable && !Data->bBackground; },
					[M, L](bool bOn) { M->SetLayerBreakable(L, bOn); },
					TAttribute<bool>::CreateLambda([IsBackground]() { return !IsBackground(); }))
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(1.0f, 0.0f, 6.0f, 0.0f)
			[
				F2DPalette::ToggleChip("F2D.Icon.Background", FText::GetEmpty(),
					TAttribute<FText>::CreateLambda([IsBackground]()
					{
						return IsBackground()
							? LOCTEXT("BackgroundOnTip", "Background: yes. Darkened back wall: does not collide and cannot be dug. Click to remove it.")
							: LOCTEXT("BackgroundOffTip", "Background: no. Click to turn it into a back wall (darkened, no collision, cannot be dug).");
					}),
					[IsBackground]() { return IsBackground(); },
					[M, L](bool bOn) { M->SetLayerBackground(L, bOn); })
			]
		];

	Row->SetRenameTarget(NameBlock);
	return Row;
}

// ---------------------------------------------------------------------
//  4. Colision
// ---------------------------------------------------------------------
TSharedRef<SWidget> SFramework2DTilePalette::MakeShapeButton(EFramework2DCollisionShape Shape)
{
	FFramework2DTilePaintMode* M = Mode;
	TSharedRef<SWidget> Content = SNew(SFramework2DShapeGlyph)
		.Shape(Shape)
		.Size(24.0f)
		.IsActive_Lambda([M, Shape]() { return M->CollisionBrush == Shape; });
	if (Shape == EFramework2DCollisionShape::Auto)
	{
		// "A" de Automatica encima del contorno discontinuo.
		Content = SNew(SOverlay)
			+ SOverlay::Slot()
			[
				Content
			]
			+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("AutoGlyph", "A"))
				.Font(F2DPalette::Font(true, 10))
				.ColorAndOpacity(FSlateColor::UseForeground())
			];
	}

	TSharedRef<SButton> Button = SNew(SButton)
		.ButtonStyle(&F2DPalette::ShapeButtonStyle(false))
		.ContentPadding(FMargin(0.0f))
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.ToolTipText(FText::Format(LOCTEXT("ShapeTip", "{0}\n{1}"),
			FFramework2DTilePaintMode::GetShapeName(Shape), FFramework2DTilePaintMode::GetShapeHelp(Shape)))
		.OnClicked_Lambda([M, Shape]()
		{
			M->SetCollisionBrush(Shape);
			F2DPalette::RedrawViewports();
			return FReply::Handled();
		})
		[
			Content
		];
	RegisterStatefulButton(Button, [M, Shape]() { return M->CollisionBrush == Shape; },
		&F2DPalette::ShapeButtonStyle(false), &F2DPalette::ShapeButtonStyle(true));

	return SNew(SBox)
		.WidthOverride(32.0f)
		.HeightOverride(32.0f)
		[
			Button
		];
}

TSharedRef<SWidget> SFramework2DTilePalette::MakeCollisionCard()
{
	// 6 columnas: 11 botones de 32 px caben de sobra en 400 px.
	TSharedRef<SUniformGridPanel> Grid = SNew(SUniformGridPanel).SlotPadding(FMargin(2.0f));
	for (int32 I = 0; I < F2DPalette::NumCollisionShapes; ++I)
	{
		Grid->AddSlot(I % 6, I / 6)
		[
			MakeShapeButton((EFramework2DCollisionShape)I)
		];
	}

	return F2DPalette::Card(
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			F2DPalette::CardHeader("F2D.Tool.Collision", LOCTEXT("CollisionTitle", "Collision"))
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 2.0f, 0.0f, 6.0f)
		[
			F2DPalette::Caption(LOCTEXT("CollisionHelp", "Paints collision shapes cell by cell. Automatic = remove."))
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				Grid
			]
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 6.0f, 0.0f, 0.0f)
		[
			SNew(STextBlock)
			.TextStyle(&F2DPalette::Text("F2D.Text.Body"))
			.Font(F2DPalette::Font(true, 9))
			.Text_Lambda([this]()
			{
				return FText::Format(LOCTEXT("ShapeCurrent", "Brush: {0}"), FFramework2DTilePaintMode::GetShapeName(Mode->CollisionBrush));
			})
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 2.0f, 0.0f, 0.0f)
		[
			F2DPalette::Caption(TAttribute<FText>::CreateLambda([this]() { return FFramework2DTilePaintMode::GetShapeHelp(Mode->CollisionBrush); }))
		]);
}

// ---------------------------------------------------------------------
//  5. Atlas
// ---------------------------------------------------------------------
int32 SFramework2DTilePalette::GetEffectiveZoom() const
{
	if (Zoom > 0) { return Zoom; }
	// Automatico: que el atlas quepa en unos 340 px de ancho (panel de 400).
	int32 W = 0, H = 0;
	const UFramework2DTileSet* Set = Mode->GetTileSet();
	if (!Set || !Set->GetPageSize(Mode->ActivePage, W, H) || W <= 0) { return 3; }
	return FMath::Clamp(340 / W, 1, 8);
}

void SFramework2DTilePalette::SetZoom(int32 NewZoom)
{
	Zoom = FMath::Clamp(NewZoom, 1, F2DPalette::MaxZoom);
}

FText SFramework2DTilePalette::GetSelectionText() const
{
	const UFramework2DTileSet* Set = Mode->GetTileSet();
	if (!Set) { return FText::GetEmpty(); }
	if (Mode->IsGeneratorBrush())
	{
		if (const FFramework2DGenerator* Generator = Mode->GetGenerator(Mode->BrushGeneratorId))
		{
			return FText::Format(LOCTEXT("SelGenerator", "Brush: generator «{0}». Paint it on the cells where you want vegetation; its sprites are marked in the atlas."),
				FText::FromName(Generator->Name));
		}
	}
	if (Mode->IsFlipbookBrush())
	{
		const int32 Index = Set->FindFlipbookIndex(Mode->BrushFlipbookId);
		if (Index != INDEX_NONE)
		{
			const FFramework2DFlipbook& Flipbook = Set->Flipbooks[Index];
			return FText::Format(LOCTEXT("SelFlipbook", "Brush: flipbook «{0}» ({1} {1}|plural(one=frame,other=frames)). Its frames are marked in the atlas."),
				FText::FromName(Flipbook.Name), Flipbook.Frames.Num());
		}
	}
	const int32 W = Mode->BrushWidth();
	const int32 H = Mode->BrushHeight();
	if (W * H > 1)
	{
		return FText::Format(LOCTEXT("SelBlock", "Block of {0} × {1} tiles: stamped whole and repeated when dragging, with the bucket and with the rectangle."),
			FText::AsNumber(W), FText::AsNumber(H));
	}
	const FText Material = F2DPalette::MaterialLabel(Set->GetTileMaterial(Mode->SelectedTile));
	const int32 Page = Framework2D::TilePageOf(Mode->SelectedTile);
	if (Page != 0)
	{
		return FText::Format(LOCTEXT("SelPageTile", "{0} · tile {1} · material: {2}"), Set->GetPageDisplayName(Page),
			FText::AsNumber(Framework2D::TileLocalOf(Mode->SelectedTile)), Material);
	}
	return FText::Format(LOCTEXT("SelTile", "Tile {0} · material: {1}"), FText::AsNumber(Framework2D::TileLocalOf(Mode->SelectedTile)), Material);
}

void SFramework2DTilePalette::RefreshMaterialOptions()
{
	// "Ninguno" + los materiales del TileSet. Solo se rehace si cambiaron (asi la seleccion
	// del desplegable sigue apuntando a objetos validos).
	TArray<FName> Names;
	Names.Add(NAME_None);
	if (const UFramework2DTileSet* Set = Mode->GetTileSet())
	{
		for (const FFramework2DMaterial& Material : Set->Materials)
		{
			if (!Material.Name.IsNone()) { Names.AddUnique(Material.Name); }
		}
	}
	bool bSame = Names.Num() == MaterialOptions.Num();
	for (int32 I = 0; bSame && I < Names.Num(); ++I)
	{
		bSame = MaterialOptions[I].IsValid() && *MaterialOptions[I] == Names[I];
	}
	if (bSame) { return; }

	MaterialOptions.Reset();
	for (const FName& Name : Names)
	{
		MaterialOptions.Add(MakeShared<FName>(Name));
	}
	if (MaterialCombo.IsValid())
	{
		MaterialCombo->RefreshOptions();
	}
}

void SFramework2DTilePalette::SyncComboSelections()
{
	// Lo que marca el propio panel no es una eleccion del usuario.
	TGuardValue<bool> Guard(bSyncingCombos, true);
	// El desplegable marca el valor actual (o nada si hay mezcla): asi elegir otra vez el
	// mismo valor no hace nada y elegir uno distinto siempre aplica.
	if (MaterialCombo.IsValid())
	{
		bool bMixed = false;
		const FName Current = Mode->GetSelectionMaterial(bMixed);
		TSharedPtr<FName> Match;
		for (const TSharedPtr<FName>& Option : MaterialOptions)
		{
			if (!bMixed && Option.IsValid() && *Option == Current) { Match = Option; break; }
		}
		if (Match.IsValid()) { MaterialCombo->SetSelectedItem(Match); }
		else { MaterialCombo->ClearSelection(); }
	}
	if (CollisionCombo.IsValid())
	{
		bool bMixed = false;
		const EFramework2DCollisionShape Current = Mode->GetSelectionCollision(bMixed);
		TSharedPtr<EFramework2DCollisionShape> Match;
		for (const TSharedPtr<EFramework2DCollisionShape>& Option : ShapeOptions)
		{
			if (!bMixed && Option.IsValid() && *Option == Current) { Match = Option; break; }
		}
		if (Match.IsValid()) { CollisionCombo->SetSelectedItem(Match); }
		else { CollisionCombo->ClearSelection(); }
	}
}

TSharedRef<SWidget> SFramework2DTilePalette::MakeSelectionProperties()
{
	auto Label = [](const FText& InText) -> TSharedRef<SWidget>
	{
		return SNew(SBox)
			.WidthOverride(64.0f)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.TextStyle(&F2DPalette::Text("F2D.Text.Body"))
				.ColorAndOpacity(FFramework2DEditorStyle::ForegroundDim())
				.Text(InText)
			];
	};

	SAssignNew(MaterialCombo, SComboBox<TSharedPtr<FName>>)
		.OptionsSource(&MaterialOptions)
		.ToolTipText(LOCTEXT("MaterialComboTip", "Terrain material of the selection (atlas tiles or flipbook): decides how it breaks, whether it collides and what is collected. «None» = not terrain."))
		.OnComboBoxOpening_Lambda([this]()
		{
			RefreshMaterialOptions();
			SyncComboSelections();
		})
		.OnGenerateWidget_Lambda([](TSharedPtr<FName> Item) -> TSharedRef<SWidget>
		{
			return SNew(STextBlock).Text(F2DPalette::MaterialLabel(Item.IsValid() ? *Item : FName(NAME_None)));
		})
		.OnSelectionChanged_Lambda([this](TSharedPtr<FName> Item, ESelectInfo::Type Info)
		{
			// Direct = lo pone el propio panel al sincronizar; solo aplica lo que elige el usuario.
			if (Item.IsValid() && !bSyncingCombos) { Mode->SetSelectionMaterial(*Item); }
		})
		[
			SNew(STextBlock)
			.Text_Lambda([this]()
			{
				bool bMixed = false;
				const FName Material = Mode->GetSelectionMaterial(bMixed);
				return bMixed ? LOCTEXT("MixedMaterial", "Several") : F2DPalette::MaterialLabel(Material);
			})
		];

	SAssignNew(CollisionCombo, SComboBox<TSharedPtr<EFramework2DCollisionShape>>)
		.OptionsSource(&ShapeOptions)
		.ToolTipText(LOCTEXT("CollisionComboTip", "Collision of the selection in every map. Cell by cell it is changed with the Collision brush, which wins over this."))
		.OnComboBoxOpening_Lambda([this]() { SyncComboSelections(); })
		.OnGenerateWidget_Lambda([](TSharedPtr<EFramework2DCollisionShape> Item) -> TSharedRef<SWidget>
		{
			const EFramework2DCollisionShape Shape = Item.IsValid() ? *Item : EFramework2DCollisionShape::Auto;
			return SNew(SHorizontalBox)
				.ToolTipText(FFramework2DTilePaintMode::GetShapeHelp(Shape))
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(0.0f, 2.0f, 8.0f, 2.0f)
				[
					SNew(SFramework2DShapeGlyph)
					.Shape(Shape)
					.Size(16.0f)
				]
				+ SHorizontalBox::Slot()
				.FillWidth(1.0f)
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock).Text(FFramework2DTilePaintMode::GetShapeName(Shape))
				];
		})
		.OnSelectionChanged_Lambda([this](TSharedPtr<EFramework2DCollisionShape> Item, ESelectInfo::Type Info)
		{
			if (Item.IsValid() && !bSyncingCombos) { Mode->SetSelectionCollision(*Item); }
		})
		[
			SNew(STextBlock)
			.Text_Lambda([this]()
			{
				bool bMixed = false;
				const EFramework2DCollisionShape Shape = Mode->GetSelectionCollision(bMixed);
				return bMixed ? LOCTEXT("MixedCollision", "Several") : FFramework2DTilePaintMode::GetShapeName(Shape);
			})
		];

	return SNew(SVerticalBox)
		.IsEnabled_Lambda([this]() { return Mode->GetTileSet() != nullptr; })
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 10.0f, 0.0f, 6.0f)
		[
			SNew(STextBlock)
			.TextStyle(&F2DPalette::Text("F2D.Text.Section"))
			.Text_Lambda([this]()
			{
				return (Mode->IsGeneratorBrush()
					? LOCTEXT("PropsGenerator", "Generator properties")
					: Mode->IsFlipbookBrush()
					? LOCTEXT("PropsFlipbook", "Flipbook properties")
					: LOCTEXT("PropsSelection", "Selection properties")).ToUpper();
			})
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().AutoWidth() [ Label(LOCTEXT("MaterialLabel", "Material")) ]
			+ SHorizontalBox::Slot().FillWidth(1.0f) [ MaterialCombo.ToSharedRef() ]
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 4.0f, 0.0f, 0.0f)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().AutoWidth() [ Label(LOCTEXT("CollisionLabel", "Collision")) ]
			+ SHorizontalBox::Slot().FillWidth(1.0f) [ CollisionCombo.ToSharedRef() ]
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 6.0f, 0.0f, 0.0f)
		[
			F2DPalette::Caption(LOCTEXT("PropsHelp", "Saved in the Tile Set: they apply to every map that uses it."))
		];
}

TSharedRef<SWidget> SFramework2DTilePalette::MakeAtlasCard()
{
	auto HasAtlas = [this]()
	{
		const UFramework2DTileSet* Set = Mode->GetTileSet();
		int32 W = 0, H = 0;
		return Set && Set->GetPageTexture(Mode->ActivePage) && Set->GetPageSize(Mode->ActivePage, W, H);
	};

	TSharedRef<SHorizontalBox> ZoomControls = SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			F2DPalette::IconButton("F2D.Icon.ZoomOut", LOCTEXT("ZoomOutTip", "Zoom the atlas out"),
				FOnClicked::CreateLambda([this]() { SetZoom(GetEffectiveZoom() - 1); return FReply::Handled(); }),
				TAttribute<bool>::CreateLambda([this, HasAtlas]() { return HasAtlas() && GetEffectiveZoom() > 1; }))
		]
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		[
			SNew(SBox)
			.MinDesiredWidth(30.0f)
			.HAlign(HAlign_Center)
			[
				SNew(STextBlock)
				.TextStyle(&F2DPalette::Text("F2D.Text.Body"))
				.ToolTipText(LOCTEXT("ZoomValueTip", "Atlas zoom: screen pixels per atlas pixel."))
				.Text_Lambda([this]() { return FText::Format(LOCTEXT("ZoomValue", "{0}×"), FText::AsNumber(GetEffectiveZoom())); })
			]
		]
		+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			F2DPalette::IconButton("F2D.Icon.ZoomIn", LOCTEXT("ZoomInTip", "Zoom the atlas in"),
				FOnClicked::CreateLambda([this]() { SetZoom(GetEffectiveZoom() + 1); return FReply::Handled(); }),
				TAttribute<bool>::CreateLambda([this, HasAtlas]() { return HasAtlas() && GetEffectiveZoom() < F2DPalette::MaxZoom; }))
		];

	return F2DPalette::Card(
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			F2DPalette::CardHeader("F2D.Icon.Grid", LOCTEXT("AtlasTitle", "Atlas"), ZoomControls)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 2.0f, 0.0f, 8.0f)
		[
			F2DPalette::Caption(LOCTEXT("AtlasHelp", "Click: one tile · Drag: a block (stamped whole). Tiles with no material are dimmed. Each tab is another image (another environment)."))
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			MakePageControls()
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SBorder)
			.BorderImage(F2DPalette::Brush("F2D.Row"))
			.Padding(FMargin(4.0f))
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					// La rueda del raton sigue moviendo el panel; el atlas ancho se desplaza con la barra.
					SNew(SScrollBox)
					.Orientation(Orient_Horizontal)
					.ConsumeMouseWheel(EConsumeMouseWheel::Never)
					.Visibility_Lambda([HasAtlas]() { return HasAtlas() ? EVisibility::Visible : EVisibility::Collapsed; })
					+ SScrollBox::Slot()
					[
						SNew(SFramework2DAtlasPicker, Mode)
						.Zoom_Lambda([this]() { return GetEffectiveZoom(); })
					]
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(FMargin(6.0f, 10.0f))
				[
					SNew(STextBlock)
					.TextStyle(&F2DPalette::Text("F2D.Text.Caption"))
					.AutoWrapText(true)
					.Text(LOCTEXT("NoAtlasYet", "This atlas has no image yet: choose it above (or in the Tile Set, with the tile size)."))
					.Visibility_Lambda([HasAtlas]() { return HasAtlas() ? EVisibility::Collapsed : EVisibility::Visible; })
				]
			]
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 8.0f, 0.0f, 0.0f)
		[
			SNew(STextBlock)
			.TextStyle(&F2DPalette::Text("F2D.Text.Body"))
			.AutoWrapText(true)
			.Text(this, &SFramework2DTilePalette::GetSelectionText)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			MakeSelectionProperties()
		]);
}

// ---------------------------------------------------------------------
//  6. Flipbooks
// ---------------------------------------------------------------------
TSharedRef<SWidget> SFramework2DTilePalette::MakeFlipbooksCard()
{
	TSharedRef<SWidget> NewButton = SNew(SButton)
		.ButtonStyle(&F2DPalette::Button("F2D.Button.Primary"))
		.ContentPadding(FMargin(0.0f))
		.VAlign(VAlign_Center)
		.IsEnabled_Lambda([this]() { return Mode->CanCreateFlipbook(); })
		.ToolTipText(LOCTEXT("NewFlipbookTip", "Select the frames in the atlas (in reading order) and press. No tile is changed."))
		.OnClicked_Lambda([this]()
		{
			Mode->CreateFlipbookFromSelection();
			F2DPalette::RedrawViewports();
			return FReply::Handled();
		})
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			[
				SNew(SImage)
				.Image(F2DPalette::Brush("F2D.Icon.Add"))
				.ColorAndOpacity(FSlateColor::UseForeground())
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(5.0f, 0.0f, 0.0f, 0.0f)
			[
				SNew(STextBlock)
				.TextStyle(&F2DPalette::Text("F2D.Text.OnAccent"))
				.ColorAndOpacity(FSlateColor::UseForeground())
				.Text(LOCTEXT("NewFlipbook", "New from selection"))
			]
		];

	return F2DPalette::Card(
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			F2DPalette::CardHeader("F2D.Icon.Flipbook", LOCTEXT("FlipbooksTitle", "Flipbooks"), NewButton)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 4.0f, 0.0f, 8.0f)
		[
			F2DPalette::Caption(LOCTEXT("FlipbooksHelp", "Animated tiles. They live apart from the atlas: creating them changes no tile. Click: paint with it · Double click: rename."))
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SAssignNew(FlipbooksBox, SVerticalBox)
		]);
}

void SFramework2DTilePalette::RebuildFlipbooks()
{
	FlipbooksBox->ClearChildren();
	const UFramework2DTileSet* Set = Mode->GetTileSet();
	if (!Set || Set->Flipbooks.Num() == 0)
	{
		// Estado vacio: que hacer para tener el primero.
		FlipbooksBox->AddSlot()
			.AutoHeight()
			[
				SNew(SBorder)
				.BorderImage(F2DPalette::Brush("F2D.Row"))
				.Padding(FMargin(12.0f, 14.0f))
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					.AutoHeight()
					.HAlign(HAlign_Center)
					.Padding(0.0f, 0.0f, 0.0f, 6.0f)
					[
						SNew(SImage)
						.Image(F2DPalette::Brush("F2D.Icon.Flipbook"))
						.ColorAndOpacity(FFramework2DEditorStyle::ForegroundDim())
					]
					+ SVerticalBox::Slot()
					.AutoHeight()
					[
						SNew(STextBlock)
						.TextStyle(&F2DPalette::Text("F2D.Text.Caption"))
						.AutoWrapText(true)
						.Justification(ETextJustify::Center)
						.Text(Set
							? LOCTEXT("NoFlipbooks", "No flipbooks yet. Select their frames in the atlas (in reading order) and press «New from selection».")
							: LOCTEXT("NoFlipbooksNoSet", "No Tile Set yet: flipbooks are saved in it."))
					]
				]
			];
		return;
	}

	for (const FFramework2DFlipbook& Flipbook : Set->Flipbooks)
	{
		FlipbooksBox->AddSlot()
			.AutoHeight()
			.Padding(0.0f, 0.0f, 0.0f, 2.0f)
			[
				MakeFlipbookRow(Flipbook.Id)
			];
	}
}

TSharedRef<SWidget> SFramework2DTilePalette::MakeFlipbookRow(int32 FlipbookId)
{
	FFramework2DTilePaintMode* M = Mode;
	auto Find = [M, FlipbookId]() -> const FFramework2DFlipbook*
	{
		const UFramework2DTileSet* Set = M->GetTileSet();
		const int32 Index = Set ? Set->FindFlipbookIndex(FlipbookId) : INDEX_NONE;
		return Index != INDEX_NONE ? &Set->Flipbooks[Index] : nullptr;
	};
	auto IsActive = [M, FlipbookId]() { return M->IsFlipbookBrush() && M->BrushFlipbookId == FlipbookId; };
	const TSharedRef<F2DPalette::FSpinDrag> FpsDrag = MakeShared<F2DPalette::FSpinDrag>();

	TSharedPtr<SInlineEditableTextBlock> NameBlock;
	TSharedRef<SFramework2DListRow> Row = SNew(SFramework2DListRow)
		.IsActive_Lambda(IsActive)
		.OnSelected_Lambda([M, FlipbookId]() { M->SelectFlipbook(FlipbookId); F2DPalette::RedrawViewports(); })
		[
			SNew(SHorizontalBox)
			// Barra de acento del flipbook que es el pincel.
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SBox)
				.WidthOverride(3.0f)
				.Padding(FMargin(0.0f, 10.0f))
				[
					SNew(SImage)
					.Image(F2DPalette::Brush("F2D.AccentBar"))
					.Visibility_Lambda([IsActive]() { return IsActive() ? EVisibility::Visible : EVisibility::Hidden; })
				]
			]
			// Miniatura animada.
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(5.0f, 5.0f, 8.0f, 5.0f)
			[
				SNew(SFramework2DTileThumb, M, [M, FlipbookId]()
				{
					const UFramework2DTileSet* S = M->GetTileSet();
					return FIntVector(S ? S->GetFrameTile(Framework2D::MakeFlipbookValue(FlipbookId), FPlatformTime::Seconds()) : -1, 1, 1);
				})
				.bAnimated(true)
				.ToolTipText(LOCTEXT("ThumbTip", "Animated preview, at its frames per second."))
			]
			// Nombre e informacion.
			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			.VAlign(VAlign_Center)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SAssignNew(NameBlock, SInlineEditableTextBlock)
					.ToolTipText(LOCTEXT("FlipbookNameTip", "Click: paint with this flipbook. Double click or F2: rename."))
					.Text_Lambda([Find]()
					{
						const FFramework2DFlipbook* Flipbook = Find();
						return Flipbook ? FText::FromName(Flipbook->Name) : FText::GetEmpty();
					})
					.Font_Lambda([IsActive]() { return F2DPalette::Font(IsActive(), 9); })
					.ColorAndOpacity(FFramework2DEditorStyle::Foreground())
					.OnVerifyTextChanged_Lambda([](const FText& InText, FText& OutError) { return F2DPalette::VerifyName(InText, OutError); })
					.OnTextCommitted_Lambda([M, FlipbookId](const FText& NewText, ETextCommit::Type Commit)
					{
						if (Commit != ETextCommit::OnCleared) { M->RenameFlipbook(FlipbookId, NewText); }
					})
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(0.0f, 2.0f, 0.0f, 0.0f)
				[
					SNew(STextBlock)
					.TextStyle(&F2DPalette::Text("F2D.Text.Caption"))
					.OverflowPolicy(ETextOverflowPolicy::Ellipsis)
					.Text_Lambda([Find]()
					{
						const FFramework2DFlipbook* Flipbook = Find();
						if (!Flipbook) { return FText::GetEmpty(); }
						const FText Material = Flipbook->MaterialName.IsNone() ? LOCTEXT("FlipbookNoMaterial", "no material") : FText::FromName(Flipbook->MaterialName);
						return FText::Format(LOCTEXT("FlipbookInfo", "{0} {0}|plural(one=frame,other=frames) · {1}"), Flipbook->Frames.Num(), Material);
					})
				]
			]
			// Fotogramas por segundo: se guarda al soltar o al escribirlo (un paso de deshacer).
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(6.0f, 0.0f, 0.0f, 0.0f)
			[
				SNew(SBox)
				.WidthOverride(52.0f)
				[
					SNew(SSpinBox<float>)
					.MinValue(0.1f)
					.MaxValue(60.0f)
					.MinSliderValue(0.1f)
					.MaxSliderValue(60.0f)
					.Delta(0.5f)
					.MaxFractionalDigits(1)
					.ToolTipText(LOCTEXT("FpsTip", "Frames per second (0.1 to 60)."))
					.Value_Lambda([Find, FpsDrag]()
					{
						if (FpsDrag->bDragging) { return FpsDrag->Value; }
						const FFramework2DFlipbook* Flipbook = Find();
						return Flipbook ? Flipbook->FPS : 8.0f;
					})
					.OnBeginSliderMovement_Lambda([Find, FpsDrag]()
					{
						const FFramework2DFlipbook* Flipbook = Find();
						FpsDrag->bDragging = true;
						FpsDrag->Value = Flipbook ? Flipbook->FPS : 8.0f;
					})
					.OnValueChanged_Lambda([FpsDrag](float NewValue)
					{
						if (FpsDrag->bDragging) { FpsDrag->Value = NewValue; }
					})
					.OnEndSliderMovement_Lambda([M, FlipbookId, Find, FpsDrag](float NewValue)
					{
						FpsDrag->bDragging = false;
						const FFramework2DFlipbook* Flipbook = Find();
						if (Flipbook && !FMath::IsNearlyEqual(Flipbook->FPS, NewValue)) { M->SetFlipbookFPS(FlipbookId, NewValue); }
					})
					.OnValueCommitted_Lambda([M, FlipbookId, Find, FpsDrag](float NewValue, ETextCommit::Type)
					{
						const FFramework2DFlipbook* Flipbook = Find();
						if (!FpsDrag->bDragging && Flipbook && !FMath::IsNearlyEqual(Flipbook->FPS, NewValue)) { M->SetFlipbookFPS(FlipbookId, NewValue); }
					})
				]
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(4.0f, 0.0f, 4.0f, 0.0f)
			[
				SNew(STextBlock)
				.TextStyle(&F2DPalette::Text("F2D.Text.Caption"))
				.Text(LOCTEXT("FpsUnit", "fps"))
			]
			// Reemplazar fotogramas y borrar.
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			[
				F2DPalette::IconButton("F2D.Icon.Replace",
					TAttribute<FText>::CreateLambda([M]()
					{
						return M->IsSpecialBrush()
							? LOCTEXT("ReplaceFramesOffTip", "Replace frames: first select the new ones in the atlas (in reading order).")
							: LOCTEXT("ReplaceFramesTip", "Replace its frames with the current atlas selection (in reading order).");
					}),
					FOnClicked::CreateLambda([M, FlipbookId]() { M->SetFlipbookFramesFromSelection(FlipbookId); return FReply::Handled(); }),
					TAttribute<bool>::CreateLambda([M]() { return !M->IsSpecialBrush() && M->GetTileSet() != nullptr; }))
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(2.0f, 0.0f, 6.0f, 0.0f)
			[
				F2DPalette::IconButton("F2D.Icon.Trash",
					LOCTEXT("DeleteFlipbookTip", "Delete the flipbook. The map cells that use it become empty (Ctrl+Z undoes it)."),
					FOnClicked::CreateLambda([M, FlipbookId]()
					{
						M->DeleteFlipbook(FlipbookId);
						F2DPalette::RedrawViewports();
						return FReply::Handled();
					}),
					TAttribute<bool>(true),
					&F2DPalette::DangerIconButtonStyle())
			]
		];

	Row->SetRenameTarget(NameBlock);
	return Row;
}

// ---------------------------------------------------------------------
//  5b. Paginas del atlas (pestanas + imagen de la pagina activa)
// ---------------------------------------------------------------------
uint32 SFramework2DTilePalette::ComputePagesSignature() const
{
	const UFramework2DTileSet* Set = Mode->GetTileSet();
	uint32 H = GetTypeHash(Set);
	H = HashCombine(H, GetTypeHash(Set ? Set->GetNumPages() : -1));
	if (Set)
	{
		for (int32 P = 0; P < Set->GetNumPages(); ++P) { H = HashCombine(H, GetTypeHash(Set->GetPageIdAt(P))); }
	}
	return H;
}

void SFramework2DTilePalette::RebuildPageTabs()
{
	PageTabsBox->ClearChildren();
	const UFramework2DTileSet* Set = Mode->GetTileSet();
	if (!Set) { return; }
	Mode->SetActivePage(Mode->ActivePage); // la pagina activa puede haber desaparecido (deshacer)

	FFramework2DTilePaintMode* M = Mode;
	for (int32 P = 0; P < Set->GetNumPages(); ++P)
	{
		const int32 PageId = Set->GetPageIdAt(P);
		TSharedRef<SButton> Tab = SNew(SButton)
			.ButtonStyle(&F2DPalette::Button("F2D.Button.Secondary"))
			.ContentPadding(FMargin(10.0f, 4.0f))
			.ToolTipText(LOCTEXT("PageTabTip", "Show this atlas in the palette. Each tab is an image of the Tile Set."))
			.OnClicked_Lambda([M, PageId]()
			{
				M->SetActivePage(PageId);
				return FReply::Handled();
			})
			[
				SNew(STextBlock)
				.Font(F2DPalette::Font(false, 9))
				.ColorAndOpacity(FSlateColor::UseForeground())
				.Text_Lambda([M, PageId]()
				{
					const UFramework2DTileSet* S = M->GetTileSet();
					return S ? S->GetPageDisplayName(PageId) : FText::GetEmpty();
				})
			];
		RegisterStatefulButton(Tab, [M, PageId]() { return M->ActivePage == PageId; },
			&F2DPalette::Button("F2D.Button.Secondary"), &F2DPalette::Button("F2D.Button.ToolActive"));
		PageTabsBox->AddSlot()
			.AutoWidth()
			.Padding(0.0f, 0.0f, 3.0f, 0.0f)
			[
				Tab
			];
	}
	PageTabsBox->AddSlot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		[
			F2DPalette::IconButton("F2D.Icon.Add",
				LOCTEXT("AddPageTip", "Add another atlas (another image, for another environment). Then choose its image below. Its tiles must be the same size as the main atlas's."),
				FOnClicked::CreateLambda([M]() { M->AddAtlasPage(nullptr); return FReply::Handled(); }),
				TAttribute<bool>::CreateLambda([M]() { const UFramework2DTileSet* S = M->GetTileSet(); return S && S->GetNumPages() < Framework2D::MaxAtlasPages; }))
		];
}

TSharedRef<SWidget> SFramework2DTilePalette::MakePageControls()
{
	FFramework2DTilePaintMode* M = Mode;
	auto IsExtra = [M]() { return M->ActivePage != 0 && M->GetTileSet() != nullptr; };
	auto Label = [](const FText& InText) -> TSharedRef<SWidget>
	{
		return SNew(SBox)
			.WidthOverride(64.0f)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.TextStyle(&F2DPalette::Text("F2D.Text.Body"))
				.ColorAndOpacity(FFramework2DEditorStyle::ForegroundDim())
				.Text(InText)
			];
	};

	return SNew(SVerticalBox)
		.Visibility_Lambda([M]() { return M->GetTileSet() ? EVisibility::Visible : EVisibility::Collapsed; })
		// Pestanas (se desplazan si no caben).
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 0.0f, 0.0f, 6.0f)
		[
			SNew(SScrollBox)
			.Orientation(Orient_Horizontal)
			.ConsumeMouseWheel(EConsumeMouseWheel::Never)
			+ SScrollBox::Slot()
			[
				SAssignNew(PageTabsBox, SHorizontalBox)
			]
		]
		// Imagen de la pagina activa.
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 0.0f, 0.0f, 4.0f)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().AutoWidth() [ Label(LOCTEXT("PageImage", "Image")) ]
			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			[
				SNew(SObjectPropertyEntryBox)
				.AllowedClass(UTexture2D::StaticClass())
				.DisplayThumbnail(false)
				.ThumbnailPool(UThumbnailManager::Get().GetSharedThumbnailPool())
				.ToolTipText(LOCTEXT("PageImageTip", "This atlas's image (tiles in a grid, no margins, the same size as the main atlas's)."))
				.ObjectPath_Lambda([M]() -> FString
				{
					const UFramework2DTileSet* S = M->GetTileSet();
					const UTexture2D* Texture = S ? S->GetPageTexture(M->ActivePage) : nullptr;
					return Texture ? Texture->GetPathName() : FString();
				})
				.OnObjectChanged_Lambda([M](const FAssetData& Asset)
				{
					M->SetPageTexture(M->ActivePage, Cast<UTexture2D>(Asset.GetAsset()));
				})
			]
		]
		// Nombre y quitar (solo los atlas extra; el principal es el del Tile Set).
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SHorizontalBox)
			.Visibility_Lambda([IsExtra]() { return IsExtra() ? EVisibility::Visible : EVisibility::Collapsed; })
			+ SHorizontalBox::Slot().AutoWidth() [ Label(LOCTEXT("PageName", "Name")) ]
			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			.VAlign(VAlign_Center)
			[
				SNew(SEditableTextBox)
				.ToolTipText(LOCTEXT("PageNameTip", "Tab name (for example: Cave, Forest, Vegetation)."))
				.Text_Lambda([M]()
				{
					const UFramework2DTileSet* S = M->GetTileSet();
					return S ? S->GetPageDisplayName(M->ActivePage) : FText::GetEmpty();
				})
				.OnTextCommitted_Lambda([M](const FText& NewText, ETextCommit::Type) { M->RenamePage(M->ActivePage, NewText); })
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(4.0f, 0.0f, 0.0f, 0.0f)
			[
				F2DPalette::IconButton("F2D.Icon.Trash",
					LOCTEXT("RemovePageTip", "Remove this atlas from the Tile Set. The map cells that use its tiles become empty (Ctrl+Z undoes it)."),
					FOnClicked::CreateLambda([M]()
					{
						M->RemoveAtlasPage(M->ActivePage);
						F2DPalette::RedrawViewports();
						return FReply::Handled();
					}),
					TAttribute<bool>(true),
					&F2DPalette::DangerIconButtonStyle())
			]
		];
}

// ---------------------------------------------------------------------
//  7. Generadores de vegetacion
// ---------------------------------------------------------------------
const FFramework2DGenerator* SFramework2DTilePalette::GetEditedGenerator() const
{
	return EditedGeneratorId != INDEX_NONE ? Mode->GetGenerator(EditedGeneratorId) : nullptr;
}

uint32 SFramework2DTilePalette::ComputeGeneratorsSignature() const
{
	const UFramework2DTileSet* Set = Mode->GetTileSet();
	uint32 H = GetTypeHash(Set);
	H = HashCombine(H, GetTypeHash(Set ? Set->Generators.Num() : -1));
	if (Set)
	{
		for (const FFramework2DGenerator& Generator : Set->Generators) { H = HashCombine(H, GetTypeHash(Generator.Id)); }
	}
	// La tira de sprites del generador que se ajusta.
	H = HashCombine(H, GetTypeHash(EditedGeneratorId));
	if (const FFramework2DGenerator* Edited = GetEditedGenerator())
	{
		for (const FFramework2DScatterSprite& Sprite : Edited->Sprites)
		{
			H = HashCombine(H, GetTypeHash(Sprite.Tile));
			H = HashCombine(H, GetTypeHash(Sprite.WidthInTiles * 100 + Sprite.HeightInTiles));
		}
	}
	return H;
}

TSharedRef<SWidget> SFramework2DTilePalette::MakeGeneratorsCard()
{
	TSharedRef<SWidget> NewButton = SNew(SButton)
		.ButtonStyle(&F2DPalette::Button("F2D.Button.Primary"))
		.ContentPadding(FMargin(0.0f))
		.VAlign(VAlign_Center)
		.IsEnabled_Lambda([this]() { return Mode->GetTileSet() != nullptr; })
		.ToolTipText(LOCTEXT("NewGeneratorTip", "Creates a generator with the tiles selected in the atlas as sprites (one per tile). Then paint with it on any layer."))
		.OnClicked_Lambda([this]()
		{
			EditedGeneratorId = Mode->CreateGeneratorFromSelection();
			F2DPalette::RedrawViewports();
			return FReply::Handled();
		})
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			[
				SNew(SImage)
				.Image(F2DPalette::Brush("F2D.Icon.Add"))
				.ColorAndOpacity(FSlateColor::UseForeground())
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(5.0f, 0.0f, 0.0f, 0.0f)
			[
				SNew(STextBlock)
				.TextStyle(&F2DPalette::Text("F2D.Text.OnAccent"))
				.ColorAndOpacity(FSlateColor::UseForeground())
				.Text(LOCTEXT("NewGenerator", "New from selection"))
			]
		];

	return F2DPalette::Card(
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			F2DPalette::CardHeader("F2D.Icon.Generator", LOCTEXT("GeneratorsTitle", "Generators"), NewButton)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 4.0f, 0.0f, 8.0f)
		[
			F2DPalette::Caption(LOCTEXT("GeneratorsHelp", "Vegetation, rocks, mushrooms... Paint them on a cell of any layer: when baking they scatter their sprites with variation. What they generate breaks like the terrain."))
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SAssignNew(GeneratorsBox, SVerticalBox)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			MakeGeneratorEditor()
		]);
}

void SFramework2DTilePalette::RebuildGenerators()
{
	GeneratorsBox->ClearChildren();
	const UFramework2DTileSet* Set = Mode->GetTileSet();
	if (EditedGeneratorId != INDEX_NONE && !GetEditedGenerator()) { EditedGeneratorId = INDEX_NONE; }

	if (!Set || Set->Generators.Num() == 0)
	{
		GeneratorsBox->AddSlot()
			.AutoHeight()
			[
				SNew(SBorder)
				.BorderImage(F2DPalette::Brush("F2D.Row"))
				.Padding(FMargin(12.0f, 14.0f))
				[
					SNew(STextBlock)
					.TextStyle(&F2DPalette::Text("F2D.Text.Caption"))
					.AutoWrapText(true)
					.Justification(ETextJustify::Center)
					.Text(Set
						? LOCTEXT("NoGenerators", "No generators yet. Select in the atlas the plants or rocks you want and press «New from selection».")
						: LOCTEXT("NoGeneratorsNoSet", "No Tile Set yet: generators are saved in it."))
				]
			];
	}
	else
	{
		for (const FFramework2DGenerator& Generator : Set->Generators)
		{
			GeneratorsBox->AddSlot()
				.AutoHeight()
				.Padding(0.0f, 0.0f, 0.0f, 2.0f)
				[
					MakeGeneratorRow(Generator.Id)
				];
		}
	}

	// Tira de sprites del generador que se ajusta.
	if (!GeneratorSpritesBox.IsValid()) { return; }
	GeneratorSpritesBox->ClearChildren();
	const FFramework2DGenerator* Edited = GetEditedGenerator();
	if (!Edited) { return; }
	FFramework2DTilePaintMode* M = Mode;
	const int32 GeneratorId = EditedGeneratorId;
	for (int32 I = 0; I < Edited->Sprites.Num(); ++I)
	{
		const FFramework2DScatterSprite Sprite = Edited->Sprites[I];
		GeneratorSpritesBox->AddSlot()
			.Padding(0.0f, 0.0f, 4.0f, 4.0f)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SFramework2DTileThumb, M, [Sprite]() { return FIntVector(Sprite.Tile, Sprite.WidthInTiles, Sprite.HeightInTiles); })
					.Size(40.0f)
					.ToolTipText(FText::Format(LOCTEXT("SpriteTip", "Sprite {0}: {1} × {2} tiles · weight {3}. The weight is changed in the Tile Set (Generators › Sprites)."),
						FText::AsNumber(I + 1), FText::AsNumber(Sprite.WidthInTiles), FText::AsNumber(Sprite.HeightInTiles), FText::AsNumber(Sprite.Weight)))
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Center)
				[
					F2DPalette::IconButton("F2D.Icon.Remove",
						LOCTEXT("RemoveSpriteTip", "Remove this sprite from the generator."),
						FOnClicked::CreateLambda([M, GeneratorId, I]()
						{
							M->RemoveGeneratorSprite(GeneratorId, I);
							F2DPalette::RedrawViewports();
							return FReply::Handled();
						}),
						TAttribute<bool>(true),
						&F2DPalette::DangerIconButtonStyle())
				]
			];
	}
}

TSharedRef<SWidget> SFramework2DTilePalette::MakeGeneratorRow(int32 GeneratorId)
{
	FFramework2DTilePaintMode* M = Mode;
	auto Find = [M, GeneratorId]() { return M->GetGenerator(GeneratorId); };
	auto IsActive = [M, GeneratorId]() { return M->IsGeneratorBrush() && M->BrushGeneratorId == GeneratorId; };

	TSharedPtr<SInlineEditableTextBlock> NameBlock;
	TSharedRef<SFramework2DListRow> Row = SNew(SFramework2DListRow)
		.IsActive_Lambda(IsActive)
		.OnSelected_Lambda([this, M, GeneratorId]()
		{
			M->SelectGenerator(GeneratorId);
			EditedGeneratorId = GeneratorId;
			F2DPalette::RedrawViewports();
		})
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SBox)
				.WidthOverride(3.0f)
				.Padding(FMargin(0.0f, 10.0f))
				[
					SNew(SImage)
					.Image(F2DPalette::Brush("F2D.AccentBar"))
					.Visibility_Lambda([IsActive]() { return IsActive() ? EVisibility::Visible : EVisibility::Hidden; })
				]
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(5.0f, 5.0f, 8.0f, 5.0f)
			[
				SNew(SFramework2DTileThumb, M, [Find]()
				{
					const FFramework2DGenerator* Generator = Find();
					if (!Generator || Generator->Sprites.Num() == 0) { return FIntVector(-1, 1, 1); }
					const FFramework2DScatterSprite& First = Generator->Sprites[0];
					return FIntVector(First.Tile, First.WidthInTiles, First.HeightInTiles);
				})
				.ToolTipText(LOCTEXT("GeneratorThumbTip", "Its first sprite."))
			]
			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			.VAlign(VAlign_Center)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SAssignNew(NameBlock, SInlineEditableTextBlock)
					.ToolTipText(LOCTEXT("GeneratorNameTip", "Click: paint with this generator and adjust it below. Double click or F2: rename."))
					.Text_Lambda([Find]()
					{
						const FFramework2DGenerator* Generator = Find();
						return Generator ? FText::FromName(Generator->Name) : FText::GetEmpty();
					})
					.Font_Lambda([IsActive]() { return F2DPalette::Font(IsActive(), 9); })
					.ColorAndOpacity(FFramework2DEditorStyle::Foreground())
					.OnVerifyTextChanged_Lambda([](const FText& InText, FText& OutError) { return F2DPalette::VerifyName(InText, OutError); })
					.OnTextCommitted_Lambda([M, GeneratorId](const FText& NewText, ETextCommit::Type Commit)
					{
						if (Commit != ETextCommit::OnCleared) { M->RenameGenerator(GeneratorId, NewText); }
					})
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(0.0f, 2.0f, 0.0f, 0.0f)
				[
					SNew(STextBlock)
					.TextStyle(&F2DPalette::Text("F2D.Text.Caption"))
					.OverflowPolicy(ETextOverflowPolicy::Ellipsis)
					.Text_Lambda([Find]()
					{
						const FFramework2DGenerator* Generator = Find();
						if (!Generator) { return FText::GetEmpty(); }
						FNumberFormattingOptions OneDecimal;
						OneDecimal.MaximumFractionalDigits = 1;
						return FText::Format(LOCTEXT("GeneratorInfo", "{0} {0}|plural(one=sprite,other=sprites) · {1} per cell · {2}"),
							Generator->Sprites.Num(), FText::AsNumber(Generator->Density, &OneDecimal), F2DPalette::MaterialLabel(Generator->MaterialName));
					})
				]
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(2.0f, 0.0f, 6.0f, 0.0f)
			[
				F2DPalette::IconButton("F2D.Icon.Trash",
					LOCTEXT("DeleteGeneratorTip", "Delete the generator. The map cells that use it become empty (Ctrl+Z undoes it)."),
					FOnClicked::CreateLambda([M, GeneratorId]()
					{
						M->DeleteGenerator(GeneratorId);
						F2DPalette::RedrawViewports();
						return FReply::Handled();
					}),
					TAttribute<bool>(true),
					&F2DPalette::DangerIconButtonStyle())
			]
		];

	Row->SetRenameTarget(NameBlock);
	return Row;
}

TSharedRef<SWidget> SFramework2DTilePalette::MakeGeneratorSpin(const FText& Label, const FText& Tip, float Min, float Max, float Delta, int32 Digits,
	TFunction<float(const FFramework2DGenerator&)> Get, TFunction<void(FFramework2DGenerator&, float)> Set)
{
	// Se ve en vivo mientras se arrastra; se guarda (un paso de deshacer y un rehorneado) al soltar o al escribirlo.
	const TSharedRef<F2DPalette::FSpinDrag> Drag = MakeShared<F2DPalette::FSpinDrag>();
	FFramework2DTilePaintMode* M = Mode;
	auto Commit = [this, M, Set](float Value)
	{
		const int32 GeneratorId = EditedGeneratorId;
		M->ChangeGenerator(GeneratorId, LOCTEXT("GeneratorParam", "Adjust generator"), [&Set, Value](FFramework2DGenerator& Generator) { Set(Generator, Value); });
		F2DPalette::RedrawViewports();
	};

	return SNew(SHorizontalBox)
		.ToolTipText(Tip)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		[
			SNew(SBox)
			.WidthOverride(132.0f)
			[
				SNew(STextBlock)
				.TextStyle(&F2DPalette::Text("F2D.Text.Body"))
				.ColorAndOpacity(FFramework2DEditorStyle::ForegroundDim())
				.Text(Label)
			]
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.0f)
		[
			SNew(SSpinBox<float>)
			.MinValue(Min)
			.MaxValue(Max)
			.MinSliderValue(Min)
			.MaxSliderValue(Max)
			.Delta(Delta)
			.MinFractionalDigits(0)
			.MaxFractionalDigits(Digits)
			.Value_Lambda([this, Get, Drag]()
			{
				if (Drag->bDragging) { return Drag->Value; }
				const FFramework2DGenerator* Generator = GetEditedGenerator();
				return Generator ? Get(*Generator) : 0.0f;
			})
			.OnBeginSliderMovement_Lambda([this, Get, Drag]()
			{
				const FFramework2DGenerator* Generator = GetEditedGenerator();
				Drag->bDragging = true;
				Drag->Value = Generator ? Get(*Generator) : 0.0f;
			})
			.OnValueChanged_Lambda([Drag](float NewValue)
			{
				if (Drag->bDragging) { Drag->Value = NewValue; }
			})
			.OnEndSliderMovement_Lambda([Drag, Commit](float NewValue)
			{
				Drag->bDragging = false;
				Commit(NewValue);
			})
			.OnValueCommitted_Lambda([Drag, Commit](float NewValue, ETextCommit::Type)
			{
				if (!Drag->bDragging) { Commit(NewValue); }
			})
		];
}

TSharedRef<SWidget> SFramework2DTilePalette::MakeGeneratorColor(const FText& Label, const FText& Tip, bool bTintB)
{
	FFramework2DTilePaintMode* M = Mode;
	return SNew(SHorizontalBox)
		.ToolTipText(Tip)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		[
			SNew(SBox)
			.WidthOverride(132.0f)
			[
				SNew(STextBlock)
				.TextStyle(&F2DPalette::Text("F2D.Text.Body"))
				.ColorAndOpacity(FFramework2DEditorStyle::ForegroundDim())
				.Text(Label)
			]
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.0f)
		.VAlign(VAlign_Center)
		[
			SNew(SColorBlock)
			.Size(FVector2D(120.0f, 20.0f))
			.CornerRadius(FVector4(4.0f, 4.0f, 4.0f, 4.0f))
			.Color_Lambda([this, bTintB]()
			{
				const FFramework2DGenerator* Generator = GetEditedGenerator();
				return Generator ? (bTintB ? Generator->TintB : Generator->TintA) : FLinearColor::White;
			})
			.OnMouseButtonDown_Lambda([this, M, bTintB](const FGeometry&, const FPointerEvent& Event) -> FReply
			{
				const FFramework2DGenerator* Generator = GetEditedGenerator();
				if (!Generator || Event.GetEffectingButton() != EKeys::LeftMouseButton) { return FReply::Unhandled(); }
				const int32 GeneratorId = EditedGeneratorId;
				FColorPickerArgs Args;
				Args.bUseAlpha = false;
				Args.bOnlyRefreshOnOk = true; // un solo cambio (y un rehorneado) al pulsar OK
#if UE_VERSION_NEWER_THAN(5, 1, 99)
				Args.InitialColor = bTintB ? Generator->TintB : Generator->TintA;
#else
				Args.InitialColorOverride = bTintB ? Generator->TintB : Generator->TintA;
#endif
				Args.OnColorCommitted = FOnLinearColorValueChanged::CreateLambda([M, GeneratorId, bTintB](FLinearColor NewColor)
				{
					M->ChangeGenerator(GeneratorId, LOCTEXT("GeneratorTint", "Generator tint"), [bTintB, NewColor](FFramework2DGenerator& Generator)
					{
						(bTintB ? Generator.TintB : Generator.TintA) = NewColor;
					});
					F2DPalette::RedrawViewports();
				});
				OpenColorPicker(Args);
				return FReply::Handled();
			})
		];
}

TSharedRef<SWidget> SFramework2DTilePalette::MakeGeneratorEditor()
{
	FFramework2DTilePaintMode* M = Mode;
	auto Toggle = [this, M](FName Icon, const FText& Text, const FText& Tip, TFunction<bool(const FFramework2DGenerator&)> Get, TFunction<void(FFramework2DGenerator&, bool)> Set)
	{
		return F2DPalette::ToggleChip(Icon, Text, Tip,
			[this, Get]() { const FFramework2DGenerator* G = GetEditedGenerator(); return G && Get(*G); },
			[this, M, Set](bool bOn)
			{
				M->ChangeGenerator(EditedGeneratorId, LOCTEXT("GeneratorToggle", "Adjust generator"), [&Set, bOn](FFramework2DGenerator& G) { Set(G, bOn); });
				F2DPalette::RedrawViewports();
			});
	};
	auto AddButton = [M, this](const FText& Text, const FText& Tip, bool bAsOneSprite) -> TSharedRef<SWidget>
	{
		return SNew(SButton)
			.ButtonStyle(&F2DPalette::Button("F2D.Button.Secondary"))
			.ContentPadding(FMargin(8.0f, 4.0f))
			.ToolTipText(Tip)
			.IsEnabled_Lambda([M]()
			{
				TArray<int32> Values;
				M->GetSelectionTileValues(Values);
				return M->CanUseSelectionAsSprites() && Values.Num() > 0;
			})
			.OnClicked_Lambda([this, M, bAsOneSprite]()
			{
				M->AddSelectionToGenerator(EditedGeneratorId, bAsOneSprite);
				F2DPalette::RedrawViewports();
				return FReply::Handled();
			})
			[
				SNew(STextBlock)
				.Font(F2DPalette::Font(false, 8))
				.ColorAndOpacity(FSlateColor::UseForeground())
				.Text(Text)
			];
	};

	return SNew(SVerticalBox)
		.Visibility_Lambda([this]() { return GetEditedGenerator() ? EVisibility::Visible : EVisibility::Collapsed; })
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 10.0f, 0.0f, 6.0f)
		[
			SNew(STextBlock)
			.TextStyle(&F2DPalette::Text("F2D.Text.Section"))
			.Text_Lambda([this]()
			{
				const FFramework2DGenerator* Generator = GetEditedGenerator();
				return Generator ? FText::Format(LOCTEXT("GeneratorEditorTitle", "«{0}» settings"), FText::FromName(Generator->Name)).ToUpper() : FText::GetEmpty();
			})
		]
		// Sprites.
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SAssignNew(GeneratorSpritesBox, SWrapBox)
			.UseAllottedSize(true)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 2.0f, 0.0f, 8.0f)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.Padding(0.0f, 0.0f, 4.0f, 0.0f)
			[
				AddButton(LOCTEXT("AddEachTile", "+ Each tile"),
					LOCTEXT("AddEachTileTip", "Adds each tile selected in the atlas as a different sprite (grass variants, reeds...)."), false)
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				AddButton(LOCTEXT("AddAsOne", "+ Block as one sprite"),
					LOCTEXT("AddAsOneTip", "Adds the block selected in the atlas as a single large sprite (a 2×2 bush, a tree...)."), true)
			]
		]
		// Reparto.
		+ SVerticalBox::Slot().AutoHeight().Padding(0, 2)
		[
			MakeGeneratorSpin(LOCTEXT("Density", "Density"), LOCTEXT("DensityTip", "Sprites per cell (average). 0.5 = one every two cells; 3 = three per cell."),
				0.0f, 16.0f, 0.1f, 1, [](const FFramework2DGenerator& G) { return G.Density; }, [](FFramework2DGenerator& G, float V) { G.Density = V; })
		]
		+ SVerticalBox::Slot().AutoHeight().Padding(0, 2)
		[
			MakeGeneratorSpin(LOCTEXT("JitterX", "X variation (px)"), LOCTEXT("JitterXTip", "How far each sprite moves left or right, at random."),
				0.0f, 128.0f, 1.0f, 0, [](const FFramework2DGenerator& G) { return G.JitterX; }, [](FFramework2DGenerator& G, float V) { G.JitterX = V; })
		]
		+ SVerticalBox::Slot().AutoHeight().Padding(0, 2)
		[
			MakeGeneratorSpin(LOCTEXT("JitterY", "Y variation (px)"), LOCTEXT("JitterYTip", "How far each sprite moves up or down, at random."),
				0.0f, 128.0f, 1.0f, 0, [](const FFramework2DGenerator& G) { return G.JitterY; }, [](FFramework2DGenerator& G, float V) { G.JitterY = V; })
		]
		+ SVerticalBox::Slot().AutoHeight().Padding(0, 2)
		[
			MakeGeneratorSpin(LOCTEXT("OffsetY", "Sink into the ground (px)"), LOCTEXT("OffsetYTip", "Fixed downward offset (negative = upwards). 1 or 2 px make plants look planted."),
				-64.0f, 64.0f, 1.0f, 0, [](const FFramework2DGenerator& G) { return G.OffsetY; }, [](FFramework2DGenerator& G, float V) { G.OffsetY = V; })
		]
		+ SVerticalBox::Slot().AutoHeight().Padding(0, 2)
		[
			MakeGeneratorSpin(LOCTEXT("ScaleMin", "Min scale"), LOCTEXT("ScaleMinTip", "Minimum size of each sprite (1 = as in the atlas). With pixel art 1 or whole numbers look best."),
				0.1f, 8.0f, 0.05f, 2, [](const FFramework2DGenerator& G) { return G.ScaleMin; },
				[](FFramework2DGenerator& G, float V) { G.ScaleMin = V; G.ScaleMax = FMath::Max(G.ScaleMax, V); })
		]
		+ SVerticalBox::Slot().AutoHeight().Padding(0, 2)
		[
			MakeGeneratorSpin(LOCTEXT("ScaleMax", "Max scale"), LOCTEXT("ScaleMaxTip", "Maximum size of each sprite."),
				0.1f, 8.0f, 0.05f, 2, [](const FFramework2DGenerator& G) { return G.ScaleMax; },
				[](FFramework2DGenerator& G, float V) { G.ScaleMax = V; G.ScaleMin = FMath::Min(G.ScaleMin, V); })
		]
		// Color.
		+ SVerticalBox::Slot().AutoHeight().Padding(0, 6, 0, 2)
		[
			MakeGeneratorColor(LOCTEXT("TintA", "Tint A"), LOCTEXT("TintATip", "Each sprite is tinted with a random color between tint A and tint B. White = no tint."), false)
		]
		+ SVerticalBox::Slot().AutoHeight().Padding(0, 2)
		[
			MakeGeneratorColor(LOCTEXT("TintB", "Tint B"), LOCTEXT("TintBTip", "The other end of the random tint."), true)
		]
		+ SVerticalBox::Slot().AutoHeight().Padding(0, 2)
		[
			MakeGeneratorSpin(LOCTEXT("Brightness", "Brightness variation"), LOCTEXT("BrightnessTip", "How much lighter or darker each sprite can be (0.15 = 15 %)."),
				0.0f, 1.0f, 0.01f, 2, [](const FFramework2DGenerator& G) { return G.BrightnessVariation; }, [](FFramework2DGenerator& G, float V) { G.BrightnessVariation = V; })
		]
		// Suelo, volteo y semilla.
		+ SVerticalBox::Slot().AutoHeight().Padding(0, 6, 0, 2)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.Padding(0.0f, 0.0f, 4.0f, 0.0f)
			[
				Toggle("F2D.Icon.Collide", LOCTEXT("SnapToGround", "Rest on the ground"),
					LOCTEXT("SnapToGroundTip", "Each sprite drops to the first colliding ground below its point. If there is no ground nearby, it does not appear."),
					[](const FFramework2DGenerator& G) { return G.bSnapToGround; }, [](FFramework2DGenerator& G, bool bOn) { G.bSnapToGround = bOn; })
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				Toggle("F2D.Icon.Flip", LOCTEXT("RandomFlip", "Random flip"),
					LOCTEXT("RandomFlipTip", "Flips half of the sprites horizontally, at random."),
					[](const FFramework2DGenerator& G) { return G.bRandomFlip; }, [](FFramework2DGenerator& G, bool bOn) { G.bRandomFlip = bOn; })
			]
		]
		+ SVerticalBox::Slot().AutoHeight().Padding(0, 2)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				Toggle("F2D.Icon.Up", LOCTEXT("HangFromCeiling", "Hang from the ceiling"),
					LOCTEXT("HangFromCeilingTip", "Each sprite rises to the first colliding ceiling above its point and hangs from it (vines, roots, rocks under an island or ledge). Wins over «Rest on the ground»."),
					[](const FFramework2DGenerator& G) { return G.bHangFromCeiling; }, [](FFramework2DGenerator& G, bool bOn) { G.bHangFromCeiling = bOn; })
			]
		]
		+ SVerticalBox::Slot().AutoHeight().Padding(0, 2)
		[
			MakeGeneratorSpin(LOCTEXT("GroundSearch", "Search ground (cells)"), LOCTEXT("GroundSearchTip", "How many cells below to search for the ground."),
				0.0f, 8.0f, 1.0f, 0, [](const FFramework2DGenerator& G) { return (float)G.GroundSearchTiles; },
				[](FFramework2DGenerator& G, float V) { G.GroundSearchTiles = FMath::Clamp(FMath::RoundToInt(V), 0, 8); })
		]
		+ SVerticalBox::Slot().AutoHeight().Padding(0, 2)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			[
				MakeGeneratorSpin(LOCTEXT("Seed", "Seed"), LOCTEXT("SeedTip", "Another seed = another random distribution with the same settings."),
					0.0f, 99999.0f, 1.0f, 0, [](const FFramework2DGenerator& G) { return (float)G.Seed; },
					[](FFramework2DGenerator& G, float V) { G.Seed = FMath::Max(0, FMath::RoundToInt(V)); })
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(4.0f, 0.0f, 0.0f, 0.0f)
			[
				F2DPalette::IconButton("F2D.Icon.Refresh", LOCTEXT("ReseedTip", "Another random distribution (changes the seed)."),
					FOnClicked::CreateLambda([this, M]()
					{
						M->ChangeGenerator(EditedGeneratorId, LOCTEXT("GeneratorReseed", "New seed"), [](FFramework2DGenerator& G)
						{
							G.Seed = (int32)((uint32)(G.Seed + 1) * 2654435761u % 99991u);
						});
						F2DPalette::RedrawViewports();
						return FReply::Handled();
					}))
			]
		];
}

// ---------------------------------------------------------------------
//  Botones con estado
// ---------------------------------------------------------------------
void SFramework2DTilePalette::RegisterStatefulButton(const TSharedRef<SButton>& Button, TFunction<bool()> IsActive,
	const FButtonStyle* NormalStyle, const FButtonStyle* ActiveStyle)
{
	FStatefulButton Entry;
	Entry.Button = Button;
	Entry.bActive = IsActive ? IsActive() : false;
	Entry.IsActive = MoveTemp(IsActive);
	Entry.NormalStyle = NormalStyle;
	Entry.ActiveStyle = ActiveStyle;
	Button->SetButtonStyle(Entry.bActive ? ActiveStyle : NormalStyle);
	StatefulButtons.Add(MoveTemp(Entry));
}

void SFramework2DTilePalette::UpdateStatefulButtons()
{
	// La herramienta o la forma tambien cambian desde el viewport (atajos, cuentagotas).
	for (FStatefulButton& Entry : StatefulButtons)
	{
		const TSharedPtr<SButton> Button = Entry.Button.Pin();
		if (!Button.IsValid() || !Entry.IsActive) { continue; }
		const bool bActive = Entry.IsActive();
		if (bActive != Entry.bActive)
		{
			Entry.bActive = bActive;
			Button->SetButtonStyle(bActive ? Entry.ActiveStyle : Entry.NormalStyle);
		}
	}
}

#undef LOCTEXT_NAMESPACE
