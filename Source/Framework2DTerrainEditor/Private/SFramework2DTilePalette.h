// Copyright Chema Luque. Plugin Framework2DTerrain (modulo Editor).

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Input/SComboBox.h"
#include "Framework2DTerrainTypes.h"

class FFramework2DTilePaintMode;
class SVerticalBox;
class SHorizontalBox;
class SWrapBox;
struct FFramework2DGenerator;
class SButton;
struct FButtonStyle;
enum class EFramework2DTileTool : uint8;
class SFramework2DProcGenPanel;

/** Pestañas del panel (control segmentado bajo la tarjeta de estado). */
enum class EFramework2DPaletteTab : uint8
{
	Paint,    // «Pintar»: herramientas, capas, colisión, atlas, flipbooks y generadores
	Generate  // «Generar»: generación procedural del mapa (biomas, piezas y receta)
};

/**
 * Panel del modo "Framework2D Tiles": herramientas, capas, colision, el ATLAS completo para
 * seleccionar (clic = un tile, arrastrar = un bloque), propiedades de los tiles elegidos y la
 * lista de flipbooks. En la pestaña «Generar», el panel de generación procedural.
 */
class SFramework2DTilePalette : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SFramework2DTilePalette) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, FFramework2DTilePaintMode* InMode);
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	//~ Pestañas (también para las pruebas automáticas: inline, no hace falta exportar la clase)
	EFramework2DPaletteTab GetActiveTab() const { return ActiveTab; }
	void SetActiveTab(EFramework2DPaletteTab InTab) { ActiveTab = InTab; }
	/** Panel de la pestaña «Generar». Siempre existe; solo se ve (y se actualiza) en esa pestaña. */
	TSharedPtr<SFramework2DProcGenPanel> GetProcGenPanel() const { return ProcGenPanel; }

private:
	FFramework2DTilePaintMode* Mode = nullptr;
	EFramework2DPaletteTab ActiveTab = EFramework2DPaletteTab::Paint; // siempre empieza en «Pintar»
	TSharedPtr<SFramework2DProcGenPanel> ProcGenPanel;
	TSharedPtr<SVerticalBox> LayersBox;
	TSharedPtr<SVerticalBox> FlipbooksBox;
	int32 Zoom = 0; // pixeles de pantalla por pixel del atlas (0 = automatico)
	uint32 LastLayersSignature = 0;
	uint32 LastFlipbooksSignature = 0;

	uint32 ComputeLayersSignature() const;
	uint32 ComputeFlipbooksSignature() const;
	uint32 ComputePagesSignature() const;
	uint32 ComputeGeneratorsSignature() const;
	void RebuildLayers();
	void RebuildFlipbooks();
	void RebuildPageTabs();
	void RebuildGenerators();

	// Paginas del atlas (pestanas) y generadores de vegetacion.
	TSharedPtr<SHorizontalBox> PageTabsBox;
	TSharedPtr<SVerticalBox> GeneratorsBox;
	TSharedPtr<SWrapBox> GeneratorSpritesBox;
	uint32 LastPagesSignature = 0;
	uint32 LastGeneratorsSignature = 0;
	int32 EditedGeneratorId = INDEX_NONE; // el que se ajusta abajo (sigue aunque el pincel cambie)

	TSharedRef<SWidget> MakePageControls();
	TSharedRef<SWidget> MakeGeneratorsCard();
	TSharedRef<SWidget> MakeGeneratorRow(int32 GeneratorId);
	TSharedRef<SWidget> MakeGeneratorEditor();
	TSharedRef<SWidget> MakeGeneratorSpin(const FText& Label, const FText& Tip, float Min, float Max, float Delta, int32 Digits,
		TFunction<float(const FFramework2DGenerator&)> Get, TFunction<void(FFramework2DGenerator&, float)> Set);
	TSharedRef<SWidget> MakeGeneratorColor(const FText& Label, const FText& Tip, bool bTintB);
	const FFramework2DGenerator* GetEditedGenerator() const;
	TSharedRef<SWidget> MakeToolButton(EFramework2DTileTool InTool);
	FText GetStatusText() const;
	FText GetSelectionText() const;
	int32 GetEffectiveZoom() const;

	/** Boton cuyo estilo cambia con el estado (herramienta activa, forma de colision activa). */
	struct FStatefulButton
	{
		TWeakPtr<SButton> Button;
		TFunction<bool()> IsActive;
		const FButtonStyle* NormalStyle = nullptr;
		const FButtonStyle* ActiveStyle = nullptr;
		bool bActive = false;
	};
	TArray<FStatefulButton> StatefulButtons;

	// Desplegables de propiedades de la seleccion (material y colision).
	TSharedPtr<SComboBox<TSharedPtr<FName>>> MaterialCombo;
	TSharedPtr<SComboBox<TSharedPtr<EFramework2DCollisionShape>>> CollisionCombo;
	TArray<TSharedPtr<FName>> MaterialOptions;
	TArray<TSharedPtr<EFramework2DCollisionShape>> ShapeOptions;
	bool bSyncingCombos = false; // true mientras el panel marca el valor actual (no es una eleccion)

	// Arrastre del valor "Separacion entre capas": se aplica en vivo y se guarda al soltar.
	bool bSeparationDragging = false;
	float SeparationAtDragStart = 0.0f;

	TSharedRef<SWidget> MakeStatusCard();
	TSharedRef<SWidget> MakeTabsBar();
	TSharedRef<SWidget> MakeTabButton(EFramework2DPaletteTab Tab);
	TSharedRef<SWidget> MakeToolsCard();
	TSharedRef<SWidget> MakeLayersCard();
	TSharedRef<SWidget> MakeCollisionCard();
	TSharedRef<SWidget> MakeAtlasCard();
	TSharedRef<SWidget> MakeSelectionProperties();
	TSharedRef<SWidget> MakeFlipbooksCard();
	TSharedRef<SWidget> MakeShapeButton(EFramework2DCollisionShape Shape);
	TSharedRef<SWidget> MakeLayerRow(int32 Layer);
	TSharedRef<SWidget> MakeFlipbookRow(int32 FlipbookId);

	void RegisterStatefulButton(const TSharedRef<SButton>& Button, TFunction<bool()> IsActive, const FButtonStyle* NormalStyle, const FButtonStyle* ActiveStyle);
	void UpdateStatefulButtons();
	void RefreshMaterialOptions();
	void SyncComboSelections();
	bool IsReady() const;
	void SetZoom(int32 NewZoom);
	void ApplySeparation(float Value, bool bFinal);
};
