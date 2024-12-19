// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <string>

#include <Interfaces/IPluginManager.h>

#include "GameLiftPluginConstants.h"

namespace Paths
{
	inline const auto& PluginRootPath()
	{
		static FString PluginRootPath =
			FPaths::ConvertRelativePathToFull(*IPluginManager::Get().FindPlugin(Plugin::sGameLiftPluginName)->GetBaseDir());
		return PluginRootPath;
	}

	inline const auto& DefaultOutConfigFilePath()
	{
		static FString CloudFormationRootPath = FPaths::ConvertRelativePathToFull(FPaths::Combine(
			PluginRootPath(),
			TEXT(".."),
			TEXT(".."),
			TEXT("Content"),
			TEXT("CloudFormation")
		));
		return CloudFormationRootPath;
	}

	inline const auto& DefaultContainersPath()
	{
		static FString DefaultContainersPath = FPaths::ConvertRelativePathToFull(FPaths::Combine(
			PluginRootPath(),
			TEXT("Content"),
			TEXT("GameLiftContainers")
		));
		return DefaultContainersPath;
	}

	inline const auto& DefaultContainerImagePath()
	{
		static FString DefaultContainersImagePath = FPaths::ConvertRelativePathToFull(FPaths::Combine(
			DefaultContainersPath(),
			TEXT("ContainerImage")
		));
		return DefaultContainersImagePath;
	}

	inline const auto& ContainersSamplePushScriptPath()
	{
		static FString ContainersSamplePushScriptPath = FPaths::ConvertRelativePathToFull(FPaths::Combine(
			PluginRootPath(),
			TEXT("Resources"),
			TEXT("Containers"),
			TEXT("SamplePushScript.ps1")
		));
		return ContainersSamplePushScriptPath;
	}

	inline const auto& PushExistingImageToECRPath()
	{
		static FString ContainersSamplePushScriptPath = FPaths::ConvertRelativePathToFull(FPaths::Combine(
			PluginRootPath(),
			TEXT("Resources"),
			TEXT("Containers"),
			TEXT("PushExistingImageToECRScript.ps1")
		));
		return ContainersSamplePushScriptPath;
	}

	inline const auto& ContainersPushScriptPath()
	{
		static FString ContainersPushScriptPath = FPaths::ConvertRelativePathToFull(FPaths::Combine(
			DefaultContainersPath(),
			TEXT("ContainerImagePushScript.ps1")
		));
		return ContainersPushScriptPath;
	}

	inline const auto& ContainersPushScriptLogPath()
	{
		static FString ContainersPushScriptLogPath = FPaths::ConvertRelativePathToFull(FPaths::Combine(
			DefaultContainersPath(),
			TEXT("PushScriptLog.txt")
		));
		return ContainersPushScriptLogPath;
	}

	inline const auto& DefaultExtraServerResourcesPath()
	{
		static FString CloudFormationRootPath = FPaths::ConvertRelativePathToFull(FPaths::Combine(
			PluginRootPath(),
			TEXT("Resources"),
			TEXT("CloudFormation"),
			TEXT("extra_server_resources")
		));
		return CloudFormationRootPath;
	}
} // namespace Paths