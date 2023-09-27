// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameLiftPlugin/Private/Settings/UGameLiftSettings.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeUGameLiftSettings() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	GAMELIFTPLUGIN_API UClass* Z_Construct_UClass_UGameLiftSettings();
	GAMELIFTPLUGIN_API UClass* Z_Construct_UClass_UGameLiftSettings_NoRegister();
	UPackage* Z_Construct_UPackage__Script_GameLiftPlugin();
// End Cross Module References
	void UGameLiftSettings::StaticRegisterNativesUGameLiftSettings()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGameLiftSettings);
	UClass* Z_Construct_UClass_UGameLiftSettings_NoRegister()
	{
		return UGameLiftSettings::StaticClass();
	}
	struct Z_Construct_UClass_UGameLiftSettings_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ProfileName_MetaData[];
#endif
		static const UECodeGen_Private::FTextPropertyParams NewProp_ProfileName;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AwsRegion_MetaData[];
#endif
		static const UECodeGen_Private::FTextPropertyParams NewProp_AwsRegion;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_S3Bucket_MetaData[];
#endif
		static const UECodeGen_Private::FTextPropertyParams NewProp_S3Bucket;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BootstrapStatus_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_BootstrapStatus;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BootstrapError_MetaData[];
#endif
		static const UECodeGen_Private::FTextPropertyParams NewProp_BootstrapError;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UGameLiftSettings_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_GameLiftPlugin,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameLiftSettings_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "Settings/UGameLiftSettings.h" },
		{ "ModuleRelativePath", "Private/Settings/UGameLiftSettings.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameLiftSettings_Statics::NewProp_ProfileName_MetaData[] = {
		{ "Category", "AWS Credentials" },
		{ "ModuleRelativePath", "Private/Settings/UGameLiftSettings.h" },
	};
#endif
	const UECodeGen_Private::FTextPropertyParams Z_Construct_UClass_UGameLiftSettings_Statics::NewProp_ProfileName = { "ProfileName", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UGameLiftSettings, ProfileName), METADATA_PARAMS(Z_Construct_UClass_UGameLiftSettings_Statics::NewProp_ProfileName_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGameLiftSettings_Statics::NewProp_ProfileName_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameLiftSettings_Statics::NewProp_AwsRegion_MetaData[] = {
		{ "Category", "AWS Credentials" },
		{ "ModuleRelativePath", "Private/Settings/UGameLiftSettings.h" },
	};
#endif
	const UECodeGen_Private::FTextPropertyParams Z_Construct_UClass_UGameLiftSettings_Statics::NewProp_AwsRegion = { "AwsRegion", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UGameLiftSettings, AwsRegion), METADATA_PARAMS(Z_Construct_UClass_UGameLiftSettings_Statics::NewProp_AwsRegion_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGameLiftSettings_Statics::NewProp_AwsRegion_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameLiftSettings_Statics::NewProp_S3Bucket_MetaData[] = {
		{ "Category", "AWS Credentials" },
		{ "ModuleRelativePath", "Private/Settings/UGameLiftSettings.h" },
	};
#endif
	const UECodeGen_Private::FTextPropertyParams Z_Construct_UClass_UGameLiftSettings_Statics::NewProp_S3Bucket = { "S3Bucket", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UGameLiftSettings, S3Bucket), METADATA_PARAMS(Z_Construct_UClass_UGameLiftSettings_Statics::NewProp_S3Bucket_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGameLiftSettings_Statics::NewProp_S3Bucket_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameLiftSettings_Statics::NewProp_BootstrapStatus_MetaData[] = {
		{ "Category", "AWS Credentials" },
		{ "ModuleRelativePath", "Private/Settings/UGameLiftSettings.h" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_UGameLiftSettings_Statics::NewProp_BootstrapStatus = { "BootstrapStatus", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UGameLiftSettings, BootstrapStatus), METADATA_PARAMS(Z_Construct_UClass_UGameLiftSettings_Statics::NewProp_BootstrapStatus_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGameLiftSettings_Statics::NewProp_BootstrapStatus_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameLiftSettings_Statics::NewProp_BootstrapError_MetaData[] = {
		{ "Category", "AWS Credentials" },
		{ "ModuleRelativePath", "Private/Settings/UGameLiftSettings.h" },
	};
#endif
	const UECodeGen_Private::FTextPropertyParams Z_Construct_UClass_UGameLiftSettings_Statics::NewProp_BootstrapError = { "BootstrapError", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UGameLiftSettings, BootstrapError), METADATA_PARAMS(Z_Construct_UClass_UGameLiftSettings_Statics::NewProp_BootstrapError_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGameLiftSettings_Statics::NewProp_BootstrapError_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGameLiftSettings_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGameLiftSettings_Statics::NewProp_ProfileName,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGameLiftSettings_Statics::NewProp_AwsRegion,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGameLiftSettings_Statics::NewProp_S3Bucket,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGameLiftSettings_Statics::NewProp_BootstrapStatus,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGameLiftSettings_Statics::NewProp_BootstrapError,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UGameLiftSettings_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGameLiftSettings>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UGameLiftSettings_Statics::ClassParams = {
		&UGameLiftSettings::StaticClass,
		"EditorPerProjectUserSettings",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UGameLiftSettings_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UGameLiftSettings_Statics::PropPointers),
		0,
		0x000000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UGameLiftSettings_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UGameLiftSettings_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UGameLiftSettings()
	{
		if (!Z_Registration_Info_UClass_UGameLiftSettings.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGameLiftSettings.OuterSingleton, Z_Construct_UClass_UGameLiftSettings_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UGameLiftSettings.OuterSingleton;
	}
	template<> GAMELIFTPLUGIN_API UClass* StaticClass<UGameLiftSettings>()
	{
		return UGameLiftSettings::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGameLiftSettings);
	UGameLiftSettings::~UGameLiftSettings() {}
	struct Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftPlugin_Private_Settings_UGameLiftSettings_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftPlugin_Private_Settings_UGameLiftSettings_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UGameLiftSettings, UGameLiftSettings::StaticClass, TEXT("UGameLiftSettings"), &Z_Registration_Info_UClass_UGameLiftSettings, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGameLiftSettings), 2407002508U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftPlugin_Private_Settings_UGameLiftSettings_h_3456858861(TEXT("/Script/GameLiftPlugin"),
		Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftPlugin_Private_Settings_UGameLiftSettings_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftPlugin_Private_Settings_UGameLiftSettings_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
