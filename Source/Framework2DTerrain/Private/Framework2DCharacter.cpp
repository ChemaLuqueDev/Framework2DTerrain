// Copyright Chema Luque. Plugin Framework2DTerrain.

#include "Framework2DCharacter.h"

#include "Framework2DTerrainDeformerComponent.h"

AFramework2DCharacter::AFramework2DCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Solo se anade el componente: el resto de valores son los de Paper Character, para que al
	// ponerlo como padre de un personaje que ya existe no cambie nada de como se mueve o se ve.
	TerrainDeformer = CreateDefaultSubobject<UFramework2DTerrainDeformerComponent>(TEXT("TerrainDeformer"));
}
