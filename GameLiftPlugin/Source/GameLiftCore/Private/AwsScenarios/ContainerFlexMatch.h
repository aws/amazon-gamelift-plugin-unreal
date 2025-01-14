// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GameLiftCoreConstants.h"
#include "Base/ScenarioWithContainerParameters.h"

namespace AwsScenarios
{
	class ContainersFlexMatch : public ScenarioWithContainerParameters
	{
	public:
		static const FText& Name()
		{
			return Menu::DeploymentServer::kContainersFlexMatch;
		}

		static TUniquePtr<IAWSScenario> Create()
		{
			return MakeUnique<ContainersFlexMatch>();
		}

		virtual FText GetTooltip() const override
		{
			return Menu::DeploymentServer::kContainersFlexMatchTooltip;
		}

		virtual FString GetFolderName() const override
		{
			return Menu::DeploymentServer::kContainersFlexMatchFolder;
		}

		virtual FText GetUserName() const override
		{
			return Name();
		}
	};
} // namespace AwsScenarios