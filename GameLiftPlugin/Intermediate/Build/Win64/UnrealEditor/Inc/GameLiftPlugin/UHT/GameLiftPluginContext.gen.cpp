// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameLiftPlugin/Public/GameLiftPluginContext.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGameLiftPluginContext() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	GAMELIFTPLUGIN_API UClass* Z_Construct_UClass_UGameLiftToolbarMenuContext();
	GAMELIFTPLUGIN_API UClass* Z_Construct_UClass_UGameLiftToolbarMenuContext_NoRegister();
	UPackage* Z_Construct_UPackage__Script_GameLiftPlugin();
// End Cross Module References
	void UGameLiftToolbarMenuContext::StaticRegisterNativesUGameLiftToolbarMenuContext()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGameLiftToolbarMenuContext);
	UClass* Z_Construct_UClass_UGameLiftToolbarMenuContext_NoRegister()
	{
		return UGameLiftToolbarMenuContext::StaticClass();
	}
	struct Z_Construct_UClass_UGameLiftToolbarMenuContext_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UGameLiftToolbarMenuContext_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_GameLiftPlugin,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameLiftToolbarMenuContext_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "GameLiftPluginContext.h" },
		{ "ModuleRelativePath", "Public/GameLiftPluginContext.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UGameLiftToolbarMenuContext_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGameLiftToolbarMenuContext>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UGameLiftToolbarMenuContext_Statics::ClassParams = {
		&UGameLiftToolbarMenuContext::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UGameLiftToolbarMenuContext_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UGameLiftToolbarMenuContext_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UGameLiftToolbarMenuContext()
	{
		if (!Z_Registration_Info_UClass_UGameLiftToolbarMenuContext.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGameLiftToolbarMenuContext.OuterSingleton, Z_Construct_UClass_UGameLiftToolbarMenuContext_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UGameLiftToolbarMenuContext.OuterSingleton;
	}
	template<> GAMELIFTPLUGIN_API UClass* StaticClass<UGameLiftToolbarMenuContext>()
	{
		return UGameLiftToolbarMenuContext::StaticClass();
	}
	UGameLiftToolbarMenuContext::UGameLiftToolbarMenuContext(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGameLiftToolbarMenuContext);
	UGameLiftToolbarMenuContext::~UGameLiftToolbarMenuContext() {}
	struct Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftPlugin_Public_GameLiftPluginContext_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftPlugin_Public_GameLiftPluginContext_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UGameLiftToolbarMenuContext, UGameLiftToolbarMenuContext::StaticClass, TEXT("UGameLiftToolbarMenuContext"), &Z_Registration_Info_UClass_UGameLiftToolbarMenuContext, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGameLiftToolbarMenuContext), 4139866687U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftPlugin_Public_GameLiftPluginContext_h_2319748417(TEXT("/Script/GameLiftPlugin"),
		Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftPlugin_Public_GameLiftPluginContext_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftPlugin_Public_GameLiftPluginContext_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
