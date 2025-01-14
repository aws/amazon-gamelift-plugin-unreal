// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

class SIntakeQuestionnaireSection;

DECLARE_MULTICAST_DELEGATE_OneParam(FDeploymentScenarioState, const SIntakeQuestionnaireSection* /* Sender */);

class SIntakeQuestionnaireSection : public SCompoundWidget
{
    SLATE_BEGIN_ARGS(SIntakeQuestionnaireSection) { }

    SLATE_END_ARGS()

public:
    void Construct(const FArguments& InArgs);
    static FDeploymentScenarioState OnDeploymentScenarioStateChangedMultiDelegate;

private:
    enum class EHasExistingContainerImageChoice {
        NoExistingContainerImage,
        HasExistingContainerImage
    };
    enum class EUseExistingECRRepoChoice {
        NoExistingECRRepo,
        UseExistingECRRepo
    };
    enum class EContainerImageChoice {
        AmazonECR,
        Docker
    };

    TSharedRef<SWidget> CreateFirstQuestion();
    TSharedRef<SWidget> CreateSecondQuestion();

    ECheckBoxState IsRadioChecked(EHasExistingContainerImageChoice RadioButtonChoice) const;
    void OnRadioChanged(ECheckBoxState NewRadioState, EHasExistingContainerImageChoice RadioButtonChoice);
    ECheckBoxState IsRadioChecked(EUseExistingECRRepoChoice RadioButtonChoice) const;
    void OnRadioChanged(ECheckBoxState NewRadioState, EUseExistingECRRepoChoice RadioButtonChoice);
    ECheckBoxState IsRadioChecked(EContainerImageChoice RadioButtonChoice) const;
    void OnRadioChanged(ECheckBoxState NewRadioState, EContainerImageChoice RadioButtonChoice);
   
    void UpdateDeploymentScenarioState();

};
