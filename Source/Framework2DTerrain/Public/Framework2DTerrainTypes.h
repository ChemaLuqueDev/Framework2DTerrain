// Copyright Chema Luque. Plugin Framework2DTerrain.

#pragma once

#include "CoreMinimal.h"
#include "Framework2DTerrainTypes.generated.h"

/**
 * Un MATERIAL de terreno (tierra, piedra, madera...). Se definen en el TileSet y cada tile
 * dice de que material es. Decide como se rompe, si colisiona y si se puede recoger.
 */
USTRUCT(BlueprintType)
struct FFramework2DMaterial
{
	GENERATED_BODY()

	// Nombre con el que lo eliges en los tiles y lo usas desde Blueprint ("Dirt", "Stone"...).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	FName Name = NAME_None;

	// Color de las celdas que no tienen dibujo (por ejemplo las que coloca el jugador si el
	// material no tiene tile de relleno). Las celdas horneadas usan el dibujo del tile.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	FColor Color = FColor::White;

	// Variacion de color por celda para que el relleno sin dibujo no se vea plano. 0 = plano.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D", meta = (ClampMin = "0", ClampMax = "80"))
	int32 ColorVariance = 12;

	// Si true, el personaje choca con el. False para decoracion (hierba, plantas...).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	bool bCollides = true;

	// Dano que necesita una celda para romperse al picar (MineAt / varita / Explode).
	// 0 o 1 = se rompe al primer golpe. 255 = durisimo.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D", meta = (ClampMin = "0", ClampMax = "255"))
	int32 Hardness = 3;

	// Si true, nada lo rompe (ni picar, ni Dig, ni explosiones). Bordes del nivel.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	bool bIndestructible = false;

	// Si true, lo picado va al inventario de quien pica (y luego se puede colocar).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	bool bCollectable = true;

	// Si true, sus celdas dibujan el borde oscuro donde tocan aire (el corte del agujero).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	bool bDrawEdge = true;
};

/** Cuanto se ha recogido de UN material (fila del resultado de picar). */
USTRUCT(BlueprintType)
struct FFramework2DMaterialAmount
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	FName Material = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	int32 Count = 0;
};

/**
 * Resultado de un golpe al terreno (MineAt / Dig / Explode). Lo devuelve MineAt y lo emite
 * el evento OnTerrainMined, para enganchar sonido, particulas o inventario.
 */
USTRUCT(BlueprintType)
struct FFramework2DDigResult
{
	GENERATED_BODY()

	// Celdas que se han roto de verdad en este golpe.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	int32 CellsRemoved = 0;

	// Celdas alcanzadas: rotas o que han sumado dano (con la dureza, romper puede llevar varios golpes).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	int32 CellsHit = 0;

	// Material recogido (solo materiales con bCollectable).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	TArray<FFramework2DMaterialAmount> Collected;

	// Punto del mundo donde se golpeo.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D")
	FVector Location = FVector::ZeroVector;
};

/** Que hacen los pixeles que saltan al romper el terreno. */
UENUM(BlueprintType)
enum class EFramework2DDebrisMode : uint8
{
	// Sin escombros.
	None        UMETA(DisplayName = "No debris"),

	// Saltan hacia fuera con gravedad y se desvanecen.
	Burst       UMETA(DisplayName = "Burst"),

	// Vuelan hacia quien pica (como la varita de KYORA). Sin recolector, salpican.
	ToCollector UMETA(DisplayName = "Towards the digger")
};

/**
 * Colision de un tile. Se elige por tile en el TileSet (vale en todo el mapa) y, celda a
 * celda, con el pincel de COLISION del modo Framework2D Tiles (gana al del TileSet).
 * Las formas (Bloque, mitades, rampas, plataforma) son colision "a medida": no dependen del
 * dibujo, asi que sirven tambien para paredes invisibles. Si el jugador pica un pixel, ese
 * pixel vuelve a la colision automatica (lo roto deja de chocar).
 */
UENUM(BlueprintType)
enum class EFramework2DCollisionShape : uint8
{
	// La de siempre: chocan los pixeles del dibujo cuyo material colisiona.
	Auto        UMETA(DisplayName = "Automatic"),
	// Nada de este tile choca.
	None        UMETA(DisplayName = "No collision"),
	// Chocan todos los pixeles del dibujo, aunque el material no colisione (p. ej. Decoration).
	Pixels      UMETA(DisplayName = "Drawing pixels"),
	// El tile entero, tenga dibujo o no (pared invisible).
	Full        UMETA(DisplayName = "Full block"),
	TopHalf     UMETA(DisplayName = "Top half"),
	BottomHalf  UMETA(DisplayName = "Bottom half"),
	LeftHalf    UMETA(DisplayName = "Left half"),
	RightHalf   UMETA(DisplayName = "Right half"),
	// Rampa que sube hacia la derecha (triangulo abajo-derecha).
	SlopeUp     UMETA(DisplayName = "Rising ramp"),
	// Rampa que baja hacia la derecha (triangulo abajo-izquierda).
	SlopeDown   UMETA(DisplayName = "Falling ramp"),
	// Franja fina en la parte de arriba del tile (un cuarto del alto).
	Platform    UMETA(DisplayName = "Thin platform")
};

namespace Framework2D
{
	/** Materiales con los que nace un TileSet nuevo: Dirt, Stone, Wood, Sand, Decoration, Bedrock. */
	FRAMEWORK2DTERRAIN_API TArray<FFramework2DMaterial> MakeDefaultMaterials();

	/**
	 * Valores de celda de un tilemap:
	 *   -1                                    vacio
	 *   0 .. FlipbookTileBase-1               tile de un atlas: (Id de la pagina << 20) | numero
	 *                                         de tile en esa pagina. La pagina 0 es el atlas
	 *                                         principal, asi que los mapas de antes no cambian.
	 *   FlipbookTileBase .. GeneratorTileBase-1   flipbook (base + Id del flipbook)
	 *   >= GeneratorTileBase                  generador de vegetacion (base + Id del generador)
	 */
	constexpr int32 FlipbookTileBase = 1 << 28;
	constexpr int32 GeneratorTileBase = 1 << 29;
	constexpr int32 AtlasPageShift = 20;
	constexpr int32 AtlasLocalMask = (1 << AtlasPageShift) - 1;
	constexpr int32 MaxAtlasPages = FlipbookTileBase >> AtlasPageShift; // 256

	inline bool IsAtlasTileValue(int32 Value) { return Value >= 0 && Value < FlipbookTileBase; }
	inline int32 MakeTileValue(int32 PageId, int32 LocalTile) { return (PageId << AtlasPageShift) | (LocalTile & AtlasLocalMask); }
	inline int32 TilePageOf(int32 Value) { return Value >> AtlasPageShift; }
	inline int32 TileLocalOf(int32 Value) { return Value & AtlasLocalMask; }

	inline bool IsFlipbookValue(int32 Value) { return Value >= FlipbookTileBase && Value < GeneratorTileBase; }
	inline int32 MakeFlipbookValue(int32 FlipbookId) { return FlipbookTileBase + FlipbookId; }
	inline int32 FlipbookIdFromValue(int32 Value) { return Value - FlipbookTileBase; }

	inline bool IsGeneratorValue(int32 Value) { return Value >= GeneratorTileBase; }
	inline int32 MakeGeneratorValue(int32 GeneratorId) { return GeneratorTileBase + GeneratorId; }
	inline int32 GeneratorIdFromValue(int32 Value) { return Value - GeneratorTileBase; }

	/** True si la forma es "a medida" (rasteriza su propia colision, sin mirar el dibujo). */
	inline bool IsCustomShape(EFramework2DCollisionShape Shape)
	{
		return Shape >= EFramework2DCollisionShape::Full;
	}

	/**
	 * Forma a medida rasterizada: true si el pixel (Cx, Cy) de un tile de Size x Size pixeles
	 * (Cy = 0 arriba) es solido. Solo para formas a medida (IsCustomShape).
	 */
	inline bool ShapeCovers(EFramework2DCollisionShape Shape, int32 Cx, int32 Cy, int32 Size)
	{
		const int32 Half = FMath::Max(1, Size / 2);
		switch (Shape)
		{
		case EFramework2DCollisionShape::Full:       return true;
		case EFramework2DCollisionShape::TopHalf:    return Cy < Half;
		case EFramework2DCollisionShape::BottomHalf: return Cy >= Size - Half;
		case EFramework2DCollisionShape::LeftHalf:   return Cx < Half;
		case EFramework2DCollisionShape::RightHalf:  return Cx >= Size - Half;
		case EFramework2DCollisionShape::SlopeUp:    return Cy >= Size - 1 - Cx;
		case EFramework2DCollisionShape::SlopeDown:  return Cy >= Cx;
		case EFramework2DCollisionShape::Platform:   return Cy < FMath::Max(1, Size / 4);
		default:                                     return false;
		}
	}
}
