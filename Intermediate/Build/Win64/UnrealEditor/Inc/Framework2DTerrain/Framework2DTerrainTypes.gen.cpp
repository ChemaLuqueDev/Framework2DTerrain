// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Framework2DTerrain/Public/Framework2DTerrainTypes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFramework2DTerrainTypes() {}
// Cross Module References
	FRAMEWORK2DTERRAIN_API UScriptStruct* Z_Construct_UScriptStruct_FFramework2DMaterial();
	UPackage* Z_Construct_UPackage__Script_Framework2DTerrain();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FColor();
	FRAMEWORK2DTERRAIN_API UScriptStruct* Z_Construct_UScriptStruct_FFramework2DMaterialAmount();
	FRAMEWORK2DTERRAIN_API UScriptStruct* Z_Construct_UScriptStruct_FFramework2DDigResult();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	FRAMEWORK2DTERRAIN_API UEnum* Z_Construct_UEnum_Framework2DTerrain_EFramework2DDebrisMode();
	FRAMEWORK2DTERRAIN_API UEnum* Z_Construct_UEnum_Framework2DTerrain_EFramework2DCollisionShape();
// End Cross Module References
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_Framework2DMaterial;
class UScriptStruct* FFramework2DMaterial::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_Framework2DMaterial.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_Framework2DMaterial.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FFramework2DMaterial, Z_Construct_UPackage__Script_Framework2DTerrain(), TEXT("Framework2DMaterial"));
	}
	return Z_Registration_Info_UScriptStruct_Framework2DMaterial.OuterSingleton;
}
template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<FFramework2DMaterial>()
{
	return FFramework2DMaterial::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FFramework2DMaterial_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[];
#endif
		static const UECodeGen_Private::FNamePropertyParams NewProp_Name;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Color_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Color;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ColorVariance_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_ColorVariance;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bCollides_MetaData[];
#endif
		static void NewProp_bCollides_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bCollides;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Hardness_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Hardness;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bIndestructible_MetaData[];
#endif
		static void NewProp_bIndestructible_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bIndestructible;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bCollectable_MetaData[];
#endif
		static void NewProp_bCollectable_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bCollectable;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bDrawEdge_MetaData[];
#endif
		static void NewProp_bDrawEdge_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bDrawEdge;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * Un MATERIAL de terreno (tierra, piedra, madera...). Se definen en el TileSet y cada tile\n * dice de que material es. Decide como se rompe, si colisiona y si se puede recoger.\n */" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainTypes.h" },
		{ "ToolTip", "Un MATERIAL de terreno (tierra, piedra, madera...). Se definen en el TileSet y cada tile\ndice de que material es. Decide como se rompe, si colisiona y si se puede recoger." },
	};
#endif
	void* Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFramework2DMaterial>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_Name_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Nombre con el que lo eliges en los tiles y lo usas desde Blueprint (\"Dirt\", \"Stone\"...).\n" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainTypes.h" },
		{ "ToolTip", "Nombre con el que lo eliges en los tiles y lo usas desde Blueprint (\"Dirt\", \"Stone\"...)." },
	};
#endif
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DMaterial, Name), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_Name_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_Name_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_Color_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Color de las celdas que no tienen dibujo (por ejemplo las que coloca el jugador si el\n// material no tiene tile de relleno). Las celdas horneadas usan el dibujo del tile.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainTypes.h" },
		{ "ToolTip", "Color de las celdas que no tienen dibujo (por ejemplo las que coloca el jugador si el\nmaterial no tiene tile de relleno). Las celdas horneadas usan el dibujo del tile." },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_Color = { "Color", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DMaterial, Color), Z_Construct_UScriptStruct_FColor, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_Color_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_Color_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_ColorVariance_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "80" },
		{ "ClampMin", "0" },
		{ "Comment", "// Variacion de color por celda para que el relleno sin dibujo no se vea plano. 0 = plano.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainTypes.h" },
		{ "ToolTip", "Variacion de color por celda para que el relleno sin dibujo no se vea plano. 0 = plano." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_ColorVariance = { "ColorVariance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DMaterial, ColorVariance), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_ColorVariance_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_ColorVariance_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_bCollides_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Si true, el personaje choca con el. False para decoracion (hierba, plantas...).\n" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainTypes.h" },
		{ "ToolTip", "Si true, el personaje choca con el. False para decoracion (hierba, plantas...)." },
	};
#endif
	void Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_bCollides_SetBit(void* Obj)
	{
		((FFramework2DMaterial*)Obj)->bCollides = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_bCollides = { "bCollides", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FFramework2DMaterial), &Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_bCollides_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_bCollides_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_bCollides_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_Hardness_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "255" },
		{ "ClampMin", "0" },
		{ "Comment", "// Dano que necesita una celda para romperse al picar (MineAt / varita / Explode).\n// 0 o 1 = se rompe al primer golpe. 255 = durisimo.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainTypes.h" },
		{ "ToolTip", "Dano que necesita una celda para romperse al picar (MineAt / varita / Explode).\n0 o 1 = se rompe al primer golpe. 255 = durisimo." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_Hardness = { "Hardness", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DMaterial, Hardness), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_Hardness_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_Hardness_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_bIndestructible_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Si true, nada lo rompe (ni picar, ni Dig, ni explosiones). Bordes del nivel.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainTypes.h" },
		{ "ToolTip", "Si true, nada lo rompe (ni picar, ni Dig, ni explosiones). Bordes del nivel." },
	};
#endif
	void Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_bIndestructible_SetBit(void* Obj)
	{
		((FFramework2DMaterial*)Obj)->bIndestructible = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_bIndestructible = { "bIndestructible", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FFramework2DMaterial), &Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_bIndestructible_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_bIndestructible_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_bIndestructible_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_bCollectable_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Si true, lo picado va al inventario de quien pica (y luego se puede colocar).\n" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainTypes.h" },
		{ "ToolTip", "Si true, lo picado va al inventario de quien pica (y luego se puede colocar)." },
	};
#endif
	void Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_bCollectable_SetBit(void* Obj)
	{
		((FFramework2DMaterial*)Obj)->bCollectable = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_bCollectable = { "bCollectable", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FFramework2DMaterial), &Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_bCollectable_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_bCollectable_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_bCollectable_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_bDrawEdge_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Si true, sus celdas dibujan el borde oscuro donde tocan aire (el corte del agujero).\n" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainTypes.h" },
		{ "ToolTip", "Si true, sus celdas dibujan el borde oscuro donde tocan aire (el corte del agujero)." },
	};
#endif
	void Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_bDrawEdge_SetBit(void* Obj)
	{
		((FFramework2DMaterial*)Obj)->bDrawEdge = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_bDrawEdge = { "bDrawEdge", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FFramework2DMaterial), &Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_bDrawEdge_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_bDrawEdge_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_bDrawEdge_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_Name,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_Color,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_ColorVariance,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_bCollides,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_Hardness,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_bIndestructible,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_bCollectable,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewProp_bDrawEdge,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_Framework2DTerrain,
		nullptr,
		&NewStructOps,
		"Framework2DMaterial",
		sizeof(FFramework2DMaterial),
		alignof(FFramework2DMaterial),
		Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FFramework2DMaterial()
	{
		if (!Z_Registration_Info_UScriptStruct_Framework2DMaterial.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_Framework2DMaterial.InnerSingleton, Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_Framework2DMaterial.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_Framework2DMaterialAmount;
class UScriptStruct* FFramework2DMaterialAmount::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_Framework2DMaterialAmount.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_Framework2DMaterialAmount.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FFramework2DMaterialAmount, Z_Construct_UPackage__Script_Framework2DTerrain(), TEXT("Framework2DMaterialAmount"));
	}
	return Z_Registration_Info_UScriptStruct_Framework2DMaterialAmount.OuterSingleton;
}
template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<FFramework2DMaterialAmount>()
{
	return FFramework2DMaterialAmount::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FFramework2DMaterialAmount_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Material_MetaData[];
#endif
		static const UECodeGen_Private::FNamePropertyParams NewProp_Material;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Count_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Count;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DMaterialAmount_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/** Cuanto se ha recogido de UN material (fila del resultado de picar). */" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainTypes.h" },
		{ "ToolTip", "Cuanto se ha recogido de UN material (fila del resultado de picar)." },
	};
#endif
	void* Z_Construct_UScriptStruct_FFramework2DMaterialAmount_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFramework2DMaterialAmount>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DMaterialAmount_Statics::NewProp_Material_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainTypes.h" },
	};
#endif
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FFramework2DMaterialAmount_Statics::NewProp_Material = { "Material", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DMaterialAmount, Material), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DMaterialAmount_Statics::NewProp_Material_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DMaterialAmount_Statics::NewProp_Material_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DMaterialAmount_Statics::NewProp_Count_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DMaterialAmount_Statics::NewProp_Count = { "Count", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DMaterialAmount, Count), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DMaterialAmount_Statics::NewProp_Count_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DMaterialAmount_Statics::NewProp_Count_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FFramework2DMaterialAmount_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DMaterialAmount_Statics::NewProp_Material,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DMaterialAmount_Statics::NewProp_Count,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFramework2DMaterialAmount_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_Framework2DTerrain,
		nullptr,
		&NewStructOps,
		"Framework2DMaterialAmount",
		sizeof(FFramework2DMaterialAmount),
		alignof(FFramework2DMaterialAmount),
		Z_Construct_UScriptStruct_FFramework2DMaterialAmount_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DMaterialAmount_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DMaterialAmount_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DMaterialAmount_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FFramework2DMaterialAmount()
	{
		if (!Z_Registration_Info_UScriptStruct_Framework2DMaterialAmount.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_Framework2DMaterialAmount.InnerSingleton, Z_Construct_UScriptStruct_FFramework2DMaterialAmount_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_Framework2DMaterialAmount.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_Framework2DDigResult;
class UScriptStruct* FFramework2DDigResult::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_Framework2DDigResult.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_Framework2DDigResult.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FFramework2DDigResult, Z_Construct_UPackage__Script_Framework2DTerrain(), TEXT("Framework2DDigResult"));
	}
	return Z_Registration_Info_UScriptStruct_Framework2DDigResult.OuterSingleton;
}
template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<FFramework2DDigResult>()
{
	return FFramework2DDigResult::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FFramework2DDigResult_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CellsRemoved_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_CellsRemoved;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CellsHit_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_CellsHit;
		static const UECodeGen_Private::FStructPropertyParams NewProp_Collected_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Collected_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Collected;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Location_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Location;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DDigResult_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * Resultado de un golpe al terreno (MineAt / Dig / Explode). Lo devuelve MineAt y lo emite\n * el evento OnTerrainMined, para enganchar sonido, particulas o inventario.\n */" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainTypes.h" },
		{ "ToolTip", "Resultado de un golpe al terreno (MineAt / Dig / Explode). Lo devuelve MineAt y lo emite\nel evento OnTerrainMined, para enganchar sonido, particulas o inventario." },
	};
#endif
	void* Z_Construct_UScriptStruct_FFramework2DDigResult_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFramework2DDigResult>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DDigResult_Statics::NewProp_CellsRemoved_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Celdas que se han roto de verdad en este golpe.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainTypes.h" },
		{ "ToolTip", "Celdas que se han roto de verdad en este golpe." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DDigResult_Statics::NewProp_CellsRemoved = { "CellsRemoved", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DDigResult, CellsRemoved), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DDigResult_Statics::NewProp_CellsRemoved_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DDigResult_Statics::NewProp_CellsRemoved_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DDigResult_Statics::NewProp_CellsHit_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Celdas alcanzadas: rotas o que han sumado dano (con la dureza, romper puede llevar varios golpes).\n" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainTypes.h" },
		{ "ToolTip", "Celdas alcanzadas: rotas o que han sumado dano (con la dureza, romper puede llevar varios golpes)." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DDigResult_Statics::NewProp_CellsHit = { "CellsHit", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DDigResult, CellsHit), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DDigResult_Statics::NewProp_CellsHit_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DDigResult_Statics::NewProp_CellsHit_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FFramework2DDigResult_Statics::NewProp_Collected_Inner = { "Collected", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FFramework2DMaterialAmount, METADATA_PARAMS(nullptr, 0) }; // 4006623681
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DDigResult_Statics::NewProp_Collected_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Material recogido (solo materiales con bCollectable).\n" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainTypes.h" },
		{ "ToolTip", "Material recogido (solo materiales con bCollectable)." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FFramework2DDigResult_Statics::NewProp_Collected = { "Collected", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DDigResult, Collected), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DDigResult_Statics::NewProp_Collected_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DDigResult_Statics::NewProp_Collected_MetaData)) }; // 4006623681
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DDigResult_Statics::NewProp_Location_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Punto del mundo donde se golpeo.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainTypes.h" },
		{ "ToolTip", "Punto del mundo donde se golpeo." },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FFramework2DDigResult_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DDigResult, Location), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DDigResult_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DDigResult_Statics::NewProp_Location_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FFramework2DDigResult_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DDigResult_Statics::NewProp_CellsRemoved,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DDigResult_Statics::NewProp_CellsHit,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DDigResult_Statics::NewProp_Collected_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DDigResult_Statics::NewProp_Collected,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DDigResult_Statics::NewProp_Location,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFramework2DDigResult_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_Framework2DTerrain,
		nullptr,
		&NewStructOps,
		"Framework2DDigResult",
		sizeof(FFramework2DDigResult),
		alignof(FFramework2DDigResult),
		Z_Construct_UScriptStruct_FFramework2DDigResult_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DDigResult_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DDigResult_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DDigResult_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FFramework2DDigResult()
	{
		if (!Z_Registration_Info_UScriptStruct_Framework2DDigResult.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_Framework2DDigResult.InnerSingleton, Z_Construct_UScriptStruct_FFramework2DDigResult_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_Framework2DDigResult.InnerSingleton;
	}
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_EFramework2DDebrisMode;
	static UEnum* EFramework2DDebrisMode_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_EFramework2DDebrisMode.OuterSingleton)
		{
			Z_Registration_Info_UEnum_EFramework2DDebrisMode.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_Framework2DTerrain_EFramework2DDebrisMode, Z_Construct_UPackage__Script_Framework2DTerrain(), TEXT("EFramework2DDebrisMode"));
		}
		return Z_Registration_Info_UEnum_EFramework2DDebrisMode.OuterSingleton;
	}
	template<> FRAMEWORK2DTERRAIN_API UEnum* StaticEnum<EFramework2DDebrisMode>()
	{
		return EFramework2DDebrisMode_StaticEnum();
	}
	struct Z_Construct_UEnum_Framework2DTerrain_EFramework2DDebrisMode_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_Framework2DTerrain_EFramework2DDebrisMode_Statics::Enumerators[] = {
		{ "EFramework2DDebrisMode::None", (int64)EFramework2DDebrisMode::None },
		{ "EFramework2DDebrisMode::Burst", (int64)EFramework2DDebrisMode::Burst },
		{ "EFramework2DDebrisMode::ToCollector", (int64)EFramework2DDebrisMode::ToCollector },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_Framework2DTerrain_EFramework2DDebrisMode_Statics::Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Burst.Comment", "// Saltan hacia fuera con gravedad y se desvanecen.\n" },
		{ "Burst.DisplayName", "Burst" },
		{ "Burst.Name", "EFramework2DDebrisMode::Burst" },
		{ "Burst.ToolTip", "Saltan hacia fuera con gravedad y se desvanecen." },
		{ "Comment", "/** Que hacen los pixeles que saltan al romper el terreno. */" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainTypes.h" },
		{ "None.Comment", "// Sin escombros.\n" },
		{ "None.DisplayName", "No debris" },
		{ "None.Name", "EFramework2DDebrisMode::None" },
		{ "None.ToolTip", "Sin escombros." },
		{ "ToCollector.Comment", "// Vuelan hacia quien pica (como la varita de KYORA). Sin recolector, salpican.\n" },
		{ "ToCollector.DisplayName", "Towards the digger" },
		{ "ToCollector.Name", "EFramework2DDebrisMode::ToCollector" },
		{ "ToCollector.ToolTip", "Vuelan hacia quien pica (como la varita de KYORA). Sin recolector, salpican." },
		{ "ToolTip", "Que hacen los pixeles que saltan al romper el terreno." },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_Framework2DTerrain_EFramework2DDebrisMode_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_Framework2DTerrain,
		nullptr,
		"EFramework2DDebrisMode",
		"EFramework2DDebrisMode",
		Z_Construct_UEnum_Framework2DTerrain_EFramework2DDebrisMode_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_Framework2DTerrain_EFramework2DDebrisMode_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(Z_Construct_UEnum_Framework2DTerrain_EFramework2DDebrisMode_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_Framework2DTerrain_EFramework2DDebrisMode_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_Framework2DTerrain_EFramework2DDebrisMode()
	{
		if (!Z_Registration_Info_UEnum_EFramework2DDebrisMode.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EFramework2DDebrisMode.InnerSingleton, Z_Construct_UEnum_Framework2DTerrain_EFramework2DDebrisMode_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_EFramework2DDebrisMode.InnerSingleton;
	}
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_EFramework2DCollisionShape;
	static UEnum* EFramework2DCollisionShape_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_EFramework2DCollisionShape.OuterSingleton)
		{
			Z_Registration_Info_UEnum_EFramework2DCollisionShape.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_Framework2DTerrain_EFramework2DCollisionShape, Z_Construct_UPackage__Script_Framework2DTerrain(), TEXT("EFramework2DCollisionShape"));
		}
		return Z_Registration_Info_UEnum_EFramework2DCollisionShape.OuterSingleton;
	}
	template<> FRAMEWORK2DTERRAIN_API UEnum* StaticEnum<EFramework2DCollisionShape>()
	{
		return EFramework2DCollisionShape_StaticEnum();
	}
	struct Z_Construct_UEnum_Framework2DTerrain_EFramework2DCollisionShape_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_Framework2DTerrain_EFramework2DCollisionShape_Statics::Enumerators[] = {
		{ "EFramework2DCollisionShape::Auto", (int64)EFramework2DCollisionShape::Auto },
		{ "EFramework2DCollisionShape::None", (int64)EFramework2DCollisionShape::None },
		{ "EFramework2DCollisionShape::Pixels", (int64)EFramework2DCollisionShape::Pixels },
		{ "EFramework2DCollisionShape::Full", (int64)EFramework2DCollisionShape::Full },
		{ "EFramework2DCollisionShape::TopHalf", (int64)EFramework2DCollisionShape::TopHalf },
		{ "EFramework2DCollisionShape::BottomHalf", (int64)EFramework2DCollisionShape::BottomHalf },
		{ "EFramework2DCollisionShape::LeftHalf", (int64)EFramework2DCollisionShape::LeftHalf },
		{ "EFramework2DCollisionShape::RightHalf", (int64)EFramework2DCollisionShape::RightHalf },
		{ "EFramework2DCollisionShape::SlopeUp", (int64)EFramework2DCollisionShape::SlopeUp },
		{ "EFramework2DCollisionShape::SlopeDown", (int64)EFramework2DCollisionShape::SlopeDown },
		{ "EFramework2DCollisionShape::Platform", (int64)EFramework2DCollisionShape::Platform },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_Framework2DTerrain_EFramework2DCollisionShape_Statics::Enum_MetaDataParams[] = {
		{ "Auto.Comment", "// La de siempre: chocan los pixeles del dibujo cuyo material colisiona.\n" },
		{ "Auto.DisplayName", "Automatic" },
		{ "Auto.Name", "EFramework2DCollisionShape::Auto" },
		{ "Auto.ToolTip", "La de siempre: chocan los pixeles del dibujo cuyo material colisiona." },
		{ "BlueprintType", "true" },
		{ "BottomHalf.DisplayName", "Bottom half" },
		{ "BottomHalf.Name", "EFramework2DCollisionShape::BottomHalf" },
		{ "Comment", "/**\n * Colision de un tile. Se elige por tile en el TileSet (vale en todo el mapa) y, celda a\n * celda, con el pincel de COLISION del modo Framework2D Tiles (gana al del TileSet).\n * Las formas (Bloque, mitades, rampas, plataforma) son colision \"a medida\": no dependen del\n * dibujo, asi que sirven tambien para paredes invisibles. Si el jugador pica un pixel, ese\n * pixel vuelve a la colision automatica (lo roto deja de chocar).\n */" },
		{ "Full.Comment", "// El tile entero, tenga dibujo o no (pared invisible).\n" },
		{ "Full.DisplayName", "Full block" },
		{ "Full.Name", "EFramework2DCollisionShape::Full" },
		{ "Full.ToolTip", "El tile entero, tenga dibujo o no (pared invisible)." },
		{ "LeftHalf.DisplayName", "Left half" },
		{ "LeftHalf.Name", "EFramework2DCollisionShape::LeftHalf" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainTypes.h" },
		{ "None.Comment", "// Nada de este tile choca.\n" },
		{ "None.DisplayName", "No collision" },
		{ "None.Name", "EFramework2DCollisionShape::None" },
		{ "None.ToolTip", "Nada de este tile choca." },
		{ "Pixels.Comment", "// Chocan todos los pixeles del dibujo, aunque el material no colisione (p. ej. Decoration).\n" },
		{ "Pixels.DisplayName", "Drawing pixels" },
		{ "Pixels.Name", "EFramework2DCollisionShape::Pixels" },
		{ "Pixels.ToolTip", "Chocan todos los pixeles del dibujo, aunque el material no colisione (p. ej. Decoration)." },
		{ "Platform.Comment", "// Franja fina en la parte de arriba del tile (un cuarto del alto).\n" },
		{ "Platform.DisplayName", "Thin platform" },
		{ "Platform.Name", "EFramework2DCollisionShape::Platform" },
		{ "Platform.ToolTip", "Franja fina en la parte de arriba del tile (un cuarto del alto)." },
		{ "RightHalf.DisplayName", "Right half" },
		{ "RightHalf.Name", "EFramework2DCollisionShape::RightHalf" },
		{ "SlopeDown.Comment", "// Rampa que baja hacia la derecha (triangulo abajo-izquierda).\n" },
		{ "SlopeDown.DisplayName", "Falling ramp" },
		{ "SlopeDown.Name", "EFramework2DCollisionShape::SlopeDown" },
		{ "SlopeDown.ToolTip", "Rampa que baja hacia la derecha (triangulo abajo-izquierda)." },
		{ "SlopeUp.Comment", "// Rampa que sube hacia la derecha (triangulo abajo-derecha).\n" },
		{ "SlopeUp.DisplayName", "Rising ramp" },
		{ "SlopeUp.Name", "EFramework2DCollisionShape::SlopeUp" },
		{ "SlopeUp.ToolTip", "Rampa que sube hacia la derecha (triangulo abajo-derecha)." },
		{ "ToolTip", "Colision de un tile. Se elige por tile en el TileSet (vale en todo el mapa) y, celda a\ncelda, con el pincel de COLISION del modo Framework2D Tiles (gana al del TileSet).\nLas formas (Bloque, mitades, rampas, plataforma) son colision \"a medida\": no dependen del\ndibujo, asi que sirven tambien para paredes invisibles. Si el jugador pica un pixel, ese\npixel vuelve a la colision automatica (lo roto deja de chocar)." },
		{ "TopHalf.DisplayName", "Top half" },
		{ "TopHalf.Name", "EFramework2DCollisionShape::TopHalf" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_Framework2DTerrain_EFramework2DCollisionShape_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_Framework2DTerrain,
		nullptr,
		"EFramework2DCollisionShape",
		"EFramework2DCollisionShape",
		Z_Construct_UEnum_Framework2DTerrain_EFramework2DCollisionShape_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_Framework2DTerrain_EFramework2DCollisionShape_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(Z_Construct_UEnum_Framework2DTerrain_EFramework2DCollisionShape_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_Framework2DTerrain_EFramework2DCollisionShape_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_Framework2DTerrain_EFramework2DCollisionShape()
	{
		if (!Z_Registration_Info_UEnum_EFramework2DCollisionShape.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EFramework2DCollisionShape.InnerSingleton, Z_Construct_UEnum_Framework2DTerrain_EFramework2DCollisionShape_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_EFramework2DCollisionShape.InnerSingleton;
	}
	struct Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainTypes_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainTypes_h_Statics::EnumInfo[] = {
		{ EFramework2DDebrisMode_StaticEnum, TEXT("EFramework2DDebrisMode"), &Z_Registration_Info_UEnum_EFramework2DDebrisMode, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 4228834754U) },
		{ EFramework2DCollisionShape_StaticEnum, TEXT("EFramework2DCollisionShape"), &Z_Registration_Info_UEnum_EFramework2DCollisionShape, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 627041027U) },
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainTypes_h_Statics::ScriptStructInfo[] = {
		{ FFramework2DMaterial::StaticStruct, Z_Construct_UScriptStruct_FFramework2DMaterial_Statics::NewStructOps, TEXT("Framework2DMaterial"), &Z_Registration_Info_UScriptStruct_Framework2DMaterial, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FFramework2DMaterial), 3334758378U) },
		{ FFramework2DMaterialAmount::StaticStruct, Z_Construct_UScriptStruct_FFramework2DMaterialAmount_Statics::NewStructOps, TEXT("Framework2DMaterialAmount"), &Z_Registration_Info_UScriptStruct_Framework2DMaterialAmount, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FFramework2DMaterialAmount), 4006623681U) },
		{ FFramework2DDigResult::StaticStruct, Z_Construct_UScriptStruct_FFramework2DDigResult_Statics::NewStructOps, TEXT("Framework2DDigResult"), &Z_Registration_Info_UScriptStruct_Framework2DDigResult, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FFramework2DDigResult), 3002348450U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainTypes_h_1909032981(TEXT("/Script/Framework2DTerrain"),
		nullptr, 0,
		Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainTypes_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainTypes_h_Statics::ScriptStructInfo),
		Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainTypes_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainTypes_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
