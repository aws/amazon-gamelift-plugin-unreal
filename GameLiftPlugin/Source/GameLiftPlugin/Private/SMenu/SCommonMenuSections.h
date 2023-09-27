// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "SWidgets/SSectionsWithHeaders.h"

class SPathInput;

class SSetProfileSection : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SSetProfileSection) {}

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);
	
	SSectionsWithHeaders::FSectionInfo GetSectionInfo();
};

class SIntegrateGameSection : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SIntegrateGameSection) {}

	SLATE_ARGUMENT_DEFAULT(bool, HideBuildPathInput) { false };

	SLATE_ARGUMENT(FString, HowToIntegrateYourGameLinkUrl)

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

	SSectionsWithHeaders::FSectionInfo GetSectionInfo();

	void UpdateUI();

	const FString& GetGameServerPath() const;
	const FString& GetGameClientPath() const;

	void LoadImages();
	FReply SwitchActiveToggler(int index);
	void GenerateTogglerButtons();
	TSharedRef<SWidget> MakeTogglerButtonWidget(const FText& SectionName, const FSlateBrush* ImageBrush, FVector2D ImageSize, int index);
	void GenerateTogglerContent();

private:
	void OnServerPathInputUpdated(const FString& NewPath);
	void OnClientPathInputUpdated(const FString& NewPath);

	TSharedPtr<SPathInput> GameServerPathInput;
	TSharedPtr<SPathInput> GameClientPathInput;

	int ActiveTogglerTab = 0;
	TSharedPtr<SHorizontalBox> TogglerButtonsBox;
	TSharedPtr<SVerticalBox> TogglerContentBox;

	FString HowToIntegrateYourGameLinkUrl;
};

