// Copyright Chema Luque. Plugin Framework2DTerrain.

#include "Framework2DTileSet.h"

#include "Engine/Texture2D.h"
#include "UObject/ObjectSaveContext.h"

// =====================================================================
//  Materiales de serie
// =====================================================================
TArray<FFramework2DMaterial> Framework2D::MakeDefaultMaterials()
{
	TArray<FFramework2DMaterial> Out;
	auto Add = [&Out](FName Name, FColor Color, int32 Variance, bool bCollides, int32 Hardness) -> FFramework2DMaterial&
	{
		FFramework2DMaterial M;
		M.Name = Name;
		M.Color = Color;
		M.ColorVariance = Variance;
		M.bCollides = bCollides;
		M.Hardness = Hardness;
		return Out[Out.Add(M)];
	};
	Add("Dirt",  FColor(120, 82, 48),   14, true, 3);
	Add("Stone", FColor(120, 128, 140), 10, true, 8);
	Add("Wood",  FColor(96, 64, 36),    10, true, 4);
	Add("Sand",  FColor(224, 169, 74),  16, true, 1);

	// Decoracion: hierba, plantas... se ve y se rompe, pero no colisiona ni da material.
	FFramework2DMaterial& Deco = Add("Decoration", FColor(90, 160, 70), 10, false, 1);
	Deco.bCollectable = false;
	Deco.bDrawEdge = false;

	// Roca madre: los bordes del nivel que nada rompe.
	FFramework2DMaterial& Bedrock = Add("Bedrock", FColor(46, 44, 54), 6, true, 255);
	Bedrock.bIndestructible = true;
	Bedrock.bCollectable = false;
	return Out;
}

// =====================================================================
//  Lectura del atlas
// =====================================================================
#if WITH_EDITOR
// Decodifica el PNG ORIGINAL de la textura (Source) a FColor, sin importar la compresion.
// GetMipData copia bajo el cerrojo del Source: seguro aunque la textura se este compilando
// en segundo plano (LockMipReadOnly no lo es en UE 5.0).
static bool Framework2DDecodeTextureSource(UTexture2D* Tex, TArray<FColor>& OutPixels, int32& OutW, int32& OutH)
{
	if (!Tex || !Tex->Source.IsValid()) { return false; }

	FTextureSource& Src = Tex->Source;
	const int32 W = Src.GetSizeX();
	const int32 H = Src.GetSizeY();
	if (W <= 0 || H <= 0) { return false; }

	TArray64<uint8> Raw;
	if (!Src.GetMipData(Raw, 0, 0, 0)) { return false; }

	const int64 Num = (int64)W * H;
	const ETextureSourceFormat Format = Src.GetFormat();
	OutPixels.SetNumUninitialized((int32)Num);
	switch (Format)
	{
	case TSF_BGRA8:
		if (Raw.Num() < Num * 4) { return false; }
		FMemory::Memcpy(OutPixels.GetData(), Raw.GetData(), (SIZE_T)Num * sizeof(FColor)); // FColor ya es BGRA
		break;
	case TSF_G8:
		if (Raw.Num() < Num) { return false; }
		for (int64 i = 0; i < Num; ++i) { const uint8 G = Raw[i]; OutPixels[i] = FColor(G, G, G, 255); }
		break;
	case TSF_RGBA16:
	{
		if (Raw.Num() < Num * 8) { return false; }
		const uint16* P = reinterpret_cast<const uint16*>(Raw.GetData());
		for (int64 i = 0; i < Num; ++i)
		{
			OutPixels[i] = FColor((uint8)(P[i * 4] >> 8), (uint8)(P[i * 4 + 1] >> 8), (uint8)(P[i * 4 + 2] >> 8), (uint8)(P[i * 4 + 3] >> 8));
		}
		break;
	}
	case TSF_G16:
	{
		if (Raw.Num() < Num * 2) { return false; }
		const uint16* P = reinterpret_cast<const uint16*>(Raw.GetData());
		for (int64 i = 0; i < Num; ++i) { const uint8 G = (uint8)(P[i] >> 8); OutPixels[i] = FColor(G, G, G, 255); }
		break;
	}
	default:
		UE_LOG(LogTemp, Warning, TEXT("[Framework2DTerrain] El atlas '%s' tiene un formato no soportado (usa un PNG de 8 o 16 bits)."), *Tex->GetName());
		OutPixels.Reset();
		return false;
	}
	OutW = W;
	OutH = H;
	return true;
}
#endif

// =====================================================================
//  Valores de celda
// =====================================================================

// True si el valor es un tile de alguna pagina que se puede dibujar. Sin lista Tiles (imagen
// recien asignada, aun sin refrescar) se acepta cualquier numero: la imagen decide.
static bool Framework2DIsAtlasTile(const UFramework2DTileSet& Set, int32 Value)
{
	if (!Framework2D::IsAtlasTileValue(Value)) { return false; }
	const int32 PageId = Framework2D::TilePageOf(Value);
	const int32 Local = Framework2D::TileLocalOf(Value);
	const TArray<FFramework2DTileDef>* Tiles = Set.GetPageTiles(PageId);
	if (!Tiles) { return false; }
	if (Tiles->Num() > 0) { return Local < Tiles->Num(); }
	return Set.GetPageTexture(PageId) != nullptr;
}

// Nombre por defecto de un flipbook: "Flipbook N" con N = su Id.
static FName Framework2DDefaultFlipbookName(int32 Id)
{
	return FName(*FString::Printf(TEXT("Flipbook %d"), Id));
}

