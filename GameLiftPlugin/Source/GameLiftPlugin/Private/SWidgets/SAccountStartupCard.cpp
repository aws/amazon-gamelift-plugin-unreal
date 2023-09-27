// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SAccountStartupCard.h"

#include "SWidgets/SOnlineHyperlink.h"

#include "GameLiftPluginConstants.h"
#include "GameLiftPluginStyle.h"

#define LOCTEXT_NAMESPACE "GL_SAccountStartupCard"

void SAccountStartupCard::Construct(const FArguments& InArgs)
{
	ContextWindow = InArgs._ContextWindow;
	OnButtonClicked = InArgs._OnButtonClicked;

	int32 CardWidth = 300;
	int32 CardHeight = 190;
	int32 CardIconSize = 80;
	int32 CardBorderSize = 2;

	// Button
	TSharedPtr<SWidget> ButtonWidget;

	if (InArgs._IsHyperlinkButton)
	{
		SAssignNew(ButtonWidget, SButton)
			.ButtonStyle(FGameLiftPluginStyle::Get(), InArgs._UseSuccessButton ? Style::Button::kSuccessButtonStyleName : Style::Button::kNormalButtonStyleName)
			.OnClicked(this, &SAccountStartupCard::OnButtonPressed)
			.Content()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.Text(InArgs._ButtonText)
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(SPadding::Left)
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Center)
				[
					SNew(SBox)
					.WidthOverride(Style::kLinkIconSize)
					.HeightOverride(Style::kLinkIconSize)
					[
						SNew(SImage)
						.Image(FGameLiftPluginStyle::Get().GetBrush(Style::Brush::kExternalLinkIconName))
#if(ENGINE_MAJOR_VERSION == 4)
						.ColorAndOpacity(FColor::Black)
#endif
					]
				]
			];
	}
	else
	{
		SAssignNew(ButtonWidget, SButton)
			.Text(InArgs._ButtonText)
			.ButtonStyle(FGameLiftPluginStyle::Get(), InArgs._UseSuccessButton ? Style::Button::kSuccessButtonStyleName : Style::Button::kNormalButtonStyleName)
			.TextStyle(FGameLiftPluginStyle::Get(), InArgs._UseSuccessButton ? Style::Text::kButtonLight : Style::Text::kButtonNormal)
			.OnClicked(this, &SAccountStartupCard::OnButtonPressed);
	}

	// Link
	TSharedPtr<SWidget> BottomTextWidget;

	if (InArgs._LinkUrl.IsEmpty())
	{
		SAssignNew(BottomTextWidget, STextBlock)
			.Text(InArgs._LinkText)
			.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kNote);
	}
	else
	{
		SAssignNew(BottomTextWidget, SOnlineHyperlink)
			.Text(InArgs._LinkText)
			.Link(InArgs._LinkUrl);
	}

	ChildSlot
	[
		SNew(SBox)
		.WidthOverride(CardWidth)
		.HeightOverride(CardHeight)
		[
			SNew(SBorder)
			.BorderImage(FGameLiftPluginStyle::Get().GetBrush(Style::Brush::kBorderImageName))
			.BorderBackgroundColor(FColor::Black)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(CardBorderSize)
			[
				SNew(SBorder)
				.BorderImage(FGameLiftPluginStyle::Get().GetBrush(Style::Brush::kBorderImageName))
				.BorderBackgroundColor(FGameLiftPluginStyle::Get().GetSlateColor(Style::Color::kCardBackground))
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					.AutoHeight()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Top)
					.Padding(SPadding::Bottom)
					[
						SNew(SBox)
						.WidthOverride(CardIconSize)
						.HeightOverride(CardIconSize)
						[
							SNew(SImage)
							.Image(FGameLiftPluginStyle::Get().GetBrush(InArgs._Icon))
						]
					]
					+ SVerticalBox::Slot()
					.AutoHeight()
					.HAlign(HAlign_Center)
					.Padding(SPadding::Top_Bottom)
					[
						SNew(STextBlock)
						.Text(InArgs._DescriptionText)
					]
					+ SVerticalBox::Slot()
					.AutoHeight()
					.HAlign(HAlign_Center)
					.Padding(SPadding::Top_Bottom)
					[
						ButtonWidget.ToSharedRef()
					]
					+ SVerticalBox::Slot()
					.AutoHeight()
					.HAlign(HAlign_Center)
					.Padding(SPadding::Top + SPadding::Bottom2x)
					[
						BottomTextWidget.ToSharedRef()
					]
				]
			]
		]
	];
}

FReply SAccountStartupCard::OnButtonPressed()
{
	OnButtonClicked.ExecuteIfBound();
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE
