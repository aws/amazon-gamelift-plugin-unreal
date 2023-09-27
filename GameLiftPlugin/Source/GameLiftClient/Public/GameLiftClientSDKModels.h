// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"

#if WITH_GAMELIFT_CLIENT
#include <aws/gamelift/core/exports.h>
#endif

#include "GameLiftClientSDKModels.generated.h"

UENUM(BlueprintType)
enum class EGL_GameSessionStatus : uint8 {
	NOT_SET         UMETA(DisplayName = "Not Set"),
	ACTIVE          UMETA(DisplayName = "Active"),
	ACTIVATING      UMETA(DisplayName = "Activating"),
	TERMINATED      UMETA(DisplayName = "Terminated"),
	TERMINATING     UMETA(DisplayName = "Terminating"),
	ERROR_          UMETA(DisplayName = "Error"),
};

UENUM(BlueprintType)

enum class EGL_PlayerSessionStatus : uint8
{
	NOT_SET         UMETA(DisplayName = "Not Set"),
	RESERVED        UMETA(DisplayName = "Reserved"),
	ACTIVE          UMETA(DisplayName = "Active"),
	COMPLETED       UMETA(DisplayName = "Completed"),
	TIMEDOUT        UMETA(DisplayName = "Timedout")
};

USTRUCT(BlueprintType)
struct FGL_GameSession
{
	GENERATED_BODY()

	UPROPERTY(Category = "GameLiftClient", BlueprintReadOnly)
	FString GameSessionId;

	UPROPERTY(Category = "GameLiftClient", BlueprintReadOnly)
	FString FleetId;

	UPROPERTY(Category = "GameLiftClient", BlueprintReadOnly)
	int CurrentPlayerSessionCount = 0;

	UPROPERTY(Category = "GameLiftClient", BlueprintReadOnly)
	int MaximumPlayerSessionCount = 0;

	UPROPERTY(Category = "GameLiftClient", BlueprintReadOnly)
	EGL_GameSessionStatus Status = EGL_GameSessionStatus::NOT_SET;

	UPROPERTY(Category = "GameLiftClient", BlueprintReadOnly)
	FString IpAddress;

	UPROPERTY(Category = "GameLiftClient", BlueprintReadOnly)
	FString DnsName;

	UPROPERTY(Category = "GameLiftClient", BlueprintReadOnly)
	int Port = 0;

	FString ToString() const
	{
		return FString::Printf(TEXT("GameSessionId: %s,\nFleetId: %s,\nMaximumPlayerSesssionCount: %s,\nStatus: %s,\nIpAddress: %s,\nDnsName: %s,\nPort: %s\n"),
			*GameSessionId, *FleetId, *FString::FromInt(MaximumPlayerSessionCount), *StaticEnum<EGL_GameSessionStatus>()->GetValueAsString(Status), *IpAddress, *DnsName, *FString::FromInt(Port));
	}
};

USTRUCT(BlueprintType)
struct FGL_PlayerSession
{
	GENERATED_BODY()

	UPROPERTY(Category = "GameLiftClient", BlueprintReadOnly)
	FString DnsName;

	UPROPERTY(Category = "GameLiftClient", BlueprintReadOnly)
	FString FleetArn;

	UPROPERTY(Category = "GameLiftClient", BlueprintReadOnly)
	FString FleetId;

	UPROPERTY(Category = "GameLiftClient", BlueprintReadOnly)
	FString GameSessionId;

	UPROPERTY(Category = "GameLiftClient", BlueprintReadOnly)
	FString IpAddress;

	UPROPERTY(Category = "GameLiftClient", BlueprintReadOnly)
	FString PlayerData;

	UPROPERTY(Category = "GameLiftClient", BlueprintReadOnly)
	FString PlayerId;

	UPROPERTY(Category = "GameLiftClient", BlueprintReadOnly)
	FString PlayerSessionId;

	UPROPERTY(Category = "GameLiftClient", BlueprintReadOnly)
	int Port = 0;

	UPROPERTY(Category = "GameLiftClient", BlueprintReadOnly)
	EGL_PlayerSessionStatus Status = EGL_PlayerSessionStatus::NOT_SET;

	FString ToString() const
	{
		return FString::Printf(TEXT("DnsName: %s,\nFleetArn: %s,\nFleetId: %s,\nGameSessionId: %s,\nIpAddress: %s,\nPlayerData: %s,\nPlayerId: %s,\nPlayerSesssionId: %s,\nPort: %s,\nPlayerStatus: %s,\n"),
			*DnsName, *FleetArn, *FleetId, *GameSessionId, *IpAddress, *PlayerData, *PlayerId, *PlayerSessionId, *FString::FromInt(Port), *StaticEnum<EGL_PlayerSessionStatus>()->GetValueAsString(Status));
	}
};

namespace GL_Utils
{
#if WITH_GAMELIFT_CLIENT
	FGL_GameSession AwsGameSessionToUe(GAMELIFT_GAMESESSION_INSTANCE_HANDLE GameSession);
	FGL_GameSession AwsGameSessionToUe(const GAMELIFT_GAMESESSION_INFO& GameSessionInfo);
	FGL_PlayerSession AwsPlayerSessionToUe(GAMELIFT_PLAYERSESSION_INSTANCE_HANDLE PlayerSession);
#endif
} // namespace GL_Utils
