// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "UI/TestAnywhereMenuWidget.h"

#if WITH_GAMELIFT_CLIENT
#include "GameLiftClientSDK.h"
#include "GameLiftClientSDKModels.h"
#include <Kismet/GameplayStatics.h>
#endif

UTestAnywhereMenuWidget::UTestAnywhereMenuWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_GAMELIFT_CLIENT
	GameLiftSdkModule = &FModuleManager::LoadModuleChecked<FGameLiftClientSDKModule>(FName("GameLiftClientSDK"));
	check(GameLiftSdkModule);

	TryFetchCommandLineArguments();

	if (!InputCredentialsName.IsEmpty())
	{
		GameLiftSdkModule->ConfigureClient(InputCredentialsName);
	}
#endif
}

void UTestAnywhereMenuWidget::TryFetchCommandLineArguments()
{
	FString ArgumentFleetId;
	if (FParse::Value(FCommandLine::Get(), TEXT("glAnywhereClientFleetId="), ArgumentFleetId))
	{
		InputFleetId = ArgumentFleetId;
	}

	FString ArgumentCredentialsName;
	if (FParse::Value(FCommandLine::Get(), TEXT("glAnywhereClientCredentialsName="), ArgumentCredentialsName))
	{
		InputCredentialsName = ArgumentCredentialsName;
	}

	FString ArgumentCustomLocation;
	if (FParse::Value(FCommandLine::Get(), TEXT("glAnywhereClientCustomLocation="), ArgumentCustomLocation))
	{
		InputCustomLocation = ArgumentCustomLocation;
	}

	bool bArgumentFetched = !ArgumentCredentialsName.IsEmpty() && !ArgumentFleetId.IsEmpty() && !ArgumentCustomLocation.IsEmpty();

	if (bArgumentFetched)
	{
		SetOutputMessage(FString::Printf(TEXT("Successfully loaded launch arguments!\n\nCredentials:  %s\nFleet ID:  %s\nLocation:  %s"),
			*ArgumentCredentialsName, *ArgumentFleetId, *ArgumentCustomLocation));
	}
	else
	{
		FString EmptyString(TEXT("<empty>"));

		SetOutputMessage(FString::Printf(TEXT("Failed to load launch arguments!\n\nCredentials:  %s\nFleet ID:  %s\nLocation:  %s"),
			ArgumentCredentialsName.IsEmpty() ? *EmptyString : *ArgumentCredentialsName,
			ArgumentFleetId.IsEmpty() ? *EmptyString : *ArgumentFleetId,
			ArgumentCustomLocation.IsEmpty() ? *EmptyString : *ArgumentCustomLocation), true);
	}
}

bool UTestAnywhereMenuWidget::ConnectToServer()
{
#if WITH_GAMELIFT_CLIENT
	// Talk to Amazon GameLift to retrieve information to join your game server running on your Anywhere fleet.
	if (!ConnectToAmazonGameLift())
	{
		// If the client cannot create a player session, it will not connect to the running game server.
		return false;
	}

	const FString Options = "?PlayerSessionId=" + ServerPlayerSessionId + "?PlayerId=" + ServerPlayerId;

	// This will connect to the server map.
	FString LevelName = ServerIpAddress + ":" + ServerPort;
	UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelName), false, Options);

	FString DisplayMessage = FString::Printf(TEXT("Successfully connected to a game session and created a player session!\n\n"));
	DisplayMessage += FString::Printf(TEXT("Game Session ID:  %s\n"), *ServerGameSessionId);
	DisplayMessage += FString::Printf(TEXT("Player Session ID:  %s\n"), *ServerPlayerSessionId);
	DisplayMessage += FString::Printf(TEXT("Player ID:  %s\n"), *ServerPlayerId);
	DisplayMessage += FString::Printf(TEXT("Host:  %s:%s\n\n"), *ServerIpAddress, *ServerPort);
	DisplayMessage += FString::Printf(TEXT("Opening level: %s  (Options: %s)"), *LevelName, *Options);

	SetOutputMessage(DisplayMessage);

	return true;
#else
	return false;
#endif
}

bool UTestAnywhereMenuWidget::ConnectToAmazonGameLift()
{
	// Find or create a new game session on your Anywhere fleet.
	if (!FindGameSession())
	{
		if (!CreateGameSession(kMaximumPlayerSessionCount))
		{
			return false;
		}
		else
		{
			// A new game session will be in ACTIVATING state for a while. Wait 1 second to connect.
			FPlatformProcess::Sleep(1);
		}
	}

	// Create a new player session before joining the game server.
	if (!CreatePlayerSession())
	{
		return false;
	}

	return true;
}

bool UTestAnywhereMenuWidget::FindGameSession()
{
#if WITH_GAMELIFT_CLIENT
	check(GameLiftSdkModule);

	if (!ServerGameSessionId.IsEmpty())
	{
		SetOutputMessage(FString::Printf(TEXT("Game session already started: %s"), *ServerGameSessionId));
		return true;
	}

	FString ErrorMessage;
	FString StatusFilter = TEXT("ACTIVE");

	const TArray<FGL_GameSession>& GLGameSessionList = GameLiftSdkModule->DescribeGameSessions(InputFleetId, StatusFilter, ErrorMessage);

	if (!ErrorMessage.IsEmpty())
	{
		SetOutputMessage(ErrorMessage, true);
		return false;
	}

	for (const FGL_GameSession& GLGameSession: GLGameSessionList)
	{
		SetOutputMessage(FString::Printf(TEXT("Found game session: %s"), *(GLGameSession.ToString())));

		// Use this game session if it is available.
		if (GLGameSession.CurrentPlayerSessionCount < GLGameSession.MaximumPlayerSessionCount)
		{
			ServerGameSessionId = GLGameSession.GameSessionId;
			ServerIpAddress = GLGameSession.IpAddress;
			ServerPort = FString::FromInt(GLGameSession.Port);
			return true;
		}
	}
#endif

	return false;
}

bool UTestAnywhereMenuWidget::CreateGameSession(size_t InMaxPlayerCount)
{
#if WITH_GAMELIFT_CLIENT
	check(GameLiftSdkModule);

	if (!ServerGameSessionId.IsEmpty())
	{
		SetOutputMessage(FString::Printf(TEXT("Game session already started: %s"), *ServerGameSessionId));
		return true;
	}

	FString ErrorMessage;
	FGL_GameSession GLGameSession = GameLiftSdkModule->CreateGameSession(InMaxPlayerCount, InputFleetId, ErrorMessage, InputCustomLocation);

	if (!ErrorMessage.IsEmpty())
	{
		SetOutputMessage(ErrorMessage, true);
		return false;
	}

	SetOutputMessage(FString::Printf(TEXT("Successfully created new game session: %s"), *(GLGameSession.ToString())));

	ServerGameSessionId = GLGameSession.GameSessionId;
	ServerIpAddress = GLGameSession.IpAddress;
	ServerPort = FString::FromInt(GLGameSession.Port);

	return true;
#else
	return false;
#endif
}

bool UTestAnywhereMenuWidget::CreatePlayerSession()
{
#if WITH_GAMELIFT_CLIENT
	check(GameLiftSdkModule);

	if (ServerGameSessionId.IsEmpty())
	{
		SetOutputMessage("Game session is empty!", true);
		return false;
	}

	FString ErorrMessage;
	const FString PlayerData = TEXT("TestAnywhere_PlayerData");
	ServerPlayerId = TEXT("TestAnywhere_Player_") + FString::FromInt(FMath::RandRange(0, kMaximumPlayerSessionCount * 100));

	FGL_PlayerSession PlayerSession = GameLiftSdkModule->CreatePlayerSession(ServerGameSessionId, PlayerData, ServerPlayerId, ErorrMessage);

	if (!ErorrMessage.IsEmpty())
	{
		SetOutputMessage(ErorrMessage, true);
		return false;
	}

	SetOutputMessage(FString::Printf(TEXT("Successfully created player session: %s"), *(PlayerSession.ToString())));

	ServerPlayerSessionId = PlayerSession.PlayerSessionId;

	return true;
#else
	return false;
#endif
}

void UTestAnywhereMenuWidget::SetOutputMessage(const FString& InMessage, bool bIsError)
{
#if WITH_GAMELIFT_CLIENT
	LogOutputText = FText::FromString(!bIsError ? InMessage : FString("[Error]\n" + InMessage));
	LogOutputColor = !bIsError ? FLinearColor::White : FLinearColor::Red;
#endif
}
