// Copyright Chema Luque. Plugin Framework2DTerrain (modulo Editor).

#include "SFramework2DProcGenPanel.h"

#include "Framework2DEditorStyle.h"
#include "Framework2DPaletteWidgets.h"
#include "Framework2DProcGen.h"
#include "Framework2DTileMapAsset.h"
#include "Framework2DTileSet.h"
#include "Framework2DTilePaintMode.h"

#include "Framework/Application/IMenu.h"
#include "Framework/Application/MenuStack.h"
#include "Framework/Application/SlateApplication.h"
#include "HAL/PlatformTime.h"
#include "Layout/Children.h"
#include "Layout/WidgetPath.h"
#include "Styling/StyleDefaults.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SSpinBox.h"
#include "Widgets/Layout/SExpandableArea.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SUniformGridPanel.h"
#include "Widgets/Layout/SWrapBox.h"
#include "Widgets/SOverlay.h"

#define LOCTEXT_NAMESPACE "SFramework2DProcGenPanel"

// =====================================================================
//  Utilidades de este panel (espacio de nombres propio: en las compilaciones
//  "unity" varios .cpp comparten unidad y los anonimos chocarian)
// =====================================================================
namespace Framework2DProcGenPanelUtil
{
	/** Lo que se ve AHORA de un valor de celda: el tile, el fotograma del flipbook o el primer sprite del generador. */
	FIntVector ThumbOf(const UFramework2DTileSet* Set, int32 Value)
	{
		if (!Set || Value < 0) { return FIntVector(-1, 1, 1); }
		if (Framework2D::IsGeneratorValue(Value))
		{
			const FFramework2DGenerator* Generator = Set->FindGeneratorByValue(Value);
			if (!Generator || Generator->Sprites.Num() == 0) { return FIntVector(-1, 1, 1); }
			const FFramework2DScatterSprite& First = Generator->Sprites[0];
			return FIntVector(First.Tile, FMath::Clamp(First.WidthInTiles, 1, 16), FMath::Clamp(First.HeightInTiles, 1, 16));
		}
		return FIntVector(Set->GetFrameTile(Value, FPlatformTime::Seconds()), 1, 1);
	}

	/** Hay valor pero ya no existe en el Tile Set (flipbook, generador o pagina borrados). */
	bool IsMissing(const UFramework2DTileSet* Set, int32 Value)
	{
		return Value >= 0 && !UFramework2DProcGenLibrary::IsUsablePiece(Set, Value);
	}

	/** Nombre corto: el del flipbook o generador, o «Tile N». */
	FText ValueName(const UFramework2DTileSet* Set, int32 Value)
	{
		if (Value < 0) { return LOCTEXT("ValueEmpty", "Empty"); }
		if (Framework2D::IsGeneratorValue(Value))
		{
			const FFramework2DGenerator* Generator = Set ? Set->FindGeneratorByValue(Value) : nullptr;
			return Generator ? FText::FromName(Generator->Name) : LOCTEXT("ValueGeneratorGone", "Generator deleted");
		}
		if (Framework2D::IsFlipbookValue(Value))
		{
			const FFramework2DFlipbook* Flipbook = Set ? Set->FindFlipbookByValue(Value) : nullptr;
			return Flipbook ? FText::FromName(Flipbook->Name) : LOCTEXT("ValueFlipbookGone", "Flipbook deleted");
		}
		return FText::Format(LOCTEXT("ValueTile", "Tile {0}"), FText::AsNumber(Framework2D::TileLocalOf(Value)));
	}

	/** Qué es (segunda línea de las filas de decoración). */
	FText KindLabel(const UFramework2DTileSet* Set, int32 Value)
	{
		if (Value < 0) { return FText::GetEmpty(); }
		if (IsMissing(Set, Value)) { return LOCTEXT("KindMissing", "No longer exists: choose another piece or remove it"); }
		if (Framework2D::IsGeneratorValue(Value))
		{
			const FFramework2DGenerator* Generator = Set ? Set->FindGeneratorByValue(Value) : nullptr;
			return FText::Format(LOCTEXT("KindGenerator", "Generator · {0} {0}|plural(one=sprite,other=sprites)"), Generator ? Generator->Sprites.Num() : 0);
		}
		if (Framework2D::IsFlipbookValue(Value))
		{
			const FFramework2DFlipbook* Flipbook = Set ? Set->FindFlipbookByValue(Value) : nullptr;
			return FText::Format(LOCTEXT("KindFlipbook", "Flipbook · {0} {0}|plural(one=frame,other=frames)"), Flipbook ? Flipbook->Frames.Num() : 0);
		}
		return FText::Format(LOCTEXT("KindTile", "Tile from atlas «{0}»"), Set ? Set->GetPageDisplayName(Framework2D::TilePageOf(Value)) : FText::GetEmpty());
	}

	/** Frase completa para los tooltips: qué hay en el hueco. */
	FText DescribeValue(const UFramework2DTileSet* Set, int32 Value)
	{
		if (Value < 0) { return LOCTEXT("DescEmpty", "Empty."); }
		if (IsMissing(Set, Value))
		{
			return LOCTEXT("DescMissing", "The piece no longer exists (its flipbook, generator or page was deleted). Choose another or clear the slot.");
		}
		if (Framework2D::IsGeneratorValue(Value))
		{
			const FFramework2DGenerator* Generator = Set ? Set->FindGeneratorByValue(Value) : nullptr;
			return FText::Format(LOCTEXT("DescGenerator", "Generator «{0}»: scatters {1} {1}|plural(one=sprite,other=sprites) when baking."),
				ValueName(Set, Value), Generator ? Generator->Sprites.Num() : 0);
		}
		if (Framework2D::IsFlipbookValue(Value))
		{
			const FFramework2DFlipbook* Flipbook = Set ? Set->FindFlipbookByValue(Value) : nullptr;
			FNumberFormattingOptions OneDecimal;
			OneDecimal.MaximumFractionalDigits = 1;
			return FText::Format(LOCTEXT("DescFlipbook", "Flipbook «{0}»: {1} {1}|plural(one=frame,other=frames) at {2} fps."),
				ValueName(Set, Value), Flipbook ? Flipbook->Frames.Num() : 0, FText::AsNumber(Flipbook ? Flipbook->FPS : 0.0f, &OneDecimal));
		}
		return FText::Format(LOCTEXT("DescTile", "Tile {0} of atlas «{1}»."), FText::AsNumber(Framework2D::TileLocalOf(Value)),
			Set ? Set->GetPageDisplayName(Framework2D::TilePageOf(Value)) : FText::GetEmpty());
	}

	/** Nombre completo de cada hueco (título del selector y tooltips). */
	FText SlotName(EFramework2DBiomeSlot Slot)
	{
		switch (Slot)
		{
		case EFramework2DBiomeSlot::GroundTopLeft:         return LOCTEXT("SlotGroundTL", "Terrain top-left");
		case EFramework2DBiomeSlot::GroundTop:             return LOCTEXT("SlotGroundT", "Terrain top");
		case EFramework2DBiomeSlot::GroundTopRight:        return LOCTEXT("SlotGroundTR", "Terrain top-right");
		case EFramework2DBiomeSlot::GroundLeft:            return LOCTEXT("SlotGroundL", "Terrain left");
		case EFramework2DBiomeSlot::GroundCenter:          return LOCTEXT("SlotGroundC", "Terrain center");
		case EFramework2DBiomeSlot::GroundRight:           return LOCTEXT("SlotGroundR", "Terrain right");
		case EFramework2DBiomeSlot::GroundBottomLeft:      return LOCTEXT("SlotGroundBL", "Terrain bottom-left");
		case EFramework2DBiomeSlot::GroundBottom:          return LOCTEXT("SlotGroundB", "Terrain bottom");
		case EFramework2DBiomeSlot::GroundBottomRight:     return LOCTEXT("SlotGroundBR", "Terrain bottom-right");
		case EFramework2DBiomeSlot::InnerTopLeft:          return LOCTEXT("SlotInnerTL", "Inner corner top-left");
		case EFramework2DBiomeSlot::InnerTopRight:         return LOCTEXT("SlotInnerTR", "Inner corner top-right");
		case EFramework2DBiomeSlot::InnerBottomLeft:       return LOCTEXT("SlotInnerBL", "Inner corner bottom-left");
		case EFramework2DBiomeSlot::InnerBottomRight:      return LOCTEXT("SlotInnerBR", "Inner corner bottom-right");
		case EFramework2DBiomeSlot::RampUp:                return LOCTEXT("SlotRampUp", "45° ramp rising to the right");
		case EFramework2DBiomeSlot::RampDown:              return LOCTEXT("SlotRampDown", "45° ramp falling to the right");
		case EFramework2DBiomeSlot::GentleUpLow:           return LOCTEXT("SlotGentleUpLow", "Gentle rising ramp: low half");
		case EFramework2DBiomeSlot::GentleUpHigh:          return LOCTEXT("SlotGentleUpHigh", "Gentle rising ramp: high half");
		case EFramework2DBiomeSlot::GentleDownHigh:        return LOCTEXT("SlotGentleDownHigh", "Gentle falling ramp: high half");
		case EFramework2DBiomeSlot::GentleDownLow:         return LOCTEXT("SlotGentleDownLow", "Gentle falling ramp: low half");
		case EFramework2DBiomeSlot::PlatformLeft:          return LOCTEXT("SlotPlatformL", "Platform: left end");
		case EFramework2DBiomeSlot::PlatformMiddle:        return LOCTEXT("SlotPlatformM", "Platform: span");
		case EFramework2DBiomeSlot::PlatformRight:         return LOCTEXT("SlotPlatformR", "Platform: right end");
		case EFramework2DBiomeSlot::BackgroundTopLeft:     return LOCTEXT("SlotBgTL", "Background top-left");
		case EFramework2DBiomeSlot::BackgroundTop:         return LOCTEXT("SlotBgT", "Background top");
		case EFramework2DBiomeSlot::BackgroundTopRight:    return LOCTEXT("SlotBgTR", "Background top-right");
		case EFramework2DBiomeSlot::BackgroundLeft:        return LOCTEXT("SlotBgL", "Background left");
		case EFramework2DBiomeSlot::BackgroundCenter:      return LOCTEXT("SlotBgC", "Background center");
		case EFramework2DBiomeSlot::BackgroundRight:       return LOCTEXT("SlotBgR", "Background right");
		case EFramework2DBiomeSlot::BackgroundBottomLeft:  return LOCTEXT("SlotBgBL", "Background bottom-left");
		case EFramework2DBiomeSlot::BackgroundBottom:      return LOCTEXT("SlotBgB", "Background bottom");
		case EFramework2DBiomeSlot::BackgroundBottomRight: return LOCTEXT("SlotBgBR", "Background bottom-right");
		case EFramework2DBiomeSlot::WaterSurface:          return LOCTEXT("SlotWaterSurface", "Water surface");
		case EFramework2DBiomeSlot::WaterBody:             return LOCTEXT("SlotWaterBody", "Water body");
		case EFramework2DBiomeSlot::WaterfallTop:          return LOCTEXT("SlotFallTop", "Waterfall: top");
		case EFramework2DBiomeSlot::WaterfallBody:         return LOCTEXT("SlotFallBody", "Waterfall: fall");
		case EFramework2DBiomeSlot::WaterfallBottom:       return LOCTEXT("SlotFallBottom", "Waterfall: foam");
		case EFramework2DBiomeSlot::BridgeLeft:            return LOCTEXT("SlotBridgeL", "Bridge: left end");
		case EFramework2DBiomeSlot::BridgeMiddle:          return LOCTEXT("SlotBridgeM", "Bridge: planks");
		case EFramework2DBiomeSlot::BridgeRight:           return LOCTEXT("SlotBridgeR", "Bridge: right end");
		case EFramework2DBiomeSlot::EdgeTop:               return LOCTEXT("SlotEdgeTop", "Natural top edge (over every top edge)");
		case EFramework2DBiomeSlot::EdgeBottom:            return LOCTEXT("SlotEdgeBottom", "Natural bottom edge (under islands and ledges)");
		case EFramework2DBiomeSlot::WaterCrest:            return LOCTEXT("SlotWaterCrest", "Waves: what shows above the water surface");
		case EFramework2DBiomeSlot::BridgePostLeftLow:     return LOCTEXT("SlotPostLL", "Bridge left post (bottom)");
		case EFramework2DBiomeSlot::BridgePostLeftHigh:    return LOCTEXT("SlotPostLH", "Bridge left post (top)");
		case EFramework2DBiomeSlot::BridgePostRightLow:    return LOCTEXT("SlotPostRL", "Bridge right post (bottom)");
		case EFramework2DBiomeSlot::BridgePostRightHigh:   return LOCTEXT("SlotPostRH", "Bridge right post (top)");
		case EFramework2DBiomeSlot::WallFootLeft:          return LOCTEXT("SlotFootL", "Wall foot with ground on the left: first wall column");
		case EFramework2DBiomeSlot::WallFootLeftInner:     return LOCTEXT("SlotFootLI", "Wall foot with ground on the left: next column (cap)");
		case EFramework2DBiomeSlot::WallFootRight:         return LOCTEXT("SlotFootR", "Wall foot with ground on the right: first wall column");
		case EFramework2DBiomeSlot::WallFootRightInner:    return LOCTEXT("SlotFootRI", "Wall foot with ground on the right: next column (cap)");
		case EFramework2DBiomeSlot::PlatformCapLeft:       return LOCTEXT("SlotCapL", "Cap above the platform's left end");
		case EFramework2DBiomeSlot::PlatformCapMiddle:     return LOCTEXT("SlotCapM", "Cap above the platform span");
		case EFramework2DBiomeSlot::PlatformCapRight:      return LOCTEXT("SlotCapR", "Cap above the platform's right end");
		case EFramework2DBiomeSlot::GroundDeep:            return LOCTEXT("SlotDeep", "Deep interior: what goes deeper than the 5×5 rows");
		case EFramework2DBiomeSlot::BridgeCapLeft:         return LOCTEXT("SlotBridgeCapL", "Bridge lip above the first plank (with the 5×5)");
		case EFramework2DBiomeSlot::BridgeCapMiddle:       return LOCTEXT("SlotBridgeCapM", "Bridge lip above the planks (with the 5×5)");
		case EFramework2DBiomeSlot::BridgeCapRight:        return LOCTEXT("SlotBridgeCapR", "Bridge lip above the last plank (with the 5×5)");
		default:
			if (Slot >= EFramework2DBiomeSlot::Ground5_00 && Slot <= EFramework2DBiomeSlot::Ground5_44)
			{
				const int32 I = (int32)Slot - (int32)EFramework2DBiomeSlot::Ground5_00;
				return FText::Format(LOCTEXT("SlotGround5", "Terrain 5×5: row {0}, column {1}"), I / 5 + 1, I % 5 + 1);
			}
			return FText::GetEmpty();
		}
	}

	/** Etiqueta corta debajo del hueco (los de las rejillas 3x3 y 2x2 no llevan: los sitúa su posición). */
	FText SlotLabel(EFramework2DBiomeSlot Slot)
	{
		switch (Slot)
		{
		case EFramework2DBiomeSlot::RampUp:          return LOCTEXT("LabelRampUp", "Rises");
		case EFramework2DBiomeSlot::RampDown:        return LOCTEXT("LabelRampDown", "Falls");
		case EFramework2DBiomeSlot::GentleUpLow:     return LOCTEXT("LabelGentleUpLow", "Rises (low)");
		case EFramework2DBiomeSlot::GentleUpHigh:    return LOCTEXT("LabelGentleUpHigh", "Rises (high)");
		case EFramework2DBiomeSlot::GentleDownHigh:  return LOCTEXT("LabelGentleDownHigh", "Falls (high)");
		case EFramework2DBiomeSlot::GentleDownLow:   return LOCTEXT("LabelGentleDownLow", "Falls (low)");
		case EFramework2DBiomeSlot::PlatformLeft:    return LOCTEXT("LabelPlatformL", "Left");
		case EFramework2DBiomeSlot::PlatformMiddle:  return LOCTEXT("LabelPlatformM", "Span");
		case EFramework2DBiomeSlot::PlatformRight:   return LOCTEXT("LabelPlatformR", "Right");
		case EFramework2DBiomeSlot::WaterSurface:    return LOCTEXT("LabelWaterSurface", "Surface");
		case EFramework2DBiomeSlot::WaterBody:       return LOCTEXT("LabelWaterBody", "Water body");
		case EFramework2DBiomeSlot::WaterfallTop:    return LOCTEXT("LabelFallTop", "Top");
		case EFramework2DBiomeSlot::WaterfallBody:   return LOCTEXT("LabelFallBody", "Fall");
		case EFramework2DBiomeSlot::WaterfallBottom: return LOCTEXT("LabelFallBottom", "Foam");
		case EFramework2DBiomeSlot::BridgeLeft:      return LOCTEXT("LabelBridgeL", "Left");
		case EFramework2DBiomeSlot::BridgeMiddle:    return LOCTEXT("LabelBridgeM", "Planks");
		case EFramework2DBiomeSlot::BridgeRight:     return LOCTEXT("LabelBridgeR", "Right");
		case EFramework2DBiomeSlot::EdgeTop:         return LOCTEXT("LabelEdgeTop", "Top");
		case EFramework2DBiomeSlot::EdgeBottom:      return LOCTEXT("LabelEdgeBottom", "Bottom");
		case EFramework2DBiomeSlot::WaterCrest:      return LOCTEXT("LabelWaterCrest", "Waves");
		case EFramework2DBiomeSlot::BridgePostLeftLow:   return LOCTEXT("LabelPostLL", "Left post");
		case EFramework2DBiomeSlot::BridgePostLeftHigh:  return LOCTEXT("LabelPostLH", "Left post (high)");
		case EFramework2DBiomeSlot::BridgePostRightLow:  return LOCTEXT("LabelPostRL", "Right post");
		case EFramework2DBiomeSlot::BridgePostRightHigh: return LOCTEXT("LabelPostRH", "Right post (high)");
		case EFramework2DBiomeSlot::WallFootLeft:        return LOCTEXT("LabelFootL", "Left ground");
		case EFramework2DBiomeSlot::WallFootLeftInner:   return LOCTEXT("LabelFootLI", "Left cap");
		case EFramework2DBiomeSlot::WallFootRight:       return LOCTEXT("LabelFootR", "Right ground");
		case EFramework2DBiomeSlot::WallFootRightInner:  return LOCTEXT("LabelFootRI", "Right cap");
		case EFramework2DBiomeSlot::PlatformCapLeft:     return LOCTEXT("LabelCapL", "Left lip");
		case EFramework2DBiomeSlot::PlatformCapMiddle:   return LOCTEXT("LabelCapM", "Lip");
		case EFramework2DBiomeSlot::PlatformCapRight:    return LOCTEXT("LabelCapR", "Right lip");
		case EFramework2DBiomeSlot::GroundDeep:          return LOCTEXT("LabelDeep", "Deep");
		case EFramework2DBiomeSlot::BridgeCapLeft:       return LOCTEXT("LabelBridgeCapL", "Left lip");
		case EFramework2DBiomeSlot::BridgeCapMiddle:     return LOCTEXT("LabelBridgeCapM", "Lip");
		case EFramework2DBiomeSlot::BridgeCapRight:      return LOCTEXT("LabelBridgeCapR", "Right lip");
		default:                                     return FText::GetEmpty();
		}
	}

	FText TargetName(const FFramework2DPieceTarget& Target)
	{
		switch (Target.Kind)
		{
		case EFramework2DPieceTargetKind::Block3x3:
			if (Target.BlockSize == 5) { return LOCTEXT("TargetBlock5", "Terrain 5×5 block"); }
			return Target.bBackground ? LOCTEXT("TargetBlockBg", "Background 3×3 block") : LOCTEXT("TargetBlockGround", "Terrain 3×3 block");
		case EFramework2DPieceTargetKind::AddVariant:    return LOCTEXT("TargetAddVariant", "New center variant");
		case EFramework2DPieceTargetKind::Variant:       return FText::Format(LOCTEXT("TargetVariant", "Center variant {0}"), Target.Index + 1);
		case EFramework2DPieceTargetKind::AddDecoration: return LOCTEXT("TargetAddDecoration", "New decoration");
		case EFramework2DPieceTargetKind::Decoration:    return FText::Format(LOCTEXT("TargetDecoration", "Decoration {0}"), Target.Index + 1);
		default:                                         return SlotName(Target.Slot);
		}
	}

	/** Piezas sueltas con valor + variantes del centro (resumen de la fila del bioma). */
	int32 CountPieces(const FFramework2DBiome& Biome)
	{
		int32 Count = Biome.CenterVariants.Num();
		for (int32 S = 0; S < (int32)EFramework2DBiomeSlot::Count; ++S)
		{
			if (Framework2D::GetBiomeSlot(Biome, (EFramework2DBiomeSlot)S) >= 0) { ++Count; }
		}
		return Count;
	}

	/** Capas de la receta: 0 Terreno, 1 Fondo, 2 Agua, 3 Decoracion. */
	FName& LayerNameRef(FFramework2DProcGenSettings& Settings, int32 Which)
	{
		switch (Which)
		{
		case 1:  return Settings.BackgroundLayer;
		case 2:  return Settings.WaterLayer;
		case 3:  return Settings.DecorationLayer;
		default: return Settings.TerrainLayer;
		}
	}

	FName LayerName(const FFramework2DProcGenSettings& Settings, int32 Which)
	{
		return LayerNameRef(const_cast<FFramework2DProcGenSettings&>(Settings), Which);
	}

	FText LayerTitle(int32 Which)
	{
		switch (Which)
		{
		case 1:  return LOCTEXT("LayerTitleBg", "Background");
		case 2:  return LOCTEXT("LayerTitleWater", "Water");
		case 3:  return LOCTEXT("LayerTitleDecor", "Decoration");
		default: return LOCTEXT("LayerTitleTerrain", "Terrain");
		}
	}

	/** Círculo del aviso «!»: rojo = la pieza ya no existe; ámbar = falta una obligatoria. */
	const FSlateBrush* BadgeBrush(bool bDanger)
	{
		static const FSlateRoundedBoxBrush DangerBrush(FFramework2DEditorStyle::Danger(), 7.0f);
		static const FSlateRoundedBoxBrush AccentBrush(FFramework2DEditorStyle::Accent(), 7.0f);
		return bDanger ? &DangerBrush : &AccentBrush;
	}

	/** Botón con icono y texto (secundario, o principal con el acento). */
	TSharedRef<SButton> TextButton(FName Icon, const FText& Label, const TAttribute<FText>& Tip, FOnClicked OnClicked,
		const TAttribute<bool>& Enabled, bool bPrimary)
	{
		return SNew(SButton)
			.ButtonStyle(&F2DPalette::Button(bPrimary ? FName("F2D.Button.Primary") : FName("F2D.Button.Secondary")))
			.ContentPadding(FMargin(0.0f))
			.VAlign(VAlign_Center)
			.ToolTipText(Tip)
			.IsEnabled(Enabled)
			.OnClicked(OnClicked)
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
						.Image(F2DPalette::Brush(Icon))
						.ColorAndOpacity(FSlateColor::UseForeground())
					]
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(5.0f, 0.0f, 0.0f, 0.0f)
				[
					SNew(STextBlock)
					.Text(Label)
					.Font(F2DPalette::Font(bPrimary, bPrimary ? 9 : 8))
					.ColorAndOpacity(FSlateColor::UseForeground())
				]
			];
	}

	/**
	 * SExpandableArea pinta su cabecera con un SButton sin tooltip: se lo pone (todo botón del
	 * panel lleva tooltip, y la auditoría de las pruebas lo comprueba).
	 */
	bool SetFirstButtonTip(const TSharedRef<SWidget>& Root, const FText& Tip, int32 Depth)
	{
		if (Root->GetType() == FName(TEXT("SButton")))
		{
			Root->SetToolTipText(Tip);
			return true;
		}
		FChildren* Children = Depth < 8 ? Root->GetChildren() : nullptr;
		if (!Children) { return false; }
		for (int32 I = 0; I < Children->Num(); ++I)
		{
			if (SetFirstButtonTip(Children->GetChildAt(I), Tip, Depth + 1)) { return true; }
		}
		return false;
	}

	/** Otra semilla (la misma cuenta que el modo: siempre de 0 a 999999). */
	int32 NewSeed(int32 Seed)
	{
		return (int32)(HashCombine((uint32)Seed, FPlatformTime::Cycles()) % 1000000u);
	}

	/** Tipo de la línea de resultado del pie. */
	enum class EReportKind : uint8 { None, Ok, Warning, Problem };
}

// =====================================================================
//  HUECO de una pieza: miniatura (animada si es flipbook), distintivo de
//  flipbook/generador, aviso y etiqueta corta. Enfocable con Tab.
//  Clic / Intro / Espacio = abrir el selector · Clic derecho / Supr / Retroceso = vaciar
// =====================================================================
DECLARE_DELEGATE_TwoParams(FFramework2DOnOpenPieceSlot, TSharedRef<SWidget> /*Anchor*/, bool /*bFromKeyboard*/);

class SFramework2DPieceSlot : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SFramework2DPieceSlot)
		: _Size(44.0f)
		, _bRequired(false)
		, _bRemovable(false)
		, _bAdd(false)
	{}
		SLATE_ARGUMENT(float, Size)
		SLATE_ARGUMENT(FText, Label)       // etiqueta corta debajo (vacía = sin etiqueta)
		SLATE_ARGUMENT(FText, SlotName)    // nombre completo para el tooltip
		SLATE_ARGUMENT(bool, bRequired)    // vacío = aviso (el centro del terreno)
		SLATE_ARGUMENT(bool, bRemovable)   // elemento de una lista: vaciar = quitarlo
		SLATE_ARGUMENT(bool, bAdd)         // hueco «+» que añade a una lista
		SLATE_EVENT(FFramework2DOnOpenPieceSlot, OnOpen)
		SLATE_EVENT(FSimpleDelegate, OnClear)
	SLATE_END_ARGS()

	/** InGetValue: el valor que tiene ahora el hueco (-1 = vacío). */
	void Construct(const FArguments& InArgs, FFramework2DTilePaintMode* InMode, TFunction<int32()> InGetValue)
	{
		Mode = InMode;
		GetValue = MoveTemp(InGetValue);
		Size = InArgs._Size;
		SlotName = InArgs._SlotName;
		bRequired = InArgs._bRequired;
		bRemovable = InArgs._bRemovable;
		bAdd = InArgs._bAdd;
		OnOpen = InArgs._OnOpen;
		OnClear = InArgs._OnClear;

		const bool bHasLabel = !InArgs._Label.IsEmpty();
		FFramework2DTilePaintMode* M = Mode;
		const TFunction<int32()> Get = GetValue;

		ChildSlot
		[
			SNew(SBox)
			.WidthOverride(bHasLabel ? FMath::Max(Size, 64.0f) : Size)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Center)
				[
					SNew(SBox)
					.WidthOverride(Size)
					.HeightOverride(Size)
					[
						SNew(SOverlay)
						// Fondo del hueco vacío (la miniatura pinta el suyo, a cuadros).
						+ SOverlay::Slot()
						[
							SNew(SImage)
							.Image_Lambda([this]() { return F2DPalette::Brush(IsHovered() ? FName("F2D.Row.Hover") : FName("F2D.Row")); })
						]
						+ SOverlay::Slot()
						[
							SNew(SFramework2DTileThumb, M, [M, Get]() { return Framework2DProcGenPanelUtil::ThumbOf(M->GetTileSet(), Get ? Get() : -1); })
							.Size(Size)
							.bAnimated(true)
							.Visibility_Lambda([this]() { return HasValue() ? EVisibility::HitTestInvisible : EVisibility::Collapsed; })
						]
						// Vacío: «+» (y contorno discontinuo, en OnPaint).
						+ SOverlay::Slot()
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						[
							SNew(SImage)
							.Image(F2DPalette::Brush("F2D.Icon.Add"))
							.ColorAndOpacity_Lambda([this]() -> FSlateColor
							{
								return IsHovered() ? FFramework2DEditorStyle::Foreground() : FFramework2DEditorStyle::ForegroundDim();
							})
							.Visibility_Lambda([this]() { return HasValue() ? EVisibility::Collapsed : EVisibility::HitTestInvisible; })
						]
						// Distintivo de flipbook o de generador (un icono: forma, no solo color).
						+ SOverlay::Slot()
						.HAlign(HAlign_Right)
						.VAlign(VAlign_Bottom)
						.Padding(2.0f)
						[
							SNew(SBorder)
							.BorderImage(F2DPalette::Brush("F2D.Card"))
							.Padding(FMargin(1.0f))
							.Visibility_Lambda([this]() { return GetBadgeIcon().IsNone() ? EVisibility::Collapsed : EVisibility::HitTestInvisible; })
							[
								SNew(SBox)
								.WidthOverride(12.0f)
								.HeightOverride(12.0f)
								[
									SNew(SImage)
									.Image_Lambda([this]()
									{
										const FName Icon = GetBadgeIcon();
										return F2DPalette::Brush(Icon.IsNone() ? FName("F2D.Icon.Flipbook") : Icon);
									})
									.ColorAndOpacity(FFramework2DEditorStyle::Foreground())
								]
							]
						]
						// Aviso «!»: la pieza ya no existe (rojo) o falta una obligatoria (ámbar).
						+ SOverlay::Slot()
						.HAlign(HAlign_Right)
						.VAlign(VAlign_Top)
						.Padding(2.0f)
						[
							SNew(SBox)
							.WidthOverride(14.0f)
							.HeightOverride(14.0f)
							.Visibility_Lambda([this]() { return (IsMissing() || IsRequiredEmpty()) ? EVisibility::HitTestInvisible : EVisibility::Collapsed; })
							[
								SNew(SBorder)
								.BorderImage_Lambda([this]() { return Framework2DProcGenPanelUtil::BadgeBrush(IsMissing()); })
								.Padding(FMargin(0.0f))
								.HAlign(HAlign_Center)
								.VAlign(VAlign_Center)
								[
									SNew(STextBlock)
									.Text(LOCTEXT("WarningGlyph", "!"))
									.Font(F2DPalette::Font(true, 8))
									.ColorAndOpacity(FFramework2DEditorStyle::OnAccent())
								]
							]
						]
					]
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(0.0f, 3.0f, 0.0f, 0.0f)
				[
					SNew(STextBlock)
					.Visibility(bHasLabel ? EVisibility::HitTestInvisible : EVisibility::Collapsed)
					.TextStyle(&F2DPalette::Text("F2D.Text.Caption"))
					.Justification(ETextJustify::Center)
					.AutoWrapText(true)
					.Text(InArgs._Label)
				]
			]
		];

		SetToolTipText(TAttribute<FText>::CreateLambda([this]() { return GetTip(); }));
	}

	// Enfocable con el teclado (Tab). El anillo de foco lo pinta el propio hueco (el del motor
	// rodearía también la etiqueta).
	virtual bool SupportsKeyboardFocus() const override { return true; }
	virtual const FSlateBrush* GetFocusBrush() const override { return nullptr; }

	virtual FReply OnFocusReceived(const FGeometry& Geo, const FFocusEvent& Event) override
	{
		bFocusFromKeys = Event.GetCause() != EFocusCause::Mouse;
		Invalidate(EInvalidateWidgetReason::Paint);
		return SCompoundWidget::OnFocusReceived(Geo, Event);
	}

	virtual void OnFocusLost(const FFocusEvent& Event) override
	{
		bFocusFromKeys = false;
		Invalidate(EInvalidateWidgetReason::Paint);
		SCompoundWidget::OnFocusLost(Event);
	}

	virtual FReply OnKeyDown(const FGeometry& Geo, const FKeyEvent& Event) override
	{
		const FKey Key = Event.GetKey();
		if (Key == EKeys::Enter || Key == EKeys::SpaceBar)
		{
			Open(true);
			return FReply::Handled();
		}
		if (Key == EKeys::Delete || Key == EKeys::BackSpace)
		{
			// Siempre se queda aquí: Supr no debe llegar al editor (borraría el actor seleccionado).
			Clear();
			return FReply::Handled();
		}
		return SCompoundWidget::OnKeyDown(Geo, Event);
	}

	virtual FReply OnMouseButtonDown(const FGeometry& Geo, const FPointerEvent& Event) override
	{
		if (Event.GetEffectingButton() == EKeys::LeftMouseButton)
		{
			bPressed = true;
			return FReply::Handled().CaptureMouse(SharedThis(this));
		}
		// El clic derecho se queda aquí (vacía al soltar; sin esto la lista lo usaría para desplazarse).
		return Event.GetEffectingButton() == EKeys::RightMouseButton ? FReply::Handled() : FReply::Unhandled();
	}

	virtual FReply OnMouseButtonUp(const FGeometry& Geo, const FPointerEvent& Event) override
	{
		if (Event.GetEffectingButton() == EKeys::LeftMouseButton && bPressed)
		{
			bPressed = false;
			const bool bInside = Geo.IsUnderLocation(Event.GetScreenSpacePosition());
			if (bInside) { Open(false); }
			return FReply::Handled().ReleaseMouseCapture();
		}
		if (Event.GetEffectingButton() == EKeys::RightMouseButton)
		{
			Clear();
			return FReply::Handled();
		}
		return FReply::Unhandled();
	}

	virtual FReply OnMouseButtonDoubleClick(const FGeometry&, const FPointerEvent&) override
	{
		// El primer clic ya abrió el selector; el segundo no hace nada más.
		return FReply::Handled();
	}

	virtual void OnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent) override
	{
		bPressed = false;
		SCompoundWidget::OnMouseCaptureLost(CaptureLostEvent);
	}

	virtual FCursorReply OnCursorQuery(const FGeometry&, const FPointerEvent&) const override { return FCursorReply::Cursor(EMouseCursor::Hand); }

	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& Geo, const FSlateRect& Culling, FSlateWindowElementList& Out,
		int32 Layer, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override
	{
		const int32 ChildLayer = SCompoundWidget::OnPaint(Args, Geo, Culling, Out, Layer, InWidgetStyle, bParentEnabled);
		const int32 Top = ChildLayer + 1;
		const ESlateDrawEffect Effect = ShouldBeEnabled(bParentEnabled) ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect;
		const FVector2D Local = Geo.GetLocalSize();
		const float X = FMath::RoundToFloat(((float)Local.X - Size) * 0.5f);

		if (!HasValue())
		{
			// Vacío: contorno discontinuo (ámbar si es obligatorio; el «!» lo dice también).
			const FLinearColor Dim = IsHovered() ? FFramework2DEditorStyle::Foreground() : FFramework2DEditorStyle::ForegroundDim();
			const FLinearColor Color = IsRequiredEmpty() ? FFramework2DEditorStyle::Accent() : Dim.CopyWithNewOpacity(0.85f);
			F2DPalette::DashedFrame(Out, Top, Geo, Effect, X, 0.0f, Size, Size, 1.0f, 3.0f, Color);
		}
		else if (IsHovered())
		{
			F2DPalette::Frame(Out, Top, Geo, Effect, X, 0.0f, Size, Size, 1.0f, FLinearColor(1.0f, 1.0f, 1.0f, 0.7f));
		}
		// Anillo de foco del teclado (2 px de acento).
		if (bFocusFromKeys && HasKeyboardFocus())
		{
			F2DPalette::Frame(Out, Top, Geo, Effect, X, 0.0f, Size, Size, 2.0f, FFramework2DEditorStyle::Accent());
		}
		return Top;
	}

private:
	FFramework2DTilePaintMode* Mode = nullptr;
	TFunction<int32()> GetValue;
	FFramework2DOnOpenPieceSlot OnOpen;
	FSimpleDelegate OnClear;
	FText SlotName;
	float Size = 44.0f;
	bool bRequired = false;
	bool bRemovable = false;
	bool bAdd = false;
	bool bPressed = false;
	bool bFocusFromKeys = false;

	int32 Value() const { return GetValue ? GetValue() : -1; }
	bool HasValue() const { return Value() >= 0; }
	bool IsMissing() const { return Framework2DProcGenPanelUtil::IsMissing(Mode->GetTileSet(), Value()); }
	// El centro del 3x3 solo hace falta sin el centro del 5x5.
	bool IsRequiredEmpty() const
	{
		if (!bRequired || HasValue()) { return false; }
		const FFramework2DBiome* Biome = Mode->GetActiveBiome();
		return !(Biome && Biome->Ground5.At(2, 2) >= 0);
	}

	FName GetBadgeIcon() const
	{
		const int32 V = Value();
		if (V < 0 || IsMissing()) { return NAME_None; }
		if (Framework2D::IsGeneratorValue(V)) { return FName("F2D.Icon.Generator"); }
		if (Framework2D::IsFlipbookValue(V)) { return FName("F2D.Icon.Flipbook"); }
		return NAME_None;
	}

	void Open(bool bFromKeyboard)
	{
		OnOpen.ExecuteIfBound(SharedThis(this), bFromKeyboard);
	}

	void Clear()
	{
		if (bAdd) { return; }
		if (bRemovable || HasValue()) { OnClear.ExecuteIfBound(); }
	}

	FText GetTip() const
	{
		const int32 V = Value();
		FText Content;
		if (bAdd)
		{
			Content = LOCTEXT("SlotAddContent", "Adds a piece to the list: a tile, a flipbook or a generator.");
		}
		else if (V < 0)
		{
			Content = bRequired
				? LOCTEXT("SlotRequiredEmpty", "Empty. Required: without it nothing can be generated.")
				: LOCTEXT("SlotOptionalEmpty", "Empty (optional).");
		}
		else
		{
			Content = Framework2DProcGenPanelUtil::DescribeValue(Mode->GetTileSet(), V);
		}
		const FText Usage = bAdd
			? LOCTEXT("SlotUsageAdd", "Click, Enter or Space: choose the piece.")
			: bRemovable
			? LOCTEXT("SlotUsageRemovable", "Click, Enter or Space: change it · Right click, Delete or Backspace: remove it.")
			: LOCTEXT("SlotUsage", "Click, Enter or Space: choose · Right click, Delete or Backspace: clear.");
		return FText::Format(LOCTEXT("SlotTipFormat", "{0}\n{1}\n{2}"), SlotName, Content, Usage);
	}
};

// =====================================================================
//  Atlas del SELECTOR: una página entera. Clic = ese tile. En modo bloque,
//  arrastrar un bloque de 3x3 (o clic en su esquina de arriba-izquierda).
//  Con el teclado: flechas para moverse e Intro/Espacio para elegir.
// =====================================================================
class SFramework2DPieceAtlas : public SLeafWidget
{
public:
	SLATE_BEGIN_ARGS(SFramework2DPieceAtlas)
		: _bBlockMode(false)
		, _BlockSize(3)
	{}
		SLATE_ATTRIBUTE(int32, Page)
		SLATE_ATTRIBUTE(int32, Zoom)
		SLATE_ARGUMENT(bool, bBlockMode)
		SLATE_ARGUMENT(int32, BlockSize)              // 3 o 5
		SLATE_ARGUMENT(TArray<int32>, Highlight)   // valores que se marcan (lo que tiene ahora la pieza)
	SLATE_END_ARGS()

	/** InOnPicked: rectángulo elegido en tiles de la página (Min..Max incluidos). */
	void Construct(const FArguments& InArgs, FFramework2DTilePaintMode* InMode, TFunction<void(const FIntRect&)> InOnPicked)
	{
		Mode = InMode;
		Page = InArgs._Page;
		Zoom = InArgs._Zoom;
		bBlockMode = InArgs._bBlockMode;
		BlockSize = FMath::Max(1, InArgs._BlockSize);
		Highlight = InArgs._Highlight;
		OnPicked = MoveTemp(InOnPicked);
	}

	virtual FVector2D ComputeDesiredSize(float) const override
	{
		int32 W = 0, H = 0;
		const UFramework2DTileSet* Set = Mode->GetTileSet();
		if (!Set || !Set->GetPageSize(Page.Get(), W, H)) { return FVector2D(1.0f, 1.0f); }
		const int32 Z = FMath::Max(1, Zoom.Get());
		return FVector2D(W * Z, H * Z);
	}

	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& Geo, const FSlateRect& Culling, FSlateWindowElementList& Out,
		int32 Layer, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override
	{
		const UFramework2DTileSet* Set = Mode->GetTileSet();
		const int32 P = Page.Get();
		UTexture2D* Texture = Set ? Set->GetPageTexture(P) : nullptr;
		int32 AW = 0, AH = 0, Cols = 0, Rows = 0;
		if (!Texture || !Set->GetPageSize(P, AW, AH) || !GetGrid(Cols, Rows)) { return Layer; }
		const ESlateDrawEffect Effect = ShouldBeEnabled(bParentEnabled) ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect;
		const float Z = (float)FMath::Max(1, Zoom.Get());
		const float TW = Set->TileWidth * Z;
		const float TH = Set->TileHeight * Z;
		const FLinearColor Accent = FFramework2DEditorStyle::Accent();
		const FLinearColor White(1.0f, 1.0f, 1.0f, 0.9f);
		auto Box = [&](float X, float Y, float W, float H, const FLinearColor& C, int32 L)
		{
			F2DPalette::Box(Out, L, Geo, Effect, X, Y, W, H, C);
		};
		auto Frame = [&](float X, float Y, float W, float H, float T, const FLinearColor& C, int32 L)
		{
			F2DPalette::Frame(Out, L, Geo, Effect, X, Y, W, H, T, C);
		};

		// Fondo a cuadros (se ven los pixeles transparentes) y la imagen encima.
		Box(0.0f, 0.0f, AW * Z, AH * Z, FLinearColor(0.16f, 0.16f, 0.17f), Layer);
		const float Q = FMath::Max(4.0f, Z * 4.0f);
		for (float Y = 0.0f; Y < AH * Z; Y += Q)
		{
			for (float X = ((int32)(Y / Q) % 2) * Q; X < AW * Z; X += 2.0f * Q)
			{
				Box(X, Y, FMath::Min(Q, AW * Z - X), FMath::Min(Q, AH * Z - Y), FLinearColor(0.22f, 0.22f, 0.23f), Layer);
			}
		}
		AtlasBrush.SetResourceObject(Texture);
		AtlasBrush.DrawAs = ESlateBrushDrawType::Image;
		AtlasBrush.SetImageSize(FVector2D(AW, AH));
		FSlateDrawElement::MakeBox(Out, Layer + 1, Geo.ToPaintGeometry(FVector2D(AW * Z, AH * Z), FSlateLayoutTransform(FVector2D(0.0f, 0.0f))),
			&AtlasBrush, Effect, InWidgetStyle.GetColorAndOpacityTint());

		// Rejilla de tiles.
		for (int32 C = 1; C < Cols; ++C) { Box(C * TW, 0.0f, 1.0f, Rows * TH, FLinearColor(1.0f, 1.0f, 1.0f, 0.18f), Layer + 2); }
		for (int32 R = 1; R < Rows; ++R) { Box(0.0f, R * TH, Cols * TW, 1.0f, FLinearColor(1.0f, 1.0f, 1.0f, 0.18f), Layer + 2); }

		// Lo que tiene ahora la pieza: relleno y marco de acento.
		for (const int32 V : Highlight)
		{
			if (!Framework2D::IsAtlasTileValue(V) || Framework2D::TilePageOf(V) != P) { continue; }
			const int32 LocalTile = Framework2D::TileLocalOf(V);
			const float X = (LocalTile % Cols) * TW;
			const float Y = (LocalTile / Cols) * TH;
			Box(X, Y, TW, TH, Accent.CopyWithNewOpacity(0.22f), Layer + 3);
			Frame(X, Y, TW, TH, 2.0f, Accent, Layer + 4);
		}

		// Lo que se va a elegir. Al arrastrar un bloque: ámbar si es de 3x3, discontinuo si no vale.
		if (bDragging && bBlockMode)
		{
			const FIntRect R = DragRect();
			const int32 WT = R.Max.X - R.Min.X + 1;
			const int32 HT = R.Max.Y - R.Min.Y + 1;
			const bool bValid = WT == BlockSize && HT == BlockSize;
			Box(R.Min.X * TW, R.Min.Y * TH, WT * TW, HT * TH, (bValid ? Accent : White).CopyWithNewOpacity(0.16f), Layer + 5);
			if (bValid) { Frame(R.Min.X * TW, R.Min.Y * TH, WT * TW, HT * TH, 2.0f, Accent, Layer + 6); }
			else { F2DPalette::DashedFrame(Out, Layer + 6, Geo, Effect, R.Min.X * TW, R.Min.Y * TH, WT * TW, HT * TH, 2.0f, 4.0f, White); }
		}
		else
		{
			const bool bKeys = bShowCursor && HasKeyboardFocus();
			const FIntPoint Point = bKeys ? KeyCursor : HoverTile;
			if (Point.X >= 0 && Point.Y >= 0 && Point.X < Cols && Point.Y < Rows)
			{
				const FIntPoint A = bBlockMode ? BlockAnchor(Point, Cols, Rows) : Point;
				const int32 N = bBlockMode ? BlockSize : 1;
				if (A.X >= 0) { Frame(A.X * TW, A.Y * TH, N * TW, N * TH, bKeys ? 2.0f : 1.0f, White, Layer + 6); }
			}
		}
		// Foco del teclado: contorno de todo el atlas.
		if (bShowCursor && HasKeyboardFocus()) { Frame(0.0f, 0.0f, Cols * TW, Rows * TH, 1.0f, Accent, Layer + 6); }
		return Layer + 6;
	}

	virtual bool SupportsKeyboardFocus() const override { return true; }
	virtual const FSlateBrush* GetFocusBrush() const override { return nullptr; }

	virtual FReply OnFocusReceived(const FGeometry& Geo, const FFocusEvent& Event) override
	{
		bShowCursor = Event.GetCause() != EFocusCause::Mouse;
		int32 Cols = 0, Rows = 0;
		if (GetGrid(Cols, Rows) && (KeyCursor.X < 0 || KeyCursor.X >= Cols || KeyCursor.Y >= Rows)) { KeyCursor = StartCursor(Cols, Rows); }
		return SLeafWidget::OnFocusReceived(Geo, Event);
	}

	virtual void OnFocusLost(const FFocusEvent& Event) override
	{
		bShowCursor = false;
		SLeafWidget::OnFocusLost(Event);
	}

	virtual FReply OnKeyDown(const FGeometry& Geo, const FKeyEvent& Event) override
	{
		int32 Cols = 0, Rows = 0;
		if (!GetGrid(Cols, Rows)) { return SLeafWidget::OnKeyDown(Geo, Event); }
		const FKey Key = Event.GetKey();
		int32 Dx = 0, Dy = 0;
		if (Key == EKeys::Left) { Dx = -1; }
		else if (Key == EKeys::Right) { Dx = 1; }
		else if (Key == EKeys::Up) { Dy = -1; }
		else if (Key == EKeys::Down) { Dy = 1; }
		if (Dx != 0 || Dy != 0)
		{
			if (KeyCursor.X < 0) { KeyCursor = StartCursor(Cols, Rows); }
			KeyCursor.X = FMath::Clamp(KeyCursor.X + Dx, 0, Cols - 1);
			KeyCursor.Y = FMath::Clamp(KeyCursor.Y + Dy, 0, Rows - 1);
			bShowCursor = true;
			return FReply::Handled();
		}
		if (Key == EKeys::Enter || Key == EKeys::SpaceBar)
		{
			if (KeyCursor.X < 0 || KeyCursor.X >= Cols || KeyCursor.Y >= Rows) { KeyCursor = StartCursor(Cols, Rows); }
			Pick(FIntRect(KeyCursor, KeyCursor));
			return FReply::Handled();
		}
		return SLeafWidget::OnKeyDown(Geo, Event);
	}

	virtual FReply OnMouseButtonDown(const FGeometry& Geo, const FPointerEvent& Event) override
	{
		if (Event.GetEffectingButton() != EKeys::LeftMouseButton) { return FReply::Unhandled(); }
		const FIntPoint T = TileAt(Geo, Event, false);
		if (T.X < 0) { return FReply::Unhandled(); }
		bDragging = true;
		bShowCursor = false;
		DragStart = T;
		DragEnd = T;
		return FReply::Handled().CaptureMouse(SharedThis(this));
	}

	virtual FReply OnMouseMove(const FGeometry& Geo, const FPointerEvent& Event) override
	{
		HoverTile = TileAt(Geo, Event, bDragging);
		if (bDragging && HoverTile.X >= 0) { DragEnd = HoverTile; }
		return bDragging ? FReply::Handled() : FReply::Unhandled();
	}

	virtual FReply OnMouseButtonUp(const FGeometry& Geo, const FPointerEvent& Event) override
	{
		if (!bDragging || Event.GetEffectingButton() != EKeys::LeftMouseButton) { return FReply::Unhandled(); }
		bDragging = false;
		if (bBlockMode)
		{
			Pick(DragRect());
		}
		else
		{
			// Una pieza: el tile sobre el que se suelta (si se suelta fuera, nada).
			const FIntPoint T = TileAt(Geo, Event, false);
			if (T.X >= 0) { Pick(FIntRect(T, T)); }
		}
		return FReply::Handled().ReleaseMouseCapture();
	}

	virtual void OnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent) override
	{
		bDragging = false;
		SLeafWidget::OnMouseCaptureLost(CaptureLostEvent);
	}

	virtual void OnMouseLeave(const FPointerEvent& Event) override
	{
		SLeafWidget::OnMouseLeave(Event);
		HoverTile = FIntPoint(-1, -1);
	}

	virtual FCursorReply OnCursorQuery(const FGeometry&, const FPointerEvent&) const override { return FCursorReply::Cursor(EMouseCursor::Crosshairs); }

private:
	FFramework2DTilePaintMode* Mode = nullptr;
	TAttribute<int32> Page;
	TAttribute<int32> Zoom;
	bool bBlockMode = false;
	int32 BlockSize = 3;
	TArray<int32> Highlight;
	TFunction<void(const FIntRect&)> OnPicked;
	mutable FSlateBrush AtlasBrush;
	bool bDragging = false;
	bool bShowCursor = false;
	FIntPoint DragStart = FIntPoint(0, 0);
	FIntPoint DragEnd = FIntPoint(0, 0);
	FIntPoint HoverTile = FIntPoint(-1, -1);
	FIntPoint KeyCursor = FIntPoint(-1, -1);

	bool GetGrid(int32& OutCols, int32& OutRows) const
	{
		const UFramework2DTileSet* Set = Mode->GetTileSet();
		return Set && Set->GetPageGrid(Page.Get(), OutCols, OutRows) && OutCols > 0 && OutRows > 0;
	}

	FIntRect DragRect() const
	{
		return FIntRect(
			FIntPoint(FMath::Min(DragStart.X, DragEnd.X), FMath::Min(DragStart.Y, DragEnd.Y)),
			FIntPoint(FMath::Max(DragStart.X, DragEnd.X), FMath::Max(DragStart.Y, DragEnd.Y)));
	}

	/** Esquina de arriba-izquierda del bloque de 3x3 que empieza en Point (se mete dentro de la página). */
	FIntPoint BlockAnchor(const FIntPoint& Point, int32 Cols, int32 Rows) const
	{
		if (Cols < BlockSize || Rows < BlockSize) { return FIntPoint(-1, -1); }
		return FIntPoint(FMath::Min(Point.X, Cols - BlockSize), FMath::Min(Point.Y, Rows - BlockSize));
	}

	/** El cursor del teclado empieza en lo que tiene ahora la pieza (si está en esta página). */
	FIntPoint StartCursor(int32 Cols, int32 Rows) const
	{
		const int32 P = Page.Get();
		for (const int32 V : Highlight)
		{
			if (!Framework2D::IsAtlasTileValue(V) || Framework2D::TilePageOf(V) != P) { continue; }
			const int32 LocalTile = Framework2D::TileLocalOf(V);
			if (LocalTile / Cols < Rows) { return FIntPoint(LocalTile % Cols, LocalTile / Cols); }
		}
		return FIntPoint(0, 0);
	}

	FIntPoint TileAt(const FGeometry& Geo, const FPointerEvent& Event, bool bClamp) const
	{
		const UFramework2DTileSet* Set = Mode->GetTileSet();
		int32 Cols = 0, Rows = 0;
		if (!Set || !GetGrid(Cols, Rows)) { return FIntPoint(-1, -1); }
		const FVector2D LocalPos = Geo.AbsoluteToLocal(Event.GetScreenSpacePosition());
		const float Z = (float)FMath::Max(1, Zoom.Get());
		int32 X = FMath::FloorToInt((float)LocalPos.X / (Set->TileWidth * Z));
		int32 Y = FMath::FloorToInt((float)LocalPos.Y / (Set->TileHeight * Z));
		if (bClamp) { X = FMath::Clamp(X, 0, Cols - 1); Y = FMath::Clamp(Y, 0, Rows - 1); }
		if (X < 0 || Y < 0 || X >= Cols || Y >= Rows) { return FIntPoint(-1, -1); }
		return FIntPoint(X, Y);
	}

	void Pick(const FIntRect& Rect)
	{
		if (OnPicked) { OnPicked(Rect); }
	}
};

// =====================================================================
//  SELECTOR de piezas (menú emergente): páginas del atlas, el atlas, tiras
//  de flipbooks y de generadores, «Usar el pincel actual» y «Vaciar». Esc cierra.
// =====================================================================
class SFramework2DPiecePicker : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SFramework2DPiecePicker) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TSharedRef<SFramework2DProcGenPanel>& InPanel, const FFramework2DPieceTarget& InTarget)
	{
		Panel = InPanel;
		Mode = InPanel->GetMode();
		Target = InTarget;
		const UFramework2DTileSet* Set = Mode->GetTileSet();
		const FFramework2DBiome* Biome = Mode->GetActiveBiome();

		// Lo que se marca en el atlas: lo que tiene ahora la pieza (en modo bloque, las 9).
		if (Target.IsBlock())
		{
			if (Biome && Target.BlockSize == 5)
			{
				for (const int32 V : Biome->Ground5.Pieces) { if (V >= 0) { Highlight.Add(V); } }
			}
			else if (Biome)
			{
				const FFramework2DTile3x3& Block = Target.bBackground ? Biome->Background : Biome->Ground;
				for (int32 I = 0; I < FFramework2DTile3x3::Num; ++I)
				{
					if (Block.Get(I) >= 0) { Highlight.Add(Block.Get(I)); }
				}
			}
		}
		else
		{
			const int32 Current = InPanel->GetTargetValue(Target);
			if (Current >= 0) { Highlight.Add(Current); }
		}

		// Página inicial: la de lo que tiene ahora la pieza; si no, la que se ve en «Pintar».
		Page = Mode->ActivePage;
		for (const int32 V : Highlight)
		{
			if (Framework2D::IsAtlasTileValue(V)) { Page = Framework2D::TilePageOf(V); break; }
		}
		if (Set && Set->FindPageIndex(Page) == INDEX_NONE) { Page = Set->GetPageIdAt(0); }

		// Zoom: que el atlas quepa en unos 560 px, con tiles de al menos 20 px para apuntar bien.
		int32 AW = 0, AH = 0;
		const bool bHasImage = Set && Set->GetPageSize(Page, AW, AH) && AW > 0;
		const int32 TileW = Set ? FMath::Max(1, Set->TileWidth) : 16;
		const int32 Fit = bHasImage ? FMath::Max(1, 560 / AW) : 2;
		Zoom = FMath::Clamp(FMath::Max(FMath::Min(Fit, 4), FMath::DivideAndRoundUp(20, TileW)), 1, F2DPalette::MaxZoom);
		const float Width = FMath::Clamp(bHasImage ? (float)(AW * Zoom + 12) : 360.0f, 340.0f, 584.0f);

		TWeakPtr<SFramework2DProcGenPanel> WeakPanel = InPanel;
		FFramework2DTilePaintMode* M = Mode;
		const FFramework2DPieceTarget T = Target;
		auto HasImage = [this]()
		{
			const UFramework2DTileSet* S = Mode->GetTileSet();
			int32 W = 0, H = 0;
			return S && S->GetPageTexture(Page) && S->GetPageSize(Page, W, H);
		};

		const FText Hint = Target.IsBlock()
			? FText::Format(LOCTEXT("PickerHintBlockN", "Drag a block of {0} × {0} tiles (or click its top-left corner): fills its {1} pieces. Arrows and Enter with the keyboard."), Target.BlockSize, Target.BlockSize * Target.BlockSize)
			: LOCTEXT("PickerHint", "Click a tile to choose it (or a flipbook or generator below). Arrows and Enter with the keyboard; Esc closes.");

		ChildSlot
		[
			SNew(SBorder)
			.BorderImage(F2DPalette::Brush("F2D.Card"))
			.Padding(FMargin(10.0f, 8.0f, 10.0f, 10.0f))
			[
				SNew(SBox)
				.WidthOverride(Width)
				[
					SNew(SVerticalBox)
					// Título: qué pieza se está eligiendo.
					+ SVerticalBox::Slot()
					.AutoHeight()
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot()
						.AutoWidth()
						.VAlign(VAlign_Center)
						.Padding(0.0f, 0.0f, 6.0f, 0.0f)
						[
							SNew(SBox)
							.WidthOverride(16.0f)
							.HeightOverride(16.0f)
							[
								SNew(SImage)
								.Image(F2DPalette::Brush(Target.IsBlock() ? FName("F2D.Icon.Grid") : FName("F2D.Icon.Biome")))
								.ColorAndOpacity(FFramework2DEditorStyle::Accent())
							]
						]
						+ SHorizontalBox::Slot()
						.FillWidth(1.0f)
						.VAlign(VAlign_Center)
						[
							SNew(STextBlock)
							.TextStyle(&F2DPalette::Text("F2D.Text.Body"))
							.Font(F2DPalette::Font(true, 10))
							.AutoWrapText(true)
							.Text(Target.IsBlock() || Target.IsAdd()
								? Framework2DProcGenPanelUtil::TargetName(Target)
								: FText::Format(LOCTEXT("PickerTitle", "Piece: {0}"), Framework2DProcGenPanelUtil::TargetName(Target)))
						]
					]
					// Lo que tiene ahora.
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(0.0f, 2.0f, 0.0f, 8.0f)
					[
						F2DPalette::Caption(TAttribute<FText>::CreateLambda([WeakPanel, M, T]() -> FText
						{
							const TSharedPtr<SFramework2DProcGenPanel> P = WeakPanel.Pin();
							if (!P || T.IsBlock() || T.IsAdd()) { return LOCTEXT("PickerNowNone", "Choose from the atlas, or a flipbook or a generator."); }
							return FText::Format(LOCTEXT("PickerNow", "Now: {0}"), Framework2DProcGenPanelUtil::DescribeValue(M->GetTileSet(), P->GetTargetValue(T)));
						}))
					]
					// Páginas del atlas (solo si hay más de una).
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(0.0f, 0.0f, 0.0f, 6.0f)
					[
						SAssignNew(PageTabs, SWrapBox)
						.UseAllottedSize(true)
						.InnerSlotPadding(FVector2D(3.0f, 3.0f))
						.Visibility_Lambda([M]() { const UFramework2DTileSet* S = M->GetTileSet(); return (S && S->GetNumPages() > 1) ? EVisibility::Visible : EVisibility::Collapsed; })
					]
					// El atlas (se desplaza en las dos direcciones si no cabe).
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
								SNew(SBox)
								.MaxDesiredHeight(320.0f)
								.Visibility_Lambda([HasImage]() { return HasImage() ? EVisibility::Visible : EVisibility::Collapsed; })
								[
									SNew(SScrollBox)
									+ SScrollBox::Slot()
									[
										SNew(SScrollBox)
										.Orientation(Orient_Horizontal)
										.ConsumeMouseWheel(EConsumeMouseWheel::Never)
										+ SScrollBox::Slot()
										[
											SNew(SFramework2DPieceAtlas, M, [this](const FIntRect& Rect) { HandleAtlasPick(Rect); })
											.Page_Lambda([this]() { return Page; })
											.Zoom_Lambda([this]() { return Zoom; })
											.bBlockMode(Target.IsBlock())
											.BlockSize(Target.BlockSize)
											.Highlight(Highlight)
											.ToolTipText(Hint)
										]
									]
								]
							]
							+ SVerticalBox::Slot()
							.AutoHeight()
							.Padding(FMargin(6.0f, 10.0f))
							[
								SNew(STextBlock)
								.TextStyle(&F2DPalette::Text("F2D.Text.Caption"))
								.AutoWrapText(true)
								.Text(LOCTEXT("PickerNoImage", "This atlas page has no image yet."))
								.Visibility_Lambda([HasImage]() { return HasImage() ? EVisibility::Collapsed : EVisibility::Visible; })
							]
						]
					]
					// Ayuda (o por qué no valió el bloque) y zoom.
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(0.0f, 6.0f, 0.0f, 0.0f)
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot()
						.FillWidth(1.0f)
						.VAlign(VAlign_Center)
						[
							F2DPalette::Caption(TAttribute<FText>::CreateLambda([this, Hint]() { return Message.IsEmpty() ? Hint : Message; }))
						]
						+ SHorizontalBox::Slot()
						.AutoWidth()
						.VAlign(VAlign_Center)
						.Padding(6.0f, 0.0f, 0.0f, 0.0f)
						[
							F2DPalette::IconButton("F2D.Icon.ZoomOut", LOCTEXT("PickerZoomOutTip", "Zoom the atlas out"),
								FOnClicked::CreateLambda([this]() { Zoom = FMath::Max(1, Zoom - 1); return FReply::Handled(); }),
								TAttribute<bool>::CreateLambda([this]() { return Zoom > 1; }))
						]
						+ SHorizontalBox::Slot()
						.AutoWidth()
						.VAlign(VAlign_Center)
						[
							F2DPalette::IconButton("F2D.Icon.ZoomIn", LOCTEXT("PickerZoomInTip", "Zoom the atlas in"),
								FOnClicked::CreateLambda([this]() { Zoom = FMath::Min(F2DPalette::MaxZoom, Zoom + 1); return FReply::Handled(); }),
								TAttribute<bool>::CreateLambda([this]() { return Zoom < F2DPalette::MaxZoom; }))
						]
					]
					// Flipbooks y generadores (no en modo bloque: un 3x3 son tiles del atlas).
					+ SVerticalBox::Slot()
					.AutoHeight()
					[
						MakeStrip(false)
					]
					+ SVerticalBox::Slot()
					.AutoHeight()
					[
						MakeStrip(true)
					]
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(0.0f, 10.0f, 0.0f, 0.0f)
					[
						MakeFooter()
					]
				]
			]
		];
		RebuildPageTabs();
	}

	// El menú le da el foco al abrirse: así Esc y Tab funcionan desde el primer momento.
	virtual bool SupportsKeyboardFocus() const override { return true; }

	virtual FReply OnKeyDown(const FGeometry& Geo, const FKeyEvent& Event) override
	{
		if (Event.GetKey() == EKeys::Escape)
		{
			if (const TSharedPtr<SFramework2DProcGenPanel> P = Panel.Pin()) { P->ClosePicker(); }
			return FReply::Handled();
		}
		return SCompoundWidget::OnKeyDown(Geo, Event);
	}

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override
	{
		SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
		// Las pestañas se rehacen aquí y no en su propio clic (no se destruye un botón mientras se pulsa).
		if (bTabsDirty)
		{
			bTabsDirty = false;
			RebuildPageTabs();
		}
	}

private:
	TWeakPtr<SFramework2DProcGenPanel> Panel;
	FFramework2DTilePaintMode* Mode = nullptr;
	FFramework2DPieceTarget Target;
	int32 Page = 0;
	int32 Zoom = 2;
	FText Message;
	TArray<int32> Highlight;
	TSharedPtr<SWrapBox> PageTabs;
	bool bTabsDirty = false;

	void RebuildPageTabs()
	{
		if (!PageTabs.IsValid()) { return; }
		PageTabs->ClearChildren();
		const UFramework2DTileSet* Set = Mode->GetTileSet();
		if (!Set) { return; }
		for (int32 I = 0; I < Set->GetNumPages(); ++I)
		{
			const int32 PageId = Set->GetPageIdAt(I);
			const bool bActive = PageId == Page;
			PageTabs->AddSlot()
			[
				SNew(SButton)
				.ButtonStyle(&F2DPalette::Button(bActive ? FName("F2D.Button.ToolActive") : FName("F2D.Button.Secondary")))
				.ContentPadding(FMargin(8.0f, 0.0f))
				.ToolTipText(FText::Format(LOCTEXT("PickerPageTip", "Show atlas «{0}» in the picker."), Set->GetPageDisplayName(PageId)))
				.OnClicked_Lambda([this, PageId]()
				{
					if (Page != PageId)
					{
						Page = PageId;
						Message = FText::GetEmpty();
						bTabsDirty = true;
					}
					return FReply::Handled();
				})
				[
					SNew(STextBlock)
					.Font(F2DPalette::Font(bActive, 9))
					.ColorAndOpacity(FSlateColor::UseForeground())
					.Text(Set->GetPageDisplayName(PageId))
				]
			];
		}
	}

	void HandleAtlasPick(const FIntRect& Rect)
	{
		const TSharedPtr<SFramework2DProcGenPanel> P = Panel.Pin();
		const UFramework2DTileSet* Set = Mode->GetTileSet();
		int32 Cols = 0, Rows = 0;
		if (!P || !Set || !Set->GetPageGrid(Page, Cols, Rows) || Cols <= 0 || Rows <= 0) { return; }
		const int32 W = Rect.Max.X - Rect.Min.X + 1;
		const int32 H = Rect.Max.Y - Rect.Min.Y + 1;
		if (Target.IsBlock())
		{
			const int32 N = Target.BlockSize;
			FIntPoint Corner = Rect.Min;
			if (W == 1 && H == 1)
			{
				// Un clic: el bloque que empieza ahí (metido dentro de la página).
				Corner.X = FMath::Min(Corner.X, Cols - N);
				Corner.Y = FMath::Min(Corner.Y, Rows - N);
			}
			else if (W != N || H != N)
			{
				Message = FText::Format(LOCTEXT("PickerBlockWrongSizeN", "You selected {0} × {1} tiles: drag a block of {2} × {2} (or click its top-left corner)."), W, H, N);
				return;
			}
			if (Corner.X < 0 || Corner.Y < 0)
			{
				Message = FText::Format(LOCTEXT("PickerBlockTooSmallN", "This page has fewer than {0} × {0} tiles: choose another."), N);
				return;
			}
			P->PickBlock(Target, Framework2D::MakeTileValue(Page, Corner.Y * Cols + Corner.X));
			return;
		}
		P->PickValue(Target, Framework2D::MakeTileValue(Page, Rect.Min.Y * Cols + Rect.Min.X));
	}

	/** Tira de flipbooks (miniaturas animadas) o de generadores (su primer sprite). Clic = elegir. */
	TSharedRef<SWidget> MakeStrip(bool bGenerators)
	{
		const UFramework2DTileSet* Set = Mode->GetTileSet();
		if (Target.IsBlock() || !Set || (bGenerators ? Set->Generators.Num() : Set->Flipbooks.Num()) == 0)
		{
			return SNullWidget::NullWidget;
		}
		TWeakPtr<SFramework2DProcGenPanel> WeakPanel = Panel;
		FFramework2DTilePaintMode* M = Mode;
		const FFramework2DPieceTarget T = Target;
		TSharedRef<SWrapBox> Wrap = SNew(SWrapBox)
			.UseAllottedSize(true)
			.InnerSlotPadding(FVector2D(4.0f, 4.0f));

		const int32 Num = bGenerators ? Set->Generators.Num() : Set->Flipbooks.Num();
		for (int32 I = 0; I < Num; ++I)
		{
			const int32 Value = bGenerators ? Framework2D::MakeGeneratorValue(Set->Generators[I].Id) : Framework2D::MakeFlipbookValue(Set->Flipbooks[I].Id);
			const FText Tip = bGenerators
				? FText::Format(LOCTEXT("PickerGeneratorTip", "Generator «{0}»: scatters {1} {1}|plural(one=sprite,other=sprites) when baking. Click: use it."),
					FText::FromName(Set->Generators[I].Name), Set->Generators[I].Sprites.Num())
				: FText::Format(LOCTEXT("PickerFlipbookTip", "Flipbook «{0}»: {1} {1}|plural(one=frame,other=frames). Click: use it."),
					FText::FromName(Set->Flipbooks[I].Name), Set->Flipbooks[I].Frames.Num());
			// Lo que tiene ahora la pieza sale con el fondo ámbar.
			const bool bCurrent = Highlight.Contains(Value);
			Wrap->AddSlot()
			[
				SNew(SButton)
				.ButtonStyle(&F2DPalette::ShapeButtonStyle(bCurrent))
				.ContentPadding(FMargin(0.0f))
				.ToolTipText(Tip)
				.OnClicked_Lambda([WeakPanel, T, Value]()
				{
					if (const TSharedPtr<SFramework2DProcGenPanel> P = WeakPanel.Pin()) { P->PickValue(T, Value); }
					return FReply::Handled();
				})
				[
					SNew(SFramework2DTileThumb, M, [M, Value]() { return Framework2DProcGenPanelUtil::ThumbOf(M->GetTileSet(), Value); })
					.Size(32.0f)
					.bAnimated(!bGenerators)
				]
			];
		}

		return SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 10.0f, 0.0f, 4.0f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(0.0f, 0.0f, 6.0f, 0.0f)
				[
					SNew(SImage)
					.Image(F2DPalette::Brush(bGenerators ? FName("F2D.Icon.Generator") : FName("F2D.Icon.Flipbook")))
					.ColorAndOpacity(FFramework2DEditorStyle::ForegroundDim())
				]
				+ SHorizontalBox::Slot()
				.FillWidth(1.0f)
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.TextStyle(&F2DPalette::Text("F2D.Text.Section"))
					.Text((bGenerators ? LOCTEXT("PickerGenerators", "Generators") : LOCTEXT("PickerFlipbooks", "Flipbooks")).ToUpper())
				]
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				Wrap
			];
	}

	TSharedRef<SWidget> MakeFooter()
	{
		TWeakPtr<SFramework2DProcGenPanel> WeakPanel = Panel;
		FFramework2DTilePaintMode* M = Mode;
		const FFramework2DPieceTarget T = Target;
		TSharedRef<SWrapBox> Footer = SNew(SWrapBox)
			.UseAllottedSize(true)
			.InnerSlotPadding(FVector2D(4.0f, 4.0f));

		if (T.IsBlock())
		{
			Footer->AddSlot()
			[
				Framework2DProcGenPanelUtil::TextButton("F2D.Icon.Replace", LOCTEXT("PickerUseSelection", "Use the atlas selection"),
					TAttribute<FText>::CreateLambda([M, T]()
					{
						const bool bCan = T.BlockSize == 5 ? M->CanUseSelectionAs5x5() : M->CanUseSelectionAs3x3();
						return bCan
							? FText::Format(LOCTEXT("PickerUseSelectionTipN", "Fills the pieces with the {0} × {0} tile block selected in the atlas of the Paint tab."), T.BlockSize)
							: FText::Format(LOCTEXT("PickerUseSelectionOffTipN", "First select a block of {0} × {0} tiles in the atlas of the Paint tab (with no flipbook or generator as the brush)."), T.BlockSize);
					}),
					FOnClicked::CreateLambda([WeakPanel, T]()
					{
						if (const TSharedPtr<SFramework2DProcGenPanel> P = WeakPanel.Pin())
						{
							if (T.BlockSize == 5) { P->UseSelectionAs5x5(); }
							else { P->UseSelectionAs3x3(T.bBackground); }
						}
						return FReply::Handled();
					}),
					TAttribute<bool>::CreateLambda([M, T]() { return T.BlockSize == 5 ? M->CanUseSelectionAs5x5() : M->CanUseSelectionAs3x3(); }), false)
			];
			Footer->AddSlot()
			[
				Framework2DProcGenPanelUtil::TextButton("F2D.Icon.Trash", LOCTEXT("PickerClearBlock", "Clear the 3×3"),
					LOCTEXT("PickerClearBlockTip", "Clears the 9 pieces of this 3×3 (Ctrl+Z undoes it)."),
					FOnClicked::CreateLambda([WeakPanel, T]()
					{
						if (const TSharedPtr<SFramework2DProcGenPanel> P = WeakPanel.Pin()) { P->ClearTarget(T); }
						return FReply::Handled();
					}),
					TAttribute<bool>(Highlight.Num() > 0), false)
			];
			return Footer;
		}

		Footer->AddSlot()
		[
			Framework2DProcGenPanelUtil::TextButton("F2D.Tool.Paint", LOCTEXT("PickerUseBrush", "Use the current brush"),
				TAttribute<FText>::CreateLambda([M]()
				{
					const int32 Brush = M->GetBrushValue();
					return Brush >= 0
						? FText::Format(LOCTEXT("PickerUseBrushTip", "Uses what you have as the brush in the Paint tab: {0}"), Framework2DProcGenPanelUtil::DescribeValue(M->GetTileSet(), Brush))
						: LOCTEXT("PickerUseBrushOffTip", "No brush: choose a tile, a flipbook or a generator in the Paint tab.");
				}),
				FOnClicked::CreateLambda([WeakPanel, M, T]()
				{
					const TSharedPtr<SFramework2DProcGenPanel> P = WeakPanel.Pin();
					const int32 Brush = M->GetBrushValue();
					if (P && Brush >= 0) { P->PickValue(T, Brush); }
					return FReply::Handled();
				}),
				TAttribute<bool>::CreateLambda([M]() { return M->GetBrushValue() >= 0; }), false)
		];
		if (!T.IsAdd())
		{
			const bool bList = T.Kind == EFramework2DPieceTargetKind::Variant || T.Kind == EFramework2DPieceTargetKind::Decoration;
			Footer->AddSlot()
			[
				Framework2DProcGenPanelUtil::TextButton("F2D.Icon.Trash", bList ? LOCTEXT("PickerRemove", "Remove") : LOCTEXT("PickerClear", "Clear"),
					bList ? LOCTEXT("PickerRemoveTip", "Removes this item from the list (Ctrl+Z undoes it).") : LOCTEXT("PickerClearTip", "Leaves this slot empty (Ctrl+Z undoes it)."),
					FOnClicked::CreateLambda([WeakPanel, T]()
					{
						if (const TSharedPtr<SFramework2DProcGenPanel> P = WeakPanel.Pin()) { P->ClearTarget(T); }
						return FReply::Handled();
					}),
					TAttribute<bool>::CreateLambda([WeakPanel, T, bList]()
					{
						const TSharedPtr<SFramework2DProcGenPanel> P = WeakPanel.Pin();
						return P.IsValid() && (bList || P->GetTargetValue(T) >= 0);
					}), false)
			];
		}
		return Footer;
	}
};

// =====================================================================
//  Panel
// =====================================================================
void SFramework2DProcGenPanel::Construct(const FArguments& InArgs, FFramework2DTilePaintMode* InMode)
{
	Mode = InMode;

	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot().AutoHeight()                         [ MakeBiomeCard() ]
		+ SVerticalBox::Slot().AutoHeight().Padding(0, 6, 0, 0)  [ MakePiecesCard() ]
		+ SVerticalBox::Slot().AutoHeight().Padding(0, 6, 0, 0)  [ MakeSceneryCard() ]
		+ SVerticalBox::Slot().AutoHeight().Padding(0, 6, 0, 0)  [ MakeRecipeCard() ]
		+ SVerticalBox::Slot().AutoHeight().Padding(0, 6, 0, 0)  [ MakeGenerateCard() ]
	];

	RebuildBiomes();
	LastBiomesSignature = ComputeBiomesSignature();
	RebuildVariants();
	RebuildDecorations();
	RebuildBackdrops();
	RebuildProps();
	LastPiecesSignature = ComputePiecesSignature();
}

SFramework2DProcGenPanel::~SFramework2DProcGenPanel()
{
	// El selector vive en su propia ventana: que no se quede abierto apuntando a un panel muerto
	// (al salir del modo con el selector abierto). Al cerrar el editor, Slate ya lo ha cerrado.
	const TSharedPtr<IMenu> Menu = PickerMenu.Pin();
	PickerMenu.Reset();
	if (Menu.IsValid() && FSlateApplication::IsInitialized())
	{
		Menu->Dismiss();
	}
}

void SFramework2DProcGenPanel::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);

	// Las listas solo se rehacen si cambia su forma (qué biomas, cuántas variantes y adornos,
	// cuál es el activo); lo demás (nombres, piezas, pesos) lo leen las propias filas.
	const uint32 BiomesSignature = ComputeBiomesSignature();
	if (BiomesSignature != LastBiomesSignature)
	{
		LastBiomesSignature = BiomesSignature;
		RebuildBiomes();
	}
	const uint32 PiecesSignature = ComputePiecesSignature();
	if (PiecesSignature != LastPiecesSignature)
	{
		LastPiecesSignature = PiecesSignature;
		RebuildVariants();
		RebuildDecorations();
		RebuildBackdrops();
		RebuildProps();
	}
	// Si el bioma cambia con el selector abierto (Ctrl+Z, otro mapa), lo que elegía ya no vale.
	if (IsPickerOpen() && Mode->GetActiveBiomeId() != PickerBiomeId)
	{
		ClosePicker();
	}
}

uint32 SFramework2DProcGenPanel::ComputeBiomesSignature() const
{
	const UFramework2DTileSet* Set = Mode->GetTileSet();
	uint32 H = GetTypeHash(Set);
	H = HashCombine(H, GetTypeHash(Set ? Set->Biomes.Num() : -1));
	if (Set)
	{
		for (const FFramework2DBiome& Biome : Set->Biomes) { H = HashCombine(H, GetTypeHash(Biome.Id)); }
	}
	return H;
}

uint32 SFramework2DProcGenPanel::ComputePiecesSignature() const
{
	const FFramework2DBiome* Biome = Mode->GetActiveBiome();
	uint32 H = GetTypeHash(Mode->GetTileSet());
	H = HashCombine(H, GetTypeHash(Biome ? Biome->Id : INDEX_NONE));
	H = HashCombine(H, GetTypeHash(Biome ? Biome->CenterVariants.Num() : -1));
	H = HashCombine(H, GetTypeHash(Biome ? Biome->Decorations.Num() : -1));
	H = HashCombine(H, GetTypeHash(Biome ? Biome->Backdrops.Num() : -1));
	H = HashCombine(H, GetTypeHash(Biome ? Biome->Props.Num() : -1));
	return H;
}

// ---------------------------------------------------------------------
//  1. Bioma
// ---------------------------------------------------------------------
TSharedRef<SWidget> SFramework2DProcGenPanel::MakeBiomeCard()
{
	FFramework2DTilePaintMode* M = Mode;
	TSharedRef<SWidget> AddButton = F2DPalette::IconButton("F2D.Icon.Add",
		LOCTEXT("NewBiomeTip", "New empty biome (it becomes the active one). Then choose its pieces: with the center of the 3×3 terrain you can already generate."),
		FOnClicked::CreateLambda([M]() { M->CreateBiome(); F2DPalette::RedrawViewports(); return FReply::Handled(); }),
		TAttribute<bool>::CreateLambda([M]() { return M->GetTileSet() != nullptr; }));

	return F2DPalette::Card(
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			F2DPalette::CardHeader("F2D.Icon.Biome", LOCTEXT("BiomesTitle", "Biome"), AddButton)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 2.0f, 0.0f, 8.0f)
		[
			F2DPalette::Caption(LOCTEXT("BiomesHelp", "The pieces the level is built from (saved in the Tile Set). Click: use it in this map · Double click or F2: rename."))
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SAssignNew(BiomesBox, SVerticalBox)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Left)
		.Padding(0.0f, 8.0f, 0.0f, 0.0f)
		[
			Framework2DProcGenPanelUtil::TextButton("F2D.Icon.Grid", LOCTEXT("TemplateTTiles", "T_Tiles biomes (5×5)"),
				TAttribute<FText>::CreateLambda([M]()
				{
					const UFramework2DTileSet* S = M->GetTileSet();
					const FText PageName = S ? S->GetPageDisplayName(M->ActivePage) : FText::GetEmpty();
					return FText::Format(LOCTEXT("TemplateTTilesTip", "Creates «Forest (T_Tiles)» and «Rock (T_Tiles)» from the active atlas page («{0}»), which must have the T_Tiles layout (25 × 25 tiles of 16 px): 5×5 terrain, water with waves, waterfall, bridge with posts, plank, flowers, mushrooms, reeds and trees, canopies and rocks from the atlas itself. One Ctrl+Z step."), PageName);
				}),
				FOnClicked::CreateLambda([M]()
				{
					M->CreateTTilesBiomes(M->ActivePage);
					F2DPalette::RedrawViewports();
					return FReply::Handled();
				}),
				TAttribute<bool>::CreateLambda([M]() { return M->GetTileSet() && M->GetPageColumns(M->ActivePage) >= 25 && M->GetPageRows(M->ActivePage) >= 25; }), false)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Left)
		.Padding(0.0f, 4.0f, 0.0f, 0.0f)
		[
			Framework2DProcGenPanelUtil::TextButton("F2D.Icon.Biome", LOCTEXT("ExampleOutdoor", "Outdoor example"),
				LOCTEXT("ExampleOutdoorTip", "One click: imports the plugin's example images into the project (/Game/Framework2D_Ejemplo) (atlas, sky, mountains, forests, trees and rocks), creates the «Outdoor forest» biome with bridges, natural edges, parallax backgrounds and large objects, sets a hills-and-islands recipe and GENERATES the map (replaces its generated layers; Ctrl+Z undoes the biome and the map)."),
				FOnClicked::CreateLambda([M]()
				{
					M->CreateExampleOutdoorBiome();
					F2DPalette::RedrawViewports();
					return FReply::Handled();
				}),
				TAttribute<bool>::CreateLambda([M]() { return M->GetTileSet() && M->GetTileMap(); }), false)
		]);
}

void SFramework2DProcGenPanel::RebuildBiomes()
{
	BiomesBox->ClearChildren();
	const UFramework2DTileSet* Set = Mode->GetTileSet();
	if (!Set || Set->Biomes.Num() == 0)
	{
		BiomesBox->AddSlot()
			.AutoHeight()
			[
				MakeEmptyBiomes()
			];
		return;
	}
	for (const FFramework2DBiome& Biome : Set->Biomes)
	{
		BiomesBox->AddSlot()
			.AutoHeight()
			.Padding(0.0f, 0.0f, 0.0f, 2.0f)
			[
				MakeBiomeRow(Biome.Id)
			];
	}
}

TSharedRef<SWidget> SFramework2DProcGenPanel::MakeEmptyBiomes()
{
	FFramework2DTilePaintMode* M = Mode;
	if (!M->GetTileSet())
	{
		return SNew(SBorder)
			.BorderImage(F2DPalette::Brush("F2D.Row"))
			.Padding(FMargin(12.0f, 14.0f))
			[
				SNew(STextBlock)
				.TextStyle(&F2DPalette::Text("F2D.Text.Caption"))
				.AutoWrapText(true)
				.Justification(ETextJustify::Center)
				.Text(LOCTEXT("NoBiomesNoSet", "No Tile Set yet: biomes are saved in it. Assign it to the terrain's Tile Map."))
			];
	}

	// El ejemplo necesita una página con la distribución de Ejemplo/AtlasBioma.png (16 x 10 tiles).
	auto PageFits = [M]() { return M->GetTileSet() && M->GetPageColumns(M->ActivePage) >= 16 && M->GetPageRows(M->ActivePage) >= 10; };
	TSharedRef<SButton> ExampleButton = Framework2DProcGenPanelUtil::TextButton("F2D.Icon.Biome", LOCTEXT("ExampleBiome", "Create example biome"),
		TAttribute<FText>::CreateLambda([M, PageFits]()
		{
			const UFramework2DTileSet* S = M->GetTileSet();
			const FText PageName = S ? S->GetPageDisplayName(M->ActivePage) : FText::GetEmpty();
			if (PageFits())
			{
				return FText::Format(LOCTEXT("ExampleBiomeTip", "Creates the «Forest» and «Cave» biomes from the active atlas page («{0}»), which must have the Ejemplo/AtlasBioma.png layout (16 × 10 tiles): its water and waterfall flipbooks, its grass and rock generators and all its pieces. A single Ctrl+Z step."), PageName);
			}
			return FText::Format(LOCTEXT("ExampleBiomeOffTip", "Needs an atlas page with the Ejemplo/AtlasBioma.png layout (16 × 10 tiles). The active page («{0}») has {1} × {2} tiles: add that image as a page in the Paint tab and keep it active."),
				PageName, M->GetPageColumns(M->ActivePage), M->GetPageRows(M->ActivePage));
		}),
		FOnClicked::CreateLambda([M]()
		{
			M->CreateExampleBiome(M->ActivePage);
			F2DPalette::RedrawViewports();
			return FReply::Handled();
		}),
		TAttribute<bool>::CreateLambda(PageFits), true);

	TSharedRef<SButton> EmptyButton = Framework2DProcGenPanelUtil::TextButton("F2D.Icon.Add", LOCTEXT("EmptyBiome", "Empty biome"),
		LOCTEXT("EmptyBiomeTip", "Creates a biome with no pieces (it becomes the active one). Then choose at least the center of the 3×3 terrain."),
		FOnClicked::CreateLambda([M]() { M->CreateBiome(); F2DPalette::RedrawViewports(); return FReply::Handled(); }),
		TAttribute<bool>(true), false);

	return SNew(SBorder)
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
				.Image(F2DPalette::Brush("F2D.Icon.Biome"))
				.ColorAndOpacity(FFramework2DEditorStyle::ForegroundDim())
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 0.0f, 0.0f, 10.0f)
			[
				SNew(STextBlock)
				.TextStyle(&F2DPalette::Text("F2D.Text.Caption"))
				.AutoWrapText(true)
				.Justification(ETextJustify::Center)
				.Text(LOCTEXT("NoBiomes", "No biomes yet. A biome is the level's pieces: the 3×3 terrain (at least its center), ramps, platforms, background, water, waterfalls and decoration."))
			]
			// A todo el ancho (con UseAllottedSize, una caja centrada se quedaría con su ancho
			// mínimo y partiría los botones en dos filas); los botones se centran dentro.
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SWrapBox)
				.UseAllottedSize(true)
				.HAlign(HAlign_Center)
				.InnerSlotPadding(FVector2D(6.0f, 6.0f))
				+ SWrapBox::Slot()
				[
					ExampleButton
				]
				+ SWrapBox::Slot()
				[
					EmptyButton
				]
			]
		];
}

TSharedRef<SWidget> SFramework2DProcGenPanel::MakeBiomeRow(int32 BiomeId)
{
	FFramework2DTilePaintMode* M = Mode;
	auto Find = [M, BiomeId]() -> const FFramework2DBiome*
	{
		const UFramework2DTileSet* S = M->GetTileSet();
		return S ? S->FindBiomeById(BiomeId) : nullptr;
	};
	auto IsActive = [M, BiomeId]() { return M->GetActiveBiomeId() == BiomeId; };
	auto Problem = [M, Find]() -> FText
	{
		const FFramework2DBiome* Biome = Find();
		const UFramework2DTileSet* S = M->GetTileSet();
		return (Biome && S) ? UFramework2DProcGenLibrary::GetBiomeProblem(S, *Biome) : FText::GetEmpty();
	};

	TSharedPtr<SInlineEditableTextBlock> NameBlock;
	TSharedRef<SFramework2DListRow> Row = SNew(SFramework2DListRow)
		.IsActive_Lambda(IsActive)
		.OnSelected_Lambda([M, BiomeId]() { M->SetActiveBiome(BiomeId); F2DPalette::RedrawViewports(); })
		[
			SNew(SHorizontalBox)
			// Barra de acento del bioma activo (forma, además de color).
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
			// Miniatura: el centro de su terreno 3x3.
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(5.0f, 5.0f, 8.0f, 5.0f)
			[
				SNew(SFramework2DTileThumb, M, [M, Find]()
				{
					const FFramework2DBiome* Biome = Find();
					return Framework2DProcGenPanelUtil::ThumbOf(M->GetTileSet(), Biome ? Biome->Ground.Center : -1);
				})
				.Size(32.0f)
				.bAnimated(true)
				.ToolTipText(LOCTEXT("BiomeThumbTip", "The center of its 3×3 terrain."))
			]
			// Nombre y estado (lo que le falta o cuántas piezas tiene).
			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			.VAlign(VAlign_Center)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SAssignNew(NameBlock, SInlineEditableTextBlock)
					.ToolTipText(LOCTEXT("BiomeNameTip", "Click: use this biome in the map (the recipe remembers it). Double click or F2: rename."))
					.Text_Lambda([Find]()
					{
						const FFramework2DBiome* Biome = Find();
						return Biome ? FText::FromName(Biome->Name) : FText::GetEmpty();
					})
					.Font_Lambda([IsActive]() { return F2DPalette::Font(IsActive(), 9); })
					.ColorAndOpacity(FFramework2DEditorStyle::Foreground())
					.OnVerifyTextChanged_Lambda([](const FText& InText, FText& OutError) { return F2DPalette::VerifyName(InText, OutError); })
					.OnTextCommitted_Lambda([M, BiomeId](const FText& NewText, ETextCommit::Type Commit)
					{
						if (Commit != ETextCommit::OnCleared) { M->RenameBiome(BiomeId, NewText); }
					})
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(0.0f, 2.0f, 0.0f, 0.0f)
				[
					SNew(SHorizontalBox)
					// Si le falta algo para generar, un icono de aviso además del texto.
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.VAlign(VAlign_Center)
					.Padding(0.0f, 0.0f, 4.0f, 0.0f)
					[
						SNew(SBox)
						.WidthOverride(12.0f)
						.HeightOverride(12.0f)
						.Visibility_Lambda([Problem]() { return Problem().IsEmpty() ? EVisibility::Collapsed : EVisibility::Visible; })
						[
							SNew(SImage)
							.Image(F2DPalette::Brush("F2D.Icon.Info"))
							.ColorAndOpacity(FFramework2DEditorStyle::Accent())
						]
					]
					+ SHorizontalBox::Slot()
					.FillWidth(1.0f)
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
						.TextStyle(&F2DPalette::Text("F2D.Text.Caption"))
						.OverflowPolicy(ETextOverflowPolicy::Ellipsis)
						.Text_Lambda([Find, Problem]() -> FText
						{
							const FFramework2DBiome* Biome = Find();
							if (!Biome) { return FText::GetEmpty(); }
							const FText Missing = Problem();
							if (!Missing.IsEmpty()) { return Missing; }
							return FText::Format(LOCTEXT("BiomeSummary", "{0} {0}|plural(one=piece,other=pieces) · {1} {1}|plural(one=decoration,other=decorations)"),
								Framework2DProcGenPanelUtil::CountPieces(*Biome), Biome->Decorations.Num());
						})
						.ToolTipText_Lambda([Problem]()
						{
							const FText Missing = Problem();
							return Missing.IsEmpty() ? LOCTEXT("BiomeReadyTip", "Ready to generate.") : Missing;
						})
					]
				]
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(2.0f, 0.0f, 6.0f, 0.0f)
			[
				F2DPalette::IconButton("F2D.Icon.Trash",
					LOCTEXT("DeleteBiomeTip", "Delete the biome (Ctrl+Z brings it back). Maps that used it switch to the first one left."),
					FOnClicked::CreateLambda([M, BiomeId]()
					{
						M->DeleteBiome(BiomeId);
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
//  2. Piezas del bioma activo
// ---------------------------------------------------------------------
TSharedRef<SWidget> SFramework2DProcGenPanel::MakeSection(const FText& Title, const FText& Help, const TSharedRef<SWidget>& Content)
{
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 12.0f, 0.0f, 2.0f)
		[
			SNew(STextBlock)
			.TextStyle(&F2DPalette::Text("F2D.Text.Body"))
			.Font(F2DPalette::Font(true, 9))
			.Text(Title)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 0.0f, 0.0f, 6.0f)
		[
			F2DPalette::Caption(Help)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			Content
		];
}

TSharedRef<SWidget> SFramework2DProcGenPanel::MakePieceSlot(const FFramework2DPieceTarget& Target, const FText& Label, float Size, bool bRequired)
{
	const bool bAdd = Target.IsAdd();
	const bool bRemovable = Target.Kind == EFramework2DPieceTargetKind::Variant || Target.Kind == EFramework2DPieceTargetKind::Decoration;
	TSharedRef<SFramework2DPieceSlot> Widget = SNew(SFramework2DPieceSlot, Mode, [this, Target]() { return GetTargetValue(Target); })
		.Size(Size)
		.Label(Label)
		.SlotName(Framework2DProcGenPanelUtil::TargetName(Target))
		.bRequired(bRequired)
		.bRemovable(bRemovable)
		.bAdd(bAdd)
		.OnOpen_Lambda([this, Target](TSharedRef<SWidget> Anchor, bool bFromKeyboard) { OpenPickerAt(Target, Anchor, bFromKeyboard); })
		.OnClear_Lambda([this, Target]() { ClearTarget(Target); });

	// Se recuerda para anclar el selector (y para las pruebas).
	const TWeakPtr<SWidget> Weak = TSharedRef<SWidget>(Widget);
	switch (Target.Kind)
	{
	case EFramework2DPieceTargetKind::Slot:
		SlotWidgets.Add((int32)Target.Slot, Weak);
		break;
	case EFramework2DPieceTargetKind::AddVariant:
		AddVariantAnchor = Weak;
		break;
	case EFramework2DPieceTargetKind::Variant:
		if (Target.Index >= 0)
		{
			if (VariantAnchors.Num() <= Target.Index) { VariantAnchors.SetNum(Target.Index + 1); }
			VariantAnchors[Target.Index] = Weak;
		}
		break;
	case EFramework2DPieceTargetKind::Decoration:
		if (Target.Index >= 0)
		{
			if (DecorationAnchors.Num() <= Target.Index) { DecorationAnchors.SetNum(Target.Index + 1); }
			DecorationAnchors[Target.Index] = Weak;
		}
		break;
	default:
		break;
	}
	return Widget;
}

TSharedRef<SWidget> SFramework2DProcGenPanel::MakeSlotRow(const TArray<EFramework2DBiomeSlot>& Slots)
{
	// Se parten en filas si el panel es estrecho.
	TSharedRef<SWrapBox> Row = SNew(SWrapBox)
		.UseAllottedSize(true)
		.InnerSlotPadding(FVector2D(4.0f, 6.0f));
	for (const EFramework2DBiomeSlot PieceSlot : Slots)
	{
		Row->AddSlot()
		[
			MakePieceSlot(FFramework2DPieceTarget::ForSlot(PieceSlot), Framework2DProcGenPanelUtil::SlotLabel(PieceSlot), 44.0f, false)
		];
	}
	return Row;
}

TSharedRef<SWidget> SFramework2DProcGenPanel::Make3x3(bool bBackground)
{
	TSharedRef<SUniformGridPanel> Grid = SNew(SUniformGridPanel).SlotPadding(FMargin(2.0f));
	for (int32 I = 0; I < FFramework2DTile3x3::Num; ++I)
	{
		const EFramework2DBiomeSlot PieceSlot = Framework2D::Biome3x3Slot(bBackground, I);
		Grid->AddSlot(I % 3, I / 3)
		[
			// El centro del terreno es obligatorio (sin él no se puede generar).
			MakePieceSlot(FFramework2DPieceTarget::ForSlot(PieceSlot), FText::GetEmpty(), 44.0f, !bBackground && I == 4)
		];
	}

	FFramework2DTilePaintMode* M = Mode;
	const int32 AnchorIndex = bBackground ? 1 : 0;
	TSharedRef<SButton> BlockButton = Framework2DProcGenPanelUtil::TextButton("F2D.Icon.Grid", LOCTEXT("PickBlock", "Choose 3×3 block…"),
		bBackground
			? LOCTEXT("PickBlockBgTip", "Opens the picker to choose a 3 × 3 tile block in the atlas: fills the 9 background pieces at once.")
			: LOCTEXT("PickBlockTip", "Opens the picker to choose a 3 × 3 tile block in the atlas: fills the 9 terrain pieces at once."),
		FOnClicked::CreateLambda([this, bBackground, AnchorIndex]()
		{
			if (const TSharedPtr<SWidget> Anchor = BlockAnchors[AnchorIndex].Pin())
			{
				OpenPickerAt(FFramework2DPieceTarget::ForBlock(bBackground), Anchor.ToSharedRef(), false);
			}
			return FReply::Handled();
		}),
		TAttribute<bool>::CreateLambda([M]() { return M->GetTileSet() != nullptr; }), false);
	BlockAnchors[AnchorIndex] = BlockButton;

	TSharedRef<SButton> SelectionButton = Framework2DProcGenPanelUtil::TextButton("F2D.Icon.Replace", LOCTEXT("UseSelection3x3", "Use the atlas selection"),
		TAttribute<FText>::CreateLambda([M]()
		{
			return M->CanUseSelectionAs3x3()
				? LOCTEXT("UseSelection3x3Tip", "Fills the 9 pieces with the 3 × 3 tile block selected in the atlas of the Paint tab.")
				: LOCTEXT("UseSelection3x3OffTip", "First select a 3 × 3 tile block in the atlas of the Paint tab (with no flipbook or generator as the brush).");
		}),
		FOnClicked::CreateLambda([this, bBackground]() { UseSelectionAs3x3(bBackground); return FReply::Handled(); }),
		TAttribute<bool>::CreateLambda([M]() { return M->CanUseSelectionAs3x3(); }), false);

	return SNew(SWrapBox)
		.UseAllottedSize(true)
		.InnerSlotPadding(FVector2D(10.0f, 6.0f))
		+ SWrapBox::Slot()
		[
			Grid
		]
		+ SWrapBox::Slot()
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(HAlign_Left)
			.Padding(0.0f, 2.0f, 0.0f, 0.0f)
			[
				BlockButton
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(HAlign_Left)
			.Padding(0.0f, 4.0f, 0.0f, 0.0f)
			[
				SelectionButton
			]
		];
}

TSharedRef<SWidget> SFramework2DProcGenPanel::Make5x5()
{
	TSharedRef<SUniformGridPanel> Grid = SNew(SUniformGridPanel)
		.SlotPadding(FMargin(1.0f))
		.ToolTipText(LOCTEXT("Grid5Tip", "Rows: the very top one, the second, the interior, the one above the bottom edge and the bottom one. Columns the same, left to right. Click a piece to choose it; «Choose 5×5 block…» fills all 25."));
	for (int32 I = 0; I < 25; ++I)
	{
		Grid->AddSlot(I % 5, I / 5)
		[
			MakePieceSlot(FFramework2DPieceTarget::ForSlot(Framework2D::Biome5x5Slot(I / 5, I % 5)), FText::GetEmpty(), 34.0f, false)
		];
	}
	FFramework2DTilePaintMode* M = Mode;
	TSharedRef<SButton> BlockButton = Framework2DProcGenPanelUtil::TextButton("F2D.Icon.Grid", LOCTEXT("PickBlock5", "Choose 5×5 block…"),
		LOCTEXT("PickBlock5Tip", "Opens the picker to choose a 5 × 5 tile block in the atlas: fills the 25 terrain pieces at once."),
		FOnClicked::CreateLambda([this]()
		{
			if (const TSharedPtr<SWidget> Anchor = BlockAnchors[2].Pin())
			{
				OpenPickerAt(FFramework2DPieceTarget::ForBlock5(), Anchor.ToSharedRef(), false);
			}
			return FReply::Handled();
		}),
		TAttribute<bool>::CreateLambda([M]() { return M->GetTileSet() != nullptr; }), false);
	BlockAnchors[2] = BlockButton;
	TSharedRef<SButton> SelectionButton = Framework2DProcGenPanelUtil::TextButton("F2D.Icon.Replace", LOCTEXT("UseSelection5x5", "Use the atlas selection"),
		TAttribute<FText>::CreateLambda([M]()
		{
			return M->CanUseSelectionAs5x5()
				? LOCTEXT("UseSelection5x5Tip", "Fills the 25 pieces with the 5 × 5 tile block selected in the atlas of the Paint tab.")
				: LOCTEXT("UseSelection5x5OffTip", "First select a 5 × 5 tile block in the atlas of the Paint tab (with no flipbook or generator as the brush).");
		}),
		FOnClicked::CreateLambda([this]() { UseSelectionAs5x5(); return FReply::Handled(); }),
		TAttribute<bool>::CreateLambda([M]() { return M->CanUseSelectionAs5x5(); }), false);
	TSharedRef<SButton> ClearButton = Framework2DProcGenPanelUtil::TextButton("F2D.Icon.Trash", LOCTEXT("Clear5x5", "Clear"),
		LOCTEXT("Clear5x5Tip", "Clears the 25 pieces of the 5×5: the biome goes back to the 3×3 (Ctrl+Z undoes it)."),
		FOnClicked::CreateLambda([this]() { ClearTarget(FFramework2DPieceTarget::ForBlock5()); return FReply::Handled(); }),
		TAttribute<bool>::CreateLambda([M]() { const FFramework2DBiome* B = M->GetActiveBiome(); return B && !B->Ground5.IsEmpty(); }), false);

	// Fila fija (no SWrapBox): la rejilla y los botones caben a 380 px y asi no reserva alto de mas.
	return SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.VAlign(VAlign_Top)
		.Padding(0.0f, 0.0f, 10.0f, 0.0f)
		[
			Grid
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.0f)
		.VAlign(VAlign_Top)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Left).Padding(0.0f, 2.0f, 0.0f, 0.0f)[ BlockButton ]
			+ SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Left).Padding(0.0f, 4.0f, 0.0f, 0.0f)[ SelectionButton ]
			+ SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Left).Padding(0.0f, 4.0f, 0.0f, 0.0f)[ ClearButton ]
		];
}

TSharedRef<SWidget> SFramework2DProcGenPanel::MakeInnerCorners()
{
	TSharedRef<SUniformGridPanel> Grid = SNew(SUniformGridPanel).SlotPadding(FMargin(2.0f));
	for (int32 I = 0; I < FFramework2DInnerCorners::Num; ++I)
	{
		const EFramework2DBiomeSlot PieceSlot = (EFramework2DBiomeSlot)((int32)EFramework2DBiomeSlot::InnerTopLeft + I);
		Grid->AddSlot(I % 2, I / 2)
		[
			MakePieceSlot(FFramework2DPieceTarget::ForSlot(PieceSlot), FText::GetEmpty(), 44.0f, false)
		];
	}
	return SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			Grid
		];
}

TSharedRef<SWidget> SFramework2DProcGenPanel::MakePiecesCard()
{
	FFramework2DTilePaintMode* M = Mode;
	VariantsBox = SNew(SWrapBox)
		.UseAllottedSize(true)
		.InnerSlotPadding(FVector2D(4.0f, 4.0f));
	DecorationsBox = SNew(SVerticalBox);

	TSharedRef<SButton> AddDecorationButton = Framework2DProcGenPanelUtil::TextButton("F2D.Icon.Add", LOCTEXT("AddDecoration", "Add decoration…"),
		LOCTEXT("AddDecorationTip", "Opens the picker to choose a decoration: a generator (grass, rocks...), a flipbook (torches, flowers...) or a tile. It goes on the ground with weight 1."),
		FOnClicked::CreateLambda([this]()
		{
			if (const TSharedPtr<SWidget> Anchor = AddDecorationAnchor.Pin())
			{
				OpenPickerAt(FFramework2DPieceTarget::ForList(EFramework2DPieceTargetKind::AddDecoration), Anchor.ToSharedRef(), false);
			}
			return FReply::Handled();
		}),
		TAttribute<bool>::CreateLambda([M]() { return M->GetActiveBiome() != nullptr; }), false);
	AddDecorationAnchor = AddDecorationButton;

	using ESlotKind = EFramework2DBiomeSlot;
	return SNew(SBox)
		.Visibility_Lambda([M]() { return M->GetActiveBiome() ? EVisibility::Visible : EVisibility::Collapsed; })
		[
			F2DPalette::Card(
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					F2DPalette::CardHeader("F2D.Icon.Grid", LOCTEXT("PiecesTitle", "Biome pieces"))
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(0.0f, 2.0f, 0.0f, 0.0f)
				[
					F2DPalette::Caption(TAttribute<FText>::CreateLambda([M]()
					{
						const FFramework2DBiome* Biome = M->GetActiveBiome();
						return FText::Format(LOCTEXT("PiecesHelp", "«{0}». Click a slot: choose its piece (tile, flipbook or generator) · Right click or Delete: clear. Missing ones use the closest match."),
							Biome ? FText::FromName(Biome->Name) : FText::GetEmpty());
					}))
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					MakeSection(LOCTEXT("SectionGround5", "Terrain 5×5"),
						LOCTEXT("SectionGround5Help", "Optional: tilesets with two-tile edges (two rows of grass). With its center, it overrides the 3×3."),
						Make5x5())
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					MakeSection(LOCTEXT("SectionGround", "Terrain 3×3"),
						LOCTEXT("SectionGroundHelp", "The center (!) is required, unless you use the 5×5. Missing corners and edges use the edge or the center."),
						Make3x3(false))
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					MakeSection(LOCTEXT("SectionInner", "Inner corners"),
						LOCTEXT("SectionInnerHelp", "Optional. They join the ground to the wall of a step (the grass bends inwards)."),
						MakeInnerCorners())
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					MakeSection(LOCTEXT("SectionWallFoot", "Deep interior and wall foot (5×5)"),
						LOCTEXT("SectionWallFootHelp", "Optional, with the 5×5. «Deep»: what goes deeper than the 5×5 rows (if the center is a band of rocks and below it is plain). Wall foot: where a ground meets the wall of a step, its grass passes in front of the wall's foot and ends with its cap; with these pieces, the ground's second row goes into the wall and ends against the rock (bushes, roots...)."),
						SNew(SVerticalBox)
						+ SVerticalBox::Slot().AutoHeight()[ MakeSlotRow({ ESlotKind::GroundDeep }) ]
						+ SVerticalBox::Slot().AutoHeight().Padding(0.0f, 4.0f, 0.0f, 0.0f)
						[
							MakeSlotRow({ ESlotKind::WallFootLeft, ESlotKind::WallFootLeftInner, ESlotKind::WallFootRight, ESlotKind::WallFootRightInner })
						])
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					MakeSection(LOCTEXT("SectionVariants", "Center variants"),
						LOCTEXT("SectionVariantsHelp", "Optional. Mixed at random with the center so it does not repeat. «+» adds one."),
						VariantsBox.ToSharedRef())
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					MakeSection(LOCTEXT("SectionRamps", "Ramps"),
						LOCTEXT("SectionRampsHelp", "Optional. One tile per tile of height, with the upper triangle transparent."),
						MakeSlotRow({ ESlotKind::RampUp, ESlotKind::RampDown }))
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					MakeSection(LOCTEXT("SectionGentle", "Gentle ramps"),
						LOCTEXT("SectionGentleHelp", "Optional. Two tiles per tile of height: the low half and the high half."),
						MakeSlotRow({ ESlotKind::GentleUpLow, ESlotKind::GentleUpHigh, ESlotKind::GentleDownHigh, ESlotKind::GentleDownLow }))
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					MakeSection(LOCTEXT("SectionPlatforms", "Platforms"),
						LOCTEXT("SectionPlatformsHelp", "Optional. Without them, platforms use the terrain's top row (with the 5×5, its two top rows and the bottom one). The lip (optional, only with platform pieces) goes above each tile: for planks that stick out a little above their tile."),
						SNew(SVerticalBox)
						+ SVerticalBox::Slot().AutoHeight()[ MakeSlotRow({ ESlotKind::PlatformLeft, ESlotKind::PlatformMiddle, ESlotKind::PlatformRight }) ]
						+ SVerticalBox::Slot().AutoHeight().Padding(0.0f, 4.0f, 0.0f, 0.0f)
						[
							MakeSlotRow({ ESlotKind::PlatformCapLeft, ESlotKind::PlatformCapMiddle, ESlotKind::PlatformCapRight })
						])
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					MakeSection(LOCTEXT("SectionBackground", "Background 3×3"),
						LOCTEXT("SectionBackgroundHelp", "Optional. Back wall and hills behind the terrain; visible when digging. With only the center, the whole background is that piece."),
						Make3x3(true))
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					MakeSection(LOCTEXT("SectionWater", "Water"),
						LOCTEXT("SectionWaterHelp", "Optional; usually flipbooks. If one is missing, the other does both."),
						MakeSlotRow({ ESlotKind::WaterSurface, ESlotKind::WaterBody, ESlotKind::WaterCrest }))
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					MakeSection(LOCTEXT("SectionWaterfall", "Waterfall"),
						LOCTEXT("SectionWaterfallHelp", "Optional; usually flipbooks. Needs at least the fall: it runs down cliffs of 2 tiles or more."),
						MakeSlotRow({ ESlotKind::WaterfallTop, ESlotKind::WaterfallBody, ESlotKind::WaterfallBottom }))
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					MakeSection(LOCTEXT("SectionBridges", "Bridges"),
						LOCTEXT("SectionBridgesHelp", "Optional. They cross pits, lakes and narrow valleys between two banks at the same height. Without ends, everything is planks. With the 5×5 the planks sit flush with the banks' grass, the ends and posts on the banks and the lip (5×5 only) above the planks."),
						SNew(SVerticalBox)
						+ SVerticalBox::Slot().AutoHeight()[ MakeSlotRow({ ESlotKind::BridgeLeft, ESlotKind::BridgeMiddle, ESlotKind::BridgeRight }) ]
						+ SVerticalBox::Slot().AutoHeight().Padding(0.0f, 4.0f, 0.0f, 0.0f)
						[
							MakeSlotRow({ ESlotKind::BridgeCapLeft, ESlotKind::BridgeCapMiddle, ESlotKind::BridgeCapRight })
						]
						+ SVerticalBox::Slot().AutoHeight().Padding(0.0f, 4.0f, 0.0f, 0.0f)
						[
							MakeSlotRow({ ESlotKind::BridgePostLeftLow, ESlotKind::BridgePostLeftHigh, ESlotKind::BridgePostRightLow, ESlotKind::BridgePostRightHigh })
						])
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					MakeSection(LOCTEXT("SectionEdges", "Natural edges"),
						LOCTEXT("SectionEdgesHelp", "Optional; usually generators. «Top» goes over EVERY top edge (grass or moss that hides the tiles' straight line); «Bottom», under islands and ledges (rocks, roots: enable «Hang from ceiling» in its generator)."),
						MakeSlotRow({ ESlotKind::EdgeTop, ESlotKind::EdgeBottom }))
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					MakeSection(LOCTEXT("SectionDecoration", "Decoration"),
						LOCTEXT("SectionDecorationHelp", "Scattered on top of the ground or hanging under platforms (Ceiling), by weight: the more weight, the more often it appears."),
						SNew(SVerticalBox)
						+ SVerticalBox::Slot()
						.AutoHeight()
						[
							DecorationsBox.ToSharedRef()
						]
						+ SVerticalBox::Slot()
						.AutoHeight()
						.HAlign(HAlign_Left)
						.Padding(0.0f, 6.0f, 0.0f, 0.0f)
						[
							AddDecorationButton
						])
				])
		];
}

void SFramework2DProcGenPanel::RebuildVariants()
{
	VariantsBox->ClearChildren();
	VariantAnchors.Reset();
	const FFramework2DBiome* Biome = Mode->GetActiveBiome();
	if (!Biome) { return; }

	FFramework2DTilePaintMode* M = Mode;
	for (int32 I = 0; I < Biome->CenterVariants.Num(); ++I)
	{
		VariantsBox->AddSlot()
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				MakePieceSlot(FFramework2DPieceTarget::ForList(EFramework2DPieceTargetKind::Variant, I), FText::GetEmpty(), 44.0f, false)
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(HAlign_Center)
			.Padding(0.0f, 2.0f, 0.0f, 0.0f)
			[
				F2DPalette::IconButton("F2D.Icon.Remove",
					FText::Format(LOCTEXT("RemoveVariantTip", "Remove variant {0} (Ctrl+Z brings it back)."), I + 1),
					FOnClicked::CreateLambda([M, I]()
					{
						const int32 BiomeId = M->GetActiveBiomeId();
						if (BiomeId != INDEX_NONE) { M->RemoveBiomeCenterVariant(BiomeId, I); }
						F2DPalette::RedrawViewports();
						return FReply::Handled();
					}),
					TAttribute<bool>(true),
					&F2DPalette::DangerIconButtonStyle())
			]
		];
	}
	// Hueco «+»: añade una variante.
	VariantsBox->AddSlot()
	[
		MakePieceSlot(FFramework2DPieceTarget::ForList(EFramework2DPieceTargetKind::AddVariant), FText::GetEmpty(), 44.0f, false)
	];
}

void SFramework2DProcGenPanel::RebuildDecorations()
{
	DecorationsBox->ClearChildren();
	DecorationAnchors.Reset();
	const FFramework2DBiome* Biome = Mode->GetActiveBiome();
	if (!Biome || Biome->Decorations.Num() == 0)
	{
		DecorationsBox->AddSlot()
			.AutoHeight()
			[
				SNew(SBorder)
				.BorderImage(F2DPalette::Brush("F2D.Row"))
				.Padding(FMargin(10.0f, 8.0f))
				[
					F2DPalette::Caption(LOCTEXT("NoDecorations", "No decorations yet: add grass, rocks, torches... with «Add decoration…»."))
				]
			];
		return;
	}
	for (int32 I = 0; I < Biome->Decorations.Num(); ++I)
	{
		DecorationsBox->AddSlot()
			.AutoHeight()
			.Padding(0.0f, 0.0f, 0.0f, 2.0f)
			[
				MakeDecorationRow(I)
			];
	}
}

TSharedRef<SWidget> SFramework2DProcGenPanel::MakeDecorationRow(int32 Index)
{
	FFramework2DTilePaintMode* M = Mode;
	auto Find = [M, Index]() -> const FFramework2DBiomeDecoration*
	{
		const FFramework2DBiome* Biome = M->GetActiveBiome();
		return (Biome && Biome->Decorations.IsValidIndex(Index)) ? &Biome->Decorations[Index] : nullptr;
	};
	auto IsCeiling = [Find]()
	{
		const FFramework2DBiomeDecoration* Decoration = Find();
		return Decoration && Decoration->Placement == EFramework2DDecorPlacement::Ceiling;
	};
	// Cambia el adorno con un paso de deshacer (el modo no crea pasos vacíos).
	auto ChangeDecoration = [M, Index](const FText& Description, TFunction<void(FFramework2DBiomeDecoration&)> Change)
	{
		const int32 BiomeId = M->GetActiveBiomeId();
		if (BiomeId == INDEX_NONE) { return; }
		M->ChangeBiome(BiomeId, Description, [Index, &Change](FFramework2DBiome& Biome)
		{
			if (Biome.Decorations.IsValidIndex(Index)) { Change(Biome.Decorations[Index]); }
		});
		F2DPalette::RedrawViewports();
	};
	const TSharedRef<F2DPalette::FSpinDrag> WeightDrag = MakeShared<F2DPalette::FSpinDrag>();
	const FText WeightTip = LOCTEXT("DecorationWeightTip", "Weight: probability relative to the other decorations in the same place (0 = never; 2 = twice as often as weight 1).");

	return SNew(SBorder)
		.BorderImage(F2DPalette::Brush("F2D.Row"))
		.Padding(FMargin(0.0f))
		[
			SNew(SHorizontalBox)
			// Miniatura = hueco: clic para cambiar la pieza; Supr para quitar el adorno.
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(4.0f, 4.0f, 8.0f, 4.0f)
			[
				MakePieceSlot(FFramework2DPieceTarget::ForList(EFramework2DPieceTargetKind::Decoration, Index), FText::GetEmpty(), 36.0f, false)
			]
			// Nombre del generador / flipbook o «Tile N», y qué es.
			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			.VAlign(VAlign_Center)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(STextBlock)
					.TextStyle(&F2DPalette::Text("F2D.Text.Body"))
					.OverflowPolicy(ETextOverflowPolicy::Ellipsis)
					.Text_Lambda([M, Find]()
					{
						const FFramework2DBiomeDecoration* Decoration = Find();
						return Decoration ? Framework2DProcGenPanelUtil::ValueName(M->GetTileSet(), Decoration->Value) : FText::GetEmpty();
					})
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(0.0f, 2.0f, 0.0f, 0.0f)
				[
					SNew(STextBlock)
					.TextStyle(&F2DPalette::Text("F2D.Text.Caption"))
					.OverflowPolicy(ETextOverflowPolicy::Ellipsis)
					.Text_Lambda([M, Find]()
					{
						const FFramework2DBiomeDecoration* Decoration = Find();
						return Decoration ? Framework2DProcGenPanelUtil::KindLabel(M->GetTileSet(), Decoration->Value) : FText::GetEmpty();
					})
				]
			]
			// Peso: en vivo al arrastrar, se guarda al soltar o al escribirlo (un paso de deshacer).
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(6.0f, 0.0f, 0.0f, 0.0f)
			[
				SNew(SBox)
				.WidthOverride(56.0f)
				[
					SNew(SSpinBox<float>)
					.MinValue(0.0f)
					.MaxValue(10.0f)
					.MinSliderValue(0.0f)
					.MaxSliderValue(10.0f)
					.Delta(0.05f)
					.MinFractionalDigits(0)
					.MaxFractionalDigits(2)
					.ToolTipText(WeightTip)
					.Value_Lambda([Find, WeightDrag]() -> float
					{
						if (WeightDrag->bDragging) { return WeightDrag->Value; }
						const FFramework2DBiomeDecoration* Decoration = Find();
						return Decoration ? Decoration->Weight : 1.0f;
					})
					.OnBeginSliderMovement_Lambda([Find, WeightDrag]()
					{
						const FFramework2DBiomeDecoration* Decoration = Find();
						WeightDrag->bDragging = true;
						WeightDrag->Value = Decoration ? Decoration->Weight : 1.0f;
					})
					.OnValueChanged_Lambda([WeightDrag](float NewValue)
					{
						if (WeightDrag->bDragging) { WeightDrag->Value = NewValue; }
					})
					.OnEndSliderMovement_Lambda([ChangeDecoration, WeightDrag](float NewValue)
					{
						WeightDrag->bDragging = false;
						ChangeDecoration(LOCTEXT("DecorationWeight", "Decoration weight"), [NewValue](FFramework2DBiomeDecoration& Decoration) { Decoration.Weight = FMath::Max(0.0f, NewValue); });
					})
					.OnValueCommitted_Lambda([ChangeDecoration, WeightDrag](float NewValue, ETextCommit::Type)
					{
						if (WeightDrag->bDragging) { return; }
						ChangeDecoration(LOCTEXT("DecorationWeight", "Decoration weight"), [NewValue](FFramework2DBiomeDecoration& Decoration) { Decoration.Weight = FMath::Max(0.0f, NewValue); });
					})
				]
			]
			// Sitio: Suelo / Techo (icono y texto, no solo color).
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(4.0f, 0.0f, 0.0f, 0.0f)
			[
				SNew(SButton)
				.ButtonStyle(&F2DPalette::Button("F2D.Button.Secondary"))
				.ContentPadding(FMargin(0.0f))
				.VAlign(VAlign_Center)
				.ToolTipText_Lambda([IsCeiling]()
				{
					return IsCeiling()
						? LOCTEXT("DecorCeilingTip", "Place: Ceiling. Hangs under platforms (vines, stalactites). Click to put it on the ground.")
						: LOCTEXT("DecorGroundTip", "Place: Ground. Goes on top of the ground and platforms (grass, rocks, torches). Click to hang it from the ceiling.");
				})
				.OnClicked_Lambda([ChangeDecoration]()
				{
					ChangeDecoration(LOCTEXT("DecorationPlacement", "Decoration place"), [](FFramework2DBiomeDecoration& Decoration)
					{
						Decoration.Placement = Decoration.Placement == EFramework2DDecorPlacement::Ceiling ? EFramework2DDecorPlacement::Ground : EFramework2DDecorPlacement::Ceiling;
					});
					return FReply::Handled();
				})
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.VAlign(VAlign_Center)
					[
						SNew(SImage)
						.Image_Lambda([IsCeiling]() { return F2DPalette::Brush(IsCeiling() ? FName("F2D.Icon.Up") : FName("F2D.Icon.Down")); })
						.ColorAndOpacity(FSlateColor::UseForeground())
					]
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.VAlign(VAlign_Center)
					.Padding(4.0f, 0.0f, 0.0f, 0.0f)
					[
						SNew(STextBlock)
						.Font(F2DPalette::Font(false, 8))
						.ColorAndOpacity(FSlateColor::UseForeground())
						.Text_Lambda([IsCeiling]() { return IsCeiling() ? LOCTEXT("DecorCeiling", "Ceiling") : LOCTEXT("DecorGround", "Ground"); })
					]
				]
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(2.0f, 0.0f, 4.0f, 0.0f)
			[
				F2DPalette::IconButton("F2D.Icon.Trash",
					LOCTEXT("RemoveDecorationTip", "Remove this decoration from the biome (Ctrl+Z brings it back)."),
					FOnClicked::CreateLambda([M, Index]()
					{
						const int32 BiomeId = M->GetActiveBiomeId();
						if (BiomeId != INDEX_NONE) { M->RemoveBiomeDecoration(BiomeId, Index); }
						F2DPalette::RedrawViewports();
						return FReply::Handled();
					}),
					TAttribute<bool>(true),
					&F2DPalette::DangerIconButtonStyle())
			]
		];
}

// ---------------------------------------------------------------------
//  Selector de piezas
// ---------------------------------------------------------------------
int32 SFramework2DProcGenPanel::GetTargetValue(const FFramework2DPieceTarget& Target) const
{
	const FFramework2DBiome* Biome = Mode->GetActiveBiome();
	if (!Biome) { return -1; }
	switch (Target.Kind)
	{
	case EFramework2DPieceTargetKind::Slot:
		return Framework2D::GetBiomeSlot(*Biome, Target.Slot);
	case EFramework2DPieceTargetKind::Variant:
		return Biome->CenterVariants.IsValidIndex(Target.Index) ? Biome->CenterVariants[Target.Index] : -1;
	case EFramework2DPieceTargetKind::Decoration:
		return Biome->Decorations.IsValidIndex(Target.Index) ? Biome->Decorations[Target.Index].Value : -1;
	default:
		return -1;
	}
}

TWeakPtr<SWidget> SFramework2DProcGenPanel::FindAnchor(const FFramework2DPieceTarget& Target) const
{
	switch (Target.Kind)
	{
	case EFramework2DPieceTargetKind::Slot:
		return SlotWidgets.FindRef((int32)Target.Slot);
	case EFramework2DPieceTargetKind::Block3x3:
		return BlockAnchors[Target.BlockSize == 5 ? 2 : (Target.bBackground ? 1 : 0)];
	case EFramework2DPieceTargetKind::AddVariant:
		return AddVariantAnchor;
	case EFramework2DPieceTargetKind::Variant:
		return VariantAnchors.IsValidIndex(Target.Index) ? VariantAnchors[Target.Index] : TWeakPtr<SWidget>();
	case EFramework2DPieceTargetKind::AddDecoration:
		return AddDecorationAnchor;
	case EFramework2DPieceTargetKind::Decoration:
		return DecorationAnchors.IsValidIndex(Target.Index) ? DecorationAnchors[Target.Index] : TWeakPtr<SWidget>();
	default:
		return TWeakPtr<SWidget>();
	}
}

TSharedPtr<SWidget> SFramework2DProcGenPanel::GetSlotWidget(EFramework2DBiomeSlot Slot) const
{
	return SlotWidgets.FindRef((int32)Slot).Pin();
}

bool SFramework2DProcGenPanel::OpenPicker(const FFramework2DPieceTarget& Target)
{
	const TSharedPtr<SWidget> Anchor = FindAnchor(Target).Pin();
	return Anchor.IsValid() && OpenPickerAt(Target, Anchor.ToSharedRef(), false);
}

bool SFramework2DProcGenPanel::OpenPickerAt(const FFramework2DPieceTarget& Target, const TSharedRef<SWidget>& Anchor, bool bFromKeyboard)
{
	ClosePicker();
	if (!FSlateApplication::IsInitialized() || !Mode->GetTileSet() || Mode->GetActiveBiomeId() == INDEX_NONE) { return false; }

	// Debajo del hueco (o encima, si no cabe: lo decide el menú con el rectángulo del hueco).
	const FGeometry& Geo = Anchor->GetTickSpaceGeometry();
	const FVector2D AnchorPos = Geo.GetAbsolutePosition();
	const FVector2D AnchorSize = Geo.GetAbsoluteSize();
	const TSharedPtr<IMenu> Menu = FSlateApplication::Get().PushMenu(Anchor, FWidgetPath(), MakePickerContent(Target), AnchorPos,
		FPopupTransitionEffect(FPopupTransitionEffect::ComboButton), /*bFocusImmediately*/ true, AnchorSize);
	if (!Menu.IsValid()) { return false; }

	PickerMenu = Menu;
	PickerAnchor = Anchor;
	PickerTarget = Target;
	PickerBiomeId = Mode->GetActiveBiomeId();
	bPickerFromKeyboard = bFromKeyboard;
	bRestoreFocusOnDismiss = false;

	// Se cierra también al hacer clic fuera o con Esc: el panel se entera aquí.
	const TWeakPtr<SFramework2DProcGenPanel> WeakPanel = SharedThis(this);
	Menu->GetOnMenuDismissed().AddLambda([WeakPanel](TSharedRef<IMenu>)
	{
		if (const TSharedPtr<SFramework2DProcGenPanel> Panel = WeakPanel.Pin()) { Panel->OnPickerDismissed(); }
	});
	return true;
}

TSharedRef<SWidget> SFramework2DProcGenPanel::MakePickerContent(const FFramework2DPieceTarget& Target)
{
	return SNew(SFramework2DPiecePicker, SharedThis(this), Target);
}

bool SFramework2DProcGenPanel::IsPickerOpen() const
{
	return PickerMenu.IsValid();
}

void SFramework2DProcGenPanel::ClosePicker()
{
	if (const TSharedPtr<IMenu> Menu = PickerMenu.Pin())
	{
		bRestoreFocusOnDismiss = true;
		Menu->Dismiss();
	}
	PickerMenu.Reset();
}

void SFramework2DProcGenPanel::OnPickerDismissed()
{
	PickerMenu.Reset();
	// Si se abrió con el teclado, el foco vuelve a su hueco (para seguir con Tab). Al hacer clic
	// fuera no: el foco es de lo que se ha pulsado.
	const TSharedPtr<SWidget> Anchor = PickerAnchor.Pin();
	if (bRestoreFocusOnDismiss && bPickerFromKeyboard && Anchor.IsValid() && FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().SetKeyboardFocus(Anchor, EFocusCause::SetDirectly);
	}
	bRestoreFocusOnDismiss = false;
	bPickerFromKeyboard = false;
}

bool SFramework2DProcGenPanel::PickValue(const FFramework2DPieceTarget& InTarget, int32 Value)
{
	const FFramework2DPieceTarget Target = InTarget; // copia: quien llama puede ser el selector que se cierra
	const int32 BiomeId = Mode->GetActiveBiomeId();
	if (BiomeId == INDEX_NONE || Value < 0) { return false; }
	if (Target.IsBlock()) { return PickBlock(Target, Value); }
	ClosePicker();

	switch (Target.Kind)
	{
	case EFramework2DPieceTargetKind::Slot:
		Mode->SetBiomeSlot(BiomeId, Target.Slot, Value);
		break;
	case EFramework2DPieceTargetKind::AddVariant:
		Mode->AddBiomeCenterVariant(BiomeId, Value);
		break;
	case EFramework2DPieceTargetKind::Variant:
		Mode->ChangeBiome(BiomeId, LOCTEXT("ChangeVariant", "Change center variant"), [&Target, Value](FFramework2DBiome& Biome)
		{
			if (Biome.CenterVariants.IsValidIndex(Target.Index)) { Biome.CenterVariants[Target.Index] = Value; }
		});
		break;
	case EFramework2DPieceTargetKind::AddDecoration:
		Mode->AddBiomeDecoration(BiomeId, Value, EFramework2DDecorPlacement::Ground);
		break;
	case EFramework2DPieceTargetKind::Decoration:
		Mode->ChangeBiome(BiomeId, LOCTEXT("ChangeDecoration", "Change decoration"), [&Target, Value](FFramework2DBiome& Biome)
		{
			if (Biome.Decorations.IsValidIndex(Target.Index)) { Biome.Decorations[Target.Index].Value = Value; }
		});
		break;
	default:
		return false;
	}
	F2DPalette::RedrawViewports();
	return true;
}

bool SFramework2DProcGenPanel::PickBlock(const FFramework2DPieceTarget& InTarget, int32 TopLeftTileValue)
{
	const FFramework2DPieceTarget Target = InTarget;
	const int32 BiomeId = Mode->GetActiveBiomeId();
	if (BiomeId == INDEX_NONE || !Framework2D::IsAtlasTileValue(TopLeftTileValue)) { return false; }
	ClosePicker();
	if (Target.BlockSize == 5) { Mode->SetBiome5x5FromBlock(BiomeId, TopLeftTileValue); }
	else { Mode->SetBiome3x3FromBlock(BiomeId, Target.bBackground, TopLeftTileValue); }
	F2DPalette::RedrawViewports();
	return true;
}

bool SFramework2DProcGenPanel::UseSelectionAs5x5()
{
	const int32 BiomeId = Mode->GetActiveBiomeId();
	if (BiomeId == INDEX_NONE || !Mode->CanUseSelectionAs5x5()) { return false; }
	ClosePicker();
	Mode->SetBiome5x5FromSelection(BiomeId);
	F2DPalette::RedrawViewports();
	return true;
}

bool SFramework2DProcGenPanel::UseSelectionAs3x3(bool bBackground)
{
	const int32 BiomeId = Mode->GetActiveBiomeId();
	if (BiomeId == INDEX_NONE || !Mode->CanUseSelectionAs3x3()) { return false; }
	ClosePicker();
	Mode->SetBiome3x3FromSelection(BiomeId, bBackground);
	F2DPalette::RedrawViewports();
	return true;
}

bool SFramework2DProcGenPanel::ClearTarget(const FFramework2DPieceTarget& InTarget)
{
	const FFramework2DPieceTarget Target = InTarget;
	const int32 BiomeId = Mode->GetActiveBiomeId();
	if (BiomeId == INDEX_NONE || Target.IsAdd()) { return false; }
	ClosePicker();

	switch (Target.Kind)
	{
	case EFramework2DPieceTargetKind::Slot:
		Mode->SetBiomeSlot(BiomeId, Target.Slot, -1);
		break;
	case EFramework2DPieceTargetKind::Block3x3:
		Mode->ChangeBiome(BiomeId, Target.BlockSize == 5 ? LOCTEXT("ClearBlock5", "Clear 5×5") : LOCTEXT("ClearBlock", "Clear 3×3"), [&Target](FFramework2DBiome& Biome)
		{
			if (Target.BlockSize == 5) { Biome.Ground5 = FFramework2DTile5x5(); }
			else { (Target.bBackground ? Biome.Background : Biome.Ground) = FFramework2DTile3x3(); }
		});
		break;
	case EFramework2DPieceTargetKind::Variant:
		Mode->RemoveBiomeCenterVariant(BiomeId, Target.Index);
		break;
	case EFramework2DPieceTargetKind::Decoration:
		Mode->RemoveBiomeDecoration(BiomeId, Target.Index);
		break;
	default:
		return false;
	}
	F2DPalette::RedrawViewports();
	return true;
}

// ---------------------------------------------------------------------
//  3. Receta
// ---------------------------------------------------------------------
void SFramework2DProcGenPanel::ChangeRecipe(const FText& Description, TFunctionRef<void(FFramework2DProcGenSettings&)> Change)
{
	// El modo prueba el cambio en una copia: sin cambio no hay paso de deshacer (ni se regenera).
	Mode->ChangeProcGenSettings(Description, Change);
	F2DPalette::RedrawViewports();
}

TSharedRef<SWidget> SFramework2DProcGenPanel::MakeRecipeGroup(const FText& Title)
{
	return SNew(STextBlock)
		.TextStyle(&F2DPalette::Text("F2D.Text.Section"))
		.Text(Title.ToUpper());
}

TSharedRef<SWidget> SFramework2DProcGenPanel::MakeRecipeRow(const FText& Label, const FText& Tip, const TSharedRef<SWidget>& Value)
{
	return SNew(SHorizontalBox)
		.ToolTipText(Tip)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		[
			SNew(SBox)
			.WidthOverride(150.0f)
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
			Value
		];
}

TSharedRef<SWidget> SFramework2DProcGenPanel::MakeRecipeSpin(const FText& Label, const FText& Tip, float Min, float Max, float Delta, int32 Digits,
	TFunction<float(const FFramework2DProcGenSettings&)> Get, TFunction<void(FFramework2DProcGenSettings&, float)> Set, bool bSlider)
{
	// Se ve en vivo mientras se arrastra; se guarda (un paso de deshacer y, con «Regenerar al
	// cambiar», el mapa nuevo en ese mismo paso) al soltar o al escribirlo.
	const TSharedRef<F2DPalette::FSpinDrag> Drag = MakeShared<F2DPalette::FSpinDrag>();
	FFramework2DTilePaintMode* M = Mode;
	auto Commit = [this, Set, Label](float Value)
	{
		ChangeRecipe(FText::Format(LOCTEXT("RecipeParam", "Recipe: {0}"), Label), [&Set, Value](FFramework2DProcGenSettings& Settings) { Set(Settings, Value); });
	};

	return MakeRecipeRow(Label, Tip,
		SNew(SSpinBox<float>)
		.MinValue(Min)
		.MaxValue(Max)
		.MinSliderValue(bSlider ? TOptional<float>(Min) : TOptional<float>())
		.MaxSliderValue(bSlider ? TOptional<float>(Max) : TOptional<float>())
		.Delta(Delta)
		.MinFractionalDigits(0)
		.MaxFractionalDigits(Digits)
		.ToolTipText(Tip)
		.Value_Lambda([M, Get, Drag]() -> float
		{
			if (Drag->bDragging) { return Drag->Value; }
			const FFramework2DProcGenSettings* Settings = M->GetProcGenSettings();
			return Settings ? Get(*Settings) : 0.0f;
		})
		.OnBeginSliderMovement_Lambda([M, Get, Drag]()
		{
			const FFramework2DProcGenSettings* Settings = M->GetProcGenSettings();
			Drag->bDragging = true;
			Drag->Value = Settings ? Get(*Settings) : 0.0f;
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
		}));
}

TSharedRef<SWidget> SFramework2DProcGenPanel::MakePercentSpin(const FText& Label, const FText& Tip,
	TFunction<float(const FFramework2DProcGenSettings&)> Get, TFunction<void(FFramework2DProcGenSettings&, float)> Set)
{
	// Se ve de 0 a 100 y se guarda de 0 a 1.
	return MakeRecipeSpin(Label, Tip, 0.0f, 100.0f, 1.0f, 0,
		[Get](const FFramework2DProcGenSettings& Settings) { return FMath::RoundToFloat(Get(Settings) * 100.0f); },
		[Set](FFramework2DProcGenSettings& Settings, float Value) { Set(Settings, FMath::Clamp(Value, 0.0f, 100.0f) / 100.0f); });
}

TSharedRef<SWidget> SFramework2DProcGenPanel::MakeMapSizeSpin(const FText& Label, const FText& Tip, bool bHeight)
{
	// Tamaño del mapa: se guarda al soltar o al escribirlo con ResizeMap (un paso de deshacer).
	const TSharedRef<F2DPalette::FSpinDrag> Drag = MakeShared<F2DPalette::FSpinDrag>();
	FFramework2DTilePaintMode* M = Mode;
	auto Current = [M, bHeight]() -> float
	{
		const UFramework2DTileMapAsset* Map = M->GetTileMap();
		return Map ? (float)(bHeight ? Map->Height : Map->Width) : 0.0f;
	};
	auto Commit = [M, bHeight](float Value)
	{
		UFramework2DTileMapAsset* Map = M->GetTileMap();
		if (!Map) { return; }
		const int32 N = FMath::Clamp(FMath::RoundToInt(Value), 4, 1024);
		const int32 W = bHeight ? Map->Width : N;
		const int32 H = bHeight ? N : Map->Height;
		if (W != Map->Width || H != Map->Height)
		{
			M->ResizeMap(W, H);
			F2DPalette::RedrawViewports();
		}
	};

	return MakeRecipeRow(Label, Tip,
		SNew(SSpinBox<float>)
		.MinValue(4.0f)
		.MaxValue(1024.0f)
		.Delta(1.0f)
		.MinFractionalDigits(0)
		.MaxFractionalDigits(0)
		.ToolTipText(Tip)
		.Value_Lambda([Current, Drag]() -> float { return Drag->bDragging ? Drag->Value : Current(); })
		.OnBeginSliderMovement_Lambda([Current, Drag]()
		{
			Drag->bDragging = true;
			Drag->Value = Current();
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
		}));
}

TSharedRef<SWidget> SFramework2DProcGenPanel::MakeLayerNameRow(const FText& Label, const FText& Tip, int32 Which)
{
	FFramework2DTilePaintMode* M = Mode;
	// Ni vacío ni repetido: cada parte del nivel necesita su propia capa.
	auto Verify = [M, Which](const FText& InText, FText& OutError) -> bool
	{
		if (!F2DPalette::VerifyName(InText, OutError)) { return false; }
		const FFramework2DProcGenSettings* Settings = M->GetProcGenSettings();
		if (!Settings) { return true; }
		const FName Name(*InText.ToString().TrimStartAndEnd());
		for (int32 Other = 0; Other < 4; ++Other)
		{
			if (Other != Which && Framework2DProcGenPanelUtil::LayerName(*Settings, Other) == Name)
			{
				OutError = FText::Format(LOCTEXT("LayerNameTaken", "Already used by «{0}»: each part of the level needs its own layer."), Framework2DProcGenPanelUtil::LayerTitle(Other));
				return false;
			}
		}
		return true;
	};

	return MakeRecipeRow(Label, Tip,
		SNew(SEditableTextBox)
		.ToolTipText(Tip)
		.Font(F2DPalette::Font(false, 9))
		.SelectAllTextWhenFocused(true)
		.RevertTextOnEscape(true)
		.Text_Lambda([M, Which]()
		{
			const FFramework2DProcGenSettings* Settings = M->GetProcGenSettings();
			return Settings ? FText::FromName(Framework2DProcGenPanelUtil::LayerName(*Settings, Which)) : FText::GetEmpty();
		})
		.OnVerifyTextChanged_Lambda(Verify)
		.OnTextCommitted_Lambda([this, Which, Verify](const FText& NewText, ETextCommit::Type Commit)
		{
			if (Commit == ETextCommit::OnCleared) { return; }
			FText Error;
			if (!Verify(NewText, Error)) { return; }
			const FName Name(*NewText.ToString().TrimStartAndEnd());
			ChangeRecipe(LOCTEXT("RecipeLayerName", "Recipe: layer name"), [Which, Name](FFramework2DProcGenSettings& Settings)
			{
				Framework2DProcGenPanelUtil::LayerNameRef(Settings, Which) = Name;
			});
		}));
}

