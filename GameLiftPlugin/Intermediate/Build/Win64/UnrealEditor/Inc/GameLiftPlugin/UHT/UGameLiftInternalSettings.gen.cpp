// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameLiftPlugin/Private/Settings/UGameLiftInternalSettings.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeUGameLiftInternalSettings() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FFilePath();
	GAMELIFTPLUGIN_API UClass* Z_Construct_UClass_UGameLiftInternalSettings();
	GAMELIFTPLUGIN_API UClass* Z_Construct_UClass_UGameLiftInternalSettings_NoRegister();
	UPackage* Z_Construct_UPackage__Script_GameLiftPlugin();
// End Cross Module References
	void UGameLiftInternalSettings::StaticRegisterNativesUGameLiftInternalSettings()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGameLiftInternalSettings);
	UClass* Z_Construct_UClass_UGameLiftInternalSettings_NoRegister()
	{
		return UGameLiftInternalSettings::StaticClass();
	}
	struct Z_Construct_UClass_UGameLiftInternalSettings_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DeployGameClientPath_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_DeployGameClientPath;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UGameLiftInternalSettings_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_GameLiftPlugin,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameLiftInternalSettings_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "Settings/UGameLiftInternalSettings.h" },
		{ "ModuleRelativePath", "Private/Settings/UGameLiftInternalSettings.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameLiftInternalSettings_Statics::NewProp_DeployGameClientPath_MetaData[] = {
		{ "Category", "Deploy Game Run" },
		{ "ModuleRelativePath", "Private/Settings/UGameLiftInternalSettings.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UGameLiftInternalSettings_Statics::NewProp_DeployGameClientPath = { "DeployGameClientPath", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UGameLiftInternalSettings, DeployGameClientPath), Z_Construct_UScriptStruct_FFilePath, METADATA_PARAMS(Z_Construct_UClass_UGameLiftInternalSettings_Statics::NewProp_DeployGameClientPath_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGameLiftInternalSettings_Statics::NewProp_DeployGameClientPath_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGameLiftInternalSettings_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGameLiftInternalSettings_Statics::NewProp_DeployGameClientPath,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UGameLiftInternalSettings_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGameLiftInternalSettings>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UGameLiftInternalSettings_Statics::ClassParams = {
		&UGameLiftInternalSettings::StaticClass,
		"EditorPerProjectUserSettings",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UGameLiftInternalSettings_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UGameLiftInternalSettings_Statics::PropPointers),
		0,
		0x000000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UGameLiftInternalSettings_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UGameLiftInternalSettings_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UGameLiftInternalSettings()
	{
		if (!Z_Registration_Info_UClass_UGameLiftInternalSettings.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGameLiftInternalSettings.OuterSingleton, Z_Construct_UClass_UGameLiftInternalSettings_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UGameLiftInternalSettings.OuterSingleton;
	}
	template<> GAMELIFTPLUGIN_API UClass* StaticClass<UGameLiftInternalSettings>()
	{
		return UGameLiftInternalSettings::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGameLiftInternalSettings);
	UGameLiftInternalSettings::~UGameLiftInternalSettings() {}
	struct Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftPlugin_Private_Settings_UGameLiftInternalSettings_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftPlugin_Private_Settings_UGameLiftInternalSettings_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UGameLiftInternalSettings, UGameLiftInternalSettings::StaticClass, TEXT("UGameLiftInternalSettings"), &Z_Registration_Info_UClass_UGameLiftInternalSettings, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGameLiftInternalSettings), 2403308266U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftPlugin_Private_Settings_UGameLiftInternalSettings_h_45240876(TEXT("/Script/GameLiftPlugin"),
		Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftPlugin_Private_Settings_UGameLiftInternalSettings_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftPlugin_Private_Settings_UGameLiftInternalSettings_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
