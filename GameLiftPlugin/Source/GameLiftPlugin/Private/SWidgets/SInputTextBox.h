// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"

class SWindow;
class SEditableTextBox;

// Display an editable text box with an optional visibility button to decide whether the text should be hidden.
class SInputTextBox : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SInputTextBox) {}

	SLATE_ARGUMENT(TWeakPtr<SWindow>, ContextWindow)

	SLATE_ARGUMENT_DEFAULT(EVisibility, ButtonVisibility) { EVisibility::Visible };

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

	FText GetInputText() const;
	void SetInputText(const FText& NewText);
	void SetInputText(const FString& NewText);

	static TSharedRef<SInputTextBox> CastToSharedRef(TSharedPtr<SWidget> WidgetToCast)
	{
		return StaticCastSharedRef<SInputTextBox>(WidgetToCast.ToSharedRef());
	}

private:
	FReply OnHideClicked();
	FText GetButtonText() const;

private:
	TWeakPtr<SWindow> ContextWindow;
	TSharedPtr<SEditableTextBox> EditableTextBox;
	bool IsTextHidden = true;
};
