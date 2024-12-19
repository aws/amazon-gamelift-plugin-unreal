// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "SWidgets/SSectionStep.h"

#include "Types/EDeploymentMessageState.h"

DECLARE_MULTICAST_DELEGATE(FDeploymentProgress);
class SDeployScenarioSection : public SSectionStep
{
	SLATE_BEGIN_ARGS(SDeployScenarioSection) { }

	SLATE_ARGUMENT(TSharedPtr<SWidget>, SetDeploymentFields)

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);
	static FDeploymentProgress OnEC2DeploymentProgressChangedMultiDelegate;

private:
	void SetDefaultValues();
	bool IsDeploymentStatusActive();
	void UpdateUIBasedOnCurrentState();
	void SetUGameLiftDeploymentStatus(EDeploymentMessageState State);
	void StartSection();
	std::pair<bool, FText> HandleStopButtonState();
	std::pair<bool, FText> HandleDeployButtonState();

	FReply DeployCloudFormation();
	FReply StopDeploying();

	TSharedRef<SWidget> CreateCloudFormationInConsoleHyperLink();

private:
	TSharedPtr<SNotificationItem> NotificationItem;
	TSharedPtr<SWidget> DeploymentFields;
	TSharedPtr<SWidget> DeploymentStatus;
	FText ScenarioSelected;
	const int OverrideButtonHeight = 20;

};
