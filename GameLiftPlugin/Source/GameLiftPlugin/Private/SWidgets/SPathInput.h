// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"

#include "GameLiftPluginConstants.h"

class SWindow;

DECLARE_DELEGATE_OneParam(FOnPathUpdated, const FString&);

class SPathInput : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SPathInput) {}

	SLATE_ARGUMENT(TWeakPtr<SWindow>, ContextWindow)

	SLATE_ARGUMENT(FString, FileTypes)

	SLATE_ARGUMENT(FText, Title)

	SLATE_ARGUMENT_DEFAULT(FText, PathHint) { FText::GetEmpty() };

	SLATE_ARGUMENT_DEFAULT(bool, IsFileSelection) { true };

	SLATE_EVENT(FOnPathUpdated, OnPathUpdated)

	SLATE_ARGUMENT_DEFAULT(EVisibility, ButtonVisibility) { EVisibility::Visible };

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

	void SetSelectedPath(const FString& Path);
	void SetSelectedPath(const FText& Path);

	FText GetSelectedPath() const;
	const FText& GetSelectedPathRef() const;
	EVisibility GetVisibility() const;

	void SetReadonly(bool Readonly);

private:
	FReply OnBrowseToFileClicked();

private:
	TWeakPtr<SWindow> ContextWindow;
	FText Title;
	FString FileTypes;
	FText SelectedPath;
	FOnPathUpdated OnPathUpdated;
	EVisibility ButtonVisibility;
	TSharedPtr<SEditableTextBox> EditableTextBox;
	TSharedPtr<SButton> FolderOpenButton;
	bool IsFileSelection;
};
