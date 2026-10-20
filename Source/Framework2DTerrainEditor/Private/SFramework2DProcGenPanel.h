// Copyright Chema Luque. Plugin Framework2DTerrain (modulo Editor).

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Framework2DProcGenTypes.h"

class FFramework2DTilePaintMode;
class IMenu;
class SButton;
class SVerticalBox;
class SWidget;
class SWrapBox;

/** A qué se aplica lo que se elige en el selector de piezas. */
enum class EFramework2DPieceTargetKind : uint8
{
	Slot,           // una pieza suelta del bioma (Slot)
	Block3x3,       // las piezas de un bloque (3x3 de terreno o de fondo, o el 5x5 de terreno: BlockSize) con un bloque del atlas
	AddVariant,     // una variante del centro nueva
	Variant,        // la variante del centro número Index
	AddDecoration,  // un adorno nuevo
	Decoration      // el adorno número Index
};

/** Hueco del bioma activo que edita el selector de piezas. */
struct FFramework2DPieceTarget
{
	EFramework2DPieceTargetKind Kind = EFramework2DPieceTargetKind::Slot;
	EFramework2DBiomeSlot Slot = EFramework2DBiomeSlot::GroundCenter;
	bool bBackground = false;  // Block3x3: el 3x3 del fondo en vez del de terreno
	int32 BlockSize = 3;       // Block3x3: 3 (3x3) o 5 (el 5x5 del terreno)
	int32 Index = INDEX_NONE;  // Variant y Decoration

	static FFramework2DPieceTarget ForSlot(EFramework2DBiomeSlot InSlot)
	{
		FFramework2DPieceTarget T;
		T.Kind = EFramework2DPieceTargetKind::Slot;
		T.Slot = InSlot;
		return T;
	}
	static FFramework2DPieceTarget ForBlock(bool bInBackground)
	{
		FFramework2DPieceTarget T;
		T.Kind = EFramework2DPieceTargetKind::Block3x3;
		T.bBackground = bInBackground;
		return T;
	}
	static FFramework2DPieceTarget ForBlock5()
	{
		FFramework2DPieceTarget T;
		T.Kind = EFramework2DPieceTargetKind::Block3x3;
		T.BlockSize = 5;
		return T;
	}
	static FFramework2DPieceTarget ForList(EFramework2DPieceTargetKind InKind, int32 InIndex = INDEX_NONE)
	{
		FFramework2DPieceTarget T;
		T.Kind = InKind;
		T.Index = InIndex;
		return T;
	}
	bool IsBlock() const { return Kind == EFramework2DPieceTargetKind::Block3x3; }
	bool IsAdd() const { return Kind == EFramework2DPieceTargetKind::AddVariant || Kind == EFramework2DPieceTargetKind::AddDecoration; }
};

/**
 * SFramework2DProcGenPanel
 * =================================================================
 * Pestaña «Generar» del panel del modo Framework2D Tiles: generación procedural del mapa.
 *   1. Bioma: lista de biomas del Tile Set (clic = el que usa la receta del mapa).
 *   2. Piezas del bioma activo: huecos (terreno 3×3, esquinas, variantes, rampas, plataformas,
 *      fondo, agua, cascada y decoración). Cada hueco abre el SELECTOR (atlas, flipbooks y
 *      generadores) en un menú emergente.
 *   3. Receta: tamaño del mapa, alturas, rampas, agua, plataformas, decoración, fondo y semilla.
 *   4. Generar: botón principal, otra semilla, «Regenerar al cambiar» y el último resultado.
 * Cada cambio es un paso de Ctrl+Z (lo abre el modo). Exportada para las pruebas automáticas.
 */
class FRAMEWORK2DTERRAINEDITOR_API SFramework2DProcGenPanel : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SFramework2DProcGenPanel) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, FFramework2DTilePaintMode* InMode);
	virtual ~SFramework2DProcGenPanel();
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	//~ Selector de piezas (lo usan los huecos; también para las pruebas automáticas)

	/** Abre el selector de ese hueco, anclado a su widget del panel. False si el hueco no está a la vista o no hay bioma. */
	bool OpenPicker(const FFramework2DPieceTarget& Target);
	bool OpenSlotPicker(EFramework2DBiomeSlot Slot) { return OpenPicker(FFramework2DPieceTarget::ForSlot(Slot)); }
	bool IsPickerOpen() const;
	FFramework2DPieceTarget GetPickerTarget() const { return PickerTarget; }
	void ClosePicker();
	/** Lo mismo que elegir Value en el selector (y lo cierra si estaba abierto). False si no hay bioma activo. */
	bool PickValue(const FFramework2DPieceTarget& Target, int32 Value);
	/** Rellena el 3x3 de ese hueco (Block3x3) con el bloque de 3x3 tiles cuya esquina de arriba-izquierda es ese tile. */
	bool PickBlock(const FFramework2DPieceTarget& Target, int32 TopLeftTileValue);
	/** Rellena el 3x3 (de terreno o de fondo) con la selección del atlas de la pestaña «Pintar» (si es de 3x3). */
	bool UseSelectionAs3x3(bool bBackground);
	/** Rellena el 5x5 del terreno con la selección del atlas de la pestaña «Pintar» (si es de 5x5). */
	bool UseSelectionAs5x5();
	/** Lo mismo que «Vaciar» (en una lista, quitar el elemento). */
	bool ClearTarget(const FFramework2DPieceTarget& Target);
	/** Valor que tiene ahora ese hueco en el bioma activo (-1 si vacío o no aplica). */
	int32 GetTargetValue(const FFramework2DPieceTarget& Target) const;
	/** Contenido del selector sin abrir el menú (para capturas con FWidgetRenderer). */
	TSharedRef<SWidget> MakePickerContent(const FFramework2DPieceTarget& Target);

	FFramework2DTilePaintMode* GetMode() const { return Mode; }

	//~ Pruebas automáticas
	TSharedPtr<SButton> GetGenerateButton() const { return GenerateButton; }
	TSharedPtr<SButton> GetNewSeedButton() const { return NewSeedButton; }
	/** Widget del hueco de una pieza suelta (nullptr si aún no se ha construido). */
	TSharedPtr<SWidget> GetSlotWidget(EFramework2DBiomeSlot Slot) const;
	/** Texto de la línea de resultado del pie (lo que ve el usuario tras generar). */
	FText GetReportText() const;

private:
	FFramework2DTilePaintMode* Mode = nullptr;

	// Listas que se rehacen solo cuando cambia su forma.
	TSharedPtr<SVerticalBox> BiomesBox;
	TSharedPtr<SWrapBox> VariantsBox;
	TSharedPtr<SVerticalBox> DecorationsBox;
	uint32 LastBiomesSignature = 0;
	uint32 LastPiecesSignature = 0;
	uint32 ComputeBiomesSignature() const;
	uint32 ComputePiecesSignature() const;
	void RebuildBiomes();
	void RebuildVariants();
	void RebuildDecorations();

	// Paisaje (v2.4): fondos parallax y objetos grandes del bioma activo (SFramework2DProcGenScenery.cpp).
	TSharedPtr<SVerticalBox> BackdropsBox;
	TSharedPtr<SVerticalBox> PropsBox;
	TSharedRef<SWidget> MakeSceneryCard();
	TSharedRef<SWidget> MakeBackdropRow(int32 Index);
	TSharedRef<SWidget> MakePropRow(int32 Index);
	void RebuildBackdrops();
	void RebuildProps();

	// Botones y huecos que se buscan desde fuera (pruebas) o para anclar el selector.
	TSharedPtr<SButton> GenerateButton;
	TSharedPtr<SButton> NewSeedButton;
	TMap<int32, TWeakPtr<SWidget>> SlotWidgets;   // por (int32)EFramework2DBiomeSlot
	TWeakPtr<SWidget> BlockAnchors[3];            // «Elegir bloque…» del 3x3 de terreno [0], de fondo [1] y del 5x5 [2]
	TWeakPtr<SWidget> AddVariantAnchor;
	TWeakPtr<SWidget> AddDecorationAnchor;
	TArray<TWeakPtr<SWidget>> VariantAnchors;
	TArray<TWeakPtr<SWidget>> DecorationAnchors;

	// Selector abierto.
	TWeakPtr<IMenu> PickerMenu;
	TWeakPtr<SWidget> PickerAnchor;
	FFramework2DPieceTarget PickerTarget;
	int32 PickerBiomeId = INDEX_NONE;
	bool bPickerFromKeyboard = false;

	// Tarjetas.
	TSharedRef<SWidget> MakeBiomeCard();
	TSharedRef<SWidget> MakeBiomeRow(int32 BiomeId);
	TSharedRef<SWidget> MakeEmptyBiomes();
	TSharedRef<SWidget> MakePiecesCard();
	TSharedRef<SWidget> MakeRecipeCard();
	TSharedRef<SWidget> MakeGenerateCard();

	// Piezas.
	TSharedRef<SWidget> MakeSection(const FText& Title, const FText& Help, const TSharedRef<SWidget>& Content);
	TSharedRef<SWidget> MakePieceSlot(const FFramework2DPieceTarget& Target, const FText& Label, float Size, bool bRequired);
	TSharedRef<SWidget> MakeSlotRow(const TArray<EFramework2DBiomeSlot>& Slots);
	TSharedRef<SWidget> Make3x3(bool bBackground);
	TSharedRef<SWidget> Make5x5();
	TSharedRef<SWidget> MakeInnerCorners();
	TSharedRef<SWidget> MakeDecorationRow(int32 Index);
	TWeakPtr<SWidget> FindAnchor(const FFramework2DPieceTarget& Target) const;
	bool OpenPickerAt(const FFramework2DPieceTarget& Target, const TSharedRef<SWidget>& Anchor, bool bFromKeyboard);
	void OnPickerDismissed();
	bool bRestoreFocusOnDismiss = false; // solo al cerrar desde el propio selector (elegir, Esc), no al hacer clic fuera

	// Receta.
	TSharedRef<SWidget> MakeRecipeGroup(const FText& Title);
	TSharedRef<SWidget> MakeRecipeRow(const FText& Label, const FText& Tip, const TSharedRef<SWidget>& Value);
	TSharedRef<SWidget> MakeRecipeSpin(const FText& Label, const FText& Tip, float Min, float Max, float Delta, int32 Digits,
		TFunction<float(const FFramework2DProcGenSettings&)> Get, TFunction<void(FFramework2DProcGenSettings&, float)> Set, bool bSlider = true);
	TSharedRef<SWidget> MakePercentSpin(const FText& Label, const FText& Tip,
		TFunction<float(const FFramework2DProcGenSettings&)> Get, TFunction<void(FFramework2DProcGenSettings&, float)> Set);
	TSharedRef<SWidget> MakeMapSizeSpin(const FText& Label, const FText& Tip, bool bHeight);
	TSharedRef<SWidget> MakeLayerNameRow(const FText& Label, const FText& Tip, int32 Which);
	void ChangeRecipe(const FText& Description, TFunctionRef<void(FFramework2DProcGenSettings&)> Change);

	// Pie.
	FText GetGenerateTip() const;
	bool CanGenerate() const;
};
