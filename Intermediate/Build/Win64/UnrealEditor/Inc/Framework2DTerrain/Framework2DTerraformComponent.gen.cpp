// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Framework2DTerrain/Public/Framework2DTerraformComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFramework2DTerraformComponent() {}
// Cross Module References
	FRAMEWORK2DTERRAIN_API UFunction* Z_Construct_UDelegateFunction_Framework2DTerrain_Framework2DOnInventoryChanged__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_Framework2DTerrain();
	FRAMEWORK2DTERRAIN_API UClass* Z_Construct_UClass_UFramework2DTerraformComponent_NoRegister();
	FRAMEWORK2DTERRAIN_API UClass* Z_Construct_UClass_UFramework2DTerraformComponent();
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	FRAMEWORK2DTERRAIN_API UClass* Z_Construct_UClass_AFramework2DTerrainWorld_NoRegister();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	FRAMEWORK2DTERRAIN_API UScriptStruct* Z_Construct_UScriptStruct_FFramework2DDigResult();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_Framework2DTerrain_Framework2DOnInventoryChanged__DelegateSignature_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_Framework2DTerrain_Framework2DOnInventoryChanged__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Framework2DTerraformComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_Framework2DTerrain_Framework2DOnInventoryChanged__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_Framework2DTerrain, nullptr, "Framework2DOnInventoryChanged__DelegateSignature", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_Framework2DTerrain_Framework2DOnInventoryChanged__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_Framework2DTerrain_Framework2DOnInventoryChanged__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_Framework2DTerrain_Framework2DOnInventoryChanged__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_Framework2DTerrain_Framework2DOnInventoryChanged__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	DEFINE_FUNCTION(UFramework2DTerraformComponent::execGetTerrain)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(AFramework2DTerrainWorld**)Z_Param__Result=P_THIS->GetTerrain();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFramework2DTerraformComponent::execConsumeMaterial)
	{
		P_GET_PROPERTY(FNameProperty,Z_Param_Material);
		P_GET_PROPERTY(FIntProperty,Z_Param_Count);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->ConsumeMaterial(Z_Param_Material,Z_Param_Count);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFramework2DTerraformComponent::execAddMaterial)
	{
		P_GET_PROPERTY(FNameProperty,Z_Param_Material);
		P_GET_PROPERTY(FIntProperty,Z_Param_Count);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->AddMaterial(Z_Param_Material,Z_Param_Count);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFramework2DTerraformComponent::execGetTotalStored)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->GetTotalStored();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFramework2DTerraformComponent::execGetAmount)
	{
		P_GET_PROPERTY(FNameProperty,Z_Param_Material);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->GetAmount(Z_Param_Material);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFramework2DTerraformComponent::execSelectNextMaterial)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_Direction);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SelectNextMaterial(Z_Param_Direction);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFramework2DTerraformComponent::execPlaceToward)
	{
		P_GET_STRUCT(FVector,Z_Param_TargetWorld);
		P_GET_PROPERTY(FFloatProperty,Z_Param_DeltaSeconds);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->PlaceToward(Z_Param_TargetWorld,Z_Param_DeltaSeconds);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFramework2DTerraformComponent::execMineToward)
	{
		P_GET_STRUCT(FVector,Z_Param_TargetWorld);
		P_GET_PROPERTY(FFloatProperty,Z_Param_DeltaSeconds);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FFramework2DDigResult*)Z_Param__Result=P_THIS->MineToward(Z_Param_TargetWorld,Z_Param_DeltaSeconds);
		P_NATIVE_END;
	}
	void UFramework2DTerraformComponent::StaticRegisterNativesUFramework2DTerraformComponent()
	{
		UClass* Class = UFramework2DTerraformComponent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "AddMaterial", &UFramework2DTerraformComponent::execAddMaterial },
			{ "ConsumeMaterial", &UFramework2DTerraformComponent::execConsumeMaterial },
			{ "GetAmount", &UFramework2DTerraformComponent::execGetAmount },
			{ "GetTerrain", &UFramework2DTerraformComponent::execGetTerrain },
			{ "GetTotalStored", &UFramework2DTerraformComponent::execGetTotalStored },
			{ "MineToward", &UFramework2DTerraformComponent::execMineToward },
			{ "PlaceToward", &UFramework2DTerraformComponent::execPlaceToward },
			{ "SelectNextMaterial", &UFramework2DTerraformComponent::execSelectNextMaterial },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UFramework2DTerraformComponent_AddMaterial_Statics
	{
		struct Framework2DTerraformComponent_eventAddMaterial_Parms
		{
			FName Material;
			int32 Count;
			int32 ReturnValue;
		};
		static const UECodeGen_Private::FNamePropertyParams NewProp_Material;
		static const UECodeGen_Private::FIntPropertyParams NewProp_Count;
		static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UFramework2DTerraformComponent_AddMaterial_Statics::NewProp_Material = { "Material", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DTerraformComponent_eventAddMaterial_Parms, Material), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UFramework2DTerraformComponent_AddMaterial_Statics::NewProp_Count = { "Count", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DTerraformComponent_eventAddMaterial_Parms, Count), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UFramework2DTerraformComponent_AddMaterial_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DTerraformComponent_eventAddMaterial_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFramework2DTerraformComponent_AddMaterial_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTerraformComponent_AddMaterial_Statics::NewProp_Material,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTerraformComponent_AddMaterial_Statics::NewProp_Count,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTerraformComponent_AddMaterial_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFramework2DTerraformComponent_AddMaterial_Statics::Function_MetaDataParams[] = {
		{ "Category", "Framework2D|Terraform" },
		{ "Comment", "/** Mete material en el inventario (respeta Capacity). Devuelve lo que cupo. */" },
		{ "ModuleRelativePath", "Public/Framework2DTerraformComponent.h" },
		{ "ToolTip", "Mete material en el inventario (respeta Capacity). Devuelve lo que cupo." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFramework2DTerraformComponent_AddMaterial_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFramework2DTerraformComponent, nullptr, "AddMaterial", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFramework2DTerraformComponent_AddMaterial_Statics::Framework2DTerraformComponent_eventAddMaterial_Parms), Z_Construct_UFunction_UFramework2DTerraformComponent_AddMaterial_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTerraformComponent_AddMaterial_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFramework2DTerraformComponent_AddMaterial_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTerraformComponent_AddMaterial_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFramework2DTerraformComponent_AddMaterial()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFramework2DTerraformComponent_AddMaterial_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFramework2DTerraformComponent_ConsumeMaterial_Statics
	{
		struct Framework2DTerraformComponent_eventConsumeMaterial_Parms
		{
			FName Material;
			int32 Count;
			bool ReturnValue;
		};
		static const UECodeGen_Private::FNamePropertyParams NewProp_Material;
		static const UECodeGen_Private::FIntPropertyParams NewProp_Count;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UFramework2DTerraformComponent_ConsumeMaterial_Statics::NewProp_Material = { "Material", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DTerraformComponent_eventConsumeMaterial_Parms, Material), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UFramework2DTerraformComponent_ConsumeMaterial_Statics::NewProp_Count = { "Count", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DTerraformComponent_eventConsumeMaterial_Parms, Count), METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UFramework2DTerraformComponent_ConsumeMaterial_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((Framework2DTerraformComponent_eventConsumeMaterial_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UFramework2DTerraformComponent_ConsumeMaterial_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(Framework2DTerraformComponent_eventConsumeMaterial_Parms), &Z_Construct_UFunction_UFramework2DTerraformComponent_ConsumeMaterial_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFramework2DTerraformComponent_ConsumeMaterial_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTerraformComponent_ConsumeMaterial_Statics::NewProp_Material,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTerraformComponent_ConsumeMaterial_Statics::NewProp_Count,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTerraformComponent_ConsumeMaterial_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFramework2DTerraformComponent_ConsumeMaterial_Statics::Function_MetaDataParams[] = {
		{ "Category", "Framework2D|Terraform" },
		{ "Comment", "/** Gasta material. Devuelve false (y no gasta nada) si no hay suficiente. */" },
		{ "ModuleRelativePath", "Public/Framework2DTerraformComponent.h" },
		{ "ToolTip", "Gasta material. Devuelve false (y no gasta nada) si no hay suficiente." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFramework2DTerraformComponent_ConsumeMaterial_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFramework2DTerraformComponent, nullptr, "ConsumeMaterial", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFramework2DTerraformComponent_ConsumeMaterial_Statics::Framework2DTerraformComponent_eventConsumeMaterial_Parms), Z_Construct_UFunction_UFramework2DTerraformComponent_ConsumeMaterial_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTerraformComponent_ConsumeMaterial_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFramework2DTerraformComponent_ConsumeMaterial_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTerraformComponent_ConsumeMaterial_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFramework2DTerraformComponent_ConsumeMaterial()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFramework2DTerraformComponent_ConsumeMaterial_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFramework2DTerraformComponent_GetAmount_Statics
	{
		struct Framework2DTerraformComponent_eventGetAmount_Parms
		{
			FName Material;
			int32 ReturnValue;
		};
		static const UECodeGen_Private::FNamePropertyParams NewProp_Material;
		static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UFramework2DTerraformComponent_GetAmount_Statics::NewProp_Material = { "Material", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DTerraformComponent_eventGetAmount_Parms, Material), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UFramework2DTerraformComponent_GetAmount_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DTerraformComponent_eventGetAmount_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFramework2DTerraformComponent_GetAmount_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTerraformComponent_GetAmount_Statics::NewProp_Material,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTerraformComponent_GetAmount_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFramework2DTerraformComponent_GetAmount_Statics::Function_MetaDataParams[] = {
		{ "Category", "Framework2D|Terraform" },
		{ "Comment", "/** Celdas que llevas de un material. */" },
		{ "ModuleRelativePath", "Public/Framework2DTerraformComponent.h" },
		{ "ToolTip", "Celdas que llevas de un material." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFramework2DTerraformComponent_GetAmount_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFramework2DTerraformComponent, nullptr, "GetAmount", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFramework2DTerraformComponent_GetAmount_Statics::Framework2DTerraformComponent_eventGetAmount_Parms), Z_Construct_UFunction_UFramework2DTerraformComponent_GetAmount_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTerraformComponent_GetAmount_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFramework2DTerraformComponent_GetAmount_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTerraformComponent_GetAmount_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFramework2DTerraformComponent_GetAmount()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFramework2DTerraformComponent_GetAmount_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFramework2DTerraformComponent_GetTerrain_Statics
	{
		struct Framework2DTerraformComponent_eventGetTerrain_Parms
		{
			AFramework2DTerrainWorld* ReturnValue;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFramework2DTerraformComponent_GetTerrain_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DTerraformComponent_eventGetTerrain_Parms, ReturnValue), Z_Construct_UClass_AFramework2DTerrainWorld_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFramework2DTerraformComponent_GetTerrain_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTerraformComponent_GetTerrain_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFramework2DTerraformComponent_GetTerrain_Statics::Function_MetaDataParams[] = {
		{ "Category", "Framework2D|Terraform" },
		{ "Comment", "/** El terreno en uso (busca uno en el nivel si Terrain esta vacio). */" },
		{ "ModuleRelativePath", "Public/Framework2DTerraformComponent.h" },
		{ "ToolTip", "El terreno en uso (busca uno en el nivel si Terrain esta vacio)." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFramework2DTerraformComponent_GetTerrain_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFramework2DTerraformComponent, nullptr, "GetTerrain", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFramework2DTerraformComponent_GetTerrain_Statics::Framework2DTerraformComponent_eventGetTerrain_Parms), Z_Construct_UFunction_UFramework2DTerraformComponent_GetTerrain_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTerraformComponent_GetTerrain_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFramework2DTerraformComponent_GetTerrain_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTerraformComponent_GetTerrain_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFramework2DTerraformComponent_GetTerrain()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFramework2DTerraformComponent_GetTerrain_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFramework2DTerraformComponent_GetTotalStored_Statics
	{
		struct Framework2DTerraformComponent_eventGetTotalStored_Parms
		{
			int32 ReturnValue;
		};
		static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UFramework2DTerraformComponent_GetTotalStored_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DTerraformComponent_eventGetTotalStored_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFramework2DTerraformComponent_GetTotalStored_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTerraformComponent_GetTotalStored_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFramework2DTerraformComponent_GetTotalStored_Statics::Function_MetaDataParams[] = {
		{ "Category", "Framework2D|Terraform" },
		{ "Comment", "/** Celdas totales en el inventario. */" },
		{ "ModuleRelativePath", "Public/Framework2DTerraformComponent.h" },
		{ "ToolTip", "Celdas totales en el inventario." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFramework2DTerraformComponent_GetTotalStored_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFramework2DTerraformComponent, nullptr, "GetTotalStored", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFramework2DTerraformComponent_GetTotalStored_Statics::Framework2DTerraformComponent_eventGetTotalStored_Parms), Z_Construct_UFunction_UFramework2DTerraformComponent_GetTotalStored_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTerraformComponent_GetTotalStored_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFramework2DTerraformComponent_GetTotalStored_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTerraformComponent_GetTotalStored_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFramework2DTerraformComponent_GetTotalStored()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFramework2DTerraformComponent_GetTotalStored_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFramework2DTerraformComponent_MineToward_Statics
	{
		struct Framework2DTerraformComponent_eventMineToward_Parms
		{
			FVector TargetWorld;
			float DeltaSeconds;
			FFramework2DDigResult ReturnValue;
		};
		static const UECodeGen_Private::FStructPropertyParams NewProp_TargetWorld;
		static const UECodeGen_Private::FFloatPropertyParams NewProp_DeltaSeconds;
		static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFramework2DTerraformComponent_MineToward_Statics::NewProp_TargetWorld = { "TargetWorld", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DTerraformComponent_eventMineToward_Parms, TargetWorld), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFramework2DTerraformComponent_MineToward_Statics::NewProp_DeltaSeconds = { "DeltaSeconds", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DTerraformComponent_eventMineToward_Parms, DeltaSeconds), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFramework2DTerraformComponent_MineToward_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DTerraformComponent_eventMineToward_Parms, ReturnValue), Z_Construct_UScriptStruct_FFramework2DDigResult, METADATA_PARAMS(nullptr, 0) }; // 3002348450
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFramework2DTerraformComponent_MineToward_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTerraformComponent_MineToward_Statics::NewProp_TargetWorld,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTerraformComponent_MineToward_Statics::NewProp_DeltaSeconds,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTerraformComponent_MineToward_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFramework2DTerraformComponent_MineToward_Statics::Function_MetaDataParams[] = {
		{ "Category", "Framework2D|Terraform" },
		{ "Comment", "/** Pica hacia TargetWorld (rayo desde el dueno). Llamalo cada frame con el boton pulsado. */" },
		{ "ModuleRelativePath", "Public/Framework2DTerraformComponent.h" },
		{ "ToolTip", "Pica hacia TargetWorld (rayo desde el dueno). Llamalo cada frame con el boton pulsado." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFramework2DTerraformComponent_MineToward_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFramework2DTerraformComponent, nullptr, "MineToward", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFramework2DTerraformComponent_MineToward_Statics::Framework2DTerraformComponent_eventMineToward_Parms), Z_Construct_UFunction_UFramework2DTerraformComponent_MineToward_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTerraformComponent_MineToward_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04820401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFramework2DTerraformComponent_MineToward_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTerraformComponent_MineToward_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFramework2DTerraformComponent_MineToward()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFramework2DTerraformComponent_MineToward_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFramework2DTerraformComponent_PlaceToward_Statics
	{
		struct Framework2DTerraformComponent_eventPlaceToward_Parms
		{
			FVector TargetWorld;
			float DeltaSeconds;
			int32 ReturnValue;
		};
		static const UECodeGen_Private::FStructPropertyParams NewProp_TargetWorld;
		static const UECodeGen_Private::FFloatPropertyParams NewProp_DeltaSeconds;
		static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFramework2DTerraformComponent_PlaceToward_Statics::NewProp_TargetWorld = { "TargetWorld", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DTerraformComponent_eventPlaceToward_Parms, TargetWorld), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFramework2DTerraformComponent_PlaceToward_Statics::NewProp_DeltaSeconds = { "DeltaSeconds", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DTerraformComponent_eventPlaceToward_Parms, DeltaSeconds), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UFramework2DTerraformComponent_PlaceToward_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DTerraformComponent_eventPlaceToward_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFramework2DTerraformComponent_PlaceToward_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTerraformComponent_PlaceToward_Statics::NewProp_TargetWorld,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTerraformComponent_PlaceToward_Statics::NewProp_DeltaSeconds,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTerraformComponent_PlaceToward_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFramework2DTerraformComponent_PlaceToward_Statics::Function_MetaDataParams[] = {
		{ "Category", "Framework2D|Terraform" },
		{ "Comment", "/** Coloca el material seleccionado en TargetWorld (recortado al alcance). Devuelve celdas colocadas. */" },
		{ "ModuleRelativePath", "Public/Framework2DTerraformComponent.h" },
		{ "ToolTip", "Coloca el material seleccionado en TargetWorld (recortado al alcance). Devuelve celdas colocadas." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFramework2DTerraformComponent_PlaceToward_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFramework2DTerraformComponent, nullptr, "PlaceToward", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFramework2DTerraformComponent_PlaceToward_Statics::Framework2DTerraformComponent_eventPlaceToward_Parms), Z_Construct_UFunction_UFramework2DTerraformComponent_PlaceToward_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTerraformComponent_PlaceToward_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04820401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFramework2DTerraformComponent_PlaceToward_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTerraformComponent_PlaceToward_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFramework2DTerraformComponent_PlaceToward()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFramework2DTerraformComponent_PlaceToward_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFramework2DTerraformComponent_SelectNextMaterial_Statics
	{
		struct Framework2DTerraformComponent_eventSelectNextMaterial_Parms
		{
			int32 Direction;
		};
		static const UECodeGen_Private::FIntPropertyParams NewProp_Direction;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UFramework2DTerraformComponent_SelectNextMaterial_Statics::NewProp_Direction = { "Direction", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DTerraformComponent_eventSelectNextMaterial_Parms, Direction), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFramework2DTerraformComponent_SelectNextMaterial_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTerraformComponent_SelectNextMaterial_Statics::NewProp_Direction,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFramework2DTerraformComponent_SelectNextMaterial_Statics::Function_MetaDataParams[] = {
		{ "Category", "Framework2D|Terraform" },
		{ "Comment", "/** Pasa al siguiente (+1) o anterior (-1) material del inventario. */" },
		{ "CPP_Default_Direction", "1" },
		{ "ModuleRelativePath", "Public/Framework2DTerraformComponent.h" },
		{ "ToolTip", "Pasa al siguiente (+1) o anterior (-1) material del inventario." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFramework2DTerraformComponent_SelectNextMaterial_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFramework2DTerraformComponent, nullptr, "SelectNextMaterial", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFramework2DTerraformComponent_SelectNextMaterial_Statics::Framework2DTerraformComponent_eventSelectNextMaterial_Parms), Z_Construct_UFunction_UFramework2DTerraformComponent_SelectNextMaterial_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTerraformComponent_SelectNextMaterial_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFramework2DTerraformComponent_SelectNextMaterial_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTerraformComponent_SelectNextMaterial_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFramework2DTerraformComponent_SelectNextMaterial()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFramework2DTerraformComponent_SelectNextMaterial_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UFramework2DTerraformComponent);
	UClass* Z_Construct_UClass_UFramework2DTerraformComponent_NoRegister()
	{
		return UFramework2DTerraformComponent::StaticClass();
	}
	struct Z_Construct_UClass_UFramework2DTerraformComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Terrain_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_Terrain;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Range_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Range;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MineRadius_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_MineRadius;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MineDamagePerSecond_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_MineDamagePerSecond;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PlaceRadius_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_PlaceRadius;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PlaceCellsPerSecond_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_PlaceCellsPerSecond;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Capacity_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Capacity;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bInfiniteMaterials_MetaData[];
#endif
		static void NewProp_bInfiniteMaterials_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bInfiniteMaterials;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bAvoidPawnsWhenPlacing_MetaData[];
#endif
		static void NewProp_bAvoidPawnsWhenPlacing_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bAvoidPawnsWhenPlacing;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SelectedMaterial_MetaData[];
#endif
		static const UECodeGen_Private::FNamePropertyParams NewProp_SelectedMaterial;
		static const UECodeGen_Private::FIntPropertyParams NewProp_Inventory_ValueProp;
		static const UECodeGen_Private::FNamePropertyParams NewProp_Inventory_Key_KeyProp;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Inventory_MetaData[];
#endif
		static const UECodeGen_Private::FMapPropertyParams NewProp_Inventory;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OnInventoryChanged_MetaData[];
#endif
		static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnInventoryChanged;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UFramework2DTerraformComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_Framework2DTerrain,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UFramework2DTerraformComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UFramework2DTerraformComponent_AddMaterial, "AddMaterial" }, // 3343185675
		{ &Z_Construct_UFunction_UFramework2DTerraformComponent_ConsumeMaterial, "ConsumeMaterial" }, // 1875571461
		{ &Z_Construct_UFunction_UFramework2DTerraformComponent_GetAmount, "GetAmount" }, // 3118986526
		{ &Z_Construct_UFunction_UFramework2DTerraformComponent_GetTerrain, "GetTerrain" }, // 1474887723
		{ &Z_Construct_UFunction_UFramework2DTerraformComponent_GetTotalStored, "GetTotalStored" }, // 1980316456
		{ &Z_Construct_UFunction_UFramework2DTerraformComponent_MineToward, "MineToward" }, // 234909021
		{ &Z_Construct_UFunction_UFramework2DTerraformComponent_PlaceToward, "PlaceToward" }, // 3103877408
		{ &Z_Construct_UFunction_UFramework2DTerraformComponent_SelectNextMaterial, "SelectNextMaterial" }, // 2739879217
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTerraformComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Framework2D" },
		{ "Comment", "/**\n * UFramework2DTerraformComponent\n * =================================================================\n * La \"varita\" estilo KYORA, lista para poner en tu personaje:\n *   - MineToward: lanza un rayo desde el dueno hacia un punto, pica lo PRIMERO que toca\n *     (con la dureza de cada material) y GUARDA lo picado en el inventario.\n *   - PlaceToward: coloca el material seleccionado gastando inventario (terraformar).\n *\n * Llamalos cada frame mientras el boton este pulsado (pasando DeltaSeconds): el dano y\n * las celdas colocadas se reparten por segundo, no por clic.\n *\n * Prefijo U = UObject. Es un ActorComponent: anadelo en el Blueprint de tu personaje.\n */" },
		{ "IncludePath", "Framework2DTerraformComponent.h" },
		{ "ModuleRelativePath", "Public/Framework2DTerraformComponent.h" },
		{ "ToolTip", "UFramework2DTerraformComponent\n\nLa \"varita\" estilo KYORA, lista para poner en tu personaje:\n  - MineToward: lanza un rayo desde el dueno hacia un punto, pica lo PRIMERO que toca\n    (con la dureza de cada material) y GUARDA lo picado en el inventario.\n  - PlaceToward: coloca el material seleccionado gastando inventario (terraformar).\n\nLlamalos cada frame mientras el boton este pulsado (pasando DeltaSeconds): el dano y\nlas celdas colocadas se reparten por segundo, no por clic.\n\nPrefijo U = UObject. Es un ActorComponent: anadelo en el Blueprint de tu personaje." },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_Terrain_MetaData[] = {
		{ "Category", "Framework2D|Terraform" },
		{ "Comment", "/** Terreno sobre el que actua. Si lo dejas vacio, usa el primero que haya en el nivel. */" },
		{ "ModuleRelativePath", "Public/Framework2DTerraformComponent.h" },
		{ "ToolTip", "Terreno sobre el que actua. Si lo dejas vacio, usa el primero que haya en el nivel." },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_Terrain = { "Terrain", nullptr, (EPropertyFlags)0x0014000000000005, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTerraformComponent, Terrain), Z_Construct_UClass_AFramework2DTerrainWorld_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_Terrain_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_Terrain_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_Range_MetaData[] = {
		{ "Category", "Framework2D|Terraform" },
		{ "ClampMin", "0.0" },
		{ "Comment", "/** Alcance maximo (cm) desde el dueno. */" },
		{ "ModuleRelativePath", "Public/Framework2DTerraformComponent.h" },
		{ "ToolTip", "Alcance maximo (cm) desde el dueno." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_Range = { "Range", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTerraformComponent, Range), METADATA_PARAMS(Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_Range_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_Range_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_MineRadius_MetaData[] = {
		{ "Category", "Framework2D|Terraform" },
		{ "ClampMin", "0.0" },
		{ "Comment", "/** Radio (cm) de la punta al picar. */" },
		{ "ModuleRelativePath", "Public/Framework2DTerraformComponent.h" },
		{ "ToolTip", "Radio (cm) de la punta al picar." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_MineRadius = { "MineRadius", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTerraformComponent, MineRadius), METADATA_PARAMS(Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_MineRadius_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_MineRadius_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_MineDamagePerSecond_MetaData[] = {
		{ "Category", "Framework2D|Terraform" },
		{ "ClampMin", "0.0" },
		{ "Comment", "/** Dano por segundo. Se compara con la Hardness de cada material (Dirt 3, Stone 8...). */" },
		{ "ModuleRelativePath", "Public/Framework2DTerraformComponent.h" },
		{ "ToolTip", "Dano por segundo. Se compara con la Hardness de cada material (Dirt 3, Stone 8...)." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_MineDamagePerSecond = { "MineDamagePerSecond", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTerraformComponent, MineDamagePerSecond), METADATA_PARAMS(Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_MineDamagePerSecond_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_MineDamagePerSecond_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_PlaceRadius_MetaData[] = {
		{ "Category", "Framework2D|Terraform" },
		{ "ClampMin", "0.0" },
		{ "Comment", "/** Radio (cm) al colocar. */" },
		{ "ModuleRelativePath", "Public/Framework2DTerraformComponent.h" },
		{ "ToolTip", "Radio (cm) al colocar." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_PlaceRadius = { "PlaceRadius", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTerraformComponent, PlaceRadius), METADATA_PARAMS(Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_PlaceRadius_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_PlaceRadius_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_PlaceCellsPerSecond_MetaData[] = {
		{ "Category", "Framework2D|Terraform" },
		{ "ClampMin", "0.0" },
		{ "Comment", "/** Celdas por segundo que puede colocar. */" },
		{ "ModuleRelativePath", "Public/Framework2DTerraformComponent.h" },
		{ "ToolTip", "Celdas por segundo que puede colocar." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_PlaceCellsPerSecond = { "PlaceCellsPerSecond", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTerraformComponent, PlaceCellsPerSecond), METADATA_PARAMS(Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_PlaceCellsPerSecond_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_PlaceCellsPerSecond_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_Capacity_MetaData[] = {
		{ "Category", "Framework2D|Terraform" },
		{ "ClampMin", "0" },
		{ "Comment", "/** Capacidad total del inventario (en celdas). 0 = sin limite. */" },
		{ "ModuleRelativePath", "Public/Framework2DTerraformComponent.h" },
		{ "ToolTip", "Capacidad total del inventario (en celdas). 0 = sin limite." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_Capacity = { "Capacity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTerraformComponent, Capacity), METADATA_PARAMS(Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_Capacity_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_Capacity_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_bInfiniteMaterials_MetaData[] = {
		{ "Category", "Framework2D|Terraform" },
		{ "Comment", "/** Modo creativo: colocar no gasta inventario y puedes elegir cualquier material del tileset. */" },
		{ "ModuleRelativePath", "Public/Framework2DTerraformComponent.h" },
		{ "ToolTip", "Modo creativo: colocar no gasta inventario y puedes elegir cualquier material del tileset." },
	};
#endif
	void Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_bInfiniteMaterials_SetBit(void* Obj)
	{
		((UFramework2DTerraformComponent*)Obj)->bInfiniteMaterials = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_bInfiniteMaterials = { "bInfiniteMaterials", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UFramework2DTerraformComponent), &Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_bInfiniteMaterials_SetBit, METADATA_PARAMS(Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_bInfiniteMaterials_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_bInfiniteMaterials_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_bAvoidPawnsWhenPlacing_MetaData[] = {
		{ "Category", "Framework2D|Terraform" },
		{ "Comment", "/** No coloca terreno encima de personajes (evita dejarlos atrapados). */" },
		{ "ModuleRelativePath", "Public/Framework2DTerraformComponent.h" },
		{ "ToolTip", "No coloca terreno encima de personajes (evita dejarlos atrapados)." },
	};
#endif
	void Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_bAvoidPawnsWhenPlacing_SetBit(void* Obj)
	{
		((UFramework2DTerraformComponent*)Obj)->bAvoidPawnsWhenPlacing = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_bAvoidPawnsWhenPlacing = { "bAvoidPawnsWhenPlacing", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UFramework2DTerraformComponent), &Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_bAvoidPawnsWhenPlacing_SetBit, METADATA_PARAMS(Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_bAvoidPawnsWhenPlacing_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_bAvoidPawnsWhenPlacing_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_SelectedMaterial_MetaData[] = {
		{ "Category", "Framework2D|Terraform" },
		{ "Comment", "/** Material que se coloca. Se elige solo con lo primero que piques (o escribelo a mano). */" },
		{ "ModuleRelativePath", "Public/Framework2DTerraformComponent.h" },
		{ "ToolTip", "Material que se coloca. Se elige solo con lo primero que piques (o escribelo a mano)." },
	};
#endif
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_SelectedMaterial = { "SelectedMaterial", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTerraformComponent, SelectedMaterial), METADATA_PARAMS(Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_SelectedMaterial_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_SelectedMaterial_MetaData)) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_Inventory_ValueProp = { "Inventory", nullptr, (EPropertyFlags)0x0000000000020001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 1, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_Inventory_Key_KeyProp = { "Inventory_Key", nullptr, (EPropertyFlags)0x0000000000020001, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_Inventory_MetaData[] = {
		{ "Category", "Framework2D|Terraform" },
		{ "Comment", "/** Lo que llevas: material -> celdas. */" },
		{ "ModuleRelativePath", "Public/Framework2DTerraformComponent.h" },
		{ "ToolTip", "Lo que llevas: material -> celdas." },
	};
#endif
	const UECodeGen_Private::FMapPropertyParams Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_Inventory = { "Inventory", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTerraformComponent, Inventory), EMapPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_Inventory_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_Inventory_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_OnInventoryChanged_MetaData[] = {
		{ "Category", "Framework2D|Terraform" },
		{ "Comment", "/** Se emite cuando cambia el inventario o el material seleccionado. */" },
		{ "ModuleRelativePath", "Public/Framework2DTerraformComponent.h" },
		{ "ToolTip", "Se emite cuando cambia el inventario o el material seleccionado." },
	};
#endif
	const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_OnInventoryChanged = { "OnInventoryChanged", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTerraformComponent, OnInventoryChanged), Z_Construct_UDelegateFunction_Framework2DTerrain_Framework2DOnInventoryChanged__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_OnInventoryChanged_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_OnInventoryChanged_MetaData)) }; // 398468763
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UFramework2DTerraformComponent_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_Terrain,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_Range,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_MineRadius,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_MineDamagePerSecond,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_PlaceRadius,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_PlaceCellsPerSecond,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_Capacity,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_bInfiniteMaterials,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_bAvoidPawnsWhenPlacing,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_SelectedMaterial,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_Inventory_ValueProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_Inventory_Key_KeyProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_Inventory,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTerraformComponent_Statics::NewProp_OnInventoryChanged,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UFramework2DTerraformComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFramework2DTerraformComponent>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UFramework2DTerraformComponent_Statics::ClassParams = {
		&UFramework2DTerraformComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UFramework2DTerraformComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTerraformComponent_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UFramework2DTerraformComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTerraformComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UFramework2DTerraformComponent()
	{
		if (!Z_Registration_Info_UClass_UFramework2DTerraformComponent.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UFramework2DTerraformComponent.OuterSingleton, Z_Construct_UClass_UFramework2DTerraformComponent_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UFramework2DTerraformComponent.OuterSingleton;
	}
	template<> FRAMEWORK2DTERRAIN_API UClass* StaticClass<UFramework2DTerraformComponent>()
	{
		return UFramework2DTerraformComponent::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UFramework2DTerraformComponent);
	struct Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerraformComponent_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerraformComponent_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UFramework2DTerraformComponent, UFramework2DTerraformComponent::StaticClass, TEXT("UFramework2DTerraformComponent"), &Z_Registration_Info_UClass_UFramework2DTerraformComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UFramework2DTerraformComponent), 2050553861U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerraformComponent_h_3905070283(TEXT("/Script/Framework2DTerrain"),
		Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerraformComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerraformComponent_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
