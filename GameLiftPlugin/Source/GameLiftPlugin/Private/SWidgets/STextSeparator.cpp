// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "STextSeparator.h"

#include "GameLiftPluginConstants.h"

#define LOCTEXT_NAMESPACE "GL_SHorizontalSeparator"

void STextSeparator::Construct(const FArguments& InArgs)
{
	ContextWindow = InArgs._ContextWindow;

	ChildSlot
	[
		SNew(STextBlock)
		.Text(FText::FromString(InArgs._Separator))
		.Justification(ETextJustify::Center)
		.Margin(SPadding::Left2x_Right2x)
	];
}

#undef LOCTEXT_NAMESPACE
