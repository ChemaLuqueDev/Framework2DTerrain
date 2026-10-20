// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FFramework2DDigResult;
#ifdef FRAMEWORK2DTERRAIN_Framework2DTerrainDeformerComponent_generated_h
#error "Framework2DTerrainDeformerComponent.generated.h already included, missing '#pragma once' in Framework2DTerrainDeformerComponent.h"
#endif
#define FRAMEWORK2DTERRAIN_Framework2DTerrainDeformerComponent_generated_h

#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainDeformerComponent_h_43_DELEGATE \
struct _Script_Framework2DTerrain_eventFramework2DOnTerrainDeformed_Parms \
{ \
	FFramework2DDigResult Result; \
}; \
static inline void FFramework2DOnTerrainDeformed_DelegateWrapper(const FMulticastScriptDelegate& Framework2DOnTerrainDeformed, FFramework2DDigResult const& Result) \
{ \
	_Script_Framework2DTerrain_eventFramework2DOnTerrainDeformed_Parms Parms; \
	Parms.Result=Result; \
	Framework2DOnTerrainDeformed.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainDeformerComponent_h_66_SPARSE_DATA
#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainDeformerComponent_h_66_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execSetFacing); \
	DECLARE_FUNCTION(execGetFacing); \
	DECLARE_FUNCTION(execGetAimDirection); \
	DECLARE_FUNCTION(execGetAimPoint); \
	DECLARE_FUNCTION(execIsDeforming); \
	DECLARE_FUNCTION(execStopDeforming); \
	DECLARE_FUNCTION(execStartDeforming); \
	DECLARE_FUNCTION(execDeformAt); \
	DECLARE_FUNCTION(execDeformNow);


#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainDeformerComponent_h_66_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execSetFacing); \
	DECLARE_FUNCTION(execGetFacing); \
	DECLARE_FUNCTION(execGetAimDirection); \
	DECLARE_FUNCTION(execGetAimPoint); \
	DECLARE_FUNCTION(execIsDeforming); \
	DECLARE_FUNCTION(execStopDeforming); \
	DECLARE_FUNCTION(execStartDeforming); \
	DECLARE_FUNCTION(execDeformAt); \
	DECLARE_FUNCTION(execDeformNow);


#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainDeformerComponent_h_66_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUFramework2DTerrainDeformerComponent(); \
	friend struct Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics; \
public: \
	DECLARE_CLASS(UFramework2DTerrainDeformerComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Framework2DTerrain"), NO_API) \
	DECLARE_SERIALIZER(UFramework2DTerrainDeformerComponent)


#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainDeformerComponent_h_66_INCLASS \
private: \
	static void StaticRegisterNativesUFramework2DTerrainDeformerComponent(); \
	friend struct Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics; \
public: \
	DECLARE_CLASS(UFramework2DTerrainDeformerComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Framework2DTerrain"), NO_API) \
	DECLARE_SERIALIZER(UFramework2DTerrainDeformerComponent)


#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainDeformerComponent_h_66_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UFramework2DTerrainDeformerComponent(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UFramework2DTerrainDeformerComponent) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UFramework2DTerrainDeformerComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UFramework2DTerrainDeformerComponent); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UFramework2DTerrainDeformerComponent(UFramework2DTerrainDeformerComponent&&); \
	NO_API UFramework2DTerrainDeformerComponent(const UFramework2DTerrainDeformerComponent&); \
public:


#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainDeformerComponent_h_66_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UFramework2DTerrainDeformerComponent(UFramework2DTerrainDeformerComponent&&); \
	NO_API UFramework2DTerrainDeformerComponent(const UFramework2DTerrainDeformerComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UFramework2DTerrainDeformerComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UFramework2DTerrainDeformerComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UFramework2DTerrainDeformerComponent)


#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainDeformerComponent_h_63_PROLOG
#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainDeformerComponent_h_66_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainDeformerComponent_h_66_SPARSE_DATA \
	FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainDeformerComponent_h_66_RPC_WRAPPERS \
	FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainDeformerComponent_h_66_INCLASS \
	FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainDeformerComponent_h_66_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainDeformerComponent_h_66_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainDeformerComponent_h_66_SPARSE_DATA \
	FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainDeformerComponent_h_66_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainDeformerComponent_h_66_INCLASS_NO_PURE_DECLS \
	FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainDeformerComponent_h_66_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FRAMEWORK2DTERRAIN_API UClass* StaticClass<class UFramework2DTerrainDeformerComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainDeformerComponent_h


#define FOREACH_ENUM_EFRAMEWORK2DDEFORMMODE(op) \
	op(EFramework2DDeformMode::Mine) \
	op(EFramework2DDeformMode::Dig) 

enum class EFramework2DDeformMode : uint8;
template<> FRAMEWORK2DTERRAIN_API UEnum* StaticEnum<EFramework2DDeformMode>();

#define FOREACH_ENUM_EFRAMEWORK2DFACINGSOURCE(op) \
	op(EFramework2DFacingSource::Movement) \
	op(EFramework2DFacingSource::ActorRotation) \
	op(EFramework2DFacingSource::SpriteRotation) \
	op(EFramework2DFacingSource::Mouse) 

enum class EFramework2DFacingSource : uint8;
template<> FRAMEWORK2DTERRAIN_API UEnum* StaticEnum<EFramework2DFacingSource>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
