// Copyright Chema Luque. Plugin Framework2DTerrain (modulo Editor).

#include "Framework2DEditorStyle.h"

#include "Brushes/SlateColorBrush.h"
#include "Brushes/SlateImageBrush.h"
#include "Brushes/SlateNoResource.h"
#include "Brushes/SlateRoundedBoxBrush.h"
#include "Framework/Application/SlateApplication.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h"
#include "Rendering/SlateRenderer.h"
#include "Styling/CoreStyle.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Styling/SlateTypes.h"

TSharedPtr<FSlateStyleSet> FFramework2DEditorStyle::StyleSet;

// Nombre propio (no anonimo): en las compilaciones "unity" varios .cpp comparten unidad.
namespace Framework2DStyleUtil
{
	// Color desde su valor hexadecimal sRGB, como en cualquier herramienta de diseno.
	// FLinearColor(FColor) hace la conversion a lineal; asi el editor muestra el tono exacto.
	FLinearColor Hex(uint8 R, uint8 G, uint8 B, float Alpha = 1.0f)
	{
		FLinearColor Color(FColor(R, G, B, 255));
		Color.A = Alpha;
		return Color;
	}

	FLinearColor WithAlpha(const FLinearColor& Color, float Alpha)
	{
		return FLinearColor(Color.R, Color.G, Color.B, Alpha);
	}

	// Tonos intermedios que no necesita nadie fuera de este archivo.
	FLinearColor Pressed()        { return Hex(0x38, 0x38, 0x38); }
	FLinearColor DisabledFill()   { return Hex(0x1F, 0x1F, 0x1F); }
	FLinearColor DisabledText()   { return Hex(0x5C, 0x5C, 0x5C); }
	FLinearColor Outline()        { return Hex(0x2C, 0x2C, 0x2C); }
	FLinearColor OutlineStrong()  { return Hex(0x3A, 0x3A, 0x3A); }
	FLinearColor ToolForeground() { return Hex(0xC4, 0xC4, 0xC4); } // reposo: algo mas apagado que el texto principal
	FLinearColor IconForeground() { return Hex(0xB4, 0xB4, 0xB4); }
	FLinearColor AccentPressed()  { return Hex(0xE0, 0x93, 0x16); }
	FLinearColor AccentTint()     { return Hex(0x3A, 0x2E, 0x1C); } // fondo oscuro tenido de ambar (filas y chips activos)
	FLinearColor AccentTintHover(){ return Hex(0x4A, 0x3A, 0x20); }

	// Un icono SVG de Resources/Icons.
	FSlateVectorImageBrush* Icon(FSlateStyleSet& Style, const TCHAR* File, float Size)
	{
		return new FSlateVectorImageBrush(Style.RootToContentDir(FString(TEXT("Icons/")) + File, TEXT(".svg")), FVector2D(Size, Size));
	}
}

//======================================================================
// Paleta
//======================================================================
// Contrastes (WCAG) medidos sobre la tarjeta #1A1A1A: texto principal 14:1, secundario 6:1,
// oscuro sobre ambar 8.9:1. Todo pasa AA.
FLinearColor FFramework2DEditorStyle::Accent()        { return Framework2DStyleUtil::Hex(0xF5, 0xA5, 0x24); }
FLinearColor FFramework2DEditorStyle::AccentHover()   { return Framework2DStyleUtil::Hex(0xFF, 0xBA, 0x45); }
FLinearColor FFramework2DEditorStyle::OnAccent()      { return Framework2DStyleUtil::Hex(0x16, 0x16, 0x1A); }
FLinearColor FFramework2DEditorStyle::Surface()       { return Framework2DStyleUtil::Hex(0x1A, 0x1A, 0x1A); }
FLinearColor FFramework2DEditorStyle::SurfaceRaised() { return Framework2DStyleUtil::Hex(0x24, 0x24, 0x24); }
FLinearColor FFramework2DEditorStyle::SurfaceHover()  { return Framework2DStyleUtil::Hex(0x2F, 0x2F, 0x2F); }
FLinearColor FFramework2DEditorStyle::Foreground()    { return Framework2DStyleUtil::Hex(0xE6, 0xE6, 0xE6); }
FLinearColor FFramework2DEditorStyle::ForegroundDim() { return Framework2DStyleUtil::Hex(0x9A, 0x9A, 0x9A); }
FLinearColor FFramework2DEditorStyle::Danger()        { return Framework2DStyleUtil::Hex(0xFF, 0x6B, 0x6B); }
FLinearColor FFramework2DEditorStyle::Collision()     { return Framework2DStyleUtil::Hex(0x3D, 0xD6, 0x8C); }

//======================================================================
// Registro
//======================================================================
FName FFramework2DEditorStyle::GetStyleSetName()
{
	static const FName Name(TEXT("Framework2DTerrainStyle"));
	return Name;
}

const ISlateStyle& FFramework2DEditorStyle::Get()
{
	// Por si algo pide el estilo antes de que arranque el modulo (pruebas): se crea al vuelo.
	if (!StyleSet.IsValid())
	{
		Initialize();
	}
	return *StyleSet;
}

void FFramework2DEditorStyle::Shutdown()
{
	if (StyleSet.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet);
		StyleSet.Reset();
	}
}

void FFramework2DEditorStyle::Initialize()
{
	using namespace Framework2DStyleUtil;

	if (StyleSet.IsValid())
	{
		return;
	}

	StyleSet = MakeShared<FSlateStyleSet>(GetStyleSetName());

	// Los SVG viven en <plugin>/Resources/Icons.
	const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("Framework2DTerrain"));
	const FString ResourcesDir = Plugin.IsValid()
		? Plugin->GetBaseDir() / TEXT("Resources")
		: FPaths::ProjectPluginsDir() / TEXT("Framework2DTerrain/Resources");
	StyleSet->SetContentRoot(ResourcesDir);

	FSlateStyleSet& S = *StyleSet;

	//---------------------- Iconos ----------------------
	// Todos blancos: quien los usa los tine con el color de primer plano del boton.
	S.Set("F2D.Mode",       Icon(S, TEXT("Mode"), 40.0f));
	S.Set("F2D.Mode.Small", Icon(S, TEXT("Mode"), 20.0f));

	S.Set("F2D.Tool.Paint",     Icon(S, TEXT("Tool_Paint"), 20.0f));
	S.Set("F2D.Tool.Erase",     Icon(S, TEXT("Tool_Erase"), 20.0f));
	S.Set("F2D.Tool.Fill",      Icon(S, TEXT("Tool_Fill"), 20.0f));
	S.Set("F2D.Tool.Rect",      Icon(S, TEXT("Tool_Rect"), 20.0f));
	S.Set("F2D.Tool.Pick",      Icon(S, TEXT("Tool_Pick"), 20.0f));
	S.Set("F2D.Tool.Collision", Icon(S, TEXT("Tool_Collision"), 20.0f));

	S.Set("F2D.Icon.Eye",        Icon(S, TEXT("Icon_Eye"), 16.0f));
	S.Set("F2D.Icon.EyeOff",     Icon(S, TEXT("Icon_EyeOff"), 16.0f));
	S.Set("F2D.Icon.Collide",    Icon(S, TEXT("Icon_Collide"), 16.0f));
	S.Set("F2D.Icon.Break",      Icon(S, TEXT("Icon_Break"), 16.0f));
	S.Set("F2D.Icon.Background", Icon(S, TEXT("Icon_Background"), 16.0f));
	S.Set("F2D.Icon.Add",        Icon(S, TEXT("Icon_Add"), 16.0f));
	S.Set("F2D.Icon.Remove",     Icon(S, TEXT("Icon_Remove"), 16.0f));
	S.Set("F2D.Icon.Up",         Icon(S, TEXT("Icon_Up"), 16.0f));
	S.Set("F2D.Icon.Down",       Icon(S, TEXT("Icon_Down"), 16.0f));
	S.Set("F2D.Icon.Trash",      Icon(S, TEXT("Icon_Trash"), 16.0f));
	S.Set("F2D.Icon.Flipbook",   Icon(S, TEXT("Icon_Flipbook"), 16.0f));
	S.Set("F2D.Icon.Grid",       Icon(S, TEXT("Icon_Grid"), 16.0f));
	S.Set("F2D.Icon.Refresh",    Icon(S, TEXT("Icon_Refresh"), 16.0f));
	S.Set("F2D.Icon.ZoomIn",     Icon(S, TEXT("Icon_ZoomIn"), 16.0f));
	S.Set("F2D.Icon.ZoomOut",    Icon(S, TEXT("Icon_ZoomOut"), 16.0f));
	S.Set("F2D.Icon.Replace",    Icon(S, TEXT("Icon_Replace"), 16.0f));
	S.Set("F2D.Icon.Ghost",      Icon(S, TEXT("Icon_Ghost"), 16.0f));
	S.Set("F2D.Icon.Generator",  Icon(S, TEXT("Icon_Generator"), 16.0f));
	S.Set("F2D.Icon.Flip",       Icon(S, TEXT("Icon_Flip"), 16.0f));
	S.Set("F2D.Icon.Layers",     Icon(S, TEXT("Icon_Layers"), 16.0f));
	S.Set("F2D.Icon.Info",       Icon(S, TEXT("Icon_Info"), 16.0f));

	// Pestana "Generar" (generacion procedural).
	S.Set("F2D.Icon.Biome",      Icon(S, TEXT("Icon_Biome"), 16.0f));
	S.Set("F2D.Icon.Dice",       Icon(S, TEXT("Icon_Dice"), 16.0f));
	S.Set("F2D.Icon.Water",      Icon(S, TEXT("Icon_Water"), 16.0f));
	S.Set("F2D.Icon.Ramp",       Icon(S, TEXT("Icon_Ramp"), 16.0f));
	S.Set("F2D.Icon.Platform",   Icon(S, TEXT("Icon_Platform"), 16.0f));
	S.Set("F2D.Icon.Mountain",   Icon(S, TEXT("Icon_Mountain"), 16.0f));

	//---------------------- Superficies ----------------------
	S.Set("F2D.Card",       new FSlateRoundedBoxBrush(Surface(), 6.0f, Outline(), 1.0f));
	S.Set("F2D.Row",        new FSlateRoundedBoxBrush(SurfaceRaised(), 4.0f));
	S.Set("F2D.Row.Hover",  new FSlateRoundedBoxBrush(SurfaceHover(), 4.0f));
	S.Set("F2D.Row.Active", new FSlateRoundedBoxBrush(AccentTint(), 4.0f, WithAlpha(Accent(), 0.55f), 1.0f));
	S.Set("F2D.AccentBar",  new FSlateRoundedBoxBrush(Accent(), 1.5f));
	S.Set("F2D.White",      new FSlateColorBrush(FLinearColor::White));

	//---------------------- Botones ----------------------
	// Planos, redondeados y sin degradados. Cada estado cambia el fondo Y el primer plano,
	// asi se distinguen aunque no se vea bien el color.
	const FButtonStyle ToolButton = FButtonStyle()
		.SetNormal(FSlateRoundedBoxBrush(SurfaceRaised(), 4.0f))
		.SetHovered(FSlateRoundedBoxBrush(SurfaceHover(), 4.0f))
		.SetPressed(FSlateRoundedBoxBrush(Pressed(), 4.0f))
		.SetDisabled(FSlateRoundedBoxBrush(DisabledFill(), 4.0f))
		.SetNormalForeground(ToolForeground())
		.SetHoveredForeground(Foreground())
		.SetPressedForeground(Foreground())
		.SetDisabledForeground(DisabledText())
		.SetNormalPadding(FMargin(2.0f, 6.0f, 2.0f, 5.0f))
		.SetPressedPadding(FMargin(2.0f, 7.0f, 2.0f, 4.0f));
	S.Set("F2D.Button.Tool", ToolButton);

	const FButtonStyle ToolActiveButton = FButtonStyle(ToolButton)
		.SetNormal(FSlateRoundedBoxBrush(Accent(), 4.0f))
		.SetHovered(FSlateRoundedBoxBrush(AccentHover(), 4.0f))
		.SetPressed(FSlateRoundedBoxBrush(AccentPressed(), 4.0f))
		.SetNormalForeground(OnAccent())
		.SetHoveredForeground(OnAccent())
		.SetPressedForeground(OnAccent());
	S.Set("F2D.Button.ToolActive", ToolActiveButton);

	// Solo icono: 4 px de margen + icono de 16 = 24x24 (objetivo minimo de clic).
	const FButtonStyle IconButton = FButtonStyle()
		.SetNormal(FSlateNoResource())
		.SetHovered(FSlateRoundedBoxBrush(SurfaceHover(), 4.0f))
		.SetPressed(FSlateRoundedBoxBrush(Pressed(), 4.0f))
		.SetDisabled(FSlateNoResource())
		.SetNormalForeground(IconForeground())
		.SetHoveredForeground(Foreground())
		.SetPressedForeground(Foreground())
		.SetDisabledForeground(Hex(0x4F, 0x4F, 0x4F))
		.SetNormalPadding(FMargin(4.0f))
		.SetPressedPadding(FMargin(4.0f, 5.0f, 4.0f, 3.0f));
	S.Set("F2D.Button.Icon", IconButton);

	const FButtonStyle PrimaryButton = FButtonStyle()
		.SetNormal(FSlateRoundedBoxBrush(Accent(), 4.0f))
		.SetHovered(FSlateRoundedBoxBrush(AccentHover(), 4.0f))
		.SetPressed(FSlateRoundedBoxBrush(AccentPressed(), 4.0f))
		.SetDisabled(FSlateRoundedBoxBrush(Hex(0x2C, 0x2C, 0x2C), 4.0f))
		.SetNormalForeground(OnAccent())
		.SetHoveredForeground(OnAccent())
		.SetPressedForeground(OnAccent())
		.SetDisabledForeground(Hex(0x6E, 0x6E, 0x6E))
		.SetNormalPadding(FMargin(10.0f, 5.0f, 10.0f, 5.0f))
		.SetPressedPadding(FMargin(10.0f, 6.0f, 10.0f, 4.0f));
	S.Set("F2D.Button.Primary", PrimaryButton);

	const FButtonStyle SecondaryButton = FButtonStyle()
		.SetNormal(FSlateRoundedBoxBrush(SurfaceRaised(), 4.0f, OutlineStrong(), 1.0f))
		.SetHovered(FSlateRoundedBoxBrush(SurfaceHover(), 4.0f, Hex(0x4A, 0x4A, 0x4A), 1.0f))
		.SetPressed(FSlateRoundedBoxBrush(Pressed(), 4.0f, Hex(0x4A, 0x4A, 0x4A), 1.0f))
		.SetDisabled(FSlateRoundedBoxBrush(DisabledFill(), 4.0f, Outline(), 1.0f))
		.SetNormalForeground(Foreground())
		.SetHoveredForeground(Foreground())
		.SetPressedForeground(Foreground())
		.SetDisabledForeground(DisabledText())
		.SetNormalPadding(FMargin(8.0f, 4.0f, 8.0f, 4.0f))
		.SetPressedPadding(FMargin(8.0f, 5.0f, 8.0f, 3.0f));
	S.Set("F2D.Button.Secondary", SecondaryButton);

	//---------------------- Interruptores ----------------------
	// Apagado: solo contorno y el icono gris. Encendido: fondo tenido, contorno e icono ambar.
	// La diferencia es de relleno y de brillo, no solo de tono.
	const FSlateRoundedBoxBrush ChipOff(FLinearColor::Transparent, 4.0f, OutlineStrong(), 1.0f);
	const FCheckBoxStyle Chip = FCheckBoxStyle()
		.SetCheckBoxType(ESlateCheckBoxType::ToggleButton)
		.SetUncheckedImage(ChipOff)
		.SetUncheckedHoveredImage(FSlateRoundedBoxBrush(SurfaceHover(), 4.0f, Hex(0x4A, 0x4A, 0x4A), 1.0f))
		.SetUncheckedPressedImage(FSlateRoundedBoxBrush(Pressed(), 4.0f, Hex(0x4A, 0x4A, 0x4A), 1.0f))
		.SetCheckedImage(FSlateRoundedBoxBrush(AccentTint(), 4.0f, WithAlpha(Accent(), 0.7f), 1.0f))
		.SetCheckedHoveredImage(FSlateRoundedBoxBrush(AccentTintHover(), 4.0f, Accent(), 1.0f))
		.SetCheckedPressedImage(FSlateRoundedBoxBrush(Hex(0x2E, 0x25, 0x16), 4.0f, Accent(), 1.0f))
		.SetUndeterminedImage(ChipOff)
		.SetUndeterminedHoveredImage(FSlateRoundedBoxBrush(SurfaceHover(), 4.0f, Hex(0x4A, 0x4A, 0x4A), 1.0f))
		.SetUndeterminedPressedImage(FSlateRoundedBoxBrush(Pressed(), 4.0f, Hex(0x4A, 0x4A, 0x4A), 1.0f))
		.SetPadding(FMargin(4.0f))
		.SetForegroundColor(ForegroundDim())
		.SetHoveredForegroundColor(Foreground())
		.SetPressedForegroundColor(Foreground())
		.SetCheckedForegroundColor(Accent())
		.SetCheckedHoveredForegroundColor(AccentHover())
		.SetCheckedPressedForegroundColor(Accent())
		.SetUndeterminedForegroundColor(ForegroundDim());
	S.Set("F2D.Toggle.Chip", Chip);

	//---------------------- Textos ----------------------
	const FTextBlockStyle Body = FTextBlockStyle()
		.SetFont(FCoreStyle::GetDefaultFontStyle("Regular", 9))
		.SetColorAndOpacity(Foreground())
		.SetShadowColorAndOpacity(FLinearColor::Transparent);
	S.Set("F2D.Text.Body", Body);

	S.Set("F2D.Text.Title", FTextBlockStyle(Body)
		.SetFont(FCoreStyle::GetDefaultFontStyle("Bold", 12)));

	// Titulo de seccion: mayusculas (las pone quien lo usa) con algo de aire entre letras.
	// LetterSpacing va en milesimas del tamano: 120 a 9 pt = 1 px.
	FSlateFontInfo SectionFont = FCoreStyle::GetDefaultFontStyle("Bold", 9);
	SectionFont.LetterSpacing = 120;
	S.Set("F2D.Text.Section", FTextBlockStyle(Body)
		.SetFont(SectionFont)
		.SetColorAndOpacity(ForegroundDim()));

	S.Set("F2D.Text.Caption", FTextBlockStyle(Body)
		.SetFont(FCoreStyle::GetDefaultFontStyle("Regular", 8))
		.SetColorAndOpacity(ForegroundDim()));

	S.Set("F2D.Text.OnAccent", FTextBlockStyle(Body)
		.SetFont(FCoreStyle::GetDefaultFontStyle("Bold", 9))
		.SetColorAndOpacity(OnAccent()));

	FSlateStyleRegistry::RegisterSlateStyle(S);

	// Si el editor ya estaba en marcha (recarga del modulo), que se rastericen los SVG nuevos.
	if (FSlateApplication::IsInitialized())
	{
		if (FSlateRenderer* Renderer = FSlateApplication::Get().GetRenderer())
		{
			Renderer->ReloadTextureResources();
		}
	}
}
