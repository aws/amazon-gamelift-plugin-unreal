// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UI/TestAnywhereMenuWidget.h"
#include "Styling/SlateColor.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTestAnywhereMenuWidget() {}
// Cross Module References
	GAMELIFTCLIENTSDK_API UClass* Z_Construct_UClass_UTestAnywhereMenuWidget();
	GAMELIFTCLIENTSDK_API UClass* Z_Construct_UClass_UTestAnywhereMenuWidget_NoRegister();
	SLATECORE_API UScriptStruct* Z_Construct_UScriptStruct_FSlateColor();
	UMG_API UClass* Z_Construct_UClass_UUserWidget();
	UPackage* Z_Construct_UPackage__Script_GameLiftClientSDK();
// End Cross Module References
	DEFINE_FUNCTION(UTestAnywhereMenuWidget::execConnectToServer)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->ConnectToServer();
		P_NATIVE_END;
	}
	void UTestAnywhereMenuWidget::StaticRegisterNativesUTestAnywhereMenuWidget()
	{
		UClass* Class = UTestAnywhereMenuWidget::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "ConnectToServer", &UTestAnywhereMenuWidget::execConnectToServer },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UTestAnywhereMenuWidget_ConnectToServer_Statics
	{
		struct TestAnywhereMenuWidget_eventConnectToServer_Parms
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
	void Z_Construct_UFunction_UTestAnywhereMenuWidget_ConnectToServer_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((TestAnywhereMenuWidget_eventConnectToServer_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UTestAnywhereMenuWidget_ConnectToServer_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(TestAnywhereMenuWidget_eventConnectToServer_Parms), &Z_Construct_UFunction_UTestAnywhereMenuWidget_ConnectToServer_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UTestAnywhereMenuWidget_ConnectToServer_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTestAnywhereMenuWidget_ConnectToServer_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UTestAnywhereMenuWidget_ConnectToServer_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/UI/TestAnywhereMenuWidget.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UTestAnywhereMenuWidget_ConnectToServer_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UTestAnywhereMenuWidget, nullptr, "ConnectToServer", nullptr, nullptr, sizeof(Z_Construct_UFunction_UTestAnywhereMenuWidget_ConnectToServer_Statics::TestAnywhereMenuWidget_eventConnectToServer_Parms), Z_Construct_UFunction_UTestAnywhereMenuWidget_ConnectToServer_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UTestAnywhereMenuWidget_ConnectToServer_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UTestAnywhereMenuWidget_ConnectToServer_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UTestAnywhereMenuWidget_ConnectToServer_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UTestAnywhereMenuWidget_ConnectToServer()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UTestAnywhereMenuWidget_ConnectToServer_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UTestAnywhereMenuWidget);
	UClass* Z_Construct_UClass_UTestAnywhereMenuWidget_NoRegister()
	{
		return UTestAnywhereMenuWidget::StaticClass();
	}
	struct Z_Construct_UClass_UTestAnywhereMenuWidget_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_LogOutputText_MetaData[];
#endif
		static const UECodeGen_Private::FTextPropertyParams NewProp_LogOutputText;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_LogOutputColor_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_LogOutputColor;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UTestAnywhereMenuWidget_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UUserWidget,
		(UObject* (*)())Z_Construct_UPackage__Script_GameLiftClientSDK,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UTestAnywhereMenuWidget_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UTestAnywhereMenuWidget_ConnectToServer, "ConnectToServer" }, // 2591442792
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTestAnywhereMenuWidget_Statics::Class_MetaDataParams[] = {
		{ "Comment", "// This is a sample game mode that you can use the test the GameLift Anywhere workflow in the plugin.\n// It simulates the process of talking to Amazon GameLift and retrieve info needed to connect to a running game server.\n" },
		{ "IncludePath", "UI/TestAnywhereMenuWidget.h" },
		{ "ModuleRelativePath", "Public/UI/TestAnywhereMenuWidget.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
		{ "ToolTip", "This is a sample game mode that you can use the test the GameLift Anywhere workflow in the plugin.\nIt simulates the process of talking to Amazon GameLift and retrieve info needed to connect to a running game server." },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTestAnywhereMenuWidget_Statics::NewProp_LogOutputText_MetaData[] = {
		{ "Category", "TestAnywhereMenuWidget" },
		{ "ModuleRelativePath", "Public/UI/TestAnywhereMenuWidget.h" },
	};
#endif
	const UECodeGen_Private::FTextPropertyParams Z_Construct_UClass_UTestAnywhereMenuWidget_Statics::NewProp_LogOutputText = { "LogOutputText", nullptr, (EPropertyFlags)0x0010000000020005, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UTestAnywhereMenuWidget, LogOutputText), METADATA_PARAMS(Z_Construct_UClass_UTestAnywhereMenuWidget_Statics::NewProp_LogOutputText_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UTestAnywhereMenuWidget_Statics::NewProp_LogOutputText_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTestAnywhereMenuWidget_Statics::NewProp_LogOutputColor_MetaData[] = {
		{ "Category", "TestAnywhereMenuWidget" },
		{ "ModuleRelativePath", "Public/UI/TestAnywhereMenuWidget.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UTestAnywhereMenuWidget_Statics::NewProp_LogOutputColor = { "LogOutputColor", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UTestAnywhereMenuWidget, LogOutputColor), Z_Construct_UScriptStruct_FSlateColor, METADATA_PARAMS(Z_Construct_UClass_UTestAnywhereMenuWidget_Statics::NewProp_LogOutputColor_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UTestAnywhereMenuWidget_Statics::NewProp_LogOutputColor_MetaData)) }; // 3007839000
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UTestAnywhereMenuWidget_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTestAnywhereMenuWidget_Statics::NewProp_LogOutputText,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTestAnywhereMenuWidget_Statics::NewProp_LogOutputColor,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UTestAnywhereMenuWidget_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UTestAnywhereMenuWidget>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UTestAnywhereMenuWidget_Statics::ClassParams = {
		&UTestAnywhereMenuWidget::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UTestAnywhereMenuWidget_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UTestAnywhereMenuWidget_Statics::PropPointers),
		0,
		0x00A010A0u,
		METADATA_PARAMS(Z_Construct_UClass_UTestAnywhereMenuWidget_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UTestAnywhereMenuWidget_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UTestAnywhereMenuWidget()
	{
		if (!Z_Registration_Info_UClass_UTestAnywhereMenuWidget.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UTestAnywhereMenuWidget.OuterSingleton, Z_Construct_UClass_UTestAnywhereMenuWidget_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UTestAnywhereMenuWidget.OuterSingleton;
	}
	template<> GAMELIFTCLIENTSDK_API UClass* StaticClass<UTestAnywhereMenuWidget>()
	{
		return UTestAnywhereMenuWidget::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UTestAnywhereMenuWidget);
	UTestAnywhereMenuWidget::~UTestAnywhereMenuWidget() {}
	struct Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftClient_Public_UI_TestAnywhereMenuWidget_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftClient_Public_UI_TestAnywhereMenuWidget_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UTestAnywhereMenuWidget, UTestAnywhereMenuWidget::StaticClass, TEXT("UTestAnywhereMenuWidget"), &Z_Registration_Info_UClass_UTestAnywhereMenuWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UTestAnywhereMenuWidget), 1841180684U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftClient_Public_UI_TestAnywhereMenuWidget_h_4009216797(TEXT("/Script/GameLiftClientSDK"),
		Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftClient_Public_UI_TestAnywhereMenuWidget_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftClient_Public_UI_TestAnywhereMenuWidget_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
