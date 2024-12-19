// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

// Display help documentations.
class SGameLiftSettingsHelpMenu : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SGameLiftSettingsHelpMenu) {}

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

private:
	TSharedRef<SWidget> MakeHelpWidget() const;
	TSharedRef<SWidget> MakeHelpCardWidget(const TCHAR* UrlLink, int IconWidth, const FString& IconName, const FText TitleText, const FText DescriptionText) const;
};
