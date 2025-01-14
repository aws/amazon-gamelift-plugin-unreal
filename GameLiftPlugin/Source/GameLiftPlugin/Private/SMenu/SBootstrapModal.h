// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"
#include "GameLiftPluginConstants.h"

class SWindow;
class SPathInput;

DECLARE_DELEGATE_OneParam(FBootstrapProfile, FString);

class SBootstrapModal : public SCompoundWidget
{
    SLATE_BEGIN_ARGS(SBootstrapModal) {}

        SLATE_ARGUMENT(FString, DefaultS3BucketName)

        SLATE_ARGUMENT(TWeakPtr<SWidget>, ParentWidget)

        SLATE_EVENT(FBootstrapProfile, OnBootstrapProfileClickedDelegate)

    SLATE_END_ARGS()

public:
    void Construct(const FArguments& InArgs);
    void ShowModal();
    void CloseModal();

private:
    FReply OnBootstrapProfileClicked();
    FReply OnCloseButtonClicked();
    void SetParentWindow();
    void OnS3BucketNameInputUpdated(const FString& NewPath);
    TSharedRef<SWidget> CreateS3BucketNameInput();

private:
    TSharedPtr<SPathInput> S3BucketNameInput;
    TSharedPtr<SWindow> OwnerWindow;
    TWeakPtr<SWidget> ParentWidget;
    TSharedPtr<SButton> BootstrapProfile;
    TSharedPtr<STextBlock> BootstrapProfileHeader;
    FString S3BucketNameToUpdate;
    FString S3BucketName;
    FBootstrapProfile OnBootstrapProfileClickedDelegate;
    const int MinModalWindowWidth = 650;
    const int MaxModalWindowWidth = 800;
};