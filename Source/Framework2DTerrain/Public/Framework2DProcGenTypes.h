// Copyright Chema Luque. Plugin Framework2DTerrain.

#pragma once

#include "CoreMinimal.h"
#include "Framework2DProcGenTypes.generated.h"

class UTexture2D;

/**
 * GENERACION PROCEDURAL DE MAPAS (v2.3)
 * =================================================================
 * Un BIOMA (en el Tile Set) dice con que piezas se construye un nivel: el terreno 3x3, rampas,
 * plataformas, fondo, agua, cascadas y decoracion. La RECETA (en el Tile Map) dice como es el
 * nivel: cuantas alturas, cuanta decoracion, rampas, lagos... y la semilla. El generador junta
 * las dos y rellena las capas Terreno, Fondo, Agua y Decoracion del mapa.
 *
 * Todas las piezas son VALORES DE CELDA (ver Framework2D::FlipbookTileBase): un tile de
 * cualquier pagina del atlas, un flipbook (agua, cascadas, antorchas...) o un generador de
 * vegetacion. -1 = sin asignar.
 */

/** Donde va un adorno del bioma. */
UENUM(BlueprintType)
enum class EFramework2DDecorPlacement : uint8
{
	// Encima del suelo (hierba, rocas, flores, antorchas...).
	Ground  UMETA(DisplayName = "Suelo"),
	// Colgando bajo el terreno (lianas o estalactitas bajo las plataformas).
	Ceiling UMETA(DisplayName = "Techo")
};

/**
 * Las 9 piezas de un terreno "3x3": esquinas, bordes y centro. Con solo el centro ya se puede
 * generar (las que falten usan la pieza mas parecida: esquina -> borde -> centro).
 */
USTRUCT(BlueprintType)
struct FFramework2DTile3x3
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D") int32 TopLeft = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D") int32 Top = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D") int32 TopRight = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D") int32 Left = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D") int32 Center = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D") int32 Right = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D") int32 BottomLeft = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D") int32 Bottom = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D") int32 BottomRight = -1;

	static constexpr int32 Num = 9;

	/** Pieza por indice en orden de lectura: 0 arriba-izquierda, 1 arriba, 2 arriba-derecha, 3 izquierda, 4 centro, 5 derecha, 6 abajo-izquierda, 7 abajo, 8 abajo-derecha. */
	int32& Ref(int32 Index)
	{
		switch (Index)
		{
		case 0: return TopLeft;
		case 1: return Top;
		case 2: return TopRight;
		case 3: return Left;
		case 5: return Right;
		case 6: return BottomLeft;
		case 7: return Bottom;
		case 8: return BottomRight;
		default: return Center;
		}
	}
	int32 Get(int32 Index) const { return const_cast<FFramework2DTile3x3*>(this)->Ref(Index); }
	void Set(int32 Index, int32 Value) { Ref(Index) = Value; }

	/** Pieza de la fila (0 arriba, 1 medio, 2 abajo) y columna (0 izquierda, 1 medio, 2 derecha). */
	int32 At(int32 Row, int32 Col) const { return Get(FMath::Clamp(Row, 0, 2) * 3 + FMath::Clamp(Col, 0, 2)); }

	bool IsEmpty() const
	{
		for (int32 I = 0; I < Num; ++I) { if (Get(I) >= 0) { return false; } }
		return true;
	}
};

/**
 * Terreno 5x5 (opcional): para tilesets cuyos bordes tienen DOS tiles de grosor (la hierba que
 * ocupa dos filas, rocas en los lados...). Filas: 0 = la de arriba del todo, 1 = la segunda, 2 y 3 =
 * el interior (3 = la de justo encima del borde de abajo), 4 = la de abajo. Columnas igual de
 * izquierda a derecha. Si tiene el centro (fila 2, columna 2), manda sobre el 3x3.
 */
USTRUCT(BlueprintType)
struct FFramework2DTile5x5
{
	GENERATED_BODY()

	// 25 piezas en orden de lectura (fila * 5 + columna). -1 = sin asignar.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, EditFixedSize, Category = "Framework2D")
	TArray<int32> Pieces;

	FFramework2DTile5x5() { Pieces.Init(-1, 25); }

	int32 At(int32 Row, int32 Col) const
	{
		const int32 I = FMath::Clamp(Row, 0, 4) * 5 + FMath::Clamp(Col, 0, 4);
		return Pieces.IsValidIndex(I) ? Pieces[I] : -1;
	}
	int32& Ref(int32 Index)
	{
		if (Pieces.Num() != 25) { const int32 Old = Pieces.Num(); Pieces.SetNum(25); for (int32 i = Old; i < 25; ++i) { Pieces[i] = -1; } }
		return Pieces[FMath::Clamp(Index, 0, 24)];
	}
	bool IsEmpty() const
	{
		for (const int32 P : Pieces) { if (P >= 0) { return false; } }
		return true;
	}
};

/**
 * Esquinas INTERIORES (opcionales): la pieza que une un suelo con la pared de un escalon (la
 * hierba dobla la esquina hacia dentro). Sin ellas se usa el centro.
 */
USTRUCT(BlueprintType)
struct FFramework2DInnerCorners
{
	GENERATED_BODY()

	// Hueco arriba-izquierda (pie de un escalon que sube hacia la derecha).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D") int32 TopLeft = -1;
	// Hueco arriba-derecha (pie de un escalon que sube hacia la izquierda).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D") int32 TopRight = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D") int32 BottomLeft = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D") int32 BottomRight = -1;

	static constexpr int32 Num = 4;

	/** 0 arriba-izquierda, 1 arriba-derecha, 2 abajo-izquierda, 3 abajo-derecha. */
	int32& Ref(int32 Index)
	{
		switch (Index)
		{
		case 1: return TopRight;
		case 2: return BottomLeft;
		case 3: return BottomRight;
		default: return TopLeft;
		}
	}
	int32 Get(int32 Index) const { return const_cast<FFramework2DInnerCorners*>(this)->Ref(Index); }
};

/** Forma del suelo que construye el generador. */
UENUM(BlueprintType)
enum class EFramework2DReliefStyle : uint8
{
	// Llanos a varias alturas unidos por escalones y rampas (plataformas clasicas).
	Steps UMETA(DisplayName = "Escalones"),
	// Lomas suaves que suben y bajan casilla a casilla (exteriores naturales).
	Hills UMETA(DisplayName = "Lomas")
};

/** Donde va un objeto grande del bioma. */
UENUM(BlueprintType)
enum class EFramework2DPropDepth : uint8
{
	// En una capa detras del terreno (arboles, rocas del paisaje): no choca ni se rompe.
	Behind UMETA(DisplayName = "Behind the terrain"),
	// En la capa de decoracion, delante (setas grandes, piedras): se ve delante del personaje.
	Front  UMETA(DisplayName = "Delante del terreno")
};

/**
 * Una capa de FONDO PARALLAX: una imagen (cielo, montanas, bosque lejano...) detras del terreno
 * que se mueve mas despacio que el nivel al mover la camara. Se ve en el editor y en el juego.
 */
USTRUCT(BlueprintType)
struct FFramework2DBackdropLayer
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	FName Name = TEXT("Background");

	// La imagen. Para pixel art: Filter = Nearest y sin mipmaps (boton derecho > Sprite Actions >
	// Apply Paper2D Texture Settings). Para repetirla a lo ancho, Address X = Wrap (el de serie).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	TObjectPtr<UTexture2D> Texture = nullptr;

	// Cuanto se mueve con el nivel: 0 = quieta en la pantalla (cielo), 1 = como el terreno.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float Parallax = 0.3f;

	// Lo mismo en vertical (normalmente menos que en horizontal).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float VerticalParallax = 0.15f;

	// Tamano: pixeles del terreno por pixel de la imagen (1 = el mismo tamano de pixel que el nivel).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D", meta = (ClampMin = "0.1", ClampMax = "32.0"))
	float Scale = 1.0f;

	// Altura (tiles) del borde de abajo de la imagen sobre el fondo del nivel.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D", meta = (ClampMin = "-256.0", ClampMax = "1024.0"))
	float Height = 0.0f;

	// Repetir la imagen a lo ancho (sin fin).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	bool bRepeat = true;

	// Alarga la fila de abajo de la imagen hasta el fondo del nivel (sin huecos debajo).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	bool bFillBelow = true;

	// Alarga la fila de arriba hasta lo alto del nivel (para el cielo).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	bool bFillAbove = false;

	// Tinte (blanco = sin cambios).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	FLinearColor Tint = FLinearColor::White;
};

/**
 * Un OBJETO GRANDE colocado en el mapa (arbol, roca, piedra runica...): una imagen del Tile Set
 * (Props) que se hornea como pixeles de una capa. Lo crea el generador procedural.
 */
USTRUCT(BlueprintType)
struct FFramework2DPropInstance
{
	GENERATED_BODY()

	// Id del objeto en el Tile Set (Props).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	int32 PropId = 0;

	// Capa del mapa (por nombre) donde se hornea.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	FName Layer = NAME_None;

	// Centro horizontal (en tiles; 10.5 = la mitad de la columna 10).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	float X = 0.0f;

	// Fila del mapa (Y = 0 arriba) de la casilla sobre la que se apoya: el pie del objeto queda en
	// el borde de abajo de esa casilla (o, si cuelga, la cabeza en su borde de arriba).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	int32 Y = 0;

	// Pixeles que se hunde en el suelo (o en el techo, si cuelga).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	int32 SinkPixels = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	bool bFlip = false;

	// Cuelga del techo en vez de apoyarse en el suelo.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	bool bHanging = false;

	// Tapa lo que ya hay en su capa (tiles y objetos de antes). Si no, solo pinta donde no hay nada.
	// Si no, solo pinta donde la capa esta vacia.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	bool bCoverTiles = false;

	// Apoya el pie en el primer pixel de suelo que choca bajo su centro (como los generadores):
	// asi no flota sobre tiles cuya hierba empieza mas abajo del borde del tile. Hundir se suma.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	bool bSnapToGround = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D", meta = (ClampMin = "0.1", ClampMax = "8.0"))
	float Scale = 1.0f;
};

/** Un objeto grande que el generador reparte por el suelo del nivel. */
USTRUCT(BlueprintType)
struct FFramework2DBiomeProp
{
	GENERATED_BODY()

	// Id del objeto en el Tile Set (Props).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	int32 PropId = 0;

	// Probabilidad relativa frente a los demas objetos del bioma.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D", meta = (ClampMin = "0.0", UIMax = "10.0"))
	float Weight = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	EFramework2DPropDepth Depth = EFramework2DPropDepth::Behind;

	// Pixeles que se hunde en el suelo (raices, base de la roca).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D", meta = (ClampMin = "0", ClampMax = "64"))
	int32 SinkPixels = 2;

	// Voltear en horizontal la mitad, al azar.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	bool bRandomFlip = true;
};

/** Un adorno que el generador reparte por el nivel. */
USTRUCT(BlueprintType)
struct FFramework2DBiomeDecoration
{
	GENERATED_BODY()

	// Tile, flipbook (antorcha, flor animada...) o generador de vegetacion.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	int32 Value = -1;

	// Probabilidad relativa frente a los demas adornos del mismo sitio (suelo o techo).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D", meta = (ClampMin = "0.0", UIMax = "10.0"))
	float Weight = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	EFramework2DDecorPlacement Placement = EFramework2DDecorPlacement::Ground;
};

/**
 * Un BIOMA: las piezas con las que el generador procedural construye un nivel (bosque, cueva,
 * desierto...). Se guardan en el Tile Set y se editan en la pestana "Generar" del panel.
 */
USTRUCT(BlueprintType)
struct FFramework2DBiome
{
	GENERATED_BODY()

	// Nombre que se ve en el panel.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	FName Name = TEXT("Bioma");

	// Identificador estable que guardan las recetas de los mapas. No lo cambies a mano.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Framework2D")
	int32 Id = 0;

	// El terreno 3x3 (obligatorio al menos el centro, o el del 5x5).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Terrain")
	FFramework2DTile3x3 Ground;

	// Terreno 5x5 (opcional): bordes de dos tiles de grosor. Con su centro, se usa en vez del 3x3.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Terrain")
	FFramework2DTile5x5 Ground5;

	// Interior profundo (opcional, con el 5x5): lo que va mas adentro que las filas del 5x5 (a 4 o
	// mas casillas del aire por arriba). Para tilesets cuyo centro es una franja (rocas bajo la
	// hierba) y lo de debajo es liso. Sin el, el centro del 5x5.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Terrain")
	int32 GroundDeep = -1;

	// Esquinas interiores (opcional).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Terrain")
	FFramework2DInnerCorners InnerCorners;

	// Variantes del centro (opcional): se mezclan al azar con el centro para que no se repita.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Terrain")
	TArray<int32> CenterVariants;

	// Rampa de 45 grados que sube hacia la derecha ( / ). Un tile por cada tile de altura.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Ramps")
	int32 RampUp = -1;

	// Rampa de 45 grados que baja hacia la derecha ( \ ).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Ramps")
	int32 RampDown = -1;

	// Rampa suave que sube (dos tiles por cada tile de altura): la mitad baja y la alta.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Ramps")
	int32 GentleUpLow = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Ramps")
	int32 GentleUpHigh = -1;

	// Rampa suave que baja: primero la mitad alta y luego la baja.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Ramps")
	int32 GentleDownHigh = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Ramps")
	int32 GentleDownLow = -1;

	// Plataformas flotantes (opcional): extremo izquierdo, tramo y extremo derecho. Sin ellas,
	// las plataformas usan la fila de arriba del terreno 3x3.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Platforms")
	int32 PlatformLeft = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Platforms")
	int32 PlatformMiddle = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Platforms")
	int32 PlatformRight = -1;

	// Fondo (opcional): pared trasera y colinas detras del terreno. Se ve al picar. Con solo
	// el centro, todo el fondo es esa pieza.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Background")
	FFramework2DTile3x3 Background;

	// Agua (opcional; suelen ser flipbooks): la fila de arriba de cada lago y el resto.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Water")
	int32 WaterSurface = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Water")
	int32 WaterBody = -1;

	// Olas (opcional): lo que asoma por ENCIMA de la superficie del agua (va en la casilla de encima).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Water")
	int32 WaterCrest = -1;

	// Cascada (opcional; suelen ser flipbooks): el borde de arriba, la caida y la espuma de abajo.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Water")
	int32 WaterfallTop = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Water")
	int32 WaterfallBody = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Water")
	int32 WaterfallBottom = -1;

	// Adornos que se reparten por el suelo (o cuelgan del techo).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Decoration", meta = (TitleProperty = "Value"))
	TArray<FFramework2DBiomeDecoration> Decorations;

	// Puentes (opcional): sobre fosos, lagos y valles estrechos entre dos orillas a la misma
	// altura. Extremo izquierdo, tablas y extremo derecho; sin extremos, todo son tablas.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Bridges")
	int32 BridgeLeft = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Bridges")
	int32 BridgeMiddle = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Bridges")
	int32 BridgeRight = -1;

	// Canto del puente (opcional, con el 5x5): encima de las tablas, en la capa de bordes (el borde
	// claro de las tablas y el arranque de las cuerdas). Extremo izquierdo, tramo y extremo derecho.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Bridges")
	int32 BridgeCapLeft = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Bridges")
	int32 BridgeCapMiddle = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Bridges")
	int32 BridgeCapRight = -1;

	// Postes de los extremos del puente (opcional): la casilla de encima de cada extremo (abajo) y
	// la de encima de esa (arriba). Son decoracion: no chocan.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Bridges")
	int32 BridgePostLeftLow = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Bridges")
	int32 BridgePostLeftHigh = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Bridges")
	int32 BridgePostRightLow = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Bridges")
	int32 BridgePostRightHigh = -1;

	// Bordes naturales (opcional; suelen ser generadores): lo que se pone encima de CADA borde de
	// arriba del terreno (franja de hierba o musgo que tapa la linea recta de los tiles) y debajo
	// de cada borde de abajo (rocas o raices bajo islas y salientes: generador con "Colgar del techo").
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Edges")
	int32 EdgeTop = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Edges")
	int32 EdgeBottom = -1;

	// Fondos parallax (cielo, montanas, bosque lejano...), de atras a delante. Al generar se copian
	// al Tile Map.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Background", meta = (TitleProperty = "Name"))
	TArray<FFramework2DBackdropLayer> Backdrops;

	// Objetos grandes (arboles, rocas...) que se reparten por el suelo.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Objects")
	TArray<FFramework2DBiomeProp> Props;

