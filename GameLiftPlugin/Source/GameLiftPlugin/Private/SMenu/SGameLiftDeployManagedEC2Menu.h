// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"

class SWindow;
class SPathInput;

class SGameLiftDeployManagedEC2Menu : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SGameLiftDeployManagedEC2Menu) { }
	
	SLATE_ARGUMENT(TWeakPtr<SWindow>, ContextWindow)

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

private:
	TSharedRef<SWidget> CreateSelectDeploymentScenarioSection();
	TSharedRef<SWidget> CreateGameParametersSection();
	TSharedRef<SWidget> CreateDeploySection();
	TSharedRef<SWidget> CreateLaunchClientSection();

	void BuildScenarioValues();

	void OnBuildingDeploymentScenarioValues(TArray<FTextIntPair>& Items);
	void OnDeploymentScenarioSelected(int SelectionId, const FTextIntPair& Item);

	void SetDefaultValues();
	FReply DeployCloudFormation();
	FReply StopDeploying();
	void SwitchDeploymentFields();
	bool CanLaunchGameClient() const;

	FText TooltipLaunchGameClient() const;

	TSharedRef<SWidget> CreateCloudFormationInConsoleHyperLink();

private:
	TSharedPtr<SWidget> DeploymentFields;
	TSharedPtr<SWidget> DeploymentStatus;
	TSharedPtr<SPathInput> GameClientPathInput;
	TSharedPtr<SWidget> ScenariosSelected;
	TSharedPtr<SWidget> ScenariosSelector;
	TArray<FText> ScenarioNames;
	int CurrentScenarioSelected = 0;

	TWeakPtr<SWindow> ContextWindow;
	TSharedPtr<SNotificationItem> NotificationItem;

	bool IsLaunchingGameClient = false;
};
