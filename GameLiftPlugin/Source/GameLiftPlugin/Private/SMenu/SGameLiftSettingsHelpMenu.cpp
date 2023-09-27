// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SGameLiftSettingsHelpMenu.h"

#include "GameLiftPluginConstants.h"
#include "SWidgets/SOnlineHyperlink.h"

#define LOCTEXT_NAMESPACE "SGameLiftSettingsHelpMenu"

void SGameLiftSettingsHelpMenu::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		MakeHelpWidget()
	];
}

TSharedRef<SWidget> SGameLiftSettingsHelpMenu::MakeHelpWidget() const
{
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.Padding(SPadding::Top2x_Bottom)
		.AutoHeight()
		.HAlign(HAlign_Left)
		[
			SNew(SOnlineHyperlink)
			.Text(Settings::Help::kHelpGameLiftDocumentationLinkText)
			.Link(Url::kGameLiftDocumentationUrl)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top_Bottom)
		.HAlign(HAlign_Left)
		[
			SNew(SOnlineHyperlink)
			.Text(Settings::Help::kHelpAwsGameTechForumLinkText)
			.Link(Url::kGameTechForumUrl)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top_Bottom)
		.HAlign(HAlign_Left)
		[
			SNew(SOnlineHyperlink)
			.Text(Settings::Help::kHelpTroubleshootAccountAccessIssuesLinkText)
			.Link(Url::kTroubleshootAccountAccessIssueUrl)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top_Bottom)
		.HAlign(HAlign_Left)
		[
			SNew(SOnlineHyperlink)
			.Text(Settings::Help::kHelpAboutAmazonGameLiftLinkText)
			.Link(Url::kAboutGameLiftUrl)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top_Bottom)
		.HAlign(HAlign_Left)
		[
			SNew(SOnlineHyperlink)
			.Text(Settings::Help::kHelpAwsForGamesBlogLinkText)
			.Link(Url::kAwsForGamesBlogUrl)
		]

		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top_Bottom)
		.HAlign(HAlign_Left)
		[
			SNew(SOnlineHyperlink)
			.Text(Settings::Help::kHelpAwsForGamesLinkText)
			.Link(Url::kAwsForGamesUrl)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top_Bottom)
		.HAlign(HAlign_Left)
		[
			SNew(SOnlineHyperlink)
			.Text(Settings::Help::kHelpReportIssuesLinkText)
			.Link(Url::kReportIssuesUrl)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(SPadding::Top_Bottom2x + SPadding::Bottom)
		.HAlign(HAlign_Left)
		[
			SNew(SOnlineHyperlink)
			.Text(Settings::Help::kHelpContributingGuidelinesLinkText)
			.Link(Url::kContributingGuidelinesUrl)
		]
	;
}

#undef LOCTEXT_NAMESPACE
