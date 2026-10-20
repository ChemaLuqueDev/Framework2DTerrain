// Copyright Chema Luque. Plugin Framework2DTerrain.

#include "Framework2DBackdropComponent.h"

#include "Camera/PlayerCameraManager.h"
#include "Engine/Texture2D.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"

UFramework2DBackdropComponent::UFramework2DBackdropComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Despues de mover la camara: la imagen queda en su sitio en el mismo frame (sin temblar).
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_PostUpdateWork;
	bTickInEditor = true;
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetCastShadow(false);
	bUseAsyncCooking = false;
}

void UFramework2DBackdropComponent::ClearLayers()
{
	Layers.Reset();
	TextureSizes.Reset();
	ClearAllMeshSections();
	EmptyOverrideMaterials();
	LastCamera = FVector(TNumericLimits<float>::Max());
}

void UFramework2DBackdropComponent::SetLayers(const TArray<FFramework2DBackdropLayer>& InLayers, UMaterialInterface* InMaterial, float InCellSize,
	const FVector2D& InLevelSize, float InTileSize, float InDepthY)
{
	TArray<TObjectPtr<UMaterialInstanceDynamic>> OldMIDs = MoveTemp(LayerMIDs);
	ClearLayers();
	LayerMIDs.Reset();
	CellSize = FMath::Max(0.01f, InCellSize);
	LevelSize = InLevelSize;
	TileSize = FMath::Max(0.01f, InTileSize);
	DepthY = InDepthY;
	if (!InMaterial) { return; }

	for (const FFramework2DBackdropLayer& Layer : InLayers)
	{
		UTexture2D* Texture = Layer.Texture;
		if (!Texture || Texture->GetSizeX() <= 0 || Texture->GetSizeY() <= 0) { continue; }
		const int32 Index = Layers.Add(Layer);
		TextureSizes.Add(FIntPoint(Texture->GetSizeX(), Texture->GetSizeY()));

		// Se reutilizan los materiales de la vez anterior (rehacer la vista previa es frecuente).
		UMaterialInstanceDynamic* MID = OldMIDs.IsValidIndex(Index) ? OldMIDs[Index].Get() : nullptr;
		if (!MID || MID->Parent != InMaterial)
		{
			MID = UMaterialInstanceDynamic::Create(InMaterial, this);
			if (MID) { MID->SetFlags(RF_Transient); }
		}
		if (MID)
		{
			MID->SetTextureParameterValue(TEXT("TerrainTexture"), Texture); // material propio
			MID->SetTextureParameterValue(TEXT("SpriteTexture"), Texture);  // material de Paper2D
		}
		LayerMIDs.Add(MID);

		// La geometria de verdad se pone en UpdateForCamera; aqui solo se crea la seccion.
		TArray<FVector> Verts;
		TArray<FVector2D> UVs;
		BuildLayerGeometry(Index, FVector(LevelSize.X * 0.5f, 0.0f, LevelSize.Y * 0.5f), Verts, UVs);
		const TArray<int32> Tris = { 0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7, 8, 9, 10, 8, 10, 11 };
		TArray<FVector> Normals;
		Normals.Init(FVector(0, -1, 0), Verts.Num());
		TArray<FLinearColor> Colors;
		Colors.Init(Layer.Tint, Verts.Num());
		CreateMeshSection_LinearColor(Index, Verts, Tris, Normals, UVs, Colors, TArray<FProcMeshTangent>(), /*bCreateCollision*/ false);
		SetMaterial(Index, MID);
	}

	FVector Camera;
	if (FindCameraLocation(Camera)) { UpdateForCamera(Camera); }
}

void UFramework2DBackdropComponent::BuildLayerGeometry(int32 Index, const FVector& CameraLocal, TArray<FVector>& OutVerts, TArray<FVector2D>& OutUVs) const
{
	const FFramework2DBackdropLayer& Layer = Layers[Index];
	const FIntPoint TexSize = TextureSizes[Index];
	const float Scale = FMath::Clamp(Layer.Scale, 0.1f, 32.0f);
	const float ImgW = (float)TexSize.X * CellSize * Scale;
	const float ImgH = (float)TexSize.Y * CellSize * Scale;

	// Con la camara en el centro del nivel la imagen queda como esta configurada; al moverse,
	// la imagen la sigue en (1 - Parallax): 0 = pegada a la camara, 1 = quieta con el nivel.
	const FVector2D Center(LevelSize.X * 0.5f, LevelSize.Y * 0.5f);
	const float OffsetX = (CameraLocal.X - Center.X) * (1.0f - FMath::Clamp(Layer.Parallax, 0.0f, 1.0f));
	const float OffsetZ = (CameraLocal.Z - Center.Y) * (1.0f - FMath::Clamp(Layer.VerticalParallax, 0.0f, 1.0f));
	const float Bottom = Layer.Height * TileSize + OffsetZ;
	const float Top = Bottom + ImgH;

	// A lo ancho: repetida, cubre de sobra lo que ve la camara; sola, centrada en el nivel.
	float X0 = 0.0f, X1 = 0.0f, U0 = 0.0f, U1 = 1.0f;
	if (Layer.bRepeat)
	{
		const float Span = LevelSize.X + 2.0f * ImgW + 4000.0f;
		X0 = CameraLocal.X - Span;
		X1 = CameraLocal.X + Span;
		const float Origin = Center.X - ImgW * 0.5f + OffsetX; // borde izquierdo de una copia
		U0 = (X0 - Origin) / ImgW;
		U1 = (X1 - Origin) / ImgW;
	}
	else
	{
		X0 = Center.X - ImgW * 0.5f + OffsetX;
		X1 = X0 + ImgW;
	}

	// Mas cerca de la camara cuanto mas adelante en la lista (la 0 es la del fondo del todo).
	const float Y = DepthY - (float)(Layers.Num() - 1 - Index) * 2.0f;
	const float Margin = LevelSize.Y + 4000.0f;
	const float HalfTexelV = 0.5f / (float)FMath::Max(1, TexSize.Y);

	// Tres quads: la imagen, la fila de abajo alargada hacia abajo y la de arriba hacia arriba
	// (vacios si no se piden). V = 0 arriba en la textura.
	auto AddQuad = [&](float Z0, float Z1, float V0, float V1)
	{
		OutVerts.Add(FVector(X0, Y, Z0));
		OutVerts.Add(FVector(X1, Y, Z0));
		OutVerts.Add(FVector(X1, Y, Z1));
		OutVerts.Add(FVector(X0, Y, Z1));
		OutUVs.Add(FVector2D(U0, V0));
		OutUVs.Add(FVector2D(U1, V0));
		OutUVs.Add(FVector2D(U1, V1));
		OutUVs.Add(FVector2D(U0, V1));
	};
	AddQuad(Bottom, Top, 1.0f, 0.0f);
	const float BelowZ0 = Layer.bFillBelow ? FMath::Min(Bottom, CameraLocal.Z - Margin) : Bottom;
	AddQuad(BelowZ0, Bottom, 1.0f - HalfTexelV, 1.0f - HalfTexelV);
	const float AboveZ1 = Layer.bFillAbove ? FMath::Max(Top, CameraLocal.Z + Margin) : Top;
	AddQuad(Top, AboveZ1, HalfTexelV, HalfTexelV);
}

void UFramework2DBackdropComponent::UpdateForCamera(const FVector& CameraWorldLocation)
{
	if (Layers.Num() == 0) { return; }
	const FVector CameraLocal = GetComponentTransform().InverseTransformPosition(CameraWorldLocation);
	if (CameraLocal.Equals(LastCamera, 0.01f)) { return; }
	LastCamera = CameraLocal;
	for (int32 Index = 0; Index < Layers.Num(); ++Index)
	{
		TArray<FVector> Verts;
		TArray<FVector2D> UVs;
		BuildLayerGeometry(Index, CameraLocal, Verts, UVs);
		TArray<FVector> Normals;
		Normals.Init(FVector(0, -1, 0), Verts.Num());
		TArray<FLinearColor> Colors;
		Colors.Init(Layers[Index].Tint, Verts.Num());
		UpdateMeshSection_LinearColor(Index, Verts, Normals, UVs, Colors, TArray<FProcMeshTangent>());
	}
}

bool UFramework2DBackdropComponent::FindCameraLocation(FVector& OutLocation) const
{
	const UWorld* World = GetWorld();
	if (!World) { return false; }
	// En juego: la camara del jugador (ya movida este frame). En el editor: el ultimo viewport.
	if (World->IsGameWorld())
	{
		const APlayerController* PC = World->GetFirstPlayerController();
		if (PC && PC->PlayerCameraManager)
		{
			OutLocation = PC->PlayerCameraManager->GetCameraLocation();
			return true;
		}
	}
	if (World->ViewLocationsRenderedLastFrame.Num() > 0)
	{
		OutLocation = World->ViewLocationsRenderedLastFrame[0];
		return true;
	}
	return false;
}

void UFramework2DBackdropComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector Camera;
	if (Layers.Num() > 0 && FindCameraLocation(Camera)) { UpdateForCamera(Camera); }
}
