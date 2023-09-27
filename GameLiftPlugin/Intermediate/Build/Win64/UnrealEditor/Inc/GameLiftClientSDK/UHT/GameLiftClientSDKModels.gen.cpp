// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameLiftClientSDKModels.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGameLiftClientSDKModels() {}
// Cross Module References
	GAMELIFTCLIENTSDK_API UEnum* Z_Construct_UEnum_GameLiftClientSDK_EGL_GameSessionStatus();
	GAMELIFTCLIENTSDK_API UEnum* Z_Construct_UEnum_GameLiftClientSDK_EGL_PlayerSessionStatus();
	GAMELIFTCLIENTSDK_API UScriptStruct* Z_Construct_UScriptStruct_FGL_GameSession();
	GAMELIFTCLIENTSDK_API UScriptStruct* Z_Construct_UScriptStruct_FGL_PlayerSession();
	UPackage* Z_Construct_UPackage__Script_GameLiftClientSDK();
// End Cross Module References
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_EGL_GameSessionStatus;
	static UEnum* EGL_GameSessionStatus_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_EGL_GameSessionStatus.OuterSingleton)
		{
			Z_Registration_Info_UEnum_EGL_GameSessionStatus.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_GameLiftClientSDK_EGL_GameSessionStatus, (UObject*)Z_Construct_UPackage__Script_GameLiftClientSDK(), TEXT("EGL_GameSessionStatus"));
		}
		return Z_Registration_Info_UEnum_EGL_GameSessionStatus.OuterSingleton;
	}
	template<> GAMELIFTCLIENTSDK_API UEnum* StaticEnum<EGL_GameSessionStatus>()
	{
		return EGL_GameSessionStatus_StaticEnum();
	}
	struct Z_Construct_UEnum_GameLiftClientSDK_EGL_GameSessionStatus_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_GameLiftClientSDK_EGL_GameSessionStatus_Statics::Enumerators[] = {
		{ "EGL_GameSessionStatus::NOT_SET", (int64)EGL_GameSessionStatus::NOT_SET },
		{ "EGL_GameSessionStatus::ACTIVE", (int64)EGL_GameSessionStatus::ACTIVE },
		{ "EGL_GameSessionStatus::ACTIVATING", (int64)EGL_GameSessionStatus::ACTIVATING },
		{ "EGL_GameSessionStatus::TERMINATED", (int64)EGL_GameSessionStatus::TERMINATED },
		{ "EGL_GameSessionStatus::TERMINATING", (int64)EGL_GameSessionStatus::TERMINATING },
		{ "EGL_GameSessionStatus::ERROR_", (int64)EGL_GameSessionStatus::ERROR_ },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_GameLiftClientSDK_EGL_GameSessionStatus_Statics::Enum_MetaDataParams[] = {
		{ "ACTIVATING.DisplayName", "Activating" },
		{ "ACTIVATING.Name", "EGL_GameSessionStatus::ACTIVATING" },
		{ "ACTIVE.DisplayName", "Active" },
		{ "ACTIVE.Name", "EGL_GameSessionStatus::ACTIVE" },
		{ "BlueprintType", "true" },
		{ "ERROR_.DisplayName", "Error" },
		{ "ERROR_.Name", "EGL_GameSessionStatus::ERROR_" },
		{ "ModuleRelativePath", "Public/GameLiftClientSDKModels.h" },
		{ "NOT_SET.DisplayName", "Not Set" },
		{ "NOT_SET.Name", "EGL_GameSessionStatus::NOT_SET" },
		{ "TERMINATED.DisplayName", "Terminated" },
		{ "TERMINATED.Name", "EGL_GameSessionStatus::TERMINATED" },
		{ "TERMINATING.DisplayName", "Terminating" },
		{ "TERMINATING.Name", "EGL_GameSessionStatus::TERMINATING" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_GameLiftClientSDK_EGL_GameSessionStatus_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_GameLiftClientSDK,
		nullptr,
		"EGL_GameSessionStatus",
		"EGL_GameSessionStatus",
		Z_Construct_UEnum_GameLiftClientSDK_EGL_GameSessionStatus_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_GameLiftClientSDK_EGL_GameSessionStatus_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(Z_Construct_UEnum_GameLiftClientSDK_EGL_GameSessionStatus_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_GameLiftClientSDK_EGL_GameSessionStatus_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_GameLiftClientSDK_EGL_GameSessionStatus()
	{
		if (!Z_Registration_Info_UEnum_EGL_GameSessionStatus.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EGL_GameSessionStatus.InnerSingleton, Z_Construct_UEnum_GameLiftClientSDK_EGL_GameSessionStatus_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_EGL_GameSessionStatus.InnerSingleton;
	}
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_EGL_PlayerSessionStatus;
	static UEnum* EGL_PlayerSessionStatus_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_EGL_PlayerSessionStatus.OuterSingleton)
		{
			Z_Registration_Info_UEnum_EGL_PlayerSessionStatus.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_GameLiftClientSDK_EGL_PlayerSessionStatus, (UObject*)Z_Construct_UPackage__Script_GameLiftClientSDK(), TEXT("EGL_PlayerSessionStatus"));
		}
		return Z_Registration_Info_UEnum_EGL_PlayerSessionStatus.OuterSingleton;
	}
	template<> GAMELIFTCLIENTSDK_API UEnum* StaticEnum<EGL_PlayerSessionStatus>()
	{
		return EGL_PlayerSessionStatus_StaticEnum();
	}
	struct Z_Construct_UEnum_GameLiftClientSDK_EGL_PlayerSessionStatus_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_GameLiftClientSDK_EGL_PlayerSessionStatus_Statics::Enumerators[] = {
		{ "EGL_PlayerSessionStatus::NOT_SET", (int64)EGL_PlayerSessionStatus::NOT_SET },
		{ "EGL_PlayerSessionStatus::RESERVED", (int64)EGL_PlayerSessionStatus::RESERVED },
		{ "EGL_PlayerSessionStatus::ACTIVE", (int64)EGL_PlayerSessionStatus::ACTIVE },
		{ "EGL_PlayerSessionStatus::COMPLETED", (int64)EGL_PlayerSessionStatus::COMPLETED },
		{ "EGL_PlayerSessionStatus::TIMEDOUT", (int64)EGL_PlayerSessionStatus::TIMEDOUT },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_GameLiftClientSDK_EGL_PlayerSessionStatus_Statics::Enum_MetaDataParams[] = {
		{ "ACTIVE.DisplayName", "Active" },
		{ "ACTIVE.Name", "EGL_PlayerSessionStatus::ACTIVE" },
		{ "BlueprintType", "true" },
		{ "COMPLETED.DisplayName", "Completed" },
		{ "COMPLETED.Name", "EGL_PlayerSessionStatus::COMPLETED" },
		{ "ModuleRelativePath", "Public/GameLiftClientSDKModels.h" },
		{ "NOT_SET.DisplayName", "Not Set" },
		{ "NOT_SET.Name", "EGL_PlayerSessionStatus::NOT_SET" },
		{ "RESERVED.DisplayName", "Reserved" },
		{ "RESERVED.Name", "EGL_PlayerSessionStatus::RESERVED" },
		{ "TIMEDOUT.DisplayName", "Timedout" },
		{ "TIMEDOUT.Name", "EGL_PlayerSessionStatus::TIMEDOUT" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_GameLiftClientSDK_EGL_PlayerSessionStatus_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_GameLiftClientSDK,
		nullptr,
		"EGL_PlayerSessionStatus",
		"EGL_PlayerSessionStatus",
		Z_Construct_UEnum_GameLiftClientSDK_EGL_PlayerSessionStatus_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_GameLiftClientSDK_EGL_PlayerSessionStatus_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(Z_Construct_UEnum_GameLiftClientSDK_EGL_PlayerSessionStatus_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_GameLiftClientSDK_EGL_PlayerSessionStatus_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_GameLiftClientSDK_EGL_PlayerSessionStatus()
	{
		if (!Z_Registration_Info_UEnum_EGL_PlayerSessionStatus.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EGL_PlayerSessionStatus.InnerSingleton, Z_Construct_UEnum_GameLiftClientSDK_EGL_PlayerSessionStatus_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_EGL_PlayerSessionStatus.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_GL_GameSession;
class UScriptStruct* FGL_GameSession::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_GL_GameSession.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_GL_GameSession.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FGL_GameSession, (UObject*)Z_Construct_UPackage__Script_GameLiftClientSDK(), TEXT("GL_GameSession"));
	}
	return Z_Registration_Info_UScriptStruct_GL_GameSession.OuterSingleton;
}
template<> GAMELIFTCLIENTSDK_API UScriptStruct* StaticStruct<FGL_GameSession>()
{
	return FGL_GameSession::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FGL_GameSession_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GameSessionId_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_GameSessionId;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FleetId_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_FleetId;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CurrentPlayerSessionCount_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_CurrentPlayerSessionCount;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MaximumPlayerSessionCount_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_MaximumPlayerSessionCount;
		static const UECodeGen_Private::FBytePropertyParams NewProp_Status_Underlying;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Status_MetaData[];
#endif
		static const UECodeGen_Private::FEnumPropertyParams NewProp_Status;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_IpAddress_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_IpAddress;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DnsName_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_DnsName;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Port_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_Port;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FGL_GameSession_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/GameLiftClientSDKModels.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FGL_GameSession>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_GameSessionId_MetaData[] = {
		{ "Category", "GameLiftClient" },
		{ "ModuleRelativePath", "Public/GameLiftClientSDKModels.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_GameSessionId = { "GameSessionId", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FGL_GameSession, GameSessionId), METADATA_PARAMS(Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_GameSessionId_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_GameSessionId_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_FleetId_MetaData[] = {
		{ "Category", "GameLiftClient" },
		{ "ModuleRelativePath", "Public/GameLiftClientSDKModels.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_FleetId = { "FleetId", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FGL_GameSession, FleetId), METADATA_PARAMS(Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_FleetId_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_FleetId_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_CurrentPlayerSessionCount_MetaData[] = {
		{ "Category", "GameLiftClient" },
		{ "ModuleRelativePath", "Public/GameLiftClientSDKModels.h" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_CurrentPlayerSessionCount = { "CurrentPlayerSessionCount", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FGL_GameSession, CurrentPlayerSessionCount), METADATA_PARAMS(Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_CurrentPlayerSessionCount_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_CurrentPlayerSessionCount_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_MaximumPlayerSessionCount_MetaData[] = {
		{ "Category", "GameLiftClient" },
		{ "ModuleRelativePath", "Public/GameLiftClientSDKModels.h" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_MaximumPlayerSessionCount = { "MaximumPlayerSessionCount", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FGL_GameSession, MaximumPlayerSessionCount), METADATA_PARAMS(Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_MaximumPlayerSessionCount_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_MaximumPlayerSessionCount_MetaData)) };
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_Status_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_Status_MetaData[] = {
		{ "Category", "GameLiftClient" },
		{ "ModuleRelativePath", "Public/GameLiftClientSDKModels.h" },
	};
#endif
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_Status = { "Status", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FGL_GameSession, Status), Z_Construct_UEnum_GameLiftClientSDK_EGL_GameSessionStatus, METADATA_PARAMS(Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_Status_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_Status_MetaData)) }; // 3746541899
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_IpAddress_MetaData[] = {
		{ "Category", "GameLiftClient" },
		{ "ModuleRelativePath", "Public/GameLiftClientSDKModels.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_IpAddress = { "IpAddress", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FGL_GameSession, IpAddress), METADATA_PARAMS(Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_IpAddress_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_IpAddress_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_DnsName_MetaData[] = {
		{ "Category", "GameLiftClient" },
		{ "ModuleRelativePath", "Public/GameLiftClientSDKModels.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_DnsName = { "DnsName", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FGL_GameSession, DnsName), METADATA_PARAMS(Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_DnsName_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_DnsName_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_Port_MetaData[] = {
		{ "Category", "GameLiftClient" },
		{ "ModuleRelativePath", "Public/GameLiftClientSDKModels.h" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_Port = { "Port", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FGL_GameSession, Port), METADATA_PARAMS(Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_Port_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_Port_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FGL_GameSession_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_GameSessionId,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_FleetId,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_CurrentPlayerSessionCount,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_MaximumPlayerSessionCount,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_Status_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_Status,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_IpAddress,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_DnsName,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewProp_Port,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FGL_GameSession_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_GameLiftClientSDK,
		nullptr,
		&NewStructOps,
		"GL_GameSession",
		sizeof(FGL_GameSession),
		alignof(FGL_GameSession),
		Z_Construct_UScriptStruct_FGL_GameSession_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGL_GameSession_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FGL_GameSession_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGL_GameSession_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FGL_GameSession()
	{
		if (!Z_Registration_Info_UScriptStruct_GL_GameSession.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_GL_GameSession.InnerSingleton, Z_Construct_UScriptStruct_FGL_GameSession_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_GL_GameSession.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_GL_PlayerSession;
class UScriptStruct* FGL_PlayerSession::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_GL_PlayerSession.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_GL_PlayerSession.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FGL_PlayerSession, (UObject*)Z_Construct_UPackage__Script_GameLiftClientSDK(), TEXT("GL_PlayerSession"));
	}
	return Z_Registration_Info_UScriptStruct_GL_PlayerSession.OuterSingleton;
}
template<> GAMELIFTCLIENTSDK_API UScriptStruct* StaticStruct<FGL_PlayerSession>()
{
	return FGL_PlayerSession::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FGL_PlayerSession_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DnsName_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_DnsName;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FleetArn_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_FleetArn;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FleetId_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_FleetId;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GameSessionId_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_GameSessionId;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_IpAddress_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_IpAddress;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PlayerData_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_PlayerData;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PlayerId_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_PlayerId;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PlayerSessionId_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_PlayerSessionId;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Port_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_Port;
		static const UECodeGen_Private::FBytePropertyParams NewProp_Status_Underlying;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Status_MetaData[];
#endif
		static const UECodeGen_Private::FEnumPropertyParams NewProp_Status;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/GameLiftClientSDKModels.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FGL_PlayerSession>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_DnsName_MetaData[] = {
		{ "Category", "GameLiftClient" },
		{ "ModuleRelativePath", "Public/GameLiftClientSDKModels.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_DnsName = { "DnsName", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FGL_PlayerSession, DnsName), METADATA_PARAMS(Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_DnsName_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_DnsName_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_FleetArn_MetaData[] = {
		{ "Category", "GameLiftClient" },
		{ "ModuleRelativePath", "Public/GameLiftClientSDKModels.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_FleetArn = { "FleetArn", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FGL_PlayerSession, FleetArn), METADATA_PARAMS(Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_FleetArn_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_FleetArn_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_FleetId_MetaData[] = {
		{ "Category", "GameLiftClient" },
		{ "ModuleRelativePath", "Public/GameLiftClientSDKModels.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_FleetId = { "FleetId", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FGL_PlayerSession, FleetId), METADATA_PARAMS(Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_FleetId_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_FleetId_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_GameSessionId_MetaData[] = {
		{ "Category", "GameLiftClient" },
		{ "ModuleRelativePath", "Public/GameLiftClientSDKModels.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_GameSessionId = { "GameSessionId", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FGL_PlayerSession, GameSessionId), METADATA_PARAMS(Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_GameSessionId_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_GameSessionId_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_IpAddress_MetaData[] = {
		{ "Category", "GameLiftClient" },
		{ "ModuleRelativePath", "Public/GameLiftClientSDKModels.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_IpAddress = { "IpAddress", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FGL_PlayerSession, IpAddress), METADATA_PARAMS(Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_IpAddress_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_IpAddress_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_PlayerData_MetaData[] = {
		{ "Category", "GameLiftClient" },
		{ "ModuleRelativePath", "Public/GameLiftClientSDKModels.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_PlayerData = { "PlayerData", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FGL_PlayerSession, PlayerData), METADATA_PARAMS(Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_PlayerData_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_PlayerData_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_PlayerId_MetaData[] = {
		{ "Category", "GameLiftClient" },
		{ "ModuleRelativePath", "Public/GameLiftClientSDKModels.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_PlayerId = { "PlayerId", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FGL_PlayerSession, PlayerId), METADATA_PARAMS(Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_PlayerId_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_PlayerId_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_PlayerSessionId_MetaData[] = {
		{ "Category", "GameLiftClient" },
		{ "ModuleRelativePath", "Public/GameLiftClientSDKModels.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_PlayerSessionId = { "PlayerSessionId", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FGL_PlayerSession, PlayerSessionId), METADATA_PARAMS(Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_PlayerSessionId_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_PlayerSessionId_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_Port_MetaData[] = {
		{ "Category", "GameLiftClient" },
		{ "ModuleRelativePath", "Public/GameLiftClientSDKModels.h" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_Port = { "Port", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FGL_PlayerSession, Port), METADATA_PARAMS(Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_Port_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_Port_MetaData)) };
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_Status_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_Status_MetaData[] = {
		{ "Category", "GameLiftClient" },
		{ "ModuleRelativePath", "Public/GameLiftClientSDKModels.h" },
	};
#endif
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_Status = { "Status", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FGL_PlayerSession, Status), Z_Construct_UEnum_GameLiftClientSDK_EGL_PlayerSessionStatus, METADATA_PARAMS(Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_Status_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_Status_MetaData)) }; // 3776001770
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_DnsName,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_FleetArn,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_FleetId,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_GameSessionId,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_IpAddress,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_PlayerData,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_PlayerId,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_PlayerSessionId,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_Port,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_Status_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewProp_Status,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_GameLiftClientSDK,
		nullptr,
		&NewStructOps,
		"GL_PlayerSession",
		sizeof(FGL_PlayerSession),
		alignof(FGL_PlayerSession),
		Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FGL_PlayerSession()
	{
		if (!Z_Registration_Info_UScriptStruct_GL_PlayerSession.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_GL_PlayerSession.InnerSingleton, Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_GL_PlayerSession.InnerSingleton;
	}
	struct Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftClient_Public_GameLiftClientSDKModels_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftClient_Public_GameLiftClientSDKModels_h_Statics::EnumInfo[] = {
		{ EGL_GameSessionStatus_StaticEnum, TEXT("EGL_GameSessionStatus"), &Z_Registration_Info_UEnum_EGL_GameSessionStatus, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3746541899U) },
		{ EGL_PlayerSessionStatus_StaticEnum, TEXT("EGL_PlayerSessionStatus"), &Z_Registration_Info_UEnum_EGL_PlayerSessionStatus, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3776001770U) },
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftClient_Public_GameLiftClientSDKModels_h_Statics::ScriptStructInfo[] = {
		{ FGL_GameSession::StaticStruct, Z_Construct_UScriptStruct_FGL_GameSession_Statics::NewStructOps, TEXT("GL_GameSession"), &Z_Registration_Info_UScriptStruct_GL_GameSession, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FGL_GameSession), 86523797U) },
		{ FGL_PlayerSession::StaticStruct, Z_Construct_UScriptStruct_FGL_PlayerSession_Statics::NewStructOps, TEXT("GL_PlayerSession"), &Z_Registration_Info_UScriptStruct_GL_PlayerSession, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FGL_PlayerSession), 2769174965U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftClient_Public_GameLiftClientSDKModels_h_3472394359(TEXT("/Script/GameLiftClientSDK"),
		nullptr, 0,
		Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftClient_Public_GameLiftClientSDKModels_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftClient_Public_GameLiftClientSDKModels_h_Statics::ScriptStructInfo),
		Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftClient_Public_GameLiftClientSDKModels_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftClient_Public_GameLiftClientSDKModels_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
