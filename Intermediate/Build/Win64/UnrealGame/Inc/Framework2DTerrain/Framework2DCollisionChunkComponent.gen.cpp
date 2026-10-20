// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Framework2DTerrain/Public/Framework2DCollisionChunkComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFramework2DCollisionChunkComponent() {}
// Cross Module References
	FRAMEWORK2DTERRAIN_API UClass* Z_Construct_UClass_UFramework2DCollisionChunkComponent_NoRegister();
	FRAMEWORK2DTERRAIN_API UClass* Z_Construct_UClass_UFramework2DCollisionChunkComponent();
	ENGINE_API UClass* Z_Construct_UClass_UPrimitiveComponent();
	UPackage* Z_Construct_UPackage__Script_Framework2DTerrain();
	ENGINE_API UClass* Z_Construct_UClass_UBodySetup_NoRegister();
// End Cross Module References
	void UFramework2DCollisionChunkComponent::StaticRegisterNativesUFramework2DCollisionChunkComponent()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UFramework2DCollisionChunkComponent);
	UClass* Z_Construct_UClass_UFramework2DCollisionChunkComponent_NoRegister()
	{
		return UFramework2DCollisionChunkComponent::StaticClass();
	}
	struct Z_Construct_UClass_UFramework2DCollisionChunkComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ChunkBodySetup_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_ChunkBodySetup;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UFramework2DCollisionChunkComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UPrimitiveComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_Framework2DTerrain,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DCollisionChunkComponent_Statics::Class_MetaDataParams[] = {
		{ "ClassGroupNames", "Framework2D" },
		{ "Comment", "/**\n * UFramework2DCollisionChunkComponent\n * =================================================================\n * Colision de UN trozo (chunk) del terreno. El actor de terreno crea una rejilla de estos\n * al empezar y, cuando picas, solo reconstruye los chunks tocados.\n *\n * Por que cajas y no una malla: la colision por malla (ProceduralMesh) hay que \"cocinarla\"\n * entera cada vez que cambia, y eso da tirones con mundos grandes. Aqui cada chunk es una\n * union de cajas (las del greedy-mesh) y las cajas NO necesitan cocinado: reconstruir un\n * chunk es practicamente gratis y el personaje se apoya en ellas igual que en una malla.\n *\n * No se dibuja (no tiene scene proxy): solo aporta fisica y trazas.\n */" },
		{ "HideCategories", "Mobility VirtualTexture Trigger" },
		{ "IncludePath", "Framework2DCollisionChunkComponent.h" },
		{ "ModuleRelativePath", "Public/Framework2DCollisionChunkComponent.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
		{ "ToolTip", "UFramework2DCollisionChunkComponent\n\nColision de UN trozo (chunk) del terreno. El actor de terreno crea una rejilla de estos\nal empezar y, cuando picas, solo reconstruye los chunks tocados.\n\nPor que cajas y no una malla: la colision por malla (ProceduralMesh) hay que \"cocinarla\"\nentera cada vez que cambia, y eso da tirones con mundos grandes. Aqui cada chunk es una\nunion de cajas (las del greedy-mesh) y las cajas NO necesitan cocinado: reconstruir un\nchunk es practicamente gratis y el personaje se apoya en ellas igual que en una malla.\n\nNo se dibuja (no tiene scene proxy): solo aporta fisica y trazas." },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DCollisionChunkComponent_Statics::NewProp_ChunkBodySetup_MetaData[] = {
		{ "ModuleRelativePath", "Public/Framework2DCollisionChunkComponent.h" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_UFramework2DCollisionChunkComponent_Statics::NewProp_ChunkBodySetup = { "ChunkBodySetup", nullptr, (EPropertyFlags)0x0044000000002000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DCollisionChunkComponent, ChunkBodySetup), Z_Construct_UClass_UBodySetup_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UFramework2DCollisionChunkComponent_Statics::NewProp_ChunkBodySetup_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DCollisionChunkComponent_Statics::NewProp_ChunkBodySetup_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UFramework2DCollisionChunkComponent_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DCollisionChunkComponent_Statics::NewProp_ChunkBodySetup,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UFramework2DCollisionChunkComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFramework2DCollisionChunkComponent>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UFramework2DCollisionChunkComponent_Statics::ClassParams = {
		&UFramework2DCollisionChunkComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UFramework2DCollisionChunkComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DCollisionChunkComponent_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UFramework2DCollisionChunkComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DCollisionChunkComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UFramework2DCollisionChunkComponent()
	{
		if (!Z_Registration_Info_UClass_UFramework2DCollisionChunkComponent.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UFramework2DCollisionChunkComponent.OuterSingleton, Z_Construct_UClass_UFramework2DCollisionChunkComponent_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UFramework2DCollisionChunkComponent.OuterSingleton;
	}
	template<> FRAMEWORK2DTERRAIN_API UClass* StaticClass<UFramework2DCollisionChunkComponent>()
	{
		return UFramework2DCollisionChunkComponent::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UFramework2DCollisionChunkComponent);
	struct Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DCollisionChunkComponent_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DCollisionChunkComponent_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UFramework2DCollisionChunkComponent, UFramework2DCollisionChunkComponent::StaticClass, TEXT("UFramework2DCollisionChunkComponent"), &Z_Registration_Info_UClass_UFramework2DCollisionChunkComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UFramework2DCollisionChunkComponent), 3451702097U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DCollisionChunkComponent_h_1698423426(TEXT("/Script/Framework2DTerrain"),
		Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DCollisionChunkComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DCollisionChunkComponent_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
