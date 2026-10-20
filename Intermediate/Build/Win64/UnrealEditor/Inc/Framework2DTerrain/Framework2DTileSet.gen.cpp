// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Framework2DTerrain/Public/Framework2DTileSet.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFramework2DTileSet() {}
// Cross Module References
	FRAMEWORK2DTERRAIN_API UScriptStruct* Z_Construct_UScriptStruct_FFramework2DTileDef();
	UPackage* Z_Construct_UPackage__Script_Framework2DTerrain();
	FRAMEWORK2DTERRAIN_API UEnum* Z_Construct_UEnum_Framework2DTerrain_EFramework2DCollisionShape();
	FRAMEWORK2DTERRAIN_API UScriptStruct* Z_Construct_UScriptStruct_FFramework2DFlipbook();
	FRAMEWORK2DTERRAIN_API UScriptStruct* Z_Construct_UScriptStruct_FFramework2DAtlasPage();
	ENGINE_API UClass* Z_Construct_UClass_UTexture2D_NoRegister();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FColor();
	FRAMEWORK2DTERRAIN_API UScriptStruct* Z_Construct_UScriptStruct_FFramework2DScatterSprite();
	FRAMEWORK2DTERRAIN_API UScriptStruct* Z_Construct_UScriptStruct_FFramework2DGenerator();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FLinearColor();
	FRAMEWORK2DTERRAIN_API UScriptStruct* Z_Construct_UScriptStruct_FFramework2DPropDef();
	FRAMEWORK2DTERRAIN_API UClass* Z_Construct_UClass_UFramework2DTileSet_NoRegister();
	FRAMEWORK2DTERRAIN_API UClass* Z_Construct_UClass_UFramework2DTileSet();
	ENGINE_API UClass* Z_Construct_UClass_UDataAsset();
	FRAMEWORK2DTERRAIN_API UScriptStruct* Z_Construct_UScriptStruct_FFramework2DMaterial();
	FRAMEWORK2DTERRAIN_API UScriptStruct* Z_Construct_UScriptStruct_FFramework2DBiome();
// End Cross Module References
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_Framework2DTileDef;
class UScriptStruct* FFramework2DTileDef::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_Framework2DTileDef.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_Framework2DTileDef.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FFramework2DTileDef, Z_Construct_UPackage__Script_Framework2DTerrain(), TEXT("Framework2DTileDef"));
	}
	return Z_Registration_Info_UScriptStruct_Framework2DTileDef.OuterSingleton;
}
template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<FFramework2DTileDef>()
{
	return FFramework2DTileDef::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FFramework2DTileDef_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MaterialName_MetaData[];
#endif
		static const UECodeGen_Private::FNamePropertyParams NewProp_MaterialName;
		static const UECodeGen_Private::FBytePropertyParams NewProp_Collision_Underlying;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Collision_MetaData[];
#endif
		static const UECodeGen_Private::FEnumPropertyParams NewProp_Collision;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bFillPattern_MetaData[];
#endif
		static void NewProp_bFillPattern_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bFillPattern;
		static const UECodeGen_Private::FIntPropertyParams NewProp_AnimationFrames_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AnimationFrames_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_AnimationFrames;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AnimationFPS_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_AnimationFPS;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/** Un tile del tileset. Su posicion en la lista Tiles es su numero en el atlas. */" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Un tile del tileset. Su posicion en la lista Tiles es su numero en el atlas." },
	};
#endif
	void* Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFramework2DTileDef>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::NewProp_MaterialName_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Material de este tile (de la lista Materials del tileset). \"None\" = el tile no es\n// terreno: en una capa normal no pone nada; en una capa de fondo se ve igual.\n" },
		{ "GetOptions", "GetMaterialNameOptions" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Material de este tile (de la lista Materials del tileset). \"None\" = el tile no es\nterreno: en una capa normal no pone nada; en una capa de fondo se ve igual." },
	};
#endif
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::NewProp_MaterialName = { "MaterialName", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DTileDef, MaterialName), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::NewProp_MaterialName_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::NewProp_MaterialName_MetaData)) };
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::NewProp_Collision_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::NewProp_Collision_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Colision de este tile en todos los mapas. Automatica = la del dibujo y su material.\n// Celda a celda se puede cambiar con el pincel de colision del modo Framework2D Tiles.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Colision de este tile en todos los mapas. Automatica = la del dibujo y su material.\nCelda a celda se puede cambiar con el pincel de colision del modo Framework2D Tiles." },
	};
#endif
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::NewProp_Collision = { "Collision", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DTileDef, Collision), Z_Construct_UEnum_Framework2DTerrain_EFramework2DCollisionShape, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::NewProp_Collision_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::NewProp_Collision_MetaData)) }; // 627041027
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::NewProp_bFillPattern_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Marca un tile \"interior\" (sin hierba ni bordes): las celdas de su material que el\n// jugador COLOCA se pintan con este dibujo, alineado a la rejilla de tiles.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Marca un tile \"interior\" (sin hierba ni bordes): las celdas de su material que el\njugador COLOCA se pintan con este dibujo, alineado a la rejilla de tiles." },
	};
#endif
	void Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::NewProp_bFillPattern_SetBit(void* Obj)
	{
		((FFramework2DTileDef*)Obj)->bFillPattern = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::NewProp_bFillPattern = { "bFillPattern", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FFramework2DTileDef), &Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::NewProp_bFillPattern_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::NewProp_bFillPattern_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::NewProp_bFillPattern_MetaData)) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::NewProp_AnimationFrames_Inner = { "AnimationFrames", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::NewProp_AnimationFrames_MetaData[] = {
		{ "Comment", "// OBSOLETO (v2.0): los flipbooks ahora viven en la lista Flipbooks del tileset y ya no\n// pisan el tile. Al cargar se migran solos (PostLoad) y estos campos quedan vacios.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "OBSOLETO (v2.0): los flipbooks ahora viven en la lista Flipbooks del tileset y ya no\npisan el tile. Al cargar se migran solos (PostLoad) y estos campos quedan vacios." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::NewProp_AnimationFrames = { "AnimationFrames", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DTileDef, AnimationFrames), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::NewProp_AnimationFrames_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::NewProp_AnimationFrames_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::NewProp_AnimationFPS_MetaData[] = {
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::NewProp_AnimationFPS = { "AnimationFPS", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DTileDef, AnimationFPS), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::NewProp_AnimationFPS_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::NewProp_AnimationFPS_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::NewProp_MaterialName,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::NewProp_Collision_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::NewProp_Collision,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::NewProp_bFillPattern,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::NewProp_AnimationFrames_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::NewProp_AnimationFrames,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::NewProp_AnimationFPS,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_Framework2DTerrain,
		nullptr,
		&NewStructOps,
		"Framework2DTileDef",
		sizeof(FFramework2DTileDef),
		alignof(FFramework2DTileDef),
		Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FFramework2DTileDef()
	{
		if (!Z_Registration_Info_UScriptStruct_Framework2DTileDef.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_Framework2DTileDef.InnerSingleton, Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_Framework2DTileDef.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_Framework2DFlipbook;
class UScriptStruct* FFramework2DFlipbook::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_Framework2DFlipbook.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_Framework2DFlipbook.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FFramework2DFlipbook, Z_Construct_UPackage__Script_Framework2DTerrain(), TEXT("Framework2DFlipbook"));
	}
	return Z_Registration_Info_UScriptStruct_Framework2DFlipbook.OuterSingleton;
}
template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<FFramework2DFlipbook>()
{
	return FFramework2DFlipbook::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics
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
		static const UECodeGen_Private::FIntPropertyParams NewProp_Frames_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Frames_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Frames;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FPS_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_FPS;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MaterialName_MetaData[];
#endif
		static const UECodeGen_Private::FNamePropertyParams NewProp_MaterialName;
		static const UECodeGen_Private::FBytePropertyParams NewProp_Collision_Underlying;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Collision_MetaData[];
#endif
		static const UECodeGen_Private::FEnumPropertyParams NewProp_Collision;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * Un FLIPBOOK (tile animado). Vive aparte de los tiles del atlas: crearlo no cambia ningun\n * tile. En el mapa se pinta como un tile mas (desde la seccion Flipbooks de la paleta).\n */" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Un FLIPBOOK (tile animado). Vive aparte de los tiles del atlas: crearlo no cambia ningun\ntile. En el mapa se pinta como un tile mas (desde la seccion Flipbooks de la paleta)." },
	};
#endif
	void* Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFramework2DFlipbook>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewProp_Name_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Nombre que se ve en la paleta.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Nombre que se ve en la paleta." },
	};
#endif
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DFlipbook, Name), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewProp_Name_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewProp_Name_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewProp_Id_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Identificador estable que guardan los mapas. No lo cambies a mano.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Identificador estable que guardan los mapas. No lo cambies a mano." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewProp_Id = { "Id", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DFlipbook, Id), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewProp_Id_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewProp_Id_MetaData)) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewProp_Frames_Inner = { "Frames", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewProp_Frames_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Fotogramas: numeros de tile del atlas, en orden (se cuentan desde 0, de izquierda a\n// derecha y de arriba abajo).\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Fotogramas: numeros de tile del atlas, en orden (se cuentan desde 0, de izquierda a\nderecha y de arriba abajo)." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewProp_Frames = { "Frames", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DFlipbook, Frames), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewProp_Frames_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewProp_Frames_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewProp_FPS_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "60.0" },
		{ "ClampMin", "0.1" },
		{ "Comment", "// Fotogramas por segundo.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Fotogramas por segundo." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewProp_FPS = { "FPS", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DFlipbook, FPS), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewProp_FPS_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewProp_FPS_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewProp_MaterialName_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Material de terreno del flipbook. Agua, hierba... suelen ser Decoration (no colisiona).\n" },
		{ "GetOptions", "GetMaterialNameOptions" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Material de terreno del flipbook. Agua, hierba... suelen ser Decoration (no colisiona)." },
	};
#endif
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewProp_MaterialName = { "MaterialName", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DFlipbook, MaterialName), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewProp_MaterialName_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewProp_MaterialName_MetaData)) };
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewProp_Collision_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewProp_Collision_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Colision del flipbook (como la de un tile).\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Colision del flipbook (como la de un tile)." },
	};
#endif
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewProp_Collision = { "Collision", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DFlipbook, Collision), Z_Construct_UEnum_Framework2DTerrain_EFramework2DCollisionShape, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewProp_Collision_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewProp_Collision_MetaData)) }; // 627041027
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewProp_Name,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewProp_Id,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewProp_Frames_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewProp_Frames,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewProp_FPS,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewProp_MaterialName,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewProp_Collision_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewProp_Collision,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_Framework2DTerrain,
		nullptr,
		&NewStructOps,
		"Framework2DFlipbook",
		sizeof(FFramework2DFlipbook),
		alignof(FFramework2DFlipbook),
		Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FFramework2DFlipbook()
	{
		if (!Z_Registration_Info_UScriptStruct_Framework2DFlipbook.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_Framework2DFlipbook.InnerSingleton, Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_Framework2DFlipbook.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_Framework2DAtlasPage;
class UScriptStruct* FFramework2DAtlasPage::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_Framework2DAtlasPage.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_Framework2DAtlasPage.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FFramework2DAtlasPage, Z_Construct_UPackage__Script_Framework2DTerrain(), TEXT("Framework2DAtlasPage"));
	}
	return Z_Registration_Info_UScriptStruct_Framework2DAtlasPage.OuterSingleton;
}
template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<FFramework2DAtlasPage>()
{
	return FFramework2DAtlasPage::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics
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
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Texture_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_Texture;
		static const UECodeGen_Private::FStructPropertyParams NewProp_Tiles_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Tiles_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Tiles;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Columns_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Columns;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Rows_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Rows;
		static const UECodeGen_Private::FStructPropertyParams NewProp_PixelCache_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PixelCache_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_PixelCache;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CacheWidth_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_CacheWidth;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CacheHeight_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_CacheHeight;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * Una PAGINA de atlas extra: otra imagen con tiles del mismo tamano (otro entorno: cueva,\n * bosque, desierto...). En la paleta sale como una pestana mas del atlas.\n */" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Una PAGINA de atlas extra: otra imagen con tiles del mismo tamano (otro entorno: cueva,\nbosque, desierto...). En la paleta sale como una pestana mas del atlas." },
	};
#endif
	void* Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFramework2DAtlasPage>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_Name_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Nombre de la pestana en la paleta.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Nombre de la pestana en la paleta." },
	};
#endif
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DAtlasPage, Name), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_Name_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_Name_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_Id_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Identificador estable que guardan los mapas. No lo cambies a mano.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Identificador estable que guardan los mapas. No lo cambies a mano." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_Id = { "Id", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DAtlasPage, Id), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_Id_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_Id_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_Texture_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// La imagen, con tiles del mismo tamano que el atlas principal (Tile Width x Tile Height).\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "La imagen, con tiles del mismo tamano que el atlas principal (Tile Width x Tile Height)." },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_Texture = { "Texture", nullptr, (EPropertyFlags)0x0014000000000015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DAtlasPage, Texture), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_Texture_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_Texture_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_Tiles_Inner = { "Tiles", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FFramework2DTileDef, METADATA_PARAMS(nullptr, 0) }; // 2854456691
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_Tiles_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Un tile por cada hueco de la imagen (se crean solos).\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "TitleProperty", "MaterialName" },
		{ "ToolTip", "Un tile por cada hueco de la imagen (se crean solos)." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_Tiles = { "Tiles", nullptr, (EPropertyFlags)0x0010000000000055, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DAtlasPage, Tiles), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_Tiles_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_Tiles_MetaData)) }; // 2854456691
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_Columns_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_Columns = { "Columns", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DAtlasPage, Columns), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_Columns_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_Columns_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_Rows_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_Rows = { "Rows", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DAtlasPage, Rows), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_Rows_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_Rows_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_PixelCache_Inner = { "PixelCache", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FColor, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_PixelCache_MetaData[] = {
		{ "Comment", "// Copia CPU de la imagen para el juego empaquetado (se rellena al guardar).\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Copia CPU de la imagen para el juego empaquetado (se rellena al guardar)." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_PixelCache = { "PixelCache", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DAtlasPage, PixelCache), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_PixelCache_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_PixelCache_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_CacheWidth_MetaData[] = {
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_CacheWidth = { "CacheWidth", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DAtlasPage, CacheWidth), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_CacheWidth_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_CacheWidth_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_CacheHeight_MetaData[] = {
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_CacheHeight = { "CacheHeight", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DAtlasPage, CacheHeight), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_CacheHeight_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_CacheHeight_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_Name,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_Id,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_Texture,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_Tiles_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_Tiles,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_Columns,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_Rows,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_PixelCache_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_PixelCache,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_CacheWidth,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewProp_CacheHeight,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_Framework2DTerrain,
		nullptr,
		&NewStructOps,
		"Framework2DAtlasPage",
		sizeof(FFramework2DAtlasPage),
		alignof(FFramework2DAtlasPage),
		Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FFramework2DAtlasPage()
	{
		if (!Z_Registration_Info_UScriptStruct_Framework2DAtlasPage.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_Framework2DAtlasPage.InnerSingleton, Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_Framework2DAtlasPage.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_Framework2DScatterSprite;
class UScriptStruct* FFramework2DScatterSprite::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_Framework2DScatterSprite.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_Framework2DScatterSprite.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FFramework2DScatterSprite, Z_Construct_UPackage__Script_Framework2DTerrain(), TEXT("Framework2DScatterSprite"));
	}
	return Z_Registration_Info_UScriptStruct_Framework2DScatterSprite.OuterSingleton;
}
template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<FFramework2DScatterSprite>()
{
	return FFramework2DScatterSprite::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FFramework2DScatterSprite_Statics
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
		static const UECodeGen_Private::FMetaDataPairParam NewProp_WidthInTiles_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_WidthInTiles;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_HeightInTiles_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_HeightInTiles;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Weight_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Weight;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DScatterSprite_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/** Un sprite que puede sacar un generador: un trozo del atlas (uno o varios tiles). */" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Un sprite que puede sacar un generador: un trozo del atlas (uno o varios tiles)." },
	};
#endif
	void* Z_Construct_UScriptStruct_FFramework2DScatterSprite_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFramework2DScatterSprite>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DScatterSprite_Statics::NewProp_Tile_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Tile de arriba-izquierda del sprite (valor de tile: pagina + numero).\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Tile de arriba-izquierda del sprite (valor de tile: pagina + numero)." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DScatterSprite_Statics::NewProp_Tile = { "Tile", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DScatterSprite, Tile), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DScatterSprite_Statics::NewProp_Tile_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DScatterSprite_Statics::NewProp_Tile_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DScatterSprite_Statics::NewProp_WidthInTiles_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "16" },
		{ "ClampMin", "1" },
		{ "Comment", "// Tamano del sprite en tiles (un arbusto de 2x2, un junco de 1x2...).\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Tamano del sprite en tiles (un arbusto de 2x2, un junco de 1x2...)." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DScatterSprite_Statics::NewProp_WidthInTiles = { "WidthInTiles", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DScatterSprite, WidthInTiles), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DScatterSprite_Statics::NewProp_WidthInTiles_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DScatterSprite_Statics::NewProp_WidthInTiles_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DScatterSprite_Statics::NewProp_HeightInTiles_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "16" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DScatterSprite_Statics::NewProp_HeightInTiles = { "HeightInTiles", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DScatterSprite, HeightInTiles), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DScatterSprite_Statics::NewProp_HeightInTiles_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DScatterSprite_Statics::NewProp_HeightInTiles_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DScatterSprite_Statics::NewProp_Weight_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMin", "0.0" },
		{ "Comment", "// Probabilidad relativa de salir frente a los demas sprites del generador.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Probabilidad relativa de salir frente a los demas sprites del generador." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DScatterSprite_Statics::NewProp_Weight = { "Weight", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DScatterSprite, Weight), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DScatterSprite_Statics::NewProp_Weight_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DScatterSprite_Statics::NewProp_Weight_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FFramework2DScatterSprite_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DScatterSprite_Statics::NewProp_Tile,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DScatterSprite_Statics::NewProp_WidthInTiles,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DScatterSprite_Statics::NewProp_HeightInTiles,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DScatterSprite_Statics::NewProp_Weight,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFramework2DScatterSprite_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_Framework2DTerrain,
		nullptr,
		&NewStructOps,
		"Framework2DScatterSprite",
		sizeof(FFramework2DScatterSprite),
		alignof(FFramework2DScatterSprite),
		Z_Construct_UScriptStruct_FFramework2DScatterSprite_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DScatterSprite_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DScatterSprite_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DScatterSprite_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FFramework2DScatterSprite()
	{
		if (!Z_Registration_Info_UScriptStruct_Framework2DScatterSprite.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_Framework2DScatterSprite.InnerSingleton, Z_Construct_UScriptStruct_FFramework2DScatterSprite_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_Framework2DScatterSprite.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_Framework2DGenerator;
class UScriptStruct* FFramework2DGenerator::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_Framework2DGenerator.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_Framework2DGenerator.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FFramework2DGenerator, Z_Construct_UPackage__Script_Framework2DTerrain(), TEXT("Framework2DGenerator"));
	}
	return Z_Registration_Info_UScriptStruct_Framework2DGenerator.OuterSingleton;
}
template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<FFramework2DGenerator>()
{
	return FFramework2DGenerator::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FFramework2DGenerator_Statics
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
		static const UECodeGen_Private::FStructPropertyParams NewProp_Sprites_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Sprites_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Sprites;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Density_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Density;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_JitterX_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_JitterX;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_JitterY_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_JitterY;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OffsetY_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_OffsetY;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ScaleMin_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_ScaleMin;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ScaleMax_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_ScaleMax;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bRandomFlip_MetaData[];
#endif
		static void NewProp_bRandomFlip_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bRandomFlip;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TintA_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_TintA;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TintB_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_TintB;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BrightnessVariation_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_BrightnessVariation;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bSnapToGround_MetaData[];
#endif
		static void NewProp_bSnapToGround_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bSnapToGround;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bHangFromCeiling_MetaData[];
#endif
		static void NewProp_bHangFromCeiling_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bHangFromCeiling;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GroundSearchTiles_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_GroundSearchTiles;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MaterialName_MetaData[];
#endif
		static const UECodeGen_Private::FNamePropertyParams NewProp_MaterialName;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Seed_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Seed;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * Un GENERADOR de vegetacion (o rocas, setas...). Se pinta en una casilla de cualquier capa\n * como si fuera un tile y, al hornear, reparte por ella sprites del atlas con variacion de\n * posicion, escala, volteo y tinte. Lo generado son pixeles de terreno de esa capa: se ven en\n * el editor al momento y el jugador los rompe como lo demas. Siempre sale igual (semilla).\n */" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Un GENERADOR de vegetacion (o rocas, setas...). Se pinta en una casilla de cualquier capa\ncomo si fuera un tile y, al hornear, reparte por ella sprites del atlas con variacion de\nposicion, escala, volteo y tinte. Lo generado son pixeles de terreno de esa capa: se ven en\nel editor al momento y el jugador los rompe como lo demas. Siempre sale igual (semilla)." },
	};
#endif
	void* Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFramework2DGenerator>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_Name_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Nombre que se ve en la paleta.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Nombre que se ve en la paleta." },
	};
#endif
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DGenerator, Name), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_Name_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_Name_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_Id_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Identificador estable que guardan los mapas. No lo cambies a mano.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Identificador estable que guardan los mapas. No lo cambies a mano." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_Id = { "Id", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DGenerator, Id), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_Id_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_Id_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_Sprites_Inner = { "Sprites", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FFramework2DScatterSprite, METADATA_PARAMS(nullptr, 0) }; // 3343979898
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_Sprites_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Sprites que puede sacar (se eligen al azar segun su peso).\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "TitleProperty", "Tile" },
		{ "ToolTip", "Sprites que puede sacar (se eligen al azar segun su peso)." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_Sprites = { "Sprites", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DGenerator, Sprites), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_Sprites_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_Sprites_MetaData)) }; // 3343979898
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_Density_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "16.0" },
		{ "ClampMin", "0.0" },
		{ "Comment", "// Sprites por casilla (media). 0.5 = uno cada dos casillas; 3 = tres por casilla.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Sprites por casilla (media). 0.5 = uno cada dos casillas; 3 = tres por casilla." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_Density = { "Density", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DGenerator, Density), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_Density_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_Density_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_JitterX_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "256.0" },
		{ "ClampMin", "0.0" },
		{ "Comment", "// Variacion horizontal al azar (pixeles, a cada lado). Se reparten por la casilla y se mueven esto.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Variacion horizontal al azar (pixeles, a cada lado). Se reparten por la casilla y se mueven esto." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_JitterX = { "JitterX", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DGenerator, JitterX), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_JitterX_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_JitterX_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_JitterY_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "256.0" },
		{ "ClampMin", "0.0" },
		{ "Comment", "// Variacion vertical al azar (pixeles, arriba o abajo).\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Variacion vertical al azar (pixeles, arriba o abajo)." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_JitterY = { "JitterY", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DGenerator, JitterY), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_JitterY_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_JitterY_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_OffsetY_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "256.0" },
		{ "ClampMin", "-256.0" },
		{ "Comment", "// Desplazamiento vertical fijo (pixeles; positivo = hacia abajo, se hunde en el suelo).\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Desplazamiento vertical fijo (pixeles; positivo = hacia abajo, se hunde en el suelo)." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_OffsetY = { "OffsetY", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DGenerator, OffsetY), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_OffsetY_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_OffsetY_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_ScaleMin_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "8.0" },
		{ "ClampMin", "0.1" },
		{ "Comment", "// Escala minima y maxima de cada sprite (1 = tamano del atlas; con pixel art, mejor 1).\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Escala minima y maxima de cada sprite (1 = tamano del atlas; con pixel art, mejor 1)." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_ScaleMin = { "ScaleMin", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DGenerator, ScaleMin), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_ScaleMin_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_ScaleMin_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_ScaleMax_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "8.0" },
		{ "ClampMin", "0.1" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_ScaleMax = { "ScaleMax", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DGenerator, ScaleMax), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_ScaleMax_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_ScaleMax_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_bRandomFlip_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Voltea en horizontal la mitad de los sprites, al azar.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Voltea en horizontal la mitad de los sprites, al azar." },
	};
#endif
	void Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_bRandomFlip_SetBit(void* Obj)
	{
		((FFramework2DGenerator*)Obj)->bRandomFlip = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_bRandomFlip = { "bRandomFlip", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FFramework2DGenerator), &Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_bRandomFlip_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_bRandomFlip_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_bRandomFlip_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_TintA_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Cada sprite se tine con un color al azar entre Tint A y Tint B (blanco = sin tinte).\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Cada sprite se tine con un color al azar entre Tint A y Tint B (blanco = sin tinte)." },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_TintA = { "TintA", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DGenerator, TintA), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_TintA_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_TintA_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_TintB_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_TintB = { "TintB", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DGenerator, TintB), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_TintB_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_TintB_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_BrightnessVariation_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "Comment", "// Variacion de brillo al azar (0.15 = hasta un 15 % mas claro u oscuro).\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Variacion de brillo al azar (0.15 = hasta un 15 % mas claro u oscuro)." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_BrightnessVariation = { "BrightnessVariation", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DGenerator, BrightnessVariation), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_BrightnessVariation_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_BrightnessVariation_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_bSnapToGround_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Apoya cada sprite en el primer suelo que choca debajo de su punto (si no hay suelo, no sale).\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Apoya cada sprite en el primer suelo que choca debajo de su punto (si no hay suelo, no sale)." },
	};
#endif
	void Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_bSnapToGround_SetBit(void* Obj)
	{
		((FFramework2DGenerator*)Obj)->bSnapToGround = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_bSnapToGround = { "bSnapToGround", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FFramework2DGenerator), &Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_bSnapToGround_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_bSnapToGround_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_bSnapToGround_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_bHangFromCeiling_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Cuelga cada sprite del primer techo que choca ENCIMA de su punto (lianas, raices, rocas bajo\n// una isla o un saliente). Si no hay techo cerca, no sale. Gana a \"Apoyar en el suelo\".\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Cuelga cada sprite del primer techo que choca ENCIMA de su punto (lianas, raices, rocas bajo\nuna isla o un saliente). Si no hay techo cerca, no sale. Gana a \"Apoyar en el suelo\"." },
	};
#endif
	void Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_bHangFromCeiling_SetBit(void* Obj)
	{
		((FFramework2DGenerator*)Obj)->bHangFromCeiling = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_bHangFromCeiling = { "bHangFromCeiling", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FFramework2DGenerator), &Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_bHangFromCeiling_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_bHangFromCeiling_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_bHangFromCeiling_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_GroundSearchTiles_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "8" },
		{ "ClampMin", "0" },
		{ "Comment", "// Hasta cuantas casillas por debajo se busca el suelo.\n" },
		{ "EditCondition", "bSnapToGround" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Hasta cuantas casillas por debajo se busca el suelo." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_GroundSearchTiles = { "GroundSearchTiles", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DGenerator, GroundSearchTiles), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_GroundSearchTiles_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_GroundSearchTiles_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_MaterialName_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Material de lo generado. Decoration = se ve y se rompe, pero no choca.\n" },
		{ "GetOptions", "GetMaterialNameOptions" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Material de lo generado. Decoration = se ve y se rompe, pero no choca." },
	};
#endif
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_MaterialName = { "MaterialName", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DGenerator, MaterialName), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_MaterialName_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_MaterialName_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_Seed_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Cambiala para otra distribucion al azar con los mismos ajustes.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Cambiala para otra distribucion al azar con los mismos ajustes." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_Seed = { "Seed", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DGenerator, Seed), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_Seed_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_Seed_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_Name,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_Id,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_Sprites_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_Sprites,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_Density,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_JitterX,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_JitterY,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_OffsetY,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_ScaleMin,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_ScaleMax,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_bRandomFlip,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_TintA,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_TintB,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_BrightnessVariation,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_bSnapToGround,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_bHangFromCeiling,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_GroundSearchTiles,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_MaterialName,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewProp_Seed,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_Framework2DTerrain,
		nullptr,
		&NewStructOps,
		"Framework2DGenerator",
		sizeof(FFramework2DGenerator),
		alignof(FFramework2DGenerator),
		Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FFramework2DGenerator()
	{
		if (!Z_Registration_Info_UScriptStruct_Framework2DGenerator.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_Framework2DGenerator.InnerSingleton, Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_Framework2DGenerator.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_Framework2DPropDef;
class UScriptStruct* FFramework2DPropDef::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_Framework2DPropDef.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_Framework2DPropDef.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FFramework2DPropDef, Z_Construct_UPackage__Script_Framework2DTerrain(), TEXT("Framework2DPropDef"));
	}
	return Z_Registration_Info_UScriptStruct_Framework2DPropDef.OuterSingleton;
}
template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<FFramework2DPropDef>()
{
	return FFramework2DPropDef::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FFramework2DPropDef_Statics
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
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Texture_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_Texture;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AtlasTile_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_AtlasTile;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AtlasWidthTiles_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_AtlasWidthTiles;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AtlasHeightTiles_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_AtlasHeightTiles;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MaterialName_MetaData[];
#endif
		static const UECodeGen_Private::FNamePropertyParams NewProp_MaterialName;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FootprintTiles_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_FootprintTiles;
		static const UECodeGen_Private::FStructPropertyParams NewProp_PixelCache_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PixelCache_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_PixelCache;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CacheWidth_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_CacheWidth;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CacheHeight_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_CacheHeight;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * Un OBJETO GRANDE (arbol, roca, piedra runica, seta gigante...): una imagen suelta de\n * cualquier tamano. El generador procedural los reparte por el suelo y se hornean como pixeles\n * de una capa (detras o delante del terreno).\n */" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Un OBJETO GRANDE (arbol, roca, piedra runica, seta gigante...): una imagen suelta de\ncualquier tamano. El generador procedural los reparte por el suelo y se hornean como pixeles\nde una capa (detras o delante del terreno)." },
	};
#endif
	void* Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FFramework2DPropDef>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_Name_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
	};
#endif
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DPropDef, Name), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_Name_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_Name_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_Id_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Identificador estable que guardan los mapas y los biomas. No lo cambies a mano.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Identificador estable que guardan los mapas y los biomas. No lo cambies a mano." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_Id = { "Id", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DPropDef, Id), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_Id_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_Id_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_Texture_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// La imagen (con transparencia). 1 pixel de la imagen = 1 pixel del terreno.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "La imagen (con transparencia). 1 pixel de la imagen = 1 pixel del terreno." },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_Texture = { "Texture", nullptr, (EPropertyFlags)0x0014000000000015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DPropDef, Texture), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_Texture_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_Texture_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_AtlasTile_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// O un trozo del ATLAS (sin imagen): tile de arriba-izquierda (con pagina) y tamano en tiles.\n// Para tilesets que traen los arboles, rocas... dentro del atlas.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "O un trozo del ATLAS (sin imagen): tile de arriba-izquierda (con pagina) y tamano en tiles.\nPara tilesets que traen los arboles, rocas... dentro del atlas." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_AtlasTile = { "AtlasTile", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DPropDef, AtlasTile), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_AtlasTile_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_AtlasTile_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_AtlasWidthTiles_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "64" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_AtlasWidthTiles = { "AtlasWidthTiles", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DPropDef, AtlasWidthTiles), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_AtlasWidthTiles_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_AtlasWidthTiles_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_AtlasHeightTiles_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "64" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_AtlasHeightTiles = { "AtlasHeightTiles", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DPropDef, AtlasHeightTiles), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_AtlasHeightTiles_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_AtlasHeightTiles_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_MaterialName_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Material de sus pixeles. Decoration = se ve y no choca.\n" },
		{ "GetOptions", "GetMaterialNameOptions" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Material de sus pixeles. Decoration = se ve y no choca." },
	};
#endif
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_MaterialName = { "MaterialName", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DPropDef, MaterialName), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_MaterialName_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_MaterialName_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_FootprintTiles_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "64" },
		{ "ClampMin", "0" },
		{ "Comment", "// Suelo llano que necesita debajo (tiles). 0 = el ancho de la imagen.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Suelo llano que necesita debajo (tiles). 0 = el ancho de la imagen." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_FootprintTiles = { "FootprintTiles", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DPropDef, FootprintTiles), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_FootprintTiles_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_FootprintTiles_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_PixelCache_Inner = { "PixelCache", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FColor, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_PixelCache_MetaData[] = {
		{ "Comment", "// Copia CPU de la imagen para el juego empaquetado (se rellena al guardar).\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Copia CPU de la imagen para el juego empaquetado (se rellena al guardar)." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_PixelCache = { "PixelCache", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DPropDef, PixelCache), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_PixelCache_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_PixelCache_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_CacheWidth_MetaData[] = {
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_CacheWidth = { "CacheWidth", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DPropDef, CacheWidth), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_CacheWidth_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_CacheWidth_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_CacheHeight_MetaData[] = {
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_CacheHeight = { "CacheHeight", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFramework2DPropDef, CacheHeight), METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_CacheHeight_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_CacheHeight_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_Name,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_Id,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_Texture,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_AtlasTile,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_AtlasWidthTiles,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_AtlasHeightTiles,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_MaterialName,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_FootprintTiles,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_PixelCache_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_PixelCache,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_CacheWidth,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewProp_CacheHeight,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_Framework2DTerrain,
		nullptr,
		&NewStructOps,
		"Framework2DPropDef",
		sizeof(FFramework2DPropDef),
		alignof(FFramework2DPropDef),
		Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FFramework2DPropDef()
	{
		if (!Z_Registration_Info_UScriptStruct_Framework2DPropDef.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_Framework2DPropDef.InnerSingleton, Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_Framework2DPropDef.InnerSingleton;
	}
	DEFINE_FUNCTION(UFramework2DTileSet::execGetMaterialNameOptions)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<FString>*)Z_Param__Result=P_THIS->GetMaterialNameOptions();
		P_NATIVE_END;
	}
	void UFramework2DTileSet::StaticRegisterNativesUFramework2DTileSet()
	{
		UClass* Class = UFramework2DTileSet::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetMaterialNameOptions", &UFramework2DTileSet::execGetMaterialNameOptions },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UFramework2DTileSet_GetMaterialNameOptions_Statics
	{
		struct Framework2DTileSet_eventGetMaterialNameOptions_Parms
		{
			TArray<FString> ReturnValue;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UFramework2DTileSet_GetMaterialNameOptions_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UFramework2DTileSet_GetMaterialNameOptions_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DTileSet_eventGetMaterialNameOptions_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFramework2DTileSet_GetMaterialNameOptions_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTileSet_GetMaterialNameOptions_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTileSet_GetMaterialNameOptions_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFramework2DTileSet_GetMaterialNameOptions_Statics::Function_MetaDataParams[] = {
		{ "Comment", "// Opciones del desplegable de material de cada tile.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Opciones del desplegable de material de cada tile." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFramework2DTileSet_GetMaterialNameOptions_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFramework2DTileSet, nullptr, "GetMaterialNameOptions", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFramework2DTileSet_GetMaterialNameOptions_Statics::Framework2DTileSet_eventGetMaterialNameOptions_Parms), Z_Construct_UFunction_UFramework2DTileSet_GetMaterialNameOptions_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTileSet_GetMaterialNameOptions_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x40020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFramework2DTileSet_GetMaterialNameOptions_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTileSet_GetMaterialNameOptions_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFramework2DTileSet_GetMaterialNameOptions()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFramework2DTileSet_GetMaterialNameOptions_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UFramework2DTileSet);
	UClass* Z_Construct_UClass_UFramework2DTileSet_NoRegister()
	{
		return UFramework2DTileSet::StaticClass();
	}
	struct Z_Construct_UClass_UFramework2DTileSet_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Atlas_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_Atlas;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TileWidth_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_TileWidth;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TileHeight_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_TileHeight;
		static const UECodeGen_Private::FStructPropertyParams NewProp_Materials_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Materials_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Materials;
		static const UECodeGen_Private::FStructPropertyParams NewProp_Tiles_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Tiles_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Tiles;
		static const UECodeGen_Private::FStructPropertyParams NewProp_ExtraAtlases_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ExtraAtlases_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ExtraAtlases;
		static const UECodeGen_Private::FStructPropertyParams NewProp_Generators_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Generators_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Generators;
		static const UECodeGen_Private::FStructPropertyParams NewProp_Flipbooks_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Flipbooks_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Flipbooks;
		static const UECodeGen_Private::FStructPropertyParams NewProp_Biomes_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Biomes_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Biomes;
		static const UECodeGen_Private::FStructPropertyParams NewProp_Props_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Props_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Props;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Columns_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Columns;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Rows_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Rows;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_NextFlipbookId_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_NextFlipbookId;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_NextAtlasId_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_NextAtlasId;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_NextGeneratorId_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_NextGeneratorId;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_NextBiomeId_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_NextBiomeId;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_NextPropId_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_NextPropId;
		static const UECodeGen_Private::FStructPropertyParams NewProp_AtlasPixelCache_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AtlasPixelCache_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_AtlasPixelCache;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AtlasCacheWidth_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_AtlasCacheWidth;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AtlasCacheHeight_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_AtlasCacheHeight;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UFramework2DTileSet_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UDataAsset,
		(UObject* (*)())Z_Construct_UPackage__Script_Framework2DTerrain,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UFramework2DTileSet_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UFramework2DTileSet_GetMaterialNameOptions, "GetMaterialNameOptions" }, // 3851774994
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTileSet_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * UFramework2DTileSet\n * =================================================================\n * Tu atlas de tiles + los materiales de terreno. Se crea con:\n *   Content Browser -> Add -> Miscellaneous -> Data Asset -> Framework2DTileSet\n *\n *   1. Asigna el Atlas (imagen con los tiles en rejilla, sin margenes) y el tamano del tile.\n *      La lista Tiles se crea sola: una fila por tile del atlas.\n *   2. En cada fila elige el material del tile (desplegable) y, si quieres, su colision.\n *   3. Ajusta los materiales si quieres (dureza, colision...). Vienen 6 de serie.\n *   4. Los flipbooks y los generadores de vegetacion se crean desde la paleta del modo\n *      Framework2D Tiles. Mas atlas (otros entornos): en \"Atlas extra\" o con el \"+\" de la paleta.\n *\n * Cada pixel del dibujo de un tile sera una celda que el jugador puede romper.\n *\n * VALOR de una celda del mapa (ver Framework2D::FlipbookTileBase): -1 vacio, tile de un atlas\n * (pagina + numero), flipbook o generador. Las funciones de abajo aceptan cualquier valor.\n */" },
		{ "IncludePath", "Framework2DTileSet.h" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "UFramework2DTileSet\n\nTu atlas de tiles + los materiales de terreno. Se crea con:\n  Content Browser -> Add -> Miscellaneous -> Data Asset -> Framework2DTileSet\n\n  1. Asigna el Atlas (imagen con los tiles en rejilla, sin margenes) y el tamano del tile.\n     La lista Tiles se crea sola: una fila por tile del atlas.\n  2. En cada fila elige el material del tile (desplegable) y, si quieres, su colision.\n  3. Ajusta los materiales si quieres (dureza, colision...). Vienen 6 de serie.\n  4. Los flipbooks y los generadores de vegetacion se crean desde la paleta del modo\n     Framework2D Tiles. Mas atlas (otros entornos): en \"Atlas extra\" o con el \"+\" de la paleta.\n\nCada pixel del dibujo de un tile sera una celda que el jugador puede romper.\n\nVALOR de una celda del mapa (ver Framework2D::FlipbookTileBase): -1 vacio, tile de un atlas\n(pagina + numero), flipbook o generador. Las funciones de abajo aceptan cualquier valor." },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Atlas_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Imagen con todos los tiles en rejilla. Da igual como la importes (comprimida o no):\n// se lee el PNG original. Consejo: Filter = Nearest para que la paleta se vea nitida.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Imagen con todos los tiles en rejilla. Da igual como la importes (comprimida o no):\nse lee el PNG original. Consejo: Filter = Nearest para que la paleta se vea nitida." },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Atlas = { "Atlas", nullptr, (EPropertyFlags)0x0014000000000015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTileSet, Atlas), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Atlas_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Atlas_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_TileWidth_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "256" },
		{ "ClampMin", "1" },
		{ "Comment", "// Ancho de un tile en pixeles del atlas. Cada pixel sera una celda pickable.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Ancho de un tile en pixeles del atlas. Cada pixel sera una celda pickable." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_TileWidth = { "TileWidth", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTileSet, TileWidth), METADATA_PARAMS(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_TileWidth_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_TileWidth_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_TileHeight_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ClampMax", "256" },
		{ "ClampMin", "1" },
		{ "Comment", "// Alto de un tile en pixeles del atlas.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Alto de un tile en pixeles del atlas." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_TileHeight = { "TileHeight", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTileSet, TileHeight), METADATA_PARAMS(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_TileHeight_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_TileHeight_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Materials_Inner = { "Materials", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FFramework2DMaterial, METADATA_PARAMS(nullptr, 0) }; // 3334758378
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Materials_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Materiales de terreno de este tileset. Los tiles los eligen por nombre.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "TitleProperty", "Name" },
		{ "ToolTip", "Materiales de terreno de este tileset. Los tiles los eligen por nombre." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Materials = { "Materials", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTileSet, Materials), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Materials_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Materials_MetaData)) }; // 3334758378
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Tiles_Inner = { "Tiles", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FFramework2DTileDef, METADATA_PARAMS(nullptr, 0) }; // 2854456691
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Tiles_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Un tile por cada hueco del atlas (se crean solos al asignar el atlas).\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "TitleProperty", "MaterialName" },
		{ "ToolTip", "Un tile por cada hueco del atlas (se crean solos al asignar el atlas)." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Tiles = { "Tiles", nullptr, (EPropertyFlags)0x0010000000000055, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTileSet, Tiles), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Tiles_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Tiles_MetaData)) }; // 2854456691
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_ExtraAtlases_Inner = { "ExtraAtlases", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FFramework2DAtlasPage, METADATA_PARAMS(nullptr, 0) }; // 2616276642
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_ExtraAtlases_MetaData[] = {
		{ "Category", "Framework2D|Atlas extra" },
		{ "Comment", "// Mas imagenes con tiles del mismo tamano (otros entornos: cueva, bosque, desierto...).\n// Cada una sale como una pestana en el atlas de la paleta.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "TitleProperty", "Name" },
		{ "ToolTip", "Mas imagenes con tiles del mismo tamano (otros entornos: cueva, bosque, desierto...).\nCada una sale como una pestana en el atlas de la paleta." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_ExtraAtlases = { "ExtraAtlases", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTileSet, ExtraAtlases), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_ExtraAtlases_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_ExtraAtlases_MetaData)) }; // 2616276642
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Generators_Inner = { "Generators", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FFramework2DGenerator, METADATA_PARAMS(nullptr, 0) }; // 3527433989
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Generators_MetaData[] = {
		{ "Category", "Framework2D|Generators" },
		{ "Comment", "// Generadores de vegetacion: se pintan en una casilla como un tile y al hornear reparten\n// sprites del atlas por ella. Se crean y ajustan desde la paleta.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "TitleProperty", "Name" },
		{ "ToolTip", "Generadores de vegetacion: se pintan en una casilla como un tile y al hornear reparten\nsprites del atlas por ella. Se crean y ajustan desde la paleta." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Generators = { "Generators", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTileSet, Generators), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Generators_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Generators_MetaData)) }; // 3527433989
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Flipbooks_Inner = { "Flipbooks", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FFramework2DFlipbook, METADATA_PARAMS(nullptr, 0) }; // 2005772058
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Flipbooks_MetaData[] = {
		{ "Category", "Framework2D|Flipbooks" },
		{ "Comment", "// Tiles animados. Se crean desde la paleta (selecciona fotogramas en el atlas y pulsa\n// \"Nuevo flipbook\"); aqui puedes retocarlos.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "TitleProperty", "Name" },
		{ "ToolTip", "Tiles animados. Se crean desde la paleta (selecciona fotogramas en el atlas y pulsa\n\"Nuevo flipbook\"); aqui puedes retocarlos." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Flipbooks = { "Flipbooks", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTileSet, Flipbooks), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Flipbooks_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Flipbooks_MetaData)) }; // 2005772058
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Biomes_Inner = { "Biomes", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FFramework2DBiome, METADATA_PARAMS(nullptr, 0) }; // 2776837089
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Biomes_MetaData[] = {
		{ "Category", "Framework2D|Biomes" },
		{ "Comment", "// Biomas del generador procedural: las piezas (terreno 3x3, rampas, fondo, agua,\n// decoracion...) con las que se construye un nivel. Se editan en la pestana \"Generar\".\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "TitleProperty", "Name" },
		{ "ToolTip", "Biomas del generador procedural: las piezas (terreno 3x3, rampas, fondo, agua,\ndecoracion...) con las que se construye un nivel. Se editan en la pestana \"Generar\"." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Biomes = { "Biomes", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTileSet, Biomes), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Biomes_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Biomes_MetaData)) }; // 2776837089
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Props_Inner = { "Props", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FFramework2DPropDef, METADATA_PARAMS(nullptr, 0) }; // 3610786705
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Props_MetaData[] = {
		{ "Category", "Framework2D|Objects" },
		{ "Comment", "// Objetos grandes (imagenes sueltas: arboles, rocas...). Se anaden desde la pestana \"Generar\".\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "TitleProperty", "Name" },
		{ "ToolTip", "Objetos grandes (imagenes sueltas: arboles, rocas...). Se anaden desde la pestana \"Generar\"." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Props = { "Props", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTileSet, Props), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Props_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Props_MetaData)) }; // 3610786705
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Columns_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "Comment", "// Tiles por fila y por columna del atlas (informativo).\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Tiles por fila y por columna del atlas (informativo)." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Columns = { "Columns", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTileSet, Columns), METADATA_PARAMS(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Columns_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Columns_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Rows_MetaData[] = {
		{ "Category", "Framework2D" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Rows = { "Rows", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTileSet, Rows), METADATA_PARAMS(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Rows_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Rows_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_NextFlipbookId_MetaData[] = {
		{ "Comment", "// Siguiente Id libre para flipbooks (nunca se reutilizan).\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Siguiente Id libre para flipbooks (nunca se reutilizan)." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_NextFlipbookId = { "NextFlipbookId", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTileSet, NextFlipbookId), METADATA_PARAMS(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_NextFlipbookId_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_NextFlipbookId_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_NextAtlasId_MetaData[] = {
		{ "Comment", "// Siguientes Ids libres de paginas extra y generadores (nunca se reutilizan).\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Siguientes Ids libres de paginas extra y generadores (nunca se reutilizan)." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_NextAtlasId = { "NextAtlasId", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTileSet, NextAtlasId), METADATA_PARAMS(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_NextAtlasId_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_NextAtlasId_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_NextGeneratorId_MetaData[] = {
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_NextGeneratorId = { "NextGeneratorId", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTileSet, NextGeneratorId), METADATA_PARAMS(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_NextGeneratorId_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_NextGeneratorId_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_NextBiomeId_MetaData[] = {
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_NextBiomeId = { "NextBiomeId", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTileSet, NextBiomeId), METADATA_PARAMS(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_NextBiomeId_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_NextBiomeId_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_NextPropId_MetaData[] = {
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_NextPropId = { "NextPropId", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTileSet, NextPropId), METADATA_PARAMS(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_NextPropId_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_NextPropId_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_AtlasPixelCache_Inner = { "AtlasPixelCache", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FColor, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_AtlasPixelCache_MetaData[] = {
		{ "Comment", "// Copia CPU del atlas para el juego empaquetado (no tiene el PNG original). Se rellena al guardar.\n" },
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
		{ "ToolTip", "Copia CPU del atlas para el juego empaquetado (no tiene el PNG original). Se rellena al guardar." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_AtlasPixelCache = { "AtlasPixelCache", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTileSet, AtlasPixelCache), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_AtlasPixelCache_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_AtlasPixelCache_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_AtlasCacheWidth_MetaData[] = {
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_AtlasCacheWidth = { "AtlasCacheWidth", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTileSet, AtlasCacheWidth), METADATA_PARAMS(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_AtlasCacheWidth_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_AtlasCacheWidth_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_AtlasCacheHeight_MetaData[] = {
		{ "ModuleRelativePath", "Public/Framework2DTileSet.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_AtlasCacheHeight = { "AtlasCacheHeight", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTileSet, AtlasCacheHeight), METADATA_PARAMS(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_AtlasCacheHeight_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_AtlasCacheHeight_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UFramework2DTileSet_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Atlas,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_TileWidth,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_TileHeight,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Materials_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Materials,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Tiles_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Tiles,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_ExtraAtlases_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_ExtraAtlases,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Generators_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Generators,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Flipbooks_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Flipbooks,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Biomes_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Biomes,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Props_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Props,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Columns,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_Rows,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_NextFlipbookId,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_NextAtlasId,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_NextGeneratorId,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_NextBiomeId,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_NextPropId,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_AtlasPixelCache_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_AtlasPixelCache,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_AtlasCacheWidth,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTileSet_Statics::NewProp_AtlasCacheHeight,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UFramework2DTileSet_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFramework2DTileSet>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UFramework2DTileSet_Statics::ClassParams = {
		&UFramework2DTileSet::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UFramework2DTileSet_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTileSet_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UFramework2DTileSet_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTileSet_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UFramework2DTileSet()
	{
		if (!Z_Registration_Info_UClass_UFramework2DTileSet.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UFramework2DTileSet.OuterSingleton, Z_Construct_UClass_UFramework2DTileSet_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UFramework2DTileSet.OuterSingleton;
	}
	template<> FRAMEWORK2DTERRAIN_API UClass* StaticClass<UFramework2DTileSet>()
	{
		return UFramework2DTileSet::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UFramework2DTileSet);
	struct Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTileSet_h_Statics
	{
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTileSet_h_Statics::ScriptStructInfo[] = {
		{ FFramework2DTileDef::StaticStruct, Z_Construct_UScriptStruct_FFramework2DTileDef_Statics::NewStructOps, TEXT("Framework2DTileDef"), &Z_Registration_Info_UScriptStruct_Framework2DTileDef, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FFramework2DTileDef), 2854456691U) },
		{ FFramework2DFlipbook::StaticStruct, Z_Construct_UScriptStruct_FFramework2DFlipbook_Statics::NewStructOps, TEXT("Framework2DFlipbook"), &Z_Registration_Info_UScriptStruct_Framework2DFlipbook, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FFramework2DFlipbook), 2005772058U) },
		{ FFramework2DAtlasPage::StaticStruct, Z_Construct_UScriptStruct_FFramework2DAtlasPage_Statics::NewStructOps, TEXT("Framework2DAtlasPage"), &Z_Registration_Info_UScriptStruct_Framework2DAtlasPage, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FFramework2DAtlasPage), 2616276642U) },
		{ FFramework2DScatterSprite::StaticStruct, Z_Construct_UScriptStruct_FFramework2DScatterSprite_Statics::NewStructOps, TEXT("Framework2DScatterSprite"), &Z_Registration_Info_UScriptStruct_Framework2DScatterSprite, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FFramework2DScatterSprite), 3343979898U) },
		{ FFramework2DGenerator::StaticStruct, Z_Construct_UScriptStruct_FFramework2DGenerator_Statics::NewStructOps, TEXT("Framework2DGenerator"), &Z_Registration_Info_UScriptStruct_Framework2DGenerator, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FFramework2DGenerator), 3527433989U) },
		{ FFramework2DPropDef::StaticStruct, Z_Construct_UScriptStruct_FFramework2DPropDef_Statics::NewStructOps, TEXT("Framework2DPropDef"), &Z_Registration_Info_UScriptStruct_Framework2DPropDef, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FFramework2DPropDef), 3610786705U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTileSet_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UFramework2DTileSet, UFramework2DTileSet::StaticClass, TEXT("UFramework2DTileSet"), &Z_Registration_Info_UClass_UFramework2DTileSet, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UFramework2DTileSet), 2998145133U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTileSet_h_1716607375(TEXT("/Script/Framework2DTerrain"),
		Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTileSet_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTileSet_h_Statics::ClassInfo),
		Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTileSet_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTileSet_h_Statics::ScriptStructInfo),
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
