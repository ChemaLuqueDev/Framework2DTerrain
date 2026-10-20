// Copyright Chema Luque. Plugin Framework2DTerrain.

#include "Framework2DTerrainWorld.h"

#include "Framework2DCollisionChunkComponent.h"
#include "Framework2DBackdropComponent.h"
#include "Framework2DProcGen.h"
#include "Framework2DTileMapAsset.h"
#include "Framework2DTileSet.h"
#include "CollisionQueryParams.h"
#include "Engine/Texture2D.h"
#include "Engine/World.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
#include "Misc/App.h"
#include "ProceduralMeshComponent.h"
#include "TextureResource.h"
#include "UObject/ConstructorHelpers.h"
#include "Async/ParallelFor.h"
#include "WorldCollision.h"
#if __has_include("Engine/OverlapResult.h")
#include "Engine/OverlapResult.h" // UE 5.1+ (en 5.0 FOverlapResult viene con EngineTypes.h)
#endif

// =====================================================================
//  Utilidades locales (sin estado)
// =====================================================================
namespace Framework2DTerrainLocal
{
	// Hash entero estable: mismo (X,Y,Seed) => mismo resultado (rotura reproducible).
	FORCEINLINE uint32 Hash3(int32 X, int32 Y, uint32 Seed)
	{
		uint32 H = (uint32)X * 374761393u + (uint32)Y * 668265263u + Seed * 2246822519u;
		H = (H ^ (H >> 13)) * 1274126177u;
		return H ^ (H >> 16);
	}

	FORCEINLINE float Hash01(int32 X, int32 Y, uint32 Seed)
	{
		return (float)(Hash3(X, Y, Seed) & 0xFFFFFFu) / 16777216.0f;
	}

	FORCEINLINE uint8 LerpByte(uint8 A, uint8 B, float T)
	{
		return (uint8)FMath::Clamp(FMath::RoundToInt((float)A + ((float)B - (float)A) * T), 0, 255);
	}

	FORCEINLINE FColor LerpColor(const FColor& A, const FColor& B, float T)
	{
		T = FMath::Clamp(T, 0.0f, 1.0f);
		return FColor(LerpByte(A.R, B.R, T), LerpByte(A.G, B.G, T), LerpByte(A.B, B.B, T), LerpByte(A.A, B.A, T));
	}

	// Pixel de una capa de fondo: ya oscurecido y opaco.
	FORCEINLINE FColor Darken(const FColor& C, float Mul)
	{
		return FColor((uint8)(C.R * Mul), (uint8)(C.G * Mul), (uint8)(C.B * Mul), 255);
	}

	constexpr uint8 AlphaThreshold = 128; // pixel del atlas con menos alfa = aire
	constexpr int32 MaxTextureSize = 16384;
}
using namespace Framework2DTerrainLocal;

// =====================================================================
//  Construccion
// =====================================================================
AFramework2DTerrainWorld::AFramework2DTerrainWorld()
{
	PrimaryActorTick.bCanEverTick = true;

	RenderMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("RenderMesh"));
	RootComponent = RenderMesh;
	RenderMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RenderMesh->SetCastShadow(false);

	BackdropMesh = CreateDefaultSubobject<UFramework2DBackdropComponent>(TEXT("BackdropMesh"));
	BackdropMesh->SetupAttachment(RenderMesh);

	// Material por defecto: el de sprites de Paper2D (sin luz y con el aire transparente).
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> SpriteMaterial(TEXT("/Paper2D/DefaultSpriteMaterial.DefaultSpriteMaterial"));
	if (SpriteMaterial.Succeeded())
	{
		TerrainMaterial = SpriteMaterial.Object;
	}

	FMemory::Memzero(EdgeMask, sizeof(EdgeMask));
}

void AFramework2DTerrainWorld::BeginPlay()
{
	Super::BeginPlay();
	BuildTerrain(/*bForGameplay*/ true);
}

void AFramework2DTerrainWorld::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!bBuilt) { return; }

	// Los flipbooks se animan tambien en el editor (vista previa); lo demas solo en juego.
	UpdateAnimations(DeltaSeconds);
	if (bGameplay) { UpdateDebris(DeltaSeconds); }
	FlushVisual();
	if (bGameplay && bCollisionDirty)
	{
		RebuildDirtyCollision();
	}
}

void AFramework2DTerrainWorld::PostRegisterAllComponents()
{
	Super::PostRegisterAllComponents();
	// Vista previa en el editor: el nivel se ve tal cual sin dar a Play.
	UWorld* World = GetWorld();
	if (!bBuilt && World && !World->IsGameWorld() && !HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject))
	{
		RebuildPreview();
	}
}

#if WITH_EDITOR
void AFramework2DTerrainWorld::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	// La separacion solo mueve los planos: no hace falta rehornear (y arrastrarla es fluido).
	if (bBuilt && PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(AFramework2DTerrainWorld, LayerSeparation))
	{
		UpdateLayerDepths();
		return;
	}
	RebuildPreview();
}
#endif

void AFramework2DTerrainWorld::RebuildPreview()
{
	UWorld* World = GetWorld();
	if (!World || World->IsGameWorld() || !FApp::CanEverRender()) { return; }
	BuildTerrain(/*bForGameplay*/ false);
}

void AFramework2DTerrainWorld::RefreshPreviewTiles(const FIntRect& TileRect)
{
	// Si el mapa cambio de tamano o de tileset, toca reconstruir entero.
	const UFramework2DTileSet* Set = TileMap ? TileMap->TileSet.Get() : nullptr;
	bool bRebuild = !bBuilt || !Set || TileMap->Width * CellsPerTile != GridWidth || TileMap->Height * CellsPerTile != GridHeight ||
		FMath::Clamp(Set->TileWidth, 1, 256) != CellsPerTile;

	// Capas mostradas u ocultadas, movidas, de otro tipo o a otra profundidad: hay que rehacer los planos.
	if (!bRebuild)
	{
		int32 Slot = 0;
		for (int32 L = 0; L < TileMap->Layers.Num() && !bRebuild; ++L)
		{
			const FFramework2DTileLayer& Layer = TileMap->Layers[L];
			if (!Layer.bVisible) { continue; }
			if (!RLayers.IsValidIndex(Slot)) { bRebuild = true; break; }
			const FLayerRuntime& R = RLayers[Slot++];
			bRebuild = R.MapLayer != L || R.bBackground != Layer.bBackground ||
				R.bCollides != (!Layer.bBackground && Layer.bCollides) ||
				R.bBreakable != (!Layer.bBackground && Layer.bBreakable) ||
				!FMath::IsNearlyEqual(R.DepthY, GetLayerDepth(L));
		}
		bRebuild = bRebuild || Slot != RLayers.Num();
	}
	if (bRebuild)
	{
		RebuildPreview();
		return;
	}
	BakeTiles(TileRect);
	FlushVisual();
}

void AFramework2DTerrainWorld::ResetTerrain()
{
	BuildTerrain(bGameplay || (GetWorld() && GetWorld()->IsGameWorld()));
}

FFramework2DProcGenReport AFramework2DTerrainWorld::GenerateProceduralLevel(int32 Seed)
{
	if (!TileMap)
	{
		FFramework2DProcGenReport Missing;
		Missing.Message = TEXT("The terrain has no Tile Map: assign one to generate a level.");
		return Missing;
	}

	// La receta del Tile Map con la semilla pedida (-1 = una al azar: cada partida, un nivel distinto).
	FFramework2DProcGenSettings Settings = TileMap->ProcGen;
	Settings.Seed = Seed < 0 ? FMath::Rand() : Seed;

	UWorld* World = GetWorld();
	if (World && World->IsGameWorld())
	{
		// En juego se trabaja sobre una COPIA del Tile Map (la primera vez): el asset no cambia.
		if (!bOwnsRuntimeTileMap)
		{
			UFramework2DTileMapAsset* Copy = DuplicateObject<UFramework2DTileMapAsset>(TileMap.Get(), this);
			if (!Copy)
			{
				FFramework2DProcGenReport Failed;
				Failed.Message = TEXT("No se pudo copiar el Tile Map para generar el nivel.");
				return Failed;
			}
			// Sin Standalone ni Public: la copia vive y muere con el terreno (si no, retendria el
			// mundo al salir de Play). Transitoria: nunca se guarda.
			Copy->ClearFlags(RF_Public | RF_Standalone | RF_Transactional);
			Copy->SetFlags(RF_Transient);
			TileMap = Copy;
			bOwnsRuntimeTileMap = true;
		}
		const FFramework2DProcGenReport GameReport = UFramework2DProcGenLibrary::GenerateMapWithSettings(TileMap.Get(), Settings);
		if (GameReport.bSuccess)
		{
			TileMap->ProcGen.Seed = Settings.Seed; // la copia recuerda con que semilla salio
			BuildTerrain(/*bForGameplay*/ true);
		}
		return GameReport;
	}

	// Editor: cambia el asset (con deshacer si quien llama abrio una transaccion).
	TileMap->SetFlags(RF_Transactional);
	TileMap->Modify();
	const FFramework2DProcGenReport EditorReport = UFramework2DProcGenLibrary::GenerateMapWithSettings(TileMap.Get(), Settings);
	if (EditorReport.bSuccess)
	{
		// La receta guarda la semilla usada: volver a generar da este mismo nivel.
		TileMap->ProcGen.Seed = Settings.Seed;
		RebuildPreview();
	}
	return EditorReport;
}

bool AFramework2DTerrainWorld::UsesAsset(const UObject* Asset) const
{
	if (!Asset || !TileMap) { return false; }
	if (Asset == TileMap) { return true; }
	const UFramework2DTileSet* Set = TileMap->TileSet;
	return Set && (Asset == Set || Asset == Set->Atlas);
}

bool AFramework2DTerrainWorld::BuildTerrain(bool bForGameplay)
{
	bBuilt = false;
	bGameplay = bForGameplay;
	bVisualDirty = false;
	bCollisionDirty = false;
	++ContentRevision;
	Debris.Reset();
	DebrisChunksLastFrame.Reset();
	AnimDirtyTiles.Reset();
	AnimatedTiles.Reset();
	AnimTime = 0.0;
	DestroyCollisionChunks();
	GridWidth = 0;
	GridHeight = 0;
	// Las capas de la construccion anterior se guardan para reutilizar su memoria: reservar y
	// soltar cientos de MB en cada regeneracion era lo que mas tardaba con mapas grandes.
	TArray<FLayerRuntime> OldLayers = MoveTemp(RLayers);
	RLayers.Reset();
	ChunksX = ChunksY = 0;
	ChunkRebuild.Reset();
	ChunkUpload.Reset();
	if (RenderMesh)
	{
		// Fuera los planos (y sus materiales) de la construccion anterior: puede haber menos capas.
		RenderMesh->ClearAllMeshSections();
		RenderMesh->EmptyOverrideMaterials();
	}

	const UFramework2DTileSet* Set = TileMap ? TileMap->TileSet.Get() : nullptr;
	if (!Set)
	{
		if (bForGameplay)
		{
			UE_LOG(LogTemp, Warning, TEXT("[Framework2DTerrain] '%s' no tiene Tile Map (o el Tile Map no tiene Tile Set): no hay terreno."), *GetName());
		}
		return false;
	}

	// Un pixel del tile = una celda.
	CellsPerTile = FMath::Clamp(Set->TileWidth, 1, 256);
	const int64 W = (int64)TileMap->Width * CellsPerTile;
	const int64 H = (int64)TileMap->Height * CellsPerTile;
	if (W <= 0 || H <= 0 || W > MaxTextureSize || H > MaxTextureSize)
	{
		UE_LOG(LogTemp, Error,
			TEXT("[Framework2DTerrain] '%s': el nivel mide %lld x %lld pixeles y el maximo es %d. Reduce el Tile Map o el tamano de los tiles."),
			*GetName(), W, H, MaxTextureSize);
		return false;
	}
	GridWidth = (int32)W;
	GridHeight = (int32)H;

	ResolveMaterials(Set);
	ReadPages(Set);
	PrepareGenerators(Set);
	PrepareProps(Set);

	bCanRender = FApp::CanEverRender(); // un servidor dedicado no dibuja (ni guarda colores)

	// Un plano por capa VISIBLE del Tile Map, de atras a delante. Las ocultas no existen aqui.
	const int32 Num = GridWidth * GridHeight;
	RLayers.Reserve(TileMap->Layers.Num());
	for (int32 L = 0; L < TileMap->Layers.Num(); ++L)
	{
		const FFramework2DTileLayer& MapLayer = TileMap->Layers[L];
		if (!MapLayer.bVisible) { continue; }
		FLayerRuntime& Slot = RLayers.AddDefaulted_GetRef();
		Slot.MapLayer = L;
		Slot.bBackground = MapLayer.bBackground;
		Slot.bCollides = !MapLayer.bBackground && MapLayer.bCollides;   // el fondo nunca choca
		Slot.bBreakable = !MapLayer.bBackground && MapLayer.bBreakable; // ni se rompe
		Slot.DepthY = GetLayerDepth(L);
		// Sin inicializar: BakeTiles vacia la zona que hornea, y aqui es el mapa entero.
		const int32 Reuse = RLayers.Num() - 1;
		if (OldLayers.IsValidIndex(Reuse))
		{
			Slot.Cells = MoveTemp(OldLayers[Reuse].Cells);
			Slot.ArtColor = MoveTemp(OldLayers[Reuse].ArtColor);
			Slot.Damage = MoveTemp(OldLayers[Reuse].Damage);
		}
		Slot.Cells.SetNumUninitialized(Num);
		Slot.ArtColor.SetNumUninitialized(Num);
		// El dano solo existe en juego y en capas que se rompen.
		if (bForGameplay && Slot.bBreakable) { Slot.Damage.SetNumUninitialized(Num); }
		else { Slot.Damage.Empty(); }
	}
	OldLayers.Empty();
	if (RLayers.Num() == 0 && bForGameplay)
	{
		UE_LOG(LogTemp, Warning, TEXT("[Framework2DTerrain] '%s': el Tile Map no tiene ninguna capa visible. El terreno queda vacio."), *GetName());
	}

	CollisionMode.SetNumUninitialized(Num); // lo vacia BakeCollisionShapes (mapa entero)
	SolidMask.SetNumUninitialized(Num);     // lo rehace BakeTiles
	ChunksX = FMath::DivideAndRoundUp(GridWidth, ChunkSize);
	ChunksY = FMath::DivideAndRoundUp(GridHeight, ChunkSize);
	ChunkRebuild.Init(0, ChunksX * ChunksY);
	ChunkUpload.Init(0, ChunksX * ChunksY);

	BakeTiles(FIntRect(0, 0, TileMap->Width - 1, TileMap->Height - 1));
	BuildFillPatterns(Set);

	if (bCanRender)
	{
		CreateRenderResources();
	}
	RefreshBackdrops();

	bBuilt = true;
	MarkAllDirty();
	FlushVisual();

	if (bForGameplay && bGenerateCollision)
	{
		CreateCollisionChunks();
		RebuildDirtyCollision();
	}
	return true;
}

void AFramework2DTerrainWorld::ResolveMaterials(const UFramework2DTileSet* Set)
{
	// id 0 = aire. Los materiales del tileset son 1, 2, 3...
	ResolvedMaterials.Reset();
	ResolvedMaterials.AddDefaulted();
	ResolvedMaterials[0].Name = NAME_None;
	ResolvedMaterials[0].bCollides = false;
	NameToId.Reset();
	FMemory::Memzero(EdgeMask, sizeof(EdgeMask));

	for (const FFramework2DMaterial& M : Set->Materials)
	{
		if (ResolvedMaterials.Num() >= 256)
		{
			UE_LOG(LogTemp, Warning, TEXT("[Framework2DTerrain] Mas de 255 materiales en '%s': se ignoran los sobrantes."), *Set->GetName());
			break;
		}
		if (M.Name == NAME_None || NameToId.Contains(M.Name)) { continue; }
		const int32 Id = ResolvedMaterials.Add(M);
		NameToId.Add(M.Name, (uint8)Id);
		EdgeMask[Id] = M.bDrawEdge ? 1 : 0;
	}
}

void AFramework2DTerrainWorld::BakeTiles(const FIntRect& TileRect)
{
	const UFramework2DTileSet* Set = TileMap ? TileMap->TileSet.Get() : nullptr;
	if (!Set || GridWidth <= 0 || GridHeight <= 0) { return; }

	// Los sprites de los generadores se salen de su casilla: la zona crece lo que pueden
	// salirse, para que al pintar o borrar un generador no queden restos ni cortes. Igual con los
	// objetos apoyados en el suelo: si cambia el suelo bajo uno, se rehace entero.
	const int32 GM = GeneratorMarginTiles;
	const int32 Tx0 = FMath::Clamp(TileRect.Min.X - FMath::Max(GM, PropMarginSide), 0, TileMap->Width - 1);
	const int32 Ty0 = FMath::Clamp(TileRect.Min.Y - FMath::Max(GM, PropMarginUp), 0, TileMap->Height - 1);
	const int32 Tx1 = FMath::Clamp(TileRect.Max.X + FMath::Max(GM, PropMarginSide), 0, TileMap->Width - 1);
	const int32 Ty1 = FMath::Clamp(TileRect.Max.Y + FMath::Max(GM, PropMarginDown), 0, TileMap->Height - 1);
	if (Tx1 < Tx0 || Ty1 < Ty0) { return; }

	const int32 CPT = CellsPerTile;
	const int32 TW = FMath::Max(1, Set->TileWidth);
	const int32 TH = FMath::Max(1, Set->TileHeight);
	const bool bHasAtlas = PagesCPU.Num() > 0;
	const float BackMul = FMath::Clamp(BackgroundBrightness, 0.0f, 1.0f);

	// 1) Vaciar la zona en todas las capas: se vuelve a hornear desde cero (con sus flipbooks).
	AnimatedTiles.RemoveAll([Tx0, Ty0, Tx1, Ty1](const FAnimatedTile& A) { return A.Tx >= Tx0 && A.Tx <= Tx1 && A.Ty >= Ty0 && A.Ty <= Ty1; });
	const int32 X0 = Tx0 * CPT, Y0 = Ty0 * CPT;
	const int32 X1 = (Tx1 + 1) * CPT - 1, Y1 = (Ty1 + 1) * CPT - 1;
	const int32 RowLen = X1 - X0 + 1;
	const int32 NumRows = Y1 - Y0 + 1;
	const int32 NumPixels = GridWidth * GridHeight;
	for (FLayerRuntime& L : RLayers)
	{
		ParallelFor(NumRows, [&](int32 Row)
		{
			const int32 I = Index(X0, Y0 + Row);
			FMemory::Memzero(L.Cells.GetData() + I, (SIZE_T)RowLen);
			if (L.Damage.Num() == NumPixels) { FMemory::Memzero(L.Damage.GetData() + I, (SIZE_T)RowLen); }
			FMemory::Memzero(L.ArtColor.GetData() + I, (SIZE_T)RowLen * sizeof(FColor)); // FColor(0,0,0,0)
		}, NumRows < 64);
	}

	// Pixel (cx, cy) de un tile (de cualquier pagina), escalado a CPT. False si no se puede dibujar.
	auto Sample = [&](int32 AtlasTile, int32 cx, int32 cy, FColor& Out) -> bool
	{
		int32 Fx = 0, Fy = 0;
		const FPageCPU* FramePage = TileOrigin(AtlasTile, Fx, Fy);
		if (!FramePage) { return false; }
		Out = FramePage->Pixels[(Fy + (cy * TH) / CPT) * FramePage->W + (Fx + (cx * TW) / CPT)];
		return true;
	};

	// 2) Cada capa visible en su plano. Sus pixeles transparentes son aire en ESA capa. En paralelo:
	// una tarea por (capa, fila de tiles); cada una escribe solo sus pixeles y apunta sus flipbooks
	// aparte (se juntan despues, en orden).
	const int32 TileRows = Ty1 - Ty0 + 1;
	const int32 NumTasks = RLayers.Num() * TileRows;
	TArray<TArray<FAnimatedTile>> TaskAnims;
	TaskAnims.SetNum(NumTasks);
	ParallelFor(NumTasks, [&](int32 Task)
	{
		const int32 S = Task / TileRows;
		const int32 ty = Ty0 + Task % TileRows;
		FLayerRuntime& L = RLayers[S];
		const bool bBackLayer = L.bBackground;
		{
			for (int32 tx = Tx0; tx <= Tx1; ++tx)
			{
				const int32 Value = TileMap->At(L.MapLayer, tx, ty);
				if (Value < 0) { continue; }

				// Tile o flipbook: el material sale del TileSet en los dos casos.
				const uint8 Id = FindMaterialId(Set->GetTileMaterial(Value));
				if (!bBackLayer && Id == 0) { continue; } // tile sin material: no es terreno

				// Tile del atlas que se ve ahora (primer fotograma si es flipbook). -1 = flipbook borrado o vacio.
				const int32 ShownTile = Set->GetFrameTile(Value, 0.0);
				if (ShownTile < 0) { continue; }

				int32 Ox = 0, Oy = 0;
				const FPageCPU* Page = TileOrigin(ShownTile, Ox, Oy);
				const bool bTileInAtlas = Page != nullptr;
				if (bBackLayer && !bTileInAtlas && Id == 0) { continue; } // fondo sin dibujo ni color

				// Flipbook: se hornea su primer fotograma; la forma es la UNION de todos los
				// fotogramas (un pixel que solo existe en otro fotograma se ve como hueco ahora).
				const FFramework2DFlipbook* Flipbook = (bHasAtlas && Set->IsAnimated(Value)) ? Set->FindFlipbookByValue(Value) : nullptr;
				if (Flipbook)
				{
					FAnimatedTile Anim;
					Anim.Slot = S; Anim.Tx = tx; Anim.Ty = ty; Anim.Value = Value; Anim.ShownTile = ShownTile;
					TaskAnims[Task].Add(Anim);
				}

				for (int32 cy = 0; cy < CPT; ++cy)
				{
					for (int32 cx = 0; cx < CPT; ++cx)
					{
						const int32 I = Index(tx * CPT + cx, ty * CPT + cy);
						FColor Px(0, 0, 0, 0);
						bool bHiddenNow = false; // pixel del flipbook que existe, pero no en este fotograma
						if (bTileInAtlas)
						{
							Px = Page->Pixels[(Oy + (cy * TH) / CPT) * Page->W + (Ox + (cx * TW) / CPT)];
							if (Px.A < AlphaThreshold)
							{
								bool bInOtherFrame = false;
								if (Flipbook)
								{
									for (const int32 Frame : Flipbook->Frames)
									{
										FColor Fp;
										if (Frame != ShownTile && Sample(Frame, cx, cy, Fp) && Fp.A >= AlphaThreshold) { bInOtherFrame = true; break; }
									}
								}
								if (!bInOtherFrame) { continue; } // transparente = aire
								bHiddenNow = true;
							}
						}

						L.Cells[I] = Id;
						if (bHiddenNow)
						{
							L.ArtColor[I] = FColor(0, 0, 0, 1);
						}
						else if (bBackLayer)
						{
							// Fondo: el dibujo ya oscurecido (o el color del material si el tile no tiene dibujo).
							L.ArtColor[I] = Darken(bTileInAtlas ? Px : ResolvedMaterials[Id].Color, BackMul);
						}
						else
						{
							L.ArtColor[I] = bTileInAtlas ? FColor(Px.R, Px.G, Px.B, 255) : FColor(0, 0, 0, 0);
						}
					}
				}
			}
		}
	});
	for (TArray<FAnimatedTile>& Anims : TaskAnims) { AnimatedTiles.Append(MoveTemp(Anims)); }

	// 3) Objetos grandes y generadores de vegetacion, encima de lo ya horneado. Los objetos van
	// primero: la vegetacion generada no pisa lo que ya hay en su capa y crece a su alrededor.
	StampProps(FIntRect(X0, Y0, X1, Y1));
	StampGenerators(FIntRect(Tx0, Ty0, Tx1, Ty1), FIntRect(X0, Y0, X1, Y1));
	RefreshSolidMask(X0, Y0, X1, Y1);

	// 4) Formas de colision de la zona (dependen de lo que se acaba de hornear).
	BakeCollisionShapes(FIntRect(Tx0, Ty0, Tx1, Ty1));
	++ContentRevision;

	// 5) Repintar (con margen por los bordes) y recolisionar la zona.
	if (bBuilt)
	{
		const int32 M = EdgeWidth + 1;
		for (int32 Cy = FMath::Max(0, (Y0 - M) / ChunkSize); Cy <= FMath::Min(ChunksY - 1, (Y1 + M) / ChunkSize); ++Cy)
		{
			for (int32 Cx = FMath::Max(0, (X0 - M) / ChunkSize); Cx <= FMath::Min(ChunksX - 1, (X1 + M) / ChunkSize); ++Cx)
			{
				MarkChunkRebuild(Cx, Cy);
			}
		}
		if (CollisionChunkDirty.Num() > 0)
		{
			for (int32 CCy = Y0 / CollChunkCells; CCy <= FMath::Min(CollChunksY - 1, Y1 / CollChunkCells); ++CCy)
			{
				for (int32 CCx = X0 / CollChunkCells; CCx <= FMath::Min(CollChunksX - 1, X1 / CollChunkCells); ++CCx)
				{
					CollisionChunkDirty[CCy * CollChunksX + CCx] = 1;
					bCollisionDirty = true;
				}
			}
		}
	}
}

void AFramework2DTerrainWorld::BakeCollisionShapes(const FIntRect& TileRect)
{
	const UFramework2DTileSet* Set = TileMap ? TileMap->TileSet.Get() : nullptr;
	if (!Set || GridWidth <= 0 || GridHeight <= 0 || CollisionMode.Num() != GridWidth * GridHeight) { return; }

	const int32 Tx0 = FMath::Clamp(TileRect.Min.X, 0, TileMap->Width - 1);
	const int32 Ty0 = FMath::Clamp(TileRect.Min.Y, 0, TileMap->Height - 1);
	const int32 Tx1 = FMath::Clamp(TileRect.Max.X, 0, TileMap->Width - 1);
	const int32 Ty1 = FMath::Clamp(TileRect.Max.Y, 0, TileMap->Height - 1);
	if (Tx1 < Tx0 || Ty1 < Ty0) { return; }
	const int32 CPT = CellsPerTile;

	// 1) La zona vuelve a la colision automatica.
	const int32 X0 = Tx0 * CPT;
	const int32 RowLen = (Tx1 + 1) * CPT - X0;
	for (int32 Y = Ty0 * CPT; Y < (Ty1 + 1) * CPT; ++Y)
	{
		FMemory::Memzero(CollisionMode.GetData() + Index(X0, Y), (SIZE_T)RowLen);
	}

	const bool bOverrides = TileMap->HasCollisionOverrides();
	for (int32 ty = Ty0; ty <= Ty1; ++ty)
	{
		for (int32 tx = Tx0; tx <= Tx1; ++tx)
		{
			EFramework2DCollisionShape Shape = EFramework2DCollisionShape::Auto;
			int32 ShapeSlot = INDEX_NONE; // capa duena de la forma (para "Pixeles"); INDEX_NONE = cualquiera que choque

			// 2) Forma del tile en el TileSet, capa a capa: la de delante gana.
			for (int32 S = 0; S < RLayers.Num(); ++S)
			{
				const FLayerRuntime& L = RLayers[S];
				if (L.bBackground || !L.bCollides) { continue; }
				const int32 Value = TileMap->At(L.MapLayer, tx, ty);
				if (Value < 0) { continue; }
				const EFramework2DCollisionShape LayerShape = Set->GetTileCollision(Value);
				if (LayerShape != EFramework2DCollisionShape::Auto)
				{
					Shape = LayerShape;
					ShapeSlot = S;
				}
			}

			// 3) Lo pintado con el pincel de colision gana a todo.
			if (bOverrides)
			{
				const EFramework2DCollisionShape Painted = TileMap->GetCollisionOverride(tx, ty);
				if (Painted != EFramework2DCollisionShape::Auto)
				{
					Shape = Painted;
					ShapeSlot = INDEX_NONE;
				}
			}
			if (Shape == EFramework2DCollisionShape::Auto) { continue; }

			// 4) Rasterizar: 1 = solido, 2 = sin colision (todo el tile queda decidido).
			const bool bCustom = Framework2D::IsCustomShape(Shape);
			for (int32 cy = 0; cy < CPT; ++cy)
			{
				for (int32 cx = 0; cx < CPT; ++cx)
				{
					const int32 I = Index(tx * CPT + cx, ty * CPT + cy);
					bool bSolid = false;
					if (bCustom)
					{
						bSolid = Framework2D::ShapeCovers(Shape, cx, cy, CPT);
					}
					else if (Shape == EFramework2DCollisionShape::Pixels)
					{
						// El dibujo choca aunque su material no colisione.
						if (ShapeSlot != INDEX_NONE)
						{
							bSolid = RLayers[ShapeSlot].Cells[I] != 0;
						}
						else
						{
							for (const FLayerRuntime& L : RLayers)
							{
								if (L.bCollides && L.Cells[I] != 0) { bSolid = true; break; }
							}
						}
					}
					CollisionMode[I] = bSolid ? 1 : 2; // None: todo a 2
				}
			}
		}
	}
}

void AFramework2DTerrainWorld::BuildFillPatterns(const UFramework2DTileSet* Set)
{
	// Por material: el dibujo del tile marcado como "relleno". Lo que coloca el jugador se
	// pinta con el, alineado a la rejilla de tiles (parece pintado con el tilemap).
	FillPatterns.Reset();
	FillPatterns.SetNum(ResolvedMaterials.Num());
	if (PagesCPU.Num() == 0) { return; }

	const int32 CPT = CellsPerTile;
	const int32 TW = FMath::Max(1, Set->TileWidth);
	const int32 TH = FMath::Max(1, Set->TileHeight);
	for (int32 P = 0; P < Set->GetNumPages(); ++P)
	{
		const int32 PageId = Set->GetPageIdAt(P);
		const TArray<FFramework2DTileDef>* PageTiles = Set->GetPageTiles(PageId);
		if (!PageTiles) { continue; }
		for (int32 T = 0; T < PageTiles->Num(); ++T)
		{
			const FFramework2DTileDef& Def = (*PageTiles)[T];
			if (!Def.bFillPattern) { continue; }
			const uint8 Id = FindMaterialId(Def.MaterialName);
			if (Id == 0 || FillPatterns[Id].Num() > 0) { continue; } // el primero gana

			int32 Ox = 0, Oy = 0;
			const FPageCPU* Page = TileOrigin(Framework2D::MakeTileValue(PageId, T), Ox, Oy);
			if (!Page) { continue; }

			TArray<FColor>& Pattern = FillPatterns[Id];
			Pattern.SetNumUninitialized(CPT * CPT);
			for (int32 cy = 0; cy < CPT; ++cy)
			{
				for (int32 cx = 0; cx < CPT; ++cx)
				{
					Pattern[cy * CPT + cx] = Page->Pixels[(Oy + (cy * TH) / CPT) * Page->W + (Ox + (cx * TW) / CPT)];
				}
			}
		}
	}
}

// =====================================================================
//  Paginas de atlas (en CPU)
// =====================================================================
void AFramework2DTerrainWorld::ReadPages(const UFramework2DTileSet* Set)
{
	PagesCPU.Reset();
	for (int32 P = 0; P < Set->GetNumPages(); ++P)
	{
		FPageCPU Page;
		Page.Id = Set->GetPageIdAt(P);
		if (Page.Id != INDEX_NONE && Set->ReadPagePixels(Page.Id, Page.Pixels, Page.W, Page.H) && Page.Pixels.Num() == Page.W * Page.H)
		{
			PagesCPU.Add(MoveTemp(Page));
		}
	}
}

const AFramework2DTerrainWorld::FPageCPU* AFramework2DTerrainWorld::FindPageCPU(int32 PageId) const
{
	for (const FPageCPU& Page : PagesCPU)
	{
		if (Page.Id == PageId) { return &Page; }
	}
	return nullptr;
}

const AFramework2DTerrainWorld::FPageCPU* AFramework2DTerrainWorld::TileOrigin(int32 TileValue, int32& OutX, int32& OutY) const
{
	const UFramework2DTileSet* Set = TileMap ? TileMap->TileSet.Get() : nullptr;
	if (!Set || !Framework2D::IsAtlasTileValue(TileValue)) { return nullptr; }
	const FPageCPU* Page = FindPageCPU(Framework2D::TilePageOf(TileValue));
	if (!Page || Page->W <= 0) { return nullptr; }
	const int32 TW = FMath::Max(1, Set->TileWidth);
	const int32 TH = FMath::Max(1, Set->TileHeight);
	if (!Set->GetTilePixelOrigin(Framework2D::TileLocalOf(TileValue), Page->W, OutX, OutY) || OutX + TW > Page->W || OutY + TH > Page->H)
	{
		return nullptr;
	}
	return Page;
}

// =====================================================================
//  Generadores de vegetacion
// =====================================================================
void AFramework2DTerrainWorld::PrepareGenerators(const UFramework2DTileSet* Set)
{
	// Cada sprite se recorta una vez a su dibujo (sin el aire de alrededor): asi se apoya en el
	// suelo por su pie de verdad y no por el borde del tile.
	PreparedGenerators.Reset();
	GeneratorMarginTiles = 0;
	const int32 TW = FMath::Max(1, Set->TileWidth);
	const int32 TH = FMath::Max(1, Set->TileHeight);
	const uint8 DecorationId = FindMaterialId(TEXT("Decoration"));

	for (const FFramework2DGenerator& Def : Set->Generators)
	{
		FPreparedGenerator Gen;
		Gen.Def = Def;
		Gen.Def.ScaleMin = FMath::Clamp(Def.ScaleMin, 0.1f, 8.0f);
		Gen.Def.ScaleMax = FMath::Clamp(FMath::Max(Def.ScaleMax, Gen.Def.ScaleMin), 0.1f, 8.0f);
		Gen.Def.GroundSearchTiles = FMath::Clamp(Def.GroundSearchTiles, 0, 8);
		Gen.MaterialId = FindMaterialId(Def.MaterialName);
		if (Gen.MaterialId == 0) { Gen.MaterialId = DecorationId != 0 ? DecorationId : (ResolvedMaterials.Num() > 1 ? 1 : 0); }

		int32 MaxDim = 0;
		for (const FFramework2DScatterSprite& Entry : Def.Sprites)
		{
			if (Entry.Weight <= 0.0f) { continue; }
			int32 Ox = 0, Oy = 0;
			const FPageCPU* Page = TileOrigin(Entry.Tile, Ox, Oy);
			if (!Page) { continue; }
			const int32 W = FMath::Min(FMath::Clamp(Entry.WidthInTiles, 1, 16) * TW, Page->W - Ox);
			const int32 H = FMath::Min(FMath::Clamp(Entry.HeightInTiles, 1, 16) * TH, Page->H - Oy);

			int32 MinX = W, MinY = H, MaxX = -1, MaxY = -1;
			for (int32 y = 0; y < H; ++y)
			{
				for (int32 x = 0; x < W; ++x)
				{
					if (Page->Pixels[(Oy + y) * Page->W + Ox + x].A < AlphaThreshold) { continue; }
					MinX = FMath::Min(MinX, x); MaxX = FMath::Max(MaxX, x);
					MinY = FMath::Min(MinY, y); MaxY = FMath::Max(MaxY, y);
				}
			}
			if (MaxX < 0) { continue; } // tile transparente: no aporta nada

			FPreparedSprite Sprite;
			Sprite.W = MaxX - MinX + 1;
			Sprite.H = MaxY - MinY + 1;
			Sprite.Weight = Entry.Weight;
			Sprite.Pixels.SetNumUninitialized(Sprite.W * Sprite.H);
			for (int32 y = 0; y < Sprite.H; ++y)
			{
				for (int32 x = 0; x < Sprite.W; ++x)
				{
					Sprite.Pixels[y * Sprite.W + x] = Page->Pixels[(Oy + MinY + y) * Page->W + Ox + MinX + x];
				}
			}
			MaxDim = FMath::Max(MaxDim, FMath::Max(Sprite.W, Sprite.H));
			Gen.TotalWeight += Sprite.Weight;
			Gen.Sprites.Add(MoveTemp(Sprite));
		}

		if (Gen.Sprites.Num() > 0 && Gen.MaterialId != 0)
		{
			// Lo que puede salirse un sprite de su casilla (con su suelo debajo): rehornear una zona
			// la amplia esto para no dejar restos.
			const float ExtentPx = MaxDim * Gen.Def.ScaleMax + FMath::Abs(Def.JitterX) + FMath::Abs(Def.JitterY) + FMath::Abs(Def.OffsetY);
			const int32 Margin = FMath::CeilToInt(ExtentPx / (float)CellsPerTile) + (Def.bSnapToGround ? Gen.Def.GroundSearchTiles : 0) + 1;
			GeneratorMarginTiles = FMath::Max(GeneratorMarginTiles, FMath::Min(Margin, 32));
		}
		PreparedGenerators.Add(Def.Id, MoveTemp(Gen));
	}
}

bool AFramework2DTerrainWorld::IsGroundPixel(int32 X, int32 Y) const
{
	// Suelo = lo que choca por su material en una capa que choca (no la vegetacion ya generada).
	if (!InBounds(X, Y)) { return false; }
	const int32 I = Index(X, Y);
	for (const FLayerRuntime& L : RLayers)
	{
		if (!L.bBackground && L.bCollides && IsCollidable(L.Cells[I])) { return true; }
	}
	return false;
}

void AFramework2DTerrainWorld::StampGenerators(const FIntRect& TileRect, const FIntRect& PixelClip)
{
	if (PreparedGenerators.Num() == 0 || !TileMap) { return; }

	// Tambien las casillas de alrededor: sus sprites pueden caer dentro de la zona.
	const int32 M = GeneratorMarginTiles;
	const int32 Tx0 = FMath::Max(0, TileRect.Min.X - M);
	const int32 Ty0 = FMath::Max(0, TileRect.Min.Y - M);
	const int32 Tx1 = FMath::Min(TileMap->Width - 1, TileRect.Max.X + M);
	const int32 Ty1 = FMath::Min(TileMap->Height - 1, TileRect.Max.Y + M);

	for (int32 S = 0; S < RLayers.Num(); ++S)
	{
		for (int32 ty = Ty0; ty <= Ty1; ++ty)
		{
			for (int32 tx = Tx0; tx <= Tx1; ++tx)
			{
				const int32 Value = TileMap->At(RLayers[S].MapLayer, tx, ty);
				if (!Framework2D::IsGeneratorValue(Value)) { continue; }
				const FPreparedGenerator* Gen = PreparedGenerators.Find(Framework2D::GeneratorIdFromValue(Value));
				if (!Gen || Gen->Sprites.Num() == 0 || Gen->MaterialId == 0 || Gen->TotalWeight <= 0.0f) { continue; }
				StampGeneratorCell(S, tx, ty, *Gen, PixelClip);
			}
		}
	}
}

void AFramework2DTerrainWorld::StampGeneratorCell(int32 Slot, int32 Tx, int32 Ty, const FPreparedGenerator& Gen, const FIntRect& PixelClip)
{
	FLayerRuntime& L = RLayers[Slot];
	const FFramework2DGenerator& Def = Gen.Def;
	const int32 CPT = CellsPerTile;
	const float BackMul = FMath::Clamp(BackgroundBrightness, 0.0f, 1.0f);

	// Misma casilla, misma capa y misma semilla = mismo resultado (en el editor y en el juego).
	FRandomStream Rng((int32)Hash3(Tx, Ty, (uint32)Def.Seed * 2654435761u + (uint32)L.MapLayer * 40503u + (uint32)Def.Id * 97u));
	const float Density = FMath::Max(0.0f, Def.Density);
	int32 Count = FMath::FloorToInt(Density);
	if (Rng.FRand() < Density - (float)Count) { ++Count; }

	for (int32 i = 0; i < Count; ++i)
	{
		// Todas las tiradas al azar, siempre en el mismo orden.
		float Pick = Rng.FRand() * Gen.TotalWeight;
		const float Scale = FMath::Lerp(Def.ScaleMin, Def.ScaleMax, Rng.FRand());
		const bool bFlip = Def.bRandomFlip && Rng.FRand() < 0.5f;
		const FColor Tint = FMath::Lerp(Def.TintA, Def.TintB, Rng.FRand()).ToFColor(true);
		const float Bright = 1.0f + (Rng.FRand() * 2.0f - 1.0f) * FMath::Clamp(Def.BrightnessVariation, 0.0f, 1.0f);
		const float JX = (Rng.FRand() * 2.0f - 1.0f) * Def.JitterX;
		const float JY = (Rng.FRand() * 2.0f - 1.0f) * Def.JitterY;

		const FPreparedSprite* Sprite = &Gen.Sprites.Last();
		for (const FPreparedSprite& Candidate : Gen.Sprites)
		{
			if (Pick < Candidate.Weight) { Sprite = &Candidate; break; }
			Pick -= Candidate.Weight;
		}

		// Repartidos a lo ancho de la casilla y movidos al azar.
		const int32 AnchorX = FMath::RoundToInt((float)(Tx * CPT) + ((float)i + 0.5f) / (float)Count * (float)CPT + JX);
		int32 Bottom = (Ty + 1) * CPT - 1;
		const int32 DrawW = FMath::Max(1, FMath::RoundToInt(Sprite->W * Scale));
		const int32 DrawH = FMath::Max(1, FMath::RoundToInt(Sprite->H * Scale));
		if (Def.bHangFromCeiling)
		{
			// El primer techo ENCIMA de su punto, desde lo bajo de la casilla. Sin techo, no sale.
			int32 Ceiling = INDEX_NONE;
			const int32 YEnd = FMath::Max(0, (Ty - Def.GroundSearchTiles) * CPT);
			for (int32 Y = (Ty + 1) * CPT - 1; Y >= YEnd && AnchorX >= 0 && AnchorX < GridWidth; --Y)
			{
				if (IsGroundPixel(AnchorX, Y)) { Ceiling = Y; break; }
			}
			if (Ceiling == INDEX_NONE) { continue; }
			// Positivo = se mete en el techo (sube).
			Bottom = Ceiling + DrawH - FMath::RoundToInt(Def.OffsetY + JY);
		}
		else if (Def.bSnapToGround)
		{
			// El primer suelo bajo su punto, desde lo alto de la casilla. Sin suelo, no sale.
			int32 Ground = INDEX_NONE;
			const int32 YEnd = FMath::Min(GridHeight - 1, (Ty + 1 + Def.GroundSearchTiles) * CPT - 1);
			for (int32 Y = Ty * CPT; Y <= YEnd && AnchorX >= 0 && AnchorX < GridWidth; ++Y)
			{
				if (IsGroundPixel(AnchorX, Y)) { Ground = Y; break; }
			}
			if (Ground == INDEX_NONE) { continue; }
			Bottom = Ground - 1;
		}
		if (!Def.bHangFromCeiling) { Bottom += FMath::RoundToInt(Def.OffsetY + JY); }

		// Escalado al pixel mas cercano (el pixel art no se emborrona).
		const int32 DW = DrawW;
		const int32 DH = DrawH;
		const int32 Left = AnchorX - DW / 2;
		const int32 Top = Bottom - DH + 1;
		for (int32 dy = 0; dy < DH; ++dy)
		{
			const int32 Y = Top + dy;
			if (Y < PixelClip.Min.Y || Y > PixelClip.Max.Y || Y < 0 || Y >= GridHeight) { continue; }
			const int32 Sy = FMath::Min(Sprite->H - 1, (int32)((float)dy / Scale));
			for (int32 dx = 0; dx < DW; ++dx)
			{
				const int32 X = Left + dx;
				if (X < PixelClip.Min.X || X > PixelClip.Max.X || X < 0 || X >= GridWidth) { continue; }
				int32 Sx = FMath::Min(Sprite->W - 1, (int32)((float)dx / Scale));
				if (bFlip) { Sx = Sprite->W - 1 - Sx; }
				const FColor Src = Sprite->Pixels[Sy * Sprite->W + Sx];
				if (Src.A < AlphaThreshold) { continue; }

				// Lo generado no pisa lo que ya hay en su capa (tiles u otros sprites).
				const int32 I = Index(X, Y);
				if (L.Cells[I] != 0 || L.ArtColor[I].A != 0) { continue; }
				const FColor C(
					(uint8)FMath::Clamp(FMath::RoundToInt(Src.R * (Tint.R / 255.0f) * Bright), 0, 255),
					(uint8)FMath::Clamp(FMath::RoundToInt(Src.G * (Tint.G / 255.0f) * Bright), 0, 255),
					(uint8)FMath::Clamp(FMath::RoundToInt(Src.B * (Tint.B / 255.0f) * Bright), 0, 255),
					255);
				L.Cells[I] = Gen.MaterialId;
				L.ArtColor[I] = L.bBackground ? Darken(C, BackMul) : C;
			}
		}
	}
}

// =====================================================================
//  Objetos grandes
// =====================================================================
void AFramework2DTerrainWorld::PrepareProps(const UFramework2DTileSet* Set)
{
	// Cada imagen se recorta una vez a su dibujo: el pie del objeto es su fila de abajo con pixeles.
	PreparedProps.Reset();
	PropMarginSide = PropMarginUp = PropMarginDown = 0;
	const uint8 DecorationId = FindMaterialId(TEXT("Decoration"));
	for (const FFramework2DPropDef& Def : Set->Props)
	{
		TArray<FColor> Image;
		int32 IW = 0, IH = 0;
		if (!Set->ReadPropPixels(Def.Id, Image, IW, IH) || Image.Num() != IW * IH) { continue; }
		int32 MinX = IW, MinY = IH, MaxX = -1, MaxY = -1;
		for (int32 y = 0; y < IH; ++y)
		{
			for (int32 x = 0; x < IW; ++x)
			{
				if (Image[y * IW + x].A < AlphaThreshold) { continue; }
				MinX = FMath::Min(MinX, x); MaxX = FMath::Max(MaxX, x);
				MinY = FMath::Min(MinY, y); MaxY = FMath::Max(MaxY, y);
			}
		}
		if (MaxX < 0) { continue; }
		FPreparedProp Prop;
		Prop.W = MaxX - MinX + 1;
		Prop.H = MaxY - MinY + 1;
		Prop.Pixels.SetNumUninitialized(Prop.W * Prop.H);
		for (int32 y = 0; y < Prop.H; ++y)
		{
			for (int32 x = 0; x < Prop.W; ++x)
			{
				Prop.Pixels[y * Prop.W + x] = Image[(MinY + y) * IW + MinX + x];
			}
		}
		Prop.MaterialId = FindMaterialId(Def.MaterialName);
		if (Prop.MaterialId == 0) { Prop.MaterialId = DecorationId != 0 ? DecorationId : (ResolvedMaterials.Num() > 1 ? 1 : 0); }
		if (Prop.MaterialId != 0) { PreparedProps.Add(Def.Id, MoveTemp(Prop)); }
	}
	// Un objeto apoyado se pone sobre el primer suelo bajo su centro, entre su casilla y dos mas abajo
	// (StampProps): si cambia una casilla, puede moverse cualquiera cuyo centro este en esa columna y
	// hasta dos filas por encima. Al rehornear una zona, lo que esos objetos ocupan dibujados a cada
	// lado: media anchura, y DH - Sink pixeles por encima de su suelo y Sink por debajo.
	if (TileMap)
	{
		const int32 CPT = FMath::Max(1, CellsPerTile);
		for (const FFramework2DPropInstance& Instance : TileMap->PropInstances)
		{
			const FPreparedProp* Prop = (Instance.bSnapToGround && !Instance.bHanging) ? PreparedProps.Find(Instance.PropId) : nullptr;
			if (!Prop) { continue; }
			const float Scale = FMath::Clamp(Instance.Scale, 0.1f, 8.0f);
			const int32 DW = FMath::Max(1, FMath::RoundToInt(Prop->W * Scale));
			const int32 DH = FMath::Max(1, FMath::RoundToInt(Prop->H * Scale));
			PropMarginSide = FMath::Max(PropMarginSide, FMath::DivideAndRoundUp(DW, 2 * CPT) + 1);
			PropMarginUp = FMath::Max(PropMarginUp, 2 + FMath::DivideAndRoundUp(FMath::Max(0, DH - Instance.SinkPixels), CPT));
			PropMarginDown = FMath::Max(PropMarginDown, 3 + FMath::DivideAndRoundUp(FMath::Max(0, Instance.SinkPixels), CPT));
		}
		PropMarginSide = FMath::Min(PropMarginSide, 32);
		PropMarginUp = FMath::Min(PropMarginUp, 32);
		PropMarginDown = FMath::Min(PropMarginDown, 32);
	}
}

void AFramework2DTerrainWorld::StampProps(const FIntRect& PixelClip)
{
	if (PreparedProps.Num() == 0 || !TileMap || TileMap->PropInstances.Num() == 0) { return; }
	const int32 CPT = CellsPerTile;
	const float BackMul = FMath::Clamp(BackgroundBrightness, 0.0f, 1.0f);
	for (const FFramework2DPropInstance& Instance : TileMap->PropInstances)
	{
		const FPreparedProp* Prop = PreparedProps.Find(Instance.PropId);
		const int32 Slot = Prop ? FindSlot(TileMap->FindLayerByName(Instance.Layer)) : INDEX_NONE;
		if (Slot == INDEX_NONE) { continue; }
		FLayerRuntime& L = RLayers[Slot];

		const float Scale = FMath::Clamp(Instance.Scale, 0.1f, 8.0f);
		const int32 DW = FMath::Max(1, FMath::RoundToInt(Prop->W * Scale));
		const int32 DH = FMath::Max(1, FMath::RoundToInt(Prop->H * Scale));
		const int32 Left = FMath::RoundToInt(Instance.X * (float)CPT) - DW / 2;
		int32 Top = Instance.bHanging
			? Instance.Y * CPT - Instance.SinkPixels
			: (Instance.Y + 1) * CPT - 1 + Instance.SinkPixels - DH + 1;
		if (Instance.bSnapToGround && !Instance.bHanging)
		{
			// El primer suelo bajo su centro, desde lo alto de su casilla (como mucho dos casillas).
			const int32 AnchorX = Left + DW / 2;
			const int32 YEnd = FMath::Min(GridHeight - 1, (Instance.Y + 3) * CPT - 1);
			for (int32 Y = Instance.Y * CPT; Y <= YEnd; ++Y)
			{
				if (IsGroundPixel(AnchorX, Y)) { Top = Y - 1 + Instance.SinkPixels - DH + 1; break; }
			}
		}

		// Fuera de la zona que se hornea: nada que hacer.
		if (Left > PixelClip.Max.X || Left + DW - 1 < PixelClip.Min.X || Top > PixelClip.Max.Y || Top + DH - 1 < PixelClip.Min.Y) { continue; }
		for (int32 dy = 0; dy < DH; ++dy)
		{
			const int32 Y = Top + dy;
			if (Y < PixelClip.Min.Y || Y > PixelClip.Max.Y || Y < 0 || Y >= GridHeight) { continue; }
			const int32 Sy = FMath::Min(Prop->H - 1, (int32)((float)dy / Scale));
			for (int32 dx = 0; dx < DW; ++dx)
			{
				const int32 X = Left + dx;
				if (X < PixelClip.Min.X || X > PixelClip.Max.X || X < 0 || X >= GridWidth) { continue; }
				int32 Sx = FMath::Min(Prop->W - 1, (int32)((float)dx / Scale));
				if (Instance.bFlip) { Sx = Prop->W - 1 - Sx; }
				const FColor Src = Prop->Pixels[Sy * Prop->W + Sx];
				if (Src.A < AlphaThreshold) { continue; }
				// No pisa lo que ya hay en su capa (tiles, otro objeto), salvo si tapa (bCoverTiles).
				const int32 I = Index(X, Y);
				if (!Instance.bCoverTiles && (L.Cells[I] != 0 || L.ArtColor[I].A != 0)) { continue; }
				L.Cells[I] = Prop->MaterialId;
				L.ArtColor[I] = L.bBackground ? Darken(Src, BackMul) : FColor(Src.R, Src.G, Src.B, 255);
			}
		}
	}
}

// =====================================================================
//  Fondos parallax
// =====================================================================
void AFramework2DTerrainWorld::RefreshBackdrops()
{
	if (!BackdropMesh) { return; }
	if (!bCanRender || !bShowBackdrops || !TileMap || TileMap->Backdrops.Num() == 0 || GridWidth <= 0)
	{
		BackdropMesh->ClearLayers();
		return;
	}
	// Detras de la capa de mas atras.
	float BackY = 0.0f;
	for (const FLayerRuntime& L : RLayers) { BackY = FMath::Min(BackY, L.DepthY); }
	const float Cell = GetCellSize();
	BackdropMesh->SetLayers(TileMap->Backdrops, TerrainMaterial, Cell, FVector2D(GridWidth * Cell, GridHeight * Cell),
		Cell * CellsPerTile, BackY - FMath::Max(1.0f, BackdropDistance));
}

// =====================================================================
//  Flipbooks (tiles animados)
// =====================================================================
void AFramework2DTerrainWorld::UpdateAnimations(float DeltaSeconds)
{
	const UFramework2DTileSet* Set = TileMap ? TileMap->TileSet.Get() : nullptr;
	if (AnimatedTiles.Num() == 0 || !Set || !bCanRender) { return; }
	AnimTime += DeltaSeconds;
	for (FAnimatedTile& Anim : AnimatedTiles)
	{
		const int32 Shown = Set->GetFrameTile(Anim.Value, AnimTime);
		if (Shown != Anim.ShownTile)
		{
			Anim.ShownTile = Shown;
			DrawAnimatedFrame(Anim, Shown);
		}
	}
}

void AFramework2DTerrainWorld::DrawAnimatedFrame(const FAnimatedTile& Anim, int32 AtlasTile)
{
	const UFramework2DTileSet* Set = TileMap ? TileMap->TileSet.Get() : nullptr;
	if (!Set || !RLayers.IsValidIndex(Anim.Slot)) { return; }
	const int32 CPT = CellsPerTile;
	if (Anim.Tx < 0 || Anim.Ty < 0 || (Anim.Tx + 1) * CPT > GridWidth || (Anim.Ty + 1) * CPT > GridHeight) { return; }
	const int32 TW = FMath::Max(1, Set->TileWidth);
	const int32 TH = FMath::Max(1, Set->TileHeight);
	int32 Ox = 0, Oy = 0;
	const FPageCPU* Page = TileOrigin(AtlasTile, Ox, Oy);
	if (!Page) { return; }
	const float BackMul = FMath::Clamp(BackgroundBrightness, 0.0f, 1.0f);

	FLayerRuntime& L = RLayers[Anim.Slot];
	for (int32 cy = 0; cy < CPT; ++cy)
	{
		for (int32 cx = 0; cx < CPT; ++cx)
		{
			const int32 I = Index(Anim.Tx * CPT + cx, Anim.Ty * CPT + cy);
			// Solo la forma del flipbook (A != 0) y, si se rompe, solo lo que sigue intacto
			// (lo roto o colocado ya no es del flipbook).
			if (L.ArtColor[I].A == 0) { continue; }
			if (!L.bBackground && L.Cells[I] == 0) { continue; }
			const FColor Px = Page->Pixels[(Oy + (cy * TH) / CPT) * Page->W + (Ox + (cx * TW) / CPT)];
			const bool bOpaque = Px.A >= AlphaThreshold;
			if (L.bBackground)
			{
				L.ArtColor[I] = bOpaque ? Darken(Px, BackMul) : FColor(0, 0, 0, 1);
			}
			else
			{
				L.ArtColor[I] = bOpaque ? FColor(Px.R, Px.G, Px.B, 255) : FColor(0, 0, 0, 1);
			}
		}
	}

	// Repintar solo ESE tile en ESA capa: el fotograma no cambia las celdas (ni los bordes de las
	// vecinas ni las otras capas), solo el dibujo.
	AnimDirtyTiles.Add(FIntVector(Anim.Slot, Anim.Tx, Anim.Ty));
	bVisualDirty = true;
}

void AFramework2DTerrainWorld::CreateRenderResources()
{
	if (!RenderMesh || RLayers.Num() == 0) { return; }

	if (!TerrainMaterial)
	{
		UE_LOG(LogTemp, Warning, TEXT("[Framework2DTerrain] '%s' no tiene Terrain Material: el terreno funciona pero no se ve."), *GetName());
	}

	// Se reutilizan las texturas y materiales de la construccion anterior si encajan: rehacer la
	// vista previa a menudo no deja texturas huerfanas (CPU y GPU) esperando al recolector.
	// Despues se sube todo de nuevo (MarkAllDirty), asi que su contenido viejo no importa.
	TArray<TObjectPtr<UTexture2D>> OldTextures = MoveTemp(LayerTextures);
	TArray<TObjectPtr<UMaterialInstanceDynamic>> OldMIDs = MoveTemp(LayerMIDs);
	LayerTextures.Reset();
	LayerMIDs.Reset();

	for (int32 S = 0; S < RLayers.Num(); ++S)
	{
		UTexture2D* Texture = OldTextures.IsValidIndex(S) ? OldTextures[S].Get() : nullptr;
		if (Texture && (Texture->GetSizeX() != GridWidth || Texture->GetSizeY() != GridHeight)) { Texture = nullptr; }
		UMaterialInstanceDynamic* MID = OldMIDs.IsValidIndex(S) ? OldMIDs[S].Get() : nullptr;
		if (MID && MID->Parent != TerrainMaterial) { MID = nullptr; }
		if (!Texture)
		{
			Texture = UTexture2D::CreateTransient(GridWidth, GridHeight, PF_B8G8R8A8);
			if (!Texture) { LayerTextures.Add(nullptr); LayerMIDs.Add(nullptr); continue; }
			Texture->Filter = TextureFilter::TF_Nearest; // pixeles nitidos
			Texture->SRGB = true;
			Texture->AddressX = TextureAddress::TA_Clamp;
			Texture->AddressY = TextureAddress::TA_Clamp;
			Texture->NeverStream = true;
#if WITH_EDITORONLY_DATA
			Texture->MipGenSettings = TextureMipGenSettings::TMGS_NoMipmaps;
#endif
			Texture->UpdateResource();
		}
		if (!MID && TerrainMaterial)
		{
			MID = UMaterialInstanceDynamic::Create(TerrainMaterial, this);
			if (MID) { MID->SetFlags(RF_Transient); } // no se guarda con el nivel
		}
		if (MID)
		{
			MID->SetTextureParameterValue(TEXT("TerrainTexture"), Texture); // material propio
			MID->SetTextureParameterValue(TEXT("SpriteTexture"), Texture);  // material de Paper2D
		}
		LayerTextures.Add(Texture);
		LayerMIDs.Add(MID);
		CreateLayerSection(S);
	}
}

void AFramework2DTerrainWorld::CreateLayerSection(int32 Slot)
{
	if (!RenderMesh || !RLayers.IsValidIndex(Slot) || !LayerTextures.IsValidIndex(Slot) || !LayerTextures[Slot]) { return; }

	// Un quad por capa en el plano XZ local (X derecha, Z arriba), a la profundidad de la capa.
	// La textura tiene V=0 arriba. Seccion de la malla = slot de la capa.
	const float W = GridWidth * GetCellSize();
	const float H = GridHeight * GetCellSize();
	const TArray<int32> Tris = { 0, 1, 2, 0, 2, 3 };
	const TArray<FVector> Normals = { FVector(0, -1, 0), FVector(0, -1, 0), FVector(0, -1, 0), FVector(0, -1, 0) };
	const TArray<FVector2D> UVs = { FVector2D(0, 1), FVector2D(1, 1), FVector2D(1, 0), FVector2D(0, 0) };

	// Dos planos coplanarios se pintarian en orden imprevisible: con separacion (casi) 0, medio
	// centimetro por capa basta para que la de delante gane siempre.
	float D = RLayers[Slot].DepthY;
	if (LayerSeparation < 0.5f)
	{
		const int32 BaseSlot = FMath::Max(0, FindSlot(GetBaseLayer()));
		D += (float)(Slot - BaseSlot) * 0.5f;
	}
	const TArray<FVector> Verts = { FVector(0, D, 0), FVector(W, D, 0), FVector(W, D, H), FVector(0, D, H) };
	RenderMesh->CreateMeshSection_LinearColor(Slot, Verts, Tris, Normals, UVs, TArray<FLinearColor>(), TArray<FProcMeshTangent>(), /*bCreateCollision*/ false);
	RenderMesh->SetMaterial(Slot, LayerMIDs.IsValidIndex(Slot) ? LayerMIDs[Slot].Get() : nullptr);
}

void AFramework2DTerrainWorld::UpdateLayerDepths()
{
	// Solo se mueven los planos: las celdas y las texturas no cambian.
	if (!bBuilt) { return; }
	for (int32 S = 0; S < RLayers.Num(); ++S)
	{
		RLayers[S].DepthY = GetLayerDepth(RLayers[S].MapLayer);
		CreateLayerSection(S);
	}
	RefreshBackdrops(); // siguen detras de la capa de mas atras
}

// =====================================================================
//  Capas
// =====================================================================
int32 AFramework2DTerrainWorld::GetBaseLayer() const
{
	if (!TileMap) { return -1; }
	for (int32 L = 0; L < TileMap->Layers.Num(); ++L)
	{
		const FFramework2DTileLayer& Layer = TileMap->Layers[L];
		if (Layer.bVisible && !Layer.bBackground) { return L; }
	}
	return -1;
}

float AFramework2DTerrainWorld::GetLayerDepth(int32 Layer) const
{
	// La capa base queda en Y=0 (colision y personajes). Las de delante van a +Y y las de
	// detras a -Y: el terreno se ve derecho desde +Y (vista Right del editor, plantilla 2D).
	const int32 Base = FMath::Max(0, GetBaseLayer());
	return (float)(Layer - Base) * FMath::Max(0.0f, LayerSeparation);
}

int32 AFramework2DTerrainWorld::FindSlot(int32 MapLayer) const
{
	for (int32 S = 0; S < RLayers.Num(); ++S)
	{
		if (RLayers[S].MapLayer == MapLayer) { return S; }
	}
	return INDEX_NONE;
}

int32 AFramework2DTerrainWorld::ResolveEditSlot(int32 MapLayer) const
{
	// -1 = la capa base: el primer plano que no es de fondo.
	if (MapLayer < 0)
	{
		for (int32 S = 0; S < RLayers.Num(); ++S)
		{
			if (!RLayers[S].bBackground) { return S; }
		}
		return INDEX_NONE;
	}
	const int32 Slot = FindSlot(MapLayer);
	return (Slot != INDEX_NONE && !RLayers[Slot].bBackground) ? Slot : INDEX_NONE; // el fondo no se edita en juego
}

int32 AFramework2DTerrainWorld::FrontCellSlot(int32 X, int32 Y) const
{
	if (!InBounds(X, Y)) { return INDEX_NONE; }
	const int32 I = Index(X, Y);
	for (int32 S = RLayers.Num() - 1; S >= 0; --S)
	{
		const FLayerRuntime& L = RLayers[S];
		if (!L.bBackground && L.Cells[I] != 0) { return S; }
	}
	return INDEX_NONE;
}

bool AFramework2DTerrainWorld::IsCollidableAt(int32 X, int32 Y) const
{
	if (!InBounds(X, Y)) { return false; }
	const int32 I = Index(X, Y);

	// Las formas mandan; en automatico, choca si alguna capa que choca tiene un material que choca.
	const uint8 Mode = CollisionMode[I];
	if (Mode == 1) { return true; }
	if (Mode == 2) { return false; }
	for (const FLayerRuntime& L : RLayers)
	{
		if (L.bCollides && IsCollidable(L.Cells[I])) { return true; }
	}
	return false;
}

bool AFramework2DTerrainWorld::HasForegroundCell(int32 X, int32 Y) const
{
	if (!InBounds(X, Y)) { return false; }
	const int32 I = Index(X, Y);
	for (const FLayerRuntime& L : RLayers)
	{
		if (!L.bBackground && L.Cells[I] != 0) { return true; }
	}
	return false;
}

// =====================================================================
//  Rotura: picar con dureza, escombros, colocar, rayo
// =====================================================================
float AFramework2DTerrainWorld::GetCellSize() const
{
	if (bBuilt) { return TileSize / (float)CellsPerTile; }
	const UFramework2DTileSet* Set = TileMap ? TileMap->TileSet.Get() : nullptr;
	return TileSize / (float)FMath::Clamp(Set ? Set->TileWidth : 16, 1, 256);
}

TArray<FFramework2DMaterial> AFramework2DTerrainWorld::GetMaterials() const
{
	if (bBuilt)
	{
		TArray<FFramework2DMaterial> Out = ResolvedMaterials;
		Out.RemoveAt(0); // el aire
		return Out;
	}
	const UFramework2DTileSet* Set = TileMap ? TileMap->TileSet.Get() : nullptr;
	return Set ? Set->Materials : TArray<FFramework2DMaterial>();
}

float AFramework2DTerrainWorld::RoughRadius(float Radius, int32 Dx, int32 Dy, uint32 Seed) const
{
	// Unos pocos bultos grandes alrededor del circulo + grano fino por pixel. Solo ENCOGE.
	if (BrushRoughness <= 0.0f || Radius < 2.0f) { return Radius; }
	const float A = FMath::Atan2((float)Dy, (float)Dx);
	const float P1 = Hash01(11, 3, Seed) * 6.2831853f;
	const float P2 = Hash01(5, 17, Seed) * 6.2831853f;
	const float P3 = Hash01(23, 7, Seed) * 6.2831853f;
	const float Lumps = 0.5f + 0.5f * (0.5f * FMath::Sin(3.0f * A + P1) + 0.3f * FMath::Sin(5.0f * A + P2) + 0.2f * FMath::Sin(8.0f * A + P3));
	const float Grain = Hash01(Dx, Dy, Seed);
	return Radius * (1.0f - FMath::Clamp(BrushRoughness, 0.0f, 1.0f) * 0.45f * (0.8f * Lumps + 0.2f * Grain));
}

FFramework2DDigResult AFramework2DTerrainWorld::BreakInRadius(const FVector& WorldPosition, float Radius, int32 DamageAmount,
	bool bFalloff, bool bRoughEdge, bool bSpawnDebris, AActor* Collector, bool bRadialDebris)
{
	FFramework2DDigResult Result;
	Result.Location = WorldPosition;
	if (!bBuilt || RLayers.Num() == 0) { return Result; }

	const float CS = GetCellSize();
	int32 Cx, Cy;
	WorldToCell(WorldPosition, Cx, Cy); // aunque el centro caiga fuera, se recorta por bordes
	// Exacto: el mismo circulo que Paint. Rugoso: radio continuo con bultos.
	const float R = bRoughEdge ? FMath::Max(0.5f, Radius / CS) : (float)FMath::Max(0, FMath::CeilToInt(Radius / CS));
	const int32 RI = FMath::CeilToInt(R);
	const uint32 Seed = Hash3(Cx, Cy, ++BrushCounter);

	// Dig y Explode atraviesan todas las capas; picar solo rompe la de mas delante que tenga
	// algo (y si es indestructible, ese pixel no se toca: no se pica "a traves" de la roca madre).
	const bool bAllLayers = DamageAmount < 0 || bFalloff;
	const int32 NumSlots = RLayers.Num();

	int32 Counts[256];
	FMemory::Memzero(Counts, sizeof(Counts));

	// Golpe a la celda de una capa: dano con dureza o rotura directa.
	auto HitCell = [&](int32 S, int32 X, int32 Y, int32 I, float Dist)
	{
		FLayerRuntime& L = RLayers[S];
		const uint8 Id = L.Cells[I];
		const FFramework2DMaterial& Mat = ResolvedMaterials[Id];
		if (Mat.bIndestructible) { return; }

		if (DamageAmount >= 0)
		{
			// Dano con dureza: se acumula hasta llegar a Hardness.
			int32 Dmg = DamageAmount;
			if (bFalloff)
			{
				Dmg = FMath::RoundToInt((float)DamageAmount * FMath::Clamp(1.0f - Dist / (R + 1.0f), 0.0f, 1.0f));
			}
			if (Dmg <= 0) { return; }
			++Result.CellsHit;
			// El dano solo se guarda en juego; si se pica fuera de juego (herramientas), se crea al momento.
			if (L.Damage.Num() != GridWidth * GridHeight) { L.Damage.SetNumZeroed(GridWidth * GridHeight); }
			const int32 NewDamage = FMath::Min(255, (int32)L.Damage[I] + Dmg);
			if (NewDamage < FMath::Max(1, Mat.Hardness))
			{
				L.Damage[I] = (uint8)NewDamage;
				if (bShowDamage) { MarkVisualDirty(X, Y); }
				return;
			}
		}
		else
		{
			++Result.CellsHit;
		}

		if (bSpawnDebris)
		{
			SpawnDebris(S, X, Y, Cx, Cy, Mat.bCollectable ? Collector : nullptr, bRadialDebris); // antes de vaciar (usa su color)
		}
		++Counts[Id];
		++Result.CellsRemoved;
		SetCellInternal(S, X, Y, 0);
	};

	for (int32 Y = FMath::Max(0, Cy - RI); Y <= FMath::Min(GridHeight - 1, Cy + RI); ++Y)
	{
		for (int32 X = FMath::Max(0, Cx - RI); X <= FMath::Min(GridWidth - 1, Cx + RI); ++X)
		{
			const int32 Dx = X - Cx;
			const int32 Dy = Y - Cy;
			const float Dist = FMath::Sqrt((float)(Dx * Dx + Dy * Dy));
			if (Dist > (bRoughEdge ? RoughRadius(R, Dx, Dy, Seed) : R)) { continue; }

			// Las capas que no se rompen (y el fondo) ni bloquean ni se rompen.
			const int32 I = Index(X, Y);
			if (bAllLayers)
			{
				for (int32 S = 0; S < NumSlots; ++S)
				{
					if (RLayers[S].bBreakable && RLayers[S].Cells[I] != 0) { HitCell(S, X, Y, I, Dist); }
				}
			}
			else
			{
				for (int32 S = NumSlots - 1; S >= 0; --S)
				{
					if (RLayers[S].bBreakable && RLayers[S].Cells[I] != 0) { HitCell(S, X, Y, I, Dist); break; }
				}
			}
		}
	}

	for (int32 Id = 1; Id < ResolvedMaterials.Num(); ++Id)
	{
		if (Counts[Id] > 0 && ResolvedMaterials[Id].bCollectable)
		{
			FFramework2DMaterialAmount Amount;
			Amount.Material = ResolvedMaterials[Id].Name;
			Amount.Count = Counts[Id];
			Result.Collected.Add(Amount);
		}
	}

	if (Result.CellsRemoved > 0)
	{
		OnTerrainMined.Broadcast(Result);
	}
	return Result;
}

FFramework2DDigResult AFramework2DTerrainWorld::MineAt(FVector WorldPosition, float Radius, int32 DamageAmount, AActor* Collector)
{
	return BreakInRadius(WorldPosition, Radius, FMath::Clamp(DamageAmount, 1, 255), false, true, true, Collector, false);
}

FFramework2DDigResult AFramework2DTerrainWorld::Dig(FVector WorldPosition, float Radius)
{
	return BreakInRadius(WorldPosition, Radius, /*instantaneo*/ -1, false, /*bRoughEdge*/ false, /*bSpawnDebris*/ false, nullptr, false);
}

void AFramework2DTerrainWorld::Explode(FVector WorldPosition, float Radius, float Power)
{
	const int32 P = FMath::Clamp(FMath::RoundToInt(Power), 1, 255);
	BreakInRadius(WorldPosition, Radius, P, /*bFalloff*/ true, true, true, nullptr, /*bRadialDebris*/ true);
}

void AFramework2DTerrainWorld::Paint(FVector WorldPosition, float Radius, FName MaterialName, int32 Layer)
{
	if (!bBuilt) { return; }
	const int32 Slot = ResolveEditSlot(Layer);
	if (Slot == INDEX_NONE) { return; } // capa oculta, de fondo o inexistente
	const uint8 Id = FindMaterialId(MaterialName);
	if (Id == 0 && MaterialName != NAME_None) { return; } // material desconocido
	int32 Cx, Cy;
	WorldToCell(WorldPosition, Cx, Cy);
	const int32 R = FMath::Max(0, FMath::CeilToInt(Radius / GetCellSize()));
	for (int32 Y = FMath::Max(0, Cy - R); Y <= FMath::Min(GridHeight - 1, Cy + R); ++Y)
	{
		for (int32 X = FMath::Max(0, Cx - R); X <= FMath::Min(GridWidth - 1, Cx + R); ++X)
		{
			if ((X - Cx) * (X - Cx) + (Y - Cy) * (Y - Cy) <= R * R)
			{
				SetCellInternal(Slot, X, Y, Id);
			}
		}
	}
}

void AFramework2DTerrainWorld::SetCellInternal(int32 Slot, int32 X, int32 Y, uint8 Id)
{
	if (!RLayers.IsValidIndex(Slot) || !InBounds(X, Y)) { return; }
	FLayerRuntime& L = RLayers[Slot];
	const int32 I = Index(X, Y);
	const uint8 Old = L.Cells[I];
	if (Old == Id) { return; }

	const bool bTouchesCollision = !L.bBackground && L.bCollides;
	const bool bWasCollidable = bTouchesCollision && IsCollidableAt(X, Y);

	L.Cells[I] = Id;
	L.ArtColor[I] = FColor(0, 0, 0, 0); // celda cambiada en juego: relleno/color, no el dibujo viejo
	if (L.Damage.IsValidIndex(I)) { L.Damage[I] = 0; }
	if (!L.bBackground)
	{
		// El borde oscuro mira el compuesto de todas las capas que no son de fondo.
		uint8 Solid = 0;
		for (const FLayerRuntime& Other : RLayers) { Solid |= (!Other.bBackground && EdgeMask[Other.Cells[I]]) ? 1 : 0; }
		SolidMask[I] = Solid;
	}
	if (bTouchesCollision)
	{
		// Lo roto deja de chocar aunque estuviera dentro de una forma; lo colocado choca segun su material.
		CollisionMode[I] = 0;
		if (bWasCollidable != IsCollidableAt(X, Y)) { MarkCollisionDirty(X, Y); }
	}
	MarkVisualDirty(X, Y);
	++ContentRevision;
}

void AFramework2DTerrainWorld::SpawnDebris(int32 Slot, int32 X, int32 Y, int32 Cx, int32 Cy, AActor* Collector, bool bRadial)
{
	if (!bCanRender || DebrisMode == EFramework2DDebrisMode::None || MaxDebris <= 0 || Debris.Num() >= MaxDebris) { return; }
	if (!RLayers.IsValidIndex(Slot) || !InBounds(X, Y)) { return; }
	if (FMath::FRand() > DebrisChance) { return; }

	FFramework2DDebris P;
	P.X = (float)X + 0.5f;
	P.Y = (float)Y + 0.5f;
	P.Color = BaseCellColor(Slot, X, Y);

	// Desde el centro del golpe hacia fuera, con algo de azar.
	float DirX = (float)(X - Cx) + FMath::FRandRange(-0.75f, 0.75f);
	float DirY = (float)(Y - Cy) + FMath::FRandRange(-0.75f, 0.75f);
	const float Len = FMath::Sqrt(DirX * DirX + DirY * DirY);
	if (Len < KINDA_SMALL_NUMBER) { DirX = FMath::FRandRange(-1.0f, 1.0f); DirY = -1.0f; }
	else { DirX /= Len; DirY /= Len; }

	const float Speed = (DebrisSpeed / GetCellSize()) * FMath::FRandRange(0.5f, 1.2f); // celdas/s
	if (bRadial)
	{
		P.VX = DirX * Speed * 1.6f;
		P.VY = DirY * Speed * 1.6f - Speed * 0.3f; // Y negativa = arriba
	}
	else
	{
		P.VX = DirX * Speed * 0.6f;
		P.VY = DirY * Speed * 0.6f - Speed * 0.8f;
	}
	P.Life = DebrisLifetime * FMath::FRandRange(0.6f, 1.3f);
	if (DebrisMode == EFramework2DDebrisMode::ToCollector && Collector)
	{
		P.Target = Collector;
		P.Life = DebrisLifetime * 3.0f;
	}
	Debris.Add(P);
	bVisualDirty = true;
}

void AFramework2DTerrainWorld::UpdateDebris(float DeltaSeconds)
{
	if (Debris.Num() == 0) { return; }

	const float Grav = DebrisGravity / GetCellSize();
	const float Homing = DebrisHomingSpeed / GetCellSize();
	for (int32 i = Debris.Num() - 1; i >= 0; --i)
	{
		FFramework2DDebris& P = Debris[i];
		P.Age += DeltaSeconds;
		bool bDead = P.Age >= P.Life;

		AActor* Target = P.Target.Get();
		if (Target)
		{
			float TX, TY;
			WorldToCellFloat(Target->GetActorLocation(), TX, TY);
			const float DX = TX - P.X;
			const float DY = TY - P.Y;
			const float Dist = FMath::Sqrt(DX * DX + DY * DY);
			if (Dist < FMath::Max(2.0f, Homing * DeltaSeconds * 1.5f))
			{
				bDead = true; // llego a quien pica
			}
			else
			{
				// Primero sale despedido; enseguida "tira" de el cada vez mas fuerte.
				const float Alpha = FMath::Clamp(DeltaSeconds * 10.0f * FMath::Clamp(P.Age * 4.0f, 0.0f, 1.0f), 0.0f, 1.0f);
				P.VX = FMath::Lerp(P.VX, DX / Dist * Homing, Alpha);
				P.VY = FMath::Lerp(P.VY, DY / Dist * Homing, Alpha);
			}
		}
		else
		{
			P.VY += Grav * DeltaSeconds;
		}

		P.X += P.VX * DeltaSeconds;
		P.Y += P.VY * DeltaSeconds;

		if (!Target)
		{
			const int32 IX = FMath::FloorToInt(P.X);
			const int32 IY = FMath::FloorToInt(P.Y);
			if (!InBounds(IX, IY)) { bDead = true; }                                            // salio del terreno
			else if (P.VY > 0.0f && P.Age > 0.08f && HasForegroundCell(IX, IY)) { bDead = true; } // cayo sobre terreno
		}

		if (bDead)
		{
			Debris.RemoveAtSwap(i);
		}
	}
	bVisualDirty = true;
}

void AFramework2DTerrainWorld::GatherPawnCellRects(const FVector& WorldPosition, float Radius, TArray<FIntRect>& OutRects) const
{
	UWorld* World = GetWorld();
	if (!World) { return; }

	TArray<FOverlapResult> Overlaps;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Framework2DPlaceMaterial), false, this);
	World->OverlapMultiByObjectType(Overlaps, WorldPosition, FQuat::Identity,
		FCollisionObjectQueryParams(ECC_Pawn), FCollisionShape::MakeSphere(Radius + GetCellSize() * 4.0f), Params);

	for (const FOverlapResult& Overlap : Overlaps)
	{
		const UPrimitiveComponent* Comp = Overlap.GetComponent();
		if (!Comp) { continue; }
		const FBox B = Comp->Bounds.GetBox();
		int32 MinX = MAX_int32, MinY = MAX_int32, MaxX = MIN_int32, MaxY = MIN_int32;
		for (int32 k = 0; k < 8; ++k)
		{
			const FVector Corner((k & 1) ? B.Max.X : B.Min.X, (k & 2) ? B.Max.Y : B.Min.Y, (k & 4) ? B.Max.Z : B.Min.Z);
			int32 X, Y;
			WorldToCell(Corner, X, Y);
			MinX = FMath::Min(MinX, X); MaxX = FMath::Max(MaxX, X);
			MinY = FMath::Min(MinY, Y); MaxY = FMath::Max(MaxY, Y);
		}
		OutRects.Add(FIntRect(MinX - 1, MinY - 1, MaxX + 1, MaxY + 1)); // +1 de margen
	}
}

int32 AFramework2DTerrainWorld::PlaceMaterial(FVector WorldPosition, float Radius, FName MaterialName, int32 MaxCells, bool bAvoidPawns, int32 Layer)
{
	if (!bBuilt || MaxCells == 0) { return 0; }
	const int32 Slot = ResolveEditSlot(Layer);
	if (Slot == INDEX_NONE) { return 0; } // capa oculta, de fondo o inexistente
	const uint8 Id = FindMaterialId(MaterialName);
	if (Id == 0) { return 0; }

	int32 Cx, Cy;
	WorldToCell(WorldPosition, Cx, Cy);
	const float R = FMath::Max(0.5f, Radius / GetCellSize());
	const int32 RI = FMath::CeilToInt(R);

	TArray<FIntRect> Blocked;
	if (bAvoidPawns) { GatherPawnCellRects(WorldPosition, Radius, Blocked); }

	const TArray<uint8>& SlotCells = RLayers[Slot].Cells;
	struct FCandidate { int32 X; int32 Y; float Key; };
	TArray<FCandidate> Candidates;
	const uint32 Seed = Hash3(Cx, Cy, ++BrushCounter);
	for (int32 Y = FMath::Max(0, Cy - RI); Y <= FMath::Min(GridHeight - 1, Cy + RI); ++Y)
	{
		for (int32 X = FMath::Max(0, Cx - RI); X <= FMath::Min(GridWidth - 1, Cx + RI); ++X)
		{
			const float D2 = (float)((X - Cx) * (X - Cx) + (Y - Cy) * (Y - Cy));
			// Solo huecos de esa capa que no choquen (nada de meter tierra dentro de una pared).
			if (D2 > R * R || SlotCells[Index(X, Y)] != 0 || IsCollidableAt(X, Y)) { continue; }

			bool bIsBlocked = false;
			for (const FIntRect& B : Blocked)
			{
				if (X >= B.Min.X && X <= B.Max.X && Y >= B.Min.Y && Y <= B.Max.Y) { bIsBlocked = true; break; }
			}
			if (bIsBlocked) { continue; }

			// De dentro hacia fuera, con un poco de ruido para que el borde no sea un circulo perfecto.
			Candidates.Add(FCandidate{ X, Y, D2 + Hash01(X, Y, Seed) * R * 0.5f });
		}
	}

	if (MaxCells > 0 && Candidates.Num() > MaxCells)
	{
		Candidates.Sort([](const FCandidate& A, const FCandidate& B) { return A.Key < B.Key; });
		Candidates.SetNum(MaxCells);
	}
	for (const FCandidate& C : Candidates)
	{
		SetCellInternal(Slot, C.X, C.Y, Id);
	}
	return Candidates.Num();
}

bool AFramework2DTerrainWorld::TraceTerrain(FVector Start, FVector End, bool bOnlyCollidable, FVector& OutHitLocation, FName& OutMaterialName) const
{
	return TraceCells(Start, End, bOnlyCollidable ? ETraceStop::Collidable : ETraceStop::AnyCell, OutHitLocation, OutMaterialName);
}

bool AFramework2DTerrainWorld::TraceBreakableTerrain(FVector Start, FVector End, FVector& OutHitLocation, FName& OutMaterialName) const
{
	return TraceCells(Start, End, ETraceStop::Breakable, OutHitLocation, OutMaterialName);
}

bool AFramework2DTerrainWorld::HasBreakableCell(int32 X, int32 Y) const
{
	return BreakableCellSlot(X, Y) != INDEX_NONE;
}

int32 AFramework2DTerrainWorld::BreakableCellSlot(int32 X, int32 Y) const
{
	if (!InBounds(X, Y)) { return INDEX_NONE; }
	const int32 I = Index(X, Y);
	for (int32 S = RLayers.Num() - 1; S >= 0; --S)
	{
		if (RLayers[S].bBreakable && RLayers[S].Cells[I] != 0) { return S; }
	}
	return INDEX_NONE;
}

bool AFramework2DTerrainWorld::TraceCells(const FVector& Start, const FVector& End, ETraceStop Stop, FVector& OutHitLocation, FName& OutMaterialName) const
{
	OutHitLocation = End;
	OutMaterialName = NAME_None;
	if (!bBuilt) { return false; }

	// DDA por celdas (Amanatides & Woo): visita exactamente las celdas que cruza el rayo.
	float X0, Y0, X1, Y1;
	WorldToCellFloat(Start, X0, Y0);
	WorldToCellFloat(End, X1, Y1);
	const float DX = X1 - X0;
	const float DY = Y1 - Y0;

	int32 X = FMath::FloorToInt(X0);
	int32 Y = FMath::FloorToInt(Y0);
	const int32 EndX = FMath::FloorToInt(X1);
	const int32 EndY = FMath::FloorToInt(Y1);
	const int32 StepX = DX > 0.0f ? 1 : -1;
	const int32 StepY = DY > 0.0f ? 1 : -1;
	const float Big = 1.0e30f;
	const float TDeltaX = DX != 0.0f ? FMath::Abs(1.0f / DX) : Big;
	const float TDeltaY = DY != 0.0f ? FMath::Abs(1.0f / DY) : Big;
	float TMaxX = DX > 0.0f ? ((float)(X + 1) - X0) / DX : (DX < 0.0f ? (X0 - (float)X) / -DX : Big);
	float TMaxY = DY > 0.0f ? ((float)(Y + 1) - Y0) / DY : (DY < 0.0f ? (Y0 - (float)Y) / -DY : Big);
	float T = 0.0f;

	const int32 MaxSteps = FMath::Abs(EndX - X) + FMath::Abs(EndY - Y) + 1;
	for (int32 Step = 0; Step <= MaxSteps; ++Step)
	{
		const bool bStop = InBounds(X, Y) &&
			(Stop == ETraceStop::Collidable ? IsCollidableAt(X, Y) : (Stop == ETraceStop::Breakable ? HasBreakableCell(X, Y) : HasForegroundCell(X, Y)));
		if (bStop)
		{
			// El punto de entrada cae justo en el borde de la celda: se mete un pelo DENTRO
			// para que IsSolidAtWorld / GetMaterialNameAtWorld en ese punto den esta celda.
			const float E = 0.01f;
			const float Hx = FMath::Clamp(X0 + DX * T, (float)X + E, (float)X + 1.0f - E);
			const float Hy = FMath::Clamp(Y0 + DY * T, (float)Y + E, (float)Y + 1.0f - E);
			OutHitLocation = CellFloatToWorld(Hx, Hy);
			const int32 S = Stop == ETraceStop::Breakable ? BreakableCellSlot(X, Y) : FrontCellSlot(X, Y); // INDEX_NONE en una pared invisible
			OutMaterialName = S != INDEX_NONE ? ResolvedMaterials[RLayers[S].Cells[Index(X, Y)]].Name : NAME_None;
			return true;
		}
		if (X == EndX && Y == EndY) { break; }
		if (TMaxX < TMaxY) { T = TMaxX; TMaxX += TDeltaX; X += StepX; }
		else               { T = TMaxY; TMaxY += TDeltaY; Y += StepY; }
	}
	return false;
}

// =====================================================================
//  Consultas
// =====================================================================
bool AFramework2DTerrainWorld::IsSolidAtWorld(FVector WorldPosition) const
{
	int32 Cx, Cy;
	if (!bBuilt || !WorldToCell(WorldPosition, Cx, Cy)) { return false; }
	return IsCollidableAt(Cx, Cy);
}

FName AFramework2DTerrainWorld::GetMaterialNameAtWorld(FVector WorldPosition) const
{
	int32 Cx, Cy;
	if (!bBuilt || !WorldToCell(WorldPosition, Cx, Cy)) { return NAME_None; }
	const int32 S = FrontCellSlot(Cx, Cy);
	return S != INDEX_NONE ? ResolvedMaterials[RLayers[S].Cells[Index(Cx, Cy)]].Name : NAME_None;
}

FName AFramework2DTerrainWorld::GetLayerMaterialNameAtWorld(FVector WorldPosition, int32 Layer) const
{
	int32 Cx, Cy;
	if (!bBuilt || !WorldToCell(WorldPosition, Cx, Cy)) { return NAME_None; }
	const int32 S = FindSlot(Layer); // las de fondo tambien responden
	return S != INDEX_NONE ? ResolvedMaterials[RLayers[S].Cells[Index(Cx, Cy)]].Name : NAME_None; // el aire (id 0) se llama None
}

int32 AFramework2DTerrainWorld::CountMaterialInRadius(FVector WorldPosition, float Radius, FName MaterialName) const
{
	if (!bBuilt) { return 0; }
	const uint8 Id = FindMaterialId(MaterialName);
	if (Id == 0 && MaterialName != NAME_None) { return 0; }
	int32 Cx, Cy;
	WorldToCell(WorldPosition, Cx, Cy);
	const int32 R = FMath::CeilToInt(Radius / GetCellSize());
	int32 Count = 0;
	for (int32 Y = FMath::Max(0, Cy - R); Y <= FMath::Min(GridHeight - 1, Cy + R); ++Y)
	{
		for (int32 X = FMath::Max(0, Cx - R); X <= FMath::Min(GridWidth - 1, Cx + R); ++X)
		{
			if ((X - Cx) * (X - Cx) + (Y - Cy) * (Y - Cy) > R * R) { continue; }
			if (Id == 0)
			{
				// None = aire: ninguna capa (de las que no son de fondo) tiene algo ahi.
				if (!HasForegroundCell(X, Y)) { ++Count; }
				continue;
			}
			const int32 I = Index(X, Y);
			for (const FLayerRuntime& L : RLayers)
			{
				if (!L.bBackground && L.Cells[I] == Id) { ++Count; }
			}
		}
	}
	return Count;
}

// =====================================================================
//  Render: celdas -> pixeles -> una textura por capa (solo lo que cambia)
// =====================================================================
FColor AFramework2DTerrainWorld::BaseCellColor(int32 Slot, int32 X, int32 Y) const
{
	const FLayerRuntime& L = RLayers[Slot];
	const int32 I = Index(X, Y);
	const uint8 Id = L.Cells[I];

	// 1) Dibujo del tile (A==1 es "oculto en este fotograma": no tiene color propio).
	if (L.ArtColor[I].A > 1) { return L.ArtColor[I]; }

	// 2) Tile de relleno del material (lo que coloca el jugador).
	if (FillPatterns.IsValidIndex(Id) && FillPatterns[Id].Num() == CellsPerTile * CellsPerTile)
	{
		const FColor P = FillPatterns[Id][(Y % CellsPerTile) * CellsPerTile + (X % CellsPerTile)];
		if (P.A >= AlphaThreshold) { return FColor(P.R, P.G, P.B, 255); }
	}

	// 3) Color del material con un poco de variacion.
	const FFramework2DMaterial& Mat = ResolvedMaterials[Id];
	FColor C = Mat.Color;
	if (Mat.ColorVariance > 0)
	{
		const int32 Var = Mat.ColorVariance;
		const int32 Delta = (int32)(Hash3(X, Y, 0x9E37u) % (uint32)(2 * Var + 1)) - Var;
		C.R = (uint8)FMath::Clamp((int32)C.R + Delta, 0, 255);
		C.G = (uint8)FMath::Clamp((int32)C.G + Delta, 0, 255);
		C.B = (uint8)FMath::Clamp((int32)C.B + Delta, 0, 255);
	}
	C.A = 255;
	return C;
}

bool AFramework2DTerrainWorld::IsOpenCell(int32 X, int32 Y) const
{
	// "Abierto" = ninguna capa (de las que no son de fondo) tiene ahi un material con borde.
	// Se mira el COMPUESTO: de frente se ve igual que cuando todas las capas iban en un plano.
	// Fuera del terreno no cuenta (sin contorno en los limites).
	if (!InBounds(X, Y)) { return false; }
	return SolidMask[Index(X, Y)] == 0;
}

void AFramework2DTerrainWorld::RefreshSolidMask(int32 X0, int32 Y0, int32 X1, int32 Y1)
{
	X0 = FMath::Max(0, X0); Y0 = FMath::Max(0, Y0);
	X1 = FMath::Min(GridWidth - 1, X1); Y1 = FMath::Min(GridHeight - 1, Y1);
	if (X1 < X0 || Y1 < Y0 || SolidMask.Num() != GridWidth * GridHeight) { return; }
	const int32 Rows = Y1 - Y0 + 1;
	ParallelFor(Rows, [&](int32 Row)
	{
		const int32 Y = Y0 + Row;
		for (int32 X = X0; X <= X1; ++X)
		{
			const int32 I = Index(X, Y);
			uint8 Solid = 0;
			for (const FLayerRuntime& L : RLayers) { Solid |= (!L.bBackground && EdgeMask[L.Cells[I]]) ? 1 : 0; }
			SolidMask[I] = Solid;
		}
	}, Rows < 64);
}

int32 AFramework2DTerrainWorld::EdgeDistance(int32 X, int32 Y) const
{
	// Distancia Manhattan (1..EdgeWidth) a la celda abierta mas cercana; 0 si no hay.
	for (int32 R = 1; R <= EdgeWidth; ++R)
	{
		for (int32 Dx = -R; Dx <= R; ++Dx)
		{
			const int32 Dy = R - FMath::Abs(Dx);
			if (IsOpenCell(X + Dx, Y + Dy)) { return R; }
			if (Dy != 0 && IsOpenCell(X + Dx, Y - Dy)) { return R; }
		}
	}
	return 0;
}

FColor AFramework2DTerrainWorld::ComputeCellColor(int32 Slot, int32 X, int32 Y) const
{
	const FLayerRuntime& L = RLayers[Slot];
	const int32 I = Index(X, Y);

	// Aire: el cielo solo en el plano de mas atras; los demas dejan ver lo de detras.
	const FColor Air = (Slot == 0 && bDrawSky) ? FColor(SkyColor.R, SkyColor.G, SkyColor.B, 255) : FColor(0, 0, 0, 0);

	// Fondo: el dibujo ya va oscurecido. Sin borde ni dano.
	if (L.bBackground)
	{
		return L.ArtColor[I].A > 1 ? L.ArtColor[I] : Air;
	}

	// Aire (o pixel de flipbook que no existe en este fotograma).
	const uint8 Id = L.Cells[I];
	if (Id == 0 || L.ArtColor[I].A == 1) { return Air; }

	FColor C = BaseCellColor(Slot, X, Y);

	// Dureza: el pixel se oscurece segun el dano que lleva.
	if (bShowDamage && L.Damage.IsValidIndex(I) && L.Damage[I] > 0)
	{
		const float Hard = (float)FMath::Max(1, ResolvedMaterials[Id].Hardness);
		C = LerpColor(C, FColor(0, 0, 0, 255), 0.55f * FMath::Clamp((float)L.Damage[I] / Hard, 0.0f, 1.0f));
	}

	// Borde donde el terreno toca aire: el corte de cada agujero se lee al instante.
	if (EdgeWidth > 0 && EdgeMask[Id])
	{
		const int32 D = EdgeDistance(X, Y);
		if (D > 0)
		{
			const bool bTop = (D == 1) && TopEdgeColor.A > 0 && IsOpenCell(X, Y - 1);
			const FColor& EC = bTop ? TopEdgeColor : EdgeColor;
			const float T = ((float)EC.A / 255.0f) * (1.0f - (float)(D - 1) / (float)EdgeWidth);
			C = LerpColor(C, FColor(EC.R, EC.G, EC.B, 255), T);
		}
	}
	return C;
}

void AFramework2DTerrainWorld::MarkChunkRebuild(int32 Cx, int32 Cy)
{
	if (Cx < 0 || Cy < 0 || Cx >= ChunksX || Cy >= ChunksY) { return; }
	ChunkRebuild[Cy * ChunksX + Cx] = 1;
	bVisualDirty = true;
}

void AFramework2DTerrainWorld::MarkVisualDirty(int32 X, int32 Y)
{
	// Una celda que cambia altera el borde de sus vecinas hasta EdgeWidth (y el borde de
	// arriba de la de debajo): cerca del limite del trozo, se repinta tambien el vecino.
	// El trozo se recalcula en TODAS las capas (el borde mira el compuesto).
	const int32 Cx = X / ChunkSize;
	const int32 Cy = Y / ChunkSize;
	MarkChunkRebuild(Cx, Cy);
	const int32 M = FMath::Max(1, EdgeWidth);
	const int32 Lx = X - Cx * ChunkSize;
	const int32 Ly = Y - Cy * ChunkSize;
	const int32 Sx = Lx < M ? -1 : (Lx >= ChunkSize - M ? 1 : 0);
	const int32 Sy = Ly < M ? -1 : (Ly >= ChunkSize - M ? 1 : 0);
	if (Sx != 0) { MarkChunkRebuild(Cx + Sx, Cy); }
	if (Sy != 0) { MarkChunkRebuild(Cx, Cy + Sy); }
	if (Sx != 0 && Sy != 0) { MarkChunkRebuild(Cx + Sx, Cy + Sy); }
}

void AFramework2DTerrainWorld::MarkAllDirty()
{
	for (uint8& D : ChunkRebuild) { D = 1; }
	bVisualDirty = true;
	for (uint8& D : CollisionChunkDirty) { D = 1; }
	bCollisionDirty = CollisionChunkDirty.Num() > 0;
}

void AFramework2DTerrainWorld::FlushVisual()
{
	if (!bBuilt || !bVisualDirty) { return; }
	bVisualDirty = false;

	// Sin texturas (servidor dedicado, -nullrhi, ninguna capa visible) no hay nada que dibujar ni subir.
	const int32 NumSlots = RLayers.Num();
	bool bAnyTexture = false;
	if (bCanRender && LayerTextures.Num() == NumSlots)
	{
		for (int32 S = 0; S < NumSlots && !bAnyTexture; ++S)
		{
			bAnyTexture = LayerTextures[S] && LayerTextures[S]->GetResource();
		}
	}
	if (!bAnyTexture)
	{
		for (uint8& D : ChunkRebuild) { D = 0; }
		for (uint8& D : ChunkUpload) { D = 0; }
		AnimDirtyTiles.Reset();
		DebrisChunksLastFrame.Reset();
		return;
	}
	const int32 Front = NumSlots - 1;
	auto ChunkRect = [this](int32 C)
	{
		const int32 X0 = (C % ChunksX) * ChunkSize;
		const int32 Y0 = (C / ChunksX) * ChunkSize;
		return FIntRect(X0, Y0, FMath::Min(X0 + ChunkSize, GridWidth) - 1, FMath::Min(Y0 + ChunkSize, GridHeight) - 1);
	};

	// 1) Escombros: se pintan encima de la capa de delante al subirla. Hay que repintar los trozos
	// donde estan ahora y donde estaban el frame anterior (para borrarlos).
	TMap<int32, FDebrisPaint> Overlay;
	TArray<int32> DebrisChunks;
	for (const FFramework2DDebris& P : Debris)
	{
		const int32 X = FMath::FloorToInt(P.X);
		const int32 Y = FMath::FloorToInt(P.Y);
		if (!InBounds(X, Y)) { continue; }
		FDebrisPaint Paint;
		Paint.Color = P.Color;
		Paint.Fade = P.Target.IsValid() ? 1.0f : FMath::Clamp((1.0f - P.Age / FMath::Max(P.Life, 0.01f)) * 2.0f, 0.0f, 1.0f);
		Overlay.Add(Index(X, Y), Paint);
		DebrisChunks.AddUnique((Y / ChunkSize) * ChunksX + (X / ChunkSize));
	}
	TArray<int32> FrontChunks = DebrisChunks;
	for (const int32 C : DebrisChunksLastFrame) { FrontChunks.AddUnique(C); }
	DebrisChunksLastFrame = MoveTemp(DebrisChunks);
	if (Debris.Num() > 0 || DebrisChunksLastFrame.Num() > 0) { bVisualDirty = true; } // el frame que viene los mueve/borra

	// 2) Trozos que cambiaron (en todas las capas) y escombros (solo la de delante).
	TArray<int32> FullChunks;
	for (int32 C = 0; C < ChunkRebuild.Num(); ++C)
	{
		if (ChunkRebuild[C] || (ChunkUpload[C] & 2)) { FullChunks.Add(C); }
		ChunkRebuild[C] = 0;
		ChunkUpload[C] = 0;
	}
	// Mucho que repintar (construir, regenerar): la textura entera de una vez.
	const bool bWhole = FullChunks.Num() * 2 >= ChunksX * ChunksY;
	TArray<uint8> InFull;
	InFull.SetNumZeroed(ChunksX * ChunksY);
	for (const int32 C : FullChunks) { InFull[C] = 1; }

	for (int32 S = 0; S < NumSlots; ++S)
	{
		TArray<FIntRect> Rects;
		if (bWhole)
		{
			Rects.Add(FIntRect(0, 0, GridWidth - 1, GridHeight - 1));
		}
		else
		{
			for (const int32 C : FullChunks) { Rects.Add(ChunkRect(C)); }
			if (S == Front)
			{
				for (const int32 C : FrontChunks) { if (!InFull[C]) { Rects.Add(ChunkRect(C)); } }
			}
			// 3) Flipbooks que cambiaron de fotograma: su tile, en su capa (si su trozo no se repinta ya).
			for (const FIntVector& Tile : AnimDirtyTiles)
			{
				if (Tile.X != S) { continue; }
				const int32 PX = Tile.Y * CellsPerTile;
				const int32 PY = Tile.Z * CellsPerTile;
				if (!InBounds(PX, PY) || InFull[(PY / ChunkSize) * ChunksX + (PX / ChunkSize)]) { continue; }
				Rects.Add(FIntRect(PX, PY, FMath::Min(PX + CellsPerTile, GridWidth) - 1, FMath::Min(PY + CellsPerTile, GridHeight) - 1));
			}
		}
		if (Rects.Num() > 0) { UploadRects(S, Rects, S == Front && Overlay.Num() > 0 ? &Overlay : nullptr); }
	}
	AnimDirtyTiles.Reset();
}

void AFramework2DTerrainWorld::UploadRects(int32 Slot, const TArray<FIntRect>& Rects, const TMap<int32, FDebrisPaint>* Overlay)
{
	UTexture2D* Texture = LayerTextures.IsValidIndex(Slot) ? LayerTextures[Slot].Get() : nullptr;
	if (!Texture || !Texture->GetResource() || Rects.Num() == 0) { return; }

	// Un buffer con los rectangulos uno debajo de otro (todos con el ancho del mas ancho).
	int32 Pitch = 0;
	int32 TotalRows = 0;
	TArray<int32> FirstRow;
	FirstRow.Reserve(Rects.Num());
	for (const FIntRect& R : Rects)
	{
		FirstRow.Add(TotalRows);
		Pitch = FMath::Max(Pitch, R.Max.X - R.Min.X + 1);
		TotalRows += R.Max.Y - R.Min.Y + 1;
	}
	FColor* Buffer = (FColor*)FMemory::Malloc((SIZE_T)Pitch * TotalRows * sizeof(FColor));
	FUpdateTextureRegion2D* Regions = new FUpdateTextureRegion2D[Rects.Num()];
	TArray<FIntPoint> RowJobs; // (rectangulo, fila dentro de el)
	RowJobs.Reserve(TotalRows);
	for (int32 K = 0; K < Rects.Num(); ++K)
	{
		const FIntRect& R = Rects[K];
		Regions[K] = FUpdateTextureRegion2D((uint32)R.Min.X, (uint32)R.Min.Y, 0, (uint32)FirstRow[K],
			(uint32)(R.Max.X - R.Min.X + 1), (uint32)(R.Max.Y - R.Min.Y + 1));
		for (int32 Row = 0; Row <= R.Max.Y - R.Min.Y; ++Row) { RowJobs.Add(FIntPoint(K, Row)); }
	}

	// Los colores se calculan aqui, fila a fila y en paralelo (solo leen las celdas).
	ParallelFor(RowJobs.Num(), [&](int32 Job)
	{
		const FIntRect& R = Rects[RowJobs[Job].X];
		const int32 Row = RowJobs[Job].Y;
		const int32 Y = R.Min.Y + Row;
		FColor* Out = Buffer + (SIZE_T)(FirstRow[RowJobs[Job].X] + Row) * Pitch;
		for (int32 X = R.Min.X; X <= R.Max.X; ++X)
		{
			FColor C = ComputeCellColor(Slot, X, Y);
			if (Overlay)
			{
				if (const FDebrisPaint* Paint = Overlay->Find(Index(X, Y))) { C = LerpColor(C, Paint->Color, Paint->Fade); }
			}
			Out[X - R.Min.X] = C;
		}
	}, RowJobs.Num() < 64);

	// El buffer y las regiones viven hasta que el render thread los usa (se liberan en el callback).
	Texture->UpdateTextureRegions(0, (uint32)Rects.Num(), Regions, (uint32)(Pitch * sizeof(FColor)), (uint32)sizeof(FColor), (uint8*)Buffer,
		[](uint8* InData, const FUpdateTextureRegion2D* InRegions)
		{
			FMemory::Free(InData);
			delete[] InRegions;
		});
}

// =====================================================================
//  Colision: trozos de cajas (greedy mesh por trozo)
// =====================================================================
void AFramework2DTerrainWorld::DestroyCollisionChunks()
{
	for (UFramework2DCollisionChunkComponent* Chunk : CollisionChunks)
	{
		if (Chunk) { Chunk->DestroyComponent(); }
	}
	CollisionChunks.Reset();
	CollisionChunkDirty.Reset();
	CollChunksX = CollChunksY = 0;
}

void AFramework2DTerrainWorld::CreateCollisionChunks()
{
	DestroyCollisionChunks();
	CollChunkCells = FMath::Clamp(CollisionChunkSize, 16, 512);
	CollChunksX = FMath::DivideAndRoundUp(GridWidth, CollChunkCells);
	CollChunksY = FMath::DivideAndRoundUp(GridHeight, CollChunkCells);
	const int32 N = CollChunksX * CollChunksY;
	// Los componentes se crean al hacer falta (RebuildCollisionChunk): el cielo y las zonas sin
	// nada que choque no cuestan nada. Con mapas grandes eran miles de componentes vacios.
	CollisionChunks.Init(nullptr, N);
	CollisionChunkDirty.Init(1, N);
	bCollisionDirty = true;
}

void AFramework2DTerrainWorld::MarkCollisionDirty(int32 X, int32 Y)
{
	if (CollisionChunkDirty.Num() == 0) { return; } // sin colision (vista previa o desactivada)
	const int32 CCx = X / CollChunkCells;
	const int32 CCy = Y / CollChunkCells;
	if (CCx < 0 || CCy < 0 || CCx >= CollChunksX || CCy >= CollChunksY) { return; }
	CollisionChunkDirty[CCy * CollChunksX + CCx] = 1;
	bCollisionDirty = true;
}

void AFramework2DTerrainWorld::RebuildDirtyCollision()
{
	TArray<int32> Dirty;
	for (int32 i = 0; i < CollisionChunkDirty.Num(); ++i)
	{
		if (CollisionChunkDirty[i]) { CollisionChunkDirty[i] = 0; Dirty.Add(i); }
	}
	bCollisionDirty = false;
	if (Dirty.Num() == 0) { return; }

	// Las cajas de cada trozo se calculan en paralelo (solo leen celdas); los componentes se
	// tocan despues, en este hilo.
	TArray<TArray<FIntRect>> RectsPerChunk;
	RectsPerChunk.SetNum(Dirty.Num());
	ParallelFor(Dirty.Num(), [&](int32 K)
	{
		const int32 ChunkIndex = Dirty[K];
		const int32 X0 = (ChunkIndex % CollChunksX) * CollChunkCells;
		const int32 Y0 = (ChunkIndex / CollChunksX) * CollChunkCells;
		MergeCollisionRows(X0, Y0, FMath::Min(CollChunkCells, GridWidth - X0), FMath::Min(CollChunkCells, GridHeight - Y0), RectsPerChunk[K]);
	}, Dirty.Num() < 8);
	for (int32 K = 0; K < Dirty.Num(); ++K)
	{
		ApplyCollisionChunk(Dirty[K], RectsPerChunk[K]);
	}
}

void AFramework2DTerrainWorld::MergeCollisionRows(int32 X0, int32 Y0, int32 W, int32 H, TArray<FIntRect>& OutRects) const
{
	// La zona se recorta al terreno.
	const int32 Ax = FMath::Max(0, X0);
	const int32 Ay = FMath::Max(0, Y0);
	const int32 Bx = FMath::Min(GridWidth, X0 + W);
	const int32 By = FMath::Min(GridHeight, Y0 + H);
	if (Bx <= Ax || By <= Ay || CollisionMode.Num() != GridWidth * GridHeight) { return; }
	const int32 ZoneW = Bx - Ax;
	const int32 ZoneH = By - Ay;

	// Fusion de tramos: cada fila se parte en tramos solidos [Ini, Fin) y un tramo que coincide
	// exactamente con uno de la fila de arriba alarga esa caja hacia abajo. Asi un borde de
	// hierba dentado solo crea cajas pequenas en sus filas, y debajo queda una sola caja grande.
	struct FOpenBox { int32 Ini; int32 Fin; int32 Top; };
	TArray<FOpenBox> Open, Next;

	// Tramo cerrado -> rectangulo de celdas (Min..Max incluidos). Bottom es la fila siguiente.
	auto Emit = [&](const FOpenBox& B, int32 Bottom)
	{
		OutRects.Add(FIntRect(Ax + B.Ini, Ay + B.Top, Ax + B.Fin - 1, Ay + Bottom - 1));
	};

	for (int32 Ly = 0; Ly <= ZoneH; ++Ly)
	{
		Next.Reset();
		int32 k = 0; // Open esta ordenado por Ini: se recorre a la par que la fila
		for (int32 Lx = 0; Ly < ZoneH && Lx < ZoneW; )
		{
			if (!IsCollidableAt(Ax + Lx, Ay + Ly)) { ++Lx; continue; }
			const int32 Ini = Lx;
			while (Lx < ZoneW && IsCollidableAt(Ax + Lx, Ay + Ly)) { ++Lx; }
			while (k < Open.Num() && Open[k].Ini < Ini) { Emit(Open[k], Ly); ++k; }
			if (k < Open.Num() && Open[k].Ini == Ini && Open[k].Fin == Lx) { Next.Add(Open[k]); ++k; } // continua hacia abajo
			else { Next.Add(FOpenBox{ Ini, Lx, Ly }); }
		}
		while (k < Open.Num()) { Emit(Open[k], Ly); ++k; }
		Swap(Open, Next);
	}
}

void AFramework2DTerrainWorld::GetCollisionCellRects(TArray<FIntRect>& OutRects) const
{
	OutRects.Reset();
	if (!bBuilt) { return; }
	MergeCollisionRows(0, 0, GridWidth, GridHeight, OutRects);
}

void AFramework2DTerrainWorld::RebuildCollisionChunk(int32 ChunkIndex)
{
	if (!CollisionChunks.IsValidIndex(ChunkIndex)) { return; }
	const int32 X0 = (ChunkIndex % CollChunksX) * CollChunkCells;
	const int32 Y0 = (ChunkIndex / CollChunksX) * CollChunkCells;
	TArray<FIntRect> Rects;
	MergeCollisionRows(X0, Y0, FMath::Min(CollChunkCells, GridWidth - X0), FMath::Min(CollChunkCells, GridHeight - Y0), Rects);
	ApplyCollisionChunk(ChunkIndex, Rects);
}

void AFramework2DTerrainWorld::ApplyCollisionChunk(int32 ChunkIndex, const TArray<FIntRect>& Rects)
{
	if (!CollisionChunks.IsValidIndex(ChunkIndex)) { return; }
	UFramework2DCollisionChunkComponent* Comp = CollisionChunks[ChunkIndex].Get();
	if (!Comp)
	{
		if (Rects.Num() == 0) { return; } // nada que choque: ni componente
		Comp = NewObject<UFramework2DCollisionChunkComponent>(this, NAME_None, RF_Transient);
		Comp->SetupAttachment(RootComponent);
		Comp->SetCollisionProfileName(CollisionProfile.Name);
		Comp->RegisterComponent();
		CollisionChunks[ChunkIndex] = Comp;
	}
	const float CS = GetCellSize();

	TArray<FBox>& Boxes = CollisionBoxScratch;
	Boxes.Reset(Rects.Num());
	for (const FIntRect& R : Rects)
	{
		// Celdas -> caja en espacio local (plano XZ de la capa base). Y de celda pequena = mas arriba.
		const float ZTop = (GridHeight - R.Min.Y) * CS;
		const float ZBot = (GridHeight - (R.Max.Y + 1)) * CS;
		Boxes.Add(FBox(FVector(R.Min.X * CS, -CollisionDepth, ZBot), FVector((R.Max.X + 1) * CS, CollisionDepth, ZTop)));
	}
	Comp->SetBoxes(Boxes);
}

// =====================================================================
//  Coordenadas
// =====================================================================
bool AFramework2DTerrainWorld::WorldToCell(const FVector& World, int32& OutX, int32& OutY) const
{
	const FVector L = GetActorTransform().InverseTransformPosition(World);
	const float CS = GetCellSize();
	OutX = FMath::FloorToInt((float)(L.X / CS));
	OutY = (GridHeight - 1) - FMath::FloorToInt((float)(L.Z / CS));
	return InBounds(OutX, OutY);
}

void AFramework2DTerrainWorld::WorldToCellFloat(const FVector& World, float& OutX, float& OutY) const
{
	const FVector L = GetActorTransform().InverseTransformPosition(World);
	const float CS = GetCellSize();
	OutX = (float)(L.X / CS);
	OutY = (float)GridHeight - (float)(L.Z / CS);
}

FVector AFramework2DTerrainWorld::CellFloatToWorld(float X, float Y) const
{
	const double CS = GetCellSize();
	return GetActorTransform().TransformPosition(FVector((double)X * CS, 0.0, ((double)GridHeight - (double)Y) * CS));
}

uint8 AFramework2DTerrainWorld::FindMaterialId(FName MaterialName) const
{
	const uint8* Found = NameToId.Find(MaterialName);
	return Found ? *Found : 0;
}
