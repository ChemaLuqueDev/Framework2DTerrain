// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Framework2DTerrain/Public/Framework2DProcGenTypes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFramework2DProcGenTypes() {}
// Cross Module References
	FRAMEWORK2DTERRAIN_API UEnum* Z_Construct_UEnum_Framework2DTerrain_EFramework2DDecorPlacement();
	UPackage* Z_Construct_UPackage__Script_Framework2DTerrain();
	FRAMEWORK2DTERRAIN_API UScriptStruct* Z_Construct_UScriptStruct_FFramework2DTile3x3();
	FRAMEWORK2DTERRAIN_API UScriptStruct* Z_Construct_UScriptStruct_FFramework2DTile5x5();
	FRAMEWORK2DTERRAIN_API UScriptStruct* Z_Construct_UScriptStruct_FFramework2DInnerCorners();
	FRAMEWORK2DTERRAIN_API UEnum* Z_Construct_UEnum_Framework2DTerrain_EFramework2DReliefStyle();
	FRAMEWORK2DTERRAIN_API UEnum* Z_Construct_UEnum_Framework2DTerrain_EFramework2DPropDepth();
	FRAMEWORK2DTERRAIN_API UScriptStruct* Z_Construct_UScriptStruct_FFramework2DBackdropLayer();
	ENGINE_API UClass* Z_Construct_UClass_UTexture2D_NoRegister();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FLinearColor();
	FRAMEWORK2DTERRAIN_API UScriptStruct* Z_Construct_UScriptStruct_FFramework2DPropInstance();
	FRAMEWORK2DTERRAIN_API UScriptStruct* Z_Construct_UScriptStruct_FFramework2DBiomeProp();
	FRAMEWORK2DTERRAIN_API UScriptStruct* Z_Construct_UScriptStruct_FFramework2DBiomeBlock();
	FRAMEWORK2DTERRAIN_API UScriptStruct* Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree();
	FRAMEWORK2DTERRAIN_API UScriptStruct* Z_Construct_UScriptStruct_FFramework2DBiomeDecoration();
	FRAMEWORK2DTERRAIN_API UScriptStruct* Z_Construct_UScriptStruct_FFramework2DBiome();
	FRAMEWORK2DTERRAIN_API UEnum* Z_Construct_UEnum_Framework2DTerrain_EFramework2DBiomeSlot();
	FRAMEWORK2DTERRAIN_API UScriptStruct* Z_Construct_UScriptStruct_FFramework2DProcGenSettings();
	FRAMEWORK2DTERRAIN_API UScriptStruct* Z_Construct_UScriptStruct_FFramework2DProcGenReport();
// End Cross Module References
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_EFramework2DDecorPlacement;
	static UEnum* EFramework2DDecorPlacement_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_EFramework2DDecorPlacement.OuterSingleton)
		{
			Z_Registration_Info_UEnum_EFramework2DDecorPlacement.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_Framework2DTerrain_EFramework2DDecorPlacement, Z_Construct_UPackage__Script_Framework2DTerrain(), TEXT("EFramework2DDecorPlacement"));
		}
		return Z_Registration_Info_UEnum_EFramework2DDecorPlacement.OuterSingleton;
	}
	template<> FRAMEWORK2DTERRAIN_API UEnum* StaticEnum<EFramework2DDecorPlacement>()
	{
		return EFramework2DDecorPlacement_StaticEnum();
	}
	struct Z_Construct_UEnum_Framework2DTerrain_EFramework2DDecorPlacement_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_Framework2DTerrain_EFramework2DDecorPlacement_Statics::Enumerators[] = {
		{ "EFramework2DDecorPlacement::Ground", (int64)EFramework2DDecorPlacement::Ground },
		{ "EFramework2DDecorPlacement::Ceiling", (int64)EFramework2DDecorPlacement::Ceiling },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_Framework2DTerrain_EFramework2DDecorPlacement_Statics::Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Ceiling.Comment", "// Colgando bajo el terreno (lianas o estalactitas bajo las plataformas).\n" },
		{ "Ceiling.DisplayName", "Techo" },
		{ "Ceiling.Name", "EFramework2DDecorPlacement::Ceiling" },
		{ "Ceiling.ToolTip", "Colgando bajo el terreno (lianas o estalactitas bajo las plataformas)." },
		{ "Comment", "/** Donde va un adorno del bioma. */" },
		{ "Ground.Comment", "// Encima del suelo (hierba, rocas, flores, antorchas...).\n" },
		{ "Ground.DisplayName", "Suelo" },
		{ "Ground.Name", "EFramework2DDecorPlacement::Ground" },
		{ "Ground.ToolTip", "Encima del suelo (hierba, rocas, flores, antorchas...)." },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Donde va un adorno del bioma." },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_Framework2DTerrain_EFramework2DDecorPlacement_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_Framework2DTerrain,
		nullptr,
		"EFramework2DDecorPlacement",
		"EFramework2DDecorPlacement",
		Z_Construct_UEnum_Framework2DTerrain_EFramework2DDecorPlacement_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_Framework2DTerrain_EFramework2DDecorPlacement_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(Z_Construct_UEnum_Framework2DTerrain_EFramework2DDecorPlacement_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_Framework2DTerrain_EFramework2DDecorPlacement_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_Framework2DTerrain_EFramework2DDecorPlacement()
	{
		if (!Z_Registration_Info_UEnum_EFramework2DDecorPlacement.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EFramework2DDecorPlacement.InnerSingleton, Z_Construct_UEnum_Framework2DTerrain_EFramework2DDecorPlacement_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_EFramework2DDecorPlacement.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_Framework2DTile3x3;
class UScriptStruct* FFramework2DTile3x3::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_Framework2DTile3x3.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_Framework2DTile3x3.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FFramework2DTile3x3, Z_Construct_UPackage__Script_Framework2DTerrain(), TEXT("Framework2DTile3x3"));
	}
	return Z_Registration_Info_UScriptStruct_Framework2DTile3x3.OuterSingleton;
}
template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<FFramework2DTile3x3>()
{
	return FFramework2DTile3x3::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TopLeft_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_TopLeft;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Top_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Top;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TopRight_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_TopRight;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Left_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Left;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Center_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Center;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Right_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Right;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BottomLeft_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_BottomLeft;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Bottom_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Bottom;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BottomRight_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_BottomRight;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * Las 9 piezas de un terreno \"3x3\": esquinas, bordes y centro. Con solo el centro ya se puede\n * generar (las que falten usan la pieza mas parecida: esquina -> borde -> centro).\n */" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Las 9 piezas de un terreno \"3x3\": esquinas, bordes y centro. Con solo el centro ya se puede\ngenerar (las que falten usan la pieza mas parecida: esquina -> borde -> centro)." },
	};
#endif
	void* Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFramework2DTile3x3>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_TopLeft_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_TopLeft = { "TopLeft", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DTile3x3, TopLeft), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_TopLeft_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_TopLeft_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_Top_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_Top = { "Top", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DTile3x3, Top), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_Top_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_Top_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_TopRight_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_TopRight = { "TopRight", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DTile3x3, TopRight), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_TopRight_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_TopRight_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_Left_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_Left = { "Left", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DTile3x3, Left), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_Left_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_Left_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_Center_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_Center = { "Center", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DTile3x3, Center), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_Center_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_Center_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_Right_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_Right = { "Right", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DTile3x3, Right), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_Right_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_Right_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_BottomLeft_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_BottomLeft = { "BottomLeft", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DTile3x3, BottomLeft), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_BottomLeft_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_BottomLeft_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_Bottom_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_Bottom = { "Bottom", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DTile3x3, Bottom), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_Bottom_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_Bottom_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_BottomRight_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_BottomRight = { "BottomRight", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DTile3x3, BottomRight), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_BottomRight_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_BottomRight_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_TopLeft,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_Top,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_TopRight,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_Left,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_Center,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_Right,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_BottomLeft,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_Bottom,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewProp_BottomRight,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_Framework2DTerrain,
		nullptr,
		&NewStructOps,
		"Framework2DTile3x3",
		sizeof(FFramework2DTile3x3),
		alignof(FFramework2DTile3x3),
		Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FFramework2DTile3x3()
	{
		if (!Z_Registration_Info_UScriptStruct_Framework2DTile3x3.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_Framework2DTile3x3.InnerSingleton, Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_Framework2DTile3x3.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_Framework2DTile5x5;
class UScriptStruct* FFramework2DTile5x5::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_Framework2DTile5x5.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_Framework2DTile5x5.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FFramework2DTile5x5, Z_Construct_UPackage__Script_Framework2DTerrain(), TEXT("Framework2DTile5x5"));
	}
	return Z_Registration_Info_UScriptStruct_Framework2DTile5x5.OuterSingleton;
}
template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<FFramework2DTile5x5>()
{
	return FFramework2DTile5x5::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FFramework2DTile5x5_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UECodeGen_Private::FIntPropertyParams NewProp_Pieces_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Pieces_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Pieces;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DTile5x5_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * Terreno 5x5 (opcional): para tilesets cuyos bordes tienen DOS tiles de grosor (la hierba que\n * ocupa dos filas, rocas en los lados...). Filas: 0 = la de arriba del todo, 1 = la segunda, 2 y 3 =\n * el interior (3 = la de justo encima del borde de abajo), 4 = la de abajo. Columnas igual de\n * izquierda a derecha. Si tiene el centro (fila 2, columna 2), manda sobre el 3x3.\n */" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Terreno 5x5 (opcional): para tilesets cuyos bordes tienen DOS tiles de grosor (la hierba que\nocupa dos filas, rocas en los lados...). Filas: 0 = la de arriba del todo, 1 = la segunda, 2 y 3 =\nel interior (3 = la de justo encima del borde de abajo), 4 = la de abajo. Columnas igual de\nizquierda a derecha. Si tiene el centro (fila 2, columna 2), manda sobre el 3x3." },
	};
#endif
	void* Z_Construct_UScriptStruct_FFramework2DTile5x5_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFramework2DTile5x5>();
	}
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DTile5x5_Statics::NewProp_Pieces_Inner = { "Pieces", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DTile5x5_Statics::NewProp_Pieces_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// 25 piezas en orden de lectura (fila * 5 + columna). -1 = sin asignar.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "25 piezas en orden de lectura (fila * 5 + columna). -1 = sin asignar." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FFramework2DTile5x5_Statics::NewProp_Pieces = { "Pieces", nullptr, (EPropertyFlags)0x0010000000000045, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DTile5x5, Pieces), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DTile5x5_Statics::NewProp_Pieces_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DTile5x5_Statics::NewProp_Pieces_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FFramework2DTile5x5_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DTile5x5_Statics::NewProp_Pieces_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DTile5x5_Statics::NewProp_Pieces,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFramework2DTile5x5_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_Framework2DTerrain,
		nullptr,
		&NewStructOps,
		"Framework2DTile5x5",
		sizeof(FFramework2DTile5x5),
		alignof(FFramework2DTile5x5),
		Z_Construct_UScriptStruct_FFramework2DTile5x5_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DTile5x5_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DTile5x5_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DTile5x5_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FFramework2DTile5x5()
	{
		if (!Z_Registration_Info_UScriptStruct_Framework2DTile5x5.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_Framework2DTile5x5.InnerSingleton, Z_Construct_UScriptStruct_FFramework2DTile5x5_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_Framework2DTile5x5.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_Framework2DInnerCorners;
class UScriptStruct* FFramework2DInnerCorners::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_Framework2DInnerCorners.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_Framework2DInnerCorners.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FFramework2DInnerCorners, Z_Construct_UPackage__Script_Framework2DTerrain(), TEXT("Framework2DInnerCorners"));
	}
	return Z_Registration_Info_UScriptStruct_Framework2DInnerCorners.OuterSingleton;
}
template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<FFramework2DInnerCorners>()
{
	return FFramework2DInnerCorners::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FFramework2DInnerCorners_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TopLeft_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_TopLeft;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TopRight_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_TopRight;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BottomLeft_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_BottomLeft;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BottomRight_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_BottomRight;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DInnerCorners_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * Esquinas INTERIORES (opcionales): la pieza que une un suelo con la pared de un escalon (la\n * hierba dobla la esquina hacia dentro). Sin ellas se usa el centro.\n */" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Esquinas INTERIORES (opcionales): la pieza que une un suelo con la pared de un escalon (la\nhierba dobla la esquina hacia dentro). Sin ellas se usa el centro." },
	};
#endif
	void* Z_Construct_UScriptStruct_FFramework2DInnerCorners_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFramework2DInnerCorners>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DInnerCorners_Statics::NewProp_TopLeft_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Hueco arriba-izquierda (pie de un escalon que sube hacia la derecha).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Hueco arriba-izquierda (pie de un escalon que sube hacia la derecha)." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DInnerCorners_Statics::NewProp_TopLeft = { "TopLeft", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DInnerCorners, TopLeft), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DInnerCorners_Statics::NewProp_TopLeft_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DInnerCorners_Statics::NewProp_TopLeft_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DInnerCorners_Statics::NewProp_TopRight_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Hueco arriba-derecha (pie de un escalon que sube hacia la izquierda).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Hueco arriba-derecha (pie de un escalon que sube hacia la izquierda)." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DInnerCorners_Statics::NewProp_TopRight = { "TopRight", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DInnerCorners, TopRight), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DInnerCorners_Statics::NewProp_TopRight_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DInnerCorners_Statics::NewProp_TopRight_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DInnerCorners_Statics::NewProp_BottomLeft_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DInnerCorners_Statics::NewProp_BottomLeft = { "BottomLeft", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DInnerCorners, BottomLeft), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DInnerCorners_Statics::NewProp_BottomLeft_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DInnerCorners_Statics::NewProp_BottomLeft_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DInnerCorners_Statics::NewProp_BottomRight_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DInnerCorners_Statics::NewProp_BottomRight = { "BottomRight", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DInnerCorners, BottomRight), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DInnerCorners_Statics::NewProp_BottomRight_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DInnerCorners_Statics::NewProp_BottomRight_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FFramework2DInnerCorners_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DInnerCorners_Statics::NewProp_TopLeft,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DInnerCorners_Statics::NewProp_TopRight,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DInnerCorners_Statics::NewProp_BottomLeft,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DInnerCorners_Statics::NewProp_BottomRight,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFramework2DInnerCorners_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_Framework2DTerrain,
		nullptr,
		&NewStructOps,
		"Framework2DInnerCorners",
		sizeof(FFramework2DInnerCorners),
		alignof(FFramework2DInnerCorners),
		Z_Construct_UScriptStruct_FFramework2DInnerCorners_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DInnerCorners_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DInnerCorners_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DInnerCorners_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FFramework2DInnerCorners()
	{
		if (!Z_Registration_Info_UScriptStruct_Framework2DInnerCorners.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_Framework2DInnerCorners.InnerSingleton, Z_Construct_UScriptStruct_FFramework2DInnerCorners_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_Framework2DInnerCorners.InnerSingleton;
	}
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_EFramework2DReliefStyle;
	static UEnum* EFramework2DReliefStyle_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_EFramework2DReliefStyle.OuterSingleton)
		{
			Z_Registration_Info_UEnum_EFramework2DReliefStyle.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_Framework2DTerrain_EFramework2DReliefStyle, Z_Construct_UPackage__Script_Framework2DTerrain(), TEXT("EFramework2DReliefStyle"));
		}
		return Z_Registration_Info_UEnum_EFramework2DReliefStyle.OuterSingleton;
	}
	template<> FRAMEWORK2DTERRAIN_API UEnum* StaticEnum<EFramework2DReliefStyle>()
	{
		return EFramework2DReliefStyle_StaticEnum();
	}
	struct Z_Construct_UEnum_Framework2DTerrain_EFramework2DReliefStyle_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_Framework2DTerrain_EFramework2DReliefStyle_Statics::Enumerators[] = {
		{ "EFramework2DReliefStyle::Steps", (int64)EFramework2DReliefStyle::Steps },
		{ "EFramework2DReliefStyle::Hills", (int64)EFramework2DReliefStyle::Hills },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_Framework2DTerrain_EFramework2DReliefStyle_Statics::Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/** Forma del suelo que construye el generador. */" },
		{ "Hills.Comment", "// Lomas suaves que suben y bajan casilla a casilla (exteriores naturales).\n" },
		{ "Hills.DisplayName", "Lomas" },
		{ "Hills.Name", "EFramework2DReliefStyle::Hills" },
		{ "Hills.ToolTip", "Lomas suaves que suben y bajan casilla a casilla (exteriores naturales)." },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "Steps.Comment", "// Llanos a varias alturas unidos por escalones y rampas (plataformas clasicas).\n" },
		{ "Steps.DisplayName", "Escalones" },
		{ "Steps.Name", "EFramework2DReliefStyle::Steps" },
		{ "Steps.ToolTip", "Llanos a varias alturas unidos por escalones y rampas (plataformas clasicas)." },
		{ "ToolTip", "Forma del suelo que construye el generador." },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_Framework2DTerrain_EFramework2DReliefStyle_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_Framework2DTerrain,
		nullptr,
		"EFramework2DReliefStyle",
		"EFramework2DReliefStyle",
		Z_Construct_UEnum_Framework2DTerrain_EFramework2DReliefStyle_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_Framework2DTerrain_EFramework2DReliefStyle_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(Z_Construct_UEnum_Framework2DTerrain_EFramework2DReliefStyle_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_Framework2DTerrain_EFramework2DReliefStyle_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_Framework2DTerrain_EFramework2DReliefStyle()
	{
		if (!Z_Registration_Info_UEnum_EFramework2DReliefStyle.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EFramework2DReliefStyle.InnerSingleton, Z_Construct_UEnum_Framework2DTerrain_EFramework2DReliefStyle_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_EFramework2DReliefStyle.InnerSingleton;
	}
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_EFramework2DPropDepth;
	static UEnum* EFramework2DPropDepth_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_EFramework2DPropDepth.OuterSingleton)
		{
			Z_Registration_Info_UEnum_EFramework2DPropDepth.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_Framework2DTerrain_EFramework2DPropDepth, Z_Construct_UPackage__Script_Framework2DTerrain(), TEXT("EFramework2DPropDepth"));
		}
		return Z_Registration_Info_UEnum_EFramework2DPropDepth.OuterSingleton;
	}
	template<> FRAMEWORK2DTERRAIN_API UEnum* StaticEnum<EFramework2DPropDepth>()
	{
		return EFramework2DPropDepth_StaticEnum();
	}
	struct Z_Construct_UEnum_Framework2DTerrain_EFramework2DPropDepth_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_Framework2DTerrain_EFramework2DPropDepth_Statics::Enumerators[] = {
		{ "EFramework2DPropDepth::Behind", (int64)EFramework2DPropDepth::Behind },
		{ "EFramework2DPropDepth::Front", (int64)EFramework2DPropDepth::Front },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_Framework2DTerrain_EFramework2DPropDepth_Statics::Enum_MetaDataParams[] = {
		{ "Behind.Comment", "// En una capa detras del terreno (arboles, rocas del paisaje): no choca ni se rompe.\n" },
		{ "Behind.DisplayName", "Detr\xc3\xa1s del terreno" },
		{ "Behind.Name", "EFramework2DPropDepth::Behind" },
		{ "Behind.ToolTip", "En una capa detras del terreno (arboles, rocas del paisaje): no choca ni se rompe." },
		{ "BlueprintType", "true" },
		{ "Comment", "/** Donde va un objeto grande del bioma. */" },
		{ "Front.Comment", "// En la capa de decoracion, delante (setas grandes, piedras): se ve delante del personaje.\n" },
		{ "Front.DisplayName", "Delante del terreno" },
		{ "Front.Name", "EFramework2DPropDepth::Front" },
		{ "Front.ToolTip", "En la capa de decoracion, delante (setas grandes, piedras): se ve delante del personaje." },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Donde va un objeto grande del bioma." },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_Framework2DTerrain_EFramework2DPropDepth_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_Framework2DTerrain,
		nullptr,
		"EFramework2DPropDepth",
		"EFramework2DPropDepth",
		Z_Construct_UEnum_Framework2DTerrain_EFramework2DPropDepth_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_Framework2DTerrain_EFramework2DPropDepth_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(Z_Construct_UEnum_Framework2DTerrain_EFramework2DPropDepth_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_Framework2DTerrain_EFramework2DPropDepth_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_Framework2DTerrain_EFramework2DPropDepth()
	{
		if (!Z_Registration_Info_UEnum_EFramework2DPropDepth.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EFramework2DPropDepth.InnerSingleton, Z_Construct_UEnum_Framework2DTerrain_EFramework2DPropDepth_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_EFramework2DPropDepth.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_Framework2DBackdropLayer;
class UScriptStruct* FFramework2DBackdropLayer::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_Framework2DBackdropLayer.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_Framework2DBackdropLayer.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FFramework2DBackdropLayer, Z_Construct_UPackage__Script_Framework2DTerrain(), TEXT("Framework2DBackdropLayer"));
	}
	return Z_Registration_Info_UScriptStruct_Framework2DBackdropLayer.OuterSingleton;
}
template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<FFramework2DBackdropLayer>()
{
	return FFramework2DBackdropLayer::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics
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
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Texture_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_Texture;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Parallax_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Parallax;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VerticalParallax_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_VerticalParallax;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Scale_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Scale;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Height_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Height;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bRepeat_MetaData[];
#endif
		static void NewProp_bRepeat_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bRepeat;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bFillBelow_MetaData[];
#endif
		static void NewProp_bFillBelow_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bFillBelow;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bFillAbove_MetaData[];
#endif
		static void NewProp_bFillAbove_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bFillAbove;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Tint_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Tint;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * Una capa de FONDO PARALLAX: una imagen (cielo, montanas, bosque lejano...) detras del terreno\n * que se mueve mas despacio que el nivel al mover la camara. Se ve en el editor y en el juego.\n */" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Una capa de FONDO PARALLAX: una imagen (cielo, montanas, bosque lejano...) detras del terreno\nque se mueve mas despacio que el nivel al mover la camara. Se ve en el editor y en el juego." },
	};
#endif
	void* Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFramework2DBackdropLayer>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_Name_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBackdropLayer, Name), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_Name_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_Name_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_Texture_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// La imagen. Para pixel art: Filter = Nearest y sin mipmaps (boton derecho > Sprite Actions >\n// Apply Paper2D Texture Settings). Para repetirla a lo ancho, Address X = Wrap (el de serie).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "La imagen. Para pixel art: Filter = Nearest y sin mipmaps (boton derecho > Sprite Actions >\nApply Paper2D Texture Settings). Para repetirla a lo ancho, Address X = Wrap (el de serie)." },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_Texture = { "Texture", nullptr, (EPropertyFlags)0x0014000000000005, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBackdropLayer, Texture), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_Texture_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_Texture_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_Parallax_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "Comment", "// Cuanto se mueve con el nivel: 0 = quieta en la pantalla (cielo), 1 = como el terreno.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Cuanto se mueve con el nivel: 0 = quieta en la pantalla (cielo), 1 = como el terreno." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_Parallax = { "Parallax", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBackdropLayer, Parallax), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_Parallax_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_Parallax_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_VerticalParallax_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "Comment", "// Lo mismo en vertical (normalmente menos que en horizontal).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Lo mismo en vertical (normalmente menos que en horizontal)." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_VerticalParallax = { "VerticalParallax", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBackdropLayer, VerticalParallax), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_VerticalParallax_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_VerticalParallax_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_Scale_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "32.0" },
		{ "ClampMin", "0.1" },
		{ "Comment", "// Tamano: pixeles del terreno por pixel de la imagen (1 = el mismo tamano de pixel que el nivel).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Tamano: pixeles del terreno por pixel de la imagen (1 = el mismo tamano de pixel que el nivel)." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_Scale = { "Scale", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBackdropLayer, Scale), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_Scale_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_Scale_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_Height_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "1024.0" },
		{ "ClampMin", "-256.0" },
		{ "Comment", "// Altura (tiles) del borde de abajo de la imagen sobre el fondo del nivel.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Altura (tiles) del borde de abajo de la imagen sobre el fondo del nivel." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_Height = { "Height", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBackdropLayer, Height), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_Height_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_Height_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_bRepeat_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Repetir la imagen a lo ancho (sin fin).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Repetir la imagen a lo ancho (sin fin)." },
	};
#endif
	void Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_bRepeat_SetBit(void* Obj)
	{
		((FFramework2DBackdropLayer*)Obj)->bRepeat = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_bRepeat = { "bRepeat", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FFramework2DBackdropLayer), &Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_bRepeat_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_bRepeat_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_bRepeat_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_bFillBelow_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Alarga la fila de abajo de la imagen hasta el fondo del nivel (sin huecos debajo).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Alarga la fila de abajo de la imagen hasta el fondo del nivel (sin huecos debajo)." },
	};
#endif
	void Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_bFillBelow_SetBit(void* Obj)
	{
		((FFramework2DBackdropLayer*)Obj)->bFillBelow = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_bFillBelow = { "bFillBelow", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FFramework2DBackdropLayer), &Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_bFillBelow_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_bFillBelow_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_bFillBelow_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_bFillAbove_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Alarga la fila de arriba hasta lo alto del nivel (para el cielo).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Alarga la fila de arriba hasta lo alto del nivel (para el cielo)." },
	};
#endif
	void Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_bFillAbove_SetBit(void* Obj)
	{
		((FFramework2DBackdropLayer*)Obj)->bFillAbove = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_bFillAbove = { "bFillAbove", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FFramework2DBackdropLayer), &Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_bFillAbove_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_bFillAbove_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_bFillAbove_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_Tint_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Tinte (blanco = sin cambios).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Tinte (blanco = sin cambios)." },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_Tint = { "Tint", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBackdropLayer, Tint), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_Tint_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_Tint_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_Name,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_Texture,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_Parallax,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_VerticalParallax,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_Scale,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_Height,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_bRepeat,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_bFillBelow,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_bFillAbove,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewProp_Tint,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_Framework2DTerrain,
		nullptr,
		&NewStructOps,
		"Framework2DBackdropLayer",
		sizeof(FFramework2DBackdropLayer),
		alignof(FFramework2DBackdropLayer),
		Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FFramework2DBackdropLayer()
	{
		if (!Z_Registration_Info_UScriptStruct_Framework2DBackdropLayer.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_Framework2DBackdropLayer.InnerSingleton, Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_Framework2DBackdropLayer.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_Framework2DPropInstance;
class UScriptStruct* FFramework2DPropInstance::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_Framework2DPropInstance.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_Framework2DPropInstance.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FFramework2DPropInstance, Z_Construct_UPackage__Script_Framework2DTerrain(), TEXT("Framework2DPropInstance"));
	}
	return Z_Registration_Info_UScriptStruct_Framework2DPropInstance.OuterSingleton;
}
template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<FFramework2DPropInstance>()
{
	return FFramework2DPropInstance::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PropId_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_PropId;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Layer_MetaData[];
#endif
		static const UECodeGen_Private::FNamePropertyParams NewProp_Layer;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_X_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_X;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Y_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Y;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SinkPixels_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_SinkPixels;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bFlip_MetaData[];
#endif
		static void NewProp_bFlip_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bFlip;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bHanging_MetaData[];
#endif
		static void NewProp_bHanging_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bHanging;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bCoverTiles_MetaData[];
#endif
		static void NewProp_bCoverTiles_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bCoverTiles;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bSnapToGround_MetaData[];
#endif
		static void NewProp_bSnapToGround_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bSnapToGround;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Scale_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Scale;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * Un OBJETO GRANDE colocado en el mapa (arbol, roca, piedra runica...): una imagen del Tile Set\n * (Props) que se hornea como pixeles de una capa. Lo crea el generador procedural.\n */" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Un OBJETO GRANDE colocado en el mapa (arbol, roca, piedra runica...): una imagen del Tile Set\n(Props) que se hornea como pixeles de una capa. Lo crea el generador procedural." },
	};
#endif
	void* Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFramework2DPropInstance>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_PropId_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Id del objeto en el Tile Set (Props).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Id del objeto en el Tile Set (Props)." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_PropId = { "PropId", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DPropInstance, PropId), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_PropId_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_PropId_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_Layer_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Capa del mapa (por nombre) donde se hornea.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Capa del mapa (por nombre) donde se hornea." },
	};
#endif
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_Layer = { "Layer", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DPropInstance, Layer), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_Layer_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_Layer_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_X_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Centro horizontal (en tiles; 10.5 = la mitad de la columna 10).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Centro horizontal (en tiles; 10.5 = la mitad de la columna 10)." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_X = { "X", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DPropInstance, X), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_X_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_X_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_Y_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Fila del mapa (Y = 0 arriba) de la casilla sobre la que se apoya: el pie del objeto queda en\n// el borde de abajo de esa casilla (o, si cuelga, la cabeza en su borde de arriba).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Fila del mapa (Y = 0 arriba) de la casilla sobre la que se apoya: el pie del objeto queda en\nel borde de abajo de esa casilla (o, si cuelga, la cabeza en su borde de arriba)." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_Y = { "Y", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DPropInstance, Y), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_Y_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_Y_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_SinkPixels_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Pixeles que se hunde en el suelo (o en el techo, si cuelga).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Pixeles que se hunde en el suelo (o en el techo, si cuelga)." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_SinkPixels = { "SinkPixels", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DPropInstance, SinkPixels), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_SinkPixels_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_SinkPixels_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_bFlip_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_bFlip_SetBit(void* Obj)
	{
		((FFramework2DPropInstance*)Obj)->bFlip = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_bFlip = { "bFlip", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FFramework2DPropInstance), &Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_bFlip_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_bFlip_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_bFlip_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_bHanging_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Cuelga del techo en vez de apoyarse en el suelo.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Cuelga del techo en vez de apoyarse en el suelo." },
	};
#endif
	void Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_bHanging_SetBit(void* Obj)
	{
		((FFramework2DPropInstance*)Obj)->bHanging = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_bHanging = { "bHanging", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FFramework2DPropInstance), &Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_bHanging_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_bHanging_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_bHanging_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_bCoverTiles_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Tapa lo que ya hay en su capa (tiles y objetos de antes): la copa de un arbol tapa su tronco.\n// Si no, solo pinta donde la capa esta vacia.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Tapa lo que ya hay en su capa (tiles y objetos de antes): la copa de un arbol tapa su tronco.\nSi no, solo pinta donde la capa esta vacia." },
	};
#endif
	void Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_bCoverTiles_SetBit(void* Obj)
	{
		((FFramework2DPropInstance*)Obj)->bCoverTiles = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_bCoverTiles = { "bCoverTiles", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FFramework2DPropInstance), &Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_bCoverTiles_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_bCoverTiles_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_bCoverTiles_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_bSnapToGround_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Apoya el pie en el primer pixel de suelo que choca bajo su centro (como los generadores):\n// asi no flota sobre tiles cuya hierba empieza mas abajo del borde del tile. Hundir se suma.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Apoya el pie en el primer pixel de suelo que choca bajo su centro (como los generadores):\nasi no flota sobre tiles cuya hierba empieza mas abajo del borde del tile. Hundir se suma." },
	};
