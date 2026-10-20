// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Framework2DTerrain/Public/Framework2DBackdropComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFramework2DBackdropComponent() {}
// Cross Module References
	FRAMEWORK2DTERRAIN_API UClass* Z_Construct_UClass_UFramework2DBackdropComponent_NoRegister();
	FRAMEWORK2DTERRAIN_API UClass* Z_Construct_UClass_UFramework2DBackdropComponent();
	PROCEDURALMESHCOMPONENT_API UClass* Z_Construct_UClass_UProceduralMeshComponent();
	UPackage* Z_Construct_UPackage__Script_Framework2DTerrain();
	ENGINE_API UClass* Z_Construct_UClass_UMaterialInstanceDynamic_NoRegister();
// End Cross Module References
	void UFramework2DBackdropComponent::StaticRegisterNativesUFramework2DBackdropComponent()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UFramework2DBackdropComponent);
	UClass* Z_Construct_UClass_UFramework2DBackdropComponent_NoRegister()
	{
		return UFramework2DBackdropComponent::StaticClass();
	}
	struct Z_Construct_UClass_UFramework2DBackdropComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_LayerMIDs_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_LayerMIDs_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_LayerMIDs;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UFramework2DBackdropComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UProceduralMeshComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_Framework2DTerrain,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DBackdropComponent_Statics::Class_MetaDataParams[] = {
		{ "ClassGroupNames", "Framework2D" },
		{ "Comment", "/**\n * UFramework2DBackdropComponent\n * =================================================================\n * Los FONDOS PARALLAX del terreno: un plano por capa (cielo, montanas, bosque lejano...)\n * detras de todas las capas del Tile Map. Cada frame, DESPUES de que se mueva la camara\n * (grupo PostUpdateWork, asi no tiembla), recoloca las imagenes segun su Parallax: 0 = quietas\n * en la pantalla, 1 = pegadas al nivel. Funciona en el editor (camara del viewport) y en juego.\n *\n * Lo crea y lo configura el terreno (AFramework2DTerrainWorld); no hace falta tocarlo.\n */" },
		{ "HideCategories", "Object LOD Mobility Trigger" },
		{ "IncludePath", "Framework2DBackdropComponent.h" },
		{ "ModuleRelativePath", "Public/Framework2DBackdropComponent.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
		{ "ToolTip", "UFramework2DBackdropComponent\n\nLos FONDOS PARALLAX del terreno: un plano por capa (cielo, montanas, bosque lejano...)\ndetras de todas las capas del Tile Map. Cada frame, DESPUES de que se mueva la camara\n(grupo PostUpdateWork, asi no tiembla), recoloca las imagenes segun su Parallax: 0 = quietas\nen la pantalla, 1 = pegadas al nivel. Funciona en el editor (camara del viewport) y en juego.\n\nLo crea y lo configura el terreno (AFramework2DTerrainWorld); no hace falta tocarlo." },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_UFramework2DBackdropComponent_Statics::NewProp_LayerMIDs_Inner = { "LayerMIDs", nullptr, (EPropertyFlags)0x0004000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UMaterialInstanceDynamic_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DBackdropComponent_Statics::NewProp_LayerMIDs_MetaData[] = {
		{ "ModuleRelativePath", "Public/Framework2DBackdropComponent.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UFramework2DBackdropComponent_Statics::NewProp_LayerMIDs = { "LayerMIDs", nullptr, (EPropertyFlags)0x0044000400002000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DBackdropComponent, LayerMIDs), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UFramework2DBackdropComponent_Statics::NewProp_LayerMIDs_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DBackdropComponent_Statics::NewProp_LayerMIDs_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UFramework2DBackdropComponent_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DBackdropComponent_Statics::NewProp_LayerMIDs_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DBackdropComponent_Statics::NewProp_LayerMIDs,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UFramework2DBackdropComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFramework2DBackdropComponent>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UFramework2DBackdropComponent_Statics::ClassParams = {
		&UFramework2DBackdropComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UFramework2DBackdropComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DBackdropComponent_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UFramework2DBackdropComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DBackdropComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UFramework2DBackdropComponent()
	{
		if (!Z_Registration_Info_UClass_UFramework2DBackdropComponent.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UFramework2DBackdropComponent.OuterSingleton, Z_Construct_UClass_UFramework2DBackdropComponent_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UFramework2DBackdropComponent.OuterSingleton;
	}
	template<> FRAMEWORK2DTERRAIN_API UClass* StaticClass<UFramework2DBackdropComponent>()
	{
		return UFramework2DBackdropComponent::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UFramework2DBackdropComponent);
	struct Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DBackdropComponent_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DBackdropComponent_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UFramework2DBackdropComponent, UFramework2DBackdropComponent::StaticClass, TEXT("UFramework2DBackdropComponent"), &Z_Registration_Info_UClass_UFramework2DBackdropComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UFramework2DBackdropComponent), 2637589583U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DBackdropComponent_h_3084749238(TEXT("/Script/Framework2DTerrain"),
		Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DBackdropComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DBackdropComponent_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
