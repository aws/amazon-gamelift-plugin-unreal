// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once 

#include "IGameLiftAnywhereHandler.h"

class GameLiftAnywhereHandler : public IGameLiftAnywhereHandler
{
public:
	GameLiftAnywhereHandler() = default;

	GameLiftAnywhereCreateLocationResult CreateCustomLocation(const FString& InRegion) override;

	GameLiftAnywhereCreateFleetResult CreateFleet(const FString& InFleetName, const FString& InCustomLocation) override;

	GameLiftAnywhereAddFleetLocationResult AddFleetLocation(const FString& InFleetId, const FString& InCustomLocation) override;

	GameLiftAnywhereDescribeFleetsResult DescribeAnywhereFleets() override;

	GameLiftAnywhereRegisterComputeResult RegisterCompute(const FString& InComputeName, const FString& InIPAddress, const FString& InFleetId, const FString& InCustomLocation) override;

	GameLiftAnywhereAuthTokenResult GenerateAuthToken(const FString& InFleetId, const FString& InComputeName) override;
};
