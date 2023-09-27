// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"

class SWindow;
class SEditableTextBox;
class STextStatus;

// Display an editable text box for IP address.
class SIPAddressTextBox : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SIPAddressTextBox) {}

	SLATE_ARGUMENT(TWeakPtr<SWindow>, ContextWindow)

	SLATE_ARGUMENT_DEFAULT(FText, HintText) { FText::GetEmpty() };

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

	FString GetAddress() const;
	void SetAddress(const FString& NewAddress);
	bool IsAddressValid();

	static void FormatAddressForDisplay(FString& SourceAddress);
	
private:
	// The Tick and callback functions are used for tracking if users are editing the address.
	// By doing this, we can show the address as 'XX . XX . XX . XX' and can convert it back to 'XX.XX.XX.XX' when needed.
	void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);

	void OnAddressTextCommitted(const FText& SourceText, ETextCommit::Type CommitType);
	void OnAddressTextChanged(const FText& SourceText);
	void OnEnterKeyboardFocus();

private:
	TWeakPtr<SWindow> ContextWindow;

	TSharedPtr<SEditableTextBox> AddressTextBox;

	TSharedPtr<STextStatus> StatusIcon;

	bool bIsKeyboardFocused = false;
};
