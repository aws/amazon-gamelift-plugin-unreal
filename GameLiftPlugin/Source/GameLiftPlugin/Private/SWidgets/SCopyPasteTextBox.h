// Copyright 2024 Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"

class SWindow;

class SCopyPasteTextBox : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SCopyPasteTextBox) {}
	SLATE_ARGUMENT(TWeakPtr<SWindow>, ContextWindow)
	SLATE_ARGUMENT(FText, Text)
	SLATE_END_ARGS()
public:
	void Construct(const FArguments& InArgs);
	void SetText(FText NewText);
	static TSharedRef<SCopyPasteTextBox> CastToSharedRef(TSharedPtr<SWidget> WidgetToCast)
	{
		return StaticCastSharedRef<SCopyPasteTextBox>(WidgetToCast.ToSharedRef());
	}
private:
	TWeakPtr<SWindow> ContextWindow;
	TSharedPtr<STextBlock> TextBlock;
	FText Text;
	FReply OnClicked();

};