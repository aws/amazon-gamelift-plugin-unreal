// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameLiftExports.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGameLiftExports() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	GAMELIFTCORE_API UClass* Z_Construct_UClass_UGameLiftExports();
	GAMELIFTCORE_API UClass* Z_Construct_UClass_UGameLiftExports_NoRegister();
	UPackage* Z_Construct_UPackage__Script_GameLiftCore();
// End Cross Module References
	DEFINE_FUNCTION(UGameLiftExports::execGetGameLiftPluginName)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=UGameLiftExports::GetGameLiftPluginName();
		P_NATIVE_END;
	}
	void UGameLiftExports::StaticRegisterNativesUGameLiftExports()
	{
		UClass* Class = UGameLiftExports::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetGameLiftPluginName", &UGameLiftExports::execGetGameLiftPluginName },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UGameLiftExports_GetGameLiftPluginName_Statics
	{
		struct GameLiftExports_eventGetGameLiftPluginName_Parms
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
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameLiftExports_GetGameLiftPluginName_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameLiftExports_eventGetGameLiftPluginName_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameLiftExports_GetGameLiftPluginName_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameLiftExports_GetGameLiftPluginName_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameLiftExports_GetGameLiftPluginName_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameLiftExports" },
		{ "ModuleRelativePath", "Public/GameLiftExports.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameLiftExports_GetGameLiftPluginName_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameLiftExports, nullptr, "GetGameLiftPluginName", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameLiftExports_GetGameLiftPluginName_Statics::GameLiftExports_eventGetGameLiftPluginName_Parms), Z_Construct_UFunction_UGameLiftExports_GetGameLiftPluginName_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameLiftExports_GetGameLiftPluginName_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameLiftExports_GetGameLiftPluginName_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameLiftExports_GetGameLiftPluginName_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameLiftExports_GetGameLiftPluginName()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameLiftExports_GetGameLiftPluginName_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGameLiftExports);
	UClass* Z_Construct_UClass_UGameLiftExports_NoRegister()
	{
		return UGameLiftExports::StaticClass();
	}
	struct Z_Construct_UClass_UGameLiftExports_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UGameLiftExports_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_GameLiftCore,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UGameLiftExports_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UGameLiftExports_GetGameLiftPluginName, "GetGameLiftPluginName" }, // 3878344262
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameLiftExports_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "GameLiftExports.h" },
		{ "ModuleRelativePath", "Public/GameLiftExports.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UGameLiftExports_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGameLiftExports>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UGameLiftExports_Statics::ClassParams = {
		&UGameLiftExports::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UGameLiftExports_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UGameLiftExports_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UGameLiftExports()
	{
		if (!Z_Registration_Info_UClass_UGameLiftExports.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGameLiftExports.OuterSingleton, Z_Construct_UClass_UGameLiftExports_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UGameLiftExports.OuterSingleton;
	}
	template<> GAMELIFTCORE_API UClass* StaticClass<UGameLiftExports>()
	{
		return UGameLiftExports::StaticClass();
	}
	UGameLiftExports::UGameLiftExports(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGameLiftExports);
	UGameLiftExports::~UGameLiftExports() {}
	struct Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftCore_Public_GameLiftExports_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftCore_Public_GameLiftExports_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UGameLiftExports, UGameLiftExports::StaticClass, TEXT("UGameLiftExports"), &Z_Registration_Info_UClass_UGameLiftExports, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGameLiftExports), 2271806747U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftCore_Public_GameLiftExports_h_1930163183(TEXT("/Script/GameLiftCore"),
		Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftCore_Public_GameLiftExports_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftCore_Public_GameLiftExports_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
