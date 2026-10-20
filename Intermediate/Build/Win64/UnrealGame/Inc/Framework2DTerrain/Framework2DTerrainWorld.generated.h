// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FFramework2DDigResult;
struct FFramework2DProcGenReport;
struct FFramework2DMaterial;
class AActor;
#ifdef FRAMEWORK2DTERRAIN_Framework2DTerrainWorld_generated_h
#error "Framework2DTerrainWorld.generated.h already included, missing '#pragma once' in Framework2DTerrainWorld.h"
#endif
#define FRAMEWORK2DTERRAIN_Framework2DTerrainWorld_generated_h

#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainWorld_h_34_DELEGATE \
struct _Script_Framework2DTerrain_eventFramework2DOnTerrainMined_Parms \
{ \
	FFramework2DDigResult Result; \
}; \
static inline void FFramework2DOnTerrainMined_DelegateWrapper(const FMulticastScriptDelegate& Framework2DOnTerrainMined, FFramework2DDigResult const& Result) \
{ \
	_Script_Framework2DTerrain_eventFramework2DOnTerrainMined_Parms Parms; \
	Parms.Result=Result; \
	Framework2DOnTerrainMined.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainWorld_h_52_SPARSE_DATA
#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainWorld_h_52_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGenerateProceduralLevel); \
	DECLARE_FUNCTION(execResetTerrain); \
	DECLARE_FUNCTION(execGetMaterials); \
	DECLARE_FUNCTION(execGetCellSize); \
	DECLARE_FUNCTION(execCountMaterialInRadius); \
	DECLARE_FUNCTION(execGetLayerMaterialNameAtWorld); \
	DECLARE_FUNCTION(execGetMaterialNameAtWorld); \
	DECLARE_FUNCTION(execIsSolidAtWorld); \
	DECLARE_FUNCTION(execTraceBreakableTerrain); \
	DECLARE_FUNCTION(execTraceTerrain); \
	DECLARE_FUNCTION(execPaint); \
	DECLARE_FUNCTION(execPlaceMaterial); \
	DECLARE_FUNCTION(execExplode); \
	DECLARE_FUNCTION(execDig); \
	DECLARE_FUNCTION(execMineAt);


#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainWorld_h_52_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGenerateProceduralLevel); \
	DECLARE_FUNCTION(execResetTerrain); \
	DECLARE_FUNCTION(execGetMaterials); \
	DECLARE_FUNCTION(execGetCellSize); \
	DECLARE_FUNCTION(execCountMaterialInRadius); \
	DECLARE_FUNCTION(execGetLayerMaterialNameAtWorld); \
	DECLARE_FUNCTION(execGetMaterialNameAtWorld); \
	DECLARE_FUNCTION(execIsSolidAtWorld); \
	DECLARE_FUNCTION(execTraceBreakableTerrain); \
	DECLARE_FUNCTION(execTraceTerrain); \
	DECLARE_FUNCTION(execPaint); \
	DECLARE_FUNCTION(execPlaceMaterial); \
	DECLARE_FUNCTION(execExplode); \
	DECLARE_FUNCTION(execDig); \
	DECLARE_FUNCTION(execMineAt);


#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainWorld_h_52_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAFramework2DTerrainWorld(); \
	friend struct Z_Construct_UClass_AFramework2DTerrainWorld_Statics; \
public: \
	DECLARE_CLASS(AFramework2DTerrainWorld, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Framework2DTerrain"), NO_API) \
	DECLARE_SERIALIZER(AFramework2DTerrainWorld)


#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainWorld_h_52_INCLASS \
private: \
	static void StaticRegisterNativesAFramework2DTerrainWorld(); \
	friend struct Z_Construct_UClass_AFramework2DTerrainWorld_Statics; \
public: \
	DECLARE_CLASS(AFramework2DTerrainWorld, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Framework2DTerrain"), NO_API) \
	DECLARE_SERIALIZER(AFramework2DTerrainWorld)


#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainWorld_h_52_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AFramework2DTerrainWorld(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AFramework2DTerrainWorld) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AFramework2DTerrainWorld); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AFramework2DTerrainWorld); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AFramework2DTerrainWorld(AFramework2DTerrainWorld&&); \
	NO_API AFramework2DTerrainWorld(const AFramework2DTerrainWorld&); \
public:


#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainWorld_h_52_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AFramework2DTerrainWorld(AFramework2DTerrainWorld&&); \
	NO_API AFramework2DTerrainWorld(const AFramework2DTerrainWorld&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AFramework2DTerrainWorld); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AFramework2DTerrainWorld); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AFramework2DTerrainWorld)


#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainWorld_h_49_PROLOG
#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainWorld_h_52_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainWorld_h_52_SPARSE_DATA \
	FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainWorld_h_52_RPC_WRAPPERS \
	FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainWorld_h_52_INCLASS \
	FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainWorld_h_52_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainWorld_h_52_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainWorld_h_52_SPARSE_DATA \
	FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainWorld_h_52_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainWorld_h_52_INCLASS_NO_PURE_DECLS \
	FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainWorld_h_52_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FRAMEWORK2DTERRAIN_API UClass* StaticClass<class AFramework2DTerrainWorld>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainWorld_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
