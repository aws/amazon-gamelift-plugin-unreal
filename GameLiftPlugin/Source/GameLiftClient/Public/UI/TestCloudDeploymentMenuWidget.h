// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Http.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/EngineTypes.h"
#include "TestCloudDeploymentMenuWidget.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(TestCloudDeployment, Log, All);

enum class ServerHttpStatusCode : int32
{
	// start_game API codes
	
	// 202 (Accepted) if the matchmaking request is accepted and is now being processed
	StartGame_Accepted = 202,
	// 409 (Conflict) if the another matchmaking request is in progress
	StartGame_Conflict = 409,
	// 500 (Internal Error) if error occurred when processing the matchmaking request
	StartGame_InternalError = 500,

	// get_game_connection API codes

	// 200 (OK) if the game connection is ready, along with server info: "IpAddress", "Port", "DnsName", "PlayerSessionId", "PlayerId"
	GetGameConnection_Ready = 200,
	// 204 (No Content) if the requested game is still in progress of matchmaking
	GetGameConnection_MatchmakingInProgress = 204,
	// 404 (Not Found) if no game has been started by the player, or if all started game were expired
	GetGameConnection_NotFound = 404,
	// 500 (Internal Error) if errors occurred during matchmaking or placement
	GetGameConnection_InternalError = 500,
	// 501 (No Server Deployed) if no server has been delpoyed
	GetGameConnection_NoServerError = 501,
}; 

class UWebBrowser;

/**
 * 
 */
UCLASS()
class UTestCloudDeploymentMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UTestCloudDeploymentMenuWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	bool OnLoginClicked();

	UFUNCTION(BlueprintCallable)
	int OnSignupClicked();

	UFUNCTION(BlueprintCallable)
	int OnConfirmSignupClicked();

	UFUNCTION(BlueprintCallable)
	FString GetLatestError();

	UPROPERTY(EditAnywhere)
	FString ApiGatewayEndpoint;

	UPROPERTY(EditAnywhere)
	FString GetGameConnectionURI;

	UPROPERTY(EditAnywhere)
	int GetGameConnectionRetryDelayMs;
	
	UPROPERTY(EditAnywhere)
	uint32 MatchmakingTimeoutInSecondsParameter;

	UPROPERTY(EditAnywhere)
	FString StartSessionURI;

	UPROPERTY(EditAnywhere)
	FString SignupUrl;

	UPROPERTY(EditAnywhere)
	FString CallbackUrl;

	UPROPERTY(BlueprintReadWrite)
	FString Username;

	UPROPERTY(BlueprintReadWrite)
	FString Password;

	UPROPERTY(BlueprintReadWrite)
	FString VerificationCode;

	UPROPERTY(EditAnywhere)
	FString ConfigFilePath;

	UPROPERTY()
	UWebBrowser* WebBrowser;

	UPROPERTY()
	FTimerHandle PollGameConnectionHandle;

	UPROPERTY()
	FTimerHandle PollGameConnectionEndHandle;

protected:
	virtual void NativeConstruct() override;

private:
	void PollGameConnection();
	void PollGameConnectionEnd();

	FHttpModule* Http;

	int AuthAndGetToken();

	void EstablishGameConnection();
	void OnGetGameConnectionResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void StartGame(FString idt);
	void OnStartGameResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	bool OpenLevel(const FString& IpAddress, const FString& Port, const FString& Options);

	FString IdToken;

	bool MatchmakingInProgress;
	TAtomic<bool> MatchmakingIsTimedOut;
	FString LatestError;
};
