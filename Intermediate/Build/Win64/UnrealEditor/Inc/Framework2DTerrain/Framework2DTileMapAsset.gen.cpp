// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Framework2DTerrain/Public/Framework2DTileMapAsset.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFramework2DTileMapAsset() {}
// Cross Module References
	FRAMEWORK2DTERRAIN_API UScriptStruct* Z_Construct_UScriptStruct_FFramework2DTileLayer();
	UPackage* Z_Construct_UPackage__Script_Framework2DTerrain();
	FRAMEWORK2DTERRAIN_API UClass* Z_Construct_UClass_UFramework2DTileMapAsset_NoRegister();
	FRAMEWORK2DTERRAIN_API UClass* Z_Construct_UClass_UFramework2DTileMapAsset();
	ENGINE_API UClass* Z_Construct_UClass_UDataAsset();
	FRAMEWORK2DTERRAIN_API UClass* Z_Construct_UClass_UFramework2DTileSet_NoRegister();
	FRAMEWORK2DTERRAIN_API UScriptStruct* Z_Construct_UScriptStruct_FFramework2DProcGenSettings();
	FRAMEWORK2DTERRAIN_API UScriptStruct* Z_Construct_UScriptStruct_FFramework2DBackdropLayer();
	FRAMEWORK2DTERRAIN_API UScriptStruct* Z_Construct_UScriptStruct_FFramework2DPropInstance();
// End Cross Module References
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_Framework2DTileLayer;
class UScriptStruct* FFramework2DTileLayer::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_Framework2DTileLayer.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_Framework2DTileLayer.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FFramework2DTileLayer, Z_Construct_UPackage__Script_Framework2DTerrain(), TEXT("Framework2DTileLayer"));
	}
	return Z_Registration_Info_UScriptStruct_Framework2DTileLayer.OuterSingleton;
}
template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<FFramework2DTileLayer>()
{
	return FFramework2DTileLayer::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics
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
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bVisible_MetaData[];
#endif
		static void NewProp_bVisible_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bVisible;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bBackground_MetaData[];
#endif
		static void NewProp_bBackground_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bBackground;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bCollides_MetaData[];
#endif
		static void NewProp_bCollides_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bCollides;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bBreakable_MetaData[];
#endif
		static void NewProp_bBreakable_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bBreakable;
		static const UECodeGen_Private::FIntPropertyParams NewProp_Tiles_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Tiles_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Tiles;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * Una capa del tilemap. Tiles es una rejilla plana: indice = Y*Width + X (Y=0 arriba).\n * Valores: -1 = vacio, 0.. = tile del atlas, >= Framework2D::FlipbookTileBase = flipbook.\n *\n * Cada capa se dibuja en su propio plano, separada de las demas en profundidad (Layer\n * Separation del terreno), como las capas de los tilemaps de Unreal.\n */" },
		{ "ModuleRelativePath", "Public/Framework2DTileMapAsset.h" },
		{ "ToolTip", "Una capa del tilemap. Tiles es una rejilla plana: indice = Y*Width + X (Y=0 arriba).\nValores: -1 = vacio, 0.. = tile del atlas, >= Framework2D::FlipbookTileBase = flipbook.\n\nCada capa se dibuja en su propio plano, separada de las demas en profundidad (Layer\nSeparation del terreno), como las capas de los tilemaps de Unreal." },
	};
#endif
	void* Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFramework2DTileLayer>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_Name_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DTileMapAsset.h" },
	};
#endif
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DTileLayer, Name), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_Name_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_Name_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_bVisible_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Las capas ocultas no se hornean (ni se ven, ni colisionan).\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileMapAsset.h" },
		{ "ToolTip", "Las capas ocultas no se hornean (ni se ven, ni colisionan)." },
	};
