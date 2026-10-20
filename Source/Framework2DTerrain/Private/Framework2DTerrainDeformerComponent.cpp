// Copyright Chema Luque. Plugin Framework2DTerrain.

#include "Framework2DTerrainDeformerComponent.h"

#include "Framework2DTerrainWorld.h"
#include "Framework2DTerraformComponent.h"
#include "PaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "Engine/LocalPlayer.h"
#include "Engine/GameViewportClient.h"
#include "DrawDebugHelpers.h"
#include "EngineUtils.h" // TActorIterator

UFramework2DTerrainDeformerComponent::UFramework2DTerrainDeformerComponent()
{
	PrimaryComponentTick.bCanEverTick = true; // lee las teclas y reparte los golpes en el tiempo
	PrimaryComponentTick.bTickEvenWhenPaused = true; // en pausa solo olvida las teclas (ver TickComponent)
	Keys = { EKeys::LeftMouseButton, EKeys::Gamepad_RightTrigger };
}

void UFramework2DTerrainDeformerComponent::BeginPlay()
{
	Super::BeginPlay();
	// Al empezar mira hacia donde mire el actor (luego lo decide Facing Source).
	if (const AActor* Owner = GetOwner())
	{
		FVector Right, Up;
		GetPlaneAxes(Right, Up);
		SetFacing((float)FVector::DotProduct(Owner->GetActorForwardVector(), Right));
	}
}

//---------------------- Terreno y ejes ----------------------

void UFramework2DTerrainDeformerComponent::GatherTerrains(FTerrainList& Out, bool bRefresh) const
{
	Out.Reset();
	if (Terrain)
	{
		Out.Add(Terrain);
		return;
	}
	UWorld* World = GetWorld();
	const double Now = World ? World->GetTimeSeconds() : 0.0;
	bRefresh = bRefresh || !bTerrainsSearched || (LevelTerrains.Num() == 0 && Now - LastTerrainSearch >= 0.5) ||
		LevelTerrains.ContainsByPredicate([](const TWeakObjectPtr<AFramework2DTerrainWorld>& T) { return !T.IsValid(); });
	if (bRefresh)
	{
		bTerrainsSearched = true;
		LastTerrainSearch = Now;
		LevelTerrains.Reset();
		if (World)
		{
			for (TActorIterator<AFramework2DTerrainWorld> It(World); It; ++It) { LevelTerrains.Add(*It); }
		}
	}
	for (const TWeakObjectPtr<AFramework2DTerrainWorld>& T : LevelTerrains)
	{
		if (AFramework2DTerrainWorld* Valid = T.Get()) { Out.Add(Valid); }
	}
}

void UFramework2DTerrainDeformerComponent::GetPlaneAxes(FVector& OutRight, FVector& OutUp) const
{
	FTerrainList Terrains;
	GatherTerrains(Terrains);
	if (Terrains.Num() > 0)
	{
		const FTransform& Xf = Terrains[0]->GetActorTransform();
		OutRight = Xf.GetUnitAxis(EAxis::X);
		OutUp = Xf.GetUnitAxis(EAxis::Z);
		return;
	}
	OutRight = FVector::XAxisVector;
	OutUp = FVector::ZAxisVector;
}

APlayerController* UFramework2DTerrainDeformerComponent::GetLocalPlayerController() const
{
	const APawn* Pawn = Cast<APawn>(GetOwner());
	APlayerController* PC = Pawn ? Cast<APlayerController>(Pawn->GetController()) : nullptr;
	return (PC && PC->IsLocalController()) ? PC : nullptr;
}

bool UFramework2DTerrainDeformerComponent::IsGameInputOpen(const APlayerController* PC) const
{
	const APawn* Pawn = Cast<APawn>(GetOwner());
	if (!PC || !Pawn || !Pawn->InputEnabled() || !PC->InputEnabled()) { return false; }
	// Un menu "solo interfaz" (Set Input Mode UI Only) hace que el viewport ignore la entrada: las
	// teclas que se sueltan entonces no llegan y su estado se queda "pulsado".
	const ULocalPlayer* Local = PC->GetLocalPlayer();
	return !(Local && Local->ViewportClient && Local->ViewportClient->IgnoreInput());
}

