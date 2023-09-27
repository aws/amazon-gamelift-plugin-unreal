// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "UGameLiftDeploymentStatus.h"

#include "GameLiftPluginConstants.h"

#include "Utils/StringPaths.h"

UGameLiftDeploymentStatus::UGameLiftDeploymentStatus(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	LoadConfig();

	auto SetDefault = [&](FText& Field, auto&& Definition)
	{
		if (Field.IsEmpty())
		{
			Field = FText::FromString(Definition);
		}
	};

	SetDefault(Status, Menu::DeployManagedEC2::kNoDeployment);
	SetDefault(Scenario, Menu::DeployManagedEC2::kNeedDeployment);
	SetDefault(ApiGatewayEndpoint, Menu::DeployManagedEC2::kNeedDeployment);
	SetDefault(CognitoClientId, Menu::DeployManagedEC2::kNeedDeployment);
	SetDefault(ExtraServerResourcesPath, Paths::DefaultExtraServerResourcesPath());
	SetDefault(OutConfigFilePath, Paths::DefaultOutConfigFilePath());

	SaveConfig();
}