// Lee la imagen de una pagina: el PNG original en el editor, la copia guardada en el juego.
static bool Framework2DReadImage(UTexture2D* Texture, const TArray<FColor>& Cache, int32 CacheW, int32 CacheH,
	TArray<FColor>& OutPixels, int32& OutWidth, int32& OutHeight)
{
	OutWidth = 0;
	OutHeight = 0;
	OutPixels.Reset();
	if (!Texture) { return false; }
#if WITH_EDITOR
	if (Framework2DDecodeTextureSource(Texture, OutPixels, OutWidth, OutHeight)) { return true; }
#endif
	if (CacheW > 0 && CacheH > 0 && Cache.Num() == CacheW * CacheH)
	{
		OutPixels = Cache;
		OutWidth = CacheW;
		OutHeight = CacheH;
		return true;
	}
	return false;
}

static bool Framework2DImageSize(const UTexture2D* Texture, int32 CacheW, int32 CacheH, int32& OutWidth, int32& OutHeight)
{
	OutWidth = 0;
	OutHeight = 0;
	if (!Texture) { return false; }
#if WITH_EDITOR
	if (Texture->Source.IsValid())
	{
		OutWidth = Texture->Source.GetSizeX();
		OutHeight = Texture->Source.GetSizeY();
		return OutWidth > 0 && OutHeight > 0;
	}
#endif
	OutWidth = CacheW;
	OutHeight = CacheH;
	return OutWidth > 0 && OutHeight > 0;
}

// Los Ids repetidos o a 0 (anadidos o duplicados en Details) reciben uno nuevo; el primero que
// aparece conserva el suyo, porque los mapas ya apuntan a el.
template <typename ElementType>
static void Framework2DFixIds(TArray<ElementType>& Items, int32& NextId)
{
	for (const ElementType& Item : Items) { NextId = FMath::Max(NextId, Item.Id + 1); }
	NextId = FMath::Max(NextId, 1);
	TSet<int32> Seen;
	for (ElementType& Item : Items)
	{
		bool bAlreadySeen = false;
		if (Item.Id > 0) { Seen.Add(Item.Id, &bAlreadySeen); }
		if (Item.Id <= 0 || bAlreadySeen)
		{
			Item.Id = NextId++;
			Seen.Add(Item.Id);
		}
	}
}

UFramework2DTileSet::UFramework2DTileSet()
{
	Materials = Framework2D::MakeDefaultMaterials();
}

//---------------------- Flipbooks ----------------------

int32 UFramework2DTileSet::AddFlipbook(const TArray<int32>& Frames, FName Name)
{
	// El contador nunca va por detras de los Ids que ya hay (por si alguien edito a mano).
	for (const FFramework2DFlipbook& Existing : Flipbooks)
	{
		NextFlipbookId = FMath::Max(NextFlipbookId, Existing.Id + 1);
	}
	NextFlipbookId = FMath::Max(NextFlipbookId, 1);

	FFramework2DFlipbook Flipbook;
	Flipbook.Id = NextFlipbookId++;
	Flipbook.Name = (Name != NAME_None) ? Name : Framework2DDefaultFlipbookName(Flipbook.Id);
	Flipbook.FPS = 8.0f;
	Flipbook.Collision = EFramework2DCollisionShape::Auto;

	// Los fotogramas son tiles del atlas: fuera vacios y flipbooks dentro de flipbooks.
	Flipbook.Frames.Reserve(Frames.Num());
	for (const int32 Frame : Frames)
	{
		if (Framework2D::IsAtlasTileValue(Frame)) { Flipbook.Frames.Add(Frame); }
	}
	Flipbook.MaterialName = Flipbook.Frames.Num() > 0 ? GetTileMaterial(Flipbook.Frames[0]) : NAME_None;

	Flipbooks.Add(MoveTemp(Flipbook));
	return Flipbooks.Last().Id;
}

bool UFramework2DTileSet::RemoveFlipbook(int32 FlipbookId)
{
	const int32 Index = FindFlipbookIndex(FlipbookId);
	if (Index == INDEX_NONE) { return false; }
	// NextFlipbookId no baja: un Id borrado no se reutiliza (los mapas viejos no apuntan a otro).
	Flipbooks.RemoveAt(Index);
	// Los biomas que lo usaban (agua, cascadas, adornos...) dejan de apuntar a el.
	const int32 Value = Framework2D::MakeFlipbookValue(FlipbookId);
	ClearBiomeValues([Value](int32 Piece) { return Piece == Value; });
	return true;
}

int32 UFramework2DTileSet::FindFlipbookIndex(int32 FlipbookId) const
{
	for (int32 i = 0; i < Flipbooks.Num(); ++i)
	{
		if (Flipbooks[i].Id == FlipbookId) { return i; }
	}
	return INDEX_NONE;
}

const FFramework2DFlipbook* UFramework2DTileSet::FindFlipbookByValue(int32 Value) const
{
	if (!Framework2D::IsFlipbookValue(Value)) { return nullptr; }
	const int32 Index = FindFlipbookIndex(Framework2D::FlipbookIdFromValue(Value));
	return Index != INDEX_NONE ? &Flipbooks[Index] : nullptr;
}

FFramework2DFlipbook* UFramework2DTileSet::FindFlipbookById(int32 FlipbookId)
{
	const int32 Index = FindFlipbookIndex(FlipbookId);
	return Index != INDEX_NONE ? &Flipbooks[Index] : nullptr;
}

bool UFramework2DTileSet::IsAnimated(int32 Value) const
{
	const FFramework2DFlipbook* Flipbook = FindFlipbookByValue(Value);
	return Flipbook && Flipbook->Frames.Num() >= 2;
}

