// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"

class SWindow;

class SOnlineHyperlink : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SOnlineHyperlink) {}
	
	SLATE_ARGUMENT(TWeakPtr<SWindow>, ContextWindow)

	SLATE_ATTRIBUTE(FString, Link)

	SLATE_ARGUMENT(FText, Text)

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

private:
	void OnClicked();

private:
	TWeakPtr<SWindow> ContextWindow;
	TAttribute<FString> Link;
};
