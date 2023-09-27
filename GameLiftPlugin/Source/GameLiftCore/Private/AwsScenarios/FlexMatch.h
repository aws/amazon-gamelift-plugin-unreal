// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Base/ScenarioWithGameServer.h"
#include "GameLiftCoreConstants.h"

namespace AwsScenarios
{
	class FlexMatch : public ScenarioWithGameServer
	{
	public:
		static const FText& Name()
		{
			return Menu::DeploymentServer::kFlexMatch;
		}

		static TUniquePtr<IAWSScenario> Create()
		{
			return MakeUnique<FlexMatch>();
		}

		virtual FText GetTooltip() const override
		{
		   return Menu::DeploymentServer::kFlexMatchTooltip;
		}

		virtual FString GetFolderName() const override
		{
			return Menu::DeploymentServer::kFlexMatchFolder;
		}

		virtual FText GetUserName() const override
		{
			return Name();
		}
	};
} // namespace AwsScenarios
