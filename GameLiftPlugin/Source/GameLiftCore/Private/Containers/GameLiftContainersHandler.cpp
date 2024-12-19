// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "GameLiftContainersHandler.h"

#include "aws/gamelift/core/exports.h"
#include "aws/gamelift/GameLiftClient.h"

#include "GameLiftCoreConstants.h"
#include "GameLiftCoreLog.h"
#include "IGameLiftCoreModule.h"
#include "Utils/StringConvertors.h"
#include <Utils/StringPaths.h>
using namespace Aws::GameLift::Model::ContainerFleetBillingTypeMapper;
using namespace Aws::GameLift::Model::ContainerFleetStatusMapper;

#define LOCTEXT_NAMESPACE "GameLiftContainersHandler"

namespace GameLiftContainersHandlerInternal
{
	ECRFuncErrorCallback ErrorCallback = [](DISPATCH_RECEIVER_HANDLE ErrorReceiver, ECR_ERROR_INFO* ErrorInfo) -> void
		{
			FString* Error = reinterpret_cast<FString*>(ErrorReceiver);
			*Error = ErrorInfo->errorMessage;
		};

	FuncErrorCallback GameLiftErrorCallback = [](DISPATCH_RECEIVER_HANDLE ErrorReceiver, GAMELIFT_ERROR_INFO* ErrorInfo) -> void
		{
			FString* Error = reinterpret_cast<FString*>(ErrorReceiver);
			*Error = ErrorInfo->errorMessage;
		};
} // namespace GameLiftContainersHandlerInternal

void GameLiftContainersHandler::SetupContainersDirectory(const FString BuildDirectory, const FString GameExecutable, const FString ContainersDestinationDirectory)
{
	UE_LOG(GameLiftCoreLog, Log, TEXT("Setting up containers directory"));

	// Unreal file I/O interface
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	// Prepare directory
	FString BuildDestinationDirectory = FPaths::Combine(*ContainersDestinationDirectory, TEXT("gamebuild"));
	if (FPaths::DirectoryExists(*ContainersDestinationDirectory))
	{
		PlatformFile.DeleteDirectoryRecursively(*ContainersDestinationDirectory);
	}
	PlatformFile.CreateDirectoryTree(*ContainersDestinationDirectory);
	PlatformFile.CreateDirectoryTree(*BuildDestinationDirectory);

	// Copy the build directory to destination folder
	FString BuildDirectoryName = FPaths::GetCleanFilename(BuildDirectory);
	BuildDestinationDirectory = FPaths::Combine(*BuildDestinationDirectory, *BuildDirectoryName);
	PlatformFile.CreateDirectoryTree(*BuildDestinationDirectory);
	PlatformFile.CopyDirectoryTree(*BuildDestinationDirectory, *BuildDirectory, true);

	// Copy Dockerfile
	auto DockerfileTemplatePath = Paths::ContainersTemplatePath();
	PlatformFile.CopyFile(*FPaths::Combine(*ContainersDestinationDirectory, TEXT("Dockerfile")), *DockerfileTemplatePath);
}

GameLiftECRCreateRepositoryResult GameLiftContainersHandler::CreateRepository(const FString& InRepositoryName)
{
	IAWSAccountInstance* AccountInstance = IGameLiftCoreModule::Get().GetProfileBootstrap().GetAccountInstance();
	check(AccountInstance);
	check(AccountInstance->GetInstance());

	std::string StdRepositoryName = Convertors::FSToStdS(InRepositoryName);
	GAMELIFT_ECR_REPO_URI ECRRepoUri;


	GAMELIFT_ECR_CREATE_REPO_REQUEST Request;
	Request.repositoryName = StdRepositoryName.c_str();

	FString ErrorMessageReceiver;
	Request.errorCb = GameLiftContainersHandlerInternal::ErrorCallback;
	Request.errorReceiver = &ErrorMessageReceiver;

	GameLiftECRCreateRepositoryResult Result;
	Result.bIsSuccessful = GameLiftECRCreateRepository(AccountInstance->GetInstance(), &Request, &ECRRepoUri);
	Result.ErrorMessage = ErrorMessageReceiver;
	if (Result.bIsSuccessful)
	{
		UE_LOG(GameLiftCoreLog, Log, TEXT("Successfully created ECR Repository: %s"), *InRepositoryName);
		Result.RepoUri = FString(ECRRepoUri.repoUri);
		Result.RepositoryName = InRepositoryName;
	}
	else
	{
		UE_LOG(GameLiftCoreLog, Error, TEXT("Failed to create ECR Repository '%s' - %s"), *InRepositoryName, *(Result.ErrorMessage));
	}

	return Result;
}

GameLiftECRDescribeRepositoriesResult GameLiftContainersHandler::DescribeRepositories()
{
	IAWSAccountInstance* AccountInstance = IGameLiftCoreModule::Get().GetProfileBootstrap().GetAccountInstance();
	check(AccountInstance);
	check(AccountInstance->GetInstance());

	GAMELIFT_ECR_DESCRIBE_REPOSITORIES_REQUEST Request;

	FString ErrorMessageReceiver;
	Request.errorCb = GameLiftContainersHandlerInternal::ErrorCallback;
	Request.errorReceiver = &ErrorMessageReceiver;

	GAMELIFT_ECR_DESCRIBE_REPO_INFO DescribeReposInfo;
	GameLiftECRDescribeRepositoriesResult Result;
	if (AccountInstance->GetInstance())
	{
		Result.bIsSuccessful = GameLiftECRDescribeRepositories(AccountInstance->GetInstance(), &Request, &DescribeReposInfo);
		Result.ErrorMessage = ErrorMessageReceiver;
	}
	else
	{
		Result.bIsSuccessful = false;
	}
	if (Result.bIsSuccessful)
	{
		for (int i = 0; i < DescribeReposInfo.numRepos; i++)
		{
			auto& repoInfo = DescribeReposInfo.repos[i];
			Result.Repos.Add({ FString(repoInfo.repoName), FString(repoInfo.repoUri) });
		}
		UE_LOG(GameLiftCoreLog, Log, TEXT("Successfully retrieved ECR Repositories info"));
	}
	else
	{
		UE_LOG(GameLiftCoreLog, Error, TEXT("Failed to retrieve ECR Repositories info - %s"), *(Result.ErrorMessage));
	}

	return Result;
}

GameLiftECRListImagesResult GameLiftContainersHandler::ListImages(const FString& InRepositoryName)
{
	IAWSAccountInstance* AccountInstance = IGameLiftCoreModule::Get().GetProfileBootstrap().GetAccountInstance();
	check(AccountInstance);
	check(AccountInstance->GetInstance());

	std::string StdRepositoryName = Convertors::FSToStdS(InRepositoryName);
	GAMELIFT_ECR_LIST_IMAGES_REQUEST Request;
	Request.repositoryName = StdRepositoryName.c_str();

	FString ErrorMessageReceiver;
	Request.errorCb = GameLiftContainersHandlerInternal::ErrorCallback;
	Request.errorReceiver = &ErrorMessageReceiver;

	GAMELIFT_ECR_LIST_IMAGES_INFO ListImagesInfo;
	GameLiftECRListImagesResult Result;

	if (AccountInstance->GetInstance())
	{
		Result.bIsSuccessful = GameLiftECRListImages(AccountInstance->GetInstance(), &Request, &ListImagesInfo);
		Result.ErrorMessage = ErrorMessageReceiver;
	}
	else
	{
		Result.bIsSuccessful = false;
	}

	if (Result.bIsSuccessful)
	{
		for (int i = 0; i < ListImagesInfo.numImages; i++)
		{
			auto& imageInfo = ListImagesInfo.images[i];
			Result.Images.Add({ FString(imageInfo.imageDigest), FString(imageInfo.imageTag) });
		}
		UE_LOG(GameLiftCoreLog, Log, TEXT("Successfully listed ECR Images info"));
	}
	else
	{
		UE_LOG(GameLiftCoreLog, Error, TEXT("Failed to list ECR iamges info - %s"), *(Result.ErrorMessage));
	}

	return Result;
}

GameLiftContainersListCgdsResult GameLiftContainersHandler::ListCgds()
{
	IAWSAccountInstance* AccountInstance = IGameLiftCoreModule::Get().GetProfileBootstrap().GetAccountInstance();
	check(AccountInstance);
	check(AccountInstance->GetInstance());

	GAMELIFT_CONTAINERS_LIST_CGDS_REQUEST Request;

	FString ErrorMessageReceiver;
	Request.errorCb = GameLiftContainersHandlerInternal::GameLiftErrorCallback;
	Request.errorReceiver = &ErrorMessageReceiver;

	GAMELIFT_CONTAINERS_LIST_CGD_INFO ListCgdInfo;
	GameLiftContainersListCgdsResult Result;
	if (AccountInstance->GetInstance())
	{
		Result.bIsSuccessful = GameLiftContainersListCgds(AccountInstance->GetInstance(), &Request, &ListCgdInfo);
		Result.ErrorMessage = ErrorMessageReceiver;
	}
	else
	{
		Result.bIsSuccessful = false;
	}
	if (Result.bIsSuccessful)
	{
		for (int i = 0; i < ListCgdInfo.numCgds; i++)
		{
			auto& cgdInfo = ListCgdInfo.cgds[i];
			Result.Cgds.Add({ FString(cgdInfo.cgdName) });
		}
		UE_LOG(GameLiftCoreLog, Log, TEXT("Successfully retrieved container group definitions info"));
	}
	else
	{
		UE_LOG(GameLiftCoreLog, Error, TEXT("Failed to retrieve container group definitions info - %s"), *(Result.ErrorMessage));
	}

	return Result;
}

GameLiftDescribeCgdResult GameLiftContainersHandler::DescribeCgd(const FString& InCgdName)
{
	IAWSAccountInstance* AccountInstance = IGameLiftCoreModule::Get().GetProfileBootstrap().GetAccountInstance();
	check(AccountInstance);
	check(AccountInstance->GetInstance());

	std::string StdCgdName = Convertors::FSToStdS(InCgdName);
	GAMELIFT_CONTAINERS_DESCRIBE_CGD_INFO DescribeCgdInfo;


	GAMELIFT_CONTAINERS_DESCRIBE_CGD_REQUEST Request;
	Request.cgdName = StdCgdName.c_str();

	FString ErrorMessageReceiver;
	Request.errorCb = GameLiftContainersHandlerInternal::GameLiftErrorCallback;
	Request.errorReceiver = &ErrorMessageReceiver;

	GameLiftDescribeCgdResult Result;
	Result.bIsSuccessful = GameLiftContainersDescribeCgd(AccountInstance->GetInstance(), &Request, &DescribeCgdInfo);
	Result.ErrorMessage = ErrorMessageReceiver;
	if (Result.bIsSuccessful)
	{
		UE_LOG(GameLiftCoreLog, Log, TEXT("Successfully described container group definition: %s"), *InCgdName);
		Result.CgdVersion = FString::FromInt(DescribeCgdInfo.cgdVersion);
		Result.CgdStatus = FString(DescribeCgdInfo.cgdStatus);
		UE_LOG(GameLiftCoreLog, Log, TEXT("Container group definition status is: %s"), *Result.CgdStatus);
	}
	else
	{
		UE_LOG(GameLiftCoreLog, Error, TEXT("Failed to described container group definition '%s' - %s"), *InCgdName, *(Result.ErrorMessage));
	}

	return Result;
}

GameLiftDescribeContainerFleetResult GameLiftContainersHandler::DescribeContainerFleet(const FString& GameName)
{
	IAWSAccountInstance* AccountInstance = IGameLiftCoreModule::Get().GetProfileBootstrap().GetAccountInstance();
	check(AccountInstance);
	check(AccountInstance->GetInstance());

	auto AccountHandle = AccountInstance->GetInstance();

	GAMELIFT_CONTAINERS_DESCRIBE_CONTAINER_FLEET_INFO DescribeContainerFleetInfo;


	GAMELIFT_CONTAINERS_DESCRIBE_CONTAINER_FLEET_REQUEST Request;

	FString ErrorMessageReceiver;
	Request.errorCb = GameLiftContainersHandlerInternal::GameLiftErrorCallback;
	Request.errorReceiver = &ErrorMessageReceiver;

	GameLiftDescribeContainerFleetResult Result;

	std::string StdGameName = Convertors::FSToStdS(GameName);
	GameLiftAccountSetGameName(AccountHandle, StdGameName.c_str()); // game name needed to get the stack name

	Result.bIsSuccessful = GameLiftContainersDescribeContainerFleet(AccountHandle, &Request, &DescribeContainerFleetInfo);
	Result.ErrorMessage = ErrorMessageReceiver;
	if (Result.bIsSuccessful)
	{
		auto fleetStatusStd = GetNameForContainerFleetStatus(DescribeContainerFleetInfo.containerFleetStatus);
		auto FleetTypeStd = GetNameForContainerFleetBillingType(DescribeContainerFleetInfo.containerFleetBillingType);
		auto InstanceTypeStd = DescribeContainerFleetInfo.instanceType;
		Result.FleetId = FString(DescribeContainerFleetInfo.fleetId);
		Result.FleetStatus = FString(fleetStatusStd.c_str());
		Result.FleetType = FString(FleetTypeStd.c_str());
		Result.InstanceType = FString(InstanceTypeStd.c_str());
		UE_LOG(GameLiftCoreLog, Log, TEXT("Successfully described container fleet: %s"), *Result.FleetId);
	}
	else
	{
		UE_LOG(GameLiftCoreLog, Error, TEXT("Failed to described container fleet - %s"), *(Result.ErrorMessage));
	}

	return Result;
}

