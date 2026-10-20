// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Framework2DTerrain/Public/Framework2DCharacter.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFramework2DCharacter() {}
// Cross Module References
	FRAMEWORK2DTERRAIN_API UClass* Z_Construct_UClass_AFramework2DCharacter_NoRegister();
	FRAMEWORK2DTERRAIN_API UClass* Z_Construct_UClass_AFramework2DCharacter();
	PAPER2D_API UClass* Z_Construct_UClass_APaperCharacter();
	UPackage* Z_Construct_UPackage__Script_Framework2DTerrain();
	FRAMEWORK2DTERRAIN_API UClass* Z_Construct_UClass_UFramework2DTerrainDeformerComponent_NoRegister();
// End Cross Module References
	void AFramework2DCharacter::StaticRegisterNativesAFramework2DCharacter()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AFramework2DCharacter);
	UClass* Z_Construct_UClass_AFramework2DCharacter_NoRegister()
	{
		return AFramework2DCharacter::StaticClass();
	}
	struct Z_Construct_UClass_AFramework2DCharacter_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TerrainDeformer_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_TerrainDeformer;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AFramework2DCharacter_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APaperCharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_Framework2DTerrain,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFramework2DCharacter_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * AFramework2DCharacter\n * =================================================================\n * Personaje base (Paper Character) que deforma el terreno con el CLIC IZQUIERDO, delante de el.\n *\n * Ponlo como padre de tu personaje: abre su Blueprint > Class Settings > Parent Class >\n * \"Framework2D Character\". No cambia nada de lo tuyo (movimiento, camara, sprite, componentes):\n * solo le anade el componente Terrain Deformer. Seleccionalo en la lista de componentes y ajusta\n * sus parametros en Details (radio, alcance, dano, golpes por segundo, teclas...).\n *\n * La explosion (bombas) va aparte: AFramework2DTerrainWorld::Explode.\n */" },
		{ "DisplayName", "Framework2D Character" },
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Framework2DCharacter.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/Framework2DCharacter.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
		{ "ToolTip", "AFramework2DCharacter\n\nPersonaje base (Paper Character) que deforma el terreno con el CLIC IZQUIERDO, delante de el.\n\nPonlo como padre de tu personaje: abre su Blueprint > Class Settings > Parent Class >\n\"Framework2D Character\". No cambia nada de lo tuyo (movimiento, camara, sprite, componentes):\nsolo le anade el componente Terrain Deformer. Seleccionalo en la lista de componentes y ajusta\nsus parametros en Details (radio, alcance, dano, golpes por segundo, teclas...).\n\nLa explosion (bombas) va aparte: AFramework2DTerrainWorld::Explode." },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFramework2DCharacter_Statics::NewProp_TerrainDeformer_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "/** Deforma el terreno delante del personaje (clic izquierdo). Sus parametros, en Details. */" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Framework2DCharacter.h" },
		{ "ToolTip", "Deforma el terreno delante del personaje (clic izquierdo). Sus parametros, en Details." },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_AFramework2DCharacter_Statics::NewProp_TerrainDeformer = { "TerrainDeformer", nullptr, (EPropertyFlags)0x00140000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFramework2DCharacter, TerrainDeformer), Z_Construct_UClass_UFramework2DTerrainDeformerComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AFramework2DCharacter_Statics::NewProp_TerrainDeformer_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFramework2DCharacter_Statics::NewProp_TerrainDeformer_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AFramework2DCharacter_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFramework2DCharacter_Statics::NewProp_TerrainDeformer,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AFramework2DCharacter_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AFramework2DCharacter>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AFramework2DCharacter_Statics::ClassParams = {
		&AFramework2DCharacter::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AFramework2DCharacter_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AFramework2DCharacter_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AFramework2DCharacter_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AFramework2DCharacter_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AFramework2DCharacter()
	{
		if (!Z_Registration_Info_UClass_AFramework2DCharacter.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AFramework2DCharacter.OuterSingleton, Z_Construct_UClass_AFramework2DCharacter_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AFramework2DCharacter.OuterSingleton;
	}
	template<> FRAMEWORK2DTERRAIN_API UClass* StaticClass<AFramework2DCharacter>()
	{
		return AFramework2DCharacter::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AFramework2DCharacter);
	struct Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DCharacter_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DCharacter_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AFramework2DCharacter, AFramework2DCharacter::StaticClass, TEXT("AFramework2DCharacter"), &Z_Registration_Info_UClass_AFramework2DCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AFramework2DCharacter), 3210611354U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DCharacter_h_2254854827(TEXT("/Script/Framework2DTerrain"),
		Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DCharacter_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DCharacter_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
