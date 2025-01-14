// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"

#include "GameLiftPluginConstants.h"

class SWindow;

// Display a named row with a custom widget (text, button, input box) in the secondary column.
class SNamedRow : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SNamedRow) {}
	
	SLATE_ARGUMENT(TWeakPtr<SWindow>, ContextWindow)

	SLATE_ARGUMENT_DEFAULT(FText, NameText) { FText() };

	SLATE_ARGUMENT_DEFAULT(FText, NameTooltipText) { FText() };

	SLATE_ARGUMENT_DEFAULT(TSharedPtr<SWidget>, RowWidget) { nullptr };

	SLATE_ARGUMENT_DEFAULT(float, PrimaryColumnWidthOverride) { Style::KPrimaryWidthOverride };

	SLATE_ARGUMENT_DEFAULT(float, SecondaryColumnWidthOverride) { Style::kSecondaryWidthOverride };

	// Adding a left padding for some widgets (eg. text blocks) to make alignment look better.
	SLATE_ARGUMENT_DEFAULT(bool, SecondaryColumnLeftPadding) { false };

	// Let the first column vertically align on top
	SLATE_ARGUMENT_DEFAULT(bool, FirstColumnVAlignTop) { false };

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

	TSharedRef<SWidget> GetRowWidget();

private:
	TWeakPtr<SWindow> ContextWindow;

	TSharedPtr<SWidget> RowWidget;
};
