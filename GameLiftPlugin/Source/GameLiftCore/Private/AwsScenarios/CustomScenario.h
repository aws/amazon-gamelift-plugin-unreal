// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Base/ScenarioWithGameServer.h"
#include "GameLiftCoreConstants.h"

namespace AwsScenarios
{
	class CustomScenario : public ScenarioWithGameServer
	{
	public:
		static const FText& Name()
		{
			return Menu::DeploymentServer::kCustom;
		}

		static TUniquePtr<IAWSScenario> Create(const FString& CustomScenarioPath)
		{
			return MakeUnique<CustomScenario>(CustomScenarioPath);
		}

		CustomScenario(const FString& CustomScenarioPath) : Path(CustomScenarioPath)
		{
		}

		virtual FText GetTooltip() const override
		{
		   return Menu::DeploymentServer::kCustomTooltip;
		}

		virtual FString GetFolderName() const override
		{
			return Menu::DeploymentServer::kCustomScenarioFolder;
		}

		virtual FText GetUserName() const override
		{
			return Name();
		}

		virtual FString GetScenarioPath() const override
		{
			return Path;
		}

	private:
		FString Path;
	};
} // namespace AwsScenarios
