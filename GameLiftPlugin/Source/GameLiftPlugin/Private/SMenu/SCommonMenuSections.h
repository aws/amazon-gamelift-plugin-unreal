// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "SWidgets/SSectionsWithHeaders.h"
#include "SWidgets/SSectionStep.h"

class SPathInput;
class SGameLiftSettingsAwsAccountMenu;

class SSetProfileSection : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SSetProfileSection) {}

	SLATE_ARGUMENT_DEFAULT(FString, ReadDeveloperGuideLink) { TEXT("") };

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

	TSharedRef<SGameLiftSettingsAwsAccountMenu> GetAwsAccountMenuRef();
	
	SSectionsWithHeaders::FSectionInfo GetSectionInfo();

private:
	TSharedPtr<SGameLiftSettingsAwsAccountMenu> AwsAccountMenu;

};

class SIntegrateGameSection : public SSectionStep
{
	SLATE_BEGIN_ARGS(SIntegrateGameSection) {}

	SLATE_ARGUMENT_DEFAULT(bool, HideBuildPathInput) { false };

	SLATE_ARGUMENT(FString, HowToIntegrateYourGameLinkUrl)

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

	const FString& GetGameServerPath() const;

private:
	void OnServerPathInputUpdated(const FString& NewPath);

	void SetPaths();
	void UpdateUIBasedOnCurrentState();
	void CompleteSection();
	void StartSection() override;

	TSharedRef<SWidget> CreateUnrealSourceWarningMessage();
	TSharedRef<SWidget> CreateSubmissionButton();
	TSharedRef<SWidget> CreateModifyButton();

	FReply OnSubmissionButtonClicked();
	FReply OnModifyButtonClicked();

	TSharedPtr<SPathInput> GameServerPathInput;
	TSharedPtr<SWidgetSwitcher> SectionSwitcher;

	TSharedPtr<SWidget> UnrealSourceWarningMessage;
	TSharedPtr<SButton> SubmissionButton;
	TSharedPtr<SButton> ModifyButton;

	FString HowToIntegrateYourGameLinkUrl;

	bool HideBuildPathInput;
};
