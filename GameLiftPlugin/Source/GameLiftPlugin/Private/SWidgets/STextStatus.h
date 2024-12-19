// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"

#include "GameLiftPluginConstants.h"

class SWindow;

// Display status in text with optional status icons.
class STextStatus : public SCompoundWidget
{
public:
	enum class EIconState : int32
	{
		Inactive,
		Success,
		Error,
		Loading
	};

	SLATE_BEGIN_ARGS(STextStatus) {}
	
	SLATE_ARGUMENT(TWeakPtr<SWindow>, ContextWindow)

	SLATE_ATTRIBUTE(FText, StatusText)

	SLATE_ARGUMENT_DEFAULT(EIconState, IconState) { EIconState::Inactive };

	SLATE_ARGUMENT_DEFAULT(FName, StatusTextStyle) { Style::Text::kFieldMedium };

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);
	void SetIconState(EIconState IconState);
	void SetStatusText(const FText& StatusText);
	void SetStatusTextColor(const FSlateColor& StatusColor);
	void SetState(EIconState IconState, const FText& StatusText, FName Color = FName());

	int32 GetIconStateAsInt() const;
	FName GetIconColor();

private:
	TWeakPtr<SWindow> ContextWindow;
	TSharedPtr<STextBlock> StatusTextBlock;

	EIconState CurrentIconState = EIconState::Inactive;
};