//---------------------- Hacia donde mira ----------------------

void UFramework2DTerrainDeformerComponent::SetFacing(float Direction)
{
	if (FMath::Abs(Direction) > 0.01f) { Facing = Direction > 0.0f ? 1.0f : -1.0f; }
}

void UFramework2DTerrainDeformerComponent::UpdateFacing(APlayerController* PC)
{
	const AActor* Owner = GetOwner();
	if (!Owner) { return; }
	FVector Right, Up;
	GetPlaneAxes(Right, Up);
	switch (FacingSource)
	{
	case EFramework2DFacingSource::Movement:
		if (const APawn* Pawn = Cast<APawn>(Owner))
		{
			// La entrada de este frame (si aun no la ha gastado el movimiento) o la del anterior.
			float Side = (float)FVector::DotProduct(Pawn->GetPendingMovementInputVector(), Right);
			if (FMath::Abs(Side) <= 0.01f) { Side = (float)FVector::DotProduct(Pawn->GetLastMovementInputVector(), Right); }
			// La IA (MoveTo) mueve sin entrada: su velocidad. Al jugador no (un empujon no le da la vuelta).
			if (FMath::Abs(Side) <= 0.01f && !Pawn->IsPlayerControlled()) { Side = (float)FVector::DotProduct(Pawn->GetVelocity().GetSafeNormal(), Right); }
			SetFacing(Side);
		}
		else
		{
			SetFacing((float)FVector::DotProduct(Owner->GetVelocity().GetSafeNormal(), Right));
		}
		break;
	case EFramework2DFacingSource::ActorRotation:
		SetFacing((float)FVector::DotProduct(Owner->GetActorForwardVector(), Right));
		break;
	case EFramework2DFacingSource::SpriteRotation:
	{
		const APaperCharacter* Paper = Cast<APaperCharacter>(Owner);
		const USceneComponent* Visual = Paper ? Paper->GetSprite() : nullptr;
		if (!Visual) { Visual = Owner->GetRootComponent(); }
		if (Visual)
		{
			// Girado 180 grados o volteado con escala X negativa: las dos cosas cuentan.
			const FTransform& Xf = Visual->GetComponentTransform();
			SetFacing((float)FVector::DotProduct(Xf.GetUnitAxis(EAxis::X), Right) * FMath::Sign((float)Xf.GetScale3D().X));
		}
		break;
	}
	case EFramework2DFacingSource::Mouse:
	{
		FVector RayOrigin, RayDir;
		if (!PC || !PC->DeprojectMousePositionToWorld(RayOrigin, RayDir)) { break; }
		// Corte del rayo del raton con el plano del terreno.
		FTerrainList Terrains;
		GatherTerrains(Terrains);
		const FVector PlanePoint = Terrains.Num() > 0 ? Terrains[0]->GetActorLocation() : Owner->GetActorLocation();
		const FVector Normal = FVector::CrossProduct(Up, Right).GetSafeNormal();
		const double Denom = FVector::DotProduct(RayDir, Normal);
		if (FMath::Abs(Denom) < KINDA_SMALL_NUMBER) { break; }
		const double T = FVector::DotProduct(PlanePoint - RayOrigin, Normal) / Denom;
		if (T <= 0.0) { break; }
		FVector ToMouse = RayOrigin + RayDir * T - GetAimOrigin();
		ToMouse -= Normal * FVector::DotProduct(ToMouse, Normal);
		MouseAim = ToMouse;
		SetFacing((float)FVector::DotProduct(ToMouse, Right));
		break;
	}
	}
}

FVector UFramework2DTerrainDeformerComponent::GetAimOrigin() const
{
	const AActor* Owner = GetOwner();
	if (!Owner) { return FVector::ZeroVector; }
	FVector Right, Up;
	GetPlaneAxes(Right, Up);
	return Owner->GetActorLocation() + Up * HeightOffset;
}

FVector UFramework2DTerrainDeformerComponent::GetAimDirection() const
{
	if (FacingSource == EFramework2DFacingSource::Mouse && !MouseAim.IsNearlyZero()) { return MouseAim.GetSafeNormal(); }
	FVector Right, Up;
	GetPlaneAxes(Right, Up);
	const float Angle = FMath::DegreesToRadians(FMath::Clamp(AimAngle, -90.0f, 90.0f));
	return (Right * (Facing * FMath::Cos(Angle)) + Up * FMath::Sin(Angle)).GetSafeNormal();
}

//---------------------- Golpe ----------------------

bool UFramework2DTerrainDeformerComponent::FindTarget(FVector& OutCenter, AFramework2DTerrainWorld*& OutTerrain) const
{
	OutTerrain = nullptr;
	FTerrainList Terrains;
	GatherTerrains(Terrains);
	if (Terrains.Num() == 0 || !GetOwner()) { return false; }

	const FVector Origin = GetAimOrigin();
	const FVector Dir = GetAimDirection();
	float Length = FMath::Max(0.0f, Reach);
	// Con el raton y sin buscar la pared: en el cursor (si esta al alcance).
	if (FacingSource == EFramework2DFacingSource::Mouse && !bAimAtFirstSolid && !MouseAim.IsNearlyZero())
	{
		Length = FMath::Min(Length, (float)MouseAim.Size());
	}
	const FVector End = Origin + Dir * Length;
	if (!bAimAtFirstSolid)
	{
		OutCenter = End;
		return true;
	}

	// El primer terreno solido delante (lo que pararia al personaje), el mas cercano si hay varios.
	// La decoracion que no choca no para el rayo: se rompe con el golpe si cae dentro.
	double Best = TNumericLimits<double>::Max();
	for (AFramework2DTerrainWorld* T : Terrains)
	{
		FVector Hit;
		FName HitMaterial;
		if (T->TraceTerrain(Origin, End, /*bOnlyCollidable*/ true, Hit, HitMaterial))
		{
			const double Dist = FVector::DistSquared(Origin, Hit);
			if (Dist < Best)
			{
				Best = Dist;
				OutCenter = Hit;
				OutTerrain = T;
			}
		}
	}
	return OutTerrain != nullptr;
}

FFramework2DDigResult UFramework2DTerrainDeformerComponent::ApplyAt(const FVector& Center, AFramework2DTerrainWorld* Only)
{
	FFramework2DDigResult Result;
	Result.Location = Center;
	FTerrainList Targets;
	if (Only) { Targets.Add(Only); }
	else { GatherTerrains(Targets, /*bRefresh*/ true); } // un golpe suelto: por si se ha anadido un terreno

	// Alcanza terreno si el rayo encontro la pared, si el centro cae en terreno solido (aunque no se
	// rompa, como la roca madre) o si ha danado o roto algun pixel.
	bool bTouched = Only != nullptr;
	for (AFramework2DTerrainWorld* T : Targets)
	{
		bTouched = bTouched || T->IsSolidAtWorld(Center);
		const FFramework2DDigResult Part = Mode == EFramework2DDeformMode::Mine
			? T->MineAt(Center, Radius, Damage, GetOwner())
			: T->Dig(Center, Radius);
		Result.CellsRemoved += Part.CellsRemoved;
		Result.CellsHit += Part.CellsHit;
		for (const FFramework2DMaterialAmount& Amount : Part.Collected)
		{
			FFramework2DMaterialAmount* Same = Result.Collected.FindByPredicate([&Amount](const FFramework2DMaterialAmount& A) { return A.Material == Amount.Material; });
			if (Same) { Same->Count += Amount.Count; }
			else { Result.Collected.Add(Amount); }
		}
	}
	bTouched = bTouched || Result.CellsHit > 0;

	if (bStoreInInventory && Result.Collected.Num() > 0 && GetOwner())
	{
		if (UFramework2DTerraformComponent* Wand = GetOwner()->FindComponentByClass<UFramework2DTerraformComponent>())
		{
			for (const FFramework2DMaterialAmount& Amount : Result.Collected) { Wand->AddMaterial(Amount.Material, Amount.Count); }
		}
	}
	if (bTouched) { OnTerrainDeformed.Broadcast(Result); }
	return Result;
}

