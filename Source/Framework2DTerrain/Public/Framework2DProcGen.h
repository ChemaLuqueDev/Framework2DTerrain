// Copyright Chema Luque. Plugin Framework2DTerrain.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Framework2DProcGenTypes.h"
#include "Framework2DProcGen.generated.h"

class UFramework2DTileSet;
class UFramework2DTileMapAsset;

/** Que hay en lo alto de una columna del relieve generado. */
enum class EFramework2DProcGenSlope : uint8
{
	None,           // llano o acantilado: la columna acaba en un tile entero
	Up,             // rampa de 45 grados que sube hacia la derecha ( / )
	Down,           // rampa de 45 grados que baja hacia la derecha ( \ )
	GentleUpLow,    // rampa suave que sube: mitad baja
	GentleUpHigh,   // rampa suave que sube: mitad alta
	GentleDownHigh, // rampa suave que baja: mitad alta
	GentleDownLow   // rampa suave que baja: mitad baja
};

/**
 * Resultado de una generacion, sin tocar ningun asset. Rejillas de Width x Height valores de
 * celda (indice = Y * Width + X, Y = 0 ARRIBA, -1 = vacio), una por capa, mas el relieve por
 * columna (en filas contadas DESDE ABAJO) para herramientas y pruebas.
 */
struct FRAMEWORK2DTERRAIN_API FFramework2DProcGenOutput
{
	int32 Width = 0;
	int32 Height = 0;

	TArray<int32> Terrain;
	TArray<int32> Background;
	TArray<int32> Water;      // agua y cascadas
	TArray<int32> Decoration;
	TArray<int32> Edges;      // bordes naturales (remates de arriba y de abajo)
	TArray<int32> Behind;     // capa de detras: el agua del lecho y la de detras de las orillas (los objetos grandes van aparte)

	// Objetos grandes colocados (con su capa ya puesta) y fondos parallax del bioma.
	TArray<FFramework2DPropInstance> Props;
	TArray<FFramework2DBackdropLayer> Backdrops;

	// Por columna X:
	TArray<int32> FillHeight;  // filas de terreno macizo desde abajo (sin contar la rampa ni las plataformas)
	TArray<uint8> Slope;       // EFramework2DProcGenSlope del tile que va justo encima del macizo (fila FillHeight)
	TArray<int32> WaterTop;    // filas desde abajo hasta donde llega el lago (0 = sin lago en esa columna)

	// Que se uso de cada cosa y avisos.
	FFramework2DProcGenReport Report;

	int32 Index(int32 X, int32 Y) const { return Y * Width + X; }
	/** Fila del mapa (Y = 0 arriba) de la fila R contada desde abajo. */
	int32 RowFromBottom(int32 R) const { return Height - 1 - R; }
};

/**
 * GENERADOR PROCEDURAL DE MAPAS
 * =================================================================
 * Construye un nivel de plataformas de lado (alturas, rampas, fosos, lagos, cascadas,
 * plataformas flotantes, fondo y decoracion) con las piezas de un BIOMA y los ajustes de una
 * RECETA. Determinista: misma receta + misma semilla = mismo nivel. Cada parte usa su propio
 * flujo aleatorio, asi que tocar la decoracion no mueve el relieve.
 *
 * Desde el editor: modo Framework2D Tiles > pestana "Generar". Desde Blueprint: Generate Map
 * (sobre un Tile Map) o Generate Procedural Level (sobre el terreno, en juego).
 */
UCLASS()
class FRAMEWORK2DTERRAIN_API UFramework2DProcGenLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Genera un nivel de Width x Height tiles en Out, sin tocar ningun asset. Set (opcional)
	 * sirve para descartar piezas que ya no existen (flipbook o generador borrado). Devuelve
	 * Out.Report.bSuccess.
	 */
	static bool Generate(const UFramework2DTileSet* Set, const FFramework2DBiome& Biome, const FFramework2DProcGenSettings& Settings,
		int32 Width, int32 Height, FFramework2DProcGenOutput& Out);

	/**
	 * Escribe una generacion en el mapa: busca las capas por nombre (las crea si faltan, con sus
	 * banderas: Fondo de fondo, Agua sin colision ni rotura, Decoracion sin colision), REEMPLAZA
	 * su contenido entero y borra la colision pintada (era del nivel anterior). Las demas capas
	 * no se tocan. No abre transacciones (el editor lo envuelve en un paso de deshacer).
	 * Out.Width/Height deben coincidir con el mapa.
	 */
	static void ApplyToMap(UFramework2DTileMapAsset* Map, const FFramework2DProcGenSettings& Settings, const FFramework2DProcGenOutput& Out);

	/**
	 * Genera un nivel en el Tile Map con SU receta (ProcGen) y el bioma de su Tile Set, y lo
	 * escribe en sus capas. Reemplaza las capas Terreno, Fondo, Agua y Decoracion.
	 */
	UFUNCTION(BlueprintCallable, Category = "Framework2D|Procedural")
	static FFramework2DProcGenReport GenerateMap(UFramework2DTileMapAsset* Map);

	/** Como Generate Map, pero con otra receta (la del mapa no cambia). */
	UFUNCTION(BlueprintCallable, Category = "Framework2D|Procedural")
	static FFramework2DProcGenReport GenerateMapWithSettings(UFramework2DTileMapAsset* Map, const FFramework2DProcGenSettings& Settings);

	/** Que le falta al bioma para poder generar. Vacio = listo. */
	UFUNCTION(BlueprintPure, Category = "Framework2D|Procedural")
	static FText GetBiomeProblem(const UFramework2DTileSet* Set, const FFramework2DBiome& Biome);

	/** True si el valor sirve como pieza (existe en el Tile Set: tile, flipbook o generador). Sin Set: cualquier valor >= 0. */
	static bool IsUsablePiece(const UFramework2DTileSet* Set, int32 Value);
};
