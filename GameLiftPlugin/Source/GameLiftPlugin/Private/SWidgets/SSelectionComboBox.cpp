// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SSelectionComboBox.h"

#include "GameLiftPluginConstants.h"
#include "GameLiftPluginStyle.h"

#define LOCTEXT_NAMESPACE "GL_SSelectionComboBox"

void SSelectionComboBox::Construct(const FArguments& InArgs)
{
	ContextWindow = InArgs._ContextWindow;
	UnselectedText = InArgs._UnselectedText;
	OnListBuilding = InArgs._OnListBuilding;
	OnItemSelected = InArgs._OnItemSelected;
	HideDescription = InArgs._HideDescription;

	RequestToRebuildList();

	ChildSlot
		[
			SNew(SComboButton)
			.OnGetMenuContent_Raw(this, &SSelectionComboBox::OnGetMenuContent)
			.ContentPadding(FMargin(1.0f, 1.0f))
			.ButtonContent()
				[
					SAssignNew(SelectionTextBlock, STextBlock)
					.Text_Lambda([&]()
					{
						if (IsCurrentSelectionValid())
						{
							return ListForSelection[CurrentSelected].Text;
						}
						else
						{
							return UnselectedText;
						}
					})
				]
		];

	UpdateUnselectedTextStyle();
}

int SSelectionComboBox::GetSelectedId() const
{
	return CurrentSelected;
}

FText SSelectionComboBox::GetSelectedName() const
{
	return IsCurrentSelectionValid() ? ListForSelection[CurrentSelected].Text : FText::FromString("");
}

FTextIntPair SSelectionComboBox::GetSelectedPair() const
{
	return IsCurrentSelectionValid() ? ListForSelection[CurrentSelected] : FTextIntPair(FText::FromString(""), -1);
}

void SSelectionComboBox::SetSelectedId(int SelectionId)
{
	ChangeCurrentSelectionId(SelectionId);
}

void SSelectionComboBox::SetSelectedByName(const FText& Name)
{
	int NewSelected = kUnassignedSelectionId;
	for (int32 Index = 0; Index < ListForSelection.Num(); Index++)
	{
		if (ListForSelection[Index].Text.EqualTo(Name))
		{
			NewSelected = Index;
		}
	}

	ChangeCurrentSelectionId(NewSelected);
}

void SSelectionComboBox::ClearSelection()
{
	ChangeCurrentSelectionId(kUnassignedSelectionId);
}

bool SSelectionComboBox::IsCurrentSelectionValid() const
{
	return ListForSelection.IsValidIndex(CurrentSelected);
}

void SSelectionComboBox::SetUnselectedText(const FText& InUnselectedText)
{
	UnselectedText = InUnselectedText;
}

void SSelectionComboBox::RequestToRebuildList()
{
	ensure(OnListBuilding.IsBound());
	OnListBuilding.Execute(ListForSelection);
}

TSharedRef<SWidget> SSelectionComboBox::OnGetMenuContent()
{
	FMenuBuilder MenuBuilder(true, nullptr);

	for (int32 Index = 0; Index < ListForSelection.Num(); Index++)
	{
		const FTextIntPair& Selection = ListForSelection[Index];

		FUIAction MenuEntryAction(FExecuteAction::CreateLambda([this, Index, Selection]()
			{
				ChangeCurrentSelectionId(Index);
				OnItemSelected.ExecuteIfBound(Index, Selection);
			}));

		MenuBuilder.AddMenuEntry(MenuEntryAction, 
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
#if (ENGINE_MAJOR_VERSION == 4)
			.Padding(SPadding::Left2x)
#endif
			[
				SNew(STextBlock).Text(Selection.Text)
				.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kFieldMedium)
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(SPadding::Left2x)
			[
				SNew(STextBlock).Text(Selection.Description)
				.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kNoteItalic)
				.Visibility(HideDescription ? EVisibility::Collapsed : EVisibility::Visible)
			]
		);
	}

	return MenuBuilder.MakeWidget();
}

void SSelectionComboBox::ChangeCurrentSelectionId(int SelectionId)
{
	CurrentSelected = SelectionId;
	UpdateUnselectedTextStyle();
}

void SSelectionComboBox::UpdateUnselectedTextStyle()
{
	// Update text style
	const FTextBlockStyle& CurrentStyle = FGameLiftPluginStyle::Get().GetWidgetStyle<FTextBlockStyle>(
		IsCurrentSelectionValid() ? Style::Text::kField : Style::Text::kFieldItalic);
	SelectionTextBlock->SetTextStyle(&CurrentStyle);

}

#undef LOCTEXT_NAMESPACE
