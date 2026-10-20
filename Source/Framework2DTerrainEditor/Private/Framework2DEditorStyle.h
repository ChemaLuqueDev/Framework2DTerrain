// Copyright Chema Luque. Plugin Framework2DTerrain (modulo Editor).

#pragma once

#include "CoreMinimal.h"
#include "Styling/ISlateStyle.h"

/**
 * Estilo visual del modo Framework2D Tiles: iconos SVG (Resources/Icons) y botones planos,
 * redondeados y con buen contraste. Se registra al cargar el modulo de editor.
 *
 * NOMBRES (todos en este style set):
 *   Iconos (FSlateVectorImageBrush, blancos para poder tenirlos; 16x16 salvo el del modo):
 *     F2D.Mode (40x40) / F2D.Mode.Small (20x20)
 *     F2D.Tool.Paint  F2D.Tool.Erase  F2D.Tool.Fill  F2D.Tool.Rect  F2D.Tool.Pick  F2D.Tool.Collision  (20x20)
 *     F2D.Icon.Eye  F2D.Icon.EyeOff  F2D.Icon.Collide  F2D.Icon.Break  F2D.Icon.Background
 *     F2D.Icon.Add  F2D.Icon.Remove  F2D.Icon.Up  F2D.Icon.Down  F2D.Icon.Trash
 *     F2D.Icon.Flipbook  F2D.Icon.Grid  F2D.Icon.Refresh  F2D.Icon.ZoomIn  F2D.Icon.ZoomOut
 *     F2D.Icon.Replace  F2D.Icon.Ghost  F2D.Icon.Layers  F2D.Icon.Info  F2D.Icon.Generator  F2D.Icon.Flip
 *     Pestana "Generar" (generacion procedural):
 *       F2D.Icon.Biome     arbol y montana (tarjeta Bioma)
 *       F2D.Icon.Dice      dado (Generar mapa, Otra semilla, pestana Generar)
 *       F2D.Icon.Water     gota (agua y cascadas)
 *       F2D.Icon.Ramp      escalon con rampa (rampas)
 *       F2D.Icon.Platform  plataforma flotante sobre el suelo (plataformas)
 *       F2D.Icon.Mountain  relieve de dos picos (tarjeta Receta)
 *   Brushes:
 *     F2D.Card          fondo de cada seccion (redondeado, hundido)
 *     F2D.Row           fila de lista (capa, flipbook) en reposo
 *     F2D.Row.Hover     fila con el raton encima
 *     F2D.Row.Active    fila seleccionada (con el acento)
 *     F2D.AccentBar     barrita de acento (3 px) de la fila activa
 *     F2D.White         blanco plano (para tintar)
 *   Botones (FButtonStyle):
 *     F2D.Button.Tool        boton de herramienta (icono + texto), plano
 *     F2D.Button.ToolActive  el mismo con el acento de fondo (herramienta activa)
 *     F2D.Button.Icon        boton cuadrado solo-icono (24x24), plano
 *     F2D.Button.Primary     boton de accion principal (acento lleno, texto oscuro)
 *     F2D.Button.Secondary   boton de texto discreto
 *   Toggles (FCheckBoxStyle, tipo ToggleButton):
 *     F2D.Toggle.Chip        icono que se enciende con el acento (Visible, Colisiona...)
 *   Textos (FTextBlockStyle):
 *     F2D.Text.Title  F2D.Text.Section  F2D.Text.Body  F2D.Text.Caption  F2D.Text.OnAccent
 */
class FFramework2DEditorStyle
{
public:
	static void Initialize();
	static void Shutdown();
	static const ISlateStyle& Get();
	static FName GetStyleSetName();

	//~ Paleta (tambien para pintar a mano en widgets propios)
	static FLinearColor Accent();        // ambar: seleccion, herramienta activa
	static FLinearColor AccentHover();
	static FLinearColor OnAccent();      // texto/icono encima del acento (oscuro)
	static FLinearColor Surface();       // fondo de tarjetas
	static FLinearColor SurfaceRaised(); // filas y botones en reposo
	static FLinearColor SurfaceHover();
	static FLinearColor Foreground();    // texto principal
	static FLinearColor ForegroundDim(); // texto secundario
	static FLinearColor Danger();        // borrar
	static FLinearColor Collision();     // verde de la colision

private:
	static TSharedPtr<class FSlateStyleSet> StyleSet;
};
