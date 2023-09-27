// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Input/Reply.h"
#include "Styling/SlateColor.h"

#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/SWidget.h"

#include "GameLiftPluginConstants.h"
#include "GameLiftPluginStyle.h"

// Banner indicating an error with an optional button
class SErrorBanner : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SErrorBanner) {}

	SLATE_ARGUMENT(FText, ErrorText)

	SLATE_ARGUMENT_DEFAULT(FText, ErrorButtonText) { FText::GetEmpty() };

	SLATE_ARGUMENT_DEFAULT(FName, ErrorIcon) { Style::Brush::kStatusErrorIconName };

	SLATE_EVENT(FSimpleDelegate, OnBannerButtonClicked)

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

private:
	FSlateColor GetBorderColor() const;
	FSlateColor GetTextColor() const;

	TSharedRef<SWidget> MakeRow(FName IconName, const FText& Message, const FText& ButtonMessage);

	FReply OnBannerButtonPressed();
	FReply OnCloseButtonPressed();

private:
	FSimpleDelegate OnBannerButtonClicked;
};
