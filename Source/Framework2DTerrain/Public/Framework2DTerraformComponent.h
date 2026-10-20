// Copyright Chema Luque. Plugin Framework2DTerrain.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Framework2DTerrainTypes.h"
#include "Framework2DTerraformComponent.generated.h"

class AFramework2DTerrainWorld;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFramework2DOnInventoryChanged);

/**
 * UFramework2DTerraformComponent
 * =================================================================
 * La "varita" estilo KYORA, lista para poner en tu personaje:
 *   - MineToward: lanza un rayo desde el dueno hacia un punto, pica lo PRIMERO que toca
 *     (con la dureza de cada material) y GUARDA lo picado en el inventario.
 *   - PlaceToward: coloca el material seleccionado gastando inventario (terraformar).
 *
 * Llamalos cada frame mientras el boton este pulsado (pasando DeltaSeconds): el dano y
 * las celdas colocadas se reparten por segundo, no por clic.
 *
 * Prefijo U = UObject. Es un ActorComponent: anadelo en el Blueprint de tu personaje.
 */
UCLASS(ClassGroup = (Framework2D), meta = (BlueprintSpawnableComponent))
class FRAMEWORK2DTERRAIN_API UFramework2DTerraformComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFramework2DTerraformComponent();

	/** Terreno sobre el que actua. Si lo dejas vacio, usa el primero que haya en el nivel. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Terraform")
	TObjectPtr<AFramework2DTerrainWorld> Terrain = nullptr;

	/** Alcance maximo (cm) desde el dueno. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Terraform", meta = (ClampMin = "0.0"))
	float Range = 700.0f;

	/** Radio (cm) de la punta al picar. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Terraform", meta = (ClampMin = "0.0"))
	float MineRadius = 14.0f;

	/** Dano por segundo. Se compara con la Hardness de cada material (Dirt 3, Stone 8...). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Terraform", meta = (ClampMin = "0.0"))
	float MineDamagePerSecond = 40.0f;

	/** Radio (cm) al colocar. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Terraform", meta = (ClampMin = "0.0"))
	float PlaceRadius = 12.0f;

	/** Celdas por segundo que puede colocar. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Terraform", meta = (ClampMin = "0.0"))
	float PlaceCellsPerSecond = 500.0f;

	/** Capacidad total del inventario (en celdas). 0 = sin limite. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Terraform", meta = (ClampMin = "0"))
	int32 Capacity = 0;

	/** Modo creativo: colocar no gasta inventario y puedes elegir cualquier material del tileset. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Terraform")
	bool bInfiniteMaterials = false;

	/** No coloca terreno encima de personajes (evita dejarlos atrapados). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Terraform")
	bool bAvoidPawnsWhenPlacing = true;

	/** Material que se coloca. Se elige solo con lo primero que piques (o escribelo a mano). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Terraform")
	FName SelectedMaterial = NAME_None;

	/** Lo que llevas: material -> celdas. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Framework2D|Terraform")
	TMap<FName, int32> Inventory;

	/** Se emite cuando cambia el inventario o el material seleccionado. */
	UPROPERTY(BlueprintAssignable, Category = "Framework2D|Terraform")
	FFramework2DOnInventoryChanged OnInventoryChanged;

	/** Pica hacia TargetWorld (rayo desde el dueno). Llamalo cada frame con el boton pulsado. */
	UFUNCTION(BlueprintCallable, Category = "Framework2D|Terraform")
	FFramework2DDigResult MineToward(FVector TargetWorld, float DeltaSeconds);

	/** Coloca el material seleccionado en TargetWorld (recortado al alcance). Devuelve celdas colocadas. */
	UFUNCTION(BlueprintCallable, Category = "Framework2D|Terraform")
	int32 PlaceToward(FVector TargetWorld, float DeltaSeconds);

	/** Pasa al siguiente (+1) o anterior (-1) material del inventario. */
	UFUNCTION(BlueprintCallable, Category = "Framework2D|Terraform")
	void SelectNextMaterial(int32 Direction = 1);

	/** Celdas que llevas de un material. */
	UFUNCTION(BlueprintPure, Category = "Framework2D|Terraform")
	int32 GetAmount(FName Material) const;

	/** Celdas totales en el inventario. */
	UFUNCTION(BlueprintPure, Category = "Framework2D|Terraform")
	int32 GetTotalStored() const;

	/** Mete material en el inventario (respeta Capacity). Devuelve lo que cupo. */
	UFUNCTION(BlueprintCallable, Category = "Framework2D|Terraform")
	int32 AddMaterial(FName Material, int32 Count);

	/** Gasta material. Devuelve false (y no gasta nada) si no hay suficiente. */
	UFUNCTION(BlueprintCallable, Category = "Framework2D|Terraform")
	bool ConsumeMaterial(FName Material, int32 Count);

	/** El terreno en uso (busca uno en el nivel si Terrain esta vacio). */
	UFUNCTION(BlueprintCallable, Category = "Framework2D|Terraform")
	AFramework2DTerrainWorld* GetTerrain();

private:
	float MineAccumulator = 0.0f;
	float PlaceAccumulator = 0.0f;

	// Recorta TargetWorld al alcance desde el dueno.
	FVector ClampToRange(const FVector& Origin, const FVector& TargetWorld) const;
};
