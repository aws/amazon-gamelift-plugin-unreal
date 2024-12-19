// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <string>

#include <Interfaces/IPluginManager.h>

#include "GameLiftCoreConstants.h"

namespace Paths
{
	inline const auto& PluginRootPath()
	{
		static FString PluginRootPath = 
			FPaths::ConvertRelativePathToFull(*IPluginManager::Get().FindPlugin(Core::sGameLiftPluginName)->GetBaseDir());
		return PluginRootPath;
	}

	inline const auto& CloudFormationRootPath()
	{
		static FString CloudFormationRootPath = FPaths::ConvertRelativePathToFull(FPaths::Combine(
			PluginRootPath(),
			TEXT("Resources"),
			TEXT("CloudFormation")
		));
		return CloudFormationRootPath;
	}

	inline const auto& IntermediateCloudFormationRootPath()
	{
		static FString CloudFormationRootPath = FPaths::ConvertRelativePathToFull(FPaths::Combine(
			PluginRootPath(),
			TEXT("Intermediate"),
			TEXT("CloudFormation")
		));
		return CloudFormationRootPath;
	}

	inline const auto& ContainersTemplatePath()
	{
		static FString ContainersTemplateRootPath = FPaths::ConvertRelativePathToFull(FPaths::Combine(
			PluginRootPath(),
			TEXT("Resources"),
			TEXT("Containers"),
			TEXT("SampleDockerfile")
		));
		return ContainersTemplateRootPath;
	}

	inline const auto ScenarioPath(const FString& Scenario)
	{
		return FPaths::Combine(CloudFormationRootPath(), Scenario);
	}

	inline const auto ScenarioInstancePath(const FString& Scenario)
	{
		return FPaths::Combine(IntermediateCloudFormationRootPath(), TEXT("instance"), Scenario);
	}
} // namespace Paths
