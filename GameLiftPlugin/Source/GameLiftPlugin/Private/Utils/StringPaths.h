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
