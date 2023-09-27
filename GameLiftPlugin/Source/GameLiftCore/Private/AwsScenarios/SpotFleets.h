// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Base/ScenarioWithGameServer.h"
#include "GameLiftCoreConstants.h"

namespace AwsScenarios
{
	class SpotFleets : public ScenarioWithGameServer
	{
	public:
		static const FText& Name()
		{
			return Menu::DeploymentServer::kSpotFleets;
		}

		static TUniquePtr<IAWSScenario> Create()
		{
			return MakeUnique<SpotFleets>();
		}

		virtual FText GetTooltip() const override
		{
		   return Menu::DeploymentServer::kSpotFleetsTooltip;
		}

		virtual FString GetFolderName() const override
		{
			return Menu::DeploymentServer::kSpotFleetsFolder;
		}

		virtual FText GetUserName() const override
		{
			return Name();
		}
	};
} // namespace AwsScenarios
