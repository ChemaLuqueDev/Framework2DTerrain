// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFramework2DTerrain_init() {}
	FRAMEWORK2DTERRAIN_API UFunction* Z_Construct_UDelegateFunction_Framework2DTerrain_Framework2DOnInventoryChanged__DelegateSignature();
	FRAMEWORK2DTERRAIN_API UFunction* Z_Construct_UDelegateFunction_Framework2DTerrain_Framework2DOnTerrainDeformed__DelegateSignature();
	FRAMEWORK2DTERRAIN_API UFunction* Z_Construct_UDelegateFunction_Framework2DTerrain_Framework2DOnTerrainMined__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_Framework2DTerrain;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_Framework2DTerrain()
	{
		if (!Z_Registration_Info_UPackage__Script_Framework2DTerrain.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_Framework2DTerrain_Framework2DOnInventoryChanged__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_Framework2DTerrain_Framework2DOnTerrainDeformed__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_Framework2DTerrain_Framework2DOnTerrainMined__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/Framework2DTerrain",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0x310ADFB5,
				0x99134977,
				METADATA_PARAMS(nullptr, 0)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_Framework2DTerrain.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_Framework2DTerrain.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_Framework2DTerrain(Z_Construct_UPackage__Script_Framework2DTerrain, TEXT("/Script/Framework2DTerrain"), Z_Registration_Info_UPackage__Script_Framework2DTerrain, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x310ADFB5, 0x99134977));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
