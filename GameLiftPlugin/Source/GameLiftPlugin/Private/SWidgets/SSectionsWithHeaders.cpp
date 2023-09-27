// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SSectionsWithHeaders.h"

#include "GameLiftPluginConstants.h"
#include "GameLiftPluginStyle.h"

#include <Widgets/Layout/SExpandableArea.h>

void SSectionsWithHeaders::Construct(const FArguments& InArgs)
{
	AddSlot().Padding(SPadding::Left2x_Right2x).FillWidth(1)
		[
			SAssignNew(VerticalContainer, SVerticalBox)
		];
}

void SSectionsWithHeaders::AddSection(const FText& InHeaderTitle, TSharedRef<SWidget> InBodyContent, bool InCollapsed)
{
	VerticalContainer->AddSlot().AutoHeight().Padding(SPadding::Top_Bottom)
		[
			CreateExpandableArea(InHeaderTitle, InBodyContent, InCollapsed)
		];
}

void SSectionsWithHeaders::AddSection(const FSectionInfo& SectionInfo)
{
	AddSection(SectionInfo.HeaderTitle, SectionInfo.Body.ToSharedRef(), SectionInfo.IsCollapsed);
}

TSharedRef<SWidget> SSectionsWithHeaders::CreateExpandableArea(const FText& InHeaderTitle,
	TSharedRef<SWidget> InBodyContent, bool InCollapsed)
{
	const FMargin ContentAreaLeftIndent = SPadding::Left * 6; // Make content area align with the header title

	return SNew(SExpandableArea)
		.AreaTitle(InHeaderTitle)
		.InitiallyCollapsed(InCollapsed)
		.HeaderPadding(SPadding::Left2x_Right2x + SPadding::Top_Bottom)
		.Padding(ContentAreaLeftIndent + SPadding::Right2x + SPadding::Top2x + SPadding::Bottom)
		.AreaTitleFont(FGameLiftPluginStyle::Get().GetFontStyle(Style::Text::kSectionHeaderFontStyleName))
		.BorderImage(FGameLiftPluginStyle::GetAppStyle().GetBrush("WhiteTexture"))
		.BodyBorderImage(FGameLiftPluginStyle::GetAppStyle().GetBrush("WhiteTexture"))
		.BorderBackgroundColor(FGameLiftPluginStyle::Get().GetSlateColor(Style::Color::kSectionHeaderBackground))
		.BodyBorderBackgroundColor(FGameLiftPluginStyle::Get().GetSlateColor(Style::Color::kPanelBackground))
		.BodyContent()
		[
			InBodyContent
		];
}
