// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "GameLiftClientSDK.h"
#include "Core.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h"
#include "HAL/UnrealMemory.h"
#include "Serializer.h"
#include "GameLiftClientLog.h"

#if WITH_GAMELIFT_CLIENT

#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#endif

#include "aws/core/Aws.h"
#include "aws/core/utils/logging/LogLevel.h"
#include "aws/core/utils/memory/MemorySystemInterface.h"

#if WITH_GAMELIFT_CLIENT
#include "aws/gamelift/GameLiftClient.h"
#include "aws/gamelift/model/DescribeGameSessionsRequest.h"
#include "aws/gamelift/model/CreateGameSessionRequest.h"
#include "aws/gamelift/model/CreatePlayerSessionRequest.h"
#include "aws/gamelift/model/CreatePlayerSessionsRequest.h"
#include "aws/gamelift/model/DescribePlayerSessionsRequest.h"
#include "aws/gamelift/core/awsclients/api_initializer.h"
#include "aws/gamelift/core/exports.h"
#endif

#if PLATFORM_WINDOWS
#include "Windows/HideWindowsPlatformTypes.h"
#endif

#endif

#define LOCTEXT_NAMESPACE "FGameLiftClientSDKModule"

void FGameLiftClientSDKModule::StartupModule()
{
#if WITH_GAMELIFT_CLIENT
	auto LogProxy = [](unsigned int InLevel, const char* InMessage, int InSize)
	{
		UE_LOG(GameLiftClientLog, Log, TEXT("********* %s"), UTF8_TO_TCHAR(InMessage));
	};

	GameLift::AwsApiInitializer::Initialize(LogProxy, this);
	GameLiftClientHandle = GameLiftClientInstanceCreate();
#endif
}

void FGameLiftClientSDKModule::ShutdownModule()
{
#if WITH_GAMELIFT_CLIENT
	GameLiftClientInstanceRelease(GameLiftClientHandle);
	GameLift::AwsApiInitializer::Shutdown();
#endif
}

bool FGameLiftClientSDKModule::ConfigureClient(const FString& CredentialsName)
{
#if WITH_GAMELIFT_CLIENT
	std::string StdCredentialsName = AWSSerializer::FSToStdS(CredentialsName);

	if (GameLiftClientHandle)
	{
		GameLiftClientInstanceRelease(GameLiftClientHandle);
		GameLiftClientHandle = nullptr;
	}

	GameLiftClientHandle = GameLiftClientInstanceCreateWithCredentials(StdCredentialsName.c_str());

	return GameLiftClientHandle != nullptr;

#endif
	return false;
}

#if WITH_GAMELIFT_CLIENT
namespace
{
	FuncErrorCallback ErrorCallback = [](DISPATCH_RECEIVER_HANDLE ErrorReceiver, GAMELIFT_ERROR_INFO* ErrorInfo) -> void
	{
		FString* Error = reinterpret_cast<FString*>(ErrorReceiver);
		*Error = ErrorInfo->errorMessage;
	};
}
#endif

FGL_GameSession FGameLiftClientSDKModule::CreateGameSession(size_t MaximumPlayerCount, const FString& FleetId, FString& ErrorMsg, const FString& CustomLocation, const FString& EndPoint)
{
	FGL_GameSession Result;
#if WITH_GAMELIFT_CLIENT

	std::string StdEndPoint = AWSSerializer::FSToStdS(EndPoint);
	if (!EndPoint.IsEmpty())
	{
		GameLiftClientOverrideEndpoint(GameLiftClientHandle, StdEndPoint.c_str());
	}

	GAMELIFT_GAMESESSION_CREATE_REQUEST CreateSessionRequest;
	
	std::string StdFleetId = AWSSerializer::FSToStdS(FleetId);
	CreateSessionRequest.fleetId = StdFleetId.c_str();
	CreateSessionRequest.maximumPlayerSessionCount = &MaximumPlayerCount;
	CreateSessionRequest.errorCb = ErrorCallback;
	CreateSessionRequest.errorReceiver = &ErrorMsg;

	std::string StdCustomLocation = AWSSerializer::FSToStdS(CustomLocation);
	if (!CustomLocation.IsEmpty())
	{
		CreateSessionRequest.location = StdCustomLocation.c_str();
	}

	auto GameSessionInstance = GameLiftGameSessionCreate(GameLiftClientHandle, &CreateSessionRequest);

	if (GameSessionInstance != nullptr)
	{
		Result = GL_Utils::AwsGameSessionToUe(GameSessionInstance);
		GameLiftGameSessionRelease(GameSessionInstance);
	}
#endif
	return Result;
}

TArray<FGL_GameSession> FGameLiftClientSDKModule::DescribeGameSessions(const FString& FleetId, const FString& StatusFilter, FString& ErrorMsg, const FString& EndPoint)
{
	TArray<FGL_GameSession> Result;
#if WITH_GAMELIFT_CLIENT

	std::string StdEndPoint = AWSSerializer::FSToStdS(EndPoint);
	if (!EndPoint.IsEmpty())
	{
		GameLiftClientOverrideEndpoint(GameLiftClientHandle, StdEndPoint.c_str());
	}

	GAMELIFT_DESCRIBE_GAMESESSIONS_REQUEST DescribeGameSessionsRequest;

	std::string StdString;
	if(!FleetId.IsEmpty())
	{
		StdString = AWSSerializer::FSToStdS(FleetId);
		DescribeGameSessionsRequest.fleetId = StdString.c_str();
	}

	std::string StdStatusFilter;
	if(!StatusFilter.IsEmpty())
	{
		StdStatusFilter = AWSSerializer::FSToStdS(StatusFilter);
		DescribeGameSessionsRequest.statusFilter = StdStatusFilter.c_str();
	}

	DescribeGameSessionsRequest.errorCb = ErrorCallback;
	DescribeGameSessionsRequest.errorReceiver = &ErrorMsg;

	FuncGameSessionInfoCallback ResultCallback = [](DISPATCH_RECEIVER_HANDLE DispatchReceiver, GAMELIFT_GAMESESSION_INFO* GameSessionInfo) -> bool
	{
		auto Result = reinterpret_cast<TArray<FGL_GameSession>*>(DispatchReceiver);
		Result->Add(GL_Utils::AwsGameSessionToUe(*GameSessionInfo));
		return false; // iterate over all sessions, do not filter out any of them
	};

	DescribeGameSessionsRequest.dispatchReceiver = &Result;
	DescribeGameSessionsRequest.resultCb = ResultCallback;

	GameLiftDescribeGameSessions(GameLiftClientHandle, &DescribeGameSessionsRequest);

#endif
	return Result;
}

FGL_PlayerSession FGameLiftClientSDKModule::CreatePlayerSession(const FString& GameSessionId, const FString& PlayerData, const FString& PlayerId, FString& ErrorMsg, const FString& EndPoint)
{
	FGL_PlayerSession Result;
#if WITH_GAMELIFT_CLIENT

	std::string StdEndPoint = AWSSerializer::FSToStdS(EndPoint);
	if (!EndPoint.IsEmpty())
	{
		GameLiftClientOverrideEndpoint(GameLiftClientHandle, StdEndPoint.c_str());
	}

	GAMELIFT_PLAYERSESSION_CREATE_REQUEST CreateSessionRequest;
	std::string StdGameSessionId = TCHAR_TO_ANSI(*GameSessionId); // Note: AWSSerializer::FSToStdS does not work due to encoding issue. The converted string is not expected.
	std::string StdPlayerId = AWSSerializer::FSToStdS(PlayerId);
	std::string StdPlayerData = AWSSerializer::FSToStdS(PlayerData);
	CreateSessionRequest.gameSessionId = StdGameSessionId.c_str();
	CreateSessionRequest.playerId = StdPlayerId.c_str();
	CreateSessionRequest.playerData = StdPlayerData.c_str();
	CreateSessionRequest.errorCb = ErrorCallback;
	CreateSessionRequest.errorReceiver = &ErrorMsg;

	auto PlayerSessionInstance = GameLiftPlayerSessionCreate(GameLiftClientHandle, &CreateSessionRequest);

	if (PlayerSessionInstance != nullptr)
	{
		Result = GL_Utils::AwsPlayerSessionToUe(PlayerSessionInstance);
		GameLiftPlayerSessionRelease(PlayerSessionInstance);
	}
#endif
	return Result;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGameLiftClientSDKModule, GameLiftClientSDK)
