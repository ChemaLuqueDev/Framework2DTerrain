// Copyright Chema Luque. Plugin Framework2DTerrain.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Framework2DCharacter.generated.h"

class UFramework2DTerrainDeformerComponent;

/**
 * AFramework2DCharacter
 * =================================================================
 * Personaje base (Paper Character) que deforma el terreno con el CLIC IZQUIERDO, delante de el.
 *
 * Ponlo como padre de tu personaje: abre su Blueprint > Class Settings > Parent Class >
 * "Framework2D Character". No cambia nada de lo tuyo (movimiento, camara, sprite, componentes):
 * solo le anade el componente Terrain Deformer. Seleccionalo en la lista de componentes y ajusta
 * sus parametros en Details (radio, alcance, dano, golpes por segundo, teclas...).
 *
 * La explosion (bombas) va aparte: AFramework2DTerrainWorld::Explode.
 */
UCLASS(Blueprintable, meta = (DisplayName = "Framework2D Character"))
class FRAMEWORK2DTERRAIN_API AFramework2DCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	AFramework2DCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/** Deforma el terreno delante del personaje (clic izquierdo). Sus parametros, en Details. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Framework2D")
	TObjectPtr<UFramework2DTerrainDeformerComponent> TerrainDeformer;
};
