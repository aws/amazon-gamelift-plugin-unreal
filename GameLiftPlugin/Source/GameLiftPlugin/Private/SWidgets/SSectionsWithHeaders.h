// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include <Widgets/SBoxPanel.h>

// Display widgets grouped into expandable sections with headers
class SSectionsWithHeaders : public SHorizontalBox
{
public:
	struct FSectionInfo
	{
		FText HeaderTitle;
		TSharedPtr<SWidget> Body;
		bool IsCollapsed = false;
	};

	void Construct(const FArguments& InArgs);

	void AddSection(const FText& InHeaderTitle, TSharedRef<SWidget> InBodyContent, bool InCollapsed = false);
	void AddSection(const FSectionInfo& SectionInfo);

private:
	TSharedRef<SWidget> CreateExpandableArea(const FText& InHeaderTitle,
		TSharedRef<SWidget> InBodyContent, bool InCollapsed);

	// Vertical layout widget that holds the added sections
	TSharedPtr<SVerticalBox> VerticalContainer;
};
