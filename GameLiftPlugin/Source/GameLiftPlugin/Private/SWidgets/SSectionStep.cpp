// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SSectionStep.h"

#include "Widgets/Text/SRichTextBlock.h"

#include "GameLiftPluginConstants.h"
#include "GameLiftPluginStyle.h"

#define LOCTEXT_NAMESPACE "SSectionStep"

void SSectionStep::Construct(const FArguments& InArgs)
{
	HeaderTitle = InArgs._HeaderTitle;
	HeaderDescription = InArgs._HeaderDescription;

	ChildSlot
		[
			SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.Padding(SPadding::Right2x)
				.AutoWidth()
				[
					SAssignNew(ProgressBar, SProgressBar)
				]
				+ SHorizontalBox::Slot()
				.Padding(SPadding::Bottom5x + SPadding::Right2x)
				.FillWidth(1.0f)
				[
					SAssignNew(ExpandableSection, SExpandableSection)
						.HeaderContent()
						[
							SNew(SVerticalBox)
								+ SVerticalBox::Slot()
								.AutoHeight()
								.Padding(SPadding::SectionTitleTopPadding)
								[
									SNew(STextBlock)
										.Text(HeaderTitle)
										.AutoWrapText(true)
										.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kTitleStyleName)
								]
								+ SVerticalBox::Slot()
								.AutoHeight()
								.Padding(SPadding::Top3x)
								[
									SNew(SRichTextBlock)
										.Text(HeaderDescription)
										.AutoWrapText(true)
										.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kParagraph)
								]
						]
						.BodyContent()
						[
							SNew(SBox)
								.Padding(SPadding::Top2x)
								[
									InArgs._BodyContent.Widget
								]
						]
				]
		];
}

void SSectionStep::SetProgressBarState(SProgressBar::EProgressBarUIState State)
{
	ProgressBar->ChangeProgressBarUIState(State);
}

void SSectionStep::SetExpansion(bool IsExpanded)
{
	ExpandableSection->SetExpanded(IsExpanded);
}

void SSectionStep::SetLastSection(bool IsLast)
{
	ProgressBar->SetAsLastComponent(IsLast);
}

void SSectionStep::SetNextSection(TSharedPtr<SSectionStep> Section)
{
	NextSection = Section;
}

void SSectionStep::StartNextSection()
{
	if (NextSection.IsValid())
	{
		NextSection->StartSection();
		NextSection->SetExpansion(true);
	}
}

void SSectionStep::ResetAndCollapseSection()
{
	SetExpansion(false);
	ProgressBar->ChangeProgressBarUIState(SProgressBar::EProgressBarUIState::NotStart);
	StartSection();
}

void SSectionStep::ResetAndCollapseNextSections()
{
	StartSection();
	CollapseNextSections();
}

void SSectionStep::CollapseNextSections()
{
	ProgressBar->ChangeProgressBarUIState(SProgressBar::EProgressBarUIState::NotStart);

	if (NextSection.IsValid())
	{
		NextSection->ResetAndCollapseSection();
		NextSection->ResetAndCollapseNextSections();
	}
}

#undef LOCTEXT_NAMESPACE