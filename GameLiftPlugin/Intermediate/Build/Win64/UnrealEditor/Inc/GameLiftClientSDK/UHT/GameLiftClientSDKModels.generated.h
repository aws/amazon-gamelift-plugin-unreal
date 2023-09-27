// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "GameLiftClientSDKModels.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef GAMELIFTCLIENTSDK_GameLiftClientSDKModels_generated_h
#error "GameLiftClientSDKModels.generated.h already included, missing '#pragma once' in GameLiftClientSDKModels.h"
#endif
#define GAMELIFTCLIENTSDK_GameLiftClientSDKModels_generated_h

#define FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftClient_Public_GameLiftClientSDKModels_h_38_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FGL_GameSession_Statics; \
	GAMELIFTCLIENTSDK_API static class UScriptStruct* StaticStruct();


template<> GAMELIFTCLIENTSDK_API UScriptStruct* StaticStruct<struct FGL_GameSession>();

#define FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftClient_Public_GameLiftClientSDKModels_h_74_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FGL_PlayerSession_Statics; \
	GAMELIFTCLIENTSDK_API static class UScriptStruct* StaticStruct();


template<> GAMELIFTCLIENTSDK_API UScriptStruct* StaticStruct<struct FGL_PlayerSession>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Test3rd_Plugins_GEDSGameLiftUEPlugin_GameLiftPlugin_Source_GameLiftClient_Public_GameLiftClientSDKModels_h


#define FOREACH_ENUM_EGL_GAMESESSIONSTATUS(op) \
	op(EGL_GameSessionStatus::NOT_SET) \
	op(EGL_GameSessionStatus::ACTIVE) \
	op(EGL_GameSessionStatus::ACTIVATING) \
	op(EGL_GameSessionStatus::TERMINATED) \
	op(EGL_GameSessionStatus::TERMINATING) \
	op(EGL_GameSessionStatus::ERROR_) 

enum class EGL_GameSessionStatus : uint8;
template<> struct TIsUEnumClass<EGL_GameSessionStatus> { enum { Value = true }; };
template<> GAMELIFTCLIENTSDK_API UEnum* StaticEnum<EGL_GameSessionStatus>();

#define FOREACH_ENUM_EGL_PLAYERSESSIONSTATUS(op) \
	op(EGL_PlayerSessionStatus::NOT_SET) \
	op(EGL_PlayerSessionStatus::RESERVED) \
	op(EGL_PlayerSessionStatus::ACTIVE) \
	op(EGL_PlayerSessionStatus::COMPLETED) \
	op(EGL_PlayerSessionStatus::TIMEDOUT) 

enum class EGL_PlayerSessionStatus : uint8;
template<> struct TIsUEnumClass<EGL_PlayerSessionStatus> { enum { Value = true }; };
template<> GAMELIFTCLIENTSDK_API UEnum* StaticEnum<EGL_PlayerSessionStatus>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