TSharedRef<SWidget> SFramework2DProcGenPanel::MakeRecipeCard()
{
	FFramework2DTilePaintMode* M = Mode;
	TSharedRef<SVerticalBox> Body = SNew(SVerticalBox);
	auto Add = [&Body](const TSharedRef<SWidget>& Widget)
	{
		Body->AddSlot().AutoHeight().Padding(0.0f, 2.0f)[ Widget ];
	};
	auto Group = [this, &Body](const FText& Title)
	{
		Body->AddSlot().AutoHeight().Padding(0.0f, 10.0f, 0.0f, 4.0f)[ MakeRecipeGroup(Title) ];
	};
	using FSettings = FFramework2DProcGenSettings;

	// Tamaño del mapa.
	Group(LOCTEXT("GroupSize", "Map size"));
	Add(MakeMapSizeSpin(LOCTEXT("MapWidth", "Width (tiles)"),
		LOCTEXT("MapWidthTip", "Map width in tiles (4 to 1024). What is painted is kept, anchored top-left (Ctrl+Z undoes it)."), false));
	Add(MakeMapSizeSpin(LOCTEXT("MapHeight", "Height (tiles)"),
		LOCTEXT("MapHeightTip", "Map height in tiles (4 to 1024). Each height takes «Height of each level» tiles and there must be sky on top."), true));

	// Relieve.
	Group(LOCTEXT("GroupRelief", "Relief"));
	Add(MakeRecipeSpin(LOCTEXT("Levels", "Heights"),
		LOCTEXT("LevelsTip", "How many different heights the ground can have (1 = flat). If they do not fit in the map, the ones that fit are used."),
		1.0f, 16.0f, 1.0f, 0, [](const FSettings& S) { return (float)S.Levels; },
		[](FSettings& S, float V) { S.Levels = FMath::Clamp(FMath::RoundToInt(V), 1, 16); }));
	Add(MakeRecipeSpin(LOCTEXT("LevelHeight", "Height of each level"),
		LOCTEXT("LevelHeightTip", "Tiles from one height to the next (the height of each step)."),
		1.0f, 16.0f, 1.0f, 0, [](const FSettings& S) { return (float)S.LevelHeight; },
		[](FSettings& S, float V) { S.LevelHeight = FMath::Clamp(FMath::RoundToInt(V), 1, 16); }));
	Add(MakeRecipeSpin(LOCTEXT("BaseHeight", "Base ground"),
		LOCTEXT("BaseHeightTip", "Ground tiles below the lowest height."),
		1.0f, 256.0f, 1.0f, 0, [](const FSettings& S) { return (float)S.BaseHeight; },
		[](FSettings& S, float V) { S.BaseHeight = FMath::Clamp(FMath::RoundToInt(V), 1, 256); }));
	Add(MakeRecipeSpin(LOCTEXT("PlateauMin", "Min flat"),
		LOCTEXT("PlateauMinTip", "Minimum width (tiles) of each flat stretch."),
		1.0f, 128.0f, 1.0f, 0, [](const FSettings& S) { return (float)S.PlateauMinWidth; },
		[](FSettings& S, float V)
		{
			S.PlateauMinWidth = FMath::Clamp(FMath::RoundToInt(V), 1, 128);
			S.PlateauMaxWidth = FMath::Max(S.PlateauMaxWidth, S.PlateauMinWidth);
		}));
	Add(MakeRecipeSpin(LOCTEXT("PlateauMax", "Max flat"),
		LOCTEXT("PlateauMaxTip", "Maximum width (tiles) of each flat stretch."),
		1.0f, 256.0f, 1.0f, 0, [](const FSettings& S) { return (float)S.PlateauMaxWidth; },
		[](FSettings& S, float V)
		{
			S.PlateauMaxWidth = FMath::Clamp(FMath::RoundToInt(V), 1, 256);
			S.PlateauMinWidth = FMath::Min(S.PlateauMinWidth, S.PlateauMaxWidth);
		}));
	Add(MakeRecipeSpin(LOCTEXT("MaxLevelStep", "Max jump"),
		LOCTEXT("MaxLevelStepTip", "How many heights the ground can rise or drop at once in a cliff."),
		1.0f, 15.0f, 1.0f, 0, [](const FSettings& S) { return (float)S.MaxLevelStep; },
		[](FSettings& S, float V) { S.MaxLevelStep = FMath::Clamp(FMath::RoundToInt(V), 1, 15); }));
	Add(SNew(SWrapBox)
		.UseAllottedSize(true)
		.InnerSlotPadding(FVector2D(4.0f, 4.0f))
		+ SWrapBox::Slot()
		[
			F2DPalette::ToggleChip("F2D.Icon.Mountain", LOCTEXT("HillsChip", "Hills (outdoor)"),
				LOCTEXT("HillsChipTip", "Hills: the ground rises and falls gently, cell by cell, with ramps where there are pieces (natural outdoors). Off: steps (flats at several heights)."),
				[M]() { const FFramework2DProcGenSettings* S = M->GetProcGenSettings(); return S && S->ReliefStyle == EFramework2DReliefStyle::Hills; },
				[this](bool bOn)
				{
					ChangeRecipe(LOCTEXT("RecipeRelief", "Recipe: ground shape"), [bOn](FFramework2DProcGenSettings& S)
					{
						S.ReliefStyle = bOn ? EFramework2DReliefStyle::Hills : EFramework2DReliefStyle::Steps;
					});
				})
		]);
	Add(MakePercentSpin(LOCTEXT("Roughness", "Hills: movement (%)"),
		LOCTEXT("RoughnessTip", "Only with «Hills»: 0 = long gentle hills; 100 = they rise and fall a lot."),
		[](const FSettings& S) { return S.Roughness; }, [](FSettings& S, float V) { S.Roughness = V; }));
	Add(MakePercentSpin(LOCTEXT("RampChance", "Ramps (%)"),
		LOCTEXT("RampChanceTip", "Of the height changes, how many are ramps instead of steps. Needs ramps in the biome."),
		[](const FSettings& S) { return S.RampChance; }, [](FSettings& S, float V) { S.RampChance = V; }));
	Add(MakePercentSpin(LOCTEXT("GentleChance", "Gentle ramps (%)"),
		LOCTEXT("GentleChanceTip", "Of the ramps, how many are gentle (two tiles per tile of height). Needs gentle ramps in the biome."),
		[](const FSettings& S) { return S.GentleRampChance; }, [](FSettings& S, float V) { S.GentleRampChance = V; }));

	// Agua.
	Group(LOCTEXT("GroupWater", "Water"));
	Add(MakePercentSpin(LOCTEXT("PitChance", "Pits (%)"),
		LOCTEXT("PitChanceTip", "Chance that a flat stretch has a pit."),
		[](const FSettings& S) { return S.PitChance; }, [](FSettings& S, float V) { S.PitChance = V; }));
	Add(MakeRecipeSpin(LOCTEXT("PitDepth", "Pit depth"),
		LOCTEXT("PitDepthTip", "Depth of the pits, in tiles."),
		1.0f, 16.0f, 1.0f, 0, [](const FSettings& S) { return (float)S.PitDepth; },
		[](FSettings& S, float V) { S.PitDepth = FMath::Clamp(FMath::RoundToInt(V), 1, 16); }));
	Add(MakePercentSpin(LOCTEXT("LakeChance", "Lakes (%)"),
		LOCTEXT("LakeChanceTip", "Of the hollows (pits and valleys), how many fill with water. Needs water in the biome."),
		[](const FSettings& S) { return S.LakeChance; }, [](FSettings& S, float V) { S.LakeChance = V; }));
	Add(MakeRecipeSpin(LOCTEXT("MaxLakeWidth", "Lake: max width"),
		LOCTEXT("MaxLakeWidthTip", "Maximum width of a lake, in tiles. In a wider hollow the water goes down until only its deepest parts stay full."),
		3.0f, 1024.0f, 1.0f, 0, [](const FSettings& S) { return (float)S.MaxLakeWidth; },
		[](FSettings& S, float V) { S.MaxLakeWidth = FMath::Clamp(FMath::RoundToInt(V), 3, 1024); }, false));
	Add(MakePercentSpin(LOCTEXT("WaterfallChance", "Waterfalls (%)"),
		LOCTEXT("WaterfallChanceTip", "Of the cliffs of 2 tiles or more, how many have a waterfall. Needs the waterfall fall in the biome."),
		[](const FSettings& S) { return S.WaterfallChance; }, [](FSettings& S, float V) { S.WaterfallChance = V; }));

	// Plataformas.
	Group(LOCTEXT("GroupPlatforms", "Platforms"));
	Add(MakePercentSpin(LOCTEXT("PlatformChance", "Platforms (%)"),
		LOCTEXT("PlatformChanceTip", "Chance that a flat stretch has a floating platform above it."),
		[](const FSettings& S) { return S.PlatformChance; }, [](FSettings& S, float V) { S.PlatformChance = V; }));
	Add(MakeRecipeSpin(LOCTEXT("PlatformMin", "Min length"),
		LOCTEXT("PlatformMinTip", "Minimum platform length, in tiles."),
		1.0f, 64.0f, 1.0f, 0, [](const FSettings& S) { return (float)S.PlatformMinLength; },
		[](FSettings& S, float V)
		{
			S.PlatformMinLength = FMath::Clamp(FMath::RoundToInt(V), 1, 64);
			S.PlatformMaxLength = FMath::Max(S.PlatformMaxLength, S.PlatformMinLength);
		}));
	Add(MakeRecipeSpin(LOCTEXT("PlatformMax", "Max length"),
		LOCTEXT("PlatformMaxTip", "Maximum platform length, in tiles."),
		1.0f, 64.0f, 1.0f, 0, [](const FSettings& S) { return (float)S.PlatformMaxLength; },
		[](FSettings& S, float V)
		{
			S.PlatformMaxLength = FMath::Clamp(FMath::RoundToInt(V), 1, 64);
			S.PlatformMinLength = FMath::Min(S.PlatformMinLength, S.PlatformMaxLength);
		}));

	// Islas y puentes.
	Group(LOCTEXT("GroupIslands", "Islands and bridges"));
	Add(MakePercentSpin(LOCTEXT("IslandChance", "Floating islands (%)"),
		LOCTEXT("IslandChanceTip", "Islands with a rock base in the air: chance for every stretch of about 10 tiles. Made with the 3×3 terrain (with edges and decoration)."),
		[](const FSettings& S) { return S.IslandChance; }, [](FSettings& S, float V) { S.IslandChance = V; }));
	Add(MakeRecipeSpin(LOCTEXT("IslandMin", "Island: min width"),
		LOCTEXT("IslandMinTip", "Minimum island width, in tiles."),
		2.0f, 64.0f, 1.0f, 0, [](const FSettings& S) { return (float)S.IslandMinWidth; },
		[](FSettings& S, float V)
		{
			S.IslandMinWidth = FMath::Clamp(FMath::RoundToInt(V), 2, 64);
			S.IslandMaxWidth = FMath::Max(S.IslandMaxWidth, S.IslandMinWidth);
		}));
	Add(MakeRecipeSpin(LOCTEXT("IslandMax", "Island: max width"),
		LOCTEXT("IslandMaxTip", "Maximum island width, in tiles."),
		2.0f, 64.0f, 1.0f, 0, [](const FSettings& S) { return (float)S.IslandMaxWidth; },
		[](FSettings& S, float V)
		{
			S.IslandMaxWidth = FMath::Clamp(FMath::RoundToInt(V), 2, 64);
			S.IslandMinWidth = FMath::Min(S.IslandMinWidth, S.IslandMaxWidth);
		}));
	Add(MakePercentSpin(LOCTEXT("BridgeChance", "Bridges (%)"),
		LOCTEXT("BridgeChanceTip", "Of the gaps that can be crossed (between two banks at the same height), how many get a bridge. Needs a bridge in the biome."),
		[](const FSettings& S) { return S.BridgeChance; }, [](FSettings& S, float V) { S.BridgeChance = V; }));

	// Objetos grandes.
	Group(LOCTEXT("GroupProps", "Large objects"));
	Add(MakePercentSpin(LOCTEXT("PropDensity", "Objects (%)"),
		LOCTEXT("PropDensityTip", "Of every flat ground spot where a large object fits (tree, rock...), the fraction that gets one. Needs objects in the biome."),
		[](const FSettings& S) { return S.PropDensity; }, [](FSettings& S, float V) { S.PropDensity = V; }));
	Add(MakeRecipeSpin(LOCTEXT("PropSpacing", "Object spacing"),
		LOCTEXT("PropSpacingTip", "Minimum free tiles between two large objects."),
		0.0f, 64.0f, 1.0f, 0, [](const FSettings& S) { return (float)S.PropSpacing; },
		[](FSettings& S, float V) { S.PropSpacing = FMath::Clamp(FMath::RoundToInt(V), 0, 64); }));

	// Decoración.
	Group(LOCTEXT("GroupDecoration", "Decoration"));
	Add(MakePercentSpin(LOCTEXT("DecorationDensity", "Density (%)"),
		LOCTEXT("DecorationDensityTip", "Of every free cell above the ground (or below a platform), how many get a decoration."),
		[](const FSettings& S) { return S.DecorationDensity; }, [](FSettings& S, float V) { S.DecorationDensity = V; }));
	Add(MakeRecipeSpin(LOCTEXT("DecorationSpacing", "Spacing"),
		LOCTEXT("DecorationSpacingTip", "Minimum free cells between two decorations in a row."),
		0.0f, 16.0f, 1.0f, 0, [](const FSettings& S) { return (float)S.DecorationSpacing; },
		[](FSettings& S, float V) { S.DecorationSpacing = FMath::Clamp(FMath::RoundToInt(V), 0, 16); }));
	Add(MakePercentSpin(LOCTEXT("CenterVariantChance", "Center variants (%)"),
		LOCTEXT("CenterVariantChanceTip", "Of the terrain center cells, how many use a variant. Needs variants in the biome."),
		[](const FSettings& S) { return S.CenterVariantChance; }, [](FSettings& S, float V) { S.CenterVariantChance = V; }));

	// Fondo y bordes.
	Group(LOCTEXT("GroupBackground", "Background and edges"));
	Add(SNew(SWrapBox)
		.UseAllottedSize(true)
		.InnerSlotPadding(FVector2D(4.0f, 4.0f))
		+ SWrapBox::Slot()
		[
			F2DPalette::ToggleChip("F2D.Icon.Background", LOCTEXT("BackgroundChip", "Background"),
				LOCTEXT("BackgroundChipTip", "Background: fills the background layer with the biome's 3×3 background (back wall and hills). Visible when digging."),
				[M]() { const FFramework2DProcGenSettings* S = M->GetProcGenSettings(); return S && S->bBackground; },
				[this](bool bOn) { ChangeRecipe(LOCTEXT("RecipeBackground", "Recipe: background"), [bOn](FFramework2DProcGenSettings& S) { S.bBackground = bOn; }); })
		]
		+ SWrapBox::Slot()
		[
			F2DPalette::ToggleChip("F2D.Icon.Collide", LOCTEXT("EdgeWallsChip", "Edge walls"),
				LOCTEXT("EdgeWallsChipTip", "Edge walls: terrain columns from bottom to top on the left and right edges of the map."),
				[M]() { const FFramework2DProcGenSettings* S = M->GetProcGenSettings(); return S && S->bEdgeWalls; },
				[this](bool bOn) { ChangeRecipe(LOCTEXT("RecipeEdgeWalls", "Recipe: edge walls"), [bOn](FFramework2DProcGenSettings& S) { S.bEdgeWalls = bOn; }); })
		]);
	Add(MakeRecipeSpin(LOCTEXT("BackgroundRise", "Rises above the terrain"),
		LOCTEXT("BackgroundRiseTip", "How far the background shows above the terrain, in tiles. 0 = only behind (visible when digging)."),
		0.0f, 64.0f, 1.0f, 0, [](const FSettings& S) { return (float)S.BackgroundRise; },
		[](FSettings& S, float V) { S.BackgroundRise = FMath::Clamp(FMath::RoundToInt(V), 0, 64); }));

	// Semilla.
	Group(LOCTEXT("GroupSeed", "Seed"));
	Add(SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.FillWidth(1.0f)
		[
			MakeRecipeSpin(LOCTEXT("Seed", "Seed"),
				LOCTEXT("SeedTip", "Another seed = another map with the same settings. Same recipe and same seed = the same map."),
				0.0f, 9999999.0f, 1.0f, 0, [](const FSettings& S) { return (float)S.Seed; },
				[](FSettings& S, float V) { S.Seed = FMath::Clamp(FMath::RoundToInt(V), 0, 9999999); }, /*bSlider*/ false)
		]
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		.Padding(4.0f, 0.0f, 0.0f, 0.0f)
		[
			F2DPalette::IconButton("F2D.Icon.Dice",
				LOCTEXT("ReseedTip", "Another random seed. With «Regenerate on change» on, it generates the new map right away (one Ctrl+Z step)."),
				FOnClicked::CreateLambda([this]()
				{
					ChangeRecipe(LOCTEXT("RecipeReseed", "New seed"), [](FFramework2DProcGenSettings& S) { S.Seed = Framework2DProcGenPanelUtil::NewSeed(S.Seed); });
					return FReply::Handled();
				}),
				TAttribute<bool>::CreateLambda([M]() { return M->GetProcGenSettings() != nullptr; }))
		]);

	// Avanzado (plegado): nombres de las capas que se rellenan.
	TSharedRef<SExpandableArea> Advanced = SNew(SExpandableArea)
		.InitiallyCollapsed(true)
		.AreaTitle(LOCTEXT("Advanced", "Advanced"))
		.AreaTitleFont(F2DPalette::Font(true, 9))
		.BorderImage(FStyleDefaults::GetNoBrush())
		.BorderBackgroundColor(FLinearColor::Transparent)
		.HeaderPadding(FMargin(0.0f, 4.0f))
		.Padding(FMargin(0.0f, 4.0f, 0.0f, 0.0f))
		.BodyContent()
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 0.0f, 0.0f, 4.0f)
			[
				F2DPalette::Caption(LOCTEXT("AdvancedHelp", "Layers the generator fills. Missing ones are created; their content is REPLACED. Other layers are not touched."))
			]
			+ SVerticalBox::Slot().AutoHeight().Padding(0.0f, 2.0f)
			[
				MakeLayerNameRow(LOCTEXT("LayerTerrain", "Terrain layer"), LOCTEXT("LayerTerrainTip", "Terrain layer (collides and breaks)."), 0)
			]
			+ SVerticalBox::Slot().AutoHeight().Padding(0.0f, 2.0f)
			[
				MakeLayerNameRow(LOCTEXT("LayerBackground", "Background layer"), LOCTEXT("LayerBackgroundTip", "Background layer (darkened back wall: neither collides nor breaks)."), 1)
			]
			+ SVerticalBox::Slot().AutoHeight().Padding(0.0f, 2.0f)
			[
				MakeLayerNameRow(LOCTEXT("LayerWater", "Water layer"), LOCTEXT("LayerWaterTip", "Water and waterfall layer (neither collides nor breaks)."), 2)
			]
			+ SVerticalBox::Slot().AutoHeight().Padding(0.0f, 2.0f)
			[
				MakeLayerNameRow(LOCTEXT("LayerDecoration", "Decoration layer"), LOCTEXT("LayerDecorationTip", "Decoration layer (does not collide; breaks when dug)."), 3)
			]
		];
	Framework2DProcGenPanelUtil::SetFirstButtonTip(Advanced,
		LOCTEXT("AdvancedTip", "Advanced: names of the layers the generator fills. Click to show or hide them."), 0);
	Body->AddSlot().AutoHeight().Padding(0.0f, 10.0f, 0.0f, 0.0f)[ Advanced ];

	return SNew(SBox)
		.Visibility_Lambda([M]() { return M->GetProcGenSettings() ? EVisibility::Visible : EVisibility::Collapsed; })
		[
			F2DPalette::Card(
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					F2DPalette::CardHeader("F2D.Icon.Mountain", LOCTEXT("RecipeTitle", "Recipe"))
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(0.0f, 2.0f, 0.0f, 0.0f)
				[
					F2DPalette::Caption(LOCTEXT("RecipeHelp", "What the level is like (saved in the Tile Map). Same recipe and same seed = the same map. Each value is saved when you release or type it (one Ctrl+Z step)."))
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					Body
				])
		];
}

// ---------------------------------------------------------------------
//  4. Generar (pie)
// ---------------------------------------------------------------------
bool SFramework2DProcGenPanel::CanGenerate() const
{
	return Mode->GetGenerateProblem().IsEmpty();
}

FText SFramework2DProcGenPanel::GetGenerateTip() const
{
	const FText Problem = Mode->GetGenerateProblem();
	if (!Problem.IsEmpty())
	{
		return FText::Format(LOCTEXT("GenerateOffTip", "Cannot generate yet: {0}"), Problem);
	}
	return LOCTEXT("GenerateTip", "Generates the map with the recipe and the active biome. Replaces its terrain, background, water and decoration layers (a single Ctrl+Z step).");
}

FText SFramework2DProcGenPanel::GetReportText() const
{
	const FText Problem = Mode->GetGenerateProblem();
	if (!Problem.IsEmpty())
	{
		return FText::Format(LOCTEXT("ReportProblem", "Cannot generate: {0}"), Problem);
	}
	if (!Mode->bHasGenerateReport)
	{
		return LOCTEXT("ReportNone", "Ready. Press «Generate map» to create the level.");
	}
	const FFramework2DProcGenReport& Report = Mode->LastGenerateReport;
	if (!Report.bSuccess)
	{
		return FText::Format(LOCTEXT("ReportFailed", "Could not generate: {0}"), FText::FromString(Report.Message));
	}
	const FText Counts = FText::Format(LOCTEXT("ReportCounts", "{0} {0}|plural(one=height,other=heights) · {1} {1}|plural(one=ramp,other=ramps) · {2} {2}|plural(one=lake,other=lakes) · {3} {3}|plural(one=waterfall,other=waterfalls) · {4} {4}|plural(one=platform,other=platforms) · {5} {5}|plural(one=decoration,other=decorations)"),
		Report.Levels, Report.Ramps, Report.Lakes, Report.Waterfalls, Report.Platforms, Report.Decorations);
	// Avisos (por ejemplo, que no caben todas las alturas pedidas), en otra línea.
	return Report.Message.IsEmpty() ? Counts : FText::Format(LOCTEXT("ReportCountsWarning", "{0}\n{1}"), Counts, FText::FromString(Report.Message));
}

TSharedRef<SWidget> SFramework2DProcGenPanel::MakeGenerateCard()
{
	FFramework2DTilePaintMode* M = Mode;
	auto Kind = [M]() -> Framework2DProcGenPanelUtil::EReportKind
	{
		using EKind = Framework2DProcGenPanelUtil::EReportKind;
		if (!M->GetGenerateProblem().IsEmpty()) { return EKind::Problem; }
		if (!M->bHasGenerateReport) { return EKind::None; }
		if (!M->LastGenerateReport.bSuccess) { return EKind::Problem; }
		return M->LastGenerateReport.Message.IsEmpty() ? EKind::Ok : EKind::Warning;
	};

	// Botón principal grande: icono de dado y texto.
	GenerateButton = SNew(SButton)
		.ButtonStyle(&F2DPalette::Button("F2D.Button.Primary"))
		.ContentPadding(FMargin(0.0f, 4.0f))
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.IsEnabled_Lambda([this]() { return CanGenerate(); })
		.ToolTipText_Lambda([this]() { return GetGenerateTip(); })
		.OnClicked_Lambda([M]()
		{
			M->GenerateMap(false);
			F2DPalette::RedrawViewports();
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
					.Image(F2DPalette::Brush("F2D.Icon.Dice"))
					.ColorAndOpacity(FSlateColor::UseForeground())
				]
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(8.0f, 0.0f, 0.0f, 0.0f)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("GenerateMap", "Generate map"))
				.Font(F2DPalette::Font(true, 10))
				.ColorAndOpacity(FSlateColor::UseForeground())
			]
		];

	NewSeedButton = Framework2DProcGenPanelUtil::TextButton("F2D.Icon.Refresh", LOCTEXT("NewSeed", "New seed"),
		TAttribute<FText>::CreateLambda([this, M]()
		{
			const FText Problem = M->GetGenerateProblem();
			return Problem.IsEmpty()
				? LOCTEXT("NewSeedTip", "Changes the seed and generates another map with the same recipe (a single Ctrl+Z step).")
				: GetGenerateTip();
		}),
		FOnClicked::CreateLambda([M]()
		{
			M->GenerateMap(true);
			F2DPalette::RedrawViewports();
			return FReply::Handled();
		}),
		TAttribute<bool>::CreateLambda([this]() { return CanGenerate(); }), false);

	return F2DPalette::Card(
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			[
				GenerateButton.ToSharedRef()
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.Padding(6.0f, 0.0f, 0.0f, 0.0f)
			[
				NewSeedButton.ToSharedRef()
			]
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Left)
		.Padding(0.0f, 8.0f, 0.0f, 0.0f)
		[
			F2DPalette::ToggleChip("F2D.Icon.Refresh", LOCTEXT("AutoGenerate", "Regenerate on change"),
				LOCTEXT("AutoGenerateTip", "Regenerate on change: every change to the recipe or to the active biome's pieces generates the map again in the same Ctrl+Z step. Turn it off to adjust several things and generate at the end."),
				[M]() { return M->bAutoGenerate; },
				[M](bool bOn) { M->bAutoGenerate = bOn; })
		]
		// Qué se reemplaza (con los nombres de verdad de las capas y del mapa).
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 8.0f, 0.0f, 0.0f)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Top)
			.Padding(0.0f, 0.0f, 6.0f, 0.0f)
			[
				SNew(SImage)
				.Image(F2DPalette::Brush("F2D.Icon.Info"))
				.ColorAndOpacity(FFramework2DEditorStyle::ForegroundDim())
			]
			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			.VAlign(VAlign_Center)
			[
				F2DPalette::Caption(TAttribute<FText>::CreateLambda([M]() -> FText
				{
					const UFramework2DTileMapAsset* Map = M->GetTileMap();
					const FFramework2DProcGenSettings* S = M->GetProcGenSettings();
					if (!Map || !S) { return LOCTEXT("ReplaceNoMap", "Generating replaces the map's Terrain, Background, Behind, Edges, Decoration and Water layers. Ctrl+Z undoes it."); }
					return FText::Format(LOCTEXT("ReplaceLayersAll", "Replaces the {0}, {1}, {2}, {3}, {4} and {5} layers of «{6}». Ctrl+Z undoes it."),
						FText::FromName(S->TerrainLayer), FText::FromName(S->BackgroundLayer), FText::FromName(S->BehindLayer),
						FText::FromName(S->EdgeLayer), FText::FromName(S->DecorationLayer), FText::FromName(S->WaterLayer), FText::FromString(Map->GetName()));
				}))
			]
		]
		// Último resultado (o qué impide generar), con icono de aviso además del texto.
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0.0f, 6.0f, 0.0f, 0.0f)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Top)
			.Padding(0.0f, 0.0f, 6.0f, 0.0f)
			[
				SNew(SImage)
				.Image(F2DPalette::Brush("F2D.Icon.Info"))
				.ColorAndOpacity_Lambda([Kind]() -> FSlateColor
				{
					return Kind() == Framework2DProcGenPanelUtil::EReportKind::Problem ? FFramework2DEditorStyle::Danger() : FFramework2DEditorStyle::Accent();
				})
				.Visibility_Lambda([Kind]()
				{
					const Framework2DProcGenPanelUtil::EReportKind K = Kind();
					return (K == Framework2DProcGenPanelUtil::EReportKind::Problem || K == Framework2DProcGenPanelUtil::EReportKind::Warning) ? EVisibility::Visible : EVisibility::Collapsed;
				})
			]
			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.TextStyle(&F2DPalette::Text("F2D.Text.Body"))
				.AutoWrapText(true)
				.Text_Lambda([this]() { return GetReportText(); })
				.ColorAndOpacity_Lambda([Kind]() -> FSlateColor
				{
					return Kind() == Framework2DProcGenPanelUtil::EReportKind::None ? FFramework2DEditorStyle::ForegroundDim() : FFramework2DEditorStyle::Foreground();
				})
			]
		]);
}

#undef LOCTEXT_NAMESPACE
