// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SSectionsWithProgressBars.h"
#include "GameLiftPluginConstants.h"
#include "GameLiftPluginStyle.h"

#define LOCTEXT_NAMESPACE "SSectionsWithProgressBars"

void SSectionsWithProgressBars::Construct(const FArguments& InArgs)
{
	ChildSlot
		[
			SAssignNew(VerticalContainer, SVerticalBox)
		];
}

void SSectionsWithProgressBars::AddSection(TSharedRef<SSectionStep> CurrentSection)
{
	bool IsFirstSection = SectionList.IsEmpty();
	CurrentSection->SetLastSection(true);
	if (!IsFirstSection)
	{
		TSharedRef<SSectionStep> PreviousSection = SectionList.Last();
		PreviousSection->SetLastSection(false);
		PreviousSection->SetNextSection(CurrentSection);
	}

	SectionList.Add(CurrentSection);

	VerticalContainer->AddSlot().AutoHeight()
		[
			CurrentSection
		];
}

void SSectionsWithProgressBars::ResetUI()
{
	for (int i = 0; i < SectionList.Num(); i++)
	{
		TSharedRef<SSectionStep> Section = SectionList[i];
		if (i != 0)
		{
			Section->ResetAndCollapseSection();
		}
	}
}

#undef LOCTEXT_NAMESPACE