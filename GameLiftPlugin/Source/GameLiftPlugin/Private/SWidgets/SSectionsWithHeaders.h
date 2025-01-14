// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include <Widgets/SBoxPanel.h>

// Display widgets grouped into expandable sections with headers
class SSectionsWithHeaders : public SHorizontalBox
{
	SLATE_BEGIN_ARGS(SSectionsWithHeaders) { }

	SLATE_ARGUMENT_DEFAULT(bool, ShowDefaultColor) { false };

	SLATE_END_ARGS()

public:
	struct FSectionInfo
	{
		FText HeaderTitle;
		TSharedPtr<SWidget> Body;
		bool IsCollapsed = false;
	};

	void Construct(const FArguments& InArgs);

	void AddSection(const FText& InHeaderTitle, TSharedRef<SWidget> InBodyContent, bool InCollapsed = false);
	void ExpandSection(const FString& HeaderTitle);
	void AddSection(const FSectionInfo& SectionInfo);

private:
	TSharedRef<SWidget> CreateExpandableArea(const FText& InHeaderTitle,
	TSharedRef<SWidget> InBodyContent, bool InCollapsed);
	TMap<FString, TSharedRef<SExpandableArea>> ExpandableAreaMap;

	// Vertical layout widget that holds the added sections
	TSharedPtr<SVerticalBox> VerticalContainer;
	bool ShowDefaultColor;
};