int32 UFramework2DTileSet::GetFrameTile(int32 Value, double Time) const
{
	if (Value < 0 || Framework2D::IsGeneratorValue(Value)) { return -1; } // un generador no es un tile
	if (!Framework2D::IsFlipbookValue(Value))
	{
		return Framework2DIsAtlasTile(*this, Value) ? Value : -1;
	}

	const FFramework2DFlipbook* Flipbook = FindFlipbookByValue(Value);
	if (!Flipbook || Flipbook->Frames.Num() == 0) { return -1; }

	// Modulo positivo: un tiempo negativo no debe dar un indice fuera de la lista.
	const int64 Num = Flipbook->Frames.Num();
	const int64 Step = (int64)FMath::FloorToDouble(Time * (double)FMath::Max(0.1f, Flipbook->FPS));
	const int32 Frame = (int32)(((Step % Num) + Num) % Num);
	const int32 Tile = Flipbook->Frames[Frame];
	// Un fotograma que ya no existe en el atlas (atlas mas pequeno) no dibuja nada.
	return Framework2DIsAtlasTile(*this, Tile) ? Tile : -1;
}

//---------------------- Propiedades de un valor de celda ----------------------

FName UFramework2DTileSet::GetTileMaterial(int32 Value) const
{
	if (Framework2D::IsFlipbookValue(Value))
	{
		const FFramework2DFlipbook* Flipbook = FindFlipbookByValue(Value);
		return Flipbook ? Flipbook->MaterialName : NAME_None;
	}
	const FFramework2DTileDef* Def = FindTileDef(Value); // un generador no tiene: None
	return Def ? Def->MaterialName : NAME_None;
}

EFramework2DCollisionShape UFramework2DTileSet::GetTileCollision(int32 Value) const
{
	if (Framework2D::IsFlipbookValue(Value))
	{
		const FFramework2DFlipbook* Flipbook = FindFlipbookByValue(Value);
		return Flipbook ? Flipbook->Collision : EFramework2DCollisionShape::Auto;
	}
	const FFramework2DTileDef* Def = FindTileDef(Value);
	return Def ? Def->Collision : EFramework2DCollisionShape::Auto;
}

bool UFramework2DTileSet::IsValidValue(int32 Value) const
{
	if (Framework2D::IsGeneratorValue(Value)) { return FindGeneratorByValue(Value) != nullptr; }
	if (Framework2D::IsFlipbookValue(Value)) { return FindFlipbookByValue(Value) != nullptr; }
	return Framework2DIsAtlasTile(*this, Value);
}

const FFramework2DTileDef* UFramework2DTileSet::FindTileDef(int32 Value) const
{
	if (!Framework2D::IsAtlasTileValue(Value)) { return nullptr; }
	const TArray<FFramework2DTileDef>* PageTiles = GetPageTiles(Framework2D::TilePageOf(Value));
	const int32 Local = Framework2D::TileLocalOf(Value);
	return (PageTiles && PageTiles->IsValidIndex(Local)) ? &(*PageTiles)[Local] : nullptr;
}

FFramework2DTileDef* UFramework2DTileSet::FindTileDefMutable(int32 Value)
{
	return const_cast<FFramework2DTileDef*>(FindTileDef(Value));
}

//---------------------- Paginas de atlas ----------------------

int32 UFramework2DTileSet::GetPageIdAt(int32 Index) const
{
	if (Index == 0) { return 0; }
	return ExtraAtlases.IsValidIndex(Index - 1) ? ExtraAtlases[Index - 1].Id : INDEX_NONE;
}

int32 UFramework2DTileSet::FindPageIndex(int32 PageId) const
{
	if (PageId == 0) { return 0; }
	for (int32 i = 0; i < ExtraAtlases.Num(); ++i)
	{
		if (ExtraAtlases[i].Id == PageId) { return i + 1; }
	}
	return INDEX_NONE;
}

FText UFramework2DTileSet::GetPageDisplayName(int32 PageId) const
{
	const int32 Index = FindPageIndex(PageId);
	if (Index == 0) { return NSLOCTEXT("Framework2DTerrain", "MainAtlas", "Principal"); }
	if (Index == INDEX_NONE) { return FText::GetEmpty(); }
	const FFramework2DAtlasPage& Page = ExtraAtlases[Index - 1];
	return Page.Name.IsNone() ? FText::AsNumber(Page.Id) : FText::FromName(Page.Name);
}

UTexture2D* UFramework2DTileSet::GetPageTexture(int32 PageId) const
{
	const int32 Index = FindPageIndex(PageId);
	if (Index == 0) { return Atlas; }
	return Index != INDEX_NONE ? ExtraAtlases[Index - 1].Texture.Get() : nullptr;
}

const TArray<FFramework2DTileDef>* UFramework2DTileSet::GetPageTiles(int32 PageId) const
{
	const int32 Index = FindPageIndex(PageId);
	if (Index == 0) { return &Tiles; }
	return Index != INDEX_NONE ? &ExtraAtlases[Index - 1].Tiles : nullptr;
}

TArray<FFramework2DTileDef>* UFramework2DTileSet::GetPageTilesMutable(int32 PageId)
{
	return const_cast<TArray<FFramework2DTileDef>*>(GetPageTiles(PageId));
}

bool UFramework2DTileSet::GetPageSize(int32 PageId, int32& OutWidth, int32& OutHeight) const
{
	const int32 Index = FindPageIndex(PageId);
	if (Index == 0) { return GetAtlasSize(OutWidth, OutHeight); }
	OutWidth = OutHeight = 0;
	if (Index == INDEX_NONE) { return false; }
	const FFramework2DAtlasPage& Page = ExtraAtlases[Index - 1];
	return Framework2DImageSize(Page.Texture, Page.CacheWidth, Page.CacheHeight, OutWidth, OutHeight);
}

bool UFramework2DTileSet::GetPageGrid(int32 PageId, int32& OutColumns, int32& OutRows) const
{
	int32 W = 0, H = 0;
	OutColumns = OutRows = 0;
	if (!GetPageSize(PageId, W, H)) { return false; }
	OutColumns = W / FMath::Max(1, TileWidth);
	OutRows = H / FMath::Max(1, TileHeight);
	return OutColumns > 0 && OutRows > 0;
}

bool UFramework2DTileSet::ReadPagePixels(int32 PageId, TArray<FColor>& OutPixels, int32& OutWidth, int32& OutHeight) const
{
	const int32 Index = FindPageIndex(PageId);
	if (Index == 0) { return ReadAtlasPixels(OutPixels, OutWidth, OutHeight); }
	OutPixels.Reset();
	OutWidth = OutHeight = 0;
	if (Index == INDEX_NONE) { return false; }
	const FFramework2DAtlasPage& Page = ExtraAtlases[Index - 1];
	if (Framework2DReadImage(Page.Texture, Page.PixelCache, Page.CacheWidth, Page.CacheHeight, OutPixels, OutWidth, OutHeight)) { return true; }
	if (Page.Texture)
	{
		UE_LOG(LogTemp, Warning, TEXT("[Framework2DTerrain] No se pudo leer el atlas '%s' del tileset '%s'. Abrelo en el editor y guardalo (Ctrl+S)."),
			*Page.Name.ToString(), *GetName());
	}
	return false;
}

bool UFramework2DTileSet::GetTileValueOrigin(int32 TileValue, int32& OutPageId, int32& OutX, int32& OutY) const
{
	OutPageId = INDEX_NONE;
	OutX = OutY = 0;
	if (!Framework2D::IsAtlasTileValue(TileValue)) { return false; }
	const int32 PageId = Framework2D::TilePageOf(TileValue);
	int32 W = 0, H = 0;
	if (!GetPageSize(PageId, W, H)) { return false; }
	if (!GetTilePixelOrigin(Framework2D::TileLocalOf(TileValue), W, OutX, OutY)) { return false; }
	if (OutX + TileWidth > W || OutY + TileHeight > H) { return false; }
	OutPageId = PageId;
	return true;
}

int32 UFramework2DTileSet::AddAtlasPage(UTexture2D* Texture, FName Name)
{
	Framework2DFixIds(ExtraAtlases, NextAtlasId);
	if (GetNumPages() >= Framework2D::MaxAtlasPages || NextAtlasId >= Framework2D::MaxAtlasPages)
	{
		UE_LOG(LogTemp, Warning, TEXT("[Framework2DTerrain] '%s' ya tiene el maximo de atlas (%d)."), *GetName(), Framework2D::MaxAtlasPages);
		return INDEX_NONE;
	}
	FFramework2DAtlasPage& Page = ExtraAtlases.AddDefaulted_GetRef();
	Page.Id = NextAtlasId++;
	Page.Texture = Texture;
	Page.Name = (Name != NAME_None) ? Name : (Texture ? Texture->GetFName() : FName(*FString::Printf(TEXT("Atlas %d"), Page.Id)));
	RefreshPage(Page);
	return Page.Id;
}

bool UFramework2DTileSet::RemoveAtlasPage(int32 PageId)
{
	const int32 Index = FindPageIndex(PageId);
	if (Index <= 0) { return false; } // la principal no se quita
	ExtraAtlases.RemoveAt(Index - 1);
	// Las piezas de los biomas que eran tiles de esa pagina quedan sin asignar.
	ClearBiomeValues([PageId](int32 Piece) { return Framework2D::IsAtlasTileValue(Piece) && Framework2D::TilePageOf(Piece) == PageId; });
	return true;
}

void UFramework2DTileSet::RefreshPage(FFramework2DAtlasPage& Page)
{
	int32 W = 0, H = 0;
	if (!Framework2DImageSize(Page.Texture, Page.CacheWidth, Page.CacheHeight, W, H))
	{
		Page.Columns = Page.Rows = 0;
		return;
	}
	Page.Columns = FMath::Max(0, W / FMath::Max(1, TileWidth));
	Page.Rows = FMath::Max(0, H / FMath::Max(1, TileHeight));
	const int32 Wanted = Page.Columns * Page.Rows;
	if (Page.Tiles.Num() != Wanted)
	{
		const int32 OldNum = Page.Tiles.Num();
		Page.Tiles.SetNum(Wanted);
		// Los tiles nuevos de una pagina extra nacen sin material: suele ser decoracion o fondo,
		// y asi no colisionan hasta que les digas que son terreno.
		for (int32 i = OldNum; i < Wanted; ++i) { Page.Tiles[i].MaterialName = TEXT("Decoration"); }
	}
}

//---------------------- Generadores ----------------------

int32 UFramework2DTileSet::AddGenerator(FName Name)
{
	Framework2DFixIds(Generators, NextGeneratorId);
	FFramework2DGenerator& Generator = Generators.AddDefaulted_GetRef();
	Generator.Id = NextGeneratorId++;
	Generator.Name = (Name != NAME_None) ? Name : FName(*FString::Printf(TEXT("Generador %d"), Generator.Id));
	Generator.Seed = Generator.Id;
	return Generator.Id;
}

bool UFramework2DTileSet::RemoveGenerator(int32 GeneratorId)
{
	const int32 Index = FindGeneratorIndex(GeneratorId);
	if (Index == INDEX_NONE) { return false; }
	Generators.RemoveAt(Index);
	// Los adornos (o piezas) de los biomas que lo usaban dejan de apuntar a el.
	const int32 Value = Framework2D::MakeGeneratorValue(GeneratorId);
	ClearBiomeValues([Value](int32 Piece) { return Piece == Value; });
	return true;
}

int32 UFramework2DTileSet::FindGeneratorIndex(int32 GeneratorId) const
{
	for (int32 i = 0; i < Generators.Num(); ++i)
	{
		if (Generators[i].Id == GeneratorId) { return i; }
	}
	return INDEX_NONE;
}

const FFramework2DGenerator* UFramework2DTileSet::FindGeneratorByValue(int32 Value) const
{
	if (!Framework2D::IsGeneratorValue(Value)) { return nullptr; }
	const int32 Index = FindGeneratorIndex(Framework2D::GeneratorIdFromValue(Value));
	return Index != INDEX_NONE ? &Generators[Index] : nullptr;
}

FFramework2DGenerator* UFramework2DTileSet::FindGeneratorById(int32 GeneratorId)
{
	const int32 Index = FindGeneratorIndex(GeneratorId);
	return Index != INDEX_NONE ? &Generators[Index] : nullptr;
}

//---------------------- Biomas (generador procedural) ----------------------

int32 UFramework2DTileSet::AddBiome(FName Name)
{
	Framework2DFixIds(Biomes, NextBiomeId);
	FFramework2DBiome& Biome = Biomes.AddDefaulted_GetRef();
	Biome.Id = NextBiomeId++;
	Biome.Name = (Name != NAME_None) ? Name : FName(*FString::Printf(TEXT("Bioma %d"), Biome.Id));
	return Biome.Id;
}

bool UFramework2DTileSet::RemoveBiome(int32 BiomeId)
{
	const int32 Index = FindBiomeIndex(BiomeId);
	if (Index == INDEX_NONE) { return false; }
	// NextBiomeId no baja: una receta que apuntaba al borrado no acaba en otro bioma nuevo.
	Biomes.RemoveAt(Index);
	return true;
}

int32 UFramework2DTileSet::FindBiomeIndex(int32 BiomeId) const
{
	for (int32 i = 0; i < Biomes.Num(); ++i)
	{
		if (Biomes[i].Id == BiomeId) { return i; }
	}
	return INDEX_NONE;
}

const FFramework2DBiome* UFramework2DTileSet::FindBiomeById(int32 BiomeId) const
{
	const int32 Index = FindBiomeIndex(BiomeId);
	return Index != INDEX_NONE ? &Biomes[Index] : nullptr;
}

FFramework2DBiome* UFramework2DTileSet::FindBiomeByIdMutable(int32 BiomeId)
{
	const int32 Index = FindBiomeIndex(BiomeId);
	return Index != INDEX_NONE ? &Biomes[Index] : nullptr;
}

const FFramework2DBiome* UFramework2DTileSet::ResolveBiome(int32 BiomeId) const
{
	if (const FFramework2DBiome* Found = FindBiomeById(BiomeId)) { return Found; }
	return Biomes.Num() > 0 ? &Biomes[0] : nullptr;
}

int32 UFramework2DTileSet::ClearBiomeValues(TFunctionRef<bool(int32)> Predicate)
{
	int32 Cleared = 0;
	for (FFramework2DBiome& Biome : Biomes)
	{
		// Piezas sueltas (3x3, esquinas, rampas, plataformas, fondo, agua, cascada): quedan a -1.
		for (int32 SlotIndex = 0; SlotIndex < (int32)EFramework2DBiomeSlot::Count; ++SlotIndex)
		{
			int32* Piece = Framework2D::BiomeSlotRef(Biome, (EFramework2DBiomeSlot)SlotIndex);
			if (Piece && *Piece >= 0 && Predicate(*Piece))
			{
				*Piece = -1;
				++Cleared;
			}
		}
		// Listas: las variantes y los adornos que apuntaban a lo borrado se quitan.
		Cleared += Biome.CenterVariants.RemoveAll([&Predicate](int32 Value) { return Value >= 0 && Predicate(Value); });
		Cleared += Biome.Decorations.RemoveAll([&Predicate](const FFramework2DBiomeDecoration& Deco) { return Deco.Value >= 0 && Predicate(Deco.Value); });
	}
	return Cleared;
}

void UFramework2DTileSet::FixUpIds()
{
	Framework2DFixIds(ExtraAtlases, NextAtlasId);
	Framework2DFixIds(Generators, NextGeneratorId);
	Framework2DFixIds(Biomes, NextBiomeId);
	Framework2DFixIds(Props, NextPropId);
}

//---------------------- Objetos grandes ----------------------

int32 UFramework2DTileSet::FindOrAddProp(UTexture2D* Texture)
{
	if (!Texture) { return INDEX_NONE; }
	for (const FFramework2DPropDef& Existing : Props)
	{
		if (Existing.Texture == Texture) { return Existing.Id; }
	}
	Framework2DFixIds(Props, NextPropId);
	FFramework2DPropDef& Prop = Props.AddDefaulted_GetRef();
	Prop.Id = NextPropId++;
	Prop.Name = Texture->GetFName();
	Prop.Texture = Texture;
	return Prop.Id;
}

int32 UFramework2DTileSet::FindOrAddAtlasProp(int32 TopLeftTile, int32 WidthTiles, int32 HeightTiles, FName Name)
{
	if (!Framework2D::IsAtlasTileValue(TopLeftTile)) { return INDEX_NONE; }
	WidthTiles = FMath::Clamp(WidthTiles, 1, 64);
	HeightTiles = FMath::Clamp(HeightTiles, 1, 64);
	for (const FFramework2DPropDef& Existing : Props)
	{
		if (!Existing.Texture && Existing.AtlasTile == TopLeftTile && Existing.AtlasWidthTiles == WidthTiles && Existing.AtlasHeightTiles == HeightTiles) { return Existing.Id; }
	}
	Framework2DFixIds(Props, NextPropId);
	FFramework2DPropDef& Prop = Props.AddDefaulted_GetRef();
	Prop.Id = NextPropId++;
	Prop.Name = Name != NAME_None ? Name : FName(*FString::Printf(TEXT("Objeto %d"), Prop.Id));
	Prop.AtlasTile = TopLeftTile;
	Prop.AtlasWidthTiles = WidthTiles;
	Prop.AtlasHeightTiles = HeightTiles;
	return Prop.Id;
}

bool UFramework2DTileSet::RemoveProp(int32 PropId)
{
	const int32 Index = FindPropIndex(PropId);
	if (Index == INDEX_NONE) { return false; }
	Props.RemoveAt(Index);
	for (FFramework2DBiome& Biome : Biomes)
	{
		Biome.Props.RemoveAll([PropId](const FFramework2DBiomeProp& Entry) { return Entry.PropId == PropId; });
	}
	return true;
}

int32 UFramework2DTileSet::FindPropIndex(int32 PropId) const
{
	for (int32 i = 0; i < Props.Num(); ++i)
	{
		if (Props[i].Id == PropId) { return i; }
	}
	return INDEX_NONE;
}

const FFramework2DPropDef* UFramework2DTileSet::FindPropById(int32 PropId) const
{
	const int32 Index = FindPropIndex(PropId);
	return Index != INDEX_NONE ? &Props[Index] : nullptr;
}

bool UFramework2DTileSet::ReadPropPixels(int32 PropId, TArray<FColor>& OutPixels, int32& OutWidth, int32& OutHeight) const
{
	const FFramework2DPropDef* Prop = FindPropById(PropId);
	if (!Prop) { OutPixels.Reset(); OutWidth = OutHeight = 0; return false; }
	if (!Prop->Texture && Prop->AtlasTile >= 0)
	{
		// Un trozo del atlas: se copia de la imagen de su pagina.
		int32 PageId = 0, Ox = 0, Oy = 0, PW = 0, PH = 0;
		TArray<FColor> Page;
		if (!GetTileValueOrigin(Prop->AtlasTile, PageId, Ox, Oy) || !ReadPagePixels(PageId, Page, PW, PH)) { OutPixels.Reset(); OutWidth = OutHeight = 0; return false; }
		OutWidth = FMath::Min(Prop->AtlasWidthTiles * TileWidth, PW - Ox);
		OutHeight = FMath::Min(Prop->AtlasHeightTiles * TileHeight, PH - Oy);
		OutPixels.SetNumUninitialized(OutWidth * OutHeight);
		for (int32 y = 0; y < OutHeight; ++y)
		{
			FMemory::Memcpy(OutPixels.GetData() + y * OutWidth, Page.GetData() + (Oy + y) * PW + Ox, OutWidth * sizeof(FColor));
		}
		return OutWidth > 0 && OutHeight > 0;
	}
	return Framework2DReadImage(Prop->Texture, Prop->PixelCache, Prop->CacheWidth, Prop->CacheHeight, OutPixels, OutWidth, OutHeight);
}

bool UFramework2DTileSet::GetPropSize(int32 PropId, int32& OutWidth, int32& OutHeight) const
{
	const FFramework2DPropDef* Prop = FindPropById(PropId);
	if (!Prop) { OutWidth = OutHeight = 0; return false; }
	if (!Prop->Texture && Prop->AtlasTile >= 0)
	{
		int32 PageId = 0, Ox = 0, Oy = 0;
		if (!GetTileValueOrigin(Prop->AtlasTile, PageId, Ox, Oy)) { OutWidth = OutHeight = 0; return false; }
		OutWidth = Prop->AtlasWidthTiles * TileWidth;
		OutHeight = Prop->AtlasHeightTiles * TileHeight;
		return true;
	}
	return Framework2DImageSize(Prop->Texture, Prop->CacheWidth, Prop->CacheHeight, OutWidth, OutHeight);
}

//---------------------- Atlas ----------------------

bool UFramework2DTileSet::ReadAtlasPixels(TArray<FColor>& OutPixels, int32& OutWidth, int32& OutHeight) const
{
	OutWidth = 0;
	OutHeight = 0;
	OutPixels.Reset();
	if (!Atlas) { return false; }

#if WITH_EDITOR
	// Editor: el PNG original siempre esta al dia (aunque no se haya guardado el tileset).
	if (Framework2DDecodeTextureSource(Atlas, OutPixels, OutWidth, OutHeight)) { return true; }
#endif

	// Juego empaquetado: la copia guardada con el asset.
	if (AtlasCacheWidth > 0 && AtlasCacheHeight > 0 && AtlasPixelCache.Num() == AtlasCacheWidth * AtlasCacheHeight)
	{
		OutPixels = AtlasPixelCache;
		OutWidth = AtlasCacheWidth;
		OutHeight = AtlasCacheHeight;
		return true;
	}

	UE_LOG(LogTemp, Warning,
		TEXT("[Framework2DTerrain] No se pudo leer el atlas del tileset '%s'. Abrelo en el editor y guardalo (Ctrl+S)."), *GetName());
	return false;
}

bool UFramework2DTileSet::GetAtlasSize(int32& OutWidth, int32& OutHeight) const
{
	OutWidth = 0;
	OutHeight = 0;
	if (!Atlas) { return false; }
#if WITH_EDITOR
	if (Atlas->Source.IsValid())
	{
		OutWidth = Atlas->Source.GetSizeX();
		OutHeight = Atlas->Source.GetSizeY();
		return OutWidth > 0 && OutHeight > 0;
	}
#endif
	OutWidth = AtlasCacheWidth;
	OutHeight = AtlasCacheHeight;
	return OutWidth > 0 && OutHeight > 0;
}

bool UFramework2DTileSet::GetTilePixelOrigin(int32 Index, int32 AtlasWidth, int32& OutX, int32& OutY) const
{
	const int32 TW = FMath::Max(1, TileWidth);
	const int32 TH = FMath::Max(1, TileHeight);
	const int32 PerRow = FMath::Max(1, AtlasWidth / TW);
	if (Index < 0) { OutX = OutY = 0; return false; }
	OutX = (Index % PerRow) * TW;
	OutY = (Index / PerRow) * TH;
	return true;
}

TArray<FString> UFramework2DTileSet::GetMaterialNameOptions() const
{
	TArray<FString> Options;
	Options.Add(TEXT("None"));
	for (const FFramework2DMaterial& M : Materials)
	{
		if (M.Name != NAME_None) { Options.Add(M.Name.ToString()); }
	}
	return Options;
}

void UFramework2DTileSet::RefreshTilesFromAtlas()
{
	int32 W = 0, H = 0;
	if (!GetAtlasSize(W, H))
	{
		Columns = Rows = 0;
		for (FFramework2DAtlasPage& Page : ExtraAtlases) { RefreshPage(Page); }
		return;
	}
	Columns = FMath::Max(0, W / FMath::Max(1, TileWidth));
	Rows = FMath::Max(0, H / FMath::Max(1, TileHeight));
	const int32 Wanted = Columns * Rows;
	if (Tiles.Num() != Wanted)
	{
		const int32 OldNum = Tiles.Num();
		Tiles.SetNum(Wanted);
		// Los tiles nuevos nacen como el primer material, que es lo habitual (terreno).
		for (int32 i = OldNum; i < Wanted; ++i)
		{
			Tiles[i].MaterialName = Materials.Num() > 0 ? Materials[0].Name : NAME_None;
		}
	}
	for (FFramework2DAtlasPage& Page : ExtraAtlases) { RefreshPage(Page); }
}

//---------------------- Migracion y ciclo de vida ----------------------

int32 UFramework2DTileSet::MigrateLegacyFlipbooks()
{
	for (const FFramework2DFlipbook& Existing : Flipbooks)
	{
		NextFlipbookId = FMath::Max(NextFlipbookId, Existing.Id + 1);
	}
	NextFlipbookId = FMath::Max(NextFlipbookId, 1);

	int32 Created = 0;
	for (FFramework2DTileDef& Tile : Tiles)
	{
		if (Tile.AnimationFrames.Num() == 0) { continue; }
		// En la v2.0 el flipbook pisaba el tile: ahora va a su lista y el tile vuelve a ser estatico.
		if (Tile.AnimationFrames.Num() >= 2)
		{
			FFramework2DFlipbook Flipbook;
			Flipbook.Id = NextFlipbookId++;
			Flipbook.Name = Framework2DDefaultFlipbookName(Flipbook.Id);
			Flipbook.Frames = Tile.AnimationFrames;
			Flipbook.FPS = FMath::Clamp(Tile.AnimationFPS, 0.1f, 60.0f);
			Flipbook.MaterialName = Tile.MaterialName;
			Flipbook.Collision = EFramework2DCollisionShape::Auto;
			Flipbooks.Add(MoveTemp(Flipbook));
			++Created;
		}
		// Con un solo fotograma nunca se animo: basta con vaciarlo.
		Tile.AnimationFrames.Reset();
		Tile.AnimationFPS = 8.0f;
	}
	return Created;
}

void UFramework2DTileSet::PostLoad()
{
	Super::PostLoad();

	// Sin marcar el paquete sucio: la migracion se repite igual en cada carga hasta que se guarde.
	const int32 Migrated = MigrateLegacyFlipbooks();
	if (Migrated > 0)
	{
		UE_LOG(LogTemp, Log,
			TEXT("[Framework2DTerrain] TileSet '%s': %d flipbook(s) de la v2.0 pasados a la lista Flipbooks. Los tiles del atlas vuelven a ser estaticos; pinta los flipbooks desde su seccion de la paleta y guarda el tileset para conservar el cambio."),
			*GetName(), Migrated);
	}
}

