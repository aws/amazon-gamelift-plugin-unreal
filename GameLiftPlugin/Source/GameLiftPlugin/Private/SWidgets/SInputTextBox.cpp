// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SInputTextBox.h"

#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"

#include "GameLiftPluginConstants.h"
#include "GameLiftPluginStyle.h"

#define LOCTEXT_NAMESPACE "GL_SInputTextBox"

void SInputTextBox::Construct(const FArguments& InArgs)
{
	ContextWindow = InArgs._ContextWindow;

	TSharedPtr<SBox> EditBox;

	TSharedPtr<SHorizontalBox> HorizontalBox = SNew(SHorizontalBox);
	HorizontalBox->AddSlot()
		.HAlign(HAlign_Fill)
		[
			SAssignNew(EditBox, SBox)
			.VAlign(VAlign_Center)
			[
				SAssignNew(EditableTextBox, SEditableTextBox)
				.IsReadOnly(false)
				.Style(FGameLiftPluginStyle::Get(), Style::EditableTextBox::kField)
				.IsPassword_Lambda([&]()
				{
					return IsTextHidden;
				})
			]
		];

	if (InArgs._ButtonVisibility == EVisibility::Visible)
	{
		HorizontalBox->AddSlot()
			.AutoWidth()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Center)
			.Padding(SPadding::Left)
			[
				SNew(SBox)
				.WidthOverride(Style::Button::kVisibilityButtonWidth)
				[
					SNew(SButton)
					.Text(this, &SInputTextBox::GetButtonText)
					.OnClicked(this, &SInputTextBox::OnHideClicked)
					.Visibility(InArgs._ButtonVisibility)
					.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kNormalButtonStyleName)
					.HAlign(HAlign_Center)
					.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kButtonNormal)
				]
			];
	}
	
	ChildSlot
	[
		HorizontalBox.ToSharedRef()
	];

	if (InArgs._ButtonVisibility == EVisibility::Hidden)
	{
		IsTextHidden = false;
	}
}

FReply SInputTextBox::OnHideClicked()
{
	IsTextHidden = !IsTextHidden;
	return FReply::Handled();
}

FText SInputTextBox::GetButtonText() const
{
	return IsTextHidden 
		? NSLOCTEXT("SInputTextBox", "ShowText", "Show")
		: NSLOCTEXT("SInputTextBox", "HideText", "Hide");
}

FText SInputTextBox::GetInputText() const
{
	return EditableTextBox->GetText();
}

void SInputTextBox::SetInputText(const FText& NewText)
{
	EditableTextBox->SetText(NewText);
}

void SInputTextBox::SetInputText(const FString& NewText)
{
	EditableTextBox->SetText(FText::FromString(NewText));
}

#undef LOCTEXT_NAMESPACE
