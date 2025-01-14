// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class SWindow;

class SProgressBar : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SProgressBar) {}

	SLATE_ARGUMENT(TWeakPtr<SWindow>, ContextWindow)

	SLATE_ARGUMENT_DEFAULT(bool, IsLastComponent) { false };

	SLATE_END_ARGS()

public:
	enum class EProgressBarUIState
	{
		NotStart,
		InProgress,
		ProgressComplete,
		ProgressWarning,
		ProgressError
	};
	void Construct(const FArguments& InArgs);
	void ChangeProgressBarUIState(EProgressBarUIState InState);
	void SetAsLastComponent(bool IsLast);

private:
	int32 ProgressUIStateToInt(EProgressBarUIState State)
	{
		return (int32)State;
	};
	TSharedRef<SWidget> CreateProgressBarUI(const char* ProgressIcon, const char* BarIcon);

private:
	TWeakPtr<SWindow> ContextWindow;
	TSharedPtr<SWidgetSwitcher> ProgressBarWidgetSwitcher;
	bool IsLastComponent;
};
