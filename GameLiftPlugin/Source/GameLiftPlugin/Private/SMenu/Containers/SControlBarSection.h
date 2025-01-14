// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

class SControlBarSection;
DECLARE_MULTICAST_DELEGATE(FNewDeployment);

class SControlBarSection : public SCompoundWidget
{
    SLATE_BEGIN_ARGS(SControlBarSection) { }

    SLATE_END_ARGS()

public:
    void Construct(const FArguments& InArgs);
    static FNewDeployment OnNewDeploymentMultiDelegate;

private:
    TSharedRef<SWidget> CreateDockerInstallWarningMessage();
    TSharedRef<SWidget> CreateDeploymentTimeNotificationBar();
    TSharedRef<SWidget> CreateDeploymentButtonsRow();
    TSharedRef<SWidget> CreateAWSConsoleButton();
    TSharedRef<SWidget> CreateDeploymentButtonSwitcher();
    bool IsContainerDeploymentStatusActive();
    void DisplayResetModal();
    bool IsAccountBootstrapped() const;

private:
    TSharedPtr<SWidget> DeploymentTimeNotification;
    const int OverrideButtonHeight = 20;
    TSharedPtr<SWidget> DeploymentStatus;
    TSharedPtr<SNotificationItem> NotificationItem;

};
