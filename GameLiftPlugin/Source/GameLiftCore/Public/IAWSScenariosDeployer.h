// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once 

#include "IAWSAccountInstance.h"

class IAWSScenariosDeployer
{
public:
	virtual ~IAWSScenariosDeployer() = default;
	
	virtual bool DeployScenario(
		const FText& Scenario,
		IAWSAccountInstance *AccountInstance,
		const FString& GameName,
		const FString& BuildOperatingSystem,
		const FString& BuildFolderPath,
		const FString& BuildFilePath,
		const FString& OutConfigFilePath,
		const FString& ExtraServerResourcesPath
	) = 0;
	virtual bool DeployCustomScenario(
		const FString& CustomScenarioPath,
		IAWSAccountInstance* AccountInstance,
		const FString& GameName,
		const FString& BuildOperatingSystem,
		const FString& BuildFolderPath,
		const FString& BuildFilePath,
		const FString& OutConfigFilePath,
		const FString& ExtraServerResourcesPath
	) = 0;
	virtual bool StopDeployment(IAWSAccountInstance* AwsAccountInstance) = 0;

	virtual FString GetLastCognitoClientId() const = 0;
	virtual FString GetLastApiGatewayEndpoint() const = 0;
	virtual FString GetLastError() const = 0;
	virtual FString GetLastErrorMessage() const = 0;

	virtual TArray<FText> GetScenarios() const = 0;
	virtual FText GetToolTip(const FText& ScenarioName) const = 0;
};
