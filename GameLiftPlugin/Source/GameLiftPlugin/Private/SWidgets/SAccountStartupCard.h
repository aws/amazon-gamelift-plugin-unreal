// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class SWindow;

// Display a card widget with an optional text, button, and link widget.
class SAccountStartupCard : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SAccountStartupCard) {}

	SLATE_ARGUMENT(TWeakPtr<SWindow>, ContextWindow)

	SLATE_ARGUMENT_DEFAULT(FName, Icon) { FName() };

	SLATE_ARGUMENT_DEFAULT(FText, DescriptionText) { FText() };

	SLATE_ARGUMENT_DEFAULT(FText, MiddleDescriptionText) { FText() };

	SLATE_ARGUMENT_DEFAULT(FText, LinkText) { FText() };

	SLATE_ARGUMENT_DEFAULT(FString, LinkUrl) { FString() };

	SLATE_ARGUMENT_DEFAULT(FText, ButtonText) { FText() };

	SLATE_EVENT(FSimpleDelegate, OnButtonClicked);

	SLATE_ARGUMENT_DEFAULT(bool, IsHyperlinkButton) { false };

	SLATE_ARGUMENT_DEFAULT(bool, UseSuccessButton) { false };

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

private:
	FReply OnButtonPressed();

private:
	TWeakPtr<SWindow> ContextWindow;
	FSimpleDelegate OnButtonClicked;
};
