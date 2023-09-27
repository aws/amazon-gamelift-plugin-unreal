// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Styling/SlateColor.h" 
#include "TestAnywhereMenuWidget.generated.h"

class FGameLiftClientSDKModule;

// This is a sample game mode that you can use the test the GameLift Anywhere workflow in the plugin.
// It simulates the process of talking to Amazon GameLift and retrieve info needed to connect to a running game server.
UCLASS()
class UTestAnywhereMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UTestAnywhereMenuWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	bool ConnectToServer();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FText LogOutputText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FSlateColor LogOutputColor;

private:
	// This function will fetch command line arguments which are provided when launching the client build in the plugin's Anywhere page.
	void TryFetchCommandLineArguments();

	// Communicate with Amazon GameLift for game session (e.g. IP address) and player session information.
	// Return true if the client can create a player session and ready to connect to the running game server.
	bool ConnectToAmazonGameLift();

	// These functions simulate the process of finding, creating game session, and creating player session.
	bool FindGameSession();
	bool CreateGameSession(size_t InMaxPlayerCount);
	bool CreatePlayerSession();

	void SetOutputMessage(const FString& InMessage, bool bIsError = false);

private:
	FGameLiftClientSDKModule* GameLiftSdkModule = nullptr;
	
	// Test inputs
	FString InputFleetId;
	FString InputCredentialsName;
	FString InputCustomLocation;

	// Test outputs
	FString ServerIpAddress;
	FString ServerPort;
	FString ServerGameSessionId;
	FString ServerPlayerId;
	FString ServerPlayerSessionId;

	const size_t kMaximumPlayerSessionCount = 10;
};