#endif
	void Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_bVisible_SetBit(void* Obj)
	{
		((FFramework2DTileLayer*)Obj)->bVisible = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_bVisible = { "bVisible", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FFramework2DTileLayer), &Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_bVisible_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_bVisible_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_bVisible_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_bBackground_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Capa de FONDO (pared trasera): se ve oscurecida, no colisiona ni se pica. Ideal para cuevas.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileMapAsset.h" },
		{ "ToolTip", "Capa de FONDO (pared trasera): se ve oscurecida, no colisiona ni se pica. Ideal para cuevas." },
	};
#endif
	void Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_bBackground_SetBit(void* Obj)
	{
		((FFramework2DTileLayer*)Obj)->bBackground = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_bBackground = { "bBackground", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FFramework2DTileLayer), &Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_bBackground_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_bBackground_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_bBackground_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_bCollides_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Si false, esta capa no choca nunca (decoracion delante o detras del jugador).\n" },
		{ "EditCondition", "!bBackground" },
		{ "ModuleRelativePath", "Public/Framework2DTileMapAsset.h" },
		{ "ToolTip", "Si false, esta capa no choca nunca (decoracion delante o detras del jugador)." },
	};
#endif
	void Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_bCollides_SetBit(void* Obj)
	{
		((FFramework2DTileLayer*)Obj)->bCollides = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_bCollides = { "bCollides", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FFramework2DTileLayer), &Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_bCollides_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_bCollides_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_bCollides_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_bBreakable_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Si false, picar y explotar no la rompen (decoracion intocable).\n" },
		{ "EditCondition", "!bBackground" },
		{ "ModuleRelativePath", "Public/Framework2DTileMapAsset.h" },
		{ "ToolTip", "Si false, picar y explotar no la rompen (decoracion intocable)." },
	};
#endif
	void Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_bBreakable_SetBit(void* Obj)
	{
		((FFramework2DTileLayer*)Obj)->bBreakable = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_bBreakable = { "bBreakable", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FFramework2DTileLayer), &Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_bBreakable_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_bBreakable_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_bBreakable_MetaData)) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_Tiles_Inner = { "Tiles", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_Tiles_MetaData[] = {
		{ "ModuleRelativePath", "Public/Framework2DTileMapAsset.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_Tiles = { "Tiles", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DTileLayer, Tiles), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_Tiles_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_Tiles_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_Name,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_bVisible,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_bBackground,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_bCollides,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_bBreakable,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_Tiles_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewProp_Tiles,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_Framework2DTerrain,
		nullptr,
		&NewStructOps,
		"Framework2DTileLayer",
		sizeof(FFramework2DTileLayer),
		alignof(FFramework2DTileLayer),
		Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FFramework2DTileLayer()
	{
		if (!Z_Registration_Info_UScriptStruct_Framework2DTileLayer.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_Framework2DTileLayer.InnerSingleton, Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_Framework2DTileLayer.InnerSingleton;
	}
	DEFINE_FUNCTION(UFramework2DTileMapAsset::execAt)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_Layer);
		P_GET_PROPERTY(FIntProperty,Z_Param_X);
		P_GET_PROPERTY(FIntProperty,Z_Param_Y);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->At(Z_Param_Layer,Z_Param_X,Z_Param_Y);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFramework2DTileMapAsset::execFindLayerByName)
	{
		P_GET_PROPERTY(FNameProperty,Z_Param_LayerName);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->FindLayerByName(Z_Param_LayerName);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFramework2DTileMapAsset::execResize)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_NewWidth);
		P_GET_PROPERTY(FIntProperty,Z_Param_NewHeight);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Resize(Z_Param_NewWidth,Z_Param_NewHeight);
		P_NATIVE_END;
	}
	void UFramework2DTileMapAsset::StaticRegisterNativesUFramework2DTileMapAsset()
	{
		UClass* Class = UFramework2DTileMapAsset::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "At", &UFramework2DTileMapAsset::execAt },
			{ "FindLayerByName", &UFramework2DTileMapAsset::execFindLayerByName },
			{ "Resize", &UFramework2DTileMapAsset::execResize },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UFramework2DTileMapAsset_At_Statics
	{
		struct Framework2DTileMapAsset_eventAt_Parms
		{
			int32 Layer;
			int32 X;
			int32 Y;
			int32 ReturnValue;
		};
		static const UECodeGen_Private::FIntPropertyParams NewProp_Layer;
		static const UECodeGen_Private::FIntPropertyParams NewProp_X;
		static const UECodeGen_Private::FIntPropertyParams NewProp_Y;
		static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UFramework2DTileMapAsset_At_Statics::NewProp_Layer = { "Layer", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DTileMapAsset_eventAt_Parms, Layer), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UFramework2DTileMapAsset_At_Statics::NewProp_X = { "X", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DTileMapAsset_eventAt_Parms, X), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UFramework2DTileMapAsset_At_Statics::NewProp_Y = { "Y", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DTileMapAsset_eventAt_Parms, Y), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UFramework2DTileMapAsset_At_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DTileMapAsset_eventAt_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFramework2DTileMapAsset_At_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTileMapAsset_At_Statics::NewProp_Layer,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTileMapAsset_At_Statics::NewProp_X,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTileMapAsset_At_Statics::NewProp_Y,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTileMapAsset_At_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFramework2DTileMapAsset_At_Statics::Function_MetaDataParams[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "/** Valor en (Capa, X, Y) tal como se hornea: -1 si esta vacio, fuera de rango o la capa esta oculta. */" },
		{ "ModuleRelativePath", "Public/Framework2DTileMapAsset.h" },
		{ "ToolTip", "Valor en (Capa, X, Y) tal como se hornea: -1 si esta vacio, fuera de rango o la capa esta oculta." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFramework2DTileMapAsset_At_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFramework2DTileMapAsset, nullptr, "At", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFramework2DTileMapAsset_At_Statics::Framework2DTileMapAsset_eventAt_Parms), Z_Construct_UFunction_UFramework2DTileMapAsset_At_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTileMapAsset_At_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFramework2DTileMapAsset_At_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTileMapAsset_At_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFramework2DTileMapAsset_At()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFramework2DTileMapAsset_At_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFramework2DTileMapAsset_FindLayerByName_Statics
	{
		struct Framework2DTileMapAsset_eventFindLayerByName_Parms
		{
			FName LayerName;
			int32 ReturnValue;
		};
		static const UECodeGen_Private::FNamePropertyParams NewProp_LayerName;
		static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UFramework2DTileMapAsset_FindLayerByName_Statics::NewProp_LayerName = { "LayerName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DTileMapAsset_eventFindLayerByName_Parms, LayerName), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UFramework2DTileMapAsset_FindLayerByName_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DTileMapAsset_eventFindLayerByName_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFramework2DTileMapAsset_FindLayerByName_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTileMapAsset_FindLayerByName_Statics::NewProp_LayerName,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTileMapAsset_FindLayerByName_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFramework2DTileMapAsset_FindLayerByName_Statics::Function_MetaDataParams[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "/** Indice de la primera capa con ese nombre (sin distinguir mayusculas). INDEX_NONE si no hay. */" },
		{ "ModuleRelativePath", "Public/Framework2DTileMapAsset.h" },
		{ "ToolTip", "Indice de la primera capa con ese nombre (sin distinguir mayusculas). INDEX_NONE si no hay." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFramework2DTileMapAsset_FindLayerByName_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFramework2DTileMapAsset, nullptr, "FindLayerByName", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFramework2DTileMapAsset_FindLayerByName_Statics::Framework2DTileMapAsset_eventFindLayerByName_Parms), Z_Construct_UFunction_UFramework2DTileMapAsset_FindLayerByName_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTileMapAsset_FindLayerByName_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFramework2DTileMapAsset_FindLayerByName_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTileMapAsset_FindLayerByName_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFramework2DTileMapAsset_FindLayerByName()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFramework2DTileMapAsset_FindLayerByName_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFramework2DTileMapAsset_Resize_Statics
	{
		struct Framework2DTileMapAsset_eventResize_Parms
		{
			int32 NewWidth;
			int32 NewHeight;
		};
		static const UECodeGen_Private::FIntPropertyParams NewProp_NewWidth;
		static const UECodeGen_Private::FIntPropertyParams NewProp_NewHeight;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UFramework2DTileMapAsset_Resize_Statics::NewProp_NewWidth = { "NewWidth", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DTileMapAsset_eventResize_Parms, NewWidth), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UFramework2DTileMapAsset_Resize_Statics::NewProp_NewHeight = { "NewHeight", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DTileMapAsset_eventResize_Parms, NewHeight), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFramework2DTileMapAsset_Resize_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTileMapAsset_Resize_Statics::NewProp_NewWidth,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTileMapAsset_Resize_Statics::NewProp_NewHeight,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFramework2DTileMapAsset_Resize_Statics::Function_MetaDataParams[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "/**\n\x09 * Cambia el tamano del mapa (en tiles) conservando lo pintado que quepa, anclado arriba a la\n\x09 * izquierda como al cambiar Width/Height en Details. La colision pintada sigue a sus tiles.\n\x09 */" },
		{ "ModuleRelativePath", "Public/Framework2DTileMapAsset.h" },
		{ "ToolTip", "Cambia el tamano del mapa (en tiles) conservando lo pintado que quepa, anclado arriba a la\nizquierda como al cambiar Width/Height en Details. La colision pintada sigue a sus tiles." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFramework2DTileMapAsset_Resize_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFramework2DTileMapAsset, nullptr, "Resize", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFramework2DTileMapAsset_Resize_Statics::Framework2DTileMapAsset_eventResize_Parms), Z_Construct_UFunction_UFramework2DTileMapAsset_Resize_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTileMapAsset_Resize_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFramework2DTileMapAsset_Resize_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTileMapAsset_Resize_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFramework2DTileMapAsset_Resize()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFramework2DTileMapAsset_Resize_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UFramework2DTileMapAsset);
	UClass* Z_Construct_UClass_UFramework2DTileMapAsset_NoRegister()
	{
		return UFramework2DTileMapAsset::StaticClass();
	}
	struct Z_Construct_UClass_UFramework2DTileMapAsset_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TileSet_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_TileSet;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Width_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Width;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Height_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Height;
		static const UECodeGen_Private::FStructPropertyParams NewProp_Layers_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Layers_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Layers;
		static const UECodeGen_Private::FBytePropertyParams NewProp_CollisionOverrides_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CollisionOverrides_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_CollisionOverrides;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ProcGen_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_ProcGen;
		static const UECodeGen_Private::FStructPropertyParams NewProp_Backdrops_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Backdrops_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Backdrops;
		static const UECodeGen_Private::FStructPropertyParams NewProp_PropInstances_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PropInstances_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_PropInstances;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UFramework2DTileMapAsset_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UDataAsset,
		(UObject* (*)())Z_Construct_UPackage__Script_Framework2DTerrain,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UFramework2DTileMapAsset_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UFramework2DTileMapAsset_At, "At" }, // 4234094135
		{ &Z_Construct_UFunction_UFramework2DTileMapAsset_FindLayerByName, "FindLayerByName" }, // 3704614471
		{ &Z_Construct_UFunction_UFramework2DTileMapAsset_Resize, "Resize" }, // 663391852
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTileMapAsset_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * UFramework2DTileMapAsset\n * =================================================================\n * Tu nivel: capas de tiles de un TileSet. Se crea con:\n *   Content Browser -> Add -> Miscellaneous -> Data Asset -> Framework2DTileMapAsset\n * y se pinta en el viewport con el modo \"Framework2D Tiles\".\n *\n * Las capas van de ATRAS (indice 0) a DELANTE: cada una en su plano, mas cerca de la camara.\n */" },
		{ "IncludePath", "Framework2DTileMapAsset.h" },
		{ "ModuleRelativePath", "Public/Framework2DTileMapAsset.h" },
		{ "ToolTip", "UFramework2DTileMapAsset\n\nTu nivel: capas de tiles de un TileSet. Se crea con:\n  Content Browser -> Add -> Miscellaneous -> Data Asset -> Framework2DTileMapAsset\ny se pinta en el viewport con el modo \"Framework2D Tiles\".\n\nLas capas van de ATRAS (indice 0) a DELANTE: cada una en su plano, mas cerca de la camara." },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_TileSet_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Tileset del que salen los tiles (y sus materiales).\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileMapAsset.h" },
		{ "ToolTip", "Tileset del que salen los tiles (y sus materiales)." },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_TileSet = { "TileSet", nullptr, (EPropertyFlags)0x0014000000000015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTileMapAsset, TileSet), Z_Construct_UClass_UFramework2DTileSet_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_TileSet_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_TileSet_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_Width_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "1024" },
		{ "ClampMin", "1" },
		{ "Comment", "// Ancho del nivel EN TILES. Al cambiarlo se conserva lo pintado que quepa.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileMapAsset.h" },
		{ "ToolTip", "Ancho del nivel EN TILES. Al cambiarlo se conserva lo pintado que quepa." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_Width = { "Width", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTileMapAsset, Width), METADATA_PARAMS(Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_Width_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_Width_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_Height_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "1024" },
		{ "ClampMin", "1" },
		{ "Comment", "// Alto del nivel EN TILES.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileMapAsset.h" },
		{ "ToolTip", "Alto del nivel EN TILES." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_Height = { "Height", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTileMapAsset, Height), METADATA_PARAMS(Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_Height_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_Height_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_Layers_Inner = { "Layers", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FFramework2DTileLayer, METADATA_PARAMS(nullptr, 0) }; // 1044875417
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_Layers_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Capas, de atras (0) a delante.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileMapAsset.h" },
		{ "TitleProperty", "Name" },
		{ "ToolTip", "Capas, de atras (0) a delante." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_Layers = { "Layers", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTileMapAsset, Layers), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_Layers_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_Layers_MetaData)) }; // 1044875417
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_CollisionOverrides_Inner = { "CollisionOverrides", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_CollisionOverrides_MetaData[] = {
		{ "Comment", "/**\n\x09 * Colision pintada celda a celda con el pincel de colision (una por tile del mapa, comun a\n\x09 * todas las capas). Valor = EFramework2DCollisionShape; Auto (0) = lo que diga el TileSet.\n\x09 * Vacia hasta que se pinta la primera.\n\x09 */" },
		{ "ModuleRelativePath", "Public/Framework2DTileMapAsset.h" },
		{ "ToolTip", "Colision pintada celda a celda con el pincel de colision (una por tile del mapa, comun a\ntodas las capas). Valor = EFramework2DCollisionShape; Auto (0) = lo que diga el TileSet.\nVacia hasta que se pinta la primera." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_CollisionOverrides = { "CollisionOverrides", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTileMapAsset, CollisionOverrides), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_CollisionOverrides_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_CollisionOverrides_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_ProcGen_MetaData[] = {
		{ "Category", "Framework2D|Procedural" },
		{ "Comment", "// Receta del generador procedural (modo Framework2D Tiles > pestana \"Generar\"): alturas,\n// rampas, agua, decoracion, semilla... Cada mapa recuerda la suya.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileMapAsset.h" },
		{ "ToolTip", "Receta del generador procedural (modo Framework2D Tiles > pestana \"Generar\"): alturas,\nrampas, agua, decoracion, semilla... Cada mapa recuerda la suya." },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_ProcGen = { "ProcGen", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTileMapAsset, ProcGen), Z_Construct_UScriptStruct_FFramework2DProcGenSettings, METADATA_PARAMS(Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_ProcGen_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_ProcGen_MetaData)) }; // 2513702000
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_Backdrops_Inner = { "Backdrops", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FFramework2DBackdropLayer, METADATA_PARAMS(nullptr, 0) }; // 3674502919
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_Backdrops_MetaData[] = {
		{ "Category", "Framework2D|Background" },
		{ "Comment", "// Fondos parallax del nivel (cielo, montanas...), de atras a delante. Los pone el generador\n// (los del bioma) y tambien se pueden editar aqui a mano.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileMapAsset.h" },
		{ "TitleProperty", "Name" },
		{ "ToolTip", "Fondos parallax del nivel (cielo, montanas...), de atras a delante. Los pone el generador\n(los del bioma) y tambien se pueden editar aqui a mano." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_Backdrops = { "Backdrops", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTileMapAsset, Backdrops), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_Backdrops_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_Backdrops_MetaData)) }; // 3674502919
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_PropInstances_Inner = { "PropInstances", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FFramework2DPropInstance, METADATA_PARAMS(nullptr, 0) }; // 1687910061
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_PropInstances_MetaData[] = {
		{ "Category", "Framework2D|Objects" },
		{ "Comment", "// Objetos grandes colocados (arboles, rocas...). Los pone el generador procedural.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileMapAsset.h" },
		{ "ToolTip", "Objetos grandes colocados (arboles, rocas...). Los pone el generador procedural." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_PropInstances = { "PropInstances", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTileMapAsset, PropInstances), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_PropInstances_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_PropInstances_MetaData)) }; // 1687910061
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UFramework2DTileMapAsset_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_TileSet,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_Width,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_Height,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_Layers_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_Layers,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_CollisionOverrides_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_CollisionOverrides,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_ProcGen,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_Backdrops_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_Backdrops,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_PropInstances_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileMapAsset_Statics::NewProp_PropInstances,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UFramework2DTileMapAsset_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFramework2DTileMapAsset>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UFramework2DTileMapAsset_Statics::ClassParams = {
		&UFramework2DTileMapAsset::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UFramework2DTileMapAsset_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTileMapAsset_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UFramework2DTileMapAsset_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTileMapAsset_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UFramework2DTileMapAsset()
	{
		if (!Z_Registration_Info_UClass_UFramework2DTileMapAsset.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UFramework2DTileMapAsset.OuterSingleton, Z_Construct_UClass_UFramework2DTileMapAsset_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UFramework2DTileMapAsset.OuterSingleton;
	}
	template<> FRAMEWORK2DTERRAIN_API UClass* StaticClass<UFramework2DTileMapAsset>()
	{
		return UFramework2DTileMapAsset::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UFramework2DTileMapAsset);
	struct Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTileMapAsset_h_Statics
	{
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTileMapAsset_h_Statics::ScriptStructInfo[] = {
		{ FFramework2DTileLayer::StaticStruct, Z_Construct_UScriptStruct_FFramework2DTileLayer_Statics::NewStructOps, TEXT("Framework2DTileLayer"), &Z_Registration_Info_UScriptStruct_Framework2DTileLayer, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FFramework2DTileLayer), 1044875417U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTileMapAsset_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UFramework2DTileMapAsset, UFramework2DTileMapAsset::StaticClass, TEXT("UFramework2DTileMapAsset"), &Z_Registration_Info_UClass_UFramework2DTileMapAsset, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UFramework2DTileMapAsset), 1469795097U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTileMapAsset_h_1446709233(TEXT("/Script/Framework2DTerrain"),
		Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTileMapAsset_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTileMapAsset_h_Statics::ClassInfo),
		Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTileMapAsset_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTileMapAsset_h_Statics::ScriptStructInfo),
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
