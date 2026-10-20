// Copyright Chema Luque. Plugin Framework2DTerrain (modulo Editor).

#pragma once

/**
 * Piezas de interfaz que comparten los paneles del modo Framework2D Tiles (pestaña «Pintar»,
 * SFramework2DTilePalette, y pestaña «Generar», SFramework2DProcGenPanel): utilidades de
 * estilo (F2DPalette), la fila de lista con renombrado y la miniatura de un trozo del atlas.
 *
 * Todo va definido aquí mismo (inline): el archivo se incluye desde varios .cpp y, en las
 * compilaciones «unity», varios de ellos comparten unidad. Por eso tampoco hay espacios de
 * nombres anónimos: el nombre propio F2DPalette no choca con nada.
 */

#include "CoreMinimal.h"
#include "Framework2DEditorStyle.h"
#include "Framework2DTilePaintMode.h"
#include "Framework2DTerrainTypes.h"
#include "Framework2DTileSet.h"

#include "Brushes/SlateRoundedBoxBrush.h"
#include "Editor.h"
#include "Engine/Texture2D.h"
#include "InputCoreTypes.h"
#include "Rendering/DrawElements.h"
#include "Styling/CoreStyle.h"
#include "Styling/ISlateStyle.h"
#include "Styling/SlateTypes.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/SLeafWidget.h"
#include "Widgets/SNullWidget.h"
#include "Widgets/Text/SInlineEditableTextBlock.h"
#include "Widgets/Text/STextBlock.h"

// =====================================================================
//  Utilidades de los paneles
// =====================================================================
namespace F2DPalette
{
	constexpr int32 NumCollisionShapes = (int32)EFramework2DCollisionShape::Platform + 1;
	constexpr int32 MaxZoom = 12;

	inline const ISlateStyle& Style() { return FFramework2DEditorStyle::Get(); }
	inline const FSlateBrush* Brush(FName Name) { return Style().GetBrush(Name); }
	inline const FButtonStyle& Button(FName Name) { return Style().GetWidgetStyle<FButtonStyle>(Name); }
	inline const FTextBlockStyle& Text(FName Name) { return Style().GetWidgetStyle<FTextBlockStyle>(Name); }
	inline FSlateFontInfo Font(bool bBold, int32 Size) { return FCoreStyle::GetDefaultFontStyle(bBold ? "Bold" : "Regular", Size); }

	/** El viewport no se repinta solo al tocar el panel (rejilla, capa activa, forma...). */
	inline void RedrawViewports()
	{
		if (GEditor)
		{
			GEditor->RedrawLevelEditingViewports(false);
		}
	}

	/** Tarjeta: fondo hundido y redondeado de cada seccion. */
	inline TSharedRef<SWidget> Card(const TSharedRef<SWidget>& Content)
	{
		return SNew(SBorder)
			.BorderImage(Brush("F2D.Card"))
			.Padding(FMargin(10.0f, 8.0f, 10.0f, 10.0f))
			[
				Content
			];
	}

	/** Cabecera de tarjeta: icono, titulo en mayusculas y (opcional) botones a la derecha. */
	inline TSharedRef<SWidget> CardHeader(FName Icon, const FText& Title, const TSharedRef<SWidget>& Trailing = SNullWidget::NullWidget)
	{
		return SNew(SBox)
			.MinDesiredHeight(24.0f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(0.0f, 0.0f, 6.0f, 0.0f)
				[
					// Siempre a 16 px (los SVG se rasterizan al tamano en que se dibujan: no se emborronan).
					SNew(SBox)
					.WidthOverride(16.0f)
					.HeightOverride(16.0f)
					[
						SNew(SImage)
						.Image(Brush(Icon))
						.ColorAndOpacity(FFramework2DEditorStyle::ForegroundDim())
					]
				]
				+ SHorizontalBox::Slot()
				.FillWidth(1.0f)
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.TextStyle(&Text("F2D.Text.Section"))
					.Text(Title.ToUpper())
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				[
					Trailing
				]
			];
	}

	/** Texto secundario pequeno que se parte en lineas. */
	inline TSharedRef<SWidget> Caption(const TAttribute<FText>& InText)
	{
		return SNew(STextBlock)
			.TextStyle(&Text("F2D.Text.Caption"))
			.AutoWrapText(true)
			.Text(InText);
	}

	/** Boton cuadrado de solo icono (24x24) con su tooltip. */
	inline TSharedRef<SButton> IconButton(FName Icon, const TAttribute<FText>& Tip, FOnClicked OnClicked,
		const TAttribute<bool>& Enabled = TAttribute<bool>(true), const FButtonStyle* InStyle = nullptr)
	{
		return SNew(SButton)
			.ButtonStyle(InStyle ? InStyle : &Button("F2D.Button.Icon"))
			.ContentPadding(FMargin(0.0f))
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			.ToolTipText(Tip)
			.IsEnabled(Enabled)
			.OnClicked(OnClicked)
			[
				SNew(SImage)
				.Image(Brush(Icon))
				.ColorAndOpacity(FSlateColor::UseForeground())
			];
	}

	/** Interruptor tipo "chip": icono (y etiqueta opcional) que se enciende con el acento. */
	inline TSharedRef<SWidget> ToggleChip(FName Icon, const FText& Label, const TAttribute<FText>& Tip,
		TFunction<bool()> Get, TFunction<void(bool)> Set, const TAttribute<bool>& Enabled = TAttribute<bool>(true))
	{
		TSharedRef<SHorizontalBox> Content = SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			[
				SNew(SImage)
				.Image(Brush(Icon))
				.ColorAndOpacity(FSlateColor::UseForeground())
			];
		if (!Label.IsEmpty())
		{
			Content->AddSlot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(5.0f, 0.0f, 0.0f, 0.0f)
				[
					SNew(STextBlock)
					.Text(Label)
					.Font(Font(false, 8))
					.ColorAndOpacity(FSlateColor::UseForeground())
				];
		}
		return SNew(SCheckBox)
			.Style(&Style().GetWidgetStyle<FCheckBoxStyle>("F2D.Toggle.Chip"))
			.Padding(Label.IsEmpty() ? FMargin(4.0f) : FMargin(6.0f, 4.0f, 8.0f, 4.0f))
			.ToolTipText(Tip)
			.IsEnabled(Enabled)
			.IsChecked_Lambda([Get]() { return Get() ? ECheckBoxState::Checked : ECheckBoxState::Unchecked; })
			.OnCheckStateChanged_Lambda([Set](ECheckBoxState State) { Set(State == ECheckBoxState::Checked); })
			[
				Content
			];
	}

	/** Boton de icono que se pone rojo al pasar por encima (borrar). */
	inline const FButtonStyle& DangerIconButtonStyle()
	{
		static const FButtonStyle Danger = []()
		{
			const FLinearColor D = FFramework2DEditorStyle::Danger();
			FButtonStyle S = Button("F2D.Button.Icon");
			S.SetHovered(FSlateRoundedBoxBrush(FLinearColor(D.R, D.G, D.B, 0.16f), 4.0f));
			S.SetPressed(FSlateRoundedBoxBrush(FLinearColor(D.R, D.G, D.B, 0.28f), 4.0f));
			S.SetHoveredForeground(D);
			S.SetPressedForeground(D);
			return S;
		}();
		return Danger;
	}

	/** Botones de forma (32x32): los de herramienta con 4 px de margen para un dibujo de 24. */
	inline const FButtonStyle& ShapeButtonStyle(bool bActive)
	{
		static const FButtonStyle Normal = FButtonStyle(Button("F2D.Button.Tool"))
			.SetNormalPadding(FMargin(4.0f))
			.SetPressedPadding(FMargin(4.0f, 5.0f, 4.0f, 3.0f));
		static const FButtonStyle Active = FButtonStyle(Button("F2D.Button.ToolActive"))
			.SetNormalPadding(FMargin(4.0f))
			.SetPressedPadding(FMargin(4.0f, 5.0f, 4.0f, 3.0f));
		return bActive ? Active : Normal;
	}

