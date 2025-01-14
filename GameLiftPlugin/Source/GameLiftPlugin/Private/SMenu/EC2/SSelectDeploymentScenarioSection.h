// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "SWidgets/SSectionStep.h"
#include "Widgets/Layout/SWidgetSwitcher.h"
#include "IAWSScenariosDeployer.h"

class SSelectDeploymentScenarioSection : public SSectionStep
{
	SLATE_BEGIN_ARGS(SSelectDeploymentScenarioSection) { }

	SLATE_ARGUMENT(TSharedPtr<SWidget>, SetDeploymentFields)

	SLATE_END_ARGS()

public:
	enum class EDeploymentScenarioFleetChoice {
		SingleRegion,
		FlexMatch
	};
	void Construct(const FArguments& InArgs);

private:
	TSharedRef<SWidget> CreateDeploymentScenarioChoice();
	TSharedRef<SWidget> CreateScenarioSubmittedDetails();
	TSharedRef<SWidget> CreateSubmissionButton();
	TSharedRef<SWidget> CreateModifyButton();

	void BuildScenarioValues(IAWSScenariosCategory Category);
	void SetDefaultValues();

	ECheckBoxState IsRadioChecked(EDeploymentScenarioFleetChoice RadioButtonChoice) const;
	void OnRadioChanged(ECheckBoxState NewRadioState, EDeploymentScenarioFleetChoice RadioButtonChoice);

	FReply OnSubmissionButtonClicked();
	FReply OnModifyButtonClicked();

	void UpdateUIBasedOnCurrentState();
	void CompleteSection();
	void StartSection() override;

private:
	TSharedPtr<SWidget> DeploymentFields;
	TSharedPtr<SWidgetSwitcher> SectionSwitcher;
	TSharedPtr<SButton> SubmissionButton;
	TSharedPtr<SButton> ModifyButton;
	TArray<FText> ScenarioNames;
	TArray<FText> ScenarioDescriptions;
	int CurrentScenarioSelected = 0;
};
