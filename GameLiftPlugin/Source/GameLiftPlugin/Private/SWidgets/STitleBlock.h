// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class SWindow;

class STitleBlock : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(STitleBlock) {}

	SLATE_ARGUMENT(TWeakPtr<SWindow>, ContextWindow)

	SLATE_ARGUMENT(FText, Text)

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

private:
	TWeakPtr<SWindow> ContextWindow;
};

class SSubtitleBlock : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SSubtitleBlock) {}

	SLATE_ARGUMENT(TWeakPtr<SWindow>, ContextWindow)

	SLATE_ARGUMENT(FText, Text)

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

private:
	TWeakPtr<SWindow> ContextWindow;
};
