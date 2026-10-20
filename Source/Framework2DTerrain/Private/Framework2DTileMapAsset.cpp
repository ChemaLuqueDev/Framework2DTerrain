// Copyright Chema Luque. Plugin Framework2DTerrain.

#include "Framework2DTileMapAsset.h"

// Valor guardado -> forma de colision. Un byte fuera de rango (dato viejo o roto) vale Auto.
static EFramework2DCollisionShape Framework2DShapeFromByte(uint8 Value)
{
	return Value <= (uint8)EFramework2DCollisionShape::Platform
		? (EFramework2DCollisionShape)Value
		: EFramework2DCollisionShape::Auto;
}

// Re-mapea las capas y la colision pintada de OldW x OldH al tamano actual del mapa, anclado arriba
// a la izquierda: lo que cabe se conserva por (x, y) y lo nuevo queda vacio.
static void Framework2DRemapTileMapContent(UFramework2DTileMapAsset& Map, int32 OldW, int32 OldH)
{
	const int32 NewW = FMath::Max(1, Map.Width);
	const int32 NewH = FMath::Max(1, Map.Height);
	const int32 CopyW = FMath::Min(OldW, NewW);
	const int32 CopyH = FMath::Min(OldH, NewH);
	for (FFramework2DTileLayer& Layer : Map.Layers)
	{
		TArray<int32> NewTiles;
		NewTiles.Init(-1, NewW * NewH);
		if (Layer.Tiles.Num() == OldW * OldH)
		{
			for (int32 Y = 0; Y < CopyH; ++Y)
			{
				for (int32 X = 0; X < CopyW; ++X)
				{
					NewTiles[Y * NewW + X] = Layer.Tiles[Y * OldW + X];
				}
			}
		}
		Layer.Tiles = MoveTemp(NewTiles);
	}

	// La colision pintada sigue a sus tiles. Si estaba vacia (o no cuadraba) queda vacia.
	if (Map.CollisionOverrides.Num() == OldW * OldH)
	{
		TArray<uint8> NewOverrides;
		NewOverrides.Init((uint8)EFramework2DCollisionShape::Auto, NewW * NewH);
		for (int32 Y = 0; Y < CopyH; ++Y)
		{
			for (int32 X = 0; X < CopyW; ++X)
			{
				NewOverrides[Y * NewW + X] = Map.CollisionOverrides[Y * OldW + X];
			}
		}
		Map.CollisionOverrides = MoveTemp(NewOverrides);
	}
	else
	{
		Map.CollisionOverrides.Reset();
	}
}

UFramework2DTileMapAsset::UFramework2DTileMapAsset()
{
	FFramework2DTileLayer Ground;
	Ground.Name = TEXT("Terrain");
	Layers.Add(Ground);
}

void UFramework2DTileMapAsset::Resize(int32 NewWidth, int32 NewHeight)
{
	// Mismos limites que Width/Height en Details.
	const int32 NewW = FMath::Clamp(NewWidth, 1, 1024);
	const int32 NewH = FMath::Clamp(NewHeight, 1, 1024);
	const int32 PrevW = Width;
	const int32 PrevH = Height;
	if (NewW == PrevW && NewH == PrevH) { return; }
	Width = NewW;
	Height = NewH;
	Framework2DRemapTileMapContent(*this, PrevW, PrevH);
	OldWidth = Width;
	OldHeight = Height;
}

int32 UFramework2DTileMapAsset::FindLayerByName(FName LayerName) const
{
	// FName compara sin distinguir mayusculas.
	for (int32 i = 0; i < Layers.Num(); ++i)
	{
		if (Layers[i].Name == LayerName) { return i; }
	}
	return INDEX_NONE;
}

int32 UFramework2DTileMapAsset::At(int32 Layer, int32 X, int32 Y) const
{
	if (!Layers.IsValidIndex(Layer) || !Layers[Layer].bVisible) { return -1; }
	return GetTile(Layer, X, Y);
}

int32 UFramework2DTileMapAsset::GetTile(int32 Layer, int32 X, int32 Y) const
{
	if (!Layers.IsValidIndex(Layer)) { return -1; }
	if (X < 0 || X >= Width || Y < 0 || Y >= Height) { return -1; }
	const TArray<int32>& Tiles = Layers[Layer].Tiles;
	const int32 Idx = Y * Width + X;
	return Tiles.IsValidIndex(Idx) ? Tiles[Idx] : -1;
}

void UFramework2DTileMapAsset::EnsureLayer(int32 Layer)
{
	if (Layer < 0) { return; }
	while (Layers.Num() <= Layer)
	{
		FFramework2DTileLayer NewLayer;
		NewLayer.Name = FName(*FString::Printf(TEXT("Layer %d"), Layers.Num()));
		Layers.Add(NewLayer);
	}
	const int32 Needed = FMath::Max(1, Width) * FMath::Max(1, Height);
	if (Layers[Layer].Tiles.Num() != Needed)
	{
		Layers[Layer].Tiles.Init(-1, Needed);
	}
}

bool UFramework2DTileMapAsset::SetTile(int32 Layer, int32 X, int32 Y, int32 TileIndex)
{
	if (Layer < 0 || X < 0 || X >= Width || Y < 0 || Y >= Height) { return false; }
	EnsureLayer(Layer);
	int32& Cell = Layers[Layer].Tiles[Y * Width + X];
	const int32 NewValue = FMath::Max(-1, TileIndex);
	if (Cell == NewValue) { return false; }
	Cell = NewValue;
	return true;
}

bool UFramework2DTileMapAsset::FillRect(int32 Layer, int32 X0, int32 Y0, int32 X1, int32 Y1, int32 TileIndex)
{
	if (Layer < 0) { return false; }
	EnsureLayer(Layer);
	const int32 Ax = FMath::Clamp(FMath::Min(X0, X1), 0, Width - 1);
	const int32 Bx = FMath::Clamp(FMath::Max(X0, X1), 0, Width - 1);
	const int32 Ay = FMath::Clamp(FMath::Min(Y0, Y1), 0, Height - 1);
	const int32 By = FMath::Clamp(FMath::Max(Y0, Y1), 0, Height - 1);
	bool bChanged = false;
	for (int32 Y = Ay; Y <= By; ++Y)
	{
		for (int32 X = Ax; X <= Bx; ++X)
		{
			bChanged |= SetTile(Layer, X, Y, TileIndex);
		}
	}
	return bChanged;
}

bool UFramework2DTileMapAsset::FloodFill(int32 Layer, int32 X, int32 Y, int32 TileIndex, FIntRect& OutChanged)
{
	if (Layer < 0 || X < 0 || X >= Width || Y < 0 || Y >= Height) { return false; }
	EnsureLayer(Layer);
	TArray<int32>& Tiles = Layers[Layer].Tiles;
	const int32 Target = Tiles[Y * Width + X];
	const int32 NewValue = FMath::Max(-1, TileIndex);
	if (Target == NewValue) { return false; }

	OutChanged = FIntRect(X, Y, X, Y);
	TArray<FIntPoint> Stack;
	Stack.Add(FIntPoint(X, Y));
	Tiles[Y * Width + X] = NewValue;
	while (Stack.Num() > 0)
	{
		const FIntPoint P = Stack.Pop();
		OutChanged.Min.X = FMath::Min(OutChanged.Min.X, P.X);
		OutChanged.Min.Y = FMath::Min(OutChanged.Min.Y, P.Y);
		OutChanged.Max.X = FMath::Max(OutChanged.Max.X, P.X);
		OutChanged.Max.Y = FMath::Max(OutChanged.Max.Y, P.Y);
		static const int32 DX[4] = { 1, -1, 0, 0 };
		static const int32 DY[4] = { 0, 0, 1, -1 };
		for (int32 k = 0; k < 4; ++k)
		{
			const int32 NX = P.X + DX[k];
			const int32 NY = P.Y + DY[k];
			if (NX < 0 || NX >= Width || NY < 0 || NY >= Height) { continue; }
			int32& Cell = Tiles[NY * Width + NX];
			if (Cell != Target) { continue; }
			Cell = NewValue;
			Stack.Add(FIntPoint(NX, NY));
		}
	}
	return true;
}

//---------------------- Colision pintada ----------------------

EFramework2DCollisionShape UFramework2DTileMapAsset::GetCollisionOverride(int32 X, int32 Y) const
{
	if (X < 0 || X >= Width || Y < 0 || Y >= Height) { return EFramework2DCollisionShape::Auto; }
	// Una lista de otro tamano (vacia o de antes de redimensionar) es "nada pintado".
	if (CollisionOverrides.Num() != Width * Height) { return EFramework2DCollisionShape::Auto; }
	return Framework2DShapeFromByte(CollisionOverrides[Y * Width + X]);
}

bool UFramework2DTileMapAsset::SetCollisionOverride(int32 X, int32 Y, EFramework2DCollisionShape Shape)
{
	if (X < 0 || X >= Width || Y < 0 || Y >= Height) { return false; }
	if (CollisionOverrides.Num() != Width * Height)
	{
		// Borrar donde no hay nada pintado no cambia nada: la lista sigue vacia.
		if (Shape == EFramework2DCollisionShape::Auto) { return false; }
		CollisionOverrides.Init((uint8)EFramework2DCollisionShape::Auto, Width * Height);
	}
	uint8& Cell = CollisionOverrides[Y * Width + X];
	const uint8 NewValue = (uint8)Shape;
	if (Cell == NewValue) { return false; }
	Cell = NewValue;
	return true;
}

bool UFramework2DTileMapAsset::HasCollisionOverrides() const
{
	if (CollisionOverrides.Num() != Width * Height) { return false; }
	for (const uint8 Value : CollisionOverrides)
	{
		if (Framework2DShapeFromByte(Value) != EFramework2DCollisionShape::Auto) { return true; }
	}
	return false;
}

//---------------------- Capas ----------------------

int32 UFramework2DTileMapAsset::AddLayer(FName Name)
{
	const int32 Index = Layers.Num();
	EnsureLayer(Index);
	if (Name != NAME_None) { Layers[Index].Name = Name; }
	return Index;
}

void UFramework2DTileMapAsset::RemoveLayer(int32 Layer)
{
	if (Layers.Num() <= 1 || !Layers.IsValidIndex(Layer)) { return; }
	Layers.RemoveAt(Layer);
}

bool UFramework2DTileMapAsset::MoveLayer(int32 From, int32 To)
{
	if (!Layers.IsValidIndex(From) || !Layers.IsValidIndex(To) || From == To) { return false; }
	// Se mueve el elemento entero (nombre, banderas y tiles): quitarlo e insertarlo deja la
	// capa justo en To, suba o baje.
	FFramework2DTileLayer Moved = MoveTemp(Layers[From]);
	Layers.RemoveAt(From);
	Layers.Insert(MoveTemp(Moved), To);
	return true;
}

int32 UFramework2DTileMapAsset::ClearFlipbook(int32 FlipbookId)
{
	const int32 Value = Framework2D::MakeFlipbookValue(FlipbookId);
	return ClearValues([Value](int32 Cell) { return Cell == Value; });
}

int32 UFramework2DTileMapAsset::ClearAtlasPage(int32 PageId)
{
	return ClearValues([PageId](int32 Cell) { return Framework2D::IsAtlasTileValue(Cell) && Framework2D::TilePageOf(Cell) == PageId; });
}

int32 UFramework2DTileMapAsset::ClearGenerator(int32 GeneratorId)
{
	const int32 Value = Framework2D::MakeGeneratorValue(GeneratorId);
	return ClearValues([Value](int32 Cell) { return Cell == Value; });
}

int32 UFramework2DTileMapAsset::ClearValues(TFunctionRef<bool(int32)> Predicate)
{
	int32 Cleared = 0;
	for (FFramework2DTileLayer& Layer : Layers)
	{
		for (int32& Cell : Layer.Tiles)
		{
			if (Cell >= 0 && Predicate(Cell))
			{
				Cell = -1;
				++Cleared;
			}
		}
	}
	return Cleared;
}

#if WITH_EDITOR
void UFramework2DTileMapAsset::PreEditChange(FProperty* PropertyAboutToChange)
{
	Super::PreEditChange(PropertyAboutToChange);
	OldWidth = Width;
	OldHeight = Height;
}

void UFramework2DTileMapAsset::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	const FName Prop = PropertyChangedEvent.GetPropertyName();
	if ((Prop == GET_MEMBER_NAME_CHECKED(UFramework2DTileMapAsset, Width) ||
		 Prop == GET_MEMBER_NAME_CHECKED(UFramework2DTileMapAsset, Height)) &&
		OldWidth > 0 && OldHeight > 0 && (OldWidth != Width || OldHeight != Height))
	{
		// Mismo re-mapeo que Resize: Width/Height ya tienen el tamano nuevo.
		Framework2DRemapTileMapContent(*this, OldWidth, OldHeight);
	}
	OldWidth = Width;
	OldHeight = Height;
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif
