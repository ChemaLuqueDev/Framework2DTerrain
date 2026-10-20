// Copyright Chema Luque. Plugin Framework2DTerrain.

#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "Framework2DCollisionChunkComponent.generated.h"

class UBodySetup;

/**
 * UFramework2DCollisionChunkComponent
 * =================================================================
 * Colision de UN trozo (chunk) del terreno. El actor de terreno crea una rejilla de estos
 * al empezar y, cuando picas, solo reconstruye los chunks tocados.
 *
 * Por que cajas y no una malla: la colision por malla (ProceduralMesh) hay que "cocinarla"
 * entera cada vez que cambia, y eso da tirones con mundos grandes. Aqui cada chunk es una
 * union de cajas (las del greedy-mesh) y las cajas NO necesitan cocinado: reconstruir un
 * chunk es practicamente gratis y el personaje se apoya en ellas igual que en una malla.
 *
 * No se dibuja (no tiene scene proxy): solo aporta fisica y trazas.
 */
UCLASS(ClassGroup = (Framework2D))
class FRAMEWORK2DTERRAIN_API UFramework2DCollisionChunkComponent : public UPrimitiveComponent
{
	GENERATED_BODY()

public:
	UFramework2DCollisionChunkComponent(const FObjectInitializer& ObjectInitializer);

	/** Sustituye la colision del chunk por estas cajas (en espacio LOCAL del componente). */
	void SetBoxes(const TArray<FBox>& LocalBoxes);

	int32 GetNumBoxes() const { return NumBoxes; }

	//~ UPrimitiveComponent
	virtual UBodySetup* GetBodySetup() override;
	virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;
	virtual bool ShouldCreatePhysicsState() const override;

private:
	UPROPERTY(Transient)
	TObjectPtr<UBodySetup> ChunkBodySetup;

	FBox LocalBox = FBox(ForceInit);
	int32 NumBoxes = 0;
};
