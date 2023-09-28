// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "SErrorBanner.h"

#include "Widgets/Images/SImage.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "SErrorBanner"

void SErrorBanner::Construct(const FArguments& InArgs)
{
	OnBannerButtonClicked = InArgs._OnBannerButtonClicked;

	ChildSlot
	[
		SNew(SBorder)
		.BorderBackgroundColor(this, &SErrorBanner::GetBorderColor)
		.BorderImage(FGameLiftPluginStyle::Get().GetBrush(Style::Brush::kBorderImageName))
		[
			MakeRow(InArgs._ErrorIcon, InArgs._ErrorText, InArgs._ErrorButtonText)
		]
	];
}

TSharedRef<SWidget> SErrorBanner::MakeRow(FName IconName, const FText& ErrorText, const FText& ButtonText)
{
	TSharedRef<SHorizontalBox> HorizontalBox = SNew(SHorizontalBox)
		// Error icon
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(SPadding::BannerContentAll)
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		[
			SNew(SBox)
			.WidthOverride(Style::kBannerIconSize)
			.HeightOverride(Style::kBannerIconSize)
			[
				SNew(SImage)
				.Image(FGameLiftPluginStyle::Get().GetBrush(IconName))
			]
		]
		// Error text
		+ SHorizontalBox::Slot()
		.FillWidth(1)
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.AutoWrapText(true)
			.ColorAndOpacity(this, &SErrorBanner::GetTextColor)
			.Text(ErrorText)
			.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kParagraph)
		];

		// Optional button
		if (!ButtonText.IsEmpty())
		{
			HorizontalBox->AddSlot()
			.AutoWidth()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Center)
			.Padding(SPadding::Left2x)
			[
				SNew(SButton)
				.OnClicked(this, &SErrorBanner::OnBannerButtonPressed)
				.Text(ButtonText)
				.TextStyle(FGameLiftPluginStyle::Get(), Style::Text::kButtonNormal)
			];
		}

		// Close button
		HorizontalBox->AddSlot()
		.AutoWidth()
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Center)
		.Padding(SPadding::Left2x_Right)
		[
			SNew(SButton)
			.OnClicked(this, &SErrorBanner::OnCloseButtonPressed)
			.ButtonStyle(FGameLiftPluginStyle::Get(), Style::Button::kCloseButtonStyleName)
		];

	return HorizontalBox;
}

FSlateColor SErrorBanner::GetBorderColor() const
{
	return FGameLiftPluginStyle::Get().GetColor(Style::Color::kErrorBackground);
}

FSlateColor SErrorBanner::GetTextColor() const
{
	return FGameLiftPluginStyle::Get().GetColor(Style::Color::kErrorForeground);
}

FReply SErrorBanner::OnBannerButtonPressed()
{
	OnBannerButtonClicked.ExecuteIfBound();
	return FReply::Handled();
}

FReply SErrorBanner::OnCloseButtonPressed()
{
	SetVisibility(EVisibility::Collapsed);
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE
