// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once 

#include "Containers/UnrealString.h"
#include "Containers/Array.h"

struct GameLiftAnywhereResult
{
	bool bIsSuccessful;
	FString ErrorMessage;
};

struct GameLiftAnywhereCreateLocationResult : public GameLiftAnywhereResult
{
	FString LocationName;
};

struct GameLiftAnywhereCreateFleetResult : public GameLiftAnywhereResult
{
	FString FleetName;
	FString FleetId;
};

struct GameLiftAnywhereAddFleetLocationResult : public GameLiftAnywhereResult
{
	FString LocationName;
	FString FleetId;
};

struct GameLiftAnywhereDescribeFleetsResult : public GameLiftAnywhereResult
{
	struct FleetAttributes
	{
		FString FleetName;
		FString FleetId;
	};

	TArray<FleetAttributes> Fleets;
};

struct GameLiftAnywhereRegisterComputeResult : public GameLiftAnywhereResult
{
	FString ComputeName;
	FString LinkedFleetId;
	FString RegisteredIPAddress;
};

struct GameLiftAnywhereAuthTokenResult : public GameLiftAnywhereResult
{
	FString AuthToken;
	FDateTime ExpirationTime;
};

class IGameLiftAnywhereHandler
{
public:
	virtual ~IGameLiftAnywhereHandler() = default;

	virtual GameLiftAnywhereCreateLocationResult CreateCustomLocation(const FString& InRegion) = 0;

	virtual GameLiftAnywhereCreateFleetResult CreateFleet(const FString& InFleetName, const FString& InCustomLocation) = 0;

	virtual GameLiftAnywhereAddFleetLocationResult AddFleetLocation(const FString& InFleetId, const FString& InCustomLocation) = 0;

	virtual GameLiftAnywhereDescribeFleetsResult DescribeAnywhereFleets() = 0;

	virtual GameLiftAnywhereRegisterComputeResult RegisterCompute(const FString& InComputeName, const FString& InIPAddress, const FString& InFleetId, const FString& InCustomLocation) = 0;

	virtual GameLiftAnywhereAuthTokenResult GenerateAuthToken(const FString& InFleetId, const FString& InComputeName) = 0;
};