#endif
	void Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_bSnapToGround_SetBit(void* Obj)
	{
		((FFramework2DPropInstance*)Obj)->bSnapToGround = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_bSnapToGround = { "bSnapToGround", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FFramework2DPropInstance), &Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_bSnapToGround_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_bSnapToGround_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_bSnapToGround_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_Scale_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "8.0" },
		{ "ClampMin", "0.1" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_Scale = { "Scale", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DPropInstance, Scale), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_Scale_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_Scale_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_PropId,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_Layer,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_X,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_Y,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_SinkPixels,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_bFlip,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_bHanging,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_bCoverTiles,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_bSnapToGround,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewProp_Scale,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_Framework2DTerrain,
		nullptr,
		&NewStructOps,
		"Framework2DPropInstance",
		sizeof(FFramework2DPropInstance),
		alignof(FFramework2DPropInstance),
		Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FFramework2DPropInstance()
	{
		if (!Z_Registration_Info_UScriptStruct_Framework2DPropInstance.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_Framework2DPropInstance.InnerSingleton, Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_Framework2DPropInstance.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_Framework2DBiomeProp;
class UScriptStruct* FFramework2DBiomeProp::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_Framework2DBiomeProp.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_Framework2DBiomeProp.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FFramework2DBiomeProp, Z_Construct_UPackage__Script_Framework2DTerrain(), TEXT("Framework2DBiomeProp"));
	}
	return Z_Registration_Info_UScriptStruct_Framework2DBiomeProp.OuterSingleton;
}
template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<FFramework2DBiomeProp>()
{
	return FFramework2DBiomeProp::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PropId_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_PropId;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Weight_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Weight;
		static const UECodeGen_Private::FBytePropertyParams NewProp_Depth_Underlying;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Depth_MetaData[];
#endif
		static const UECodeGen_Private::FEnumPropertyParams NewProp_Depth;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SinkPixels_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_SinkPixels;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bRandomFlip_MetaData[];
#endif
		static void NewProp_bRandomFlip_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bRandomFlip;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/** Un objeto grande que el generador reparte por el suelo del nivel. */" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Un objeto grande que el generador reparte por el suelo del nivel." },
	};
#endif
	void* Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFramework2DBiomeProp>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::NewProp_PropId_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Id del objeto en el Tile Set (Props).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Id del objeto en el Tile Set (Props)." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::NewProp_PropId = { "PropId", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiomeProp, PropId), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::NewProp_PropId_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::NewProp_PropId_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::NewProp_Weight_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMin", "0.0" },
		{ "Comment", "// Probabilidad relativa frente a los demas objetos del bioma.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Probabilidad relativa frente a los demas objetos del bioma." },
		{ "UIMax", "10.0" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::NewProp_Weight = { "Weight", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiomeProp, Weight), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::NewProp_Weight_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::NewProp_Weight_MetaData)) };
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::NewProp_Depth_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::NewProp_Depth_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::NewProp_Depth = { "Depth", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiomeProp, Depth), Z_Construct_UEnum_Framework2DTerrain_EFramework2DPropDepth, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::NewProp_Depth_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::NewProp_Depth_MetaData)) }; // 4215662271
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::NewProp_SinkPixels_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "64" },
		{ "ClampMin", "0" },
		{ "Comment", "// Pixeles que se hunde en el suelo (raices, base de la roca).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Pixeles que se hunde en el suelo (raices, base de la roca)." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::NewProp_SinkPixels = { "SinkPixels", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiomeProp, SinkPixels), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::NewProp_SinkPixels_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::NewProp_SinkPixels_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::NewProp_bRandomFlip_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Voltear en horizontal la mitad, al azar.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Voltear en horizontal la mitad, al azar." },
	};
#endif
	void Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::NewProp_bRandomFlip_SetBit(void* Obj)
	{
		((FFramework2DBiomeProp*)Obj)->bRandomFlip = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::NewProp_bRandomFlip = { "bRandomFlip", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FFramework2DBiomeProp), &Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::NewProp_bRandomFlip_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::NewProp_bRandomFlip_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::NewProp_bRandomFlip_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::NewProp_PropId,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::NewProp_Weight,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::NewProp_Depth_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::NewProp_Depth,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::NewProp_SinkPixels,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::NewProp_bRandomFlip,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_Framework2DTerrain,
		nullptr,
		&NewStructOps,
		"Framework2DBiomeProp",
		sizeof(FFramework2DBiomeProp),
		alignof(FFramework2DBiomeProp),
		Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FFramework2DBiomeProp()
	{
		if (!Z_Registration_Info_UScriptStruct_Framework2DBiomeProp.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_Framework2DBiomeProp.InnerSingleton, Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_Framework2DBiomeProp.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_Framework2DBiomeBlock;
class UScriptStruct* FFramework2DBiomeBlock::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_Framework2DBiomeBlock.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_Framework2DBiomeBlock.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FFramework2DBiomeBlock, Z_Construct_UPackage__Script_Framework2DTerrain(), TEXT("Framework2DBiomeBlock"));
	}
	return Z_Registration_Info_UScriptStruct_Framework2DBiomeBlock.OuterSingleton;
}
template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<FFramework2DBiomeBlock>()
{
	return FFramework2DBiomeBlock::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FFramework2DBiomeBlock_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Tile_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Tile;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Width_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Width;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Height_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Height;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Weight_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Weight;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiomeBlock_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * Un BLOQUE del atlas (varios tiles juntos) que sustituye a un trozo del terreno ya autotileado:\n * en la superficie (la fila de arriba del bloque va en la de arriba del suelo llano) o en el\n * interior (todo el bloque cae sobre casillas del centro). Rompe la repeticion con piezas grandes.\n */" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Un BLOQUE del atlas (varios tiles juntos) que sustituye a un trozo del terreno ya autotileado:\nen la superficie (la fila de arriba del bloque va en la de arriba del suelo llano) o en el\ninterior (todo el bloque cae sobre casillas del centro). Rompe la repeticion con piezas grandes." },
	};
#endif
	void* Z_Construct_UScriptStruct_FFramework2DBiomeBlock_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFramework2DBiomeBlock>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiomeBlock_Statics::NewProp_Tile_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Tile de arriba-izquierda del bloque (valor de tile: pagina + numero).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Tile de arriba-izquierda del bloque (valor de tile: pagina + numero)." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiomeBlock_Statics::NewProp_Tile = { "Tile", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiomeBlock, Tile), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiomeBlock_Statics::NewProp_Tile_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiomeBlock_Statics::NewProp_Tile_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiomeBlock_Statics::NewProp_Width_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "16" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiomeBlock_Statics::NewProp_Width = { "Width", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiomeBlock, Width), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiomeBlock_Statics::NewProp_Width_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiomeBlock_Statics::NewProp_Width_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiomeBlock_Statics::NewProp_Height_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "16" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiomeBlock_Statics::NewProp_Height = { "Height", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiomeBlock, Height), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiomeBlock_Statics::NewProp_Height_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiomeBlock_Statics::NewProp_Height_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiomeBlock_Statics::NewProp_Weight_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMin", "0.0" },
		{ "Comment", "// Probabilidad relativa frente a los demas bloques de la misma lista.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Probabilidad relativa frente a los demas bloques de la misma lista." },
		{ "UIMax", "10.0" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DBiomeBlock_Statics::NewProp_Weight = { "Weight", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiomeBlock, Weight), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiomeBlock_Statics::NewProp_Weight_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiomeBlock_Statics::NewProp_Weight_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FFramework2DBiomeBlock_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiomeBlock_Statics::NewProp_Tile,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiomeBlock_Statics::NewProp_Width,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiomeBlock_Statics::NewProp_Height,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiomeBlock_Statics::NewProp_Weight,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFramework2DBiomeBlock_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_Framework2DTerrain,
		nullptr,
		&NewStructOps,
		"Framework2DBiomeBlock",
		sizeof(FFramework2DBiomeBlock),
		alignof(FFramework2DBiomeBlock),
		Z_Construct_UScriptStruct_FFramework2DBiomeBlock_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiomeBlock_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiomeBlock_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiomeBlock_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FFramework2DBiomeBlock()
	{
		if (!Z_Registration_Info_UScriptStruct_Framework2DBiomeBlock.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_Framework2DBiomeBlock.InnerSingleton, Z_Construct_UScriptStruct_FFramework2DBiomeBlock_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_Framework2DBiomeBlock.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_Framework2DBiomeGiantTree;
class UScriptStruct* FFramework2DBiomeGiantTree::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_Framework2DBiomeGiantTree.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_Framework2DBiomeGiantTree.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree, Z_Construct_UPackage__Script_Framework2DTerrain(), TEXT("Framework2DBiomeGiantTree"));
	}
	return Z_Registration_Info_UScriptStruct_Framework2DBiomeGiantTree.OuterSingleton;
}
template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<FFramework2DBiomeGiantTree>()
{
	return FFramework2DBiomeGiantTree::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TrunkTile_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_TrunkTile;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TrunkWidth_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_TrunkWidth;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TrunkHeight_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_TrunkHeight;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BranchTile_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_BranchTile;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BranchWidth_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_BranchWidth;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BranchHeight_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_BranchHeight;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BranchOffset_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_BranchOffset;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CrownPropId_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_CrownPropId;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_LeafPropId_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_LeafPropId;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MinHeight_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_MinHeight;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MaxHeight_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_MaxHeight;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Weight_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Weight;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * Un ARBOL GIGANTE (capa de detras: no choca). De abajo arriba: el TRONCO (su bloque se repite),\n * las RAMAS (un bloque centrado que asoma bajo la copa) y la COPA, hecha con dos objetos grandes\n * del Tile Set: la copa de arriba y el FOLLAJE (algo redondo, como un arbusto) que se repite\n * alrededor y debajo de ella para darle volumen y tapar su borde de abajo. Todo con variacion.\n */" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Un ARBOL GIGANTE (capa de detras: no choca). De abajo arriba: el TRONCO (su bloque se repite),\nlas RAMAS (un bloque centrado que asoma bajo la copa) y la COPA, hecha con dos objetos grandes\ndel Tile Set: la copa de arriba y el FOLLAJE (algo redondo, como un arbusto) que se repite\nalrededor y debajo de ella para darle volumen y tapar su borde de abajo. Todo con variacion." },
	};
#endif
	void* Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFramework2DBiomeGiantTree>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_TrunkTile_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Tronco: tile de arriba-izquierda y tamano en tiles (se repite en vertical).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Tronco: tile de arriba-izquierda y tamano en tiles (se repite en vertical)." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_TrunkTile = { "TrunkTile", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiomeGiantTree, TrunkTile), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_TrunkTile_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_TrunkTile_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_TrunkWidth_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "16" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_TrunkWidth = { "TrunkWidth", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiomeGiantTree, TrunkWidth), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_TrunkWidth_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_TrunkWidth_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_TrunkHeight_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "32" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_TrunkHeight = { "TrunkHeight", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiomeGiantTree, TrunkHeight), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_TrunkHeight_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_TrunkHeight_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_BranchTile_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Ramas (opcional): bloque sobre el tronco que asoma bajo la copa, al menos tan ancho como el\n// tronco (si no, no se ponen). Centrado salvo que BranchOffset diga otra cosa.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Ramas (opcional): bloque sobre el tronco que asoma bajo la copa, al menos tan ancho como el\ntronco (si no, no se ponen). Centrado salvo que BranchOffset diga otra cosa." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_BranchTile = { "BranchTile", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiomeGiantTree, BranchTile), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_BranchTile_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_BranchTile_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_BranchWidth_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "16" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_BranchWidth = { "BranchWidth", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiomeGiantTree, BranchWidth), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_BranchWidth_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_BranchWidth_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_BranchHeight_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "16" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_BranchHeight = { "BranchHeight", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiomeGiantTree, BranchHeight), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_BranchHeight_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_BranchHeight_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_BranchOffset_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "15" },
		{ "ClampMin", "-1" },
		{ "Comment", "// Columnas de las ramas que quedan a la izquierda del tronco (-1 = centradas; si sobra una\n// columna, a la derecha).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Columnas de las ramas que quedan a la izquierda del tronco (-1 = centradas; si sobra una\ncolumna, a la derecha)." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_BranchOffset = { "BranchOffset", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiomeGiantTree, BranchOffset), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_BranchOffset_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_BranchOffset_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_CrownPropId_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Copa: Id de un objeto grande del Tile Set (Props). Sin copa ni follaje no hay arbol.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Copa: Id de un objeto grande del Tile Set (Props). Sin copa ni follaje no hay arbol." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_CrownPropId = { "CrownPropId", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiomeGiantTree, CrownPropId), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_CrownPropId_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_CrownPropId_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_LeafPropId_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Follaje: Id de un objeto grande redondo (un arbusto) que se repite alrededor y debajo de la copa.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Follaje: Id de un objeto grande redondo (un arbusto) que se repite alrededor y debajo de la copa." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_LeafPropId = { "LeafPropId", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiomeGiantTree, LeafPropId), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_LeafPropId_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_LeafPropId_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_MinHeight_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "128" },
		{ "ClampMin", "2" },
		{ "Comment", "// Altura del arbol (tiles, del suelo a la parte de abajo de la copa): al azar entre las dos.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Altura del arbol (tiles, del suelo a la parte de abajo de la copa): al azar entre las dos." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_MinHeight = { "MinHeight", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiomeGiantTree, MinHeight), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_MinHeight_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_MinHeight_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_MaxHeight_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "128" },
		{ "ClampMin", "2" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_MaxHeight = { "MaxHeight", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiomeGiantTree, MaxHeight), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_MaxHeight_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_MaxHeight_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_Weight_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "UIMax", "10.0" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_Weight = { "Weight", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiomeGiantTree, Weight), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_Weight_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_Weight_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_TrunkTile,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_TrunkWidth,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_TrunkHeight,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_BranchTile,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_BranchWidth,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_BranchHeight,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_BranchOffset,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_CrownPropId,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_LeafPropId,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_MinHeight,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_MaxHeight,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewProp_Weight,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_Framework2DTerrain,
		nullptr,
		&NewStructOps,
		"Framework2DBiomeGiantTree",
		sizeof(FFramework2DBiomeGiantTree),
		alignof(FFramework2DBiomeGiantTree),
		Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree()
	{
		if (!Z_Registration_Info_UScriptStruct_Framework2DBiomeGiantTree.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_Framework2DBiomeGiantTree.InnerSingleton, Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_Framework2DBiomeGiantTree.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_Framework2DBiomeDecoration;
class UScriptStruct* FFramework2DBiomeDecoration::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_Framework2DBiomeDecoration.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_Framework2DBiomeDecoration.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FFramework2DBiomeDecoration, Z_Construct_UPackage__Script_Framework2DTerrain(), TEXT("Framework2DBiomeDecoration"));
	}
	return Z_Registration_Info_UScriptStruct_Framework2DBiomeDecoration.OuterSingleton;
}
template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<FFramework2DBiomeDecoration>()
{
	return FFramework2DBiomeDecoration::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FFramework2DBiomeDecoration_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Value_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Value;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Weight_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Weight;
		static const UECodeGen_Private::FBytePropertyParams NewProp_Placement_Underlying;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Placement_MetaData[];
#endif
		static const UECodeGen_Private::FEnumPropertyParams NewProp_Placement;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiomeDecoration_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/** Un adorno que el generador reparte por el nivel. */" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Un adorno que el generador reparte por el nivel." },
	};
#endif
	void* Z_Construct_UScriptStruct_FFramework2DBiomeDecoration_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFramework2DBiomeDecoration>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiomeDecoration_Statics::NewProp_Value_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Tile, flipbook (antorcha, flor animada...) o generador de vegetacion.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Tile, flipbook (antorcha, flor animada...) o generador de vegetacion." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiomeDecoration_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiomeDecoration, Value), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiomeDecoration_Statics::NewProp_Value_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiomeDecoration_Statics::NewProp_Value_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiomeDecoration_Statics::NewProp_Weight_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMin", "0.0" },
		{ "Comment", "// Probabilidad relativa frente a los demas adornos del mismo sitio (suelo o techo).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Probabilidad relativa frente a los demas adornos del mismo sitio (suelo o techo)." },
		{ "UIMax", "10.0" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DBiomeDecoration_Statics::NewProp_Weight = { "Weight", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiomeDecoration, Weight), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiomeDecoration_Statics::NewProp_Weight_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiomeDecoration_Statics::NewProp_Weight_MetaData)) };
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FFramework2DBiomeDecoration_Statics::NewProp_Placement_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiomeDecoration_Statics::NewProp_Placement_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FFramework2DBiomeDecoration_Statics::NewProp_Placement = { "Placement", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiomeDecoration, Placement), Z_Construct_UEnum_Framework2DTerrain_EFramework2DDecorPlacement, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiomeDecoration_Statics::NewProp_Placement_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiomeDecoration_Statics::NewProp_Placement_MetaData)) }; // 471993281
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FFramework2DBiomeDecoration_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiomeDecoration_Statics::NewProp_Value,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiomeDecoration_Statics::NewProp_Weight,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiomeDecoration_Statics::NewProp_Placement_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiomeDecoration_Statics::NewProp_Placement,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFramework2DBiomeDecoration_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_Framework2DTerrain,
		nullptr,
		&NewStructOps,
		"Framework2DBiomeDecoration",
		sizeof(FFramework2DBiomeDecoration),
		alignof(FFramework2DBiomeDecoration),
		Z_Construct_UScriptStruct_FFramework2DBiomeDecoration_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiomeDecoration_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiomeDecoration_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiomeDecoration_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FFramework2DBiomeDecoration()
	{
		if (!Z_Registration_Info_UScriptStruct_Framework2DBiomeDecoration.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_Framework2DBiomeDecoration.InnerSingleton, Z_Construct_UScriptStruct_FFramework2DBiomeDecoration_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_Framework2DBiomeDecoration.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_Framework2DBiome;
class UScriptStruct* FFramework2DBiome::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_Framework2DBiome.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_Framework2DBiome.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FFramework2DBiome, Z_Construct_UPackage__Script_Framework2DTerrain(), TEXT("Framework2DBiome"));
	}
	return Z_Registration_Info_UScriptStruct_Framework2DBiome.OuterSingleton;
}
template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<FFramework2DBiome>()
{
	return FFramework2DBiome::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FFramework2DBiome_Statics
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
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Id_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Id;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Ground_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Ground;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Ground5_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Ground5;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GroundDeep_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_GroundDeep;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InnerCorners_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_InnerCorners;
		static const UECodeGen_Private::FIntPropertyParams NewProp_CenterVariants_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CenterVariants_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_CenterVariants;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_RampUp_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_RampUp;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_RampDown_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_RampDown;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GentleUpLow_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_GentleUpLow;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GentleUpHigh_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_GentleUpHigh;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GentleDownHigh_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_GentleDownHigh;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GentleDownLow_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_GentleDownLow;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PlatformLeft_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_PlatformLeft;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PlatformMiddle_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_PlatformMiddle;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PlatformRight_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_PlatformRight;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Background_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Background;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_WaterSurface_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_WaterSurface;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_WaterBody_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_WaterBody;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_WaterCrest_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_WaterCrest;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_WaterfallTop_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_WaterfallTop;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_WaterfallBody_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_WaterfallBody;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_WaterfallBottom_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_WaterfallBottom;
		static const UECodeGen_Private::FStructPropertyParams NewProp_Decorations_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Decorations_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Decorations;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BridgeLeft_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_BridgeLeft;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BridgeMiddle_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_BridgeMiddle;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BridgeRight_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_BridgeRight;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BridgeCapLeft_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_BridgeCapLeft;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BridgeCapMiddle_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_BridgeCapMiddle;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BridgeCapRight_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_BridgeCapRight;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BridgePostLeftLow_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_BridgePostLeftLow;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BridgePostLeftHigh_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_BridgePostLeftHigh;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BridgePostRightLow_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_BridgePostRightLow;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BridgePostRightHigh_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_BridgePostRightHigh;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_EdgeTop_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_EdgeTop;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_EdgeBottom_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_EdgeBottom;
		static const UECodeGen_Private::FStructPropertyParams NewProp_Backdrops_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Backdrops_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Backdrops;
		static const UECodeGen_Private::FStructPropertyParams NewProp_Props_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Props_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Props;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_WallFootLeft_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_WallFootLeft;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_WallFootLeftInner_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_WallFootLeftInner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_WallFootRight_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_WallFootRight;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_WallFootRightInner_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_WallFootRightInner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PlatformCapLeft_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_PlatformCapLeft;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PlatformCapMiddle_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_PlatformCapMiddle;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PlatformCapRight_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_PlatformCapRight;
		static const UECodeGen_Private::FStructPropertyParams NewProp_SurfaceBlocks_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SurfaceBlocks_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_SurfaceBlocks;
		static const UECodeGen_Private::FStructPropertyParams NewProp_InteriorBlocks_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InteriorBlocks_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_InteriorBlocks;
		static const UECodeGen_Private::FStructPropertyParams NewProp_GiantTrees_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GiantTrees_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_GiantTrees;
		static const UECodeGen_Private::FStructPropertyParams NewProp_BackgroundCaps_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BackgroundCaps_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_BackgroundCaps;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * Un BIOMA: las piezas con las que el generador procedural construye un nivel (bosque, cueva,\n * desierto...). Se guardan en el Tile Set y se editan en la pestana \"Generar\" del panel.\n */" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Un BIOMA: las piezas con las que el generador procedural construye un nivel (bosque, cueva,\ndesierto...). Se guardan en el Tile Set y se editan en la pestana \"Generar\" del panel." },
	};
#endif
	void* Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFramework2DBiome>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Name_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Nombre que se ve en el panel.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Nombre que se ve en el panel." },
	};
#endif
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, Name), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Name_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Name_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Id_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Identificador estable que guardan las recetas de los mapas. No lo cambies a mano.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Identificador estable que guardan las recetas de los mapas. No lo cambies a mano." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Id = { "Id", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, Id), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Id_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Id_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Ground_MetaData[] = {
		{ "Category", "Framework2D|Terreno" },
		{ "Comment", "// El terreno 3x3 (obligatorio al menos el centro, o el del 5x5).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "El terreno 3x3 (obligatorio al menos el centro, o el del 5x5)." },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Ground = { "Ground", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, Ground), Z_Construct_UScriptStruct_FFramework2DTile3x3, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Ground_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Ground_MetaData)) }; // 4088922689
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Ground5_MetaData[] = {
		{ "Category", "Framework2D|Terreno" },
		{ "Comment", "// Terreno 5x5 (opcional): bordes de dos tiles de grosor. Con su centro, se usa en vez del 3x3.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Terreno 5x5 (opcional): bordes de dos tiles de grosor. Con su centro, se usa en vez del 3x3." },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Ground5 = { "Ground5", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, Ground5), Z_Construct_UScriptStruct_FFramework2DTile5x5, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Ground5_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Ground5_MetaData)) }; // 3607507704
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_GroundDeep_MetaData[] = {
		{ "Category", "Framework2D|Terreno" },
		{ "Comment", "// Interior profundo (opcional, con el 5x5): lo que va mas adentro que las filas del 5x5 (a 4 o\n// mas casillas del aire por arriba). Para tilesets cuyo centro es una franja (rocas bajo la\n// hierba) y lo de debajo es liso. Sin el, el centro del 5x5.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Interior profundo (opcional, con el 5x5): lo que va mas adentro que las filas del 5x5 (a 4 o\nmas casillas del aire por arriba). Para tilesets cuyo centro es una franja (rocas bajo la\nhierba) y lo de debajo es liso. Sin el, el centro del 5x5." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_GroundDeep = { "GroundDeep", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, GroundDeep), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_GroundDeep_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_GroundDeep_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_InnerCorners_MetaData[] = {
		{ "Category", "Framework2D|Terreno" },
		{ "Comment", "// Esquinas interiores (opcional).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Esquinas interiores (opcional)." },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_InnerCorners = { "InnerCorners", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, InnerCorners), Z_Construct_UScriptStruct_FFramework2DInnerCorners, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_InnerCorners_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_InnerCorners_MetaData)) }; // 2550555143
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_CenterVariants_Inner = { "CenterVariants", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_CenterVariants_MetaData[] = {
		{ "Category", "Framework2D|Terreno" },
		{ "Comment", "// Variantes del centro (opcional): se mezclan al azar con el centro para que no se repita.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Variantes del centro (opcional): se mezclan al azar con el centro para que no se repita." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_CenterVariants = { "CenterVariants", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, CenterVariants), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_CenterVariants_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_CenterVariants_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_RampUp_MetaData[] = {
		{ "Category", "Framework2D|Rampas" },
		{ "Comment", "// Rampa de 45 grados que sube hacia la derecha ( / ). Un tile por cada tile de altura.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Rampa de 45 grados que sube hacia la derecha ( / ). Un tile por cada tile de altura." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_RampUp = { "RampUp", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, RampUp), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_RampUp_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_RampUp_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_RampDown_MetaData[] = {
		{ "Category", "Framework2D|Rampas" },
		{ "Comment", "// Rampa de 45 grados que baja hacia la derecha ( \\ ).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Rampa de 45 grados que baja hacia la derecha ( \\ )." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_RampDown = { "RampDown", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, RampDown), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_RampDown_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_RampDown_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_GentleUpLow_MetaData[] = {
		{ "Category", "Framework2D|Rampas" },
		{ "Comment", "// Rampa suave que sube (dos tiles por cada tile de altura): la mitad baja y la alta.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Rampa suave que sube (dos tiles por cada tile de altura): la mitad baja y la alta." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_GentleUpLow = { "GentleUpLow", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, GentleUpLow), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_GentleUpLow_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_GentleUpLow_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_GentleUpHigh_MetaData[] = {
		{ "Category", "Framework2D|Rampas" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_GentleUpHigh = { "GentleUpHigh", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, GentleUpHigh), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_GentleUpHigh_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_GentleUpHigh_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_GentleDownHigh_MetaData[] = {
		{ "Category", "Framework2D|Rampas" },
		{ "Comment", "// Rampa suave que baja: primero la mitad alta y luego la baja.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Rampa suave que baja: primero la mitad alta y luego la baja." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_GentleDownHigh = { "GentleDownHigh", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, GentleDownHigh), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_GentleDownHigh_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_GentleDownHigh_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_GentleDownLow_MetaData[] = {
		{ "Category", "Framework2D|Rampas" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_GentleDownLow = { "GentleDownLow", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, GentleDownLow), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_GentleDownLow_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_GentleDownLow_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_PlatformLeft_MetaData[] = {
		{ "Category", "Framework2D|Plataformas" },
		{ "Comment", "// Plataformas flotantes (opcional): extremo izquierdo, tramo y extremo derecho. Sin ellas,\n// las plataformas usan la fila de arriba del terreno 3x3.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Plataformas flotantes (opcional): extremo izquierdo, tramo y extremo derecho. Sin ellas,\nlas plataformas usan la fila de arriba del terreno 3x3." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_PlatformLeft = { "PlatformLeft", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, PlatformLeft), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_PlatformLeft_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_PlatformLeft_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_PlatformMiddle_MetaData[] = {
		{ "Category", "Framework2D|Plataformas" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_PlatformMiddle = { "PlatformMiddle", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, PlatformMiddle), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_PlatformMiddle_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_PlatformMiddle_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_PlatformRight_MetaData[] = {
		{ "Category", "Framework2D|Plataformas" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_PlatformRight = { "PlatformRight", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, PlatformRight), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_PlatformRight_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_PlatformRight_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Background_MetaData[] = {
		{ "Category", "Framework2D|Fondo" },
		{ "Comment", "// Fondo (opcional): pared trasera y colinas detras del terreno. Se ve al picar. Con solo\n// el centro, todo el fondo es esa pieza.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Fondo (opcional): pared trasera y colinas detras del terreno. Se ve al picar. Con solo\nel centro, todo el fondo es esa pieza." },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Background = { "Background", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, Background), Z_Construct_UScriptStruct_FFramework2DTile3x3, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Background_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Background_MetaData)) }; // 4088922689
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WaterSurface_MetaData[] = {
		{ "Category", "Framework2D|Agua" },
		{ "Comment", "// Agua (opcional; suelen ser flipbooks): la fila de arriba de cada lago y el resto.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Agua (opcional; suelen ser flipbooks): la fila de arriba de cada lago y el resto." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WaterSurface = { "WaterSurface", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, WaterSurface), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WaterSurface_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WaterSurface_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WaterBody_MetaData[] = {
		{ "Category", "Framework2D|Agua" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WaterBody = { "WaterBody", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, WaterBody), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WaterBody_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WaterBody_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WaterCrest_MetaData[] = {
		{ "Category", "Framework2D|Agua" },
		{ "Comment", "// Olas (opcional): lo que asoma por ENCIMA de la superficie del agua (va en la casilla de encima).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Olas (opcional): lo que asoma por ENCIMA de la superficie del agua (va en la casilla de encima)." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WaterCrest = { "WaterCrest", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, WaterCrest), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WaterCrest_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WaterCrest_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WaterfallTop_MetaData[] = {
		{ "Category", "Framework2D|Agua" },
		{ "Comment", "// Cascada (opcional; suelen ser flipbooks): el borde de arriba, la caida y la espuma de abajo.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Cascada (opcional; suelen ser flipbooks): el borde de arriba, la caida y la espuma de abajo." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WaterfallTop = { "WaterfallTop", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, WaterfallTop), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WaterfallTop_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WaterfallTop_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WaterfallBody_MetaData[] = {
		{ "Category", "Framework2D|Agua" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WaterfallBody = { "WaterfallBody", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, WaterfallBody), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WaterfallBody_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WaterfallBody_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WaterfallBottom_MetaData[] = {
		{ "Category", "Framework2D|Agua" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WaterfallBottom = { "WaterfallBottom", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, WaterfallBottom), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WaterfallBottom_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WaterfallBottom_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Decorations_Inner = { "Decorations", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FFramework2DBiomeDecoration, METADATA_PARAMS(nullptr, 0) }; // 2717470893
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Decorations_MetaData[] = {
		{ "Category", "Framework2D|Decoracion" },
		{ "Comment", "// Adornos que se reparten por el suelo (o cuelgan del techo).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "TitleProperty", "Value" },
		{ "ToolTip", "Adornos que se reparten por el suelo (o cuelgan del techo)." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Decorations = { "Decorations", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, Decorations), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Decorations_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Decorations_MetaData)) }; // 2717470893
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgeLeft_MetaData[] = {
		{ "Category", "Framework2D|Puentes" },
		{ "Comment", "// Puentes (opcional): sobre fosos, lagos y valles estrechos entre dos orillas a la misma\n// altura. Extremo izquierdo, tablas y extremo derecho; sin extremos, todo son tablas.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Puentes (opcional): sobre fosos, lagos y valles estrechos entre dos orillas a la misma\naltura. Extremo izquierdo, tablas y extremo derecho; sin extremos, todo son tablas." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgeLeft = { "BridgeLeft", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, BridgeLeft), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgeLeft_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgeLeft_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgeMiddle_MetaData[] = {
		{ "Category", "Framework2D|Puentes" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgeMiddle = { "BridgeMiddle", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, BridgeMiddle), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgeMiddle_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgeMiddle_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgeRight_MetaData[] = {
		{ "Category", "Framework2D|Puentes" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgeRight = { "BridgeRight", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, BridgeRight), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgeRight_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgeRight_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgeCapLeft_MetaData[] = {
		{ "Category", "Framework2D|Puentes" },
		{ "Comment", "// Canto del puente (opcional, con el 5x5): encima de las tablas, en la capa de bordes (el borde\n// claro de las tablas y el arranque de las cuerdas). Extremo izquierdo, tramo y extremo derecho.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Canto del puente (opcional, con el 5x5): encima de las tablas, en la capa de bordes (el borde\nclaro de las tablas y el arranque de las cuerdas). Extremo izquierdo, tramo y extremo derecho." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgeCapLeft = { "BridgeCapLeft", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, BridgeCapLeft), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgeCapLeft_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgeCapLeft_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgeCapMiddle_MetaData[] = {
		{ "Category", "Framework2D|Puentes" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgeCapMiddle = { "BridgeCapMiddle", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, BridgeCapMiddle), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgeCapMiddle_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgeCapMiddle_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgeCapRight_MetaData[] = {
		{ "Category", "Framework2D|Puentes" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgeCapRight = { "BridgeCapRight", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, BridgeCapRight), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgeCapRight_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgeCapRight_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgePostLeftLow_MetaData[] = {
		{ "Category", "Framework2D|Puentes" },
		{ "Comment", "// Postes de los extremos del puente (opcional): la casilla de encima de cada extremo (abajo) y\n// la de encima de esa (arriba). Son decoracion: no chocan.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Postes de los extremos del puente (opcional): la casilla de encima de cada extremo (abajo) y\nla de encima de esa (arriba). Son decoracion: no chocan." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgePostLeftLow = { "BridgePostLeftLow", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, BridgePostLeftLow), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgePostLeftLow_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgePostLeftLow_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgePostLeftHigh_MetaData[] = {
		{ "Category", "Framework2D|Puentes" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgePostLeftHigh = { "BridgePostLeftHigh", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, BridgePostLeftHigh), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgePostLeftHigh_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgePostLeftHigh_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgePostRightLow_MetaData[] = {
		{ "Category", "Framework2D|Puentes" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgePostRightLow = { "BridgePostRightLow", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, BridgePostRightLow), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgePostRightLow_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgePostRightLow_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgePostRightHigh_MetaData[] = {
		{ "Category", "Framework2D|Puentes" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgePostRightHigh = { "BridgePostRightHigh", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, BridgePostRightHigh), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgePostRightHigh_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgePostRightHigh_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_EdgeTop_MetaData[] = {
		{ "Category", "Framework2D|Bordes" },
		{ "Comment", "// Bordes naturales (opcional; suelen ser generadores): lo que se pone encima de CADA borde de\n// arriba del terreno (franja de hierba o musgo que tapa la linea recta de los tiles) y debajo\n// de cada borde de abajo (rocas o raices bajo islas y salientes: generador con \"Colgar del techo\").\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Bordes naturales (opcional; suelen ser generadores): lo que se pone encima de CADA borde de\narriba del terreno (franja de hierba o musgo que tapa la linea recta de los tiles) y debajo\nde cada borde de abajo (rocas o raices bajo islas y salientes: generador con \"Colgar del techo\")." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_EdgeTop = { "EdgeTop", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, EdgeTop), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_EdgeTop_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_EdgeTop_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_EdgeBottom_MetaData[] = {
		{ "Category", "Framework2D|Bordes" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_EdgeBottom = { "EdgeBottom", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, EdgeBottom), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_EdgeBottom_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_EdgeBottom_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Backdrops_Inner = { "Backdrops", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FFramework2DBackdropLayer, METADATA_PARAMS(nullptr, 0) }; // 3674502919
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Backdrops_MetaData[] = {
		{ "Category", "Framework2D|Fondo" },
		{ "Comment", "// Fondos parallax (cielo, montanas, bosque lejano...), de atras a delante. Al generar se copian\n// al Tile Map.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "TitleProperty", "Name" },
		{ "ToolTip", "Fondos parallax (cielo, montanas, bosque lejano...), de atras a delante. Al generar se copian\nal Tile Map." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Backdrops = { "Backdrops", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, Backdrops), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Backdrops_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Backdrops_MetaData)) }; // 3674502919
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Props_Inner = { "Props", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FFramework2DBiomeProp, METADATA_PARAMS(nullptr, 0) }; // 3239512243
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Props_MetaData[] = {
		{ "Category", "Framework2D|Objetos" },
		{ "Comment", "// Objetos grandes (arboles, rocas...) que se reparten por el suelo.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Objetos grandes (arboles, rocas...) que se reparten por el suelo." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Props = { "Props", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, Props), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Props_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Props_MetaData)) }; // 3239512243
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WallFootLeft_MetaData[] = {
		{ "Category", "Framework2D|Terreno" },
		{ "Comment", "// Pie de pared (opcional, con el 5x5): donde un suelo llega a la pared de un escalon, la hierba\n// pasa por delante del pie de la pared. \"Izquierda\" = el suelo esta a la izquierda de la pared.\n// La pieza va en la primera columna de la pared, a la altura de la segunda fila del suelo, y la\n// de \"dentro\" en la columna siguiente (remata la hierba contra la roca).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Pie de pared (opcional, con el 5x5): donde un suelo llega a la pared de un escalon, la hierba\npasa por delante del pie de la pared. \"Izquierda\" = el suelo esta a la izquierda de la pared.\nLa pieza va en la primera columna de la pared, a la altura de la segunda fila del suelo, y la\nde \"dentro\" en la columna siguiente (remata la hierba contra la roca)." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WallFootLeft = { "WallFootLeft", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, WallFootLeft), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WallFootLeft_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WallFootLeft_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WallFootLeftInner_MetaData[] = {
		{ "Category", "Framework2D|Terreno" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WallFootLeftInner = { "WallFootLeftInner", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, WallFootLeftInner), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WallFootLeftInner_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WallFootLeftInner_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WallFootRight_MetaData[] = {
		{ "Category", "Framework2D|Terreno" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WallFootRight = { "WallFootRight", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, WallFootRight), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WallFootRight_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WallFootRight_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WallFootRightInner_MetaData[] = {
		{ "Category", "Framework2D|Terreno" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WallFootRightInner = { "WallFootRightInner", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, WallFootRightInner), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WallFootRightInner_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WallFootRightInner_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_PlatformCapLeft_MetaData[] = {
		{ "Category", "Framework2D|Plataformas" },
		{ "Comment", "// Remate de las plataformas (opcional, solo con piezas de plataforma): va encima de cada casilla\n// de plataforma, en la capa de bordes (el canto de un tablon que asoma por encima de su tile).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Remate de las plataformas (opcional, solo con piezas de plataforma): va encima de cada casilla\nde plataforma, en la capa de bordes (el canto de un tablon que asoma por encima de su tile)." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_PlatformCapLeft = { "PlatformCapLeft", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, PlatformCapLeft), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_PlatformCapLeft_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_PlatformCapLeft_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_PlatformCapMiddle_MetaData[] = {
		{ "Category", "Framework2D|Plataformas" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_PlatformCapMiddle = { "PlatformCapMiddle", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, PlatformCapMiddle), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_PlatformCapMiddle_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_PlatformCapMiddle_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_PlatformCapRight_MetaData[] = {
		{ "Category", "Framework2D|Plataformas" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_PlatformCapRight = { "PlatformCapRight", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, PlatformCapRight), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_PlatformCapRight_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_PlatformCapRight_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_SurfaceBlocks_Inner = { "SurfaceBlocks", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FFramework2DBiomeBlock, METADATA_PARAMS(nullptr, 0) }; // 1063392883
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_SurfaceBlocks_MetaData[] = {
		{ "Category", "Framework2D|Terreno" },
		{ "Comment", "// Bloques de la superficie (opcional): sustituyen las filas de arriba de un suelo llano.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Bloques de la superficie (opcional): sustituyen las filas de arriba de un suelo llano." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_SurfaceBlocks = { "SurfaceBlocks", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, SurfaceBlocks), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_SurfaceBlocks_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_SurfaceBlocks_MetaData)) }; // 1063392883
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_InteriorBlocks_Inner = { "InteriorBlocks", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FFramework2DBiomeBlock, METADATA_PARAMS(nullptr, 0) }; // 1063392883
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_InteriorBlocks_MetaData[] = {
		{ "Category", "Framework2D|Terreno" },
		{ "Comment", "// Bloques del interior (opcional): sustituyen un trozo del centro del terreno (pedruscos...).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Bloques del interior (opcional): sustituyen un trozo del centro del terreno (pedruscos...)." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_InteriorBlocks = { "InteriorBlocks", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, InteriorBlocks), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_InteriorBlocks_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_InteriorBlocks_MetaData)) }; // 1063392883
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_GiantTrees_Inner = { "GiantTrees", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree, METADATA_PARAMS(nullptr, 0) }; // 2501815260
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_GiantTrees_MetaData[] = {
		{ "Category", "Framework2D|Objetos" },
		{ "Comment", "// Arboles gigantes (opcional): troncos altos con copa, en la capa de detras.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Arboles gigantes (opcional): troncos altos con copa, en la capa de detras." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_GiantTrees = { "GiantTrees", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, GiantTrees), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_GiantTrees_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_GiantTrees_MetaData)) }; // 2501815260
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BackgroundCaps_Inner = { "BackgroundCaps", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FFramework2DBiomeProp, METADATA_PARAMS(nullptr, 0) }; // 3239512243
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BackgroundCaps_MetaData[] = {
		{ "Category", "Framework2D|Fondo" },
		{ "Comment", "// Copas del fondo (opcional): objetos grandes que se ponen a lo largo del borde de arriba del\n// fondo (cuando la receta lo hace asomar) y redondean sus colinas. Van en la capa de fondo.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Copas del fondo (opcional): objetos grandes que se ponen a lo largo del borde de arriba del\nfondo (cuando la receta lo hace asomar) y redondean sus colinas. Van en la capa de fondo." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BackgroundCaps = { "BackgroundCaps", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DBiome, BackgroundCaps), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BackgroundCaps_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BackgroundCaps_MetaData)) }; // 3239512243
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FFramework2DBiome_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Name,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Id,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Ground,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Ground5,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_GroundDeep,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_InnerCorners,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_CenterVariants_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_CenterVariants,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_RampUp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_RampDown,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_GentleUpLow,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_GentleUpHigh,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_GentleDownHigh,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_GentleDownLow,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_PlatformLeft,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_PlatformMiddle,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_PlatformRight,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Background,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WaterSurface,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WaterBody,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WaterCrest,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WaterfallTop,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WaterfallBody,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WaterfallBottom,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Decorations_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Decorations,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgeLeft,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgeMiddle,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgeRight,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgeCapLeft,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgeCapMiddle,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgeCapRight,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgePostLeftLow,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgePostLeftHigh,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgePostRightLow,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BridgePostRightHigh,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_EdgeTop,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_EdgeBottom,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Backdrops_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Backdrops,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Props_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_Props,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WallFootLeft,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WallFootLeftInner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WallFootRight,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_WallFootRightInner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_PlatformCapLeft,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_PlatformCapMiddle,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_PlatformCapRight,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_SurfaceBlocks_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_SurfaceBlocks,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_InteriorBlocks_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_InteriorBlocks,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_GiantTrees_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_GiantTrees,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BackgroundCaps_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewProp_BackgroundCaps,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFramework2DBiome_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_Framework2DTerrain,
		nullptr,
		&NewStructOps,
		"Framework2DBiome",
		sizeof(FFramework2DBiome),
		alignof(FFramework2DBiome),
		Z_Construct_UScriptStruct_FFramework2DBiome_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DBiome_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FFramework2DBiome()
	{
		if (!Z_Registration_Info_UScriptStruct_Framework2DBiome.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_Framework2DBiome.InnerSingleton, Z_Construct_UScriptStruct_FFramework2DBiome_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_Framework2DBiome.InnerSingleton;
	}
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_EFramework2DBiomeSlot;
	static UEnum* EFramework2DBiomeSlot_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_EFramework2DBiomeSlot.OuterSingleton)
		{
			Z_Registration_Info_UEnum_EFramework2DBiomeSlot.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_Framework2DTerrain_EFramework2DBiomeSlot, Z_Construct_UPackage__Script_Framework2DTerrain(), TEXT("EFramework2DBiomeSlot"));
		}
		return Z_Registration_Info_UEnum_EFramework2DBiomeSlot.OuterSingleton;
	}
	template<> FRAMEWORK2DTERRAIN_API UEnum* StaticEnum<EFramework2DBiomeSlot>()
	{
		return EFramework2DBiomeSlot_StaticEnum();
	}
	struct Z_Construct_UEnum_Framework2DTerrain_EFramework2DBiomeSlot_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_Framework2DTerrain_EFramework2DBiomeSlot_Statics::Enumerators[] = {
		{ "EFramework2DBiomeSlot::GroundTopLeft", (int64)EFramework2DBiomeSlot::GroundTopLeft },
		{ "EFramework2DBiomeSlot::GroundTop", (int64)EFramework2DBiomeSlot::GroundTop },
		{ "EFramework2DBiomeSlot::GroundTopRight", (int64)EFramework2DBiomeSlot::GroundTopRight },
		{ "EFramework2DBiomeSlot::GroundLeft", (int64)EFramework2DBiomeSlot::GroundLeft },
		{ "EFramework2DBiomeSlot::GroundCenter", (int64)EFramework2DBiomeSlot::GroundCenter },
		{ "EFramework2DBiomeSlot::GroundRight", (int64)EFramework2DBiomeSlot::GroundRight },
		{ "EFramework2DBiomeSlot::GroundBottomLeft", (int64)EFramework2DBiomeSlot::GroundBottomLeft },
		{ "EFramework2DBiomeSlot::GroundBottom", (int64)EFramework2DBiomeSlot::GroundBottom },
		{ "EFramework2DBiomeSlot::GroundBottomRight", (int64)EFramework2DBiomeSlot::GroundBottomRight },
		{ "EFramework2DBiomeSlot::InnerTopLeft", (int64)EFramework2DBiomeSlot::InnerTopLeft },
		{ "EFramework2DBiomeSlot::InnerTopRight", (int64)EFramework2DBiomeSlot::InnerTopRight },
		{ "EFramework2DBiomeSlot::InnerBottomLeft", (int64)EFramework2DBiomeSlot::InnerBottomLeft },
		{ "EFramework2DBiomeSlot::InnerBottomRight", (int64)EFramework2DBiomeSlot::InnerBottomRight },
		{ "EFramework2DBiomeSlot::RampUp", (int64)EFramework2DBiomeSlot::RampUp },
		{ "EFramework2DBiomeSlot::RampDown", (int64)EFramework2DBiomeSlot::RampDown },
		{ "EFramework2DBiomeSlot::GentleUpLow", (int64)EFramework2DBiomeSlot::GentleUpLow },
		{ "EFramework2DBiomeSlot::GentleUpHigh", (int64)EFramework2DBiomeSlot::GentleUpHigh },
		{ "EFramework2DBiomeSlot::GentleDownHigh", (int64)EFramework2DBiomeSlot::GentleDownHigh },
		{ "EFramework2DBiomeSlot::GentleDownLow", (int64)EFramework2DBiomeSlot::GentleDownLow },
		{ "EFramework2DBiomeSlot::PlatformLeft", (int64)EFramework2DBiomeSlot::PlatformLeft },
		{ "EFramework2DBiomeSlot::PlatformMiddle", (int64)EFramework2DBiomeSlot::PlatformMiddle },
		{ "EFramework2DBiomeSlot::PlatformRight", (int64)EFramework2DBiomeSlot::PlatformRight },
		{ "EFramework2DBiomeSlot::BackgroundTopLeft", (int64)EFramework2DBiomeSlot::BackgroundTopLeft },
		{ "EFramework2DBiomeSlot::BackgroundTop", (int64)EFramework2DBiomeSlot::BackgroundTop },
		{ "EFramework2DBiomeSlot::BackgroundTopRight", (int64)EFramework2DBiomeSlot::BackgroundTopRight },
		{ "EFramework2DBiomeSlot::BackgroundLeft", (int64)EFramework2DBiomeSlot::BackgroundLeft },
		{ "EFramework2DBiomeSlot::BackgroundCenter", (int64)EFramework2DBiomeSlot::BackgroundCenter },
		{ "EFramework2DBiomeSlot::BackgroundRight", (int64)EFramework2DBiomeSlot::BackgroundRight },
		{ "EFramework2DBiomeSlot::BackgroundBottomLeft", (int64)EFramework2DBiomeSlot::BackgroundBottomLeft },
		{ "EFramework2DBiomeSlot::BackgroundBottom", (int64)EFramework2DBiomeSlot::BackgroundBottom },
		{ "EFramework2DBiomeSlot::BackgroundBottomRight", (int64)EFramework2DBiomeSlot::BackgroundBottomRight },
		{ "EFramework2DBiomeSlot::WaterSurface", (int64)EFramework2DBiomeSlot::WaterSurface },
		{ "EFramework2DBiomeSlot::WaterBody", (int64)EFramework2DBiomeSlot::WaterBody },
		{ "EFramework2DBiomeSlot::WaterfallTop", (int64)EFramework2DBiomeSlot::WaterfallTop },
		{ "EFramework2DBiomeSlot::WaterfallBody", (int64)EFramework2DBiomeSlot::WaterfallBody },
		{ "EFramework2DBiomeSlot::WaterfallBottom", (int64)EFramework2DBiomeSlot::WaterfallBottom },
		{ "EFramework2DBiomeSlot::BridgeLeft", (int64)EFramework2DBiomeSlot::BridgeLeft },
		{ "EFramework2DBiomeSlot::BridgeMiddle", (int64)EFramework2DBiomeSlot::BridgeMiddle },
		{ "EFramework2DBiomeSlot::BridgeRight", (int64)EFramework2DBiomeSlot::BridgeRight },
		{ "EFramework2DBiomeSlot::EdgeTop", (int64)EFramework2DBiomeSlot::EdgeTop },
		{ "EFramework2DBiomeSlot::EdgeBottom", (int64)EFramework2DBiomeSlot::EdgeBottom },
		{ "EFramework2DBiomeSlot::WaterCrest", (int64)EFramework2DBiomeSlot::WaterCrest },
		{ "EFramework2DBiomeSlot::BridgePostLeftLow", (int64)EFramework2DBiomeSlot::BridgePostLeftLow },
		{ "EFramework2DBiomeSlot::BridgePostLeftHigh", (int64)EFramework2DBiomeSlot::BridgePostLeftHigh },
		{ "EFramework2DBiomeSlot::BridgePostRightLow", (int64)EFramework2DBiomeSlot::BridgePostRightLow },
		{ "EFramework2DBiomeSlot::BridgePostRightHigh", (int64)EFramework2DBiomeSlot::BridgePostRightHigh },
		{ "EFramework2DBiomeSlot::Ground5_00", (int64)EFramework2DBiomeSlot::Ground5_00 },
		{ "EFramework2DBiomeSlot::Ground5_01", (int64)EFramework2DBiomeSlot::Ground5_01 },
		{ "EFramework2DBiomeSlot::Ground5_02", (int64)EFramework2DBiomeSlot::Ground5_02 },
		{ "EFramework2DBiomeSlot::Ground5_03", (int64)EFramework2DBiomeSlot::Ground5_03 },
		{ "EFramework2DBiomeSlot::Ground5_04", (int64)EFramework2DBiomeSlot::Ground5_04 },
		{ "EFramework2DBiomeSlot::Ground5_10", (int64)EFramework2DBiomeSlot::Ground5_10 },
		{ "EFramework2DBiomeSlot::Ground5_11", (int64)EFramework2DBiomeSlot::Ground5_11 },
		{ "EFramework2DBiomeSlot::Ground5_12", (int64)EFramework2DBiomeSlot::Ground5_12 },
		{ "EFramework2DBiomeSlot::Ground5_13", (int64)EFramework2DBiomeSlot::Ground5_13 },
		{ "EFramework2DBiomeSlot::Ground5_14", (int64)EFramework2DBiomeSlot::Ground5_14 },
		{ "EFramework2DBiomeSlot::Ground5_20", (int64)EFramework2DBiomeSlot::Ground5_20 },
		{ "EFramework2DBiomeSlot::Ground5_21", (int64)EFramework2DBiomeSlot::Ground5_21 },
		{ "EFramework2DBiomeSlot::Ground5_22", (int64)EFramework2DBiomeSlot::Ground5_22 },
		{ "EFramework2DBiomeSlot::Ground5_23", (int64)EFramework2DBiomeSlot::Ground5_23 },
		{ "EFramework2DBiomeSlot::Ground5_24", (int64)EFramework2DBiomeSlot::Ground5_24 },
		{ "EFramework2DBiomeSlot::Ground5_30", (int64)EFramework2DBiomeSlot::Ground5_30 },
		{ "EFramework2DBiomeSlot::Ground5_31", (int64)EFramework2DBiomeSlot::Ground5_31 },
		{ "EFramework2DBiomeSlot::Ground5_32", (int64)EFramework2DBiomeSlot::Ground5_32 },
		{ "EFramework2DBiomeSlot::Ground5_33", (int64)EFramework2DBiomeSlot::Ground5_33 },
		{ "EFramework2DBiomeSlot::Ground5_34", (int64)EFramework2DBiomeSlot::Ground5_34 },
		{ "EFramework2DBiomeSlot::Ground5_40", (int64)EFramework2DBiomeSlot::Ground5_40 },
		{ "EFramework2DBiomeSlot::Ground5_41", (int64)EFramework2DBiomeSlot::Ground5_41 },
		{ "EFramework2DBiomeSlot::Ground5_42", (int64)EFramework2DBiomeSlot::Ground5_42 },
		{ "EFramework2DBiomeSlot::Ground5_43", (int64)EFramework2DBiomeSlot::Ground5_43 },
		{ "EFramework2DBiomeSlot::Ground5_44", (int64)EFramework2DBiomeSlot::Ground5_44 },
		{ "EFramework2DBiomeSlot::WallFootLeft", (int64)EFramework2DBiomeSlot::WallFootLeft },
		{ "EFramework2DBiomeSlot::WallFootLeftInner", (int64)EFramework2DBiomeSlot::WallFootLeftInner },
		{ "EFramework2DBiomeSlot::WallFootRight", (int64)EFramework2DBiomeSlot::WallFootRight },
		{ "EFramework2DBiomeSlot::WallFootRightInner", (int64)EFramework2DBiomeSlot::WallFootRightInner },
		{ "EFramework2DBiomeSlot::PlatformCapLeft", (int64)EFramework2DBiomeSlot::PlatformCapLeft },
		{ "EFramework2DBiomeSlot::PlatformCapMiddle", (int64)EFramework2DBiomeSlot::PlatformCapMiddle },
		{ "EFramework2DBiomeSlot::PlatformCapRight", (int64)EFramework2DBiomeSlot::PlatformCapRight },
		{ "EFramework2DBiomeSlot::GroundDeep", (int64)EFramework2DBiomeSlot::GroundDeep },
		{ "EFramework2DBiomeSlot::BridgeCapLeft", (int64)EFramework2DBiomeSlot::BridgeCapLeft },
		{ "EFramework2DBiomeSlot::BridgeCapMiddle", (int64)EFramework2DBiomeSlot::BridgeCapMiddle },
		{ "EFramework2DBiomeSlot::BridgeCapRight", (int64)EFramework2DBiomeSlot::BridgeCapRight },
		{ "EFramework2DBiomeSlot::Count", (int64)EFramework2DBiomeSlot::Count },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_Framework2DTerrain_EFramework2DBiomeSlot_Statics::Enum_MetaDataParams[] = {
		{ "BackgroundBottom.Name", "EFramework2DBiomeSlot::BackgroundBottom" },
		{ "BackgroundBottomLeft.Name", "EFramework2DBiomeSlot::BackgroundBottomLeft" },
		{ "BackgroundBottomRight.Name", "EFramework2DBiomeSlot::BackgroundBottomRight" },
		{ "BackgroundCenter.Name", "EFramework2DBiomeSlot::BackgroundCenter" },
		{ "BackgroundLeft.Name", "EFramework2DBiomeSlot::BackgroundLeft" },
		{ "BackgroundRight.Name", "EFramework2DBiomeSlot::BackgroundRight" },
		{ "BackgroundTop.Name", "EFramework2DBiomeSlot::BackgroundTop" },
		{ "BackgroundTopLeft.Name", "EFramework2DBiomeSlot::BackgroundTopLeft" },
		{ "BackgroundTopRight.Name", "EFramework2DBiomeSlot::BackgroundTopRight" },
		{ "BlueprintType", "true" },
		{ "BridgeCapLeft.Name", "EFramework2DBiomeSlot::BridgeCapLeft" },
		{ "BridgeCapMiddle.Name", "EFramework2DBiomeSlot::BridgeCapMiddle" },
		{ "BridgeCapRight.Name", "EFramework2DBiomeSlot::BridgeCapRight" },
		{ "BridgeLeft.Name", "EFramework2DBiomeSlot::BridgeLeft" },
		{ "BridgeMiddle.Name", "EFramework2DBiomeSlot::BridgeMiddle" },
		{ "BridgePostLeftHigh.Name", "EFramework2DBiomeSlot::BridgePostLeftHigh" },
		{ "BridgePostLeftLow.Name", "EFramework2DBiomeSlot::BridgePostLeftLow" },
		{ "BridgePostRightHigh.Name", "EFramework2DBiomeSlot::BridgePostRightHigh" },
		{ "BridgePostRightLow.Name", "EFramework2DBiomeSlot::BridgePostRightLow" },
		{ "BridgeRight.Name", "EFramework2DBiomeSlot::BridgeRight" },
		{ "Comment", "/**\n * Cada pieza suelta de un bioma, para editarlas una a una (panel, pruebas, Blueprint). Las\n * listas (variantes del centro y decoracion) se editan aparte.\n */" },
		{ "Count.Hidden", "" },
		{ "Count.Name", "EFramework2DBiomeSlot::Count" },
		{ "EdgeBottom.Name", "EFramework2DBiomeSlot::EdgeBottom" },
		{ "EdgeTop.Name", "EFramework2DBiomeSlot::EdgeTop" },
		{ "GentleDownHigh.Name", "EFramework2DBiomeSlot::GentleDownHigh" },
		{ "GentleDownLow.Name", "EFramework2DBiomeSlot::GentleDownLow" },
		{ "GentleUpHigh.Name", "EFramework2DBiomeSlot::GentleUpHigh" },
		{ "GentleUpLow.Name", "EFramework2DBiomeSlot::GentleUpLow" },
		{ "Ground5_00.Name", "EFramework2DBiomeSlot::Ground5_00" },
		{ "Ground5_01.Name", "EFramework2DBiomeSlot::Ground5_01" },
		{ "Ground5_02.Name", "EFramework2DBiomeSlot::Ground5_02" },
		{ "Ground5_03.Name", "EFramework2DBiomeSlot::Ground5_03" },
		{ "Ground5_04.Name", "EFramework2DBiomeSlot::Ground5_04" },
		{ "Ground5_10.Name", "EFramework2DBiomeSlot::Ground5_10" },
		{ "Ground5_11.Name", "EFramework2DBiomeSlot::Ground5_11" },
		{ "Ground5_12.Name", "EFramework2DBiomeSlot::Ground5_12" },
		{ "Ground5_13.Name", "EFramework2DBiomeSlot::Ground5_13" },
		{ "Ground5_14.Name", "EFramework2DBiomeSlot::Ground5_14" },
		{ "Ground5_20.Name", "EFramework2DBiomeSlot::Ground5_20" },
		{ "Ground5_21.Name", "EFramework2DBiomeSlot::Ground5_21" },
		{ "Ground5_22.Name", "EFramework2DBiomeSlot::Ground5_22" },
		{ "Ground5_23.Name", "EFramework2DBiomeSlot::Ground5_23" },
		{ "Ground5_24.Name", "EFramework2DBiomeSlot::Ground5_24" },
		{ "Ground5_30.Name", "EFramework2DBiomeSlot::Ground5_30" },
		{ "Ground5_31.Name", "EFramework2DBiomeSlot::Ground5_31" },
		{ "Ground5_32.Name", "EFramework2DBiomeSlot::Ground5_32" },
		{ "Ground5_33.Name", "EFramework2DBiomeSlot::Ground5_33" },
		{ "Ground5_34.Name", "EFramework2DBiomeSlot::Ground5_34" },
		{ "Ground5_40.Name", "EFramework2DBiomeSlot::Ground5_40" },
		{ "Ground5_41.Name", "EFramework2DBiomeSlot::Ground5_41" },
		{ "Ground5_42.Name", "EFramework2DBiomeSlot::Ground5_42" },
		{ "Ground5_43.Name", "EFramework2DBiomeSlot::Ground5_43" },
		{ "Ground5_44.Name", "EFramework2DBiomeSlot::Ground5_44" },
		{ "GroundBottom.Name", "EFramework2DBiomeSlot::GroundBottom" },
		{ "GroundBottomLeft.Name", "EFramework2DBiomeSlot::GroundBottomLeft" },
		{ "GroundBottomRight.Name", "EFramework2DBiomeSlot::GroundBottomRight" },
		{ "GroundCenter.Name", "EFramework2DBiomeSlot::GroundCenter" },
		{ "GroundDeep.Name", "EFramework2DBiomeSlot::GroundDeep" },
		{ "GroundLeft.Name", "EFramework2DBiomeSlot::GroundLeft" },
		{ "GroundRight.Name", "EFramework2DBiomeSlot::GroundRight" },
		{ "GroundTop.Name", "EFramework2DBiomeSlot::GroundTop" },
		{ "GroundTopLeft.Name", "EFramework2DBiomeSlot::GroundTopLeft" },
		{ "GroundTopRight.Name", "EFramework2DBiomeSlot::GroundTopRight" },
		{ "InnerBottomLeft.Name", "EFramework2DBiomeSlot::InnerBottomLeft" },
		{ "InnerBottomRight.Name", "EFramework2DBiomeSlot::InnerBottomRight" },
		{ "InnerTopLeft.Name", "EFramework2DBiomeSlot::InnerTopLeft" },
		{ "InnerTopRight.Name", "EFramework2DBiomeSlot::InnerTopRight" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "PlatformCapLeft.Name", "EFramework2DBiomeSlot::PlatformCapLeft" },
		{ "PlatformCapMiddle.Name", "EFramework2DBiomeSlot::PlatformCapMiddle" },
		{ "PlatformCapRight.Name", "EFramework2DBiomeSlot::PlatformCapRight" },
		{ "PlatformLeft.Name", "EFramework2DBiomeSlot::PlatformLeft" },
		{ "PlatformMiddle.Name", "EFramework2DBiomeSlot::PlatformMiddle" },
		{ "PlatformRight.Name", "EFramework2DBiomeSlot::PlatformRight" },
		{ "RampDown.Name", "EFramework2DBiomeSlot::RampDown" },
		{ "RampUp.Name", "EFramework2DBiomeSlot::RampUp" },
		{ "ToolTip", "Cada pieza suelta de un bioma, para editarlas una a una (panel, pruebas, Blueprint). Las\nlistas (variantes del centro y decoracion) se editan aparte." },
		{ "WallFootLeft.Name", "EFramework2DBiomeSlot::WallFootLeft" },
		{ "WallFootLeftInner.Name", "EFramework2DBiomeSlot::WallFootLeftInner" },
		{ "WallFootRight.Name", "EFramework2DBiomeSlot::WallFootRight" },
		{ "WallFootRightInner.Name", "EFramework2DBiomeSlot::WallFootRightInner" },
		{ "WaterBody.Name", "EFramework2DBiomeSlot::WaterBody" },
		{ "WaterCrest.Name", "EFramework2DBiomeSlot::WaterCrest" },
		{ "WaterfallBody.Name", "EFramework2DBiomeSlot::WaterfallBody" },
		{ "WaterfallBottom.Name", "EFramework2DBiomeSlot::WaterfallBottom" },
		{ "WaterfallTop.Name", "EFramework2DBiomeSlot::WaterfallTop" },
		{ "WaterSurface.Name", "EFramework2DBiomeSlot::WaterSurface" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_Framework2DTerrain_EFramework2DBiomeSlot_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_Framework2DTerrain,
		nullptr,
		"EFramework2DBiomeSlot",
		"EFramework2DBiomeSlot",
		Z_Construct_UEnum_Framework2DTerrain_EFramework2DBiomeSlot_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_Framework2DTerrain_EFramework2DBiomeSlot_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(Z_Construct_UEnum_Framework2DTerrain_EFramework2DBiomeSlot_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_Framework2DTerrain_EFramework2DBiomeSlot_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_Framework2DTerrain_EFramework2DBiomeSlot()
	{
		if (!Z_Registration_Info_UEnum_EFramework2DBiomeSlot.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EFramework2DBiomeSlot.InnerSingleton, Z_Construct_UEnum_Framework2DTerrain_EFramework2DBiomeSlot_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_EFramework2DBiomeSlot.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_Framework2DProcGenSettings;
class UScriptStruct* FFramework2DProcGenSettings::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_Framework2DProcGenSettings.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_Framework2DProcGenSettings.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FFramework2DProcGenSettings, Z_Construct_UPackage__Script_Framework2DTerrain(), TEXT("Framework2DProcGenSettings"));
	}
	return Z_Registration_Info_UScriptStruct_Framework2DProcGenSettings.OuterSingleton;
}
template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<FFramework2DProcGenSettings>()
{
	return FFramework2DProcGenSettings::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BiomeId_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_BiomeId;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Seed_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Seed;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Levels_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Levels;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_LevelHeight_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_LevelHeight;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BaseHeight_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_BaseHeight;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PlateauMinWidth_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_PlateauMinWidth;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PlateauMaxWidth_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_PlateauMaxWidth;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MaxLevelStep_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_MaxLevelStep;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_RampChance_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_RampChance;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GentleRampChance_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_GentleRampChance;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PitChance_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_PitChance;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PitDepth_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_PitDepth;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_LakeChance_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_LakeChance;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MaxLakeWidth_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_MaxLakeWidth;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_WaterfallChance_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_WaterfallChance;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PlatformChance_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_PlatformChance;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PlatformMinLength_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_PlatformMinLength;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PlatformMaxLength_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_PlatformMaxLength;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DecorationDensity_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_DecorationDensity;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DecorationSpacing_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_DecorationSpacing;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CenterVariantChance_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_CenterVariantChance;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bBackground_MetaData[];
#endif
		static void NewProp_bBackground_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bBackground;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BackgroundRise_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_BackgroundRise;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bEdgeWalls_MetaData[];
#endif
		static void NewProp_bEdgeWalls_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bEdgeWalls;
		static const UECodeGen_Private::FBytePropertyParams NewProp_ReliefStyle_Underlying;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ReliefStyle_MetaData[];
#endif
		static const UECodeGen_Private::FEnumPropertyParams NewProp_ReliefStyle;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Roughness_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Roughness;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_IslandChance_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_IslandChance;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_IslandMinWidth_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_IslandMinWidth;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_IslandMaxWidth_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_IslandMaxWidth;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BridgeChance_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_BridgeChance;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PropDensity_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_PropDensity;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PropSpacing_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_PropSpacing;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GiantTreeChance_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_GiantTreeChance;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GiantTreeSpacing_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_GiantTreeSpacing;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SurfaceBlockChance_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_SurfaceBlockChance;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InteriorBlockChance_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_InteriorBlockChance;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TerrainLayer_MetaData[];
#endif
		static const UECodeGen_Private::FNamePropertyParams NewProp_TerrainLayer;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BackgroundLayer_MetaData[];
#endif
		static const UECodeGen_Private::FNamePropertyParams NewProp_BackgroundLayer;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_WaterLayer_MetaData[];
#endif
		static const UECodeGen_Private::FNamePropertyParams NewProp_WaterLayer;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DecorationLayer_MetaData[];
#endif
		static const UECodeGen_Private::FNamePropertyParams NewProp_DecorationLayer;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BehindLayer_MetaData[];
#endif
		static const UECodeGen_Private::FNamePropertyParams NewProp_BehindLayer;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_EdgeLayer_MetaData[];
#endif
		static const UECodeGen_Private::FNamePropertyParams NewProp_EdgeLayer;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * RECETA del generador: como es el nivel. Se guarda en el Tile Map (cada mapa recuerda la suya)\n * y se edita en la pestana \"Generar\" del panel. Misma receta + misma semilla = mismo nivel.\n */" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "RECETA del generador: como es el nivel. Se guarda en el Tile Map (cada mapa recuerda la suya)\ny se edita en la pestana \"Generar\" del panel. Misma receta + misma semilla = mismo nivel." },
	};
#endif
	void* Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFramework2DProcGenSettings>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_BiomeId_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Bioma del Tile Set con el que se construye (su Id). Si no existe, se usa el primero.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Bioma del Tile Set con el que se construye (su Id). Si no existe, se usa el primero." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_BiomeId = { "BiomeId", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, BiomeId), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_BiomeId_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_BiomeId_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_Seed_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Otra semilla = otro nivel con los mismos ajustes.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Otra semilla = otro nivel con los mismos ajustes." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_Seed = { "Seed", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, Seed), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_Seed_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_Seed_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_Levels_MetaData[] = {
		{ "Category", "Framework2D|Relieve" },
		{ "ClampMax", "16" },
		{ "ClampMin", "1" },
		{ "Comment", "// Cuantas alturas distintas puede tener el suelo (1 = llano).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Cuantas alturas distintas puede tener el suelo (1 = llano)." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_Levels = { "Levels", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, Levels), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_Levels_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_Levels_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_LevelHeight_MetaData[] = {
		{ "Category", "Framework2D|Relieve" },
		{ "ClampMax", "16" },
		{ "ClampMin", "1" },
		{ "Comment", "// Tiles que hay de una altura a la siguiente (lo alto de cada escalon).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Tiles que hay de una altura a la siguiente (lo alto de cada escalon)." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_LevelHeight = { "LevelHeight", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, LevelHeight), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_LevelHeight_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_LevelHeight_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_BaseHeight_MetaData[] = {
		{ "Category", "Framework2D|Relieve" },
		{ "ClampMax", "256" },
		{ "ClampMin", "1" },
		{ "Comment", "// Tiles de suelo por debajo de la altura mas baja.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Tiles de suelo por debajo de la altura mas baja." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_BaseHeight = { "BaseHeight", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, BaseHeight), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_BaseHeight_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_BaseHeight_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PlateauMinWidth_MetaData[] = {
		{ "Category", "Framework2D|Relieve" },
		{ "ClampMax", "128" },
		{ "ClampMin", "1" },
		{ "Comment", "// Anchura minima y maxima (tiles) de cada tramo llano.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Anchura minima y maxima (tiles) de cada tramo llano." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PlateauMinWidth = { "PlateauMinWidth", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, PlateauMinWidth), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PlateauMinWidth_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PlateauMinWidth_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PlateauMaxWidth_MetaData[] = {
		{ "Category", "Framework2D|Relieve" },
		{ "ClampMax", "256" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PlateauMaxWidth = { "PlateauMaxWidth", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, PlateauMaxWidth), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PlateauMaxWidth_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PlateauMaxWidth_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_MaxLevelStep_MetaData[] = {
		{ "Category", "Framework2D|Relieve" },
		{ "ClampMax", "15" },
		{ "ClampMin", "1" },
		{ "Comment", "// Cuantas alturas puede subir o bajar el suelo de golpe (en un acantilado).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Cuantas alturas puede subir o bajar el suelo de golpe (en un acantilado)." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_MaxLevelStep = { "MaxLevelStep", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, MaxLevelStep), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_MaxLevelStep_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_MaxLevelStep_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_RampChance_MetaData[] = {
		{ "Category", "Framework2D|Relieve" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "Comment", "// De los cambios de una altura, cuantos son rampa en vez de escalon (0..1). Necesita rampas en el bioma.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "De los cambios de una altura, cuantos son rampa en vez de escalon (0..1). Necesita rampas en el bioma." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_RampChance = { "RampChance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, RampChance), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_RampChance_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_RampChance_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_GentleRampChance_MetaData[] = {
		{ "Category", "Framework2D|Relieve" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "Comment", "// De las rampas, cuantas son suaves (0..1). Necesita rampas suaves en el bioma.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "De las rampas, cuantas son suaves (0..1). Necesita rampas suaves en el bioma." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_GentleRampChance = { "GentleRampChance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, GentleRampChance), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_GentleRampChance_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_GentleRampChance_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PitChance_MetaData[] = {
		{ "Category", "Framework2D|Agua" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "Comment", "// Probabilidad de que un tramo llano tenga un foso (0..1).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Probabilidad de que un tramo llano tenga un foso (0..1)." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PitChance = { "PitChance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, PitChance), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PitChance_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PitChance_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PitDepth_MetaData[] = {
		{ "Category", "Framework2D|Agua" },
		{ "ClampMax", "16" },
		{ "ClampMin", "1" },
		{ "Comment", "// Profundidad de los fosos (tiles).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Profundidad de los fosos (tiles)." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PitDepth = { "PitDepth", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, PitDepth), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PitDepth_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PitDepth_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_LakeChance_MetaData[] = {
		{ "Category", "Framework2D|Agua" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "Comment", "// De las hondonadas (fosos y valles), cuantas se llenan de agua (0..1). Necesita agua en el bioma.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "De las hondonadas (fosos y valles), cuantas se llenan de agua (0..1). Necesita agua en el bioma." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_LakeChance = { "LakeChance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, LakeChance), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_LakeChance_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_LakeChance_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_MaxLakeWidth_MetaData[] = {
		{ "Category", "Framework2D|Agua" },
		{ "ClampMax", "1024" },
		{ "ClampMin", "3" },
		{ "Comment", "// Ancho maximo de un lago (tiles). En una hondonada mas ancha el agua baja hasta que solo\n// quedan llenas sus partes mas hondas (cada una, como mucho asi de ancha).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Ancho maximo de un lago (tiles). En una hondonada mas ancha el agua baja hasta que solo\nquedan llenas sus partes mas hondas (cada una, como mucho asi de ancha)." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_MaxLakeWidth = { "MaxLakeWidth", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, MaxLakeWidth), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_MaxLakeWidth_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_MaxLakeWidth_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_WaterfallChance_MetaData[] = {
		{ "Category", "Framework2D|Agua" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "Comment", "// De los acantilados de 2 tiles o mas, cuantos tienen cascada (0..1). Necesita cascada en el bioma.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "De los acantilados de 2 tiles o mas, cuantos tienen cascada (0..1). Necesita cascada en el bioma." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_WaterfallChance = { "WaterfallChance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, WaterfallChance), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_WaterfallChance_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_WaterfallChance_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PlatformChance_MetaData[] = {
		{ "Category", "Framework2D|Plataformas" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "Comment", "// Probabilidad de que un tramo llano tenga una plataforma flotante encima (0..1).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Probabilidad de que un tramo llano tenga una plataforma flotante encima (0..1)." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PlatformChance = { "PlatformChance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, PlatformChance), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PlatformChance_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PlatformChance_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PlatformMinLength_MetaData[] = {
		{ "Category", "Framework2D|Plataformas" },
		{ "ClampMax", "64" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PlatformMinLength = { "PlatformMinLength", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, PlatformMinLength), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PlatformMinLength_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PlatformMinLength_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PlatformMaxLength_MetaData[] = {
		{ "Category", "Framework2D|Plataformas" },
		{ "ClampMax", "64" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PlatformMaxLength = { "PlatformMaxLength", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, PlatformMaxLength), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PlatformMaxLength_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PlatformMaxLength_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_DecorationDensity_MetaData[] = {
		{ "Category", "Framework2D|Decoracion" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "Comment", "// De cada casilla de suelo libre, la fraccion que lleva un adorno (0..1).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "De cada casilla de suelo libre, la fraccion que lleva un adorno (0..1)." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_DecorationDensity = { "DecorationDensity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, DecorationDensity), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_DecorationDensity_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_DecorationDensity_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_DecorationSpacing_MetaData[] = {
		{ "Category", "Framework2D|Decoracion" },
		{ "ClampMax", "16" },
		{ "ClampMin", "0" },
		{ "Comment", "// Casillas libres minimas entre dos adornos seguidos.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Casillas libres minimas entre dos adornos seguidos." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_DecorationSpacing = { "DecorationSpacing", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, DecorationSpacing), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_DecorationSpacing_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_DecorationSpacing_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_CenterVariantChance_MetaData[] = {
		{ "Category", "Framework2D|Decoracion" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "Comment", "// De las casillas del centro del terreno, cuantas usan una variante (0..1). Necesita variantes en el bioma.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "De las casillas del centro del terreno, cuantas usan una variante (0..1). Necesita variantes en el bioma." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_CenterVariantChance = { "CenterVariantChance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, CenterVariantChance), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_CenterVariantChance_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_CenterVariantChance_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_bBackground_MetaData[] = {
		{ "Category", "Framework2D|Fondo" },
		{ "Comment", "// Rellena la capa de fondo (si el bioma tiene fondo): detras del terreno y en colinas.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Rellena la capa de fondo (si el bioma tiene fondo): detras del terreno y en colinas." },
	};
#endif
	void Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_bBackground_SetBit(void* Obj)
	{
		((FFramework2DProcGenSettings*)Obj)->bBackground = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_bBackground = { "bBackground", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FFramework2DProcGenSettings), &Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_bBackground_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_bBackground_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_bBackground_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_BackgroundRise_MetaData[] = {
		{ "Category", "Framework2D|Fondo" },
		{ "ClampMax", "64" },
		{ "ClampMin", "0" },
		{ "Comment", "// Cuanto asoma el fondo por encima del terreno (tiles). 0 = solo detras (se ve al picar).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Cuanto asoma el fondo por encima del terreno (tiles). 0 = solo detras (se ve al picar)." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_BackgroundRise = { "BackgroundRise", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, BackgroundRise), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_BackgroundRise_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_BackgroundRise_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_bEdgeWalls_MetaData[] = {
		{ "Category", "Framework2D|Bordes" },
		{ "Comment", "// Muros de terreno en los bordes izquierdo y derecho (de abajo arriba del todo).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Muros de terreno en los bordes izquierdo y derecho (de abajo arriba del todo)." },
	};
#endif
	void Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_bEdgeWalls_SetBit(void* Obj)
	{
		((FFramework2DProcGenSettings*)Obj)->bEdgeWalls = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_bEdgeWalls = { "bEdgeWalls", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FFramework2DProcGenSettings), &Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_bEdgeWalls_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_bEdgeWalls_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_bEdgeWalls_MetaData)) };
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_ReliefStyle_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_ReliefStyle_MetaData[] = {
		{ "Category", "Framework2D|Relieve" },
		{ "Comment", "// Forma del suelo: escalones (llanos a varias alturas) o lomas suaves.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Forma del suelo: escalones (llanos a varias alturas) o lomas suaves." },
	};
#endif
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_ReliefStyle = { "ReliefStyle", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, ReliefStyle), Z_Construct_UEnum_Framework2DTerrain_EFramework2DReliefStyle, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_ReliefStyle_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_ReliefStyle_MetaData)) }; // 1826366967
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_Roughness_MetaData[] = {
		{ "Category", "Framework2D|Relieve" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "Comment", "// Lomas: cuanto suben y bajan (0 = colinas largas y suaves, 1 = muy movido).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Lomas: cuanto suben y bajan (0 = colinas largas y suaves, 1 = muy movido)." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_Roughness = { "Roughness", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, Roughness), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_Roughness_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_Roughness_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_IslandChance_MetaData[] = {
		{ "Category", "Framework2D|Islas" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "Comment", "// Islas flotantes con base de roca (0..1): probabilidad por cada tramo de unos 10 tiles.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Islas flotantes con base de roca (0..1): probabilidad por cada tramo de unos 10 tiles." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_IslandChance = { "IslandChance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, IslandChance), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_IslandChance_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_IslandChance_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_IslandMinWidth_MetaData[] = {
		{ "Category", "Framework2D|Islas" },
		{ "ClampMax", "64" },
		{ "ClampMin", "2" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_IslandMinWidth = { "IslandMinWidth", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, IslandMinWidth), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_IslandMinWidth_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_IslandMinWidth_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_IslandMaxWidth_MetaData[] = {
		{ "Category", "Framework2D|Islas" },
		{ "ClampMax", "64" },
		{ "ClampMin", "2" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_IslandMaxWidth = { "IslandMaxWidth", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, IslandMaxWidth), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_IslandMaxWidth_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_IslandMaxWidth_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_BridgeChance_MetaData[] = {
		{ "Category", "Framework2D|Islas" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "Comment", "// De los huecos que se pueden cruzar con un puente, cuantos lo llevan (0..1). Necesita puente en el bioma.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "De los huecos que se pueden cruzar con un puente, cuantos lo llevan (0..1). Necesita puente en el bioma." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_BridgeChance = { "BridgeChance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, BridgeChance), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_BridgeChance_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_BridgeChance_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PropDensity_MetaData[] = {
		{ "Category", "Framework2D|Objetos" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "Comment", "// Objetos grandes: de cada sitio de suelo llano donde caben, la fraccion que lleva uno (0..1).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Objetos grandes: de cada sitio de suelo llano donde caben, la fraccion que lleva uno (0..1)." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PropDensity = { "PropDensity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, PropDensity), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PropDensity_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PropDensity_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PropSpacing_MetaData[] = {
		{ "Category", "Framework2D|Objetos" },
		{ "ClampMax", "64" },
		{ "ClampMin", "0" },
		{ "Comment", "// Tiles libres minimos entre dos objetos grandes.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Tiles libres minimos entre dos objetos grandes." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PropSpacing = { "PropSpacing", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, PropSpacing), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PropSpacing_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PropSpacing_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_GiantTreeChance_MetaData[] = {
		{ "Category", "Framework2D|Objetos" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "Comment", "// Arboles gigantes: de cada sitio de suelo llano donde cabe uno, la fraccion que lo lleva (0..1).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Arboles gigantes: de cada sitio de suelo llano donde cabe uno, la fraccion que lo lleva (0..1)." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_GiantTreeChance = { "GiantTreeChance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, GiantTreeChance), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_GiantTreeChance_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_GiantTreeChance_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_GiantTreeSpacing_MetaData[] = {
		{ "Category", "Framework2D|Objetos" },
		{ "ClampMax", "128" },
		{ "ClampMin", "0" },
		{ "Comment", "// Tiles minimos entre dos arboles gigantes.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Tiles minimos entre dos arboles gigantes." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_GiantTreeSpacing = { "GiantTreeSpacing", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, GiantTreeSpacing), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_GiantTreeSpacing_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_GiantTreeSpacing_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_SurfaceBlockChance_MetaData[] = {
		{ "Category", "Framework2D|Decoracion" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "Comment", "// Bloques de la superficie: de cada sitio de suelo llano donde cabe uno, la fraccion que lo lleva (0..1).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Bloques de la superficie: de cada sitio de suelo llano donde cabe uno, la fraccion que lo lleva (0..1)." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_SurfaceBlockChance = { "SurfaceBlockChance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, SurfaceBlockChance), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_SurfaceBlockChance_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_SurfaceBlockChance_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_InteriorBlockChance_MetaData[] = {
		{ "Category", "Framework2D|Decoracion" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "Comment", "// Bloques del interior: de cada sitio del centro del terreno donde cabe uno, la fraccion que lo lleva (0..1).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Bloques del interior: de cada sitio del centro del terreno donde cabe uno, la fraccion que lo lleva (0..1)." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_InteriorBlockChance = { "InteriorBlockChance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, InteriorBlockChance), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_InteriorBlockChance_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_InteriorBlockChance_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_TerrainLayer_MetaData[] = {
		{ "Category", "Framework2D|Capas" },
		{ "Comment", "// Nombres de las capas que se rellenan. Si no existen se crean; su contenido se REEMPLAZA.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Nombres de las capas que se rellenan. Si no existen se crean; su contenido se REEMPLAZA." },
	};
#endif
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_TerrainLayer = { "TerrainLayer", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, TerrainLayer), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_TerrainLayer_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_TerrainLayer_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_BackgroundLayer_MetaData[] = {
		{ "Category", "Framework2D|Capas" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_BackgroundLayer = { "BackgroundLayer", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, BackgroundLayer), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_BackgroundLayer_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_BackgroundLayer_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_WaterLayer_MetaData[] = {
		{ "Category", "Framework2D|Capas" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_WaterLayer = { "WaterLayer", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, WaterLayer), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_WaterLayer_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_WaterLayer_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_DecorationLayer_MetaData[] = {
		{ "Category", "Framework2D|Capas" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_DecorationLayer = { "DecorationLayer", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, DecorationLayer), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_DecorationLayer_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_DecorationLayer_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_BehindLayer_MetaData[] = {
		{ "Category", "Framework2D|Capas" },
		{ "Comment", "// Objetos grandes de detras del terreno.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Objetos grandes de detras del terreno." },
	};
#endif
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_BehindLayer = { "BehindLayer", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, BehindLayer), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_BehindLayer_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_BehindLayer_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_EdgeLayer_MetaData[] = {
		{ "Category", "Framework2D|Capas" },
		{ "Comment", "// Bordes naturales (delante del terreno, detras de la decoracion).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Bordes naturales (delante del terreno, detras de la decoracion)." },
	};
#endif
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_EdgeLayer = { "EdgeLayer", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenSettings, EdgeLayer), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_EdgeLayer_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_EdgeLayer_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_BiomeId,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_Seed,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_Levels,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_LevelHeight,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_BaseHeight,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PlateauMinWidth,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PlateauMaxWidth,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_MaxLevelStep,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_RampChance,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_GentleRampChance,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PitChance,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PitDepth,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_LakeChance,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_MaxLakeWidth,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_WaterfallChance,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PlatformChance,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PlatformMinLength,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PlatformMaxLength,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_DecorationDensity,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_DecorationSpacing,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_CenterVariantChance,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_bBackground,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_BackgroundRise,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_bEdgeWalls,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_ReliefStyle_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_ReliefStyle,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_Roughness,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_IslandChance,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_IslandMinWidth,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_IslandMaxWidth,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_BridgeChance,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PropDensity,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_PropSpacing,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_GiantTreeChance,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_GiantTreeSpacing,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_SurfaceBlockChance,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_InteriorBlockChance,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_TerrainLayer,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_BackgroundLayer,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_WaterLayer,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_DecorationLayer,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_BehindLayer,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewProp_EdgeLayer,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_Framework2DTerrain,
		nullptr,
		&NewStructOps,
		"Framework2DProcGenSettings",
		sizeof(FFramework2DProcGenSettings),
		alignof(FFramework2DProcGenSettings),
		Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FFramework2DProcGenSettings()
	{
		if (!Z_Registration_Info_UScriptStruct_Framework2DProcGenSettings.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_Framework2DProcGenSettings.InnerSingleton, Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_Framework2DProcGenSettings.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_Framework2DProcGenReport;
class UScriptStruct* FFramework2DProcGenReport::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_Framework2DProcGenReport.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_Framework2DProcGenReport.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FFramework2DProcGenReport, Z_Construct_UPackage__Script_Framework2DTerrain(), TEXT("Framework2DProcGenReport"));
	}
	return Z_Registration_Info_UScriptStruct_Framework2DProcGenReport.OuterSingleton;
}
template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<FFramework2DProcGenReport>()
{
	return FFramework2DProcGenReport::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bSuccess_MetaData[];
#endif
		static void NewProp_bSuccess_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bSuccess;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Levels_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Levels;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Ramps_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Ramps;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Cliffs_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Cliffs;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Pits_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Pits;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Lakes_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Lakes;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Waterfalls_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Waterfalls;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Platforms_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Platforms;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Decorations_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Decorations;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Islands_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Islands;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Bridges_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Bridges;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Props_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Props;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_WallFeet_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_WallFeet;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Blocks_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Blocks;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GiantTrees_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_GiantTrees;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BackgroundCaps_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_BackgroundCaps;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Message_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_Message;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/** Lo que salio en una generacion (para el panel, Blueprint y las pruebas). */" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Lo que salio en una generacion (para el panel, Blueprint y las pruebas)." },
	};
#endif
	void* Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFramework2DProcGenReport>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_bSuccess_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// False si no se pudo generar (falta el bioma, el centro del 3x3, el mapa es diminuto...).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "False si no se pudo generar (falta el bioma, el centro del 3x3, el mapa es diminuto...)." },
	};
#endif
	void Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_bSuccess_SetBit(void* Obj)
	{
		((FFramework2DProcGenReport*)Obj)->bSuccess = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_bSuccess = { "bSuccess", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FFramework2DProcGenReport), &Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_bSuccess_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_bSuccess_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_bSuccess_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Levels_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Alturas que caben de verdad en el mapa (puede ser menos de las pedidas).\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Alturas que caben de verdad en el mapa (puede ser menos de las pedidas)." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Levels = { "Levels", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenReport, Levels), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Levels_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Levels_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Ramps_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Ramps = { "Ramps", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenReport, Ramps), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Ramps_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Ramps_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Cliffs_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Cliffs = { "Cliffs", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenReport, Cliffs), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Cliffs_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Cliffs_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Pits_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Pits = { "Pits", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenReport, Pits), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Pits_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Pits_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Lakes_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Lakes = { "Lakes", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenReport, Lakes), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Lakes_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Lakes_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Waterfalls_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Waterfalls = { "Waterfalls", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenReport, Waterfalls), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Waterfalls_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Waterfalls_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Platforms_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Platforms = { "Platforms", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenReport, Platforms), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Platforms_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Platforms_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Decorations_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Decorations = { "Decorations", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenReport, Decorations), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Decorations_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Decorations_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Islands_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Islands = { "Islands", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenReport, Islands), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Islands_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Islands_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Bridges_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Bridges = { "Bridges", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenReport, Bridges), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Bridges_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Bridges_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Props_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Props = { "Props", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenReport, Props), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Props_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Props_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_WallFeet_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Pies de pared, bloques (superficie e interior) y arboles gigantes colocados.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Pies de pared, bloques (superficie e interior) y arboles gigantes colocados." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_WallFeet = { "WallFeet", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenReport, WallFeet), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_WallFeet_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_WallFeet_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Blocks_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Blocks = { "Blocks", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenReport, Blocks), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Blocks_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Blocks_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_GiantTrees_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_GiantTrees = { "GiantTrees", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenReport, GiantTrees), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_GiantTrees_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_GiantTrees_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_BackgroundCaps_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_BackgroundCaps = { "BackgroundCaps", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenReport, BackgroundCaps), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_BackgroundCaps_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_BackgroundCaps_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Message_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Por que no se pudo, o avisos (\"solo caben 2 alturas en 20 tiles de alto\"). En espanol.\n" },
		{ "ModuleRelativePath", "Public/Framework2DProcGenTypes.h" },
		{ "ToolTip", "Por que no se pudo, o avisos (\"solo caben 2 alturas en 20 tiles de alto\"). En espanol." },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Message = { "Message", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DProcGenReport, Message), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Message_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Message_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_bSuccess,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Levels,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Ramps,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Cliffs,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Pits,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Lakes,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Waterfalls,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Platforms,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Decorations,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Islands,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Bridges,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Props,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_WallFeet,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Blocks,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_GiantTrees,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_BackgroundCaps,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewProp_Message,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_Framework2DTerrain,
		nullptr,
		&NewStructOps,
		"Framework2DProcGenReport",
		sizeof(FFramework2DProcGenReport),
		alignof(FFramework2DProcGenReport),
		Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FFramework2DProcGenReport()
	{
		if (!Z_Registration_Info_UScriptStruct_Framework2DProcGenReport.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_Framework2DProcGenReport.InnerSingleton, Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_Framework2DProcGenReport.InnerSingleton;
	}
	struct Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DProcGenTypes_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DProcGenTypes_h_Statics::EnumInfo[] = {
		{ EFramework2DDecorPlacement_StaticEnum, TEXT("EFramework2DDecorPlacement"), &Z_Registration_Info_UEnum_EFramework2DDecorPlacement, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 471993281U) },
		{ EFramework2DReliefStyle_StaticEnum, TEXT("EFramework2DReliefStyle"), &Z_Registration_Info_UEnum_EFramework2DReliefStyle, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1826366967U) },
		{ EFramework2DPropDepth_StaticEnum, TEXT("EFramework2DPropDepth"), &Z_Registration_Info_UEnum_EFramework2DPropDepth, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 4215662271U) },
		{ EFramework2DBiomeSlot_StaticEnum, TEXT("EFramework2DBiomeSlot"), &Z_Registration_Info_UEnum_EFramework2DBiomeSlot, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 179662248U) },
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DProcGenTypes_h_Statics::ScriptStructInfo[] = {
		{ FFramework2DTile3x3::StaticStruct, Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics::NewStructOps, TEXT("Framework2DTile3x3"), &Z_Registration_Info_UScriptStruct_Framework2DTile3x3, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FFramework2DTile3x3), 4088922689U) },
		{ FFramework2DTile5x5::StaticStruct, Z_Construct_UScriptStruct_FFramework2DTile5x5_Statics::NewStructOps, TEXT("Framework2DTile5x5"), &Z_Registration_Info_UScriptStruct_Framework2DTile5x5, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FFramework2DTile5x5), 3607507704U) },
		{ FFramework2DInnerCorners::StaticStruct, Z_Construct_UScriptStruct_FFramework2DInnerCorners_Statics::NewStructOps, TEXT("Framework2DInnerCorners"), &Z_Registration_Info_UScriptStruct_Framework2DInnerCorners, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FFramework2DInnerCorners), 2550555143U) },
		{ FFramework2DBackdropLayer::StaticStruct, Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics::NewStructOps, TEXT("Framework2DBackdropLayer"), &Z_Registration_Info_UScriptStruct_Framework2DBackdropLayer, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FFramework2DBackdropLayer), 3674502919U) },
		{ FFramework2DPropInstance::StaticStruct, Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics::NewStructOps, TEXT("Framework2DPropInstance"), &Z_Registration_Info_UScriptStruct_Framework2DPropInstance, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FFramework2DPropInstance), 3923129924U) },
		{ FFramework2DBiomeProp::StaticStruct, Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics::NewStructOps, TEXT("Framework2DBiomeProp"), &Z_Registration_Info_UScriptStruct_Framework2DBiomeProp, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FFramework2DBiomeProp), 3239512243U) },
		{ FFramework2DBiomeBlock::StaticStruct, Z_Construct_UScriptStruct_FFramework2DBiomeBlock_Statics::NewStructOps, TEXT("Framework2DBiomeBlock"), &Z_Registration_Info_UScriptStruct_Framework2DBiomeBlock, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FFramework2DBiomeBlock), 1063392883U) },
		{ FFramework2DBiomeGiantTree::StaticStruct, Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics::NewStructOps, TEXT("Framework2DBiomeGiantTree"), &Z_Registration_Info_UScriptStruct_Framework2DBiomeGiantTree, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FFramework2DBiomeGiantTree), 2501815260U) },
		{ FFramework2DBiomeDecoration::StaticStruct, Z_Construct_UScriptStruct_FFramework2DBiomeDecoration_Statics::NewStructOps, TEXT("Framework2DBiomeDecoration"), &Z_Registration_Info_UScriptStruct_Framework2DBiomeDecoration, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FFramework2DBiomeDecoration), 2717470893U) },
		{ FFramework2DBiome::StaticStruct, Z_Construct_UScriptStruct_FFramework2DBiome_Statics::NewStructOps, TEXT("Framework2DBiome"), &Z_Registration_Info_UScriptStruct_Framework2DBiome, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FFramework2DBiome), 3730231485U) },
		{ FFramework2DProcGenSettings::StaticStruct, Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics::NewStructOps, TEXT("Framework2DProcGenSettings"), &Z_Registration_Info_UScriptStruct_Framework2DProcGenSettings, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FFramework2DProcGenSettings), 1808137377U) },
		{ FFramework2DProcGenReport::StaticStruct, Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics::NewStructOps, TEXT("Framework2DProcGenReport"), &Z_Registration_Info_UScriptStruct_Framework2DProcGenReport, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FFramework2DProcGenReport), 1251867274U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DProcGenTypes_h_3575001201(TEXT("/Script/Framework2DTerrain"),
		nullptr, 0,
		Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DProcGenTypes_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DProcGenTypes_h_Statics::ScriptStructInfo),
		Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DProcGenTypes_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DProcGenTypes_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
