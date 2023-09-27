// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameLiftPlugin/Private/Settings/UGameLiftAnywhereStatus.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeUGameLiftAnywhereStatus() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FDateTime();
	GAMELIFTPLUGIN_API UClass* Z_Construct_UClass_UGameLiftAnywhereStatus();
	GAMELIFTPLUGIN_API UClass* Z_Construct_UClass_UGameLiftAnywhereStatus_NoRegister();
	UPackage* Z_Construct_UPackage__Script_GameLiftPlugin();
// End Cross Module References
	void UGameLiftAnywhereStatus::StaticRegisterNativesUGameLiftAnywhereStatus()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGameLiftAnywhereStatus);
	UClass* Z_Construct_UClass_UGameLiftAnywhereStatus_NoRegister()
	{
		return UGameLiftAnywhereStatus::StaticClass();
	}
	struct Z_Construct_UClass_UGameLiftAnywhereStatus_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DeployedRegion_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_DeployedRegion;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CustomLocation_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_CustomLocation;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FleetName_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_FleetName;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FleetId_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_FleetId;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_IsFleetDeployed_MetaData[];
#endif
		static void NewProp_IsFleetDeployed_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_IsFleetDeployed;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ComputeName_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_ComputeName;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ComputeIPAddress_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_ComputeIPAddress;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_IsComputeRegistered_MetaData[];
#endif
		static void NewProp_IsComputeRegistered_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_IsComputeRegistered;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AuthToken_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_AuthToken;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AuthTokenExpirationTime_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_AuthTokenExpirationTime;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PathToServerBuild_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_PathToServerBuild;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PathToClientBuild_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_PathToClientBuild;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_GameLiftPlugin,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "Settings/UGameLiftAnywhereStatus.h" },
		{ "ModuleRelativePath", "Private/Settings/UGameLiftAnywhereStatus.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_DeployedRegion_MetaData[] = {
		{ "Category", "Anywhere Status" },
		{ "ModuleRelativePath", "Private/Settings/UGameLiftAnywhereStatus.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_DeployedRegion = { "DeployedRegion", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UGameLiftAnywhereStatus, DeployedRegion), METADATA_PARAMS(Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_DeployedRegion_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_DeployedRegion_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_CustomLocation_MetaData[] = {
		{ "Category", "Anywhere Status" },
		{ "ModuleRelativePath", "Private/Settings/UGameLiftAnywhereStatus.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_CustomLocation = { "CustomLocation", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UGameLiftAnywhereStatus, CustomLocation), METADATA_PARAMS(Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_CustomLocation_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_CustomLocation_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_FleetName_MetaData[] = {
		{ "Category", "Anywhere Status" },
		{ "ModuleRelativePath", "Private/Settings/UGameLiftAnywhereStatus.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_FleetName = { "FleetName", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UGameLiftAnywhereStatus, FleetName), METADATA_PARAMS(Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_FleetName_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_FleetName_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_FleetId_MetaData[] = {
		{ "Category", "Anywhere Status" },
		{ "ModuleRelativePath", "Private/Settings/UGameLiftAnywhereStatus.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_FleetId = { "FleetId", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UGameLiftAnywhereStatus, FleetId), METADATA_PARAMS(Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_FleetId_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_FleetId_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_IsFleetDeployed_MetaData[] = {
		{ "Category", "Anywhere Status" },
		{ "ModuleRelativePath", "Private/Settings/UGameLiftAnywhereStatus.h" },
	};
#endif
	void Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_IsFleetDeployed_SetBit(void* Obj)
	{
		((UGameLiftAnywhereStatus*)Obj)->IsFleetDeployed = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_IsFleetDeployed = { "IsFleetDeployed", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(UGameLiftAnywhereStatus), &Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_IsFleetDeployed_SetBit, METADATA_PARAMS(Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_IsFleetDeployed_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_IsFleetDeployed_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_ComputeName_MetaData[] = {
		{ "Category", "Anywhere Status" },
		{ "ModuleRelativePath", "Private/Settings/UGameLiftAnywhereStatus.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_ComputeName = { "ComputeName", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UGameLiftAnywhereStatus, ComputeName), METADATA_PARAMS(Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_ComputeName_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_ComputeName_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_ComputeIPAddress_MetaData[] = {
		{ "Category", "Anywhere Status" },
		{ "ModuleRelativePath", "Private/Settings/UGameLiftAnywhereStatus.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_ComputeIPAddress = { "ComputeIPAddress", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UGameLiftAnywhereStatus, ComputeIPAddress), METADATA_PARAMS(Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_ComputeIPAddress_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_ComputeIPAddress_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_IsComputeRegistered_MetaData[] = {
		{ "Category", "Anywhere Status" },
		{ "ModuleRelativePath", "Private/Settings/UGameLiftAnywhereStatus.h" },
	};
#endif
	void Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_IsComputeRegistered_SetBit(void* Obj)
	{
		((UGameLiftAnywhereStatus*)Obj)->IsComputeRegistered = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_IsComputeRegistered = { "IsComputeRegistered", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(UGameLiftAnywhereStatus), &Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_IsComputeRegistered_SetBit, METADATA_PARAMS(Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_IsComputeRegistered_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_IsComputeRegistered_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_AuthToken_MetaData[] = {
		{ "Category", "Anywhere Status" },
		{ "ModuleRelativePath", "Private/Settings/UGameLiftAnywhereStatus.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_AuthToken = { "AuthToken", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UGameLiftAnywhereStatus, AuthToken), METADATA_PARAMS(Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_AuthToken_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_AuthToken_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_AuthTokenExpirationTime_MetaData[] = {
		{ "Category", "Anywhere Status" },
		{ "ModuleRelativePath", "Private/Settings/UGameLiftAnywhereStatus.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_AuthTokenExpirationTime = { "AuthTokenExpirationTime", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UGameLiftAnywhereStatus, AuthTokenExpirationTime), Z_Construct_UScriptStruct_FDateTime, METADATA_PARAMS(Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_AuthTokenExpirationTime_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_AuthTokenExpirationTime_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_PathToServerBuild_MetaData[] = {
		{ "Category", "Anywhere Status" },
		{ "ModuleRelativePath", "Private/Settings/UGameLiftAnywhereStatus.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_PathToServerBuild = { "PathToServerBuild", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UGameLiftAnywhereStatus, PathToServerBuild), METADATA_PARAMS(Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_PathToServerBuild_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_PathToServerBuild_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_PathToClientBuild_MetaData[] = {
		{ "Category", "Anywhere Status" },
		{ "ModuleRelativePath", "Private/Settings/UGameLiftAnywhereStatus.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_PathToClientBuild = { "PathToClientBuild", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UGameLiftAnywhereStatus, PathToClientBuild), METADATA_PARAMS(Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_PathToClientBuild_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_PathToClientBuild_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_DeployedRegion,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_CustomLocation,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_FleetName,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_FleetId,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_IsFleetDeployed,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_ComputeName,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_ComputeIPAddress,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_IsComputeRegistered,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_AuthToken,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_AuthTokenExpirationTime,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_PathToServerBuild,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::NewProp_PathToClientBuild,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGameLiftAnywhereStatus>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::ClassParams = {
		&UGameLiftAnywhereStatus::StaticClass,
		"EditorPerProjectUserSettings",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::PropPointers),
		0,
		0x000000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UGameLiftAnywhereStatus()
	{
		if (!Z_Registration_Info_UClass_UGameLiftAnywhereStatus.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGameLiftAnywhereStatus.OuterSingleton, Z_Construct_UClass_UGameLiftAnywhereStatus_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UGameLiftAnywhereStatus.OuterSingleton;
	}
	template<> GAMELIFTPLUGIN_API UClass* StaticClass<UGameLiftAnywhereStatus>()
	{
		return UGameLiftAnywhereStatus::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGameLiftAnywhereStatus);
	UGameLiftAnywhereStatus::~UGameLiftAnywhereStatus() {}
	struct Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftPlugin_Private_Settings_UGameLiftAnywhereStatus_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftPlugin_Private_Settings_UGameLiftAnywhereStatus_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UGameLiftAnywhereStatus, UGameLiftAnywhereStatus::StaticClass, TEXT("UGameLiftAnywhereStatus"), &Z_Registration_Info_UClass_UGameLiftAnywhereStatus, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGameLiftAnywhereStatus), 3544612933U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftPlugin_Private_Settings_UGameLiftAnywhereStatus_h_622986151(TEXT("/Script/GameLiftPlugin"),
		Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftPlugin_Private_Settings_UGameLiftAnywhereStatus_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftPlugin_Private_Settings_UGameLiftAnywhereStatus_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
