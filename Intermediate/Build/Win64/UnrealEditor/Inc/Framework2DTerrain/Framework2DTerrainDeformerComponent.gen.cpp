// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Framework2DTerrain/Public/Framework2DTerrainDeformerComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFramework2DTerrainDeformerComponent() {}
// Cross Module References
	FRAMEWORK2DTERRAIN_API UEnum* Z_Construct_UEnum_Framework2DTerrain_EFramework2DDeformMode();
	UPackage* Z_Construct_UPackage__Script_Framework2DTerrain();
	FRAMEWORK2DTERRAIN_API UEnum* Z_Construct_UEnum_Framework2DTerrain_EFramework2DFacingSource();
	FRAMEWORK2DTERRAIN_API UFunction* Z_Construct_UDelegateFunction_Framework2DTerrain_Framework2DOnTerrainDeformed__DelegateSignature();
	FRAMEWORK2DTERRAIN_API UScriptStruct* Z_Construct_UScriptStruct_FFramework2DDigResult();
	FRAMEWORK2DTERRAIN_API UClass* Z_Construct_UClass_UFramework2DTerrainDeformerComponent_NoRegister();
	FRAMEWORK2DTERRAIN_API UClass* Z_Construct_UClass_UFramework2DTerrainDeformerComponent();
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	INPUTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FKey();
	FRAMEWORK2DTERRAIN_API UClass* Z_Construct_UClass_AFramework2DTerrainWorld_NoRegister();
// End Cross Module References
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_EFramework2DDeformMode;
	static UEnum* EFramework2DDeformMode_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_EFramework2DDeformMode.OuterSingleton)
		{
			Z_Registration_Info_UEnum_EFramework2DDeformMode.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_Framework2DTerrain_EFramework2DDeformMode, Z_Construct_UPackage__Script_Framework2DTerrain(), TEXT("EFramework2DDeformMode"));
		}
		return Z_Registration_Info_UEnum_EFramework2DDeformMode.OuterSingleton;
	}
	template<> FRAMEWORK2DTERRAIN_API UEnum* StaticEnum<EFramework2DDeformMode>()
	{
		return EFramework2DDeformMode_StaticEnum();
	}
	struct Z_Construct_UEnum_Framework2DTerrain_EFramework2DDeformMode_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_Framework2DTerrain_EFramework2DDeformMode_Statics::Enumerators[] = {
		{ "EFramework2DDeformMode::Mine", (int64)EFramework2DDeformMode::Mine },
		{ "EFramework2DDeformMode::Dig", (int64)EFramework2DDeformMode::Dig },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_Framework2DTerrain_EFramework2DDeformMode_Statics::Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/** Como cambia el terreno cada golpe. */" },
		{ "Dig.Comment", "// Quita un circulo exacto al instante, sin mirar la dureza (lo indestructible no se toca). Sin escombros.\n" },
		{ "Dig.DisplayName", "Excavar (al instante)" },
		{ "Dig.Name", "EFramework2DDeformMode::Dig" },
		{ "Dig.ToolTip", "Quita un circulo exacto al instante, sin mirar la dureza (lo indestructible no se toca). Sin escombros." },
		{ "Mine.Comment", "// Suma Damage a cada pixel del circulo: se rompe al llegar a la dureza (Hardness) de su material.\n// Borde irregular y escombros (hacia el personaje si el terreno los manda a quien pica).\n" },
		{ "Mine.DisplayName", "Picar (con dureza)" },
		{ "Mine.Name", "EFramework2DDeformMode::Mine" },
		{ "Mine.ToolTip", "Suma Damage a cada pixel del circulo: se rompe al llegar a la dureza (Hardness) de su material.\nBorde irregular y escombros (hacia el personaje si el terreno los manda a quien pica)." },
		{ "ModuleRelativePath", "Public/Framework2DTerrainDeformerComponent.h" },
		{ "ToolTip", "Como cambia el terreno cada golpe." },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_Framework2DTerrain_EFramework2DDeformMode_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_Framework2DTerrain,
		nullptr,
		"EFramework2DDeformMode",
		"EFramework2DDeformMode",
		Z_Construct_UEnum_Framework2DTerrain_EFramework2DDeformMode_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_Framework2DTerrain_EFramework2DDeformMode_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(Z_Construct_UEnum_Framework2DTerrain_EFramework2DDeformMode_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_Framework2DTerrain_EFramework2DDeformMode_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_Framework2DTerrain_EFramework2DDeformMode()
	{
		if (!Z_Registration_Info_UEnum_EFramework2DDeformMode.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EFramework2DDeformMode.InnerSingleton, Z_Construct_UEnum_Framework2DTerrain_EFramework2DDeformMode_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_EFramework2DDeformMode.InnerSingleton;
	}
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_EFramework2DFacingSource;
	static UEnum* EFramework2DFacingSource_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_EFramework2DFacingSource.OuterSingleton)
		{
			Z_Registration_Info_UEnum_EFramework2DFacingSource.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_Framework2DTerrain_EFramework2DFacingSource, Z_Construct_UPackage__Script_Framework2DTerrain(), TEXT("EFramework2DFacingSource"));
		}
		return Z_Registration_Info_UEnum_EFramework2DFacingSource.OuterSingleton;
	}
	template<> FRAMEWORK2DTERRAIN_API UEnum* StaticEnum<EFramework2DFacingSource>()
	{
		return EFramework2DFacingSource_StaticEnum();
	}
	struct Z_Construct_UEnum_Framework2DTerrain_EFramework2DFacingSource_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_Framework2DTerrain_EFramework2DFacingSource_Statics::Enumerators[] = {
		{ "EFramework2DFacingSource::Movement", (int64)EFramework2DFacingSource::Movement },
		{ "EFramework2DFacingSource::ActorRotation", (int64)EFramework2DFacingSource::ActorRotation },
		{ "EFramework2DFacingSource::SpriteRotation", (int64)EFramework2DFacingSource::SpriteRotation },
		{ "EFramework2DFacingSource::Mouse", (int64)EFramework2DFacingSource::Mouse },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_Framework2DTerrain_EFramework2DFacingSource_Statics::Enum_MetaDataParams[] = {
		{ "ActorRotation.Comment", "// Hacia donde mira el actor (si lo giras 180 grados al cambiar de lado).\n" },
		{ "ActorRotation.DisplayName", "Rotacion del actor" },
		{ "ActorRotation.Name", "EFramework2DFacingSource::ActorRotation" },
		{ "ActorRotation.ToolTip", "Hacia donde mira el actor (si lo giras 180 grados al cambiar de lado)." },
		{ "BlueprintType", "true" },
		{ "Comment", "/** De donde sale \"delante\" del personaje. */" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainDeformerComponent.h" },
		{ "Mouse.Comment", "// Hacia el cursor del raton.\n" },
		{ "Mouse.DisplayName", "Raton" },
		{ "Mouse.Name", "EFramework2DFacingSource::Mouse" },
		{ "Mouse.ToolTip", "Hacia el cursor del raton." },
		{ "Movement.Comment", "// Hacia donde se movio por ultima vez: vale gires como gires el dibujo (rotacion, escala...).\n" },
		{ "Movement.DisplayName", "Ultimo movimiento" },
		{ "Movement.Name", "EFramework2DFacingSource::Movement" },
		{ "Movement.ToolTip", "Hacia donde se movio por ultima vez: vale gires como gires el dibujo (rotacion, escala...)." },
		{ "SpriteRotation.Comment", "// Hacia donde mira el sprite del Paper Character (girado 180 grados o con escala X negativa).\n" },
		{ "SpriteRotation.DisplayName", "Rotacion del sprite" },
		{ "SpriteRotation.Name", "EFramework2DFacingSource::SpriteRotation" },
		{ "SpriteRotation.ToolTip", "Hacia donde mira el sprite del Paper Character (girado 180 grados o con escala X negativa)." },
		{ "ToolTip", "De donde sale \"delante\" del personaje." },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_Framework2DTerrain_EFramework2DFacingSource_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_Framework2DTerrain,
		nullptr,
		"EFramework2DFacingSource",
		"EFramework2DFacingSource",
		Z_Construct_UEnum_Framework2DTerrain_EFramework2DFacingSource_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_Framework2DTerrain_EFramework2DFacingSource_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(Z_Construct_UEnum_Framework2DTerrain_EFramework2DFacingSource_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_Framework2DTerrain_EFramework2DFacingSource_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_Framework2DTerrain_EFramework2DFacingSource()
	{
		if (!Z_Registration_Info_UEnum_EFramework2DFacingSource.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EFramework2DFacingSource.InnerSingleton, Z_Construct_UEnum_Framework2DTerrain_EFramework2DFacingSource_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_EFramework2DFacingSource.InnerSingleton;
	}
	struct Z_Construct_UDelegateFunction_Framework2DTerrain_Framework2DOnTerrainDeformed__DelegateSignature_Statics
	{
		struct _Script_Framework2DTerrain_eventFramework2DOnTerrainDeformed_Parms
		{
			FFramework2DDigResult Result;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Result_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Result;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_Framework2DTerrain_Framework2DOnTerrainDeformed__DelegateSignature_Statics::NewProp_Result_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_Framework2DTerrain_Framework2DOnTerrainDeformed__DelegateSignature_Statics::NewProp_Result = { "Result", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_Framework2DTerrain_eventFramework2DOnTerrainDeformed_Parms, Result), Z_Construct_UScriptStruct_FFramework2DDigResult, METADATA_PARAMS(Z_Construct_UDelegateFunction_Framework2DTerrain_Framework2DOnTerrainDeformed__DelegateSignature_Statics::NewProp_Result_MetaData, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_Framework2DTerrain_Framework2DOnTerrainDeformed__DelegateSignature_Statics::NewProp_Result_MetaData)) }; // 3002348450
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_Framework2DTerrain_Framework2DOnTerrainDeformed__DelegateSignature_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_Framework2DTerrain_Framework2DOnTerrainDeformed__DelegateSignature_Statics::NewProp_Result,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_Framework2DTerrain_Framework2DOnTerrainDeformed__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Framework2DTerrainDeformerComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_Framework2DTerrain_Framework2DOnTerrainDeformed__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_Framework2DTerrain, nullptr, "Framework2DOnTerrainDeformed__DelegateSignature", nullptr, nullptr, sizeof(Z_Construct_UDelegateFunction_Framework2DTerrain_Framework2DOnTerrainDeformed__DelegateSignature_Statics::_Script_Framework2DTerrain_eventFramework2DOnTerrainDeformed_Parms), Z_Construct_UDelegateFunction_Framework2DTerrain_Framework2DOnTerrainDeformed__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_Framework2DTerrain_Framework2DOnTerrainDeformed__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_Framework2DTerrain_Framework2DOnTerrainDeformed__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_Framework2DTerrain_Framework2DOnTerrainDeformed__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_Framework2DTerrain_Framework2DOnTerrainDeformed__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_Framework2DTerrain_Framework2DOnTerrainDeformed__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	DEFINE_FUNCTION(UFramework2DTerrainDeformerComponent::execSetFacing)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_Direction);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetFacing(Z_Param_Direction);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFramework2DTerrainDeformerComponent::execGetFacing)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(float*)Z_Param__Result=P_THIS->GetFacing();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFramework2DTerrainDeformerComponent::execGetAimDirection)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FVector*)Z_Param__Result=P_THIS->GetAimDirection();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFramework2DTerrainDeformerComponent::execGetAimPoint)
	{
		P_GET_STRUCT_REF(FVector,Z_Param_Out_OutPoint);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->GetAimPoint(Z_Param_Out_OutPoint);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFramework2DTerrainDeformerComponent::execIsDeforming)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->IsDeforming();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFramework2DTerrainDeformerComponent::execStopDeforming)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->StopDeforming();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFramework2DTerrainDeformerComponent::execStartDeforming)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->StartDeforming();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFramework2DTerrainDeformerComponent::execDeformAt)
	{
		P_GET_STRUCT(FVector,Z_Param_WorldPosition);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FFramework2DDigResult*)Z_Param__Result=P_THIS->DeformAt(Z_Param_WorldPosition);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFramework2DTerrainDeformerComponent::execDeformNow)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FFramework2DDigResult*)Z_Param__Result=P_THIS->DeformNow();
		P_NATIVE_END;
	}
	void UFramework2DTerrainDeformerComponent::StaticRegisterNativesUFramework2DTerrainDeformerComponent()
	{
		UClass* Class = UFramework2DTerrainDeformerComponent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "DeformAt", &UFramework2DTerrainDeformerComponent::execDeformAt },
			{ "DeformNow", &UFramework2DTerrainDeformerComponent::execDeformNow },
			{ "GetAimDirection", &UFramework2DTerrainDeformerComponent::execGetAimDirection },
			{ "GetAimPoint", &UFramework2DTerrainDeformerComponent::execGetAimPoint },
			{ "GetFacing", &UFramework2DTerrainDeformerComponent::execGetFacing },
			{ "IsDeforming", &UFramework2DTerrainDeformerComponent::execIsDeforming },
			{ "SetFacing", &UFramework2DTerrainDeformerComponent::execSetFacing },
			{ "StartDeforming", &UFramework2DTerrainDeformerComponent::execStartDeforming },
			{ "StopDeforming", &UFramework2DTerrainDeformerComponent::execStopDeforming },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_DeformAt_Statics
	{
		struct Framework2DTerrainDeformerComponent_eventDeformAt_Parms
		{
			FVector WorldPosition;
			FFramework2DDigResult ReturnValue;
		};
		static const UECodeGen_Private::FStructPropertyParams NewProp_WorldPosition;
		static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_DeformAt_Statics::NewProp_WorldPosition = { "WorldPosition", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DTerrainDeformerComponent_eventDeformAt_Parms, WorldPosition), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_DeformAt_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DTerrainDeformerComponent_eventDeformAt_Parms, ReturnValue), Z_Construct_UScriptStruct_FFramework2DDigResult, METADATA_PARAMS(nullptr, 0) }; // 3002348450
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_DeformAt_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_DeformAt_Statics::NewProp_WorldPosition,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_DeformAt_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_DeformAt_Statics::Function_MetaDataParams[] = {
		{ "Category", "Framework2D|Deform" },
		{ "Comment", "/** Un golpe en un punto del mundo, con el modo, radio y dano de este componente. */" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainDeformerComponent.h" },
		{ "ToolTip", "Un golpe en un punto del mundo, con el modo, radio y dano de este componente." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_DeformAt_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFramework2DTerrainDeformerComponent, nullptr, "DeformAt", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_DeformAt_Statics::Framework2DTerrainDeformerComponent_eventDeformAt_Parms), Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_DeformAt_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_DeformAt_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04820401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_DeformAt_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_DeformAt_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_DeformAt()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_DeformAt_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_DeformNow_Statics
	{
		struct Framework2DTerrainDeformerComponent_eventDeformNow_Parms
		{
			FFramework2DDigResult ReturnValue;
		};
		static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_DeformNow_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DTerrainDeformerComponent_eventDeformNow_Parms, ReturnValue), Z_Construct_UScriptStruct_FFramework2DDigResult, METADATA_PARAMS(nullptr, 0) }; // 3002348450
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_DeformNow_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_DeformNow_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_DeformNow_Statics::Function_MetaDataParams[] = {
		{ "Category", "Framework2D|Deform" },
		{ "Comment", "/** Un golpe ahora mismo delante del dueno (no mira las teclas ni el limite de golpes por segundo). */" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainDeformerComponent.h" },
		{ "ToolTip", "Un golpe ahora mismo delante del dueno (no mira las teclas ni el limite de golpes por segundo)." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_DeformNow_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFramework2DTerrainDeformerComponent, nullptr, "DeformNow", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_DeformNow_Statics::Framework2DTerrainDeformerComponent_eventDeformNow_Parms), Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_DeformNow_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_DeformNow_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_DeformNow_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_DeformNow_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_DeformNow()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_DeformNow_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetAimDirection_Statics
	{
		struct Framework2DTerrainDeformerComponent_eventGetAimDirection_Parms
		{
			FVector ReturnValue;
		};
		static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetAimDirection_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DTerrainDeformerComponent_eventGetAimDirection_Parms, ReturnValue), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetAimDirection_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetAimDirection_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetAimDirection_Statics::Function_MetaDataParams[] = {
		{ "Category", "Framework2D|Deform" },
		{ "Comment", "/** Direccion (unitaria, en el plano del terreno) en la que se golpea. */" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainDeformerComponent.h" },
		{ "ToolTip", "Direccion (unitaria, en el plano del terreno) en la que se golpea." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetAimDirection_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFramework2DTerrainDeformerComponent, nullptr, "GetAimDirection", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetAimDirection_Statics::Framework2DTerrainDeformerComponent_eventGetAimDirection_Parms), Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetAimDirection_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetAimDirection_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54820401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetAimDirection_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetAimDirection_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetAimDirection()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetAimDirection_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetAimPoint_Statics
	{
		struct Framework2DTerrainDeformerComponent_eventGetAimPoint_Parms
		{
			FVector OutPoint;
			bool ReturnValue;
		};
		static const UECodeGen_Private::FStructPropertyParams NewProp_OutPoint;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetAimPoint_Statics::NewProp_OutPoint = { "OutPoint", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DTerrainDeformerComponent_eventGetAimPoint_Parms, OutPoint), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetAimPoint_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((Framework2DTerrainDeformerComponent_eventGetAimPoint_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetAimPoint_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(Framework2DTerrainDeformerComponent_eventGetAimPoint_Parms), &Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetAimPoint_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetAimPoint_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetAimPoint_Statics::NewProp_OutPoint,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetAimPoint_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetAimPoint_Statics::Function_MetaDataParams[] = {
		{ "Category", "Framework2D|Deform" },
		{ "Comment", "/** Donde caeria el golpe ahora. False si no hay terreno solido delante (con Buscar la pared). */" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainDeformerComponent.h" },
		{ "ToolTip", "Donde caeria el golpe ahora. False si no hay terreno solido delante (con Buscar la pared)." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetAimPoint_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFramework2DTerrainDeformerComponent, nullptr, "GetAimPoint", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetAimPoint_Statics::Framework2DTerrainDeformerComponent_eventGetAimPoint_Parms), Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetAimPoint_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetAimPoint_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetAimPoint_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetAimPoint_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetAimPoint()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetAimPoint_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetFacing_Statics
	{
		struct Framework2DTerrainDeformerComponent_eventGetFacing_Parms
		{
			float ReturnValue;
		};
		static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetFacing_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DTerrainDeformerComponent_eventGetFacing_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetFacing_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetFacing_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetFacing_Statics::Function_MetaDataParams[] = {
		{ "Category", "Framework2D|Deform" },
		{ "Comment", "/** Hacia donde mira: +1 = derecha del terreno, -1 = izquierda. */" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainDeformerComponent.h" },
		{ "ToolTip", "Hacia donde mira: +1 = derecha del terreno, -1 = izquierda." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetFacing_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFramework2DTerrainDeformerComponent, nullptr, "GetFacing", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetFacing_Statics::Framework2DTerrainDeformerComponent_eventGetFacing_Parms), Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetFacing_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetFacing_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetFacing_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetFacing_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetFacing()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetFacing_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_IsDeforming_Statics
	{
		struct Framework2DTerrainDeformerComponent_eventIsDeforming_Parms
		{
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_IsDeforming_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((Framework2DTerrainDeformerComponent_eventIsDeforming_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_IsDeforming_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(Framework2DTerrainDeformerComponent_eventIsDeforming_Parms), &Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_IsDeforming_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_IsDeforming_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_IsDeforming_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_IsDeforming_Statics::Function_MetaDataParams[] = {
		{ "Category", "Framework2D|Deform" },
		{ "Comment", "/** True mientras se pulsa una de las teclas o tras Start Deforming. */" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainDeformerComponent.h" },
		{ "ToolTip", "True mientras se pulsa una de las teclas o tras Start Deforming." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_IsDeforming_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFramework2DTerrainDeformerComponent, nullptr, "IsDeforming", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_IsDeforming_Statics::Framework2DTerrainDeformerComponent_eventIsDeforming_Parms), Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_IsDeforming_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_IsDeforming_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_IsDeforming_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_IsDeforming_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_IsDeforming()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_IsDeforming_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_SetFacing_Statics
	{
		struct Framework2DTerrainDeformerComponent_eventSetFacing_Parms
		{
			float Direction;
		};
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Direction;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_SetFacing_Statics::NewProp_Direction = { "Direction", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Framework2DTerrainDeformerComponent_eventSetFacing_Parms, Direction), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_SetFacing_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_SetFacing_Statics::NewProp_Direction,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_SetFacing_Statics::Function_MetaDataParams[] = {
		{ "Category", "Framework2D|Deform" },
		{ "Comment", "/**\n\x09 * Fija hacia donde mira (+1 derecha, -1 izquierda). Con \"Ultimo movimiento\" dura hasta la siguiente\n\x09 * entrada de movimiento horizontal; con las demas fuentes se vuelve a calcular en cada frame.\n\x09 */" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainDeformerComponent.h" },
		{ "ToolTip", "Fija hacia donde mira (+1 derecha, -1 izquierda). Con \"Ultimo movimiento\" dura hasta la siguiente\nentrada de movimiento horizontal; con las demas fuentes se vuelve a calcular en cada frame." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_SetFacing_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFramework2DTerrainDeformerComponent, nullptr, "SetFacing", nullptr, nullptr, sizeof(Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_SetFacing_Statics::Framework2DTerrainDeformerComponent_eventSetFacing_Parms), Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_SetFacing_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_SetFacing_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_SetFacing_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_SetFacing_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_SetFacing()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_SetFacing_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_StartDeforming_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_StartDeforming_Statics::Function_MetaDataParams[] = {
		{ "Category", "Framework2D|Deform" },
		{ "Comment", "/** Empieza a deformar como si se pulsara una de las teclas (para tu propia entrada). */" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainDeformerComponent.h" },
		{ "ToolTip", "Empieza a deformar como si se pulsara una de las teclas (para tu propia entrada)." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_StartDeforming_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFramework2DTerrainDeformerComponent, nullptr, "StartDeforming", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_StartDeforming_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_StartDeforming_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_StartDeforming()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_StartDeforming_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_StopDeforming_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_StopDeforming_Statics::Function_MetaDataParams[] = {
		{ "Category", "Framework2D|Deform" },
		{ "Comment", "/** Deja de deformar (el contrario de Start Deforming). */" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainDeformerComponent.h" },
		{ "ToolTip", "Deja de deformar (el contrario de Start Deforming)." },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_StopDeforming_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFramework2DTerrainDeformerComponent, nullptr, "StopDeforming", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_StopDeforming_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_StopDeforming_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_StopDeforming()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_StopDeforming_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UFramework2DTerrainDeformerComponent);
	UClass* Z_Construct_UClass_UFramework2DTerrainDeformerComponent_NoRegister()
	{
		return UFramework2DTerrainDeformerComponent::StaticClass();
	}
	struct Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bUseKeys_MetaData[];
#endif
		static void NewProp_bUseKeys_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseKeys;
		static const UECodeGen_Private::FStructPropertyParams NewProp_Keys_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Keys_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Keys;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bRepeatWhileHeld_MetaData[];
#endif
		static void NewProp_bRepeatWhileHeld_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bRepeatWhileHeld;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_HitsPerSecond_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_HitsPerSecond;
		static const UECodeGen_Private::FBytePropertyParams NewProp_Mode_Underlying;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Mode_MetaData[];
#endif
		static const UECodeGen_Private::FEnumPropertyParams NewProp_Mode;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Radius_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Radius;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Damage_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Damage;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Reach_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Reach;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bAimAtFirstSolid_MetaData[];
#endif
		static void NewProp_bAimAtFirstSolid_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bAimAtFirstSolid;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_HeightOffset_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_HeightOffset;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AimAngle_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_AimAngle;
		static const UECodeGen_Private::FBytePropertyParams NewProp_FacingSource_Underlying;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FacingSource_MetaData[];
#endif
		static const UECodeGen_Private::FEnumPropertyParams NewProp_FacingSource;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Terrain_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_Terrain;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bStoreInInventory_MetaData[];
#endif
		static void NewProp_bStoreInInventory_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bStoreInInventory;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bShowAim_MetaData[];
#endif
		static void NewProp_bShowAim_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bShowAim;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OnTerrainDeformed_MetaData[];
#endif
		static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnTerrainDeformed;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_Framework2DTerrain,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_DeformAt, "DeformAt" }, // 4158323790
		{ &Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_DeformNow, "DeformNow" }, // 1293461330
		{ &Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetAimDirection, "GetAimDirection" }, // 756271815
		{ &Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetAimPoint, "GetAimPoint" }, // 1843673082
		{ &Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_GetFacing, "GetFacing" }, // 246391215
		{ &Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_IsDeforming, "IsDeforming" }, // 3480464315
		{ &Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_SetFacing, "SetFacing" }, // 3572674347
		{ &Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_StartDeforming, "StartDeforming" }, // 3878523157
		{ &Z_Construct_UFunction_UFramework2DTerrainDeformerComponent_StopDeforming, "StopDeforming" }, // 2358604393
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Framework2D" },
		{ "Comment", "/**\n * UFramework2DTerrainDeformerComponent\n * =================================================================\n * Deforma el terreno delante de su dueno. Ponlo en tu personaje (o usa AFramework2DCharacter,\n * que ya lo lleva) y, sin configurar nada mas, el CLIC IZQUIERDO pica delante del jugador:\n *   - \"delante\" sale de hacia donde se movio por ultima vez (o de su rotacion, el sprite o el raton);\n *   - lanza un rayo hacia delante y golpea el primer terreno solido dentro del alcance;\n *   - mantener pulsado repite el golpe (Hits Per Second).\n * Lo roto puede ir al inventario de la varita (Framework2D Terraform) si el dueno la lleva.\n *\n * Las teclas se leen cada frame del Player Controller que lo controla (sin Input Mappings), solo\n * en el jugador local y solo si la partida recibe la entrada: con un menu \"solo interfaz\" abierto,\n * en pausa o tras Disable Input no pica, y al volver hace falta pulsar de nuevo. En enemigos o personajes\n * de la IA no hace nada por si solo. Para usar tu propia entrada, desactiva Use Keys y llama a\n * Start/Stop Deforming o a Deform Now.\n *\n * No se replica: cada maquina cambia su propia copia del terreno (un jugador o pantalla partida).\n */" },
		{ "DisplayName", "Framework2D Terrain Deformer" },
		{ "IncludePath", "Framework2DTerrainDeformerComponent.h" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainDeformerComponent.h" },
		{ "ToolTip", "UFramework2DTerrainDeformerComponent\n\nDeforma el terreno delante de su dueno. Ponlo en tu personaje (o usa AFramework2DCharacter,\nque ya lo lleva) y, sin configurar nada mas, el CLIC IZQUIERDO pica delante del jugador:\n  - \"delante\" sale de hacia donde se movio por ultima vez (o de su rotacion, el sprite o el raton);\n  - lanza un rayo hacia delante y golpea el primer terreno solido dentro del alcance;\n  - mantener pulsado repite el golpe (Hits Per Second).\nLo roto puede ir al inventario de la varita (Framework2D Terraform) si el dueno la lleva.\n\nLas teclas se leen cada frame del Player Controller que lo controla (sin Input Mappings), solo\nen el jugador local y solo si la partida recibe la entrada: con un menu \"solo interfaz\" abierto,\nen pausa o tras Disable Input no pica, y al volver hace falta pulsar de nuevo. En enemigos o personajes\nde la IA no hace nada por si solo. Para usar tu propia entrada, desactiva Use Keys y llama a\nStart/Stop Deforming o a Deform Now.\n\nNo se replica: cada maquina cambia su propia copia del terreno (un jugador o pantalla partida)." },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bUseKeys_MetaData[] = {
		{ "Category", "Framework2D|Deform|Input" },
		{ "Comment", "/** Deforma mientras pulses una de las Keys (solo el jugador local que controla al dueno y con la entrada de la partida activa). */" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainDeformerComponent.h" },
		{ "ToolTip", "Deforma mientras pulses una de las Keys (solo el jugador local que controla al dueno y con la entrada de la partida activa)." },
	};
#endif
	void Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bUseKeys_SetBit(void* Obj)
	{
		((UFramework2DTerrainDeformerComponent*)Obj)->bUseKeys = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bUseKeys = { "bUseKeys", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UFramework2DTerrainDeformerComponent), &Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bUseKeys_SetBit, METADATA_PARAMS(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bUseKeys_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bUseKeys_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_Keys_Inner = { "Keys", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FKey, METADATA_PARAMS(nullptr, 0) }; // 2615338182
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_Keys_MetaData[] = {
		{ "Category", "Framework2D|Deform|Input" },
		{ "Comment", "/** Teclas que deforman. Por defecto, clic izquierdo y gatillo derecho del mando. */" },
		{ "EditCondition", "bUseKeys" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainDeformerComponent.h" },
		{ "ToolTip", "Teclas que deforman. Por defecto, clic izquierdo y gatillo derecho del mando." },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_Keys = { "Keys", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTerrainDeformerComponent, Keys), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_Keys_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_Keys_MetaData)) }; // 2615338182
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bRepeatWhileHeld_MetaData[] = {
		{ "Category", "Framework2D|Deform|Input" },
		{ "Comment", "/** Mantener pulsado repite el golpe. Si no, un golpe por pulsacion. */" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainDeformerComponent.h" },
		{ "ToolTip", "Mantener pulsado repite el golpe. Si no, un golpe por pulsacion." },
	};
#endif
	void Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bRepeatWhileHeld_SetBit(void* Obj)
	{
		((UFramework2DTerrainDeformerComponent*)Obj)->bRepeatWhileHeld = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bRepeatWhileHeld = { "bRepeatWhileHeld", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UFramework2DTerrainDeformerComponent), &Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bRepeatWhileHeld_SetBit, METADATA_PARAMS(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bRepeatWhileHeld_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bRepeatWhileHeld_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_HitsPerSecond_MetaData[] = {
		{ "Category", "Framework2D|Deform|Input" },
		{ "ClampMin", "0.0" },
		{ "Comment", "/** Golpes por segundo como mucho (manteniendo pulsado o haciendo clic muy rapido). 0 = sin limite. */" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainDeformerComponent.h" },
		{ "ToolTip", "Golpes por segundo como mucho (manteniendo pulsado o haciendo clic muy rapido). 0 = sin limite." },
		{ "UIMax", "30.0" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_HitsPerSecond = { "HitsPerSecond", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTerrainDeformerComponent, HitsPerSecond), METADATA_PARAMS(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_HitsPerSecond_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_HitsPerSecond_MetaData)) };
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_Mode_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_Mode_MetaData[] = {
		{ "Category", "Framework2D|Deform" },
		{ "Comment", "/** Picar (con la dureza de cada material) o excavar al instante. */" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainDeformerComponent.h" },
		{ "ToolTip", "Picar (con la dureza de cada material) o excavar al instante." },
	};
#endif
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_Mode = { "Mode", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTerrainDeformerComponent, Mode), Z_Construct_UEnum_Framework2DTerrain_EFramework2DDeformMode, METADATA_PARAMS(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_Mode_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_Mode_MetaData)) }; // 777606622
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_Radius_MetaData[] = {
		{ "Category", "Framework2D|Deform" },
		{ "ClampMin", "1.0" },
		{ "Comment", "/** Radio (cm) del circulo que se rompe en cada golpe. */" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainDeformerComponent.h" },
		{ "ToolTip", "Radio (cm) del circulo que se rompe en cada golpe." },
		{ "UIMax", "500.0" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_Radius = { "Radius", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTerrainDeformerComponent, Radius), METADATA_PARAMS(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_Radius_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_Radius_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_Damage_MetaData[] = {
		{ "Category", "Framework2D|Deform" },
		{ "ClampMax", "255" },
		{ "ClampMin", "1" },
		{ "Comment", "/** Dano de cada golpe al picar. Se compara con la Hardness de cada material (Dirt 3, Stone 8...). */" },
		{ "EditCondition", "Mode == EFramework2DDeformMode::Mine" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainDeformerComponent.h" },
		{ "ToolTip", "Dano de cada golpe al picar. Se compara con la Hardness de cada material (Dirt 3, Stone 8...)." },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_Damage = { "Damage", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTerrainDeformerComponent, Damage), METADATA_PARAMS(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_Damage_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_Damage_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_Reach_MetaData[] = {
		{ "Category", "Framework2D|Deform" },
		{ "ClampMin", "0.0" },
		{ "Comment", "/** Hasta donde llega (cm) hacia delante desde el centro del dueno. */" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainDeformerComponent.h" },
		{ "ToolTip", "Hasta donde llega (cm) hacia delante desde el centro del dueno." },
		{ "UIMax", "2000.0" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_Reach = { "Reach", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTerrainDeformerComponent, Reach), METADATA_PARAMS(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_Reach_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_Reach_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bAimAtFirstSolid_MetaData[] = {
		{ "Category", "Framework2D|Deform" },
		{ "Comment", "/**\n\x09 * Buscar la pared: lanza un rayo hacia delante y golpea el primer terreno solido que encuentre\n\x09 * dentro del alcance (si no hay ninguno, no hace nada). Desactivado, golpea siempre a Reach.\n\x09 */" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainDeformerComponent.h" },
		{ "ToolTip", "Buscar la pared: lanza un rayo hacia delante y golpea el primer terreno solido que encuentre\ndentro del alcance (si no hay ninguno, no hace nada). Desactivado, golpea siempre a Reach." },
	};
#endif
	void Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bAimAtFirstSolid_SetBit(void* Obj)
	{
		((UFramework2DTerrainDeformerComponent*)Obj)->bAimAtFirstSolid = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bAimAtFirstSolid = { "bAimAtFirstSolid", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UFramework2DTerrainDeformerComponent), &Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bAimAtFirstSolid_SetBit, METADATA_PARAMS(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bAimAtFirstSolid_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bAimAtFirstSolid_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_HeightOffset_MetaData[] = {
		{ "Category", "Framework2D|Deform" },
		{ "Comment", "/** Altura (cm) desde la que sale el golpe, respecto al centro del dueno (negativo = hacia los pies). */" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainDeformerComponent.h" },
		{ "ToolTip", "Altura (cm) desde la que sale el golpe, respecto al centro del dueno (negativo = hacia los pies)." },
		{ "UIMax", "300.0" },
		{ "UIMin", "-300.0" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_HeightOffset = { "HeightOffset", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTerrainDeformerComponent, HeightOffset), METADATA_PARAMS(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_HeightOffset_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_HeightOffset_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_AimAngle_MetaData[] = {
		{ "Category", "Framework2D|Deform" },
		{ "ClampMax", "90.0" },
		{ "ClampMin", "-90.0" },
		{ "Comment", "/** Inclinacion (grados) del golpe: 0 = recto hacia delante, positivo = hacia arriba, negativo = hacia abajo. */" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainDeformerComponent.h" },
		{ "ToolTip", "Inclinacion (grados) del golpe: 0 = recto hacia delante, positivo = hacia arriba, negativo = hacia abajo." },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_AimAngle = { "AimAngle", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTerrainDeformerComponent, AimAngle), METADATA_PARAMS(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_AimAngle_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_AimAngle_MetaData)) };
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_FacingSource_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_FacingSource_MetaData[] = {
		{ "Category", "Framework2D|Deform" },
		{ "Comment", "/** De donde sale \"delante\". */" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainDeformerComponent.h" },
		{ "ToolTip", "De donde sale \"delante\"." },
	};
#endif
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_FacingSource = { "FacingSource", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTerrainDeformerComponent, FacingSource), Z_Construct_UEnum_Framework2DTerrain_EFramework2DFacingSource, METADATA_PARAMS(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_FacingSource_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_FacingSource_MetaData)) }; // 274741146
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_Terrain_MetaData[] = {
		{ "Category", "Framework2D|Deform|Other" },
		{ "Comment", "/** Terreno sobre el que actua. Vacio = todos los del nivel (golpea el mas cercano). */" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainDeformerComponent.h" },
		{ "ToolTip", "Terreno sobre el que actua. Vacio = todos los del nivel (golpea el mas cercano)." },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_Terrain = { "Terrain", nullptr, (EPropertyFlags)0x0014000000000005, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTerrainDeformerComponent, Terrain), Z_Construct_UClass_AFramework2DTerrainWorld_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_Terrain_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_Terrain_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bStoreInInventory_MetaData[] = {
		{ "Category", "Framework2D|Deform|Other" },
		{ "Comment", "/** Si el dueno lleva la varita (Framework2D Terraform), lo que se rompe va a su inventario. */" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainDeformerComponent.h" },
		{ "ToolTip", "Si el dueno lleva la varita (Framework2D Terraform), lo que se rompe va a su inventario." },
	};
#endif
	void Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bStoreInInventory_SetBit(void* Obj)
	{
		((UFramework2DTerrainDeformerComponent*)Obj)->bStoreInInventory = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bStoreInInventory = { "bStoreInInventory", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UFramework2DTerrainDeformerComponent), &Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bStoreInInventory_SetBit, METADATA_PARAMS(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bStoreInInventory_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bStoreInInventory_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bShowAim_MetaData[] = {
		{ "Category", "Framework2D|Deform|Other" },
		{ "Comment", "/** Dibuja (en desarrollo) el circulo donde caeria el golpe. Util para ajustar los parametros. */" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainDeformerComponent.h" },
		{ "ToolTip", "Dibuja (en desarrollo) el circulo donde caeria el golpe. Util para ajustar los parametros." },
	};
#endif
	void Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bShowAim_SetBit(void* Obj)
	{
		((UFramework2DTerrainDeformerComponent*)Obj)->bShowAim = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bShowAim = { "bShowAim", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UFramework2DTerrainDeformerComponent), &Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bShowAim_SetBit, METADATA_PARAMS(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bShowAim_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bShowAim_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_OnTerrainDeformed_MetaData[] = {
		{ "Category", "Framework2D|Deform" },
		{ "Comment", "/** Salta en cada golpe que alcanza terreno: el que encuentra la pared o el que dana o rompe algun pixel (aunque la dureza aun no lo rompa). Para sonido, particulas, animacion... */" },
		{ "ModuleRelativePath", "Public/Framework2DTerrainDeformerComponent.h" },
		{ "ToolTip", "Salta en cada golpe que alcanza terreno: el que encuentra la pared o el que dana o rompe algun pixel (aunque la dureza aun no lo rompa). Para sonido, particulas, animacion..." },
	};
#endif
	const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_OnTerrainDeformed = { "OnTerrainDeformed", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UFramework2DTerrainDeformerComponent, OnTerrainDeformed), Z_Construct_UDelegateFunction_Framework2DTerrain_Framework2DOnTerrainDeformed__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_OnTerrainDeformed_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_OnTerrainDeformed_MetaData)) }; // 2423551381
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bUseKeys,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_Keys_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_Keys,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bRepeatWhileHeld,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_HitsPerSecond,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_Mode_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_Mode,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_Radius,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_Damage,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_Reach,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bAimAtFirstSolid,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_HeightOffset,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_AimAngle,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_FacingSource_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_FacingSource,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_Terrain,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bStoreInInventory,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_bShowAim,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::NewProp_OnTerrainDeformed,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFramework2DTerrainDeformerComponent>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::ClassParams = {
		&UFramework2DTerrainDeformerComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UFramework2DTerrainDeformerComponent()
	{
		if (!Z_Registration_Info_UClass_UFramework2DTerrainDeformerComponent.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UFramework2DTerrainDeformerComponent.OuterSingleton, Z_Construct_UClass_UFramework2DTerrainDeformerComponent_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UFramework2DTerrainDeformerComponent.OuterSingleton;
	}
	template<> FRAMEWORK2DTERRAIN_API UClass* StaticClass<UFramework2DTerrainDeformerComponent>()
	{
		return UFramework2DTerrainDeformerComponent::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UFramework2DTerrainDeformerComponent);
	struct Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainDeformerComponent_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainDeformerComponent_h_Statics::EnumInfo[] = {
		{ EFramework2DDeformMode_StaticEnum, TEXT("EFramework2DDeformMode"), &Z_Registration_Info_UEnum_EFramework2DDeformMode, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 777606622U) },
		{ EFramework2DFacingSource_StaticEnum, TEXT("EFramework2DFacingSource"), &Z_Registration_Info_UEnum_EFramework2DFacingSource, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 274741146U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainDeformerComponent_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UFramework2DTerrainDeformerComponent, UFramework2DTerrainDeformerComponent::StaticClass, TEXT("UFramework2DTerrainDeformerComponent"), &Z_Registration_Info_UClass_UFramework2DTerrainDeformerComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UFramework2DTerrainDeformerComponent), 4255997038U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainDeformerComponent_h_3268401284(TEXT("/Script/Framework2DTerrain"),
		Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainDeformerComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainDeformerComponent_h_Statics::ClassInfo),
		nullptr, 0,
		Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainDeformerComponent_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Pixel2DFramework_Plugins_Framework2DTerrain_Source_Framework2DTerrain_Public_Framework2DTerrainDeformerComponent_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