FFramework2DDigResult UFramework2DTerrainDeformerComponent::DeformNow()
{
	FTerrainList Refreshed;
	GatherTerrains(Refreshed, /*bRefresh*/ true); // por si se ha anadido un terreno al nivel
	UpdateFacing(GetLocalPlayerController());
	FVector Center;
	AFramework2DTerrainWorld* Target = nullptr;
	if (!FindTarget(Center, Target))
	{
		FFramework2DDigResult Miss;
		Miss.Location = GetAimOrigin() + GetAimDirection() * Reach;
		return Miss;
	}
	return ApplyAt(Center, Target);
}

FFramework2DDigResult UFramework2DTerrainDeformerComponent::DeformAt(FVector WorldPosition)
{
	return ApplyAt(WorldPosition, nullptr);
}

bool UFramework2DTerrainDeformerComponent::GetAimPoint(FVector& OutPoint)
{
	AFramework2DTerrainWorld* Target = nullptr;
	OutPoint = GetAimOrigin() + GetAimDirection() * Reach;
	return FindTarget(OutPoint, Target);
}

void UFramework2DTerrainDeformerComponent::DisarmKeys()
{
	ArmedKeys.Reset();
	bKeysDown = false;
	bPendingPress = false;
}

void UFramework2DTerrainDeformerComponent::StartDeforming()
{
	bPendingStart = bPendingStart || !bHeldByCode; // golpea aunque Stop llegue en este mismo frame
	bHeldByCode = true;
}

void UFramework2DTerrainDeformerComponent::StopDeforming()
{
	bHeldByCode = false;
}

void UFramework2DTerrainDeformerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// En pausa no se golpea, pero se olvidan las teclas: si el menu de pausa no deja llegar el soltar,
	// al quitarla no seguiria picando solo.
	if (TickType == LEVELTICK_PauseTick)
	{
		DisarmKeys();
		return;
	}
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	APlayerController* PC = GetLocalPlayerController();
	UpdateFacing(PC);

	// Teclas: solo con la entrada de la partida abierta y si se vio pulsarlas con ella abierta (una
	// tecla que se quedo "pulsada" tras un menu no pica hasta volver a pulsarla). El flanco de
	// pulsacion se guarda aparte: un clic que empieza y acaba en el mismo frame tambien golpea.
	// Cada tecla se arma por su cuenta: pulsar una no da por buena otra que se quedo "pulsada".
	if (bUseKeys && IsGameInputOpen(PC))
	{
		bKeysDown = false;
		ArmedKeys.RemoveAll([this](const FKey& Key) { return !Keys.Contains(Key); });
		for (const FKey& Key : Keys)
		{
			if (!Key.IsValid()) { continue; }
			const bool bKeyDown = PC->IsInputKeyDown(Key);
			if (PC->WasInputKeyJustPressed(Key))
			{
				ArmedKeys.AddUnique(Key);
				bPendingPress = true; // un clic durante la espera no se pierde
			}
			else if (!bKeyDown)
			{
				ArmedKeys.Remove(Key);
			}
			bKeysDown = bKeysDown || (bKeyDown && ArmedKeys.Contains(Key));
		}
	}
	else
	{
		DisarmKeys();
	}
	const bool bHeld = bKeysDown || bHeldByCode;

	// Golpes por segundo: la espera baja siempre; sin golpe pendiente no se acumula credito.
	Cooldown -= DeltaTime;
	if (Cooldown <= 0.0f && (bPendingPress || bPendingStart || (bHeld && bRepeatWhileHeld)))
	{
		bPendingPress = false;
		bPendingStart = false;
		DeformNow();
		Cooldown = HitsPerSecond > 0.0f ? FMath::Max(0.0f, Cooldown + 1.0f / HitsPerSecond) : 0.0f;
	}
	else if (Cooldown < 0.0f)
	{
		Cooldown = 0.0f;
	}

#if ENABLE_DRAW_DEBUG
	if (bShowAim)
	{
		FVector Right, Up;
		GetPlaneAxes(Right, Up);
		FVector Point;
		const bool bHit = GetAimPoint(Point);
		const FColor Color = bHit ? FColor(255, 210, 60) : FColor(150, 150, 150);
		DrawDebugLine(GetWorld(), GetAimOrigin(), Point, Color, false, -1.0f, SDPG_Foreground, 1.0f);
		DrawDebugCircle(GetWorld(), Point, Radius, 32, Color, false, -1.0f, SDPG_Foreground, 1.5f, Right, Up, false);
	}
#endif
}