void UFramework2DTileSet::PreSave(FObjectPreSaveContext SaveContext)
{
	// Tambien se llama al COCINAR el juego: asi el empaquetado lleva el atlas en CPU.
#if WITH_EDITOR
	TArray<FColor> Pixels;
	int32 W = 0, H = 0;
	if (Atlas && Framework2DDecodeTextureSource(Atlas, Pixels, W, H))
	{
		AtlasPixelCache = MoveTemp(Pixels);
		AtlasCacheWidth = W;
		AtlasCacheHeight = H;
	}
	else
	{
		AtlasPixelCache.Reset();
		AtlasCacheWidth = 0;
		AtlasCacheHeight = 0;
	}
	for (FFramework2DAtlasPage& Page : ExtraAtlases)
	{
		TArray<FColor> PagePixels;
		int32 PW = 0, PH = 0;
		if (Page.Texture && Framework2DDecodeTextureSource(Page.Texture, PagePixels, PW, PH))
		{
			Page.PixelCache = MoveTemp(PagePixels);
			Page.CacheWidth = PW;
			Page.CacheHeight = PH;
		}
		else
		{
			Page.PixelCache.Reset();
			Page.CacheWidth = Page.CacheHeight = 0;
		}
	}
	// Los objetos grandes tambien se hornean en el juego: su imagen en CPU va con el tileset.
	for (FFramework2DPropDef& Prop : Props)
	{
		TArray<FColor> PropPixels;
		int32 PW = 0, PH = 0;
		if (Prop.Texture && Framework2DDecodeTextureSource(Prop.Texture, PropPixels, PW, PH))
		{
			Prop.PixelCache = MoveTemp(PropPixels);
			Prop.CacheWidth = PW;
			Prop.CacheHeight = PH;
		}
		else
		{
			Prop.PixelCache.Reset();
			Prop.CacheWidth = Prop.CacheHeight = 0;
		}
	}
#endif
	Super::PreSave(SaveContext);
}

#if WITH_EDITOR
void UFramework2DTileSet::PreEditChange(FProperty* PropertyAboutToChange)
{
	Super::PreEditChange(PropertyAboutToChange);
	PreEditFlipbookIds.Reset();
	for (const FFramework2DFlipbook& Flipbook : Flipbooks) { PreEditFlipbookIds.Add(Flipbook.Id); }
}

void UFramework2DTileSet::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	const FName Prop = PropertyChangedEvent.GetPropertyName();
	// MemberProperty: el miembro del objeto (Flipbooks) aunque cambie algo dentro de un elemento.
	const FName MemberProp = PropertyChangedEvent.MemberProperty ? PropertyChangedEvent.MemberProperty->GetFName() : NAME_None;
	if (Prop == GET_MEMBER_NAME_CHECKED(UFramework2DTileSet, Atlas) ||
		Prop == GET_MEMBER_NAME_CHECKED(UFramework2DTileSet, TileWidth) ||
		Prop == GET_MEMBER_NAME_CHECKED(UFramework2DTileSet, TileHeight))
	{
		RefreshTilesFromAtlas();
	}

	// Paginas, generadores y biomas anadidos o duplicados en Details: Id nuevo (y tiles de la imagen).
	if (MemberProp == GET_MEMBER_NAME_CHECKED(UFramework2DTileSet, ExtraAtlases) ||
		MemberProp == GET_MEMBER_NAME_CHECKED(UFramework2DTileSet, Generators) ||
		MemberProp == GET_MEMBER_NAME_CHECKED(UFramework2DTileSet, Biomes) ||
		MemberProp == GET_MEMBER_NAME_CHECKED(UFramework2DTileSet, Props))
	{
		FixUpIds();
		for (FFramework2DAtlasPage& Page : ExtraAtlases) { RefreshPage(Page); }
	}

	if (Prop == GET_MEMBER_NAME_CHECKED(UFramework2DTileSet, Flipbooks) ||
		MemberProp == GET_MEMBER_NAME_CHECKED(UFramework2DTileSet, Flipbooks))
	{
		// Un flipbook anadido con el "+" del Details nace con Id 0, y uno duplicado repite el
		// del original: les damos uno nuevo. El primero que aparece conserva el suyo (el mapa
		// ya apunta a el).
		for (const FFramework2DFlipbook& Existing : Flipbooks)
		{
			NextFlipbookId = FMath::Max(NextFlipbookId, Existing.Id + 1);
		}
		NextFlipbookId = FMath::Max(NextFlipbookId, 1);

		// Pegar un flipbook sobre otro (Copy/Paste en Details) copia tambien su Id oculto. El
		// flipbook pegado recupera el suyo de antes: las celdas del mapa que lo usaban siguen
		// apuntando a el (ahora con el contenido pegado) y el original no pierde las suyas.
		if (Flipbooks.Num() == PreEditFlipbookIds.Num())
		{
			TMap<int32, int32> IdCount;
			for (const FFramework2DFlipbook& Flipbook : Flipbooks) { ++IdCount.FindOrAdd(Flipbook.Id); }
			for (int32 i = 0; i < Flipbooks.Num(); ++i)
			{
				const int32 OldId = PreEditFlipbookIds[i];
				int32& Count = IdCount.FindOrAdd(Flipbooks[i].Id);
				if (Flipbooks[i].Id != OldId && Count > 1 && OldId > 0 && !IdCount.Contains(OldId))
				{
					--Count;
					Flipbooks[i].Id = OldId;
					IdCount.Add(OldId, 1);
				}
			}
		}

		TSet<int32> SeenIds;
		for (FFramework2DFlipbook& Flipbook : Flipbooks)
		{
			bool bAlreadySeen = false;
			if (Flipbook.Id > 0) { SeenIds.Add(Flipbook.Id, &bAlreadySeen); }
			if (Flipbook.Id <= 0 || bAlreadySeen)
			{
				Flipbook.Id = NextFlipbookId++;
				SeenIds.Add(Flipbook.Id);
				if (Flipbook.Name == NAME_None || Flipbook.Name == FName(TEXT("Flipbook")))
				{
					Flipbook.Name = Framework2DDefaultFlipbookName(Flipbook.Id);
				}
			}
		}
	}
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif
