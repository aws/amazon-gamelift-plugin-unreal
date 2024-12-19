// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

struct GameLiftECRResult
{
	bool bIsSuccessful;
	FString ErrorMessage;
};

struct GameLiftContainersResult
{
	bool bIsSuccessful;
	FString ErrorMessage;
};

struct GameLiftECRCreateRepositoryResult : public GameLiftECRResult
{
	FString RepositoryName;
	FString RepoUri;
};

struct GameLiftDescribeCgdResult : public GameLiftContainersResult
{
	FString CgdVersion;
	FString CgdStatus;
};

struct GameLiftDescribeContainerFleetResult : public GameLiftContainersResult
{
	FString FleetId;
	FString FleetStatus;
	FString FleetType;
	FString InstanceType;
};

struct GameLiftContainersCreateCgdResult : public GameLiftContainersResult
{
	FString CgdName;
};

struct GameLiftContainersListCgdsResult : public GameLiftContainersResult
{
	struct CgdAttributes
	{
		FString CgdName;
	};

	TArray<CgdAttributes> Cgds;
};


struct GameLiftECRDescribeRepositoriesResult : public GameLiftECRResult
{
	struct RepositoryAttributes
	{
		FString RepositoryName;
		FString RepositoryUri;
	};

	TArray<RepositoryAttributes> Repos;
};

struct GameLiftECRListImagesResult : public GameLiftECRResult
{
	struct ImageDetailAttributes
	{
		FString ImageDigest;
		FString ImageTag;
	};

	TArray<ImageDetailAttributes> Images;
};

class IGameLiftContainersHandler
{
public:
	virtual ~IGameLiftContainersHandler() = default;

	virtual void SetupContainersDirectory(const FString BuildZipSource, const FString GameExecutable, const FString ContainersDestinationDirectory) = 0;
	virtual GameLiftECRCreateRepositoryResult CreateRepository(const FString& InRepositoryName) = 0;
	virtual GameLiftECRDescribeRepositoriesResult DescribeRepositories() = 0;
	virtual GameLiftECRListImagesResult ListImages(const FString& InRepositoryName) = 0;
	virtual GameLiftContainersListCgdsResult ListCgds() = 0;
	virtual GameLiftDescribeCgdResult DescribeCgd(const FString& InCgdName) = 0;
	virtual GameLiftDescribeContainerFleetResult DescribeContainerFleet(const FString& GameName) = 0;
};