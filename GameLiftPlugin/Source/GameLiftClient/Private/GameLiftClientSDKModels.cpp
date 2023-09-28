// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GameLiftClientSDKModels.h"
#include "CoreMinimal.h"
#include "Serializer.h"

#if WITH_GAMELIFT_CLIENT

#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#endif

#include "aws/core/Aws.h"
#include "aws/core/utils/DateTime.h"
#include "aws/gamelift/model/GameSession.h"
#include "aws/gamelift/model/PlayerSession.h"

#if PLATFORM_WINDOWS
#include "Windows/HideWindowsPlatformTypes.h"
#endif

#endif

namespace GL_Utils
{
#if WITH_GAMELIFT_CLIENT
   FGL_GameSession AwsGameSessionToUe(const GAMELIFT_GAMESESSION_INFO& GameSessionInfo)
	{
		FGL_GameSession Result;

		if (GameSessionInfo.gameSessionId)
		{
			Result.GameSessionId = AWSSerializer::ASToFS(GameSessionInfo.gameSessionId);
		}

		if (GameSessionInfo.fleetId)
		{
			Result.FleetId = AWSSerializer::ASToFS(GameSessionInfo.fleetId);
		}

		if (GameSessionInfo.ipAddress)
		{
			Result.IpAddress = AWSSerializer::ASToFS(GameSessionInfo.ipAddress);
		}

		if (GameSessionInfo.dnsName)
		{
			Result.DnsName = AWSSerializer::ASToFS(GameSessionInfo.dnsName);
		}
		
		Result.Status = static_cast<EGL_GameSessionStatus>(GameSessionInfo.status);
		Result.CurrentPlayerSessionCount = GameSessionInfo.currentPlayerSessionCount;
		Result.MaximumPlayerSessionCount = GameSessionInfo.maximumPlayerSessionCount;
		Result.Port = GameSessionInfo.port;

		return Result;
	}

	FGL_GameSession AwsGameSessionToUe(GAMELIFT_GAMESESSION_INSTANCE_HANDLE GameSession)
	{
		FGL_GameSession Result;
		GAMELIFT_GAMESESSION_INFO GameSessionInfo;

		GameLiftGameSessionGetInfo(GameSession, &GameSessionInfo);

		return AwsGameSessionToUe(GameSessionInfo);
	}

	FGL_PlayerSession AwsPlayerSessionToUe(GAMELIFT_PLAYERSESSION_INSTANCE_HANDLE PlayerSession)
	{
		FGL_PlayerSession Result;

		GAMELIFT_PLAYERSESSION_INFO PlayerSessionInfo;

		GameLiftPlayerSessionGetInfo(PlayerSession, &PlayerSessionInfo);

		if (PlayerSessionInfo.dnsName)
		{
			Result.DnsName = AWSSerializer::ASToFS(PlayerSessionInfo.dnsName);
		}

		if (PlayerSessionInfo.fleetArn)
		{
			Result.FleetArn = AWSSerializer::ASToFS(PlayerSessionInfo.fleetArn);
		}

		if (PlayerSessionInfo.fleetId)
		{
			Result.FleetId = AWSSerializer::ASToFS(PlayerSessionInfo.fleetId);
		}

		if (PlayerSessionInfo.gameSessionId)
		{
			Result.GameSessionId = AWSSerializer::ASToFS(PlayerSessionInfo.gameSessionId);
		}

		if (PlayerSessionInfo.ipAddress)
		{
			Result.IpAddress = AWSSerializer::ASToFS(PlayerSessionInfo.ipAddress);
		}

		if (PlayerSessionInfo.playerData)
		{
			Result.PlayerData = AWSSerializer::ASToFS(PlayerSessionInfo.playerData);
		}

		if (PlayerSessionInfo.playerId)
		{
			Result.PlayerId = AWSSerializer::ASToFS(PlayerSessionInfo.playerId);
		}

		if (PlayerSessionInfo.playerSessionId)
		{
			Result.PlayerSessionId = AWSSerializer::ASToFS(PlayerSessionInfo.playerSessionId);
		}
		
		Result.Port = PlayerSessionInfo.port;
		Result.Status = static_cast<EGL_PlayerSessionStatus>(PlayerSessionInfo.status);

		return Result;
	}

	FGL_GameSession AwsGameSessionToUe(const Aws::GameLift::Model::GameSession& GameSessionIn)
	{
		FGL_GameSession Result;
		if (GameSessionIn.GameSessionIdHasBeenSet())
		{
			Result.GameSessionId = AWSSerializer::ASToFS(GameSessionIn.GetGameSessionId().c_str());
		}

		if (GameSessionIn.FleetIdHasBeenSet())
		{
			Result.FleetId = AWSSerializer::ASToFS(GameSessionIn.GetFleetId().c_str());
		}

		if (GameSessionIn.CurrentPlayerSessionCountHasBeenSet())
		{
			Result.CurrentPlayerSessionCount = GameSessionIn.GetCurrentPlayerSessionCount();
		}

		if (GameSessionIn.MaximumPlayerSessionCountHasBeenSet())
		{
			Result.MaximumPlayerSessionCount = GameSessionIn.GetMaximumPlayerSessionCount();
		}

		if (GameSessionIn.StatusHasBeenSet())
		{
			Result.Status = static_cast<EGL_GameSessionStatus>(GameSessionIn.GetStatus());
		}

		if (GameSessionIn.IpAddressHasBeenSet())
		{
			Result.IpAddress = AWSSerializer::ASToFS(GameSessionIn.GetIpAddress().c_str());
		}

		if (GameSessionIn.DnsNameHasBeenSet())
		{
			Result.DnsName = AWSSerializer::ASToFS(GameSessionIn.GetDnsName().c_str());
		}

		if (GameSessionIn.PortHasBeenSet())
		{
			Result.Port = GameSessionIn.GetPort();
		}

		return Result;
	}

	FGL_PlayerSession AwsPlayerSessionToUe(const Aws::GameLift::Model::PlayerSession& PlayerSessionIn)
	{
		FGL_PlayerSession Result;

		if (PlayerSessionIn.DnsNameHasBeenSet())
		{
			Result.DnsName = AWSSerializer::ASToFS(PlayerSessionIn.GetDnsName().c_str());
		}

		if (PlayerSessionIn.FleetArnHasBeenSet())
		{
			Result.FleetArn = AWSSerializer::ASToFS(PlayerSessionIn.GetFleetArn().c_str());
		}

		if (PlayerSessionIn.FleetIdHasBeenSet())
		{
			Result.FleetId = AWSSerializer::ASToFS(PlayerSessionIn.GetFleetId().c_str());
		}

		if (PlayerSessionIn.GameSessionIdHasBeenSet())
		{
			Result.GameSessionId = AWSSerializer::ASToFS(PlayerSessionIn.GetGameSessionId().c_str());
		}

		if (PlayerSessionIn.IpAddressHasBeenSet())
		{
			Result.IpAddress = AWSSerializer::ASToFS(PlayerSessionIn.GetIpAddress().c_str());
		}

		if (PlayerSessionIn.PlayerDataHasBeenSet())
		{
			Result.PlayerData = AWSSerializer::ASToFS(PlayerSessionIn.GetPlayerData().c_str());
		}

		if (PlayerSessionIn.PlayerIdHasBeenSet())
		{
			Result.PlayerId = AWSSerializer::ASToFS(PlayerSessionIn.GetPlayerId().c_str());
		}

		if (PlayerSessionIn.PlayerSessionIdHasBeenSet())
		{
			Result.PlayerSessionId = AWSSerializer::ASToFS(PlayerSessionIn.GetPlayerSessionId().c_str());
		}

		if (PlayerSessionIn.PortHasBeenSet())
		{
			Result.Port = PlayerSessionIn.GetPort();
		}

		if (PlayerSessionIn.StatusHasBeenSet())
		{
			Result.Status = static_cast<EGL_PlayerSessionStatus>(PlayerSessionIn.GetStatus());
		}

		return Result;
	}
#endif
};
