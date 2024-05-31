// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "IAWSScenariosDeployer.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"

class SWindow;
class SPathInput;
struct FTextIntPair;

class SGameLiftDeployManagedEC2Menu : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SGameLiftDeployManagedEC2Menu)
		{
		}

		SLATE_ARGUMENT(TWeakPtr<SWindow>, ContextWindow)

	SLATE_END_ARGS()

public:
	virtual void Construct(const FArguments& InArgs);

protected:
	virtual TSharedRef<SWidget> CreateSelectDeploymentScenarioSection();
	virtual TSharedRef<SWidget> CreateGameParametersSection();
	virtual TSharedRef<SWidget> CreateDeploySection();
	virtual TSharedRef<SWidget> CreateLaunchClientSection();

	virtual void BuildScenarioValues(IAWSScenariosCategory Category);
 
	virtual void OnBuildingDeploymentScenarioValues(TArray<FTextIntPair>& Items);
	virtual void OnDeploymentScenarioSelected(int SelectionId, const FTextIntPair& Item);

	virtual void SetDefaultValues();
	virtual FReply DeployCloudFormation();
	virtual FReply StopDeploying();
	virtual void SwitchDeploymentFields();
	virtual bool CanLaunchGameClient() const;

	virtual FText TooltipLaunchGameClient() const;

	virtual TSharedRef<SWidget> CreateCloudFormationInConsoleHyperLink();

protected:
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
