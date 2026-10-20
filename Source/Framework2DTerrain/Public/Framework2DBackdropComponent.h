// Copyright Chema Luque. Plugin Framework2DTerrain.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "Framework2DProcGenTypes.h"
#include "Framework2DBackdropComponent.generated.h"

class UMaterialInterface;
class UMaterialInstanceDynamic;

/**
 * UFramework2DBackdropComponent
 * =================================================================
 * Los FONDOS PARALLAX del terreno: un plano por capa (cielo, montanas, bosque lejano...)
 * detras de todas las capas del Tile Map. Cada frame, DESPUES de que se mueva la camara
 * (grupo PostUpdateWork, asi no tiembla), recoloca las imagenes segun su Parallax: 0 = quietas
 * en la pantalla, 1 = pegadas al nivel. Funciona en el editor (camara del viewport) y en juego.
 *
 * Lo crea y lo configura el terreno (AFramework2DTerrainWorld); no hace falta tocarlo.
 */
UCLASS(ClassGroup = (Framework2D))
class FRAMEWORK2DTERRAIN_API UFramework2DBackdropComponent : public UProceduralMeshComponent
{
	GENERATED_BODY()

public:
	UFramework2DBackdropComponent(const FObjectInitializer& ObjectInitializer);

	/**
	 * Rehace las capas. CellSize = cm por pixel del terreno; LevelSize = ancho y alto del nivel
	 * (cm, en el plano XZ local del actor); TileSize = cm por tile; DepthY = Y local de la capa
	 * mas cercana del fondo (las demas van detras).
	 */
	void SetLayers(const TArray<FFramework2DBackdropLayer>& InLayers, UMaterialInterface* InMaterial, float InCellSize,
		const FVector2D& InLevelSize, float InTileSize, float InDepthY);

	/** Quita todas las capas. */
	void ClearLayers();

	/** Recoloca las capas para una camara en esa posicion (mundo). Lo hace solo cada frame. */
	void UpdateForCamera(const FVector& CameraWorldLocation);

	int32 GetNumBackdropLayers() const { return Layers.Num(); }

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	TArray<FFramework2DBackdropLayer> Layers;
	TArray<FIntPoint> TextureSizes;

	UPROPERTY(Transient, NonTransactional)
	TArray<TObjectPtr<UMaterialInstanceDynamic>> LayerMIDs;

	float CellSize = 4.0f;
	FVector2D LevelSize = FVector2D::ZeroVector;
	float TileSize = 64.0f;
	float DepthY = -50.0f;
	FVector LastCamera = FVector(TNumericLimits<float>::Max());

	bool FindCameraLocation(FVector& OutLocation) const;
	void BuildLayerGeometry(int32 Index, const FVector& CameraLocal, TArray<FVector>& OutVerts, TArray<FVector2D>& OutUVs) const;
};
