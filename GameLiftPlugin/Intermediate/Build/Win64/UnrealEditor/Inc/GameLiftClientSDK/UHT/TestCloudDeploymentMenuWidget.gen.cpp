// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UI/TestCloudDeploymentMenuWidget.h"
#include "../../Source/Runtime/Engine/Classes/Engine/TimerHandle.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTestCloudDeploymentMenuWidget() {}
// Cross Module References
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FTimerHandle();
	GAMELIFTCLIENTSDK_API UClass* Z_Construct_UClass_UTestCloudDeploymentMenuWidget();
	GAMELIFTCLIENTSDK_API UClass* Z_Construct_UClass_UTestCloudDeploymentMenuWidget_NoRegister();
	UMG_API UClass* Z_Construct_UClass_UUserWidget();
	UPackage* Z_Construct_UPackage__Script_GameLiftClientSDK();
	WEBBROWSERWIDGET_API UClass* Z_Construct_UClass_UWebBrowser_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(UTestCloudDeploymentMenuWidget::execGetLatestError)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=P_THIS->GetLatestError();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UTestCloudDeploymentMenuWidget::execOnConfirmSignupClicked)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->OnConfirmSignupClicked();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UTestCloudDeploymentMenuWidget::execOnSignupClicked)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->OnSignupClicked();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UTestCloudDeploymentMenuWidget::execOnLoginClicked)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->OnLoginClicked();
		P_NATIVE_END;
	}
	void UTestCloudDeploymentMenuWidget::StaticRegisterNativesUTestCloudDeploymentMenuWidget()
	{
		UClass* Class = UTestCloudDeploymentMenuWidget::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetLatestError", &UTestCloudDeploymentMenuWidget::execGetLatestError },
			{ "OnConfirmSignupClicked", &UTestCloudDeploymentMenuWidget::execOnConfirmSignupClicked },
			{ "OnLoginClicked", &UTestCloudDeploymentMenuWidget::execOnLoginClicked },
			{ "OnSignupClicked", &UTestCloudDeploymentMenuWidget::execOnSignupClicked },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_GetLatestError_Statics
	{
		struct TestCloudDeploymentMenuWidget_eventGetLatestError_Parms
		{
			FString ReturnValue;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_GetLatestError_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(TestCloudDeploymentMenuWidget_eventGetLatestError_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_GetLatestError_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_GetLatestError_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_GetLatestError_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/UI/TestCloudDeploymentMenuWidget.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_GetLatestError_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UTestCloudDeploymentMenuWidget, nullptr, "GetLatestError", nullptr, nullptr, sizeof(Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_GetLatestError_Statics::TestCloudDeploymentMenuWidget_eventGetLatestError_Parms), Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_GetLatestError_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_GetLatestError_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_GetLatestError_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_GetLatestError_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_GetLatestError()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_GetLatestError_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnConfirmSignupClicked_Statics
	{
		struct TestCloudDeploymentMenuWidget_eventOnConfirmSignupClicked_Parms
		{
			int32 ReturnValue;
		};
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnConfirmSignupClicked_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(TestCloudDeploymentMenuWidget_eventOnConfirmSignupClicked_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnConfirmSignupClicked_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnConfirmSignupClicked_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnConfirmSignupClicked_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/UI/TestCloudDeploymentMenuWidget.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnConfirmSignupClicked_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UTestCloudDeploymentMenuWidget, nullptr, "OnConfirmSignupClicked", nullptr, nullptr, sizeof(Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnConfirmSignupClicked_Statics::TestCloudDeploymentMenuWidget_eventOnConfirmSignupClicked_Parms), Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnConfirmSignupClicked_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnConfirmSignupClicked_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnConfirmSignupClicked_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnConfirmSignupClicked_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnConfirmSignupClicked()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnConfirmSignupClicked_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnLoginClicked_Statics
	{
		struct TestCloudDeploymentMenuWidget_eventOnLoginClicked_Parms
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
	void Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnLoginClicked_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((TestCloudDeploymentMenuWidget_eventOnLoginClicked_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnLoginClicked_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(TestCloudDeploymentMenuWidget_eventOnLoginClicked_Parms), &Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnLoginClicked_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnLoginClicked_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnLoginClicked_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnLoginClicked_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/UI/TestCloudDeploymentMenuWidget.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnLoginClicked_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UTestCloudDeploymentMenuWidget, nullptr, "OnLoginClicked", nullptr, nullptr, sizeof(Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnLoginClicked_Statics::TestCloudDeploymentMenuWidget_eventOnLoginClicked_Parms), Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnLoginClicked_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnLoginClicked_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnLoginClicked_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnLoginClicked_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnLoginClicked()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnLoginClicked_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnSignupClicked_Statics
	{
		struct TestCloudDeploymentMenuWidget_eventOnSignupClicked_Parms
		{
			int32 ReturnValue;
		};
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnSignupClicked_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(TestCloudDeploymentMenuWidget_eventOnSignupClicked_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnSignupClicked_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnSignupClicked_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnSignupClicked_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/UI/TestCloudDeploymentMenuWidget.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnSignupClicked_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UTestCloudDeploymentMenuWidget, nullptr, "OnSignupClicked", nullptr, nullptr, sizeof(Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnSignupClicked_Statics::TestCloudDeploymentMenuWidget_eventOnSignupClicked_Parms), Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnSignupClicked_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnSignupClicked_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnSignupClicked_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnSignupClicked_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnSignupClicked()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnSignupClicked_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UTestCloudDeploymentMenuWidget);
	UClass* Z_Construct_UClass_UTestCloudDeploymentMenuWidget_NoRegister()
	{
		return UTestCloudDeploymentMenuWidget::StaticClass();
	}
	struct Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ApiGatewayEndpoint_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_ApiGatewayEndpoint;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GetGameConnectionURI_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_GetGameConnectionURI;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GetGameConnectionRetryDelayMs_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_GetGameConnectionRetryDelayMs;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MatchmakingTimeoutInSecondsParameter_MetaData[];
#endif
		static const UECodeGen_Private::FUInt32PropertyParams NewProp_MatchmakingTimeoutInSecondsParameter;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_StartSessionURI_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_StartSessionURI;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SignupUrl_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_SignupUrl;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CallbackUrl_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_CallbackUrl;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Username_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_Username;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Password_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_Password;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VerificationCode_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_VerificationCode;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ConfigFilePath_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_ConfigFilePath;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_WebBrowser_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_WebBrowser;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PollGameConnectionHandle_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_PollGameConnectionHandle;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PollGameConnectionEndHandle_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_PollGameConnectionEndHandle;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UUserWidget,
		(UObject* (*)())Z_Construct_UPackage__Script_GameLiftClientSDK,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_GetLatestError, "GetLatestError" }, // 3012035097
		{ &Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnConfirmSignupClicked, "OnConfirmSignupClicked" }, // 409559058
		{ &Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnLoginClicked, "OnLoginClicked" }, // 1484223202
		{ &Z_Construct_UFunction_UTestCloudDeploymentMenuWidget_OnSignupClicked, "OnSignupClicked" }, // 1618219739
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "UI/TestCloudDeploymentMenuWidget.h" },
		{ "ModuleRelativePath", "Public/UI/TestCloudDeploymentMenuWidget.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_ApiGatewayEndpoint_MetaData[] = {
		{ "Category", "TestCloudDeploymentMenuWidget" },
		{ "ModuleRelativePath", "Public/UI/TestCloudDeploymentMenuWidget.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_ApiGatewayEndpoint = { "ApiGatewayEndpoint", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UTestCloudDeploymentMenuWidget, ApiGatewayEndpoint), METADATA_PARAMS(Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_ApiGatewayEndpoint_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_ApiGatewayEndpoint_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_GetGameConnectionURI_MetaData[] = {
		{ "Category", "TestCloudDeploymentMenuWidget" },
		{ "ModuleRelativePath", "Public/UI/TestCloudDeploymentMenuWidget.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_GetGameConnectionURI = { "GetGameConnectionURI", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UTestCloudDeploymentMenuWidget, GetGameConnectionURI), METADATA_PARAMS(Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_GetGameConnectionURI_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_GetGameConnectionURI_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_GetGameConnectionRetryDelayMs_MetaData[] = {
		{ "Category", "TestCloudDeploymentMenuWidget" },
		{ "ModuleRelativePath", "Public/UI/TestCloudDeploymentMenuWidget.h" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_GetGameConnectionRetryDelayMs = { "GetGameConnectionRetryDelayMs", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UTestCloudDeploymentMenuWidget, GetGameConnectionRetryDelayMs), METADATA_PARAMS(Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_GetGameConnectionRetryDelayMs_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_GetGameConnectionRetryDelayMs_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_MatchmakingTimeoutInSecondsParameter_MetaData[] = {
		{ "Category", "TestCloudDeploymentMenuWidget" },
		{ "ModuleRelativePath", "Public/UI/TestCloudDeploymentMenuWidget.h" },
	};
#endif
	const UECodeGen_Private::FUInt32PropertyParams Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_MatchmakingTimeoutInSecondsParameter = { "MatchmakingTimeoutInSecondsParameter", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::UInt32, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UTestCloudDeploymentMenuWidget, MatchmakingTimeoutInSecondsParameter), METADATA_PARAMS(Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_MatchmakingTimeoutInSecondsParameter_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_MatchmakingTimeoutInSecondsParameter_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_StartSessionURI_MetaData[] = {
		{ "Category", "TestCloudDeploymentMenuWidget" },
		{ "ModuleRelativePath", "Public/UI/TestCloudDeploymentMenuWidget.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_StartSessionURI = { "StartSessionURI", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UTestCloudDeploymentMenuWidget, StartSessionURI), METADATA_PARAMS(Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_StartSessionURI_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_StartSessionURI_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_SignupUrl_MetaData[] = {
		{ "Category", "TestCloudDeploymentMenuWidget" },
		{ "ModuleRelativePath", "Public/UI/TestCloudDeploymentMenuWidget.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_SignupUrl = { "SignupUrl", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UTestCloudDeploymentMenuWidget, SignupUrl), METADATA_PARAMS(Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_SignupUrl_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_SignupUrl_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_CallbackUrl_MetaData[] = {
		{ "Category", "TestCloudDeploymentMenuWidget" },
		{ "ModuleRelativePath", "Public/UI/TestCloudDeploymentMenuWidget.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_CallbackUrl = { "CallbackUrl", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UTestCloudDeploymentMenuWidget, CallbackUrl), METADATA_PARAMS(Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_CallbackUrl_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_CallbackUrl_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_Username_MetaData[] = {
		{ "Category", "TestCloudDeploymentMenuWidget" },
		{ "ModuleRelativePath", "Public/UI/TestCloudDeploymentMenuWidget.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_Username = { "Username", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UTestCloudDeploymentMenuWidget, Username), METADATA_PARAMS(Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_Username_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_Username_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_Password_MetaData[] = {
		{ "Category", "TestCloudDeploymentMenuWidget" },
		{ "ModuleRelativePath", "Public/UI/TestCloudDeploymentMenuWidget.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_Password = { "Password", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UTestCloudDeploymentMenuWidget, Password), METADATA_PARAMS(Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_Password_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_Password_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_VerificationCode_MetaData[] = {
		{ "Category", "TestCloudDeploymentMenuWidget" },
		{ "ModuleRelativePath", "Public/UI/TestCloudDeploymentMenuWidget.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_VerificationCode = { "VerificationCode", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UTestCloudDeploymentMenuWidget, VerificationCode), METADATA_PARAMS(Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_VerificationCode_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_VerificationCode_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_ConfigFilePath_MetaData[] = {
		{ "Category", "TestCloudDeploymentMenuWidget" },
		{ "ModuleRelativePath", "Public/UI/TestCloudDeploymentMenuWidget.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_ConfigFilePath = { "ConfigFilePath", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UTestCloudDeploymentMenuWidget, ConfigFilePath), METADATA_PARAMS(Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_ConfigFilePath_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_ConfigFilePath_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_WebBrowser_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UI/TestCloudDeploymentMenuWidget.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_WebBrowser = { "WebBrowser", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UTestCloudDeploymentMenuWidget, WebBrowser), Z_Construct_UClass_UWebBrowser_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_WebBrowser_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_WebBrowser_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_PollGameConnectionHandle_MetaData[] = {
		{ "ModuleRelativePath", "Public/UI/TestCloudDeploymentMenuWidget.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_PollGameConnectionHandle = { "PollGameConnectionHandle", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UTestCloudDeploymentMenuWidget, PollGameConnectionHandle), Z_Construct_UScriptStruct_FTimerHandle, METADATA_PARAMS(Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_PollGameConnectionHandle_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_PollGameConnectionHandle_MetaData)) }; // 3633724737
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_PollGameConnectionEndHandle_MetaData[] = {
		{ "ModuleRelativePath", "Public/UI/TestCloudDeploymentMenuWidget.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_PollGameConnectionEndHandle = { "PollGameConnectionEndHandle", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UTestCloudDeploymentMenuWidget, PollGameConnectionEndHandle), Z_Construct_UScriptStruct_FTimerHandle, METADATA_PARAMS(Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_PollGameConnectionEndHandle_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_PollGameConnectionEndHandle_MetaData)) }; // 3633724737
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_ApiGatewayEndpoint,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_GetGameConnectionURI,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_GetGameConnectionRetryDelayMs,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_MatchmakingTimeoutInSecondsParameter,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_StartSessionURI,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_SignupUrl,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_CallbackUrl,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_Username,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_Password,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_VerificationCode,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_ConfigFilePath,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_WebBrowser,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_PollGameConnectionHandle,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::NewProp_PollGameConnectionEndHandle,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UTestCloudDeploymentMenuWidget>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::ClassParams = {
		&UTestCloudDeploymentMenuWidget::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::PropPointers),
		0,
		0x00A010A0u,
		METADATA_PARAMS(Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UTestCloudDeploymentMenuWidget()
	{
		if (!Z_Registration_Info_UClass_UTestCloudDeploymentMenuWidget.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UTestCloudDeploymentMenuWidget.OuterSingleton, Z_Construct_UClass_UTestCloudDeploymentMenuWidget_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UTestCloudDeploymentMenuWidget.OuterSingleton;
	}
	template<> GAMELIFTCLIENTSDK_API UClass* StaticClass<UTestCloudDeploymentMenuWidget>()
	{
		return UTestCloudDeploymentMenuWidget::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UTestCloudDeploymentMenuWidget);
	UTestCloudDeploymentMenuWidget::~UTestCloudDeploymentMenuWidget() {}
	struct Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftClient_Public_UI_TestCloudDeploymentMenuWidget_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftClient_Public_UI_TestCloudDeploymentMenuWidget_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UTestCloudDeploymentMenuWidget, UTestCloudDeploymentMenuWidget::StaticClass, TEXT("UTestCloudDeploymentMenuWidget"), &Z_Registration_Info_UClass_UTestCloudDeploymentMenuWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UTestCloudDeploymentMenuWidget), 3551257020U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftClient_Public_UI_TestCloudDeploymentMenuWidget_h_1526601019(TEXT("/Script/GameLiftClientSDK"),
		Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftClient_Public_UI_TestCloudDeploymentMenuWidget_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftClient_Public_UI_TestCloudDeploymentMenuWidget_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
