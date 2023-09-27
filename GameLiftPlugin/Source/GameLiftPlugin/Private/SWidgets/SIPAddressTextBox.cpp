// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SIPAddressTextBox.h"

#include "Internationalization/Regex.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"

#include "GameLiftPluginConstants.h"
#include "GameLiftPluginStyle.h"

#include "SWidgets/STextStatus.h"

#define LOCTEXT_NAMESPACE "GL_SIPAddressTextBox"

void SIPAddressTextBox::Construct(const FArguments& InArgs)
{
	ContextWindow = InArgs._ContextWindow;

	const int AddressInputMinWidth = 60;
	const FMargin SpaceBeforeIcon = FMargin(6, 0, 0, 0);

	ChildSlot
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SAssignNew(AddressTextBox, SEditableTextBox)
			.HintText(InArgs._HintText)
			.MinDesiredWidth(AddressInputMinWidth)
			.OnTextCommitted_Raw(this, &SIPAddressTextBox::OnAddressTextCommitted)
			.OnTextChanged_Raw(this, &SIPAddressTextBox::OnAddressTextChanged)
			.Justification(ETextJustify::Center)
		]
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(SpaceBeforeIcon)
		.VAlign(VAlign_Center)
		[
			SAssignNew(StatusIcon, STextStatus)
		]
	];

	OnAddressTextChanged(FText::FromString(GetAddress()));
}

FString SIPAddressTextBox::GetAddress() const
{
	FString AddressString = AddressTextBox->GetText().ToString();
	AddressString.RemoveSpacesInline();

	return AddressString;
}

void SIPAddressTextBox::SetAddress(const FString& NewAddress)
{
	FString AddressCopy = NewAddress;
	FormatAddressForDisplay(AddressCopy);
	AddressTextBox->SetText(FText::FromString(AddressCopy));
}

bool SIPAddressTextBox::IsAddressValid()
{
	static const FRegexPattern AddressRegexPattern(Menu::DeployAnywhere::kIPv4ValidationRegex);
	
	FString TrimmedAddress = AddressTextBox->GetText().ToString();
	TrimmedAddress.RemoveSpacesInline();

	FRegexMatcher RegexMatcher(AddressRegexPattern, TrimmedAddress);
	return RegexMatcher.FindNext();
}

void SIPAddressTextBox::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);

	bool bIsFocused = AddressTextBox->HasKeyboardFocus();

	if (!bIsKeyboardFocused && bIsFocused)
	{
		OnEnterKeyboardFocus();
	}

	bIsKeyboardFocused = bIsFocused;
}

void SIPAddressTextBox::OnAddressTextCommitted(const FText& SourceText, ETextCommit::Type CommitType)
{
	if (IsAddressValid())
	{
		FString AddressString = SourceText.ToString();
		
		FormatAddressForDisplay(AddressString);

		AddressTextBox->SetText(FText::FromString(AddressString));
	}
}

void SIPAddressTextBox::OnAddressTextChanged(const FText& SourceText)
{
	if (IsAddressValid())
	{
		StatusIcon->SetIconState(STextStatus::EIconState::Success);
	}
	else
	{
		StatusIcon->SetIconState(STextStatus::EIconState::Error);
	}
}

void SIPAddressTextBox::OnEnterKeyboardFocus()
{
	FString NewString = AddressTextBox->GetText().ToString();
	NewString.RemoveSpacesInline();

	AddressTextBox->SetText(FText::FromString(NewString));
}

void SIPAddressTextBox::FormatAddressForDisplay(FString& SourceAddress)
{
	SourceAddress.RemoveSpacesInline();
	SourceAddress = SourceAddress.Replace(TEXT("."), TEXT(" . "));
}

#undef LOCTEXT_NAMESPACE
