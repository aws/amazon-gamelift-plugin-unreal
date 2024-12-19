// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

// Display GameLift introduction.
class SGameLiftSettingsGameLiftMenu : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SGameLiftSettingsGameLiftMenu) {}

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

private:
	TSharedRef<SWidget> MakeGetStartedWidget() const;
	TSharedRef<SWidget> CreateFleetCard(const FString& IconName, const FText TitleText, const FText DescriptionText, TSharedRef<SWidget> ButtonWidget) const;
	TSharedRef<SWidget> MakeSetUpAnywhereButtonSwitcher() const;

private:
	TSharedPtr<SButton> SetUpAnywhereButton;
};
