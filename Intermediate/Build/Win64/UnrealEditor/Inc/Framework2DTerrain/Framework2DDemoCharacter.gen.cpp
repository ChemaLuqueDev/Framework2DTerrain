// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Framework2DTerrain/Public/Framework2DDemoCharacter.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFramework2DDemoCharacter() {}
// Cross Module References
	FRAMEWORK2DTERRAIN_API UClass* Z_Construct_UClass_AFramework2DDemoCharacter_NoRegister();
	FRAMEWORK2DTERRAIN_API UClass* Z_Construct_UClass_AFramework2DDemoCharacter();
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
	UPackage* Z_Construct_UPackage__Script_Framework2DTerrain();
	FRAMEWORK2DTERRAIN_API UClass* Z_Construct_UClass_UFramework2DTerraformComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
	FRAMEWORK2DTERRAIN_API UClass* Z_Construct_UClass_AFramework2DTerrainWorld_NoRegister();
// End Cross Module References
	void AFramework2DDemoCharacter::StaticRegisterNativesAFramework2DDemoCharacter()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AFramework2DDemoCharacter);
	UClass* Z_Construct_UClass_AFramework2DDemoCharacter_NoRegister()
	{
		return AFramework2DDemoCharacter::StaticClass();
	}
	struct Z_Construct_UClass_AFramework2DDemoCharacter_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MoveInputScale_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_MoveInputScale;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ExplosionRadius_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_ExplosionRadius;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CameraDistance_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_CameraDistance;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bShowInventory_MetaData[];
#endif
		static void NewProp_bShowInventory_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bShowInventory;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Terraform_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_Terraform;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Camera_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_Camera;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Terrain_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_Terrain;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AFramework2DDemoCharacter_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_Framework2DTerrain,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFramework2DDemoCharacter_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * AFramework2DDemoCharacter\n * =================================================================\n * Personaje de DEMO para probar la rotura estilo KYORA sin montar nada.\n *   - A / D  (o flechas)  -> moverse izquierda / derecha\n *   - Espacio / W         -> saltar\n *   - Clic IZQUIERDO      -> picar donde apunta el raton (lo picado va al inventario)\n *   - Clic DERECHO        -> colocar el material seleccionado (gasta inventario)\n *   - Rueda / Q / E       -> cambiar de material\n *   - Clic CENTRAL / F    -> explosion en el raton\n *\n * Se auto-posee (Player 0) y busca solo el AFramework2DTerrainWorld del nivel.\n * Movimiento bloqueado al plano XZ (2D), gravedad -Z estandar de Unreal.\n * El inventario se muestra arriba a la izquierda (mensajes de depuracion).\n *\n * COMO USARLO:\n *   Opcion A (rapida): arrastra este actor al nivel, cerca del terreno, y Play.\n *   Opcion B (recomendada): clic derecho sobre la clase -> Create Blueprint class,\n *     abre el Blueprint, asigna una Skeletal/Static Mesh al componente Mesh si\n *     quieres verlo, y coloca ESE Blueprint en el nivel.\n *\n * No usa Enhanced Input a proposito: sondea las teclas en Tick para que funcione\n * sin configurar Input Mappings en Project Settings.\n */" },
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Framework2DDemoCharacter.h" },
		{ "ModuleRelativePath", "Public/Framework2DDemoCharacter.h" },
		{ "ToolTip", "AFramework2DDemoCharacter\n\nPersonaje de DEMO para probar la rotura estilo KYORA sin montar nada.\n  - A / D  (o flechas)  -> moverse izquierda / derecha\n  - Espacio / W         -> saltar\n  - Clic IZQUIERDO      -> picar donde apunta el raton (lo picado va al inventario)\n  - Clic DERECHO        -> colocar el material seleccionado (gasta inventario)\n  - Rueda / Q / E       -> cambiar de material\n  - Clic CENTRAL / F    -> explosion en el raton\n\nSe auto-posee (Player 0) y busca solo el AFramework2DTerrainWorld del nivel.\nMovimiento bloqueado al plano XZ (2D), gravedad -Z estandar de Unreal.\nEl inventario se muestra arriba a la izquierda (mensajes de depuracion).\n\nCOMO USARLO:\n  Opcion A (rapida): arrastra este actor al nivel, cerca del terreno, y Play.\n  Opcion B (recomendada): clic derecho sobre la clase -> Create Blueprint class,\n    abre el Blueprint, asigna una Skeletal/Static Mesh al componente Mesh si\n    quieres verlo, y coloca ESE Blueprint en el nivel.\n\nNo usa Enhanced Input a proposito: sondea las teclas en Tick para que funcione\nsin configurar Input Mappings en Project Settings." },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_MoveInputScale_MetaData[] = {
		{ "Category", "Framework2D Demo" },
		{ "Comment", "/** Multiplicador de velocidad de movimiento. */" },
		{ "ModuleRelativePath", "Public/Framework2DDemoCharacter.h" },
		{ "ToolTip", "Multiplicador de velocidad de movimiento." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_MoveInputScale = { "MoveInputScale", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFramework2DDemoCharacter, MoveInputScale), METADATA_PARAMS(Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_MoveInputScale_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_MoveInputScale_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_ExplosionRadius_MetaData[] = {
		{ "Category", "Framework2D Demo" },
		{ "Comment", "/** Radio (cm) de la explosion de prueba (clic central / F). */" },
		{ "ModuleRelativePath", "Public/Framework2DDemoCharacter.h" },
		{ "ToolTip", "Radio (cm) de la explosion de prueba (clic central / F)." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_ExplosionRadius = { "ExplosionRadius", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFramework2DDemoCharacter, ExplosionRadius), METADATA_PARAMS(Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_ExplosionRadius_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_ExplosionRadius_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_CameraDistance_MetaData[] = {
		{ "Category", "Framework2D Demo" },
		{ "Comment", "/** Distancia de la camara al personaje (en el eje +Y, mirando hacia -Y). */" },
		{ "ModuleRelativePath", "Public/Framework2DDemoCharacter.h" },
		{ "ToolTip", "Distancia de la camara al personaje (en el eje +Y, mirando hacia -Y)." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_CameraDistance = { "CameraDistance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFramework2DDemoCharacter, CameraDistance), METADATA_PARAMS(Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_CameraDistance_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_CameraDistance_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_bShowInventory_MetaData[] = {
		{ "Category", "Framework2D Demo" },
		{ "Comment", "/** Muestra el inventario en pantalla. */" },
		{ "ModuleRelativePath", "Public/Framework2DDemoCharacter.h" },
		{ "ToolTip", "Muestra el inventario en pantalla." },
	};
#endif
	void Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_bShowInventory_SetBit(void* Obj)
	{
		((AFramework2DDemoCharacter*)Obj)->bShowInventory = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_bShowInventory = { "bShowInventory", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(AFramework2DDemoCharacter), &Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_bShowInventory_SetBit, METADATA_PARAMS(Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_bShowInventory_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_bShowInventory_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_Terraform_MetaData[] = {
		{ "Category", "Framework2D Demo" },
		{ "Comment", "/** La varita: picar, recoger y colocar. Ajusta aqui alcance, dano, radios... */" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Framework2DDemoCharacter.h" },
		{ "ToolTip", "La varita: picar, recoger y colocar. Ajusta aqui alcance, dano, radios..." },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_Terraform = { "Terraform", nullptr, (EPropertyFlags)0x00140000000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFramework2DDemoCharacter, Terraform), Z_Construct_UClass_UFramework2DTerraformComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_Terraform_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_Terraform_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_Camera_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Framework2DDemoCharacter.h" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_Camera = { "Camera", nullptr, (EPropertyFlags)0x0044000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFramework2DDemoCharacter, Camera), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_Camera_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_Camera_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_Terrain_MetaData[] = {
		{ "ModuleRelativePath", "Public/Framework2DDemoCharacter.h" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_Terrain = { "Terrain", nullptr, (EPropertyFlags)0x0044000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AFramework2DDemoCharacter, Terrain), Z_Construct_UClass_AFramework2DTerrainWorld_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_Terrain_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_Terrain_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AFramework2DDemoCharacter_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_MoveInputScale,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_ExplosionRadius,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_CameraDistance,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_bShowInventory,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_Terraform,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_Camera,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFramework2DDemoCharacter_Statics::NewProp_Terrain,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AFramework2DDemoCharacter_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AFramework2DDemoCharacter>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AFramework2DDemoCharacter_Statics::ClassParams = {
		&AFramework2DDemoCharacter::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AFramework2DDemoCharacter_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AFramework2DDemoCharacter_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AFramework2DDemoCharacter_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AFramework2DDemoCharacter_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AFramework2DDemoCharacter()
	{
		if (!Z_Registration_Info_UClass_AFramework2DDemoCharacter.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AFramework2DDemoCharacter.OuterSingleton, Z_Construct_UClass_AFramework2DDemoCharacter_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AFramework2DDemoCharacter.OuterSingleton;
	}
	template<> FRAMEWORK2DTERRAIN_API UClass* StaticClass<AFramework2DDemoCharacter>()
	{
		return AFramework2DDemoCharacter::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AFramework2DDemoCharacter);
	struct Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DDemoCharacter_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DDemoCharacter_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AFramework2DDemoCharacter, AFramework2DDemoCharacter::StaticClass, TEXT("AFramework2DDemoCharacter"), &Z_Registration_Info_UClass_AFramework2DDemoCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AFramework2DDemoCharacter), 3781619030U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DDemoCharacter_h_981907245(TEXT("/Script/Framework2DTerrain"),
		Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DDemoCharacter_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DDemoCharacter_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
