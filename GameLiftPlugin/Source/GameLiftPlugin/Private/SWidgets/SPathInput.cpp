// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SPathInput.h"

#include "Fonts/SlateFontInfo.h"
#include "Misc/Paths.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SUniformGridPanel.h"
#include "Widgets/Text/STextBlock.h"
#include "EditorStyleSet.h"
#include "Styling/CoreStyle.h"
#include "DetailLayoutBuilder.h"

#include "EditorDirectories.h"
#include "Settings/EditorSettings.h"
#include "IDesktopPlatform.h"
#include "DesktopPlatformModule.h"
#include "EditorStyleSet.h"

#include "Interfaces/IMainFrameModule.h"

#include "GameLiftPluginConstants.h"
#include "GameLiftPluginStyle.h"

#define LOCTEXT_NAMESPACE "GL_SPathInput"

void SPathInput::Construct(const FArguments& InArgs)
{
	ContextWindow = InArgs._ContextWindow;
	FileTypes = InArgs._FileTypes;
	Title = InArgs._Title;
	OnPathUpdated = InArgs._OnPathUpdated;
	ButtonVisibility = InArgs._ButtonVisibility;
	IsFileSelection = InArgs._IsFileSelection;

	const FMargin SpaceBeforeButton = FMargin(2, 0, 0, 0);

	ChildSlot
	[
		SNew(SBox)
		.VAlign(VAlign_Center)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Fill)
			[
				SAssignNew(EditableTextBox, SEditableTextBox)
				.Style(FGameLiftPluginStyle::Get(), Style::EditableTextBox::kField)
				.HintText(InArgs._PathHint)
				.IsReadOnly(false)
				.Text_Raw(this, &SPathInput::GetSelectedPath)
				.OnTextCommitted_Lambda([&](const FText& NewText, ETextCommit::Type CommitInfo)
				{
					SelectedPath = NewText;
					OnPathUpdated.ExecuteIfBound(SelectedPath.ToString());
				})
				.ToolTipText_Raw(this, &SPathInput::GetSelectedPath)
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center).HAlign(HAlign_Center)
			.Padding(SpaceBeforeButton)
			[
				SAssignNew(FolderOpenButton, SButton)
				.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kFlatButtonStyleName)
				.OnClicked(this, &SPathInput::OnBrowseToFileClicked)
				.Visibility(ButtonVisibility)
				.Content()
				[
					SNew(SImage)
					.Image(FGameLiftPluginStyle::Get().GetBrush(Style::Brush::kFolderOpenIconName))
				]
			]
		]
	];
}

void SPathInput::SetSelectedPath(const FText& Path)
{
	SelectedPath = Path;
	EditableTextBox->SetText(SelectedPath);
	OnPathUpdated.ExecuteIfBound(SelectedPath.ToString());
}

void SPathInput::SetSelectedPath(const FString& Path)
{
	SetSelectedPath(FText::FromString(Path));	
}

FText SPathInput::GetSelectedPath() const
{
	return SelectedPath;
}

const FText& SPathInput::GetSelectedPathRef() const
{
	return SelectedPath;
}

EVisibility SPathInput::GetVisibility() const
{
	return ButtonVisibility;
}

void SPathInput::SetReadonly(bool Readonly)
{
	EditableTextBox->SetIsReadOnly(Readonly);
	FolderOpenButton->SetEnabled(!Readonly);
}

FReply SPathInput::OnBrowseToFileClicked()
{
	FString Path;
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();

	if (DesktopPlatform != nullptr)
	{
		void* ParentWindowWindowHandle = nullptr;
		IMainFrameModule& MainFrameModule = FModuleManager::LoadModuleChecked<IMainFrameModule>(TEXT("MainFrame"));
		const TSharedPtr<SWindow>& MainFrameParentWindow = MainFrameModule.GetParentWindow();

		if (MainFrameParentWindow.IsValid() && MainFrameParentWindow->GetNativeWindow().IsValid())
		{
			ParentWindowWindowHandle = MainFrameParentWindow->GetNativeWindow()->GetOSWindowHandle();
		}

		ensure(ParentWindowWindowHandle != nullptr);

		if (IsFileSelection)
		{
			auto DefaultPath = FPaths::GetPath(SelectedPath.ToString());
			TArray<FString> OpenedFilenames;
			bool IsOpened = DesktopPlatform->OpenFileDialog(
				ParentWindowWindowHandle,
				Title.ToString(),
				DefaultPath,
				SelectedPath.ToString(),
				*FileTypes,
				EFileDialogFlags::None,
				OpenedFilenames
			);

			if (IsOpened && OpenedFilenames.Num() > 0)
			{
				Path = OpenedFilenames[0];
			}
		}
		else
		{
			FString OpenedDirPath;

			bool IsOpened = DesktopPlatform->OpenDirectoryDialog(
				ParentWindowWindowHandle,
				Title.ToString(),
				SelectedPath.ToString(),
				OpenedDirPath
			);

			if (IsOpened)
			{
				Path = OpenedDirPath;
			}
		}
	}

	if (!Path.IsEmpty())
	{
		if (FPaths::IsRelative(Path))
		{
			Path = FPaths::ConvertRelativePathToFull(Path);
		}

		SelectedPath = FText::FromString(Path);
		EditableTextBox->SetText(SelectedPath);
		OnPathUpdated.ExecuteIfBound(SelectedPath.ToString());
	}

	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE
