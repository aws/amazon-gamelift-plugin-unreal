// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GameLiftCoreConstants.h"
#include "Base/ScenarioWithContainerParameters.h"

namespace AwsScenarios
{
	class ContainersSingleRegionFleet : public ScenarioWithContainerParameters
	{
	public:
		static const FText& Name()
		{
			return Menu::DeploymentServer::kContainersSingleRegionFleet;
		}

		static TUniquePtr<IAWSScenario> Create()
		{
			return MakeUnique<ContainersSingleRegionFleet>();
		}

		virtual FText GetTooltip() const override
		{
			return Menu::DeploymentServer::kContainersSingleRegionFleetTooltip;
		}

		virtual FString GetFolderName() const override
		{
			return Menu::DeploymentServer::kContainersSingleRegionFleetFolder;
		}

		virtual FText GetUserName() const override
		{
			return Name();
		}
	};
} // namespace AwsScenarios