// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SOnlineHyperlink.h"

#include <Widgets/Input/SHyperlink.h>
#include <Widgets/SBoxPanel.h>
#include <Widgets/Text/STextBlock.h>

#include "GameLiftPluginConstants.h"
#include "GameLiftPluginStyle.h"

#include "Utils/Misc.h"

#define LOCTEXT_NAMESPACE "GL_SOnlineHyperlink"

void SOnlineHyperlink::Construct(const FArguments& InArgs)
{
	ContextWindow = InArgs._ContextWindow;
	Link = InArgs._Link;

	ChildSlot
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		[
			SNew(SHyperlink)
			.Text(InArgs._Text)
			.Style(FGameLiftPluginStyle::Get(), Style::kLinkStyleName)
			.OnNavigate(this, &SOnlineHyperlink::OnClicked)
		]
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(SPadding::Left)
		.VAlign(VAlign_Center)
		[
			SNew(SBox)
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Center)
			.WidthOverride(Style::kLinkIconSize)
			.HeightOverride(Style::kLinkIconSize)
			[
				SNew(SImage)
				.Image(FGameLiftPluginStyle::Get().GetBrush(Style::Brush::kExternalLinkIconName))
			]
		]
	];	
}

void SOnlineHyperlink::OnClicked()
{
	FPlatformProcess::LaunchURL(*(Link.Get()), nullptr, nullptr);
}

#undef LOCTEXT_NAMESPACE
