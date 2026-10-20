// Copyright Chema Luque. Plugin Framework2DTerrain.

#include "Framework2DCollisionChunkComponent.h"

#include "PhysicsEngine/BodySetup.h"
#include "PhysicsEngine/BoxElem.h"
#include "Engine/CollisionProfile.h"

UFramework2DCollisionChunkComponent::UFramework2DCollisionChunkComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
	SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	SetGenerateOverlapEvents(false);
	SetCanEverAffectNavigation(false); // el terreno es vertical (plano XZ): el navmesh no aplica
	CastShadow = false;
	bUseAsOccluder = false;
}

void UFramework2DCollisionChunkComponent::SetBoxes(const TArray<FBox>& LocalBoxes)
{
	if (!ChunkBodySetup)
	{
		// Mismo truco que UBoxComponent: body setup propio, solo formas simples, sin cocinado.
		ChunkBodySetup = NewObject<UBodySetup>(this, NAME_None, RF_Transient);
		ChunkBodySetup->CollisionTraceFlag = CTF_UseSimpleAsComplex;
		ChunkBodySetup->bNeverNeedsCookedCollisionData = true;
	}

	ChunkBodySetup->AggGeom.BoxElems.Reset(LocalBoxes.Num());
	LocalBox = FBox(ForceInit);
	for (const FBox& B : LocalBoxes)
	{
		const FVector Size = B.GetSize();
		FKBoxElem Elem((float)Size.X, (float)Size.Y, (float)Size.Z); // dimensiones COMPLETAS
		Elem.Center = B.GetCenter();
		ChunkBodySetup->AggGeom.BoxElems.Add(Elem);
		LocalBox += B;
	}
	NumBoxes = LocalBoxes.Num();

	// Cambia el GUID y descarta datos viejos; con solo cajas no hay nada que cocinar.
	ChunkBodySetup->InvalidatePhysicsData();
	ChunkBodySetup->CreatePhysicsMeshes();

	UpdateBounds();
	if (IsRegistered())
	{
		// Destruye y vuelve a crear el cuerpo fisico con las cajas nuevas (o ninguno si esta vacio).
		RecreatePhysicsState();
	}
}

UBodySetup* UFramework2DCollisionChunkComponent::GetBodySetup()
{
	return ChunkBodySetup;
}

FBoxSphereBounds UFramework2DCollisionChunkComponent::CalcBounds(const FTransform& LocalToWorld) const
{
	if (NumBoxes == 0 || !LocalBox.IsValid)
	{
		return FBoxSphereBounds(LocalToWorld.GetLocation(), FVector::ZeroVector, 0.0f);
	}
	return FBoxSphereBounds(LocalBox).TransformBy(LocalToWorld);
}

bool UFramework2DCollisionChunkComponent::ShouldCreatePhysicsState() const
{
	// Chunk vacio (todo aire): sin cuerpo fisico, para no crear actores de fisica sin formas.
	return NumBoxes > 0 && ChunkBodySetup != nullptr && Super::ShouldCreatePhysicsState();
}
