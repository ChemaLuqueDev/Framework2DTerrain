// Copyright Chema Luque. Plugin Framework2DTerrain.

#include "Framework2DDemoCharacter.h"

#include "Framework2DTerrainWorld.h"
#include "Framework2DTerraformComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Engine.h"        // GEngine->AddOnScreenDebugMessage
#include "EngineUtils.h"          // TActorIterator
#include "InputCoreTypes.h"       // EKeys

AFramework2DDemoCharacter::AFramework2DDemoCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Auto-posesion: al colocarlo en el nivel, el jugador 0 lo controla directamente.
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Camara fija mirando el plano del terreno desde +Y.
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("DemoCamera"));
	Camera->SetupAttachment(GetCapsuleComponent());
	Camera->SetRelativeLocation(FVector(0.0f, CameraDistance, 120.0f));
	Camera->SetRelativeRotation(FRotator(-6.0f, -90.0f, 0.0f)); // desde +Y mirando a -Y: X a la derecha, como la vista Right
	Camera->bUsePawnControlRotation = false;

	// La varita estilo KYORA.
	Terraform = CreateDefaultSubobject<UFramework2DTerraformComponent>(TEXT("Terraform"));

	// Movimiento 2D: bloquear el eje Y (profundidad) y no rotar con el mando.
	bUseControllerRotationYaw = false;
	if (UCharacterMovementComponent* Move = GetCharacterMovement())
	{
		Move->SetPlaneConstraintEnabled(true);
		Move->SetPlaneConstraintNormal(FVector(0.0f, 1.0f, 0.0f));
		Move->bConstrainToPlane = true;
		Move->bOrientRotationToMovement = false;
		Move->GravityScale = 1.6f;
		Move->JumpZVelocity = 900.0f;
		Move->AirControl = 0.8f;
		Move->MaxWalkSpeed = 600.0f;
	}
}

void AFramework2DDemoCharacter::BeginPlay()
{
	Super::BeginPlay();

	// La distancia de camara se aplica aqui (en el constructor aun no hay valores del nivel/Blueprint).
	if (Camera) { Camera->SetRelativeLocation(FVector(0.0f, CameraDistance, 120.0f)); }

	// Buscar el terreno del nivel.
	for (TActorIterator<AFramework2DTerrainWorld> It(GetWorld()); It; ++It)
	{
		Terrain = *It;
		break;
	}
	if (!Terrain)
	{
		UE_LOG(LogTemp, Warning, TEXT("[Framework2DDemoCharacter] No hay ningun AFramework2DTerrainWorld en el nivel: picar/colocar no haran nada."));
	}
	else if (Terraform && !Terraform->Terrain)
	{
		Terraform->Terrain = Terrain;
	}

	// Mostrar el cursor para poder apuntar con el raton.
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;
	}
}

void AFramework2DDemoCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC) { return; }

	// --- Movimiento horizontal (sondeo de teclas, sin Input Mappings) ---
	float MoveAxis = 0.0f;
	if (PC->IsInputKeyDown(EKeys::D) || PC->IsInputKeyDown(EKeys::Right)) { MoveAxis += 1.0f; }
	if (PC->IsInputKeyDown(EKeys::A) || PC->IsInputKeyDown(EKeys::Left))  { MoveAxis -= 1.0f; }
	if (MoveAxis != 0.0f)
	{
		// Mundo X = derecha del terreno. Si en tu camara sale invertido, cambia el signo.
		AddMovementInput(FVector(1.0f, 0.0f, 0.0f), MoveAxis * MoveInputScale);
	}

	// --- Salto ---
	if (PC->WasInputKeyJustPressed(EKeys::SpaceBar) || PC->WasInputKeyJustPressed(EKeys::W) || PC->WasInputKeyJustPressed(EKeys::Up))
	{
		Jump();
	}

	if (!Terrain || !Terraform) { return; }

	// --- Cambiar de material ---
	if (PC->WasInputKeyJustPressed(EKeys::E) || PC->WasInputKeyJustPressed(EKeys::MouseScrollUp))
	{
		Terraform->SelectNextMaterial(1);
	}
	if (PC->WasInputKeyJustPressed(EKeys::Q) || PC->WasInputKeyJustPressed(EKeys::MouseScrollDown))
	{
		Terraform->SelectNextMaterial(-1);
	}

	// --- Picar / colocar / explotar apuntando con el raton ---
	FVector Hit;
	if (MouseToTerrainPlane(Hit))
	{
		if (PC->IsInputKeyDown(EKeys::LeftMouseButton))
		{
			Terraform->MineToward(Hit, DeltaSeconds);
		}
		else if (PC->IsInputKeyDown(EKeys::RightMouseButton))
		{
			Terraform->PlaceToward(Hit, DeltaSeconds);
		}
		if (PC->WasInputKeyJustPressed(EKeys::MiddleMouseButton) || PC->WasInputKeyJustPressed(EKeys::F))
		{
			Terrain->Explode(Hit, ExplosionRadius);
		}
	}

	if (bShowInventory) { DrawInventory(); }
}

void AFramework2DDemoCharacter::DrawInventory() const
{
	if (!GEngine || !Terraform) { return; }

	// Una linea por material, con el seleccionado marcado. Claves fijas => se reemplazan cada frame.
	TArray<FName> Names;
	Terraform->Inventory.GetKeys(Names);
	Names.Sort([](const FName& A, const FName& B) { return A.LexicalLess(B); });

	const uint64 BaseKey = 0xF2D0;
	GEngine->AddOnScreenDebugMessage(BaseKey, 0.0f, FColor::White,
		FString::Printf(TEXT("Inventario (%d)  |  Izq: picar  Der: colocar  Q/E: material  F: explosion"), Terraform->GetTotalStored()));
	int32 Line = 1;
	for (const FName& N : Names)
	{
		const bool bSel = (N == Terraform->SelectedMaterial);
		GEngine->AddOnScreenDebugMessage(BaseKey + Line, 0.0f, bSel ? FColor::Yellow : FColor(200, 200, 200),
			FString::Printf(TEXT("%s %s: %d"), bSel ? TEXT(">") : TEXT(" "), *N.ToString(), Terraform->GetAmount(N)));
		++Line;
	}
}

bool AFramework2DDemoCharacter::MouseToTerrainPlane(FVector& OutHit) const
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC || !Terrain) { return false; }

	FVector WorldOrigin, WorldDir;
	if (!PC->DeprojectMousePositionToWorld(WorldOrigin, WorldDir)) { return false; }

	// El terreno vive en el plano Y = (Y del actor de terreno). Intersecamos el rayo
	// del raton con ese plano.
	const double PlaneY = Terrain->GetActorLocation().Y;
	if (FMath::Abs(WorldDir.Y) < (double)KINDA_SMALL_NUMBER) { return false; }

	const double T = (PlaneY - WorldOrigin.Y) / WorldDir.Y;
	if (T <= 0.0) { return false; } // el plano esta detras de la camara

	OutHit = WorldOrigin + WorldDir * T;
	return true;
}
