// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Base/ScenarioWithGameServer.h"
#include "GameLiftCoreConstants.h"

namespace AwsScenarios
{
	class SingleRegionFleet : public ScenarioWithGameServer
	{
	public:
		static const FText& Name()
		{
			return Menu::DeploymentServer::kSingleRegionFleet;
		}

		static TUniquePtr<IAWSScenario> Create()
		{
			return MakeUnique<SingleRegionFleet>();
		}

		virtual FText GetTooltip() const override
		{
		   return Menu::DeploymentServer::kSingleRegionFleetTooltip;
		}

		virtual FString GetFolderName() const override
		{
			return Menu::DeploymentServer::kSingleRegionFleetFolder;
		}

		virtual FText GetUserName() const override
		{
			return Name();
		}
	};
} // namespace AwsScenarios
