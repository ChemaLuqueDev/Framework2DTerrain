// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Framework2DTerrain/Public/Framework2DProcGen.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFramework2DProcGen() {}
// Cross Module References
	FRAMEWORK2DTERRAIN_API UClass* Z_Construct_UClass_UFramework2DProcGenLibrary_NoRegister();
	FRAMEWORK2DTERRAIN_API UClass* Z_Construct_UClass_UFramework2DProcGenLibrary();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	UPackage* Z_Construct_UPackage__Script_Framework2DTerrain();
	FRAMEWORK2DTERRAIN_API UClass* Z_Construct_UClass_UFramework2DTileMapAsset_NoRegister();
	FRAMEWORK2DTERRAIN_API UScriptStruct* Z_Construct_UScriptStruct_FFramework2DProcGenReport();
	FRAMEWORK2DTERRAIN_API UScriptStruct* Z_Construct_UScriptStruct_FFramework2DProcGenSettings();
	FRAMEWORK2DTERRAIN_API UClass* Z_Construct_UClass_UFramework2DTileSet_NoRegister();
	FRAMEWORK2DTERRAIN_API UScriptStruct* Z_Construct_UScriptStruct_FFramework2DBiome();
// End Cross Module References
	DEFINE_FUNCTION(UFramework2DProcGenLibrary::execGetBiomeProblem)
	{
		P_GET_OBJECT(UFramework2DTileSet,Z_Param_Set);
		P_GET_STRUCT_REF(FFramework2DBiome,Z_Param_Out_Biome);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FText*)Z_Param__Result=UFramework2DProcGenLibrary::GetBiomeProblem(Z_Param_Set,Z_Param_Out_Biome);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFramework2DProcGenLibrary::execGenerateMapWithSettings)
	{
		P_GET_OBJECT(UFramework2DTileMapAsset,Z_Param_Map);
		P_GET_STRUCT_REF(FFramework2DProcGenSettings,Z_Param_Out_Settings);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FFramework2DProcGenReport*)Z_Param__Result=UFramework2DProcGenLibrary::GenerateMapWithSettings(Z_Param_Map,Z_Param_Out_Settings);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFramework2DProcGenLibrary::execGenerateMap)
	{
		P_GET_OBJECT(UFramework2DTileMapAsset,Z_Param_Map);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FFramework2DProcGenReport*)Z_Param__Result=UFramework2DProcGenLibrary::GenerateMap(Z_Param_Map);
		P_NATIVE_END;
	}
	void UFramework2DProcGenLibrary::StaticRegisterNativesUFramework2DProcGenLibrary()
	{
		UClass* Class = UFramework2DProcGenLibrary::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GenerateMap", &UFramework2DProcGenLibrary::execGenerateMap },
			{ "GenerateMapWithSettings", &UFramework2DProcGenLibrary::execGenerateMapWithSettings },
			{ "GetBiomeProblem", &UFramework2DProcGenLibrary::execGetBiomeProblem },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMap_Statics
	{
		struct Framework2DProcGenLibrary_eventGenerateMap_Parms
		{
			UFramework2DTileMapAsset* Map;
			FFramework2DProcGenReport ReturnValue;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Map;
		static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMap_Statics::NewProp_Map = { "Map", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DProcGenLibrary_eventGenerateMap_Parms, Map), Z_Construct_UClass_UFramework2DTileMapAsset_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMap_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DProcGenLibrary_eventGenerateMap_Parms, ReturnValue), Z_Construct_UScriptStruct_FFramework2DProcGenReport, METADATA_PARAMS(nullptr, 0) }; // 2526618478
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMap_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMap_Statics::NewProp_Map,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMap_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMap_Statics::Function_MetaDataParams[] = {
		{ "Category", "Framework2D|Procedural" },
		{ "Comment", "/**\n\x09 * Genera un nivel en el Tile Map con SU receta (ProcGen) y el bioma de su Tile Set, y lo\n\x09 * escribe en sus capas. Reemplaza las capas Terreno, Fondo, Agua y Decoracion.\n\x09 */" },
		{ "ModuleRelativePath", "Public/Framework2DProcGen.h" },
		{ "ToolTip", "Genera un nivel en el Tile Map con SU receta (ProcGen) y el bioma de su Tile Set, y lo\nescribe en sus capas. Reemplaza las capas Terreno, Fondo, Agua y Decoracion." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMap_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFramework2DProcGenLibrary, nullptr, "GenerateMap", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMap_Statics::Framework2DProcGenLibrary_eventGenerateMap_Parms), Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMap_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMap_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMap_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMap_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMap()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMap_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMapWithSettings_Statics
	{
		struct Framework2DProcGenLibrary_eventGenerateMapWithSettings_Parms
		{
			UFramework2DTileMapAsset* Map;
			FFramework2DProcGenSettings Settings;
			FFramework2DProcGenReport ReturnValue;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Map;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Settings_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Settings;
		static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMapWithSettings_Statics::NewProp_Map = { "Map", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DProcGenLibrary_eventGenerateMapWithSettings_Parms, Map), Z_Construct_UClass_UFramework2DTileMapAsset_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMapWithSettings_Statics::NewProp_Settings_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMapWithSettings_Statics::NewProp_Settings = { "Settings", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DProcGenLibrary_eventGenerateMapWithSettings_Parms, Settings), Z_Construct_UScriptStruct_FFramework2DProcGenSettings, METADATA_PARAMS(Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMapWithSettings_Statics::NewProp_Settings_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMapWithSettings_Statics::NewProp_Settings_MetaData)) }; // 2513702000
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMapWithSettings_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DProcGenLibrary_eventGenerateMapWithSettings_Parms, ReturnValue), Z_Construct_UScriptStruct_FFramework2DProcGenReport, METADATA_PARAMS(nullptr, 0) }; // 2526618478
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMapWithSettings_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMapWithSettings_Statics::NewProp_Map,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMapWithSettings_Statics::NewProp_Settings,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMapWithSettings_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMapWithSettings_Statics::Function_MetaDataParams[] = {
		{ "Category", "Framework2D|Procedural" },
		{ "Comment", "/** Como Generate Map, pero con otra receta (la del mapa no cambia). */" },
		{ "ModuleRelativePath", "Public/Framework2DProcGen.h" },
		{ "ToolTip", "Como Generate Map, pero con otra receta (la del mapa no cambia)." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMapWithSettings_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFramework2DProcGenLibrary, nullptr, "GenerateMapWithSettings", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMapWithSettings_Statics::Framework2DProcGenLibrary_eventGenerateMapWithSettings_Parms), Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMapWithSettings_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMapWithSettings_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMapWithSettings_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMapWithSettings_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMapWithSettings()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMapWithSettings_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFramework2DProcGenLibrary_GetBiomeProblem_Statics
	{
		struct Framework2DProcGenLibrary_eventGetBiomeProblem_Parms
		{
			const UFramework2DTileSet* Set;
			FFramework2DBiome Biome;
			FText ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Set_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Set;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Biome_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Biome;
		static const UECodeGen_Private::FTextPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFramework2DProcGenLibrary_GetBiomeProblem_Statics::NewProp_Set_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFramework2DProcGenLibrary_GetBiomeProblem_Statics::NewProp_Set = { "Set", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DProcGenLibrary_eventGetBiomeProblem_Parms, Set), Z_Construct_UClass_UFramework2DTileSet_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_UFramework2DProcGenLibrary_GetBiomeProblem_Statics::NewProp_Set_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DProcGenLibrary_GetBiomeProblem_Statics::NewProp_Set_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFramework2DProcGenLibrary_GetBiomeProblem_Statics::NewProp_Biome_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFramework2DProcGenLibrary_GetBiomeProblem_Statics::NewProp_Biome = { "Biome", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DProcGenLibrary_eventGetBiomeProblem_Parms, Biome), Z_Construct_UScriptStruct_FFramework2DBiome, METADATA_PARAMS(Z_Construct_UFunction_UFramework2DProcGenLibrary_GetBiomeProblem_Statics::NewProp_Biome_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DProcGenLibrary_GetBiomeProblem_Statics::NewProp_Biome_MetaData)) }; // 2776837089
	const UECodeGen_Private::FTextPropertyParams Z_Construct_UFunction_UFramework2DProcGenLibrary_GetBiomeProblem_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DProcGenLibrary_eventGetBiomeProblem_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFramework2DProcGenLibrary_GetBiomeProblem_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DProcGenLibrary_GetBiomeProblem_Statics::NewProp_Set,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DProcGenLibrary_GetBiomeProblem_Statics::NewProp_Biome,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DProcGenLibrary_GetBiomeProblem_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFramework2DProcGenLibrary_GetBiomeProblem_Statics::Function_MetaDataParams[] = {
		{ "Category", "Framework2D|Procedural" },
		{ "Comment", "/** Que le falta al bioma para poder generar. Vacio = listo. */" },
		{ "ModuleRelativePath", "Public/Framework2DProcGen.h" },
		{ "ToolTip", "Que le falta al bioma para poder generar. Vacio = listo." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFramework2DProcGenLibrary_GetBiomeProblem_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFramework2DProcGenLibrary, nullptr, "GetBiomeProblem", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFramework2DProcGenLibrary_GetBiomeProblem_Statics::Framework2DProcGenLibrary_eventGetBiomeProblem_Parms), Z_Construct_UFunction_UFramework2DProcGenLibrary_GetBiomeProblem_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DProcGenLibrary_GetBiomeProblem_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFramework2DProcGenLibrary_GetBiomeProblem_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DProcGenLibrary_GetBiomeProblem_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFramework2DProcGenLibrary_GetBiomeProblem()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFramework2DProcGenLibrary_GetBiomeProblem_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UFramework2DProcGenLibrary);
	UClass* Z_Construct_UClass_UFramework2DProcGenLibrary_NoRegister()
	{
		return UFramework2DProcGenLibrary::StaticClass();
	}
	struct Z_Construct_UClass_UFramework2DProcGenLibrary_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UFramework2DProcGenLibrary_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_Framework2DTerrain,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UFramework2DProcGenLibrary_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMap, "GenerateMap" }, // 3419294182
		{ &Z_Construct_UFunction_UFramework2DProcGenLibrary_GenerateMapWithSettings, "GenerateMapWithSettings" }, // 4011764591
		{ &Z_Construct_UFunction_UFramework2DProcGenLibrary_GetBiomeProblem, "GetBiomeProblem" }, // 1859513109
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DProcGenLibrary_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * GENERADOR PROCEDURAL DE MAPAS\n * =================================================================\n * Construye un nivel de plataformas de lado (alturas, rampas, fosos, lagos, cascadas,\n * plataformas flotantes, fondo y decoracion) con las piezas de un BIOMA y los ajustes de una\n * RECETA. Determinista: misma receta + misma semilla = mismo nivel. Cada parte usa su propio\n * flujo aleatorio, asi que tocar la decoracion no mueve el relieve.\n *\n * Desde el editor: modo Framework2D Tiles > pestana \"Generar\". Desde Blueprint: Generate Map\n * (sobre un Tile Map) o Generate Procedural Level (sobre el terreno, en juego).\n */" },
		{ "IncludePath", "Framework2DProcGen.h" },
		{ "ModuleRelativePath", "Public/Framework2DProcGen.h" },
		{ "ToolTip", "GENERADOR PROCEDURAL DE MAPAS\n\nConstruye un nivel de plataformas de lado (alturas, rampas, fosos, lagos, cascadas,\nplataformas flotantes, fondo y decoracion) con las piezas de un BIOMA y los ajustes de una\nRECETA. Determinista: misma receta + misma semilla = mismo nivel. Cada parte usa su propio\nflujo aleatorio, asi que tocar la decoracion no mueve el relieve.\n\nDesde el editor: modo Framework2D Tiles > pestana \"Generar\". Desde Blueprint: Generate Map\n(sobre un Tile Map) o Generate Procedural Level (sobre el terreno, en juego)." },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UFramework2DProcGenLibrary_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFramework2DProcGenLibrary>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UFramework2DProcGenLibrary_Statics::ClassParams = {
		&UFramework2DProcGenLibrary::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UFramework2DProcGenLibrary_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DProcGenLibrary_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UFramework2DProcGenLibrary()
	{
		if (!Z_Registration_Info_UClass_UFramework2DProcGenLibrary.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UFramework2DProcGenLibrary.OuterSingleton, Z_Construct_UClass_UFramework2DProcGenLibrary_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UFramework2DProcGenLibrary.OuterSingleton;
	}
	template<> FRAMEWORK2DTERRAIN_API UClass* StaticClass<UFramework2DProcGenLibrary>()
	{
		return UFramework2DProcGenLibrary::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UFramework2DProcGenLibrary);
	struct Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DProcGen_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DProcGen_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UFramework2DProcGenLibrary, UFramework2DProcGenLibrary::StaticClass, TEXT("UFramework2DProcGenLibrary"), &Z_Registration_Info_UClass_UFramework2DProcGenLibrary, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UFramework2DProcGenLibrary), 3318122308U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DProcGen_h_2469250863(TEXT("/Script/Framework2DTerrain"),
		Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DProcGen_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DProcGen_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
