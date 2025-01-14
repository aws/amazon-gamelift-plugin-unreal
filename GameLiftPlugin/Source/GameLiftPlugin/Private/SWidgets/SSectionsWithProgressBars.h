// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "SWidgets/SProgressBar.h"
#include "SWidgets/SExpandableSection.h"
#include "SWidgets/SSectionStep.h"

class SSectionStep;

// Display widgets grouped into expandable sections with progress bars
class SSectionsWithProgressBars : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SSectionsWithProgressBars) { }

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);
	void ResetUI();

	void AddSection(TSharedRef<SSectionStep> Section);

private: 
	TArray<TSharedRef<SSectionStep>> SectionList;
	TSharedPtr<SVerticalBox> VerticalContainer;
};
