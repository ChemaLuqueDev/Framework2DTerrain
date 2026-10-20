// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef FRAMEWORK2DTERRAIN_Framework2DTerrainTypes_generated_h
#error "Framework2DTerrainTypes.generated.h already included, missing '#pragma once' in Framework2DTerrainTypes.h"
#endif
#define FRAMEWORK2DTERRAIN_Framework2DTerrainTypes_generated_h

#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainTypes_h_15_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FFramework2DMaterial_Statics; \
	FRAMEWORK2DTERRAIN_API static class UScriptStruct* StaticStruct();


template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<struct FFramework2DMaterial>();

#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainTypes_h_56_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FFramework2DMaterialAmount_Statics; \
	FRAMEWORK2DTERRAIN_API static class UScriptStruct* StaticStruct();


template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<struct FFramework2DMaterialAmount>();

#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainTypes_h_72_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FFramework2DDigResult_Statics; \
	FRAMEWORK2DTERRAIN_API static class UScriptStruct* StaticStruct();


template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<struct FFramework2DDigResult>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainTypes_h


#define FOREACH_ENUM_EFRAMEWORK2DDEBRISMODE(op) \
	op(EFramework2DDebrisMode::None) \
	op(EFramework2DDebrisMode::Burst) \
	op(EFramework2DDebrisMode::ToCollector) 

enum class EFramework2DDebrisMode : uint8;
template<> FRAMEWORK2DTERRAIN_API UEnum* StaticEnum<EFramework2DDebrisMode>();

#define FOREACH_ENUM_EFRAMEWORK2DCOLLISIONSHAPE(op) \
	op(EFramework2DCollisionShape::Auto) \
	op(EFramework2DCollisionShape::None) \
	op(EFramework2DCollisionShape::Pixels) \
	op(EFramework2DCollisionShape::Full) \
	op(EFramework2DCollisionShape::TopHalf) \
	op(EFramework2DCollisionShape::BottomHalf) \
	op(EFramework2DCollisionShape::LeftHalf) \
	op(EFramework2DCollisionShape::RightHalf) \
	op(EFramework2DCollisionShape::SlopeUp) \
	op(EFramework2DCollisionShape::SlopeDown) \
	op(EFramework2DCollisionShape::Platform) 

enum class EFramework2DCollisionShape : uint8;
template<> FRAMEWORK2DTERRAIN_API UEnum* StaticEnum<EFramework2DCollisionShape>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
