// Copyright Chema Luque. Plugin Framework2DTerrain (modulo Editor).
//
// Pestaña «Generar», tarjeta «Paisaje» (v2.4): los fondos parallax y los objetos grandes del
// bioma activo. Es parte de SFramework2DProcGenPanel (archivo aparte para no alargar el otro).

#include "SFramework2DProcGenPanel.h"

#include "Framework2DEditorStyle.h"
#include "Framework2DPaletteWidgets.h"
#include "Framework2DTileSet.h"
#include "Framework2DTilePaintMode.h"

#include "AssetRegistry/AssetData.h"
#include "Engine/Texture2D.h"
#include "PropertyCustomizationHelpers.h"
#include "ThumbnailRendering/ThumbnailManager.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SSpinBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SWrapBox.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "SFramework2DProcGenScenery"

namespace Framework2DProcGenScenery
{
	/** Cambia el bioma activo con un paso de deshacer (el modo no crea pasos vacíos). */
	void ChangeActive(FFramework2DTilePaintMode* M, const FText& Description, TFunctionRef<void(FFramework2DBiome&)> Change)
	{
		const int32 BiomeId = M->GetActiveBiomeId();
		if (BiomeId == INDEX_NONE) { return; }
		M->ChangeBiome(BiomeId, Description, Change);
		F2DPalette::RedrawViewports();
	}

	/** Valor pequeño con etiqueta: en vivo al arrastrar, se guarda al soltar o al escribirlo. */
	TSharedRef<SWidget> SmallSpin(const FText& Label, const FText& Tip, float Min, float Max, float Delta, int32 Digits,
		TFunction<float()> Get, TFunction<void(float)> Commit)
	{
		const TSharedRef<F2DPalette::FSpinDrag> Drag = MakeShared<F2DPalette::FSpinDrag>();
		return SNew(SHorizontalBox)
			.ToolTipText(Tip)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(0.0f, 0.0f, 4.0f, 0.0f)
			[
				SNew(STextBlock)
				.TextStyle(&F2DPalette::Text("F2D.Text.Caption"))
				.Text(Label)
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			[
				SNew(SBox)
				.WidthOverride(58.0f)
				[
					SNew(SSpinBox<float>)
					.MinValue(Min)
					.MaxValue(Max)
					.MinSliderValue(Min)
					.MaxSliderValue(Max)
					.Delta(Delta)
					.MinFractionalDigits(0)
					.MaxFractionalDigits(Digits)
					.ToolTipText(Tip)
					.Value_Lambda([Get, Drag]() { return Drag->bDragging ? Drag->Value : Get(); })
					.OnBeginSliderMovement_Lambda([Get, Drag]() { Drag->bDragging = true; Drag->Value = Get(); })
					.OnValueChanged_Lambda([Drag](float NewValue) { if (Drag->bDragging) { Drag->Value = NewValue; } })
					.OnEndSliderMovement_Lambda([Drag, Commit](float NewValue) { Drag->bDragging = false; Commit(NewValue); })
					.OnValueCommitted_Lambda([Drag, Commit](float NewValue, ETextCommit::Type) { if (!Drag->bDragging) { Commit(NewValue); } })
				]
			];
	}

	/** Botón de texto secundario con icono (añadir). */
	TSharedRef<SWidget> AddButton(const FText& Label, const FText& Tip, TFunction<void()> OnClick, TAttribute<bool> Enabled)
	{
		return SNew(SButton)
			.ButtonStyle(&F2DPalette::Button("F2D.Button.Secondary"))
			.ContentPadding(FMargin(8.0f, 4.0f))
			.ToolTipText(Tip)
			.IsEnabled(Enabled)
			.OnClicked_Lambda([OnClick]() { OnClick(); return FReply::Handled(); })
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
					.Font(F2DPalette::Font(false, 8))
					.ColorAndOpacity(FSlateColor::UseForeground())
					.Text(Label)
				]
			];
	}

	/** Caja de imagen (asset de textura) con su miniatura. */
	TSharedRef<SWidget> TextureBox(const FText& Tip, TFunction<UTexture2D*()> Get, TFunction<void(UTexture2D*)> Set)
	{
		return SNew(SObjectPropertyEntryBox)
			.AllowedClass(UTexture2D::StaticClass())
			.DisplayThumbnail(true)
			.ThumbnailPool(UThumbnailManager::Get().GetSharedThumbnailPool())
			.ToolTipText(Tip)
			.ObjectPath_Lambda([Get]() -> FString
			{
				const UTexture2D* Texture = Get();
				return Texture ? Texture->GetPathName() : FString();
			})
			.OnObjectChanged_Lambda([Set](const FAssetData& Asset)
			{
				Set(Cast<UTexture2D>(Asset.GetAsset()));
			});
	}

	/** Miniatura de un trozo del atlas: (tile, ancho, alto) de lo que se dibuja ahora. */
	TSharedRef<SWidget> Thumb(FFramework2DTilePaintMode* M, float Size, TFunction<FIntVector()> Source)
	{
		return SNew(SFramework2DTileThumb, M, MoveTemp(Source)).Size(Size);
	}

	/** El objeto grande de una entrada del bioma si es un trozo del atlas (sin imagen suelta). */
	const FFramework2DPropDef* AtlasPropOf(FFramework2DTilePaintMode* M, const FFramework2DBiomeProp* Entry)
	{
		const UFramework2DTileSet* Set = M->GetTileSet();
		const FFramework2DPropDef* Def = (Entry && Set) ? Set->FindPropById(Entry->PropId) : nullptr;
		return (Def && !Def->Texture && Def->AtlasTile >= 0) ? Def : nullptr;
	}

	/** Mensaje de lista vacía. */
	TSharedRef<SWidget> EmptyRow(const FText& Text)
	{
		return SNew(SBorder)
			.BorderImage(F2DPalette::Brush("F2D.Row"))
			.Padding(FMargin(10.0f, 8.0f))
			[
				F2DPalette::Caption(Text)
			];
	}
}

// ---------------------------------------------------------------------
//  Tarjeta
// ---------------------------------------------------------------------
TSharedRef<SWidget> SFramework2DProcGenPanel::MakeSceneryCard()
{
	using namespace Framework2DProcGenScenery;
	FFramework2DTilePaintMode* M = Mode;
	BackdropsBox = SNew(SVerticalBox);
	PropsBox = SNew(SVerticalBox);
	const TAttribute<bool> HasBiome = TAttribute<bool>::CreateLambda([M]() { return M->GetActiveBiome() != nullptr; });

	return SNew(SBox)
		.Visibility_Lambda([M]() { return M->GetActiveBiome() ? EVisibility::Visible : EVisibility::Collapsed; })
		[
			F2DPalette::Card(
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					F2DPalette::CardHeader("F2D.Icon.Biome", LOCTEXT("SceneryTitle", "Scenery"))
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(0.0f, 2.0f, 0.0f, 0.0f)
				[
					F2DPalette::Caption(LOCTEXT("SceneryHelp", "Loose images from your project: backgrounds that move with the camera (parallax) and large objects the generator scatters on the ground."))
				]
				// Fondos parallax.
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(0.0f, 10.0f, 0.0f, 2.0f)
				[
					SNew(STextBlock)
					.TextStyle(&F2DPalette::Text("F2D.Text.Body"))
					.Text(LOCTEXT("BackdropsSection", "Parallax backgrounds"))
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(0.0f, 0.0f, 0.0f, 6.0f)
				[
					F2DPalette::Caption(LOCTEXT("BackdropsHelp", "From back (top of the list) to front. Parallax 0 % = still on screen (sky); 100 % = moves with the level. Visible right away in the viewport."))
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					BackdropsBox.ToSharedRef()
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Left)
				.Padding(0.0f, 6.0f, 0.0f, 0.0f)
				[
					AddButton(LOCTEXT("AddBackdrop", "Add background"),
						LOCTEXT("AddBackdropTip", "Adds a background layer in front of the existing ones. Then choose its image (sky, mountains, distant forest...)."),
						[M]()
						{
							ChangeActive(M, LOCTEXT("AddBackdropStep", "Add parallax background"), [](FFramework2DBiome& Biome)
							{
								FFramework2DBackdropLayer Layer;
								Layer.Name = FName(*FString::Printf(TEXT("Background %d"), Biome.Backdrops.Num() + 1));
								// Cuanto más delante, más se mueve (el primero hace de cielo).
								Layer.Parallax = Biome.Backdrops.Num() == 0 ? 0.0f : FMath::Min(0.9f, 0.2f * (float)Biome.Backdrops.Num());
								Layer.VerticalParallax = Layer.Parallax * 0.5f;
								Layer.bFillAbove = Biome.Backdrops.Num() == 0;
								Biome.Backdrops.Add(Layer);
							});
						}, HasBiome)
				]
				// Objetos grandes.
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(0.0f, 14.0f, 0.0f, 2.0f)
				[
					SNew(STextBlock)
					.TextStyle(&F2DPalette::Text("F2D.Text.Body"))
					.Text(LOCTEXT("PropsSection", "Large objects"))
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(0.0f, 0.0f, 0.0f, 6.0f)
				[
					F2DPalette::Caption(LOCTEXT("PropsHelp", "Trees, rocks, giant mushrooms, rune stones... of any size. They appear where there is flat ground for their width; «Behind» neither collides nor breaks. How many appear: Recipe › Large objects."))
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					PropsBox.ToSharedRef()
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(HAlign_Left)
				.Padding(0.0f, 6.0f, 0.0f, 0.0f)
				[
					AddButton(LOCTEXT("AddProp", "Add object"),
						LOCTEXT("AddPropTip", "Adds a large object to the biome. Then choose its image (a PNG with transparency)."),
						[M]()
						{
							ChangeActive(M, LOCTEXT("AddPropStep", "Add large object"), [](FFramework2DBiome& Biome)
							{
								Biome.Props.AddDefaulted();
							});
						}, HasBiome)
				])
		];
}

void SFramework2DProcGenPanel::RebuildBackdrops()
{
	if (!BackdropsBox.IsValid()) { return; }
	BackdropsBox->ClearChildren();
	const FFramework2DBiome* Biome = Mode->GetActiveBiome();
	if (!Biome || Biome->Backdrops.Num() == 0)
	{
		BackdropsBox->AddSlot().AutoHeight()
		[
			Framework2DProcGenScenery::EmptyRow(LOCTEXT("NoBackdrops", "No backgrounds: the sky is the scene's background color. «Add background» to add sky, mountains or a distant forest."))
		];
		return;
	}
	for (int32 I = 0; I < Biome->Backdrops.Num(); ++I)
	{
		BackdropsBox->AddSlot().AutoHeight().Padding(0.0f, 0.0f, 0.0f, 4.0f)[ MakeBackdropRow(I) ];
	}
}

void SFramework2DProcGenPanel::RebuildProps()
{
	if (!PropsBox.IsValid()) { return; }
	PropsBox->ClearChildren();
	const FFramework2DBiome* Biome = Mode->GetActiveBiome();
	if (!Biome || Biome->Props.Num() == 0)
	{
		PropsBox->AddSlot().AutoHeight()
		[
			Framework2DProcGenScenery::EmptyRow(LOCTEXT("NoProps", "No large objects. «Add object» to add trees, rocks..."))
		];
		return;
	}
	for (int32 I = 0; I < Biome->Props.Num(); ++I)
	{
		PropsBox->AddSlot().AutoHeight().Padding(0.0f, 0.0f, 0.0f, 4.0f)[ MakePropRow(I) ];
	}
}

// ---------------------------------------------------------------------
//  Fila de fondo parallax
// ---------------------------------------------------------------------
TSharedRef<SWidget> SFramework2DProcGenPanel::MakeBackdropRow(int32 Index)
{
	using namespace Framework2DProcGenScenery;
	FFramework2DTilePaintMode* M = Mode;
	auto Find = [M, Index]() -> const FFramework2DBackdropLayer*
	{
		const FFramework2DBiome* Biome = M->GetActiveBiome();
		return (Biome && Biome->Backdrops.IsValidIndex(Index)) ? &Biome->Backdrops[Index] : nullptr;
	};
	auto Change = [M, Index](const FText& Description, TFunction<void(FFramework2DBackdropLayer&)> Edit)
	{
		ChangeActive(M, Description, [Index, &Edit](FFramework2DBiome& Biome)
		{
			if (Biome.Backdrops.IsValidIndex(Index)) { Edit(Biome.Backdrops[Index]); }
		});
	};
	auto Move = [M, Index](int32 Delta)
	{
		ChangeActive(M, LOCTEXT("MoveBackdrop", "Move parallax background"), [Index, Delta](FFramework2DBiome& Biome)
		{
			const int32 To = Index + Delta;
			if (Biome.Backdrops.IsValidIndex(Index) && Biome.Backdrops.IsValidIndex(To)) { Biome.Backdrops.Swap(Index, To); }
		});
	};
	auto Chip = [Find, Change](FName Icon, const FText& Label, const FText& Tip, bool FFramework2DBackdropLayer::* Member)
	{
		return F2DPalette::ToggleChip(Icon, Label, Tip,
			[Find, Member]() { const FFramework2DBackdropLayer* Layer = Find(); return Layer && Layer->*Member; },
			[Change, Member, Label](bool bOn) { Change(FText::Format(LOCTEXT("BackdropToggle", "Background: {0}"), Label), [Member, bOn](FFramework2DBackdropLayer& Layer) { Layer.*Member = bOn; }); });
	};
	const int32 Count = Mode->GetActiveBiome() ? Mode->GetActiveBiome()->Backdrops.Num() : 0;

	return SNew(SBorder)
		.BorderImage(F2DPalette::Brush("F2D.Row"))
		.Padding(FMargin(6.0f))
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.FillWidth(1.0f)
				.VAlign(VAlign_Center)
				[
					TextureBox(LOCTEXT("BackdropImageTip", "Image of this background layer. For pixel art: Filter Nearest and no mipmaps (right click › Sprite Actions › Apply Paper2D Texture Settings)."),
						[Find]() -> UTexture2D* { const FFramework2DBackdropLayer* Layer = Find(); return Layer ? Layer->Texture.Get() : nullptr; },
						[Change](UTexture2D* Texture) { Change(LOCTEXT("BackdropImage", "Background image"), [Texture](FFramework2DBackdropLayer& Layer) { Layer.Texture = Texture; }); })
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(4.0f, 0.0f, 0.0f, 0.0f)
				[
					F2DPalette::IconButton("F2D.Icon.Up", LOCTEXT("BackdropBackTip", "Further back (up the list)."),
						FOnClicked::CreateLambda([Move]() { Move(-1); return FReply::Handled(); }), TAttribute<bool>(Index > 0))
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(2.0f, 0.0f, 0.0f, 0.0f)
				[
					F2DPalette::IconButton("F2D.Icon.Down", LOCTEXT("BackdropFrontTip", "Further forward (down the list)."),
						FOnClicked::CreateLambda([Move]() { Move(+1); return FReply::Handled(); }), TAttribute<bool>(Index < Count - 1))
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(2.0f, 0.0f, 0.0f, 0.0f)
				[
					F2DPalette::IconButton("F2D.Icon.Trash", LOCTEXT("RemoveBackdropTip", "Remove this background layer (Ctrl+Z brings it back)."),
						FOnClicked::CreateLambda([M, Index]()
						{
							ChangeActive(M, LOCTEXT("RemoveBackdrop", "Remove parallax background"), [Index](FFramework2DBiome& Biome)
							{
								if (Biome.Backdrops.IsValidIndex(Index)) { Biome.Backdrops.RemoveAt(Index); }
							});
							return FReply::Handled();
						}),
						TAttribute<bool>(true), &F2DPalette::DangerIconButtonStyle())
				]
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 6.0f, 0.0f, 0.0f)
			[
				SNew(SWrapBox)
				.UseAllottedSize(true)
				.InnerSlotPadding(FVector2D(10.0f, 4.0f))
				+ SWrapBox::Slot()
				[
					SmallSpin(LOCTEXT("BackdropParallax", "Parallax %"),
						LOCTEXT("BackdropParallaxTip", "How much it moves with the level when the camera moves: 0 % = still on screen (sky), 100 % = like the terrain. Distant layers a little; close ones more."),
						0.0f, 100.0f, 1.0f, 0,
						[Find]() { const FFramework2DBackdropLayer* Layer = Find(); return Layer ? FMath::RoundToFloat(Layer->Parallax * 100.0f) : 0.0f; },
						[Change](float V)
						{
							Change(LOCTEXT("BackdropParallaxStep", "Background parallax"), [V](FFramework2DBackdropLayer& Layer)
							{
								Layer.Parallax = FMath::Clamp(V, 0.0f, 100.0f) / 100.0f;
								Layer.VerticalParallax = Layer.Parallax * 0.5f;
							});
						})
				]
				+ SWrapBox::Slot()
				[
					SmallSpin(LOCTEXT("BackdropHeight", "Height"),
						LOCTEXT("BackdropHeightTip", "Height (tiles) of the image's bottom edge above the bottom of the level."),
						-256.0f, 1024.0f, 0.5f, 1,
						[Find]() { const FFramework2DBackdropLayer* Layer = Find(); return Layer ? Layer->Height : 0.0f; },
						[Change](float V) { Change(LOCTEXT("BackdropHeightStep", "Background height"), [V](FFramework2DBackdropLayer& Layer) { Layer.Height = V; }); })
				]
				+ SWrapBox::Slot()
				[
					SmallSpin(LOCTEXT("BackdropScale", "Scale"),
						LOCTEXT("BackdropScaleTip", "Size: terrain pixels per image pixel (1 = same pixel size as the level; 2 = double)."),
						0.1f, 32.0f, 0.1f, 2,
						[Find]() { const FFramework2DBackdropLayer* Layer = Find(); return Layer ? Layer->Scale : 1.0f; },
						[Change](float V) { Change(LOCTEXT("BackdropScaleStep", "Background scale"), [V](FFramework2DBackdropLayer& Layer) { Layer.Scale = FMath::Clamp(V, 0.1f, 32.0f); }); })
				]
				+ SWrapBox::Slot()
				[
					Chip("F2D.Icon.Replace", LOCTEXT("BackdropRepeat", "Repeat"),
						LOCTEXT("BackdropRepeatTip", "Repeat the image horizontally, endlessly (the image must tile on its sides)."), &FFramework2DBackdropLayer::bRepeat)
				]
				+ SWrapBox::Slot()
				[
					Chip("F2D.Icon.Down", LOCTEXT("BackdropFillBelow", "Fill below"),
						LOCTEXT("BackdropFillBelowTip", "Stretches the image's bottom row downwards: no gaps under the layer."), &FFramework2DBackdropLayer::bFillBelow)
				]
				+ SWrapBox::Slot()
				[
					Chip("F2D.Icon.Up", LOCTEXT("BackdropFillAbove", "Fill above"),
						LOCTEXT("BackdropFillAboveTip", "Stretches the top row upwards (for the sky: so it never ends)."), &FFramework2DBackdropLayer::bFillAbove)
				]
			]
		];
}

// ---------------------------------------------------------------------
//  Fila de objeto grande
// ---------------------------------------------------------------------
TSharedRef<SWidget> SFramework2DProcGenPanel::MakePropRow(int32 Index)
{
	using namespace Framework2DProcGenScenery;
	FFramework2DTilePaintMode* M = Mode;
	auto Find = [M, Index]() -> const FFramework2DBiomeProp*
	{
		const FFramework2DBiome* Biome = M->GetActiveBiome();
		return (Biome && Biome->Props.IsValidIndex(Index)) ? &Biome->Props[Index] : nullptr;
	};
	auto Change = [M, Index](const FText& Description, TFunction<void(FFramework2DBiomeProp&)> Edit)
	{
		ChangeActive(M, Description, [Index, &Edit](FFramework2DBiome& Biome)
		{
			if (Biome.Props.IsValidIndex(Index)) { Edit(Biome.Props[Index]); }
		});
	};
	auto IsFront = [Find]() { const FFramework2DBiomeProp* Prop = Find(); return Prop && Prop->Depth == EFramework2DPropDepth::Front; };

	return SNew(SBorder)
		.BorderImage(F2DPalette::Brush("F2D.Row"))
		.Padding(FMargin(6.0f))
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				[
					SNew(SBox)
					.Visibility_Lambda([M, Find]() { return AtlasPropOf(M, Find()) ? EVisibility::Visible : EVisibility::Collapsed; })
					[
						Thumb(M, 40.0f, [M, Find]()
						{
							const FFramework2DPropDef* Def = AtlasPropOf(M, Find());
							return Def ? FIntVector(Def->AtlasTile, Def->AtlasWidthTiles, Def->AtlasHeightTiles) : FIntVector(-1, 1, 1);
						})
					]
				]
				+ SHorizontalBox::Slot()
				.FillWidth(1.0f)
				.VAlign(VAlign_Center)
				.Padding(8.0f, 0.0f, 0.0f, 0.0f)
				[
					SNew(SBox)
					.Visibility_Lambda([M, Find]() { return AtlasPropOf(M, Find()) ? EVisibility::Visible : EVisibility::Collapsed; })
					[
						SNew(STextBlock)
						.TextStyle(&F2DPalette::Text("F2D.Text.Caption"))
						.Text_Lambda([M, Find]()
						{
							const FFramework2DPropDef* Def = AtlasPropOf(M, Find());
							return Def ? FText::Format(LOCTEXT("AtlasPropText", "{0} (atlas region)"), FText::FromName(Def->Name)) : FText::GetEmpty();
						})
					]
				]
				+ SHorizontalBox::Slot()
				.FillWidth(1.0f)
				.VAlign(VAlign_Center)
				[
					SNew(SBox)
					.Visibility_Lambda([M, Find]() { return AtlasPropOf(M, Find()) ? EVisibility::Collapsed : EVisibility::Visible; })
					[
					TextureBox(LOCTEXT("PropImageTip", "Object image (PNG with transparency; 1 image pixel = 1 terrain pixel). Its foot is the bottom row with drawing."),
						[M, Find]() -> UTexture2D*
						{
							const FFramework2DBiomeProp* Prop = Find();
							const UFramework2DTileSet* Set = M->GetTileSet();
							const FFramework2DPropDef* Def = (Prop && Set) ? Set->FindPropById(Prop->PropId) : nullptr;
							return Def ? Def->Texture.Get() : nullptr;
						},
						[M, Index](UTexture2D* Texture)
						{
							const int32 BiomeId = M->GetActiveBiomeId();
							if (BiomeId != INDEX_NONE) { M->SetBiomePropTexture(BiomeId, Index, Texture); }
							F2DPalette::RedrawViewports();
						})
					]
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(4.0f, 0.0f, 0.0f, 0.0f)
				[
					F2DPalette::IconButton("F2D.Icon.Trash", LOCTEXT("RemovePropTip", "Remove this object from the biome (Ctrl+Z brings it back)."),
						FOnClicked::CreateLambda([M, Index]()
						{
							ChangeActive(M, LOCTEXT("RemoveProp", "Remove large object"), [Index](FFramework2DBiome& Biome)
							{
								if (Biome.Props.IsValidIndex(Index)) { Biome.Props.RemoveAt(Index); }
							});
							return FReply::Handled();
						}),
						TAttribute<bool>(true), &F2DPalette::DangerIconButtonStyle())
				]
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 6.0f, 0.0f, 0.0f)
			[
				SNew(SWrapBox)
				.UseAllottedSize(true)
				.InnerSlotPadding(FVector2D(10.0f, 4.0f))
				+ SWrapBox::Slot()
				[
					SmallSpin(LOCTEXT("PropWeight", "Weight"),
						LOCTEXT("PropWeightTip", "Probability relative to the other objects (0 = never; 2 = twice as often as weight 1)."),
						0.0f, 10.0f, 0.05f, 2,
						[Find]() { const FFramework2DBiomeProp* Prop = Find(); return Prop ? Prop->Weight : 1.0f; },
						[Change](float V) { Change(LOCTEXT("PropWeightStep", "Object weight"), [V](FFramework2DBiomeProp& Prop) { Prop.Weight = FMath::Max(0.0f, V); }); })
				]
				+ SWrapBox::Slot()
				[
					SmallSpin(LOCTEXT("PropSink", "Sink (px)"),
						LOCTEXT("PropSinkTip", "Pixels it sinks into the ground (roots, rock base)."),
						0.0f, 64.0f, 1.0f, 0,
						[Find]() { const FFramework2DBiomeProp* Prop = Find(); return Prop ? (float)Prop->SinkPixels : 0.0f; },
						[Change](float V) { Change(LOCTEXT("PropSinkStep", "Sink the object"), [V](FFramework2DBiomeProp& Prop) { Prop.SinkPixels = FMath::Clamp(FMath::RoundToInt(V), 0, 64); }); })
				]
				+ SWrapBox::Slot()
				[
					SNew(SButton)
					.ButtonStyle(&F2DPalette::Button("F2D.Button.Secondary"))
					.ContentPadding(FMargin(6.0f, 2.0f))
					.ToolTipText_Lambda([IsFront]()
					{
						return IsFront()
							? LOCTEXT("PropFrontTip", "In front of the terrain: goes in the decoration layer and shows in front of the character. Click to put it behind.")
							: LOCTEXT("PropBehindTip", "Behind the terrain: goes in the «Behind» layer (neither collides nor breaks). Click to put it in front.");
					})
					.OnClicked_Lambda([Change]()
					{
						Change(LOCTEXT("PropDepthStep", "Front or behind"), [](FFramework2DBiomeProp& Prop)
						{
							Prop.Depth = Prop.Depth == EFramework2DPropDepth::Front ? EFramework2DPropDepth::Behind : EFramework2DPropDepth::Front;
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
							.Image_Lambda([IsFront]() { return F2DPalette::Brush(IsFront() ? FName("F2D.Icon.Layers") : FName("F2D.Icon.Background")); })
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
							.Text_Lambda([IsFront]() { return IsFront() ? LOCTEXT("PropFront", "Front") : LOCTEXT("PropBehind", "Behind"); })
						]
					]
				]
				+ SWrapBox::Slot()
				[
					F2DPalette::ToggleChip("F2D.Icon.Flip", LOCTEXT("PropFlip", "Flip"),
						LOCTEXT("PropFlipTip", "Flips half of the objects horizontally, at random."),
						[Find]() { const FFramework2DBiomeProp* Prop = Find(); return Prop && Prop->bRandomFlip; },
						[Change](bool bOn) { Change(LOCTEXT("PropFlipStep", "Flip the object"), [bOn](FFramework2DBiomeProp& Prop) { Prop.bRandomFlip = bOn; }); })
				]
			]
		];
}

#undef LOCTEXT_NAMESPACE
