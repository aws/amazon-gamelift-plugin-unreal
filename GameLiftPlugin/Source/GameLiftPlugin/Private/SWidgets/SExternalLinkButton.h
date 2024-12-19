// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"

class SWindow;

class SExternalLinkButton : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SExternalLinkButton) {}

	SLATE_ARGUMENT(TWeakPtr<SWindow>, ContextWindow)

	SLATE_ARGUMENT_DEFAULT(FText, ButtonTooltipText) { FText() };

	// Link to be opened
	SLATE_ATTRIBUTE(FString, Link)

	// Open the file in default application
	SLATE_ATTRIBUTE(FString, FilePath)

	// Open the folder in file explorer
	SLATE_ATTRIBUTE(FString, FolderPath)

	SLATE_ARGUMENT(FText, Text)

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

private:
	FReply OnClicked();

private:
	TWeakPtr<SWindow> ContextWindow;
	TAttribute<FString> Link;
	TAttribute<FString> FilePath;
	TAttribute<FString> FolderPath;
};
