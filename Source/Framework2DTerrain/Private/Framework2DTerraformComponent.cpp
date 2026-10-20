// Copyright Chema Luque. Plugin Framework2DTerrain.

#include "Framework2DTerraformComponent.h"

#include "Framework2DTerrainWorld.h"
#include "EngineUtils.h" // TActorIterator
#include "GameFramework/Actor.h"

UFramework2DTerraformComponent::UFramework2DTerraformComponent()
{
	PrimaryComponentTick.bCanEverTick = false; // lo mueve quien lo usa (input), no el tick
}

AFramework2DTerrainWorld* UFramework2DTerraformComponent::GetTerrain()
{
	if (!Terrain && GetWorld())
	{
		for (TActorIterator<AFramework2DTerrainWorld> It(GetWorld()); It; ++It)
		{
			Terrain = *It;
			break;
		}
	}
	return Terrain;
}

FVector UFramework2DTerraformComponent::ClampToRange(const FVector& Origin, const FVector& TargetWorld) const
{
	const FVector Delta = TargetWorld - Origin;
	return Origin + Delta.GetClampedToMaxSize(FMath::Max(0.0f, Range));
}

FFramework2DDigResult UFramework2DTerraformComponent::MineToward(FVector TargetWorld, float DeltaSeconds)
{
	FFramework2DDigResult Result;
	AFramework2DTerrainWorld* T = GetTerrain();
	AActor* Owner = GetOwner();
	if (!T || !Owner) { return Result; }

	// Rayo por celdas: la varita pica lo PRIMERO que encuentra, no lo que hay detras. Las capas
	// que no se rompen no la paran (se ven, pero no se pueden picar).
	const FVector Origin = Owner->GetActorLocation();
	const FVector End = ClampToRange(Origin, TargetWorld);
	FVector Hit;
	FName HitMaterial;
	if (!T->TraceBreakableTerrain(Origin, End, Hit, HitMaterial))
	{
		return Result; // apuntando al aire
	}

	// El dano se reparte por segundo; solo se aplica en unidades enteras.
	MineAccumulator += FMath::Max(0.0f, MineDamagePerSecond) * DeltaSeconds;
	const int32 Damage = FMath::FloorToInt(MineAccumulator);
	if (Damage <= 0) { return Result; }
	MineAccumulator -= (float)Damage;

	// Centrar la punta media celda DENTRO del terreno (el impacto esta justo en su borde).
	const FVector Dir = (End - Origin).GetSafeNormal();
	Result = T->MineAt(Hit + Dir * (T->GetCellSize() * 0.5f), MineRadius, Damage, Owner);

	for (const FFramework2DMaterialAmount& A : Result.Collected)
	{
		AddMaterial(A.Material, A.Count);
	}
	return Result;
}

int32 UFramework2DTerraformComponent::PlaceToward(FVector TargetWorld, float DeltaSeconds)
{
	AFramework2DTerrainWorld* T = GetTerrain();
	AActor* Owner = GetOwner();
	if (T && bInfiniteMaterials && SelectedMaterial == NAME_None) { SelectNextMaterial(1); }
	if (!T || !Owner || SelectedMaterial == NAME_None) { return 0; }

	PlaceAccumulator += FMath::Max(0.0f, PlaceCellsPerSecond) * DeltaSeconds;
	const int32 Budget = FMath::FloorToInt(PlaceAccumulator);
	if (Budget <= 0) { return 0; }
	PlaceAccumulator -= (float)Budget;

	const int32 Available = bInfiniteMaterials ? Budget : FMath::Min(Budget, GetAmount(SelectedMaterial));
	if (Available <= 0) { return 0; }

	const FVector Point = ClampToRange(Owner->GetActorLocation(), TargetWorld);
	const int32 Placed = T->PlaceMaterial(Point, PlaceRadius, SelectedMaterial, Available, bAvoidPawnsWhenPlacing);
	if (Placed > 0 && !bInfiniteMaterials)
	{
		ConsumeMaterial(SelectedMaterial, Placed);
	}
	return Placed;
}

void UFramework2DTerraformComponent::SelectNextMaterial(int32 Direction)
{
	// Modo creativo: todos los materiales del tileset que se pueden romper. Normal: lo que llevas.
	TArray<FName> Names;
	AFramework2DTerrainWorld* T = GetTerrain();
	if (bInfiniteMaterials && T)
	{
		for (const FFramework2DMaterial& M : T->GetMaterials())
		{
			if (!M.bIndestructible && M.Name != NAME_None) { Names.Add(M.Name); }
		}
	}
	else
	{
		for (const TPair<FName, int32>& Pair : Inventory)
		{
			if (Pair.Value > 0) { Names.Add(Pair.Key); }
		}
		Names.Sort([](const FName& A, const FName& B) { return A.LexicalLess(B); });
	}
	if (Names.Num() == 0) { return; }

	const int32 Current = Names.IndexOfByKey(SelectedMaterial);
	const int32 Step = Direction >= 0 ? 1 : -1;
	const int32 Next = (Current == INDEX_NONE) ? 0 : ((Current + Step) % Names.Num() + Names.Num()) % Names.Num();
	SelectedMaterial = Names[Next];
	OnInventoryChanged.Broadcast();
}

int32 UFramework2DTerraformComponent::GetAmount(FName Material) const
{
	const int32* Found = Inventory.Find(Material);
	return Found ? *Found : 0;
}

int32 UFramework2DTerraformComponent::GetTotalStored() const
{
	int32 Total = 0;
	for (const TPair<FName, int32>& Pair : Inventory) { Total += Pair.Value; }
	return Total;
}

int32 UFramework2DTerraformComponent::AddMaterial(FName Material, int32 Count)
{
	if (Material == NAME_None || Count <= 0) { return 0; }
	const int32 Accepted = (Capacity > 0) ? FMath::Clamp(Capacity - GetTotalStored(), 0, Count) : Count;
	if (Accepted <= 0) { return 0; }
	Inventory.FindOrAdd(Material) += Accepted;
	if (SelectedMaterial == NAME_None) { SelectedMaterial = Material; } // lo primero que coges, listo para colocar
	OnInventoryChanged.Broadcast();
	return Accepted;
}

bool UFramework2DTerraformComponent::ConsumeMaterial(FName Material, int32 Count)
{
	if (Count <= 0) { return true; }
	int32* Found = Inventory.Find(Material);
	if (!Found || *Found < Count) { return false; }
	*Found -= Count;
	if (*Found == 0)
	{
		Inventory.Remove(Material);
		// Te quedas sin el seleccionado: pasa al siguiente que tengas.
		if (SelectedMaterial == Material && !bInfiniteMaterials)
		{
			SelectedMaterial = NAME_None;
			for (const TPair<FName, int32>& Pair : Inventory)
			{
				if (Pair.Value > 0) { SelectedMaterial = Pair.Key; break; }
			}
		}
	}
	OnInventoryChanged.Broadcast();
	return true;
}
