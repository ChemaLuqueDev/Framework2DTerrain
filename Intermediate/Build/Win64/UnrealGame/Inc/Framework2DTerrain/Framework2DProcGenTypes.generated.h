// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef FRAMEWORK2DTERRAIN_Framework2DProcGenTypes_generated_h
#error "Framework2DProcGenTypes.generated.h already included, missing '#pragma once' in Framework2DProcGenTypes.h"
#endif
#define FRAMEWORK2DTERRAIN_Framework2DProcGenTypes_generated_h

#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DProcGenTypes_h_40_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FFramework2DTile3x3_Statics; \
	FRAMEWORK2DTERRAIN_API static class UScriptStruct* StaticStruct();


template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<struct FFramework2DTile3x3>();

#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DProcGenTypes_h_92_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FFramework2DTile5x5_Statics; \
	FRAMEWORK2DTERRAIN_API static class UScriptStruct* StaticStruct();


template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<struct FFramework2DTile5x5>();

#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DProcGenTypes_h_124_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FFramework2DInnerCorners_Statics; \
	FRAMEWORK2DTERRAIN_API static class UScriptStruct* StaticStruct();


template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<struct FFramework2DInnerCorners>();

#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DProcGenTypes_h_176_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FFramework2DBackdropLayer_Statics; \
	FRAMEWORK2DTERRAIN_API static class UScriptStruct* StaticStruct();


template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<struct FFramework2DBackdropLayer>();

#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DProcGenTypes_h_226_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FFramework2DPropInstance_Statics; \
	FRAMEWORK2DTERRAIN_API static class UScriptStruct* StaticStruct();


template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<struct FFramework2DPropInstance>();

#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DProcGenTypes_h_274_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FFramework2DBiomeProp_Statics; \
	FRAMEWORK2DTERRAIN_API static class UScriptStruct* StaticStruct();


template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<struct FFramework2DBiomeProp>();

#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DProcGenTypes_h_312_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FFramework2DBiomeBlock_Statics; \
	FRAMEWORK2DTERRAIN_API static class UScriptStruct* StaticStruct();


template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<struct FFramework2DBiomeBlock>();

#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DProcGenTypes_h_338_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FFramework2DBiomeGiantTree_Statics; \
	FRAMEWORK2DTERRAIN_API static class UScriptStruct* StaticStruct();


template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<struct FFramework2DBiomeGiantTree>();

#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DProcGenTypes_h_389_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FFramework2DBiomeDecoration_Statics; \
	FRAMEWORK2DTERRAIN_API static class UScriptStruct* StaticStruct();


template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<struct FFramework2DBiomeDecoration>();

#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DProcGenTypes_h_410_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FFramework2DBiome_Statics; \
	FRAMEWORK2DTERRAIN_API static class UScriptStruct* StaticStruct();


template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<struct FFramework2DBiome>();

#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DProcGenTypes_h_736_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FFramework2DProcGenSettings_Statics; \
	FRAMEWORK2DTERRAIN_API static class UScriptStruct* StaticStruct();


template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<struct FFramework2DProcGenSettings>();

#define FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DProcGenTypes_h_922_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FFramework2DProcGenReport_Statics; \
	FRAMEWORK2DTERRAIN_API static class UScriptStruct* StaticStruct();


template<> FRAMEWORK2DTERRAIN_API UScriptStruct* StaticStruct<struct FFramework2DProcGenReport>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DProcGenTypes_h


#define FOREACH_ENUM_EFRAMEWORK2DDECORPLACEMENT(op) \
	op(EFramework2DDecorPlacement::Ground) \
	op(EFramework2DDecorPlacement::Ceiling) 

enum class EFramework2DDecorPlacement : uint8;
template<> FRAMEWORK2DTERRAIN_API UEnum* StaticEnum<EFramework2DDecorPlacement>();

#define FOREACH_ENUM_EFRAMEWORK2DRELIEFSTYLE(op) \
	op(EFramework2DReliefStyle::Steps) \
	op(EFramework2DReliefStyle::Hills) 

enum class EFramework2DReliefStyle : uint8;
template<> FRAMEWORK2DTERRAIN_API UEnum* StaticEnum<EFramework2DReliefStyle>();

#define FOREACH_ENUM_EFRAMEWORK2DPROPDEPTH(op) \
	op(EFramework2DPropDepth::Behind) \
	op(EFramework2DPropDepth::Front) 

enum class EFramework2DPropDepth : uint8;
template<> FRAMEWORK2DTERRAIN_API UEnum* StaticEnum<EFramework2DPropDepth>();

#define FOREACH_ENUM_EFRAMEWORK2DBIOMESLOT(op) \
	op(EFramework2DBiomeSlot::GroundTopLeft) \
	op(EFramework2DBiomeSlot::GroundTop) \
	op(EFramework2DBiomeSlot::GroundTopRight) \
	op(EFramework2DBiomeSlot::GroundLeft) \
	op(EFramework2DBiomeSlot::GroundCenter) \
	op(EFramework2DBiomeSlot::GroundRight) \
	op(EFramework2DBiomeSlot::GroundBottomLeft) \
	op(EFramework2DBiomeSlot::GroundBottom) \
	op(EFramework2DBiomeSlot::GroundBottomRight) \
	op(EFramework2DBiomeSlot::InnerTopLeft) \
	op(EFramework2DBiomeSlot::InnerTopRight) \
	op(EFramework2DBiomeSlot::InnerBottomLeft) \
	op(EFramework2DBiomeSlot::InnerBottomRight) \
	op(EFramework2DBiomeSlot::RampUp) \
	op(EFramework2DBiomeSlot::RampDown) \
	op(EFramework2DBiomeSlot::GentleUpLow) \
	op(EFramework2DBiomeSlot::GentleUpHigh) \
	op(EFramework2DBiomeSlot::GentleDownHigh) \
	op(EFramework2DBiomeSlot::GentleDownLow) \
	op(EFramework2DBiomeSlot::PlatformLeft) \
	op(EFramework2DBiomeSlot::PlatformMiddle) \
	op(EFramework2DBiomeSlot::PlatformRight) \
	op(EFramework2DBiomeSlot::BackgroundTopLeft) \
	op(EFramework2DBiomeSlot::BackgroundTop) \
	op(EFramework2DBiomeSlot::BackgroundTopRight) \
	op(EFramework2DBiomeSlot::BackgroundLeft) \
	op(EFramework2DBiomeSlot::BackgroundCenter) \
	op(EFramework2DBiomeSlot::BackgroundRight) \
	op(EFramework2DBiomeSlot::BackgroundBottomLeft) \
	op(EFramework2DBiomeSlot::BackgroundBottom) \
	op(EFramework2DBiomeSlot::BackgroundBottomRight) \
	op(EFramework2DBiomeSlot::WaterSurface) \
	op(EFramework2DBiomeSlot::WaterBody) \
	op(EFramework2DBiomeSlot::WaterfallTop) \
	op(EFramework2DBiomeSlot::WaterfallBody) \
	op(EFramework2DBiomeSlot::WaterfallBottom) \
	op(EFramework2DBiomeSlot::BridgeLeft) \
	op(EFramework2DBiomeSlot::BridgeMiddle) \
	op(EFramework2DBiomeSlot::BridgeRight) \
	op(EFramework2DBiomeSlot::EdgeTop) \
	op(EFramework2DBiomeSlot::EdgeBottom) \
	op(EFramework2DBiomeSlot::WaterCrest) \
	op(EFramework2DBiomeSlot::BridgePostLeftLow) \
	op(EFramework2DBiomeSlot::BridgePostLeftHigh) \
	op(EFramework2DBiomeSlot::BridgePostRightLow) \
	op(EFramework2DBiomeSlot::BridgePostRightHigh) \
	op(EFramework2DBiomeSlot::Ground5_00) \
	op(EFramework2DBiomeSlot::Ground5_01) \
	op(EFramework2DBiomeSlot::Ground5_02) \
	op(EFramework2DBiomeSlot::Ground5_03) \
	op(EFramework2DBiomeSlot::Ground5_04) \
	op(EFramework2DBiomeSlot::Ground5_10) \
	op(EFramework2DBiomeSlot::Ground5_11) \
	op(EFramework2DBiomeSlot::Ground5_12) \
	op(EFramework2DBiomeSlot::Ground5_13) \
	op(EFramework2DBiomeSlot::Ground5_14) \
	op(EFramework2DBiomeSlot::Ground5_20) \
	op(EFramework2DBiomeSlot::Ground5_21) \
	op(EFramework2DBiomeSlot::Ground5_22) \
	op(EFramework2DBiomeSlot::Ground5_23) \
	op(EFramework2DBiomeSlot::Ground5_24) \
	op(EFramework2DBiomeSlot::Ground5_30) \
	op(EFramework2DBiomeSlot::Ground5_31) \
	op(EFramework2DBiomeSlot::Ground5_32) \
	op(EFramework2DBiomeSlot::Ground5_33) \
	op(EFramework2DBiomeSlot::Ground5_34) \
	op(EFramework2DBiomeSlot::Ground5_40) \
	op(EFramework2DBiomeSlot::Ground5_41) \
	op(EFramework2DBiomeSlot::Ground5_42) \
	op(EFramework2DBiomeSlot::Ground5_43) \
	op(EFramework2DBiomeSlot::Ground5_44) \
	op(EFramework2DBiomeSlot::WallFootLeft) \
	op(EFramework2DBiomeSlot::WallFootLeftInner) \
	op(EFramework2DBiomeSlot::WallFootRight) \
	op(EFramework2DBiomeSlot::WallFootRightInner) \
	op(EFramework2DBiomeSlot::PlatformCapLeft) \
	op(EFramework2DBiomeSlot::PlatformCapMiddle) \
	op(EFramework2DBiomeSlot::PlatformCapRight) \
	op(EFramework2DBiomeSlot::GroundDeep) \
	op(EFramework2DBiomeSlot::BridgeCapLeft) \
	op(EFramework2DBiomeSlot::BridgeCapMiddle) \
	op(EFramework2DBiomeSlot::BridgeCapRight) \
	op(EFramework2DBiomeSlot::Count) 

enum class EFramework2DBiomeSlot : uint8;
template<> FRAMEWORK2DTERRAIN_API UEnum* StaticEnum<EFramework2DBiomeSlot>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
