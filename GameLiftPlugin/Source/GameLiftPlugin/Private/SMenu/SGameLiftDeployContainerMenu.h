// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "SGameLiftDeployManagedEC2Menu.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"

class SWindow;
class SPathInput;

class SGameLiftDeployContainerMenu : public SGameLiftDeployManagedEC2Menu
{
public:
	virtual void Construct(const FArguments& InArgs) override;

protected:
	virtual TSharedRef<SWidget> CreateSelectDeploymentScenarioSection() override;
	virtual TSharedRef<SWidget> CreateGameParametersSection() override;
	virtual TSharedRef<SWidget> CreateDeploySection() override;
	virtual TSharedRef<SWidget> CreateLaunchClientSection() override;
	
	virtual void BuildScenarioValues(IAWSScenariosCategory Category) override;
	virtual void OnBuildingDeploymentScenarioValues(TArray<FTextIntPair>& Items) override;
	
	virtual void SetDefaultValues() override;
	virtual FReply DeployCloudFormation() override;
};
