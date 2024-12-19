// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "IGameLiftContainersHandler.h"

class GameLiftContainersHandler : public IGameLiftContainersHandler
{
public:
	GameLiftContainersHandler() = default;

	void SetupContainersDirectory(const FString BuildZipSource, const FString GameExecutable, const FString ContainersDestinationDirectory) override;

	GameLiftECRCreateRepositoryResult CreateRepository(const FString& InRepositoryName) override;

	GameLiftECRDescribeRepositoriesResult DescribeRepositories() override;

	GameLiftECRListImagesResult ListImages(const FString& InRepositoryName) override;

	GameLiftContainersListCgdsResult ListCgds() override;

	GameLiftDescribeCgdResult DescribeCgd(const FString& InCgdName) override;

	GameLiftDescribeContainerFleetResult DescribeContainerFleet(const FString& GameName) override;
};