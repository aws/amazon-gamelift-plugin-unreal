// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "STitleBlock.h"

#include "GameLiftPluginConstants.h"
#include "GameLiftPluginStyle.h"

#define LOCTEXT_NAMESPACE "GL_STitleBlock"

void STitleBlock::Construct(const FArguments& InArgs)
{
	ContextWindow = InArgs._ContextWindow;

	ChildSlot
	[
		SNew(STextBlock)
		.Text(InArgs._Text)
		.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kTitleStyleName)
	];
}

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "GL_SSubTitleBlock"

void SSubtitleBlock::Construct(const FArguments& InArgs)
{
	ContextWindow = InArgs._ContextWindow;

	ChildSlot
	[
		SNew(STextBlock)
		.Text(InArgs._Text)
		.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kSubtitleStyleName)
	];
}

#undef LOCTEXT_NAMESPACE
