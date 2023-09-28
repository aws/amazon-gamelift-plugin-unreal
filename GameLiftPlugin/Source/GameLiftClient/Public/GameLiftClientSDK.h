// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Modules/ModuleManager.h"
#include "GameLiftClientSDKModels.h"

class FGameLiftClientSDKModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual bool ConfigureClient(const FString& CredentialsName);

	virtual FGL_GameSession CreateGameSession(size_t MaximumPlayerCount, const FString& FleetId, FString& ErrorMsg, const FString& CustomLocation = TEXT(""), const FString& EndPoint = TEXT(""));

	virtual TArray<FGL_GameSession> DescribeGameSessions(const FString& FleetId, const FString& StatusFilter, FString& ErrorMsg, const FString& EndPoint = TEXT(""));

	virtual FGL_PlayerSession CreatePlayerSession(const FString& GameSessionId, const FString& PlayerData, const FString& PlayerId, FString& ErrorMsg, const FString& EndPoint = TEXT(""));

private:
	void* GameLiftClientHandle;
};