	inline FName ToolIcon(EFramework2DTileTool Tool)
	{
		switch (Tool)
		{
		case EFramework2DTileTool::Paint:     return "F2D.Tool.Paint";
		case EFramework2DTileTool::Erase:     return "F2D.Tool.Erase";
		case EFramework2DTileTool::Fill:      return "F2D.Tool.Fill";
		case EFramework2DTileTool::Rect:      return "F2D.Tool.Rect";
		case EFramework2DTileTool::Pick:      return "F2D.Tool.Pick";
		case EFramework2DTileTool::Collision: return "F2D.Tool.Collision";
		default:                              return "F2D.Tool.Paint";
		}
	}

	// Los textos de aqui conservan el espacio de nombres y las claves que tenian en
	// SFramework2DTilePalette.cpp (las traducciones no cambian al mover el codigo).
	inline FText MaterialLabel(FName Material)
	{
		return Material.IsNone() ? NSLOCTEXT("SFramework2DTilePalette", "MaterialNone", "Ninguno (no es terreno)") : FText::FromName(Material);
	}

	/** Los nombres no pueden quedar vacios (capas, flipbooks, generadores, biomas). */
	inline bool VerifyName(const FText& InText, FText& OutError)
	{
		if (InText.ToString().TrimStartAndEnd().IsEmpty())
		{
			OutError = NSLOCTEXT("SFramework2DTilePalette", "EmptyName", "El nombre no puede estar vacío.");
			return false;
		}
		return true;
	}

	/** Estado de un SSpinBox mientras se arrastra (para no crear un paso de deshacer por pixel). */
	struct FSpinDrag
	{
		bool bDragging = false;
		float Value = 0.0f;
	};

	inline void Box(FSlateWindowElementList& Out, int32 Layer, const FGeometry& Geo, ESlateDrawEffect Effect,
		float X, float Y, float W, float H, const FLinearColor& Color)
	{
		FSlateDrawElement::MakeBox(Out, Layer, Geo.ToPaintGeometry(FVector2D(W, H), FSlateLayoutTransform(FVector2D(X, Y))),
			Brush("F2D.White"), Effect, Color);
	}

	inline void Frame(FSlateWindowElementList& Out, int32 Layer, const FGeometry& Geo, ESlateDrawEffect Effect,
		float X, float Y, float W, float H, float T, const FLinearColor& Color)
	{
		Box(Out, Layer, Geo, Effect, X, Y, W, T, Color);
		Box(Out, Layer, Geo, Effect, X, Y + H - T, W, T, Color);
		Box(Out, Layer, Geo, Effect, X, Y + T, T, H - 2.0f * T, Color);
		Box(Out, Layer, Geo, Effect, X + W - T, Y + T, T, H - 2.0f * T, Color);
	}

	/** Contorno discontinuo (seleccion apagada, forma "Automatica", hueco vacio). */
	inline void DashedFrame(FSlateWindowElementList& Out, int32 Layer, const FGeometry& Geo, ESlateDrawEffect Effect,
		float X, float Y, float W, float H, float T, float Dash, const FLinearColor& Color)
	{
		for (float D = 0.0f; D < W; D += 2.0f * Dash)
		{
			const float Len = FMath::Min(Dash, W - D);
			Box(Out, Layer, Geo, Effect, X + D, Y, Len, T, Color);
			Box(Out, Layer, Geo, Effect, X + D, Y + H - T, Len, T, Color);
		}
		for (float D = 0.0f; D < H; D += 2.0f * Dash)
		{
			const float Len = FMath::Min(Dash, H - D);
			Box(Out, Layer, Geo, Effect, X, Y + D, T, Len, Color);
			Box(Out, Layer, Geo, Effect, X + W - T, Y + D, T, Len, Color);
		}
	}
}

// =====================================================================
//  Fila de lista (capa, flipbook, generador, bioma): clic = elegir, doble clic o F2 = renombrar
// =====================================================================
class SFramework2DListRow : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SFramework2DListRow) {}
		SLATE_ATTRIBUTE(bool, IsActive)
		SLATE_EVENT(FSimpleDelegate, OnSelected)
		SLATE_DEFAULT_SLOT(FArguments, Content)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs)
	{
		IsActive = InArgs._IsActive;
		OnSelected = InArgs._OnSelected;
		ChildSlot
		[
			SNew(SBorder)
			.BorderImage(this, &SFramework2DListRow::GetRowBrush)
			.Padding(FMargin(0.0f))
			[
				InArgs._Content.Widget
			]
		];
	}

	void SetRenameTarget(const TSharedPtr<SInlineEditableTextBlock>& InTarget) { RenameTarget = InTarget; }

	// Enfocable con el teclado (Tab): Intro/Espacio la elige y F2 renombra.
	virtual bool SupportsKeyboardFocus() const override { return true; }

	virtual FReply OnMouseButtonDown(const FGeometry& Geo, const FPointerEvent& Event) override
	{
		if (Event.GetEffectingButton() != EKeys::LeftMouseButton) { return FReply::Unhandled(); }
		OnSelected.ExecuteIfBound();
		return FReply::Handled();
	}

	virtual FReply OnMouseButtonDoubleClick(const FGeometry& Geo, const FPointerEvent& Event) override
	{
		if (Event.GetEffectingButton() != EKeys::LeftMouseButton) { return FReply::Unhandled(); }
		OnSelected.ExecuteIfBound();
		BeginRename();
		return FReply::Handled();
	}

	virtual FReply OnKeyDown(const FGeometry& Geo, const FKeyEvent& Event) override
	{
		const FKey Key = Event.GetKey();
		if (Key == EKeys::Enter || Key == EKeys::SpaceBar)
		{
			OnSelected.ExecuteIfBound();
			return FReply::Handled();
		}
		if (Key == EKeys::F2)
		{
			BeginRename();
			return FReply::Handled();
		}
		return SCompoundWidget::OnKeyDown(Geo, Event);
	}

private:
	TAttribute<bool> IsActive;
	FSimpleDelegate OnSelected;
	TWeakPtr<SInlineEditableTextBlock> RenameTarget;

	void BeginRename()
	{
		if (const TSharedPtr<SInlineEditableTextBlock> Target = RenameTarget.Pin())
		{
			Target->EnterEditingMode();
		}
	}

	const FSlateBrush* GetRowBrush() const
	{
		if (IsActive.Get(false)) { return F2DPalette::Brush("F2D.Row.Active"); }
		return F2DPalette::Brush(IsHovered() ? FName("F2D.Row.Hover") : FName("F2D.Row"));
	}
};

// =====================================================================
//  Miniatura de un trozo del atlas (tile, fotograma de flipbook, sprite de un generador)
// =====================================================================
class SFramework2DTileThumb : public SLeafWidget
{
public:
	SLATE_BEGIN_ARGS(SFramework2DTileThumb)
		: _Size(40.0f)
		, _bAnimated(false)
	{}
		SLATE_ARGUMENT(float, Size)
		SLATE_ARGUMENT(bool, bAnimated)
	SLATE_END_ARGS()

	/** Source: (valor de tile con pagina, ancho en tiles, alto en tiles) de lo que se dibuja ahora. X < 0 = nada. */
	void Construct(const FArguments& InArgs, FFramework2DTilePaintMode* InMode, TFunction<FIntVector()> InSource)
	{
		Mode = InMode;
		Source = MoveTemp(InSource);
		Size = InArgs._Size;
		if (InArgs._bAnimated)
		{
			// Mira 30 veces por segundo si toca otro fotograma y solo entonces se repinta.
			RegisterActiveTimer(1.0f / 30.0f, FWidgetActiveTimerDelegate::CreateSP(this, &SFramework2DTileThumb::CheckFrame));
		}
	}

	virtual FVector2D ComputeDesiredSize(float) const override { return FVector2D(Size, Size); }

	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& Geo, const FSlateRect& Culling, FSlateWindowElementList& Out,
		int32 Layer, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override
	{
		const ESlateDrawEffect Effect = ShouldBeEnabled(bParentEnabled) ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect;
		const FVector2D Local = Geo.GetLocalSize();

		// Fondo a cuadros: se ve la transparencia del dibujo.
		F2DPalette::Box(Out, Layer, Geo, Effect, 0.0f, 0.0f, Local.X, Local.Y, FFramework2DEditorStyle::SurfaceRaised());
		const float Q = FMath::Max(3.0f, FMath::RoundToFloat(Size / 8.0f));
		for (float Y = 2.0f; Y < Local.Y - 2.0f; Y += Q)
		{
			for (float X = 2.0f + ((int32)((Y - 2.0f) / Q) % 2) * Q; X < Local.X - 2.0f; X += 2.0f * Q)
			{
				F2DPalette::Box(Out, Layer, Geo, Effect, X, Y, FMath::Min(Q, Local.X - 2.0f - X), FMath::Min(Q, Local.Y - 2.0f - Y), FLinearColor(1.0f, 1.0f, 1.0f, 0.05f));
			}
		}

		const UFramework2DTileSet* Set = Mode->GetTileSet();
		const FIntVector What = Source ? Source() : FIntVector(-1, 1, 1);
		int32 PageId = 0, Px = 0, Py = 0, PW = 0, PH = 0;
		if (!Set || What.X < 0 || !Set->GetTileValueOrigin(What.X, PageId, Px, Py) || !Set->GetPageSize(PageId, PW, PH)) { return Layer; }
		UTexture2D* Texture = Set->GetPageTexture(PageId);
		if (!Texture) { return Layer; }

		// El trozo (uno o varios tiles), encajado sin deformar.
		const int32 RW = FMath::Min(PW - Px, FMath::Max(1, What.Y) * Set->TileWidth);
		const int32 RH = FMath::Min(PH - Py, FMath::Max(1, What.Z) * Set->TileHeight);
		const float Avail = FMath::Min(Local.X, Local.Y) - 4.0f;
		const float Scale = FMath::Min(Avail / FMath::Max(1, RW), Avail / FMath::Max(1, RH));
		const float W = RW * Scale;
		const float H = RH * Scale;
		ImageBrush.SetResourceObject(Texture);
		ImageBrush.DrawAs = ESlateBrushDrawType::Image;
		ImageBrush.SetImageSize(FVector2D(PW, PH));
		ImageBrush.SetUVRegion(FBox2D(
			FVector2D((double)Px / PW, (double)Py / PH),
			FVector2D((double)(Px + RW) / PW, (double)(Py + RH) / PH)));
		FSlateDrawElement::MakeBox(Out, Layer + 1,
			Geo.ToPaintGeometry(FVector2D(W, H), FSlateLayoutTransform(FVector2D(FMath::RoundToFloat((Local.X - W) * 0.5f), FMath::RoundToFloat((Local.Y - H) * 0.5f)))),
			&ImageBrush, Effect, InWidgetStyle.GetColorAndOpacityTint());
		return Layer + 1;
	}

private:
	FFramework2DTilePaintMode* Mode = nullptr;
	TFunction<FIntVector()> Source;
	float Size = 40.0f;
	FIntVector LastShown = FIntVector(-2, 0, 0);
	mutable FSlateBrush ImageBrush;

	EActiveTimerReturnType CheckFrame(double InCurrentTime, float InDeltaTime)
	{
		const FIntVector Shown = Source ? Source() : FIntVector(-1, 1, 1);
		if (Shown != LastShown)
		{
			LastShown = Shown;
			Invalidate(EInvalidateWidgetReason::Paint);
		}
		return EActiveTimerReturnType::Continue;
	}
};
