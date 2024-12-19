// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "SWidgets/SProgressBar.h"
#include "SWidgets/SExpandableSection.h"

class SSectionStep : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SSectionStep) { }

	SLATE_ARGUMENT(FText, HeaderTitle)

	SLATE_ARGUMENT(FText, HeaderDescription)

	SLATE_NAMED_SLOT(FArguments, BodyContent)

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

	void SetProgressBarState(SProgressBar::EProgressBarUIState State);
	void SetExpansion(bool IsExpanded);
	void SetLastSection(bool IsLast);
	void SetNextSection(TSharedPtr<SSectionStep> Section);

	void ResetAndCollapseSection();
	void ResetAndCollapseNextSections();
	void CollapseNextSections();
	void StartNextSection();

protected:
	virtual void StartSection() = 0;
	
private:
	FText HeaderTitle;
	FText HeaderDescription;

	TSharedPtr<SProgressBar> ProgressBar;
	TSharedPtr<SExpandableSection> ExpandableSection;
	TSharedPtr<SSectionStep> NextSection;
};
