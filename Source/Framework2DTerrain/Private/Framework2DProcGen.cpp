// Copyright Chema Luque. Plugin Framework2DTerrain.

#include "Framework2DProcGen.h"

#include "Framework2DTileMapAsset.h"
#include "Framework2DTileSet.h"
#include "Math/RandomStream.h"
#include "Templates/TypeHash.h"

#define LOCTEXT_NAMESPACE "Framework2DProcGen"

// =====================================================================
//  Utilidades locales (sin estado)
// =====================================================================

// Sal de cada flujo aleatorio. Cada parte del nivel tira de su propio FRandomStream (semilla de
// la receta + esta sal): asi tocar la decoracion, el agua o las rampas no mueve el relieve.
enum class EFramework2DProcGenStream : uint32
{
	Relief     = 0x52454C49, // anchos y alturas de los llanos
	Ramps      = 0x52414D50, // rampa o escalon: dos tiradas por transicion, siempre
	Pits       = 0x464F534F, // fosos
	Water      = 0x41475541, // lagos: una tirada por hondonada
	Waterfalls = 0x43415343, // cascadas: una tirada por acantilado candidato
	Platforms  = 0x504C4154, // plataformas flotantes
	Decoration = 0x4445434F, // adornos: una tirada por candidata y otra al poner uno (suelo y luego techo)
	Variants   = 0x56415249, // variantes del centro: una por casilla maciza (5x5) o de centro (3x3, esquinas incluidas) y otra al elegir
	Background = 0x464F4E44, // ruido de las colinas del fondo
	Hills      = 0x4C4F4D41, // lomas: ruido del relieve
	Islands    = 0x49534C41, // islas flotantes
	Bridges    = 0x5055454E, // puentes: una tirada por hueco
	Props      = 0x4F424A45  // objetos grandes: tres tiradas por columna candidata
};

// Mas celdas que esto no tiene sentido (el mapa mide como mucho 1024 x 1024).
static constexpr int64 Framework2DProcGenMaxCells = 4096 * 4096;

static FRandomStream Framework2DProcGenStream(int32 Seed, EFramework2DProcGenStream Part)
{
	return FRandomStream((int32)HashCombine((uint32)Seed, (uint32)Part));
}

// Copia del bioma con las piezas que no sirven (-1 o borradas del Tile Set) a -1, y sus listas
// sin entradas inutiles (ni adornos de peso 0). A partir de aqui "pieza asignada" es ">= 0".
static FFramework2DBiome Framework2DProcGenUsableBiome(const UFramework2DTileSet* Set, const FFramework2DBiome& Source)
{
	FFramework2DBiome Biome = Source;
	for (int32 SlotIndex = 0; SlotIndex < (int32)EFramework2DBiomeSlot::Count; ++SlotIndex)
	{
		if (int32* Piece = Framework2D::BiomeSlotRef(Biome, (EFramework2DBiomeSlot)SlotIndex))
		{
			if (!UFramework2DProcGenLibrary::IsUsablePiece(Set, *Piece)) { *Piece = -1; }
		}
	}
	Biome.CenterVariants.RemoveAll([Set](int32 Value) { return !UFramework2DProcGenLibrary::IsUsablePiece(Set, Value); });
	Biome.Decorations.RemoveAll([Set](const FFramework2DBiomeDecoration& Deco)
	{
		return !(Deco.Weight > 0.0f) || !UFramework2DProcGenLibrary::IsUsablePiece(Set, Deco.Value);
	});
	// Objetos grandes: solo los que existen en el Tile Set y tienen imagen (sin Tile Set no hay).
	Biome.Props.RemoveAll([Set](const FFramework2DBiomeProp& Entry)
	{
		int32 PW = 0, PH = 0;
		return !(Entry.Weight > 0.0f) || !Set || !Set->GetPropSize(Entry.PropId, PW, PH);
	});
	Biome.Backdrops.RemoveAll([](const FFramework2DBackdropLayer& Layer) { return Layer.Texture == nullptr; });
	return Biome;
}

// Pieza de un 3x3 para la fila y columna dadas, con reserva: la del mismo borde (fila), la del
// mismo lado (columna) y, si no, el centro.
static int32 Framework2DProcGenPick3x3(const FFramework2DTile3x3& Tiles, int32 Row, int32 Col)
{
	const int32 Candidates[3] = { Tiles.At(Row, Col), Tiles.At(Row, 1), Tiles.At(1, Col) };
	for (const int32 Value : Candidates)
	{
		if (Value >= 0) { return Value; }
	}
	return Tiles.Center;
}

// Pieza de un 5x5 con reserva: la misma fila en el centro, la misma columna en el interior y, si
// no, el centro del 5x5.
static int32 Framework2DProcGenPick5x5(const FFramework2DTile5x5& Tiles, int32 Row, int32 Col)
{
	const int32 Candidates[4] = { Tiles.At(Row, Col), Tiles.At(Row, 2), Tiles.At(2, Col), Tiles.At(2, 2) };
	for (const int32 Value : Candidates)
	{
		if (Value >= 0) { return Value; }
	}
	return -1;
}

// Fila y columna del 5x5 que le toca a una casilla ocupada segun lo lejos que tiene el aire en cada
// direccion (1 = pegado, 2 = a una casilla). R cuenta desde abajo (R + 1 = encima).
template <typename OccupiedFnType>
static void Framework2DProcGenExposure5(const OccupiedFnType& IsOccupied, int32 X, int32 R, int32& OutRow, int32& OutCol)
{
	auto Dist = [&IsOccupied, X, R](int32 Dx, int32 Dr)
	{
		if (!IsOccupied(X + Dx, R + Dr)) { return 1; }
		if (!IsOccupied(X + 2 * Dx, R + 2 * Dr)) { return 2; }
		return 3;
	};
	const int32 Up = Dist(0, 1), Down = Dist(0, -1), Left = Dist(-1, 0), Right = Dist(1, 0);
	// Primero lo de fuera (borde) y luego la segunda fila: un saliente fino es borde arriba y abajo.
	if (Up == 1) { OutRow = 0; }
	else if (Down == 1) { OutRow = 4; }
	else if (Up == 2) { OutRow = 1; }
	else if (Down == 2) { OutRow = 3; }
	else { OutRow = 2; }
	// Si los dos lados estan al aire (una columna de una casilla), el centro (como en el 3x3).
	if (Left == 1 && Right != 1) { OutCol = 0; }
	else if (Right == 1 && Left != 1) { OutCol = 4; }
	else if (Left == 2 && Right > 2) { OutCol = 1; }
	else if (Right == 2 && Left > 2) { OutCol = 3; }
	else { OutCol = 2; }
}

// Fila (0 arriba, 1 medio, 2 abajo) y columna (0 izquierda, 1 medio, 2 derecha) del 3x3 que le toca
// a una casilla ocupada, segun que vecinos estan libres. R cuenta desde abajo (R + 1 = encima).
template <typename OccupiedFnType>
static void Framework2DProcGenExposure(const OccupiedFnType& IsOccupied, int32 X, int32 R, int32& OutRow, int32& OutCol)
{
	const bool bUpOpen = !IsOccupied(X, R + 1);
	const bool bDownOpen = !IsOccupied(X, R - 1);
	const bool bLeftOpen = !IsOccupied(X - 1, R);
	const bool bRightOpen = !IsOccupied(X + 1, R);
	OutRow = bUpOpen ? 0 : (bDownOpen ? 2 : 1);
	OutCol = (bLeftOpen && !bRightOpen) ? 0 : ((bRightOpen && !bLeftOpen) ? 2 : 1);
}

// Elemento al azar segun su peso (Pick en [0, suma de pesos)); cualquier lista con Weight.
template <typename ItemType>
static const ItemType& Framework2DProcGenPickByWeight(const TArray<ItemType>& Items, float Pick)
{
	for (const ItemType& Item : Items)
	{
		if (Pick < Item.Weight) { return Item; }
		Pick -= Item.Weight;
	}
	return Items.Last();
}

template <typename ItemType>
static float Framework2DProcGenTotalWeight(const TArray<ItemType>& Items)
{
	float Total = 0.0f;
	for (const ItemType& Item : Items) { Total += Item.Weight; }
	return Total;
}

// Nombre de capa de la receta; vacio = el de serie.
static FName Framework2DProcGenLayerName(FName Wanted, const TCHAR* Default)
{
	return Wanted.IsNone() ? FName(Default) : Wanted;
}

// Las capas que rellena la receta, con sus nombres de serie (una sola vez para el generador y
// para ApplyToMap: los objetos van a la misma capa que se crea y se vacia).
struct FFramework2DProcGenLayerNames
{
	FName Terrain, Background, Behind, Edges, Decoration, Water;

	explicit FFramework2DProcGenLayerNames(const FFramework2DProcGenSettings& Settings)
		: Terrain(Framework2DProcGenLayerName(Settings.TerrainLayer, TEXT("Terrain")))
		, Background(Framework2DProcGenLayerName(Settings.BackgroundLayer, TEXT("Background")))
		, Behind(Framework2DProcGenLayerName(Settings.BehindLayer, TEXT("Behind")))
		, Edges(Framework2DProcGenLayerName(Settings.EdgeLayer, TEXT("Edges")))
		, Decoration(Framework2DProcGenLayerName(Settings.DecorationLayer, TEXT("Decoration")))
		, Water(Framework2DProcGenLayerName(Settings.WaterLayer, TEXT("Water")))
	{
	}
};

static bool Framework2DProcGenHasAny(const TArray<int32>& Cells)
{
	for (const int32 Value : Cells)
	{
		if (Value >= 0) { return true; }
	}
	return false;
}

// =====================================================================
//  El generador. Trabaja en filas contadas DESDE ABAJO (R = 0 la de abajo) y solo al final
//  pasa a filas del mapa (Y = 0 arriba).
// =====================================================================
struct FFramework2DProcGenBuilder
{
	// Tramo llano del relieve: columnas [Start, End) a la misma altura.
	struct FPlateau
	{
		int32 Start = 0;
		int32 End = 0;
	};

	// Cascada: cae por la columna X, pegada al acantilado de la columna HighX.
	struct FFall
	{
		int32 X = 0;
		int32 HighX = 0;
	};

	// Trozo de plataforma flotante (o de puente) que hay en una casilla.
	enum class EPlatformPart : uint8 { None, Left, Middle, Right, Single };

	// Un objeto grande que se puede colocar (medidas en tiles, ya calculadas con su imagen).
	struct FPropInfo
	{
		int32 Id = 0;
		int32 Footprint = 1;   // suelo llano que necesita
		int32 ArtWidth = 1;    // ancho de la imagen (tiles): todo el ancho tiene que quedar sobre suelo
		int32 HeightTiles = 1; // alto de la imagen
		float Weight = 1.0f;
		EFramework2DPropDepth Depth = EFramework2DPropDepth::Behind;
		int32 Sink = 2;
		bool bRandomFlip = true;
	};

	// Objeto grande colocado: columna izquierda de su apoyo y fila (desde abajo) de la casilla en la que esta.
	struct FPlacedProp
	{
		const FPropInfo* Info = nullptr;
		int32 X = 0;
		int32 R = 0;
		bool bFlip = false;
	};

	FFramework2DProcGenBuilder(const FFramework2DBiome& InBiome, const FFramework2DProcGenSettings& InSettings, int32 InWidth, int32 InHeight)
		: Biome(InBiome)
		, Settings(InSettings)
		, Layers(InSettings)
		, W(InWidth)
		, H(InHeight)
		, b5x5(InBiome.Ground5.At(2, 2) >= 0)
		, Drop(b5x5 ? 1 : 0)
	{
	}

	const FFramework2DBiome& Biome;   // piezas ya filtradas: -1 = sin asignar
	const FFramework2DProcGenSettings& Settings;
	const FFramework2DProcGenLayerNames Layers;
	int32 W = 0;
	int32 H = 0;
	// Terreno 5x5: su fila de arriba es casi toda aire (la hierba empieza abajo del tile). El agua,
	// las cascadas y los puentes bajan Drop filas para quedar a ras de esa hierba.
	const bool b5x5;
	const int32 Drop;

	// Presupuesto de altura (ya recortado para que quepa en el mapa).
	int32 Levels = 1;
	int32 LevelHeight = 1;
	int32 Base = 1;

	FFramework2DProcGenReport Report;

	// Relieve por columna.
	TArray<int32> Fill;                     // filas macizas desde abajo
	TArray<EFramework2DProcGenSlope> Slope; // rampa en la fila Fill (None = sin rampa)
	TArray<bool> Wall;                      // muro del borde
	TArray<int32> NaturalFill;              // Fill antes de levantar los muros del borde
	TArray<bool> ForcedLake;                // poza al pie de una cascada: se llena siempre
	TArray<int32> WaterTop;                 // fila hasta donde llega el lago (0 = sin lago)
	TArray<FPlateau> Plateaus;
	TArray<FFall> Falls;
	TArray<int32> BridgeCap;                // 0 = sin puente; si no, el agua no pasa de esa fila (la del puente)
	TArray<bool> BridgeBank;                // orilla con el extremo de un puente (sin adornos junto a sus postes)
	TArray<FPropInfo> PropInfos;            // objetos grandes del bioma que se pueden colocar
	TArray<FPlacedProp> PlacedProps;

	// Rejillas de W x H (indice R * W + X, R desde abajo).
	TArray<int32> WaterCells;               // agua y cascadas (-1 = nada)
	TArray<EPlatformPart> PlatformCells;
	TArray<int32> TerrainCells;
	TArray<int32> BackgroundCells;
	TArray<int32> DecorationCells;
	TArray<bool> IslandCells;               // islas flotantes (macizo que se autotilea como el terreno)
	TArray<EPlatformPart> BridgeCells;      // tablas de los puentes (no cuentan como macizo)
	TArray<int32> EdgeCells;                // bordes naturales
	TArray<int32> BehindCells;              // capa de detras (el agua del lecho y la de detras de las orillas)
	TArray<bool> BlockCells;                // casillas ya cambiadas por un pie de pared
	TArray<uint8> SurfaceCols;              // columna del 5x5 (1-3) de las dos filas de arriba de cada columna
	int32 TilePixels = 16;                  // alto de un tile en pixeles (para los ajustes finos)

	int32 Cell(int32 X, int32 R) const { return R * W + X; }

	bool HasBridgeAt(int32 X, int32 R) const { return BridgeCells[Cell(X, R)] != EPlatformPart::None; }

	/** Fila de la superficie (filas macizas) de la altura Level. */
	int32 Surface(int32 Level) const { return Base + Level * LevelHeight; }

	FRandomStream Stream(EFramework2DProcGenStream Part) const { return Framework2DProcGenStream(Settings.Seed, Part); }

	// Altura del suelo para el agua y el fondo: los muros del borde no cuentan (si no, todo el
	// mapa seria una hondonada entre dos muros y se inundaria entero).
	int32 GroundHeight(int32 X) const { return Wall[X] ? NaturalFill[X] : Fill[X]; }

	bool HasRamp(int32 X) const { return Slope[X] != EFramework2DProcGenSlope::None; }

	bool HasWaterAt(int32 X, int32 R) const { return WaterCells[Cell(X, R)] >= 0; }

	// Agua en la casilla o la columna es de un lago que llega a esa fila: con el 5x5 (Drop 1) un lago
	// de una fila tiene el agua DENTRO de la fila de arriba de su suelo, y la de encima, la del suelo
	// libre, es la de las olas.
	bool IsWet(int32 X, int32 R) const { return HasWaterAt(X, R) || (WaterTop[X] > 0 && R < WaterTop[X] + Drop); }

	// Casilla del terreno ocupada (macizo, rampa o plataforma). Fuera del mapa: por debajo todo es
	// suelo, por encima aire y a los lados sigue la columna del borde (asi no salen bordes falsos).
	bool IsTerrainOccupied(int32 X, int32 R) const
	{
		if (R < 0) { return true; }
		if (R >= H) { return false; }
		if (X < 0 || X >= W) { return R < Fill[X < 0 ? 0 : W - 1]; }
		return R < Fill[X] || (HasRamp(X) && R == Fill[X]) || PlatformCells[Cell(X, R)] != EPlatformPart::None || IslandCells[Cell(X, R)];
	}

	void Run()
	{
		const int32 Num = W * H;
		Fill.Init(0, W);
		Slope.Init(EFramework2DProcGenSlope::None, W);
		Wall.Init(false, W);
		ForcedLake.Init(false, W);
		WaterTop.Init(0, W);
		WaterCells.Init(-1, Num);
		PlatformCells.Init(EPlatformPart::None, Num);
		TerrainCells.Init(-1, Num);
		BackgroundCells.Init(-1, Num);
		DecorationCells.Init(-1, Num);
		IslandCells.Init(false, Num);
		BridgeCells.Init(EPlatformPart::None, Num);
		EdgeCells.Init(-1, Num);
		BehindCells.Init(-1, Num);
		BlockCells.Init(false, Num);
		BridgeCap.Init(0, W);
		BridgeBank.Init(false, W);

		// El orden importa: los puentes se ponen antes que las cascadas (no caen sobre un puente)
		// y que los lagos (el agua queda bajo las tablas); las cascadas cavan su poza antes de
		// llenar los lagos, y plataformas e islas buscan hueco cuando el agua ya esta puesta. Lo que
		// va en la capa de bordes por casillas concretas (pies de pared, cantos de plataformas y
		// puentes) va antes que los bordes naturales, que no lo pisan.
		ComputeHeightBudget();
		if (Settings.ReliefStyle == EFramework2DReliefStyle::Hills) { BuildHills(); }
		else { BuildProfile(); }
		DigPits();
		RaiseEdgeWalls();
		PlaceBridges();
		PlaceWaterfalls();
		FillLakes();
		FinishWaterfalls();
		PlacePlatforms();
		PlaceIslands();
		BuildSurfaceColumns();
		AutotileTerrain();
		PlaceWallFeet();
		BuildBackground();
		PlacePlatformCaps();
		PlaceEdges();
		PlaceDecoration();
		PlaceProps();
		Report.bSuccess = true;
	}

	//---------------------- Presupuesto de altura ----------------------

	void ComputeHeightBudget()
	{
		const int32 WantedLevels = FMath::Clamp(Settings.Levels, 1, 16);
		LevelHeight = FMath::Clamp(Settings.LevelHeight, 1, 16);
		Base = FMath::Clamp(Settings.BaseHeight, 1, H - 2);
		Levels = WantedLevels;

		// Tiene que quedar cielo: la altura mas alta, como mucho a 3 filas del techo del mapa.
		if (Surface(Levels - 1) > H - 3)
		{
			Levels = FMath::Max(1, (H - 3 - Base) / LevelHeight + 1);
			if (Surface(Levels - 1) > H - 3)
			{
				// Ni con una sola altura cabe: baja el suelo base.
				Base = FMath::Max(1, H - 3);
			}
		}
		Report.Levels = Levels;
		if (Levels < WantedLevels)
		{
			AddWarning(Levels == 1
				? FString::Printf(TEXT("Only 1 height fits in a map %d tiles high."), H)
				: FString::Printf(TEXT("Only %d heights fit in a map %d tiles high."), Levels, H));
		}
	}

	void AddWarning(const FString& Warning)
	{
		if (!Report.Message.IsEmpty()) { Report.Message += TEXT("\n"); }
		Report.Message += Warning;
	}

	//---------------------- Relieve: llanos, rampas y acantilados ----------------------

	void BuildProfile()
	{
		const FRandomStream RandRelief = Stream(EFramework2DProcGenStream::Relief);
		const FRandomStream RandRamps = Stream(EFramework2DProcGenStream::Ramps);
		const int32 MinWidth = FMath::Max(1, Settings.PlateauMinWidth);
		const int32 MaxWidth = FMath::Max(MinWidth, Settings.PlateauMaxWidth);
		const int32 MaxStep = FMath::Clamp(Settings.MaxLevelStep, 1, FMath::Max(1, Levels - 1));

		int32 X = 0;
		int32 Level = RandRelief.RandRange(0, Levels - 1);
		int32 LastDir = 0;
		while (X < W)
		{
			// Un llano. En lo mas alto y lo mas bajo (la vuelta es obligada) y a veces sin mas, el llano
			// se alarga: mesetas y valles anchos en vez de almenas. Tres tiradas, SIEMPRE.
			const int32 BaseLen = RandRelief.RandRange(MinWidth, MaxWidth);
			const int32 ExtraLen = RandRelief.RandRange(MinWidth, MaxWidth);
			const float StayRoll = RandRelief.FRand();
			const bool bExtreme = Levels > 1 && (Level == 0 || Level == Levels - 1);
			const int32 Len = FMath::Min(BaseLen + ((bExtreme || StayRoll < 0.3f) ? ExtraLen : 0), W - X);
			AddPlateau(X, Len, Level);
			X += Len;
			if (X >= W) { break; }
			if (Levels == 1) { continue; } // todo llano: el siguiente tramo, a la misma altura

			// A que altura va el siguiente llano. Con inercia: lo normal es seguir subiendo (o
			// bajando), asi salen lomas y valles en vez de almenas (arriba, abajo, arriba...).
			const int32 Step = RandRelief.RandRange(1, MaxStep);
			const float DirRoll = RandRelief.FRand();
			int32 Dir = LastDir != 0 ? (DirRoll < 0.65f ? LastDir : -LastDir) : (DirRoll < 0.5f ? -1 : 1);
			if (Level + Dir * Step < 0 || Level + Dir * Step > Levels - 1) { Dir = -Dir; }
			LastDir = Dir;
			const int32 Next = FMath::Clamp(Level + Dir * Step, 0, Levels - 1);
			const int32 Delta = Next - Level;

			// Las dos tiradas de rampa se hacen SIEMPRE: tener piezas de rampa o no, no mueve el resto.
			const float RampRoll = RandRamps.FRand();
			const float GentleRoll = RandRamps.FRand();
			if (FMath::Abs(Delta) == 1)
			{
				const bool bUp = Delta > 0;
				const bool bHas45 = bUp ? Biome.RampUp >= 0 : Biome.RampDown >= 0;
				const bool bHasGentle = bUp
					? (Biome.GentleUpLow >= 0 && Biome.GentleUpHigh >= 0)
					: (Biome.GentleDownHigh >= 0 && Biome.GentleDownLow >= 0);
				if ((bHas45 || bHasGentle) && RampRoll < Settings.RampChance)
				{
					const bool bGentle = bHasGentle && (!bHas45 || GentleRoll < Settings.GentleRampChance);
					const int32 RampWidth = bGentle ? 2 * LevelHeight : LevelHeight;
					// Tiene que quedar al menos una columna de llano detras de la rampa.
					if (X + RampWidth < W)
					{
						WriteRamp(X, Level, Next, bGentle);
						X += RampWidth;
						++Report.Ramps;
						Level = Next;
						continue;
					}
				}
			}

			// Acantilado: el siguiente llano empieza directamente a la otra altura.
			if (Delta != 0) { ++Report.Cliffs; }
			Level = Next;
		}
	}

	void AddPlateau(int32 Start, int32 Len, int32 Level)
	{
		for (int32 X = Start; X < Start + Len; ++X)
		{
			Fill[X] = Surface(Level);
			Slope[X] = EFramework2DProcGenSlope::None;
		}
		FPlateau Plateau;
		Plateau.Start = Start;
		Plateau.End = Start + Len;
		Plateaus.Add(Plateau);
	}

	// Columnas de una rampa de una altura entre FromLevel y ToLevel, empezando en X0. El borde de la
	// rampa coincide con la fila de arriba del llano de cada lado.
	void WriteRamp(int32 X0, int32 FromLevel, int32 ToLevel, bool bGentle)
	{
		const bool bUp = ToLevel > FromLevel;
		const int32 Low = Surface(FMath::Min(FromLevel, ToLevel));
		const int32 High = Surface(FMath::Max(FromLevel, ToLevel));
		for (int32 J = 0; J < LevelHeight; ++J)
		{
			const int32 ColumnFill = bUp ? Low + J : High - 1 - J;
			if (!bGentle)
			{
				Fill[X0 + J] = ColumnFill;
				Slope[X0 + J] = bUp ? EFramework2DProcGenSlope::Up : EFramework2DProcGenSlope::Down;
				continue;
			}
			// Suave: dos columnas por tile de altura (mitad baja y mitad alta, en el orden de la marcha).
			Fill[X0 + 2 * J] = ColumnFill;
			Fill[X0 + 2 * J + 1] = ColumnFill;
			Slope[X0 + 2 * J] = bUp ? EFramework2DProcGenSlope::GentleUpLow : EFramework2DProcGenSlope::GentleDownHigh;
			Slope[X0 + 2 * J + 1] = bUp ? EFramework2DProcGenSlope::GentleUpHigh : EFramework2DProcGenSlope::GentleDownLow;
		}
	}

	//---------------------- Relieve: lomas ----------------------

	// Ruido suave de una dimension: valores al azar cada Wave columnas, unidos con curva coseno.
	static float SmoothNoise(const TArray<float>& Lattice, float X, float Wave)
	{
		const float P = X / Wave;
		const int32 I = FMath::FloorToInt(P);
		const float T = P - (float)I;
		const float A = Lattice[FMath::Clamp(I, 0, Lattice.Num() - 1)];
		const float B = Lattice[FMath::Clamp(I + 1, 0, Lattice.Num() - 1)];
		const float S = (1.0f - FMath::Cos(T * PI)) * 0.5f;
		return FMath::Lerp(A, B, S);
	}

	// Lomas: la altura de cada columna sale de un ruido suave (tres octavas) entre el suelo base y
	// la altura mas alta. Donde sube o baja un tile se ponen rampas (de 45 grados si sube de una
	// columna a la siguiente; suaves si hay un llano de dos columnas antes del cambio).
	void BuildHills()
	{
		const FRandomStream RandHills = Stream(EFramework2DProcGenStream::Hills);
		const FRandomStream RandRamps = Stream(EFramework2DProcGenStream::Ramps);
		const float Rough = FMath::Clamp(Settings.Roughness, 0.0f, 1.0f);
		const float Wave = FMath::Lerp(48.0f, 9.0f, Rough);
		const float Amps[3] = { 1.0f, 0.45f, 0.2f };
		TArray<float> Lattices[3];
		for (int32 O = 0; O < 3; ++O)
		{
			const float OctaveWave = Wave / (float)(1 << O);
			const int32 Count = FMath::CeilToInt((float)W / OctaveWave) + 2;
			for (int32 I = 0; I < Count; ++I) { Lattices[O].Add(RandHills.FRand()); }
		}

		const int32 Low = Base;
		const int32 High = Surface(Levels - 1);
		TArray<int32> Target;
		Target.SetNumZeroed(W);
		for (int32 X = 0; X < W; ++X)
		{
			float V = 0.0f;
			float Sum = 0.0f;
			for (int32 O = 0; O < 3; ++O)
			{
				V += SmoothNoise(Lattices[O], (float)X + 0.5f, Wave / (float)(1 << O)) * Amps[O];
				Sum += Amps[O];
			}
			// Estirado para usar todo el rango (el ruido rara vez llega a los extremos).
			V = FMath::Clamp((V / Sum - 0.2f) / 0.6f, 0.0f, 1.0f);
			Target[X] = Low + FMath::RoundToInt(V * (float)(High - Low));
			Fill[X] = Target[X];
			Slope[X] = EFramework2DProcGenSlope::None;
		}

		const bool bUp45 = Biome.RampUp >= 0;
		const bool bDown45 = Biome.RampDown >= 0;
		const bool bGentleUp = Biome.GentleUpLow >= 0 && Biome.GentleUpHigh >= 0;
		const bool bGentleDown = Biome.GentleDownHigh >= 0 && Biome.GentleDownLow >= 0;
		auto T = [&Target, this](int32 X) { return Target[FMath::Clamp(X, 0, W - 1)]; };
		for (int32 X = 0; X < W; ++X)
		{
			if (HasRamp(X)) { continue; }
			// Dos tiradas por columna, SIEMPRE: tener piezas de rampa o no, no mueve el resto.
			const float RampRoll = RandRamps.FRand();
			const float GentleRoll = RandRamps.FRand();
			const bool bRises = X + 1 < W && T(X + 1) == T(X) + 1;
			const bool bFalls = X > 0 && T(X - 1) == T(X) + 1;
			if ((bRises && bFalls) || RampRoll >= Settings.RampChance) { continue; }

			// Suave que sube: llano de dos columnas y luego un tile mas.
			if (!bFalls && bGentleUp && X + 2 < W && T(X + 1) == T(X) && T(X + 2) == T(X) + 1 && !HasRamp(X + 1) &&
				(!bUp45 || GentleRoll < Settings.GentleRampChance))
			{
				Slope[X] = EFramework2DProcGenSlope::GentleUpLow;
				Slope[X + 1] = EFramework2DProcGenSlope::GentleUpHigh;
				++Report.Ramps;
				continue;
			}
			if (bRises && bUp45)
			{
				Slope[X] = EFramework2DProcGenSlope::Up;
				++Report.Ramps;
				continue;
			}
			if (bFalls)
			{
				// Suave que baja: dos columnas a la misma altura justo despues del borde.
				if (bGentleDown && X + 1 < W && T(X + 1) == T(X) && (X + 2 >= W || T(X + 2) <= T(X)) &&
					(!bDown45 || GentleRoll < Settings.GentleRampChance))
				{
					Slope[X] = EFramework2DProcGenSlope::GentleDownHigh;
					Slope[X + 1] = EFramework2DProcGenSlope::GentleDownLow;
					++Report.Ramps;
					continue;
				}
				if (bDown45)
				{
					Slope[X] = EFramework2DProcGenSlope::Down;
					++Report.Ramps;
				}
			}
		}

		// Escalones que quedaron sin rampa y tramos llanos (para fosos y plataformas).
		for (int32 X = 0; X + 1 < W; ++X)
		{
			const bool bCovered = (HasRamp(X) && T(X + 1) > T(X)) || (HasRamp(X + 1) && T(X) > T(X + 1));
			if (T(X) != T(X + 1) && !bCovered) { ++Report.Cliffs; }
		}
		int32 RunStart = 0;
		for (int32 X = 1; X <= W; ++X)
		{
			if (X == W || HasRamp(X) || HasRamp(X - 1) || Fill[X] != Fill[RunStart])
			{
				if (!HasRamp(RunStart))
				{
					FPlateau Plateau;
					Plateau.Start = RunStart;
					Plateau.End = X;
					Plateaus.Add(Plateau);
				}
				RunStart = X;
			}
		}
	}

	//---------------------- Fosos y muros ----------------------

	void DigPits()
	{
		const FRandomStream RandPits = Stream(EFramework2DProcGenStream::Pits);
		if (!(Settings.PitChance > 0.0f)) { return; }
		const int32 Depth = FMath::Max(1, Settings.PitDepth);
		const TArray<bool> UnderLake = ComputeLakeMask();
		// Ni en el primer llano ni en el ultimo (el jugador empieza y acaba en suelo firme).
		for (int32 I = 1; I < Plateaus.Num() - 1; ++I)
		{
			const FPlateau& Plateau = Plateaus[I];
			const int32 Len = Plateau.End - Plateau.Start;
			if (Len < 11) { continue; }
			if (RandPits.FRand() >= Settings.PitChance) { continue; }
			// Cuatro columnas de llano a cada lado y cinco por donde el llano acaba en un escalon hacia
			// abajo (con menos quedan torres sueltas entre el foso y el escalon); 3 de ancho como minimo
			// (uno de 2 parece un pozo).
			const int32 Height = Fill[Plateau.Start];
			const int32 MarginL = Plateau.Start > 0 && Fill[Plateau.Start - 1] < Height ? 5 : 4;
			const int32 MarginR = Plateau.End < W && Fill[Plateau.End] < Height ? 5 : 4;
			if (Len < 3 + MarginL + MarginR) { continue; }
			const int32 PitWidth = RandPits.RandRange(3, FMath::Min(5, Len - MarginL - MarginR));
			const int32 Start = Plateau.Start + RandPits.RandRange(MarginL, Len - PitWidth - MarginR);
			// Un llano que quedaria bajo un lago no lleva foso: dejaria el fondo del lago lleno de agujeros.
			bool bUnderLake = false;
			for (int32 X = Plateau.Start; X < Plateau.End && !bUnderLake; ++X) { bUnderLake = UnderLake[X]; }
			if (bUnderLake) { continue; }
			for (int32 X = Start; X < Start + PitWidth; ++X)
			{
				Fill[X] = FMath::Max(1, Fill[X] - Depth);
			}
			++Report.Pits;
		}
	}

	// Por columna: true si quedaria bajo el agua de un lago (con el ancho maximo, las rampas y los
	// puentes). Todo false si el bioma no tiene agua. No mira el % de lagos: asi no mueve el relieve.
	TArray<bool> ComputeLakeMask() const
	{
		TArray<bool> Mask;
		Mask.Init(false, W);
		if (Biome.WaterSurface < 0 && Biome.WaterBody < 0) { return Mask; }
		ForEachLakeBasin([this, &Mask](int32 Start, int32 End, int32 Level)
		{
			for (int32 C = Start; C < End; ++C) { Mask[C] = !HasRamp(C) && GroundHeight(C) < Level; }
		});
		return Mask;
	}

	void RaiseEdgeWalls()
	{
		NaturalFill = Fill;
		if (!Settings.bEdgeWalls) { return; }
		const int32 Edges[2] = { 0, W - 1 };
		for (const int32 X : Edges)
		{
			Fill[X] = H; // macizo de abajo arriba del todo
			Slope[X] = EFramework2DProcGenSlope::None;
			Wall[X] = true;
		}
	}

	//---------------------- Puentes ----------------------

	// Puentes sobre huecos (fosos, lagos, valles estrechos) entre dos orillas a la misma altura, sin
	// rampas. Sin el 5x5, tablas (en la fila de arriba de las orillas) y postes en el
	// hueco. Con el 5x5, como se dibujan en los tilesets: las tablas a la altura de la segunda fila
	// de las orillas (la de arriba es casi toda aire), su canto encima y los extremos con sus postes
	// SOBRE las dos orillas, en la capa de bordes (delante y sin chocar).
	void PlaceBridges()
	{
		if (Biome.BridgeMiddle < 0) { return; }
		const FRandomStream RandBridges = Stream(EFramework2DProcGenStream::Bridges);
		constexpr int32 MinBridgeSpacing = 12; // columnas entre un puente y el siguiente: sin modulos repetidos
		int32 LastBridgeEnd = -1000000;
		int32 X = 1;
		while (X < W - 1)
		{
			const int32 BankX = X - 1;
			if (HasRamp(BankX) || Wall[BankX] || Fill[X] >= Fill[BankX]) { ++X; continue; }
			const int32 Bank = Fill[BankX];
			int32 End = X;
			int32 Deepest = Bank;
			while (End < W && Fill[End] < Bank)
			{
				Deepest = FMath::Min(Deepest, Fill[End]);
				++End;
			}
			if (End >= W) { break; }

			// Una tirada por hueco candidato, SIEMPRE.
			const float Roll = RandBridges.FRand();
			const int32 Gap = End - X;
			const int32 Deck = Bank - 1 - Drop;
			bool bValid = Fill[End] == Bank && !HasRamp(End) && !Wall[End] && Gap >= 2 && Gap <= 12 && Deepest <= Deck - 1 &&
				X - LastBridgeEnd >= MinBridgeSpacing;
			for (int32 C = X; C < End && bValid; ++C) { bValid = !HasRamp(C) && !Wall[C] && Fill[C] <= Deck; }
			if (bValid && Roll < Settings.BridgeChance)
			{
				for (int32 C = X; C < End; ++C)
				{
					EPlatformPart Part = EPlatformPart::Middle;
					if (!b5x5 && C == X) { Part = EPlatformPart::Left; }
					else if (!b5x5 && C == End - 1) { Part = EPlatformPart::Right; }
					BridgeCells[Cell(C, Deck)] = Part;
					BridgeCap[C] = Deck;
					if (b5x5 && Deck + 1 < H)
					{
						const int32 CapPiece = C == X ? Biome.BridgeCapLeft : (C == End - 1 ? Biome.BridgeCapRight : Biome.BridgeCapMiddle);
						EdgeCells[Cell(C, Deck + 1)] = CapPiece >= 0 ? CapPiece : Biome.BridgeCapMiddle;
					}
				}
				BridgeBank[BankX] = true;
				BridgeBank[End] = true;
				if (b5x5)
				{
					// Extremos y postes sobre las orillas: el extremo en la segunda fila, el poste bajo en la
					// de arriba (su hierba casa con la de la orilla) y el alto encima.
					auto Anchor = [this](int32 C, int32 Row, int32 Value) { if (Value >= 0 && Row < H) { EdgeCells[Cell(C, Row)] = Value; } };
					Anchor(BankX, Deck, Biome.BridgeLeft);
					Anchor(BankX, Deck + 1, Biome.BridgePostLeftLow);
					Anchor(BankX, Deck + 2, Biome.BridgePostLeftHigh);
					Anchor(End, Deck, Biome.BridgeRight);
					Anchor(End, Deck + 1, Biome.BridgePostRightLow);
					Anchor(End, Deck + 2, Biome.BridgePostRightHigh);
				}
				else
				{
					// Postes encima de los extremos (decoracion: no chocan).
					auto Post = [this](int32 C, int32 Row, int32 Value)
					{
						if (Value >= 0 && Row < H && C >= 0 && C < W && Row >= Fill[C]) { DecorationCells[Cell(C, Row)] = Value; }
					};
					Post(X, Deck + 1, Biome.BridgePostLeftLow);
					Post(X, Deck + 2, Biome.BridgePostLeftHigh);
					Post(End - 1, Deck + 1, Biome.BridgePostRightLow);
					Post(End - 1, Deck + 2, Biome.BridgePostRightHigh);
				}
				++Report.Bridges;
				LastBridgeEnd = End;
			}
			X = End;
		}
	}

	int32 BridgePiece(EPlatformPart Part) const
	{
		const int32 Middle = Biome.BridgeMiddle;
		switch (Part)
		{
		case EPlatformPart::Left:  return Biome.BridgeLeft >= 0 ? Biome.BridgeLeft : Middle;
		case EPlatformPart::Right: return Biome.BridgeRight >= 0 ? Biome.BridgeRight : Middle;
		default:                   return Middle;
		}
	}

	//---------------------- Cascadas (antes del agua: cavan su poza) ----------------------

	void PlaceWaterfalls()
	{
		if (Biome.WaterfallBody < 0) { return; }
		const FRandomStream RandFalls = Stream(EFramework2DProcGenStream::Waterfalls);
		const bool bBiomeHasWater = Biome.WaterSurface >= 0 || Biome.WaterBody >= 0;
		TArray<bool> HasFall;
		HasFall.Init(false, W);
		const TArray<bool> UnderLake = bBiomeHasWater ? ComputeLakeMask() : TArray<bool>();
		for (int32 X = 0; X + 1 < W; ++X)
		{
			const int32 NextX = X + 1;
			if (HasRamp(X) || HasRamp(NextX) || Wall[X] || Wall[NextX]) { continue; }
			if (FMath::Abs(Fill[X] - Fill[NextX]) < 2) { continue; }
			const int32 LowX = Fill[X] < Fill[NextX] ? X : NextX;
			const int32 HighX = LowX == X ? NextX : X;

			// Una tirada por acantilado candidato, en orden de X (aunque la columna ya tenga cascada o
			// haya un puente: los puentes no mueven las demas cascadas).
			const float Roll = RandFalls.FRand();
			if (Roll >= Settings.WaterfallChance || HasFall[LowX]) { continue; }
			if (BridgeCap[X] > 0 || BridgeCap[NextX] > 0 || BridgeBank[X] || BridgeBank[NextX]) { continue; } // ni bajo un puente ni en sus extremos
			HasFall[LowX] = true;
			FFall NewFall;
			NewFall.X = LowX;
			NewFall.HighX = HighX;
			Falls.Add(NewFall);
			++Report.Waterfalls;

			if (bBiomeHasWater)
			{
				DigPlungePool(LowX, LowX < HighX ? -1 : 1, UnderLake);
			}
		}
	}

	// Poza al pie de la cascada: baja 1 las dos columnas de su pie (alejandose del acantilado) y
	// las marca como hondonada que se llena siempre. Solo si el suelo de alrededor la cierra.
	void DigPlungePool(int32 FallX, int32 Away, const TArray<bool>& UnderLake)
	{
		const int32 NextX = FallX + Away;
		const int32 BeyondX = FallX + 2 * Away;
		if (BeyondX < 0 || BeyondX >= W) { return; }
		const int32 PoolFloor = Fill[FallX];
		if (Fill[NextX] != PoolFloor || HasRamp(NextX) || Wall[NextX]) { return; }
		// Si el pie va a quedar bajo un lago, el lago la cubre: cavar dejaria un agujero en su fondo.
		if (UnderLake[FallX]) { return; }
		// Dos columnas de orilla (con una sola quedaria un pilar suelto entre la poza y lo que siga).
		const int32 FarX = FallX + 3 * Away;
		if (Fill[BeyondX] < PoolFloor || FarX < 0 || FarX >= W || Fill[FarX] < PoolFloor) { return; }
		if (PoolFloor < 2) { return; } // siempre queda al menos una fila de suelo debajo
		--Fill[FallX];
		--Fill[NextX];
		ForcedLake[FallX] = true;
		ForcedLake[NextX] = true;
	}

	//---------------------- Lagos ----------------------

	void FillLakes()
	{
		if (Biome.WaterSurface < 0 && Biome.WaterBody < 0) { return; }
		// Si falta una de las dos piezas, la otra hace de las dos.
		const int32 SurfaceValue = Biome.WaterSurface >= 0 ? Biome.WaterSurface : Biome.WaterBody;
		const int32 BodyValue = Biome.WaterBody >= 0 ? Biome.WaterBody : Biome.WaterSurface;
		const FRandomStream RandWater = Stream(EFramework2DProcGenStream::Water);
		ForEachLakeBasin([&](int32 RunStart, int32 RunEnd, int32 Level)
		{
			// Las pozas de las cascadas y lo que hay bajo un puente se llenan siempre (un puente sobre
			// una zanja seca no tiene sentido).
			bool bForced = false;
			for (int32 Column = RunStart; Column < RunEnd; ++Column) { bForced = bForced || ForcedLake[Column] || BridgeCap[Column] > 0; }

			// Una tirada por hondonada, siempre (las pozas de las cascadas se llenan sin mirarla).
			const bool bRollPassed = RandWater.FRand() < Settings.LakeChance;
			if (!bForced && !bRollPassed) { return; }

			// Con el 5x5 el agua baja Drop filas: la superficie queda a ras de la hierba de las orillas
			// (que empieza abajo de su fila de arriba) y el fondo tapa la fila de arriba del lecho.
			const int32 SurfaceRow = Level - 1 - Drop;
			bool bAnyWater = false;
			for (int32 Column = RunStart; Column < RunEnd; ++Column)
			{
				const int32 ColumnFloor = GroundHeight(Column);
				if (HasRamp(Column) || ColumnFloor >= Level) { continue; }
				for (int32 R = FMath::Max(0, ColumnFloor - Drop); R <= SurfaceRow; ++R)
				{
					const int32 Value = (R == SurfaceRow) ? SurfaceValue : BodyValue;
					WaterBehindBanks(Column, R, Value);
					// La fila de arriba del lecho (con el 5x5): el agua detras, la hierba del lecho delante;
					// si no, el agua (opaca) la cortaria en recto. En un lago de una fila y en las pozas es
					// la de la superficie: delante quedan las olas.
					if (R < ColumnFloor) { BehindCells[Cell(Column, R)] = Value; continue; }
					WaterCells[Cell(Column, R)] = Value;
				}
				WaterTop[Column] = SurfaceRow + 1;
				bAnyWater = true;
				// Olas que asoman por encima de la superficie (si caben: aire y sin puente).
				// Bajo un puente, detras de las tablas (asoman por su parte de abajo, sin cortar el agua).
				const int32 CrestRow = SurfaceRow + 1;
				if (Biome.WaterCrest >= 0 && CrestRow < H && !IsTerrainOccupied(Column, CrestRow))
				{
					if (BridgeCap[Column] == 0) { WaterCells[Cell(Column, CrestRow)] = Biome.WaterCrest; }
					else if (BehindCells[Cell(Column, CrestRow)] < 0) { BehindCells[Cell(Column, CrestRow)] = Biome.WaterCrest; }
					WaterBehindBanks(Column, CrestRow, Biome.WaterCrest);
				}
			}
			if (bAnyWater) { ++Report.Lakes; }
		});
	}

	// Recorre, de izquierda a derecha, las hondonadas que se pueden llenar de agua: Visit(Start, End,
	// Level) con las columnas [Start, End) y el nivel del agua (filas desde abajo). Una hondonada son
	// las columnas seguidas por debajo del menor de los picos a sus dos lados; si es mas ancha que el
	// maximo, el agua baja una fila y cada tramo que sigue por debajo es otra (sus orillas quedan por
	// encima: no se sale). El agua no pisa las rampas (baja hasta la mas baja) ni las tablas de un
	// puente (queda justo debajo).
	template <typename VisitType>
	void ForEachLakeBasin(const VisitType& Visit) const
	{
		TArray<int32> LeftMax, RightMax;
		LeftMax.SetNumUninitialized(W);
		RightMax.SetNumUninitialized(W);
		for (int32 X = 0; X < W; ++X) { LeftMax[X] = FMath::Max(X > 0 ? LeftMax[X - 1] : 0, GroundHeight(X)); }
		for (int32 X = W - 1; X >= 0; --X) { RightMax[X] = FMath::Max(X < W - 1 ? RightMax[X + 1] : 0, GroundHeight(X)); }
		auto LevelAt = [&LeftMax, &RightMax](int32 Column) { return FMath::Min(LeftMax[Column], RightMax[Column]); };

		// Pila: se meten de derecha a izquierda para sacar primero la de la izquierda.
		struct FBasin { int32 Start; int32 End; int32 Level; };
		TArray<FBasin> Basins;
		int32 X = W - 1;
		while (X >= 0)
		{
			if (LevelAt(X) <= GroundHeight(X)) { --X; continue; }
			const int32 RunEnd = X + 1;
			int32 Level = LevelAt(X);
			while (X >= 0 && LevelAt(X) > GroundHeight(X))
			{
				Level = FMath::Min(Level, LevelAt(X));
				--X;
			}
			Basins.Add({ X + 1, RunEnd, Level });
		}

		const int32 MaxWidth = FMath::Max(3, Settings.MaxLakeWidth);
		while (Basins.Num() > 0)
		{
			const FBasin Basin = Basins.Pop();
			if (Basin.End - Basin.Start > MaxWidth)
			{
				const int32 Lower = Basin.Level - 1;
				int32 Column = Basin.End - 1;
				while (Column >= Basin.Start)
				{
					if (GroundHeight(Column) >= Lower) { --Column; continue; }
					const int32 SubEnd = Column + 1;
					while (Column >= Basin.Start && GroundHeight(Column) < Lower) { --Column; }
					Basins.Add({ Column + 1, SubEnd, Lower });
				}
				continue;
			}
			int32 Level = Basin.Level;
			for (int32 Column = Basin.Start; Column < Basin.End; ++Column)
			{
				if (HasRamp(Column)) { Level = FMath::Min(Level, Fill[Column]); }
				if (BridgeCap[Column] > 0) { Level = FMath::Min(Level, BridgeCap[Column] + Drop); }
			}
			Visit(Basin.Start, Basin.End, Level);
		}
	}

	// Con el 5x5, agua de la casilla (X, R) tambien detras de la orilla de cada lado (capa de detras):
	// los bordes de roca y la hierba tienen margenes transparentes y por ahi se veria el fondo.
	void WaterBehindBanks(int32 X, int32 R, int32 Value)
	{
		if (!b5x5) { return; } // con el 3x3 el borde de las piezas suele llegar al tile
		for (const int32 Side : { X - 1, X + 1 })
		{
			if (Side < 0 || Side >= W || !IsTerrainOccupied(Side, R) || BehindCells[Cell(Side, R)] >= 0) { continue; }
			BehindCells[Cell(Side, R)] = Value;
		}
	}

	// Cada cascada cae desde el borde del acantilado hasta la superficie del lago (sin pisarla) o
	// hasta el suelo. Si quedan menos de 2 casillas, no hay cascada. Con el 5x5 empieza a ras de la
	// hierba del acantilado (su fila de arriba es casi toda aire) y acaba sobre la del suelo.
	void FinishWaterfalls()
	{
		const int32 BodyValue = Biome.WaterfallBody;
		const int32 TopValue = Biome.WaterfallTop >= 0 ? Biome.WaterfallTop : BodyValue;
		const int32 FoamValue = Biome.WaterfallBottom >= 0 ? Biome.WaterfallBottom : BodyValue;
		const TArray<bool> UnderLake = Falls.Num() > 0 ? ComputeLakeMask() : TArray<bool>();
		for (const FFall& Fall : Falls)
		{
			const int32 Top = Fill[Fall.HighX] - 1 - Drop;
			const int32 Bottom = WaterTop[Fall.X] > 0 ? WaterTop[Fall.X] : Fill[Fall.X] - Drop;
			// Una cascada que cae a una hondonada que se quedo seca parece una fuga: fuera.
			const bool bDryHollow = WaterTop[Fall.X] == 0 && UnderLake.IsValidIndex(Fall.X) && UnderLake[Fall.X];
			if (bDryHollow || Bottom > Top - 1)
			{
				--Report.Waterfalls;
				continue;
			}
			for (int32 R = Bottom; R <= Top; ++R)
			{
				const int32 Value = (R == Top) ? TopValue : ((R == Bottom) ? FoamValue : BodyValue);
				WaterCells[Cell(Fall.X, R)] = Value;
				WaterBehindBanks(Fall.X, R, Value);
				// Detras del acantilado, la caida (no el lago de la poza): sin rendija entre los dos.
				if (b5x5 && IsTerrainOccupied(Fall.HighX, R)) { BehindCells[Cell(Fall.HighX, R)] = (R == Top) ? TopValue : BodyValue; }
			}
			// La cabeza, con las olas encima: sin borde recto en el aire.
			if (Biome.WaterCrest >= 0 && Top + 1 < H && !IsTerrainOccupied(Fall.X, Top + 1) && !HasWaterAt(Fall.X, Top + 1))
			{
				WaterCells[Cell(Fall.X, Top + 1)] = Biome.WaterCrest;
			}
		}
	}

	//---------------------- Plataformas flotantes ----------------------

	void PlacePlatforms()
	{
		const FRandomStream RandPlatforms = Stream(EFramework2DProcGenStream::Platforms);
		const int32 MinLength = FMath::Max(1, Settings.PlatformMinLength);
		const int32 MaxLength = FMath::Max(MinLength, Settings.PlatformMaxLength);
		const int32 Gap = FMath::Max(3, LevelHeight + 1); // aire entre el suelo y la plataforma
		for (const FPlateau& Plateau : Plateaus)
		{
			const int32 Len = Plateau.End - Plateau.Start;
			if (Len < MinLength + 2) { continue; }
			if (RandPlatforms.FRand() >= Settings.PlatformChance) { continue; }

			// Dentro del llano, con al menos una columna libre a cada lado.
			const int32 Length = RandPlatforms.RandRange(MinLength, FMath::Min(MaxLength, Len - 2));
			const int32 Start = Plateau.Start + RandPlatforms.RandRange(1, Len - 1 - Length);
			int32 GroundTop = 0;
			for (int32 X = Start; X < Start + Length; ++X)
			{
				// Sobre un puente, el suelo son sus tablas (y su canto, con el 5x5): sitio para pasar por encima.
				GroundTop = FMath::Max(GroundTop, BridgeCap[X] > 0 ? FMath::Max(Fill[X], BridgeCap[X] + 1 + Drop) : Fill[X]);
			}
			// Con terreno 5x5 y sin piezas de plataforma, la plataforma es de TRES filas (las dos de
			// arriba del 5x5 y la de abajo): la de arriba es solo hierba y con la de abajo pegada la
			// hierba se cortaria en recto. Crece hacia abajo: lo alto queda donde con dos filas.
			const int32 Thick = (b5x5 && Biome.PlatformMiddle < 0) ? 3 : 1;
			const int32 Row = GroundTop + Gap + FMath::Min(Thick - 1, 1);
			if (Row > H - 3 || !IsPlatformSpotFree(Start - 1, Start + Length, Row - Thick, Row + 1)) { continue; }

			for (int32 X = Start; X < Start + Length; ++X)
			{
				EPlatformPart Part = EPlatformPart::Middle;
				if (Length == 1) { Part = EPlatformPart::Single; }
				else if (X == Start) { Part = EPlatformPart::Left; }
				else if (X == Start + Length - 1) { Part = EPlatformPart::Right; }
				for (int32 K = 0; K < Thick; ++K) { PlatformCells[Cell(X, Row - K)] = Part; }
			}
			++Report.Platforms;
		}
	}

	//---------------------- Islas flotantes ----------------------

	// Islas con base de roca: arriba un tramo de ancho completo y debajo filas cada vez mas
	// estrechas (se autotilean con el 3x3: hierba arriba y roca por los lados y debajo).
	void PlaceIslands()
	{
		if (!(Settings.IslandChance > 0.0f)) { return; }
		const FRandomStream RandIslands = Stream(EFramework2DProcGenStream::Islands);
		const int32 MinWidth = FMath::Max(2, Settings.IslandMinWidth);
		const int32 MaxWidth = FMath::Max(MinWidth, Settings.IslandMaxWidth);
		const int32 Gap = FMath::Max(3, LevelHeight + 1);
		int32 X = 2;
		while (X < W - 3)
		{
			// Cuatro tiradas por tramo, SIEMPRE.
			const float Roll = RandIslands.FRand();
			const int32 WidthRoll = RandIslands.RandRange(MinWidth, MaxWidth);
			const int32 Thick = RandIslands.RandRange(2, 4);
			const int32 Lift = RandIslands.RandRange(0, 2);
			if (Roll >= Settings.IslandChance) { X += 10; continue; }

			const int32 Width = FMath::Min(WidthRoll, W - 2 - X);
			if (Width < 2) { break; }
			int32 Ground = 0;
			for (int32 C = FMath::Max(0, X - 1); C <= FMath::Min(W - 1, X + Width); ++C)
			{
				Ground = FMath::Max(Ground, Fill[C] + (HasRamp(C) ? 1 : 0));
			}
			const int32 Bottom = Ground + Gap + Lift;
			// Con terreno 5x5, tres filas como minimo (ver abajo).
			const int32 Rows = b5x5 ? FMath::Max(Thick, 3) : Thick;
			const int32 Top = Bottom + Rows - 1;
			// Debajo, sitio para una plataforma con sus plantas y una fila libre (no pegada a ella).
			constexpr int32 UnderClear = 4;
			if (Top > H - 3 || !IsIslandSpotFree(X - 1, X + Width, Bottom - UnderClear, Top + 1))
			{
				X += Width + 4;
				continue;
			}

			// Fila K desde arriba: se estrecha hacia abajo (como una gota). Con terreno 5x5 todas son de
			// ancho completo: el 5x5 no tiene esquinas interiores y cada escalon de debajo dejaria un
			// corte recto entre la roca de abajo y el interior (y con tres filas o mas, la base de la
			// hierba nunca toca la roca fina).
			const int32 Flat = b5x5 ? Rows - 1 : 0;
			for (int32 K = 0; K < Rows; ++K)
			{
				const int32 Inset = K <= Flat ? 0 : FMath::CeilToInt((float)(K - Flat) * (float)Width / (2.0f * (float)Rows));
				const int32 RowWidth = Width - 2 * Inset;
				if (RowWidth < 1) { break; }
				for (int32 C = X + Inset; C < X + Inset + RowWidth; ++C)
				{
					IslandCells[Cell(C, Top - K)] = true;
				}
			}
			++Report.Islands;
			X += Width + 6;
		}
	}

	bool IsIslandSpotFree(int32 X0, int32 X1, int32 R0, int32 R1) const
	{
		for (int32 R = R0; R <= R1; ++R)
		{
			for (int32 X = X0; X <= X1; ++X)
			{
				if (X < 0 || X >= W || R < 0 || R >= H) { continue; }
				if (IsTerrainOccupied(X, R) || HasWaterAt(X, R) || HasBridgeAt(X, R)) { return false; }
			}
		}
		return true;
	}

	// Ninguna casilla de las filas R0..R1 entre las columnas X0 y X1 (incluidas) es agua, cascada,
	// rampa, macizo, puente, isla, otra plataforma ni un poste de puente (en la decoracion o en los
	// bordes).
	bool IsPlatformSpotFree(int32 X0, int32 X1, int32 R0, int32 R1) const
	{
		for (int32 R = R0; R <= R1; ++R)
		{
			for (int32 X = X0; X <= X1; ++X)
			{
				if (X < 0 || X >= W || R < 0 || R >= H) { continue; }
				if (R < Fill[X] || (HasRamp(X) && R == Fill[X]) || HasWaterAt(X, R) || HasBridgeAt(X, R) ||
					IslandCells[Cell(X, R)] || PlatformCells[Cell(X, R)] != EPlatformPart::None ||
					DecorationCells[Cell(X, R)] >= 0 || EdgeCells[Cell(X, R)] >= 0) { return false; }
			}
		}
		return true;
	}

	//---------------------- Autotile del terreno ----------------------

	void AutotileTerrain()
	{
		const FRandomStream RandVariants = Stream(EFramework2DProcGenStream::Variants);
		const bool bPlatformPieces = Biome.PlatformMiddle >= 0;
		for (int32 R = 0; R < H; ++R)
		{
			for (int32 X = 0; X < W; ++X)
			{
				const EPlatformPart Part = PlatformCells[Cell(X, R)];
				int32 Value = -1;
				if (HasRamp(X) && R == Fill[X])
				{
					Value = RampPiece(Slope[X]);
				}
				else if (Part != EPlatformPart::None && bPlatformPieces)
				{
					Value = PlatformPiece(Part);
				}
				else if (R < Fill[X] || Part != EPlatformPart::None || IslandCells[Cell(X, R)])
				{
					// Macizo, isla (o plataforma sin piezas propias): el 3x3 del terreno.
					Value = SolidPiece(X, R, RandVariants);
				}
				else if (HasBridgeAt(X, R))
				{
					Value = BridgePiece(BridgeCells[Cell(X, R)]);
				}
				TerrainCells[Cell(X, R)] = Value;
			}
		}
	}

	int32 SolidPiece(int32 X, int32 R, const FRandomStream& RandVariants) const
	{
		auto IsOccupied = [this](int32 Px, int32 Pr) { return IsTerrainOccupied(Px, Pr); };
		if (b5x5)
		{
			// Terreno 5x5: bordes de dos casillas de grosor. El interior admite variantes.
			int32 Row5 = 2;
			int32 Col5 = 2;
			// La pared de un escalon sigue con su pieza de lado hasta el suelo de abajo: la casilla de
			// arriba de ese suelo (aire encima) es casi toda hierba transparente y no la tapa.
			auto IsOccupiedSide = [this, X, R](int32 Px, int32 Pr)
			{
				if (!IsTerrainOccupied(Px, Pr)) { return false; }
				const bool bSideCell = Pr == R && Px != X;
				return !(bSideCell && !IsTerrainOccupied(Px, Pr + 1) && IsTerrainOccupied(X, R + 1));
			};
			Framework2DProcGenExposure5(IsOccupiedSide, X, R, Row5, Col5);
			if (Row5 <= 1 && Col5 == 2) { Col5 = SurfaceColumn(X); }
			const float Roll5 = RandVariants.FRand(); // siempre, haya variantes o no
			if (Row5 == 2 && Col5 == 2)
			{
				if (Roll5 < Settings.CenterVariantChance && Biome.CenterVariants.Num() > 0)
				{
					return Biome.CenterVariants[RandVariants.RandRange(0, Biome.CenterVariants.Num() - 1)];
				}
				// Mas adentro que las filas del 5x5 (a 4 o mas del aire por arriba): el interior profundo.
				if (Biome.GroundDeep >= 0 && IsTerrainOccupied(X, R + 3)) { return Biome.GroundDeep; }
			}
			return Framework2DProcGenPick5x5(Biome.Ground5, Row5, Col5);
		}
		int32 Row = 1;
		int32 Col = 1;
		Framework2DProcGenExposure(IsOccupied, X, R, Row, Col);
		if (Row != 1 || Col != 1)
		{
			return Framework2DProcGenPick3x3(Biome.Ground, Row, Col);
		}

		// Esquinas interiores: la primera diagonal libre (en este orden) cuya pieza existe. Si uno
		// de los dos vecinos que forman la esquina es una rampa no hay esquina: la hierba de la
		// rampa ya pasa por ahi (si no, saldria un pico de hierba bajo cada rampa).
		auto IsRampCell = [this](int32 Px, int32 Pr) { return Px >= 0 && Px < W && HasRamp(Px) && Pr == Fill[Px]; };
		auto Corner = [&](int32 Dx, int32 Dr)
		{
			return !IsOccupied(X + Dx, R + Dr) && !IsRampCell(X + Dx, R) && !IsRampCell(X, R + Dr);
		};
		// Centro: la tirada se hace SIEMPRE (haya variantes o esquina, o no) para que el resto no se mueva.
		const float Roll = RandVariants.FRand();
		const FFramework2DInnerCorners& Inner = Biome.InnerCorners;
		if (Inner.TopLeft >= 0 && Corner(-1, +1)) { return Inner.TopLeft; }
		if (Inner.TopRight >= 0 && Corner(+1, +1)) { return Inner.TopRight; }
		if (Inner.BottomLeft >= 0 && Corner(-1, -1)) { return Inner.BottomLeft; }
		if (Inner.BottomRight >= 0 && Corner(+1, -1)) { return Inner.BottomRight; }
		if (Roll < Settings.CenterVariantChance && Biome.CenterVariants.Num() > 0)
		{
			return Biome.CenterVariants[RandVariants.RandRange(0, Biome.CenterVariants.Num() - 1)];
		}
		return Biome.Ground.Center;
	}

	int32 RampPiece(EFramework2DProcGenSlope Kind) const
	{
		switch (Kind)
		{
		case EFramework2DProcGenSlope::Up:             return Biome.RampUp;
		case EFramework2DProcGenSlope::Down:           return Biome.RampDown;
		case EFramework2DProcGenSlope::GentleUpLow:    return Biome.GentleUpLow;
		case EFramework2DProcGenSlope::GentleUpHigh:   return Biome.GentleUpHigh;
		case EFramework2DProcGenSlope::GentleDownHigh: return Biome.GentleDownHigh;
		case EFramework2DProcGenSlope::GentleDownLow:  return Biome.GentleDownLow;
		default:                                       return -1;
		}
	}

	int32 PlatformPiece(EPlatformPart Part) const
	{
		const int32 Middle = Biome.PlatformMiddle;
		switch (Part)
		{
		case EPlatformPart::Left:  return Biome.PlatformLeft >= 0 ? Biome.PlatformLeft : Middle;
		case EPlatformPart::Right: return Biome.PlatformRight >= 0 ? Biome.PlatformRight : Middle;
		default:                   return Middle; // tramo o plataforma de una sola casilla
		}
	}

	//---------------------- Pie de pared ----------------------

	// Casilla de macizo normal (ni rampa, ni plataforma, ni isla) dentro del mapa.
	bool IsPlainSolid(int32 X, int32 R) const
	{
		return X >= 0 && X < W && R >= 0 && R < H && R < Fill[X] && PlatformCells[Cell(X, R)] == EPlatformPart::None && !IslandCells[Cell(X, R)];
	}

	// Con el 5x5: donde un suelo llega a la pared de un escalon, su hierba no se corta en recto
	// contra la pared (capa de bordes, salvo el pie, que es terreno):
	//  - pared estrecha (1 o 2 columnas, mismo suelo al otro lado): la hierba sigue de corrido por
	//    delante (sus dos filas) y el bulto queda detras;
	//  - sin piezas de pie de pared: la hierba acaba delante de la pared con el extremo del 5x5 (sus
	//    dos filas, redondeadas);
	//  - con piezas: la fila de arriba sigue por delante, la segunda entra en la pared con el pie y
	//    se remata en la columna siguiente (pie de dentro, con el extremo de la hierba encima).
	void PlaceWallFeet()
	{
		if (!b5x5) { return; }
		auto TipsAt = [this](int32 C) { return Framework2DProcGenPick5x5(Biome.Ground5, 0, SurfaceColumn(C)); };
		auto MatAt = [this](int32 C) { return Framework2DProcGenPick5x5(Biome.Ground5, 1, SurfaceColumn(C)); };
		auto SetEdge = [this](int32 X, int32 R, int32 Value)
		{
			if (Value < 0 || EdgeCells[Cell(X, R)] >= 0) { return false; }
			EdgeCells[Cell(X, R)] = Value;
			return true;
		};
		struct FInner { int32 X; int32 L; int32 Value; bool bFloorLeft; };
		TArray<FInner> Inners; // van al final: no pisan ningun pie
		for (int32 X = 0; X < W; ++X)
		{
			if (HasRamp(X)) { continue; }
			const int32 L = Fill[X] - 1; // fila de arriba del suelo
			if (L < 1) { continue; }
			for (const int32 Dir : { -1, +1 })
			{
				const int32 WX = X + Dir; // columna de la pared
				if (WX < 0 || WX >= W || Fill[WX] < L + 2) { continue; }
				if (!IsPlainSolid(WX, L) || !IsPlainSolid(WX, L - 1) || !IsPlainSolid(X, L - 1)) { continue; }
				const bool bFloorLeft = Dir > 0;

				// Pared estrecha (hasta 4 de ancho) o bulto de una fila (hasta 8) con el mismo suelo al otro
				// lado: dos remates se tocarian en medio. La pone una sola vez el lado izquierdo.
				int32 Span = 1;
				bool bLow = Fill[WX] == L + 2;
				while (Span < 9 && WX + Span * Dir >= 0 && WX + Span * Dir < W && Fill[WX + Span * Dir] >= L + 2)
				{
					bLow = bLow && Fill[WX + Span * Dir] == L + 2;
					++Span;
				}
				const int32 Beyond = WX + Span * Dir;
				if ((Span <= 4 || (bLow && Span <= 8)) && Beyond >= 0 && Beyond < W && !HasRamp(Beyond) && Fill[Beyond] == Fill[X])
				{
					if (!bFloorLeft) { continue; }
					for (int32 C = WX; C < Beyond; ++C)
					{
						if (!IsPlainSolid(C, L) || !IsPlainSolid(C, L - 1)) { continue; }
						SetEdge(C, L, TipsAt(C));
						SetEdge(C, L - 1, MatAt(C));
					}
					++Report.WallFeet;
					continue;
				}

				const int32 Foot = bFloorLeft ? Biome.WallFootLeft : Biome.WallFootRight;
				const int32 EndCol = bFloorLeft ? 4 : 0;
				if (Foot < 0)
				{
					SetEdge(WX, L, Biome.Ground5.At(0, EndCol));
					if (SetEdge(WX, L - 1, Biome.Ground5.At(1, EndCol))) { ++Report.WallFeet; }
					continue;
				}
				SetEdge(WX, L, TipsAt(WX));
				if (BlockCells[Cell(WX, L - 1)]) { continue; } // pilar de una columna: ya tiene el pie del otro lado
				TerrainCells[Cell(WX, L - 1)] = Foot;
				BlockCells[Cell(WX, L - 1)] = true;
				++Report.WallFeet;
				// El pie de dentro, solo dentro de la pared (si no, taparia su otro borde).
				const int32 Inner = bFloorLeft ? Biome.WallFootLeftInner : Biome.WallFootRightInner;
				const int32 IX = WX + Dir;
				if (Inner >= 0 && IX >= 0 && IX < W && Fill[IX] >= L + 2 && IsPlainSolid(IX, L) && IsPlainSolid(IX, L - 1) &&
					IsTerrainOccupied(IX + Dir, L) && IsTerrainOccupied(IX + Dir, L - 1))
				{
					Inners.Add({ IX, L, Inner, bFloorLeft });
				}
			}
		}
		for (const FInner& Entry : Inners)
		{
			const int32 Index = Cell(Entry.X, Entry.L - 1);
			if (BlockCells[Index]) { continue; }
			TerrainCells[Index] = Entry.Value;
			BlockCells[Index] = true;
			// La hierba de arriba sigue hasta aqui y se redondea (sin escalon contra el pie de dentro).
			SetEdge(Entry.X, Entry.L, Biome.Ground5.At(0, Entry.bFloorLeft ? 4 : 0));
		}
	}

	// Columna del 5x5 (1, 2 o 3) de las dos filas de arriba de la superficie en cada columna del mapa:
	// las tres del medio casan entre si, asi que se alternan. Cada una avanza 1 o 2 desde la de su
	// izquierda (nunca la repite) segun un hash de la semilla y la columna: no gasta tiradas.
	void BuildSurfaceColumns()
	{
		if (!b5x5) { return; }
		auto Hash = [this](int32 C) { return HashCombine((uint32)Settings.Seed * 2654435761u, (uint32)C * 40503u + 0x5F); };
		SurfaceCols.SetNumUninitialized(W);
		SurfaceCols[0] = (uint8)(1 + Hash(0) % 3u);
		for (int32 X = 1; X < W; ++X) { SurfaceCols[X] = (uint8)(1 + (SurfaceCols[X - 1] + (Hash(X) & 1u)) % 3); }
	}

	// Las dos filas de una columna usan la misma (fuera del mapa, la del borde).
	int32 SurfaceColumn(int32 X) const { return SurfaceCols[FMath::Clamp(X, 0, W - 1)]; }

	//---------------------- Fondo ----------------------

	void BuildBackground()
	{
		if (!Settings.bBackground || Biome.Background.Center < 0) { return; }

		// Hasta donde llega el fondo en cada columna (filas desde abajo).
		TArray<int32> BgTop;
		BgTop.SetNumZeroed(W);
		const int32 Rise = FMath::Max(0, Settings.BackgroundRise);
		if (Rise == 0)
		{
			// Solo detras del terreno: se ve al picar.
			for (int32 X = 0; X < W; ++X) { BgTop[X] = Fill[X]; }
		}
		else
		{
			const FRandomStream RandBackground = Stream(EFramework2DProcGenStream::Background);
			int32 Noise = 0;
			for (int32 X = 0; X < W; ++X)
			{
				// Ruido suave: un paseo en [-1, 1] que cambia como mucho cada 3 columnas.
				if (X % 3 == 0) { Noise = FMath::Clamp(Noise + RandBackground.RandRange(-1, 1), -1, 1); }

				// Colinas: media movil (ventana de 7) del suelo; la rampa cuenta como un tile mas.
				int32 Sum = 0;
				int32 Samples = 0;
				for (int32 I = FMath::Max(0, X - 3); I <= FMath::Min(W - 1, X + 3); ++I)
				{
					Sum += FMath::Max(GroundHeight(I), WaterTop[I] + Drop) + (HasRamp(I) ? 1 : 0);
					++Samples;
				}
				const int32 Average = FMath::RoundToInt((float)Sum / (float)FMath::Max(1, Samples));
				BgTop[X] = FMath::Max(FMath::Max(Fill[X], FMath::Min(H, WaterTop[X] + Drop + 1)), FMath::Clamp(Average + Rise + Noise, 1, H - 1));
			}
			// Sin picos ni muescas de una sola columna (el redondeo y el ruido los crean): se ven como
			// chimeneas en las colinas.
			for (int32 Pass = 0; Pass < 2; ++Pass)
			{
				for (int32 X = 1; X + 1 < W; ++X)
				{
					const int32 Left = BgTop[X - 1];
					const int32 Right = BgTop[X + 1];
					if (BgTop[X] > FMath::Max(Left, Right)) { BgTop[X] = FMath::Max(Fill[X], FMath::Max(Left, Right)); }
					else if (BgTop[X] < FMath::Min(Left, Right)) { BgTop[X] = FMath::Min(Left, Right); }
				}
				for (int32 X = 1; X + 2 < W; ++X)
				{
					if (BgTop[X] != BgTop[X + 1]) { continue; }
					const int32 Left = BgTop[X - 1];
					const int32 Right = BgTop[X + 2];
					const int32 To = BgTop[X] > FMath::Max(Left, Right) ? FMath::Max(Left, Right) : (BgTop[X] < FMath::Min(Left, Right) ? FMath::Min(Left, Right) : BgTop[X]);
					BgTop[X] = FMath::Max(Fill[X], To);
					BgTop[X + 1] = FMath::Max(Fill[X + 1], To);
				}
			}
		}

		// Con colinas, bajo un puente el fondo llega a las tablas (si no, entre las tablas y el agua
		// se veria una rendija de cielo).
		for (int32 X = 0; X < W && Rise > 0; ++X)
		{
			if (BridgeCap[X] > 0) { BgTop[X] = FMath::Max(BgTop[X], FMath::Min(H, BridgeCap[X] + 1)); }
		}

		// Mismo autotile que el terreno (sin esquinas interiores ni variantes). Fuera del mapa, igual.
		auto IsOccupied = [this, &BgTop](int32 Px, int32 Pr) -> bool
		{
			if (Pr < 0) { return true; }
			if (Pr >= H) { return false; }
			return Pr < BgTop[FMath::Clamp(Px, 0, W - 1)];
		};
		for (int32 R = 0; R < H; ++R)
		{
			for (int32 X = 0; X < W; ++X)
			{
				if (R >= BgTop[X]) { continue; }
				int32 Row = 1;
				int32 Col = 1;
				Framework2DProcGenExposure(IsOccupied, X, R, Row, Col);
				BackgroundCells[Cell(X, R)] = Framework2DProcGenPick3x3(Biome.Background, Row, Col);
			}
		}
	}

	//---------------------- Decoracion ----------------------

	void PlaceDecoration()
	{
		const FRandomStream RandDecoration = Stream(EFramework2DProcGenStream::Decoration);
		auto IsFree = [this](int32 Px, int32 Pr)
		{
			return Pr >= 0 && Pr < H && !IsTerrainOccupied(Px, Pr) && !IsWet(Px, Pr) && !HasBridgeAt(Px, Pr);
		};

		// Candidatas en orden de X (y de abajo arriba dentro de cada columna).
		// Suelo: la casilla sobre el macizo (sin rampa ni muro, ni junto a los postes de un puente:
		// un adorno los atravesaria) y la de encima de cada plataforma.
		// Techo: la de debajo de cada plataforma.
		auto IsNearBridgeEnd = [this](int32 X)
		{
			return BridgeBank[X] || (X > 0 && BridgeBank[X - 1]) || (X + 1 < W && BridgeBank[X + 1]);
		};
		TArray<FIntPoint> GroundSpots;
		TArray<FIntPoint> CeilingSpots;
		for (int32 X = 0; X < W; ++X)
		{
			if (!HasRamp(X) && !Wall[X] && Fill[X] >= 1 && Fill[X] < H && IsFree(X, Fill[X]) && !IsNearBridgeEnd(X))
			{
				GroundSpots.Add(FIntPoint(X, Fill[X]));
			}
			for (int32 R = 0; R < H; ++R)
			{
				if (PlatformCells[Cell(X, R)] == EPlatformPart::None && !IslandCells[Cell(X, R)]) { continue; }
				if (IsFree(X, R + 1)) { GroundSpots.Add(FIntPoint(X, R + 1)); }
				if (R - 1 > Fill[X] && IsFree(X, R - 1)) { CeilingSpots.Add(FIntPoint(X, R - 1)); }
			}
		}
		PlaceDecorationList(GroundSpots, EFramework2DDecorPlacement::Ground, RandDecoration);
		PlaceDecorationList(CeilingSpots, EFramework2DDecorPlacement::Ceiling, RandDecoration);
	}

	// Reparte los adornos de un sitio (suelo o techo) por sus casillas candidatas (FIntPoint: X, R).
	void PlaceDecorationList(const TArray<FIntPoint>& Spots, EFramework2DDecorPlacement Placement, const FRandomStream& RandDecoration)
	{
		TArray<FFramework2DBiomeDecoration> Entries;
		for (const FFramework2DBiomeDecoration& Deco : Biome.Decorations)
		{
			if (Deco.Placement == Placement) { Entries.Add(Deco); }
		}
		const float TotalWeight = Framework2DProcGenTotalWeight(Entries);

		const int32 Spacing = FMath::Max(0, Settings.DecorationSpacing);
		TMap<int32, int32> LastXByRow; // ultimo adorno de este sitio en cada fila
		for (const FIntPoint& Spot : Spots)
		{
			// Una tirada por candidata, SIEMPRE (haya adornos o no, quepa o no).
			const float Roll = RandDecoration.FRand();
			if (Roll >= Settings.DecorationDensity || Entries.Num() == 0) { continue; }
			if (const int32* LastX = LastXByRow.Find(Spot.Y))
			{
				if (Spot.X - *LastX - 1 < Spacing) { continue; }
			}
			const float Pick = RandDecoration.FRand() * TotalWeight;
			DecorationCells[Cell(Spot.X, Spot.Y)] = Framework2DProcGenPickByWeight(Entries, Pick).Value;
			LastXByRow.Add(Spot.Y, Spot.X);
			++Report.Decorations;
		}
	}

	//---------------------- Bordes naturales ----------------------

	// Encima de CADA casilla de macizo con aire encima (el borde de arriba) va el remate de arriba
	// y debajo de cada una con aire debajo, el de abajo (islas, plataformas, salientes). Las rampas
	// no llevan remate: su diagonal ya es borde.
	void PlaceEdges()
	{
		if (Biome.EdgeTop < 0 && Biome.EdgeBottom < 0) { return; }
		auto IsSolid = [this](int32 X, int32 R)
		{
			return X >= 0 && X < W && R >= 0 && R < H && IsTerrainOccupied(X, R) && !(HasRamp(X) && R == Fill[X]);
		};
		auto IsOpen = [this](int32 X, int32 R)
		{
			return R >= 0 && R < H && !IsTerrainOccupied(X, R) && !IsWet(X, R) && !HasBridgeAt(X, R);
		};
		for (int32 R = 0; R < H; ++R)
		{
			for (int32 X = 0; X < W; ++X)
			{
				if (!IsSolid(X, R)) { continue; }
				if (Biome.EdgeTop >= 0 && IsOpen(X, R + 1) && EdgeCells[Cell(X, R + 1)] < 0) { EdgeCells[Cell(X, R + 1)] = Biome.EdgeTop; }
				if (Biome.EdgeBottom >= 0 && IsOpen(X, R - 1) && EdgeCells[Cell(X, R - 1)] < 0) { EdgeCells[Cell(X, R - 1)] = Biome.EdgeBottom; }
			}
		}
	}

	// Remate encima de cada casilla de plataforma (solo si el bioma tiene piezas de plataforma).
	void PlacePlatformCaps()
	{
		if (Biome.PlatformMiddle < 0) { return; }
		const int32 CapMiddle = Biome.PlatformCapMiddle;
		const int32 CapLeft = Biome.PlatformCapLeft >= 0 ? Biome.PlatformCapLeft : CapMiddle;
		const int32 CapRight = Biome.PlatformCapRight >= 0 ? Biome.PlatformCapRight : CapMiddle;
		if (CapLeft < 0 && CapMiddle < 0 && CapRight < 0) { return; }
		for (int32 R = 0; R + 1 < H; ++R)
		{
			for (int32 X = 0; X < W; ++X)
			{
				const EPlatformPart Part = PlatformCells[Cell(X, R)];
				if (Part == EPlatformPart::None || IsTerrainOccupied(X, R + 1) || HasWaterAt(X, R + 1)) { continue; }
				const int32 Cap = Part == EPlatformPart::Left ? CapLeft : (Part == EPlatformPart::Right ? CapRight : CapMiddle);
				if (Cap >= 0) { EdgeCells[Cell(X, R + 1)] = Cap; }
			}
		}
	}

	//---------------------- Objetos grandes ----------------------

	// Recorre el suelo de izquierda a derecha: donde cabe el apoyo de un objeto (columnas llanas a
	// la misma altura, sin agua, rampas, puentes ni cascadas) y sale la tirada, lo pone.
	void PlaceProps()
	{
		if (PropInfos.Num() == 0) { return; }
		const FRandomStream RandProps = Stream(EFramework2DProcGenStream::Props);
		const float TotalWeight = Framework2DProcGenTotalWeight(PropInfos);
		const int32 Spacing = FMath::Max(0, Settings.PropSpacing);
		constexpr int32 SameSpacing = 10;     // el mismo objeto, como poco a estas columnas del anterior
		TMap<int32, TPair<int32, bool>> LastById; // donde salio por ultima vez cada objeto y si volteado

		int32 X = 0;
		while (X < W)
		{
			// Tres tiradas por columna candidata, SIEMPRE.
			const float Roll = RandProps.FRand();
			const float Pick = RandProps.FRand() * TotalWeight;
			const float FlipRoll = RandProps.FRand();
			if (Roll >= Settings.PropDensity) { ++X; continue; }

			const FPropInfo* Info = &Framework2DProcGenPickByWeight(PropInfos, Pick);
			const TPair<int32, bool>* Last = LastById.Find(Info->Id);
			if (Last && X - Last->Key < SameSpacing) { ++X; continue; }
			const int32 Foot = FMath::Max(1, Info->Footprint);
			const int32 GroundRow = Fill[X];
			// Todo el ancho de la imagen (centrada en el apoyo) sobre suelo a esa altura o mas: nada
			// cuelga sobre un escalon o un lago. Los muy hundidos (sus lados rectos los tapa el suelo de
			// delante), una columna mas a cada lado. Sin puentes encima ni al lado.
			const float CenterX = (float)X + (float)Foot * 0.5f;
			const int32 Pad = Info->Sink > TilePixels / 2 ? 1 : 0;
			const int32 ArtX0 = FMath::FloorToInt(CenterX - (float)Info->ArtWidth * 0.5f) - Pad;
			const int32 ArtX1 = FMath::CeilToInt(CenterX + (float)Info->ArtWidth * 0.5f) + Pad; // exclusivo
			bool bFits = X + Foot <= W && ArtX0 >= 0 && ArtX1 <= W && GroundRow >= 1 && GroundRow + Info->HeightTiles <= H;
			const int32 ArtTop = FMath::Min(H - 1, GroundRow + Info->HeightTiles); // y una fila de margen
			for (int32 C = ArtX0; C < ArtX1 && bFits; ++C)
			{
				bFits = Fill[C] >= GroundRow && !IsWet(C, GroundRow) && BridgeCap[C] == 0 && !BridgeBank[C];
				for (int32 R = GroundRow; R <= ArtTop && bFits; ++R)
				{
					bFits = PlatformCells[Cell(C, R)] == EPlatformPart::None && !IslandCells[Cell(C, R)] && !HasBridgeAt(C, R);
				}
			}
			for (int32 C = X; C < X + Foot && bFits; ++C)
			{
				bFits = Fill[C] == GroundRow && !HasRamp(C) && !Wall[C] && !HasBridgeAt(C, GroundRow) &&
					PlatformCells[Cell(C, GroundRow)] == EPlatformPart::None && !IslandCells[Cell(C, GroundRow)];
			}
			if (!bFits) { ++X; continue; }

			FPlacedProp Placed;
			Placed.Info = Info;
			Placed.X = X;
			Placed.R = GroundRow;
			// Si el mismo objeto sale cerca, al reves que el anterior: no parecen copias.
			Placed.bFlip = Info->bRandomFlip && ((Last && X - Last->Key < 2 * SameSpacing) ? !Last->Value : FlipRoll < 0.5f);
			PlacedProps.Add(Placed);
			LastById.Add(Info->Id, TPair<int32, bool>(X, Placed.bFlip));
			++Report.Props;
			X += Foot + Spacing;
		}
	}

	//---------------------- Salida ----------------------

	// Pasa las rejillas a filas del mapa (Y = 0 arriba) y copia el relieve y el informe.
	void WriteOutput(FFramework2DProcGenOutput& Out) const
	{
		const int32 Num = W * H;
		Out.Terrain.Init(-1, Num);
		Out.Background.Init(-1, Num);
		Out.Water.Init(-1, Num);
		Out.Decoration.Init(-1, Num);
		Out.Edges.Init(-1, Num);
		Out.Behind.Init(-1, Num);
		for (int32 R = 0; R < H; ++R)
		{
			const int32 Y = H - 1 - R;
			for (int32 X = 0; X < W; ++X)
			{
				const int32 From = Cell(X, R);
				const int32 To = Y * W + X;
				Out.Terrain[To] = TerrainCells[From];
				Out.Background[To] = BackgroundCells[From];
				Out.Water[To] = WaterCells[From];
				Out.Decoration[To] = DecorationCells[From];
				Out.Edges[To] = EdgeCells[From];
				Out.Behind[To] = BehindCells[From];
			}
		}
		Out.FillHeight = Fill;
		Out.Slope.SetNumZeroed(W);
		for (int32 X = 0; X < W; ++X) { Out.Slope[X] = (uint8)Slope[X]; }
		Out.WaterTop = WaterTop;
		Out.Report = Report;

		// Objetos grandes: centro de su apoyo y fila del mapa de la casilla en la que estan.
		const FName BehindName = Layers.Behind;
		const FName FrontName = Layers.Decoration;
		for (const FPlacedProp& Placed : PlacedProps)
		{
			FFramework2DPropInstance Instance;
			Instance.PropId = Placed.Info->Id;
			Instance.Layer = Placed.Info->Depth == EFramework2DPropDepth::Behind ? BehindName : FrontName;
			Instance.X = (float)Placed.X + (float)Placed.Info->Footprint * 0.5f;
			Instance.Y = H - 1 - Placed.R;
			Instance.SinkPixels = Placed.Info->Sink;
			Instance.bFlip = Placed.bFlip;
			Instance.bSnapToGround = true; // sobre la hierba de verdad (no sobre el borde del tile)
			Out.Props.Add(Instance);
		}
		Out.Backdrops = Biome.Backdrops;
	}
};

// =====================================================================
//  API
// =====================================================================

bool UFramework2DProcGenLibrary::IsUsablePiece(const UFramework2DTileSet* Set, int32 Value)
{
	if (Value < 0) { return false; }
	return !Set || Set->IsValidValue(Value);
}

FText UFramework2DProcGenLibrary::GetBiomeProblem(const UFramework2DTileSet* Set, const FFramework2DBiome& Biome)
{
	// Solo el centro del 3x3 (o el del 5x5) es obligatorio: lo demas tiene reserva o es opcional.
	if (Biome.Ground5.At(2, 2) >= 0 && IsUsablePiece(Set, Biome.Ground5.At(2, 2)))
	{
		return FText::GetEmpty();
	}
	if (Biome.Ground.Center < 0)
	{
		return LOCTEXT("ProblemNoCenter", "The 3×3 terrain center is missing: it is the only required piece of the biome.");
	}
	if (!IsUsablePiece(Set, Biome.Ground.Center))
	{
		return LOCTEXT("ProblemCenterGone", "The 3×3 terrain center no longer exists in the Tile Set: choose another piece.");
	}
	return FText::GetEmpty();
}

bool UFramework2DProcGenLibrary::Generate(const UFramework2DTileSet* Set, const FFramework2DBiome& Biome, const FFramework2DProcGenSettings& Settings,
	int32 Width, int32 Height, FFramework2DProcGenOutput& Out)
{
	Out = FFramework2DProcGenOutput();
	Out.Width = Width;
	Out.Height = Height;

	if (Width < 4 || Height < 4)
	{
		Out.Report.Message = FString::Printf(TEXT("The map is too small to generate a level: it is %d×%d tiles and needs at least 4×4."), Width, Height);
		return false;
	}
	if ((int64)Width * (int64)Height > Framework2DProcGenMaxCells)
	{
		Out.Report.Message = FString::Printf(TEXT("The map is too large to generate a level (%d×%d tiles)."), Width, Height);
		return false;
	}
	const FText Problem = GetBiomeProblem(Set, Biome);
	if (!Problem.IsEmpty())
	{
		Out.Report.Message = Problem.ToString();
		return false;
	}

	const FFramework2DBiome UsableBiome = Framework2DProcGenUsableBiome(Set, Biome);
	FFramework2DProcGenBuilder Builder(UsableBiome, Settings, Width, Height);
	if (Set)
	{
		// Medidas de cada objeto grande en tiles (de su imagen).
		const int32 TW = FMath::Max(1, Set->TileWidth);
		const int32 TH = FMath::Max(1, Set->TileHeight);
		Builder.TilePixels = TH;
		auto MakeInfo = [Set, TW, TH](const FFramework2DBiomeProp& Entry, FFramework2DProcGenBuilder::FPropInfo& Info)
		{
			const FFramework2DPropDef* Def = Set->FindPropById(Entry.PropId);
			int32 PW = 0, PH = 0;
			if (!Def || !Set->GetPropSize(Entry.PropId, PW, PH)) { return false; }
			Info.Id = Entry.PropId;
			Info.ArtWidth = FMath::Max(1, FMath::DivideAndRoundUp(PW, TW));
			Info.Footprint = Def->FootprintTiles > 0 ? FMath::Min(Def->FootprintTiles, Info.ArtWidth) : Info.ArtWidth;
			Info.HeightTiles = FMath::Max(1, FMath::DivideAndRoundUp(PH, TH));
			Info.Weight = Entry.Weight;
			Info.Depth = Entry.Depth;
			Info.Sink = FMath::Clamp(Entry.SinkPixels, 0, 64);
			Info.bRandomFlip = Entry.bRandomFlip;
			return true;
		};
		for (const FFramework2DBiomeProp& Entry : UsableBiome.Props)
		{
			FFramework2DProcGenBuilder::FPropInfo Info;
			if (MakeInfo(Entry, Info)) { Builder.PropInfos.Add(Info); }
		}
	}
	Builder.Run();
	Builder.WriteOutput(Out);
	return Out.Report.bSuccess;
}

void UFramework2DProcGenLibrary::ApplyToMap(UFramework2DTileMapAsset* Map, const FFramework2DProcGenSettings& Settings, const FFramework2DProcGenOutput& Out)
{
	if (!Map) { return; }
	const bool bSameSize = Out.Width == Map->Width && Out.Height == Map->Height && Out.Width > 0 && Out.Height > 0;
	const int32 Num = bSameSize ? Out.Width * Out.Height : 0;
	auto IsGridOk = [Num](const TArray<int32>& Grid) { return Grid.Num() == 0 || Grid.Num() == Num; };
	if (!bSameSize || Out.Terrain.Num() != Num || !IsGridOk(Out.Background) || !IsGridOk(Out.Water) || !IsGridOk(Out.Decoration) || !IsGridOk(Out.Edges) || !IsGridOk(Out.Behind))
	{
		UE_LOG(LogTemp, Warning, TEXT("[Framework2DTerrain] La generacion (%d x %d) no encaja con el Tile Map '%s' (%d x %d): no se cambia nada."),
			Out.Width, Out.Height, *Map->GetName(), Map->Width, Map->Height);
		return;
	}

	const FFramework2DProcGenLayerNames Names(Settings);
	const FName TerrainName = Names.Terrain;
	const FName BackgroundName = Names.Background;
	const FName DecorationName = Names.Decoration;
	const FName WaterName = Names.Water;
	const FName BehindName = Names.Behind;
	const FName EdgeName = Names.Edges;
	bool bBehindProps = false;
	bool bFrontProps = false;
	for (const FFramework2DPropInstance& Instance : Out.Props)
	{
		bBehindProps |= Instance.Layer == BehindName;
		bFrontProps |= Instance.Layer == DecorationName;
	}

	// Capa nueva en la posicion At. Las banderas solo se ponen al CREARLA (las de una capa que ya
	// existe son cosa del usuario).
	auto InsertLayer = [Map](int32 At, FName LayerName, bool bIsBackground, bool bLayerCollides, bool bLayerBreakable)
	{
		FFramework2DTileLayer NewLayer;
		NewLayer.Name = LayerName;
		NewLayer.bBackground = bIsBackground;
		NewLayer.bCollides = bLayerCollides;
		NewLayer.bBreakable = bLayerBreakable;
		const int32 Index = FMath::Clamp(At, 0, Map->Layers.Num());
		Map->Layers.Insert(MoveTemp(NewLayer), Index);
		Map->EnsureLayer(Index);
	};

	// Solo se crean las capas que hacen falta: Fondo justo detras del Terreno, Decoracion justo
	// delante y Agua delante de la Decoracion (o del Terreno).
	if (Map->FindLayerByName(TerrainName) == INDEX_NONE)
	{
		InsertLayer(Map->Layers.Num(), TerrainName, false, true, true);
	}
	if (Map->FindLayerByName(BackgroundName) == INDEX_NONE && Framework2DProcGenHasAny(Out.Background))
	{
		InsertLayer(Map->FindLayerByName(TerrainName), BackgroundName, true, true, true);
	}
	if (Map->FindLayerByName(BehindName) == INDEX_NONE && (bBehindProps || Framework2DProcGenHasAny(Out.Behind)))
	{
		// Objetos de detras: entre el fondo y el terreno, ni chocan ni se rompen.
		InsertLayer(Map->FindLayerByName(TerrainName), BehindName, false, false, false);
	}
	if (Map->FindLayerByName(DecorationName) == INDEX_NONE && (Framework2DProcGenHasAny(Out.Decoration) || bFrontProps))
	{
		InsertLayer(Map->FindLayerByName(TerrainName) + 1, DecorationName, false, false, true);
	}
	if (Map->FindLayerByName(EdgeName) == INDEX_NONE && Framework2DProcGenHasAny(Out.Edges))
	{
		// Bordes naturales: justo delante del terreno (detras de la decoracion).
		InsertLayer(Map->FindLayerByName(TerrainName) + 1, EdgeName, false, false, true);
	}
	if (Map->FindLayerByName(WaterName) == INDEX_NONE && Framework2DProcGenHasAny(Out.Water))
	{
		const int32 Anchor = FMath::Max(Map->FindLayerByName(TerrainName), Map->FindLayerByName(DecorationName));
		InsertLayer(Anchor + 1, WaterName, false, false, false);
	}

	// Se REEMPLAZA el contenido entero de las cuatro capas (las que existan). Primero se vacian
	// todas y luego se escriben de atras a delante: si la receta repite un nombre, las partes
	// comparten capa sin borrarse entre si.
	const int32 TargetLayers[6] =
	{
		Map->FindLayerByName(BackgroundName),
		Map->FindLayerByName(BehindName),
		Map->FindLayerByName(TerrainName),
		Map->FindLayerByName(EdgeName),
		Map->FindLayerByName(DecorationName),
		Map->FindLayerByName(WaterName)
	};
	// La capa de detras lleva el agua de detras (celdas) y los objetos grandes de detras (aparte).
	const TArray<int32>* Sources[6] = { &Out.Background, &Out.Behind, &Out.Terrain, &Out.Edges, &Out.Decoration, &Out.Water };
	for (const int32 LayerIndex : TargetLayers)
	{
		if (LayerIndex == INDEX_NONE) { continue; }
		Map->EnsureLayer(LayerIndex);
		Map->Layers[LayerIndex].Tiles.Init(-1, Num);
	}
	for (int32 Part = 0; Part < 6; ++Part)
	{
		if (TargetLayers[Part] == INDEX_NONE) { continue; }
		TArray<int32>& Tiles = Map->Layers[TargetLayers[Part]].Tiles;
		const TArray<int32>& Source = *Sources[Part];
		for (int32 I = 0; I < Source.Num(); ++I)
		{
			if (Source[I] >= 0) { Tiles[I] = Source[I]; }
		}
	}

	// La colision pintada era del nivel anterior.
	Map->CollisionOverrides.Reset();

	// Objetos grandes: fuera los de las capas que se generan y dentro los nuevos.
	const FName GeneratedLayers[6] = { BackgroundName, BehindName, TerrainName, EdgeName, DecorationName, WaterName };
	Map->PropInstances.RemoveAll([&GeneratedLayers](const FFramework2DPropInstance& Instance)
	{
		for (const FName& Name : GeneratedLayers) { if (Instance.Layer == Name) { return true; } }
		return false;
	});
	Map->PropInstances.Append(Out.Props);

	// Fondos parallax: los del bioma (si tiene; si no, se quedan los del mapa).
	if (Out.Backdrops.Num() > 0) { Map->Backdrops = Out.Backdrops; }
}

FFramework2DProcGenReport UFramework2DProcGenLibrary::GenerateMap(UFramework2DTileMapAsset* Map)
{
	return GenerateMapWithSettings(Map, Map ? Map->ProcGen : FFramework2DProcGenSettings());
}

FFramework2DProcGenReport UFramework2DProcGenLibrary::GenerateMapWithSettings(UFramework2DTileMapAsset* Map, const FFramework2DProcGenSettings& Settings)
{
	FFramework2DProcGenReport Report;
	if (!Map)
	{
		Report.Message = LOCTEXT("NoTileMap", "There is no Tile Map to generate into.").ToString();
		return Report;
	}
	const UFramework2DTileSet* Set = Map->TileSet.Get();
	if (!Set)
	{
		Report.Message = LOCTEXT("NoTileSet", "The Tile Map has no Tile Set: assign one.").ToString();
		return Report;
	}
	const FFramework2DBiome* Biome = Set->ResolveBiome(Settings.BiomeId);
	if (!Biome)
	{
		Report.Message = LOCTEXT("NoBiome", "The Tile Set has no biome: create one in the «Generate» tab.").ToString();
		return Report;
	}

	FFramework2DProcGenOutput Out;
	if (Generate(Set, *Biome, Settings, Map->Width, Map->Height, Out))
	{
		ApplyToMap(Map, Settings, Out);
		// Fuera del editor o en una copia transitoria no hace nada.
		Map->MarkPackageDirty();
	}
	return Out.Report;
}

#undef LOCTEXT_NAMESPACE