	// Pie de pared (opcional, con el 5x5): donde un suelo llega a la pared de un escalon, la hierba
	// pasa por delante del pie de la pared. "Izquierda" = el suelo esta a la izquierda de la pared.
	// La pieza va en la primera columna de la pared, a la altura de la segunda fila del suelo, y la
	// de "dentro" en la columna siguiente (remata la hierba contra la roca).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Terrain")
	int32 WallFootLeft = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Terrain")
	int32 WallFootLeftInner = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Terrain")
	int32 WallFootRight = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Terrain")
	int32 WallFootRightInner = -1;

	// Remate de las plataformas (opcional, solo con piezas de plataforma): va encima de cada casilla
	// de plataforma, en la capa de bordes (el canto de un tablon que asoma por encima de su tile).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Platforms")
	int32 PlatformCapLeft = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Platforms")
	int32 PlatformCapMiddle = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Platforms")
	int32 PlatformCapRight = -1;
};

/**
 * Cada pieza suelta de un bioma, para editarlas una a una (panel, pruebas, Blueprint). Las
 * listas (variantes del centro y decoracion) se editan aparte.
 */
UENUM(BlueprintType)
enum class EFramework2DBiomeSlot : uint8
{
	GroundTopLeft, GroundTop, GroundTopRight,
	GroundLeft, GroundCenter, GroundRight,
	GroundBottomLeft, GroundBottom, GroundBottomRight,
	InnerTopLeft, InnerTopRight, InnerBottomLeft, InnerBottomRight,
	RampUp, RampDown,
	GentleUpLow, GentleUpHigh, GentleDownHigh, GentleDownLow,
	PlatformLeft, PlatformMiddle, PlatformRight,
	BackgroundTopLeft, BackgroundTop, BackgroundTopRight,
	BackgroundLeft, BackgroundCenter, BackgroundRight,
	BackgroundBottomLeft, BackgroundBottom, BackgroundBottomRight,
	WaterSurface, WaterBody,
	WaterfallTop, WaterfallBody, WaterfallBottom,
	BridgeLeft, BridgeMiddle, BridgeRight,
	EdgeTop, EdgeBottom,
	WaterCrest,
	BridgePostLeftLow, BridgePostLeftHigh, BridgePostRightLow, BridgePostRightHigh,
	Ground5_00, Ground5_01, Ground5_02, Ground5_03, Ground5_04,
	Ground5_10, Ground5_11, Ground5_12, Ground5_13, Ground5_14,
	Ground5_20, Ground5_21, Ground5_22, Ground5_23, Ground5_24,
	Ground5_30, Ground5_31, Ground5_32, Ground5_33, Ground5_34,
	Ground5_40, Ground5_41, Ground5_42, Ground5_43, Ground5_44,
	WallFootLeft, WallFootLeftInner, WallFootRight, WallFootRightInner,
	PlatformCapLeft, PlatformCapMiddle, PlatformCapRight,
	GroundDeep,
	BridgeCapLeft, BridgeCapMiddle, BridgeCapRight,
	Count UMETA(Hidden)
};

namespace Framework2D
{
	/** La pieza de un bioma que corresponde a un hueco (nunca nullptr para un hueco valido). */
	inline int32* BiomeSlotRef(FFramework2DBiome& Biome, EFramework2DBiomeSlot Slot)
	{
		const int32 S = (int32)Slot;
		if (S >= (int32)EFramework2DBiomeSlot::GroundTopLeft && S <= (int32)EFramework2DBiomeSlot::GroundBottomRight)
		{
			return &Biome.Ground.Ref(S - (int32)EFramework2DBiomeSlot::GroundTopLeft);
		}
		if (S >= (int32)EFramework2DBiomeSlot::InnerTopLeft && S <= (int32)EFramework2DBiomeSlot::InnerBottomRight)
		{
			return &Biome.InnerCorners.Ref(S - (int32)EFramework2DBiomeSlot::InnerTopLeft);
		}
		if (S >= (int32)EFramework2DBiomeSlot::BackgroundTopLeft && S <= (int32)EFramework2DBiomeSlot::BackgroundBottomRight)
		{
			return &Biome.Background.Ref(S - (int32)EFramework2DBiomeSlot::BackgroundTopLeft);
		}
		if (S >= (int32)EFramework2DBiomeSlot::Ground5_00 && S <= (int32)EFramework2DBiomeSlot::Ground5_44)
		{
			return &Biome.Ground5.Ref(S - (int32)EFramework2DBiomeSlot::Ground5_00);
		}
		switch (Slot)
		{
		case EFramework2DBiomeSlot::RampUp:          return &Biome.RampUp;
		case EFramework2DBiomeSlot::RampDown:        return &Biome.RampDown;
		case EFramework2DBiomeSlot::GentleUpLow:     return &Biome.GentleUpLow;
		case EFramework2DBiomeSlot::GentleUpHigh:    return &Biome.GentleUpHigh;
		case EFramework2DBiomeSlot::GentleDownHigh:  return &Biome.GentleDownHigh;
		case EFramework2DBiomeSlot::GentleDownLow:   return &Biome.GentleDownLow;
		case EFramework2DBiomeSlot::PlatformLeft:    return &Biome.PlatformLeft;
		case EFramework2DBiomeSlot::PlatformMiddle:  return &Biome.PlatformMiddle;
		case EFramework2DBiomeSlot::PlatformRight:   return &Biome.PlatformRight;
		case EFramework2DBiomeSlot::WaterSurface:    return &Biome.WaterSurface;
		case EFramework2DBiomeSlot::WaterBody:       return &Biome.WaterBody;
		case EFramework2DBiomeSlot::WaterfallTop:    return &Biome.WaterfallTop;
		case EFramework2DBiomeSlot::WaterfallBody:   return &Biome.WaterfallBody;
		case EFramework2DBiomeSlot::WaterfallBottom: return &Biome.WaterfallBottom;
		case EFramework2DBiomeSlot::BridgeLeft:      return &Biome.BridgeLeft;
		case EFramework2DBiomeSlot::BridgeMiddle:    return &Biome.BridgeMiddle;
		case EFramework2DBiomeSlot::BridgeRight:     return &Biome.BridgeRight;
		case EFramework2DBiomeSlot::EdgeTop:         return &Biome.EdgeTop;
		case EFramework2DBiomeSlot::EdgeBottom:      return &Biome.EdgeBottom;
		case EFramework2DBiomeSlot::WaterCrest:      return &Biome.WaterCrest;
		case EFramework2DBiomeSlot::BridgePostLeftLow:   return &Biome.BridgePostLeftLow;
		case EFramework2DBiomeSlot::BridgePostLeftHigh:  return &Biome.BridgePostLeftHigh;
		case EFramework2DBiomeSlot::BridgePostRightLow:  return &Biome.BridgePostRightLow;
		case EFramework2DBiomeSlot::BridgePostRightHigh: return &Biome.BridgePostRightHigh;
		case EFramework2DBiomeSlot::WallFootLeft:        return &Biome.WallFootLeft;
		case EFramework2DBiomeSlot::WallFootLeftInner:   return &Biome.WallFootLeftInner;
		case EFramework2DBiomeSlot::WallFootRight:       return &Biome.WallFootRight;
		case EFramework2DBiomeSlot::WallFootRightInner:  return &Biome.WallFootRightInner;
		case EFramework2DBiomeSlot::PlatformCapLeft:     return &Biome.PlatformCapLeft;
		case EFramework2DBiomeSlot::PlatformCapMiddle:   return &Biome.PlatformCapMiddle;
		case EFramework2DBiomeSlot::PlatformCapRight:    return &Biome.PlatformCapRight;
		case EFramework2DBiomeSlot::GroundDeep:          return &Biome.GroundDeep;
		case EFramework2DBiomeSlot::BridgeCapLeft:       return &Biome.BridgeCapLeft;
		case EFramework2DBiomeSlot::BridgeCapMiddle:     return &Biome.BridgeCapMiddle;
		case EFramework2DBiomeSlot::BridgeCapRight:      return &Biome.BridgeCapRight;
		default:                                     return nullptr;
		}
	}

	inline int32 GetBiomeSlot(const FFramework2DBiome& Biome, EFramework2DBiomeSlot Slot)
	{
		// El 5x5 se lee sin tocarlo (Ref podria redimensionar su lista).
		const int32 S = (int32)Slot;
		if (S >= (int32)EFramework2DBiomeSlot::Ground5_00 && S <= (int32)EFramework2DBiomeSlot::Ground5_44)
		{
			const int32 I = S - (int32)EFramework2DBiomeSlot::Ground5_00;
			return Biome.Ground5.At(I / 5, I % 5);
		}
		const int32* Ref = BiomeSlotRef(const_cast<FFramework2DBiome&>(Biome), Slot);
		return Ref ? *Ref : -1;
	}

	/** Hueco del 5x5 de terreno por fila y columna (0..4). */
	inline EFramework2DBiomeSlot Biome5x5Slot(int32 Row, int32 Col)
	{
		return (EFramework2DBiomeSlot)((int32)EFramework2DBiomeSlot::Ground5_00 + FMath::Clamp(Row, 0, 4) * 5 + FMath::Clamp(Col, 0, 4));
	}

	/** Hueco del 3x3 de terreno (bBackground = false) o de fondo, por indice 0..8 en orden de lectura. */
	inline EFramework2DBiomeSlot Biome3x3Slot(bool bBackground, int32 Index)
	{
		const int32 Base = bBackground ? (int32)EFramework2DBiomeSlot::BackgroundTopLeft : (int32)EFramework2DBiomeSlot::GroundTopLeft;
		return (EFramework2DBiomeSlot)(Base + FMath::Clamp(Index, 0, 8));
	}
}

/**
 * RECETA del generador: como es el nivel. Se guarda en el Tile Map (cada mapa recuerda la suya)
 * y se edita en la pestana "Generar" del panel. Misma receta + misma semilla = mismo nivel.
 */
USTRUCT(BlueprintType)
struct FFramework2DProcGenSettings
{
	GENERATED_BODY()

	// Bioma del Tile Set con el que se construye (su Id). Si no existe, se usa el primero.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	int32 BiomeId = 0;

	// Otra semilla = otro nivel con los mismos ajustes.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	int32 Seed = 1;

	//---------------------- Relieve ----------------------

	// Cuantas alturas distintas puede tener el suelo (1 = llano).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Relief", meta = (ClampMin = "1", ClampMax = "16"))
	int32 Levels = 3;

	// Tiles que hay de una altura a la siguiente (lo alto de cada escalon).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Relief", meta = (ClampMin = "1", ClampMax = "16"))
	int32 LevelHeight = 3;

	// Tiles de suelo por debajo de la altura mas baja.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Relief", meta = (ClampMin = "1", ClampMax = "256"))
	int32 BaseHeight = 4;

	// Anchura minima y maxima (tiles) de cada tramo llano.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Relief", meta = (ClampMin = "1", ClampMax = "128"))
	int32 PlateauMinWidth = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Relief", meta = (ClampMin = "1", ClampMax = "256"))
	int32 PlateauMaxWidth = 10;

	// Cuantas alturas puede subir o bajar el suelo de golpe (en un acantilado).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Relief", meta = (ClampMin = "1", ClampMax = "15"))
	int32 MaxLevelStep = 1;

	// De los cambios de una altura, cuantos son rampa en vez de escalon (0..1). Necesita rampas en el bioma.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Relief", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float RampChance = 0.5f;

	// De las rampas, cuantas son suaves (0..1). Necesita rampas suaves en el bioma.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Relief", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float GentleRampChance = 0.5f;

	//---------------------- Agua ----------------------

	// Probabilidad de que un tramo llano tenga un foso (0..1).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Water", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float PitChance = 0.15f;

	// Profundidad de los fosos (tiles).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Water", meta = (ClampMin = "1", ClampMax = "16"))
	int32 PitDepth = 2;

	// De las hondonadas (fosos y valles), cuantas se llenan de agua (0..1). Necesita agua en el bioma.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Water", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float LakeChance = 0.7f;

	// Ancho maximo de un lago (tiles). En una hondonada mas ancha el agua baja hasta que solo
	// quedan llenas sus partes mas hondas (cada una, como mucho asi de ancha).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Water", meta = (ClampMin = "3", ClampMax = "1024"))
	int32 MaxLakeWidth = 24;

	// De los acantilados de 2 tiles o mas, cuantos tienen cascada (0..1). Necesita cascada en el bioma.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Water", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float WaterfallChance = 0.35f;

	//---------------------- Plataformas ----------------------

	// Probabilidad de que un tramo llano tenga una plataforma flotante encima (0..1).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Platforms", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float PlatformChance = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Platforms", meta = (ClampMin = "1", ClampMax = "64"))
	int32 PlatformMinLength = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Platforms", meta = (ClampMin = "1", ClampMax = "64"))
	int32 PlatformMaxLength = 6;

	//---------------------- Decoracion ----------------------

	// De cada casilla de suelo libre, la fraccion que lleva un adorno (0..1).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Decoration", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float DecorationDensity = 0.5f;

	// Casillas libres minimas entre dos adornos seguidos.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Decoration", meta = (ClampMin = "0", ClampMax = "16"))
	int32 DecorationSpacing = 0;

	// De las casillas del centro del terreno, cuantas usan una variante (0..1). Necesita variantes en el bioma.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Decoration", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float CenterVariantChance = 0.25f;

	//---------------------- Fondo ----------------------

	// Rellena la capa de fondo (si el bioma tiene fondo): detras del terreno y en colinas.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Background")
	bool bBackground = true;

	// Cuanto asoma el fondo por encima del terreno (tiles). 0 = solo detras (se ve al picar).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Background", meta = (ClampMin = "0", ClampMax = "64"))
	int32 BackgroundRise = 3;

	//---------------------- Bordes ----------------------

	// Muros de terreno en los bordes izquierdo y derecho (de abajo arriba del todo).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Edges")
	bool bEdgeWalls = false;

	//---------------------- Exteriores ----------------------

	// Forma del suelo: escalones (llanos a varias alturas) o lomas suaves.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Relief")
	EFramework2DReliefStyle ReliefStyle = EFramework2DReliefStyle::Steps;

	// Lomas: cuanto suben y bajan (0 = colinas largas y suaves, 1 = muy movido).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Relief", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float Roughness = 0.4f;

	// Islas flotantes con base de roca (0..1): probabilidad por cada tramo de unos 10 tiles.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Islands", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float IslandChance = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Islands", meta = (ClampMin = "2", ClampMax = "64"))
	int32 IslandMinWidth = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Islands", meta = (ClampMin = "2", ClampMax = "64"))
	int32 IslandMaxWidth = 9;

	// De los huecos que se pueden cruzar con un puente, cuantos lo llevan (0..1). Necesita puente en el bioma.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Islands", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float BridgeChance = 0.5f;

	// Objetos grandes: de cada sitio de suelo llano donde caben, la fraccion que lleva uno (0..1).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Objects", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float PropDensity = 0.35f;

	// Tiles libres minimos entre dos objetos grandes.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Objects", meta = (ClampMin = "0", ClampMax = "64"))
	int32 PropSpacing = 2;

	//---------------------- Capas ----------------------

	// Nombres de las capas que se rellenan. Si no existen se crean; su contenido se REEMPLAZA.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Layers")
	FName TerrainLayer = TEXT("Terrain");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Layers")
	FName BackgroundLayer = TEXT("Background");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Layers")
	FName WaterLayer = TEXT("Water");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Layers")
	FName DecorationLayer = TEXT("Decoration");

	// Objetos grandes de detras del terreno.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Layers")
	FName BehindLayer = TEXT("Behind");

	// Bordes naturales (delante del terreno, detras de la decoracion).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Layers")
	FName EdgeLayer = TEXT("Edges");
};

/** Lo que salio en una generacion (para el panel, Blueprint y las pruebas). */
USTRUCT(BlueprintType)
struct FFramework2DProcGenReport
{
	GENERATED_BODY()

	// False si no se pudo generar (falta el bioma, el centro del 3x3, el mapa es diminuto...).
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	bool bSuccess = false;

	// Alturas que caben de verdad en el mapa (puede ser menos de las pedidas).
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	int32 Levels = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	int32 Ramps = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	int32 Cliffs = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	int32 Pits = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	int32 Lakes = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	int32 Waterfalls = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	int32 Platforms = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	int32 Decorations = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	int32 Islands = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	int32 Bridges = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	int32 Props = 0;

	// Pies de pared colocados.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	int32 WallFeet = 0;

	// Por que no se pudo, o avisos ("solo caben 2 alturas en 20 tiles de alto"). En espanol.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	FString Message;
};
