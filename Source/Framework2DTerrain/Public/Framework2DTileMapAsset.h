// Copyright Chema Luque. Plugin Framework2DTerrain.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Framework2DTerrainTypes.h"
#include "Framework2DProcGenTypes.h"
#include "Framework2DTileMapAsset.generated.h"

class UFramework2DTileSet;

/**
 * Una capa del tilemap. Tiles es una rejilla plana: indice = Y*Width + X (Y=0 arriba).
 * Valores: -1 = vacio, 0.. = tile del atlas, >= Framework2D::FlipbookTileBase = flipbook.
 *
 * Cada capa se dibuja en su propio plano, separada de las demas en profundidad (Layer
 * Separation del terreno), como las capas de los tilemaps de Unreal.
 */
USTRUCT(BlueprintType)
struct FFramework2DTileLayer
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Framework2D")
	FName Name = TEXT("Layer");

	// Las capas ocultas no se hornean (ni se ven, ni colisionan).
	UPROPERTY(EditAnywhere, Category = "Framework2D")
	bool bVisible = true;

	// Capa de FONDO (pared trasera): se ve oscurecida, no colisiona ni se pica. Ideal para cuevas.
	UPROPERTY(EditAnywhere, Category = "Framework2D")
	bool bBackground = false;

	// Si false, esta capa no choca nunca (decoracion delante o detras del jugador).
	UPROPERTY(EditAnywhere, Category = "Framework2D", meta = (EditCondition = "!bBackground"))
	bool bCollides = true;

	// Si false, picar y explotar no la rompen (decoracion intocable).
	UPROPERTY(EditAnywhere, Category = "Framework2D", meta = (EditCondition = "!bBackground"))
	bool bBreakable = true;

	UPROPERTY()
	TArray<int32> Tiles;
};

/**
 * UFramework2DTileMapAsset
 * =================================================================
 * Tu nivel: capas de tiles de un TileSet. Se crea con:
 *   Content Browser -> Add -> Miscellaneous -> Data Asset -> Framework2DTileMapAsset
 * y se pinta en el viewport con el modo "Framework2D Tiles".
 *
 * Las capas van de ATRAS (indice 0) a DELANTE: cada una en su plano, mas cerca de la camara.
 */
UCLASS(BlueprintType)
class FRAMEWORK2DTERRAIN_API UFramework2DTileMapAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UFramework2DTileMapAsset();

	// Tileset del que salen los tiles (y sus materiales).
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D")
	TObjectPtr<UFramework2DTileSet> TileSet = nullptr;

	// Ancho del nivel EN TILES. Al cambiarlo se conserva lo pintado que quepa.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D", meta = (ClampMin = "1", ClampMax = "1024"))
	int32 Width = 64;

	// Alto del nivel EN TILES.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D", meta = (ClampMin = "1", ClampMax = "1024"))
	int32 Height = 32;

	// Capas, de atras (0) a delante.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Framework2D", meta = (TitleProperty = "Name"))
	TArray<FFramework2DTileLayer> Layers;

	/**
	 * Colision pintada celda a celda con el pincel de colision (una por tile del mapa, comun a
	 * todas las capas). Valor = EFramework2DCollisionShape; Auto (0) = lo que diga el TileSet.
	 * Vacia hasta que se pinta la primera.
	 */
	UPROPERTY()
	TArray<uint8> CollisionOverrides;

	// Receta del generador procedural (modo Framework2D Tiles > pestana "Generar"): alturas,
	// rampas, agua, decoracion, semilla... Cada mapa recuerda la suya.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Procedural")
	FFramework2DProcGenSettings ProcGen;

	// Fondos parallax del nivel (cielo, montanas...), de atras a delante. Los pone el generador
	// (los del bioma) y tambien se pueden editar aqui a mano.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Background", meta = (TitleProperty = "Name"))
	TArray<FFramework2DBackdropLayer> Backdrops;

	// Objetos grandes colocados (arboles, rocas...). Los pone el generador procedural.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Objects")
	TArray<FFramework2DPropInstance> PropInstances;

	/**
	 * Cambia el tamano del mapa (en tiles) conservando lo pintado que quepa, anclado arriba a la
	 * izquierda como al cambiar Width/Height en Details. La colision pintada sigue a sus tiles.
	 */
	UFUNCTION(BlueprintCallable, Category = "Framework2D")
	void Resize(int32 NewWidth, int32 NewHeight);

	/** Indice de la primera capa con ese nombre (sin distinguir mayusculas). INDEX_NONE si no hay. */
	UFUNCTION(BlueprintPure, Category = "Framework2D")
	int32 FindLayerByName(FName LayerName) const;

	/** Valor en (Capa, X, Y) tal como se hornea: -1 si esta vacio, fuera de rango o la capa esta oculta. */
	UFUNCTION(BlueprintPure, Category = "Framework2D")
	int32 At(int32 Layer, int32 X, int32 Y) const;

	/** Valor en (Capa, X, Y) aunque la capa este oculta (para editar). -1 si vacio o fuera. */
	int32 GetTile(int32 Layer, int32 X, int32 Y) const;

	/** Pone un valor (-1 = borrar). Devuelve true si algo cambio. */
	bool SetTile(int32 Layer, int32 X, int32 Y, int32 TileIndex);

	/** Rellena el rectangulo [X0,Y0]-[X1,Y1] (incluidos). Devuelve true si algo cambio. */
	bool FillRect(int32 Layer, int32 X0, int32 Y0, int32 X1, int32 Y1, int32 TileIndex);

	/** Bote de pintura: rellena la zona contigua del mismo valor. Devuelve el rectangulo tocado. */
	bool FloodFill(int32 Layer, int32 X, int32 Y, int32 TileIndex, FIntRect& OutChanged);

	/** Colision pintada en el tile (X, Y). Auto si no hay o fuera de rango. */
	EFramework2DCollisionShape GetCollisionOverride(int32 X, int32 Y) const;

	/** Pinta la colision de un tile (Auto = quitarla). Devuelve true si algo cambio. */
	bool SetCollisionOverride(int32 X, int32 Y, EFramework2DCollisionShape Shape);

	/** True si hay alguna colision pintada. */
	bool HasCollisionOverrides() const;

	/** Anade una capa encima de todas y devuelve su indice. */
	int32 AddLayer(FName Name);

	/** Quita una capa. Siempre queda al menos una. */
	void RemoveLayer(int32 Layer);

	/** Mueve una capa a otra posicion (0 = la de mas atras). Devuelve true si se movio. */
	bool MoveLayer(int32 From, int32 To);

	int32 GetNumLayers() const { return Layers.Num(); }

	/** Asegura que la capa existe y tiene Width*Height celdas. */
	void EnsureLayer(int32 Layer);

	/** Cualquier valor de celda que apunte a ese flipbook pasa a vacio (al borrar el flipbook). */
	int32 ClearFlipbook(int32 FlipbookId);

	/** Las celdas con tiles de esa pagina de atlas pasan a vacio (al quitar la pagina). */
	int32 ClearAtlasPage(int32 PageId);

	/** Las celdas con ese generador pasan a vacio (al borrar el generador). */
	int32 ClearGenerator(int32 GeneratorId);

	/** Vacia toda celda cuyo valor cumpla la condicion. Devuelve cuantas. */
	int32 ClearValues(TFunctionRef<bool(int32)> Predicate);

#if WITH_EDITOR
	// Al cambiar Width/Height re-mapea las capas (y la colision pintada) por (x,y).
	virtual void PreEditChange(FProperty* PropertyAboutToChange) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	// Tamano antes de editar Width/Height (para re-mapear al redimensionar).
	int32 OldWidth = 0;
	int32 OldHeight = 0;
};
