// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"

#include "Types/FTextIntPair.h"

class STextBlock;
class SWindow;

DECLARE_DELEGATE_OneParam(FOnBuildSelectionList, TArray<FTextIntPair>&);

DECLARE_DELEGATE_TwoParams(FOnItemSelected, int, const FTextIntPair&);

// Display a selection combo box that provides a drop-down menu.
class SSelectionComboBox : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SSelectionComboBox) {}
	
	SLATE_ARGUMENT(TWeakPtr<SWindow>, ContextWindow)

	SLATE_ARGUMENT(FText, UnselectedText)

	SLATE_ARGUMENT_DEFAULT(bool, HideDescription) { false };

	SLATE_EVENT(FOnBuildSelectionList, OnListBuilding)

	SLATE_EVENT(FOnItemSelected, OnItemSelected)

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

	int GetSelectedId() const;
	FText GetSelectedName() const;
	FTextIntPair GetSelectedPair() const;

	void SetSelectedId(int SelectionId);
	void SetSelectedByName(const FText& Name);
	void ClearSelection();
	bool IsCurrentSelectionValid() const;
	void SetUnselectedText(const FText& InUnselectedText);

	void RequestToRebuildList();	

	static TSharedRef<SSelectionComboBox> CastToSharedRef(TSharedPtr<SWidget> WidgetToCast)
	{
		return StaticCastSharedRef<SSelectionComboBox>(WidgetToCast.ToSharedRef());
	}

private:
	TSharedRef<SWidget> OnGetMenuContent();
	void ChangeCurrentSelectionId(int SelectionId);
	void UpdateUnselectedTextStyle();

private:
	TWeakPtr<SWindow> ContextWindow;
	FText UnselectedText;
	FOnBuildSelectionList OnListBuilding;
	FOnItemSelected OnItemSelected;
	
	TSharedPtr<STextBlock> SelectionTextBlock;
	TArray<FTextIntPair> ListForSelection;

	static constexpr int kUnassignedSelectionId = -1;
	int CurrentSelected = 0;

	bool HideDescription;
};
