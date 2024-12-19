// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "GameLiftPluginStyle.h"

#include "EditorStyleSet.h"
#include "Framework/Application/SlateApplication.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"

#include "GameLiftPlugin.h"
#include "GameLiftPluginConstants.h"
#include "Utils/Misc.h"

TSharedPtr< FSlateStyleSet > FGameLiftPluginStyle::StyleInstance = NULL;

void FGameLiftPluginStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FGameLiftPluginStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FGameLiftPluginStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("GameLiftPluginStyle"));
	return StyleSetName;
}

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( StyleSet->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define SVG_BRUSH( RelativePath, ... ) FSlateVectorImageBrush( StyleSet->RootToContentDir( RelativePath, TEXT(".svg") ), __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( StyleSet->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( StyleSet->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define TTF_FONT( RelativePath, ... ) FSlateFontInfo( StyleSet->RootToContentDir( RelativePath, TEXT(".ttf") ), __VA_ARGS__ )
#define OTF_FONT( RelativePath, ... ) FSlateFontInfo( StyleSet->RootToContentDir( RelativePath, TEXT(".otf") ), __VA_ARGS__ )
#define DEFAULT_FONT(...) FCoreStyle::GetDefaultFontStyle(__VA_ARGS__)

#if (ENGINE_MAJOR_VERSION >= 5)
	#define SVG_PREFERRED_BRUSH SVG_BRUSH
#else
	#define SVG_PREFERRED_BRUSH IMAGE_BRUSH
#endif

const FVector2D Icon2x50(2.0f, 50.0f);
const FVector2D Icon100x2(100.0f, 2.0f);
const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon18x18(18.0f, 18.0f);
const FVector2D Icon20x20(20.0f, 20.0f);
const FVector2D Icon40x40(40.0f, 40.0f);
const FVector2D Icon80x80(80.0f, 80.0f);

TSharedRef<FSlateStyleSet> FGameLiftPluginStyle::Create()
{
	TSharedRef<FSlateStyleSet> StyleSet = MakeShareable(new FSlateStyleSet(Style::kGameLiftPluginStyleName));
	StyleSet->SetContentRoot(IPluginManager::Get().FindPlugin(Plugin::sGameLiftPluginName)->GetBaseDir() / TEXT("Content") / TEXT("Editor") / TEXT("Icons"));

	ConfigureColors(StyleSet);
	ConfigureFonts(StyleSet);
	ConfigureIcons(StyleSet);
	ConfigureButtons(StyleSet);

	return StyleSet;
}

void FGameLiftPluginStyle::ConfigureColors(TSharedRef<FSlateStyleSet> StyleSet)
{
	// Panel and section header colors
#if(ENGINE_MAJOR_VERSION >= 5)
	StyleSet->Set(Style::Color::kSectionHeaderBackground, GetAppStyle().GetSlateColor("Colors.Header"));
	StyleSet->Set(Style::Color::kPanelBackground, GetAppStyle().GetSlateColor("Colors.Panel"));
#else
	StyleSet->Set(Style::Color::kSectionHeaderBackground, FColor(48, 48, 48));
	StyleSet->Set(Style::Color::kPanelBackground, FColor(67, 67, 67));
#endif
	StyleSet->Set(Style::Color::kCredentialSeparator, FColor(199, 199, 199));

	// Table
	StyleSet->Set(Style::Color::kTableRowBackground, FColor(0, 0, 0));
	StyleSet->Set(Style::Color::kTableHeaderBackground, FColor(47, 47, 47));
	StyleSet->Set(Style::Color::kTableSeparator, FColor(199, 199, 199, 0.2));

	// Card
	StyleSet->Set(Style::Color::kCardBackground, FColor(42, 42, 42));

	// Toggler
	StyleSet->Set(Style::Color::kTogglerBackground, FColor(24, 24, 24));
	StyleSet->Set(Style::Color::kTogglerBorder, FColor(60, 175, 207));

	// Success, warning, error colors
	StyleSet->Set(Style::Color::kSuccessForeground, FColor::White);
	StyleSet->Set(Style::Color::kSuccessBackground, FColor(29, 129, 2));
	StyleSet->Set(Style::Color::kWarningForeground, FColor::White);
	StyleSet->Set(Style::Color::kWarningBackground, FColor(255, 183, 1));
	StyleSet->Set(Style::Color::kErrorForeground, FColor::White);
	StyleSet->Set(Style::Color::kErrorBackground, FColor(214, 63, 56));
	StyleSet->Set(Style::Color::kInfoForeground, FColor::White);
	StyleSet->Set(Style::Color::kInfoBackground, FColor(0, 115, 187));
	StyleSet->Set(Style::Color::kHelpForeground, FColor::White);
	StyleSet->Set(Style::Color::kHelpBackground, FColor(56, 56, 56));

	StyleSet->Set(Style::Color::kInactive, FColor(192, 192, 192));
	StyleSet->Set(Style::Color::kSuccess, FColor(65, 194, 2));
	StyleSet->Set(Style::Color::kWarning, FColor::Yellow);
	StyleSet->Set(Style::Color::kError, FColor(214, 63, 56));
	StyleSet->Set(Style::Color::kLoading, FColor(192, 192, 192));

	// Button colors
	StyleSet->Set(Style::Color::kSuccessButtonNormal, FColor(47, 140, 0));
	StyleSet->Set(Style::Color::kSuccessButtonHovered, FColor(55, 161, 0));
	StyleSet->Set(Style::Color::kSuccessButtonPressed, FColor(36, 107, 0));

	StyleSet->Set(Style::Color::kErrorButtonNormal, FColor(242, 71, 63));
	StyleSet->Set(Style::Color::kErrorButtonHovered, FColor(246, 107, 100));
	StyleSet->Set(Style::Color::kErrorButtonPressed, FColor(209, 62, 55));

	StyleSet->Set(Style::Color::kDisabledButton, FColor(21, 21, 21));

	StyleSet->Set(Style::Color::kTooltip, FColor(192, 192, 192));
}

void FGameLiftPluginStyle::ConfigureFonts(TSharedRef<FSlateStyleSet> StyleSet)
{
	// Text style (STextBlock, SButton)
	const FTextBlockStyle& RegularText = GetAppStyle().GetWidgetStyle<FTextBlockStyle>("NormalText");
	StyleSet->Set(Style::Text::kParagraph, FTextBlockStyle(RegularText).SetFont(DEFAULT_FONT("Regular", Style::Font::ParagraphFontSize)));
	StyleSet->Set(Style::Text::kField, FTextBlockStyle(RegularText).SetFont(DEFAULT_FONT("Regular", Style::Font::FieldFontSize)));
	StyleSet->Set(Style::Text::kFieldMedium, FTextBlockStyle(RegularText).SetFont(DEFAULT_FONT("Medium", Style::Font::FieldFontSize)));
	StyleSet->Set(Style::Text::kFieldBold, FTextBlockStyle(RegularText).SetFont(DEFAULT_FONT("Bold", Style::Font::FieldFontSize)));
	StyleSet->Set(Style::Text::kFieldItalic, FTextBlockStyle(RegularText).SetFont(DEFAULT_FONT("Italic", Style::Font::FieldFontSize)));
	StyleSet->Set(Style::Text::kNote, FTextBlockStyle(RegularText).SetFont(DEFAULT_FONT("Regular", Style::Font::NoteFontSize)));
	StyleSet->Set(Style::Text::kNoteLight, FTextBlockStyle(RegularText).SetFont(DEFAULT_FONT("Light", Style::Font::NoteFontSize)));
	StyleSet->Set(Style::Text::kNoteItalic, FTextBlockStyle(RegularText).SetFont(DEFAULT_FONT("Italic", Style::Font::NoteFontSize)));

	StyleSet->Set(Style::Text::kTitleStyleName, FTextBlockStyle(RegularText).SetFont(DEFAULT_FONT("Medium", Style::Font::kTitleFontSize)));
	StyleSet->Set(Style::Text::kSubtitleStyleName, FTextBlockStyle(RegularText).SetFont(DEFAULT_FONT("Medium", Style::Font::kSubtitleFontSize)));

	StyleSet->Set(Style::Text::kMessageLog, GetAppStyle().GetWidgetStyle<FTextBlockStyle>("MessageLog"));

	// Text style for SRichTextBox
	StyleSet->Set(TEXT("RichTextBlock.Bold"), FTextBlockStyle(RegularText).SetFont(DEFAULT_FONT("Bold", Style::Font::ParagraphFontSize)));

	// Button text styles
#if(ENGINE_MAJOR_VERSION >= 5)
	StyleSet->Set(Style::Text::kButtonNormal, FTextBlockStyle(RegularText).SetFont(DEFAULT_FONT("Regular", Style::Font::ButtonFontSize)).SetColorAndOpacity(FSlateColor(FColor::White)));
#else
	StyleSet->Set(Style::Text::kButtonNormal, FTextBlockStyle(RegularText).SetFont(DEFAULT_FONT("Regular", Style::Font::ButtonFontSize)).SetColorAndOpacity(FSlateColor(FColor::Black))); // In UE4, button background is light color
#endif
	StyleSet->Set(Style::Text::kButtonLight, FTextBlockStyle(RegularText).SetFont(DEFAULT_FONT("Regular", Style::Font::ButtonFontSize)).SetColorAndOpacity(FSlateColor(FColor::White)));

	// Section header text style
	FSlateFontInfo SectionHeaderFontStyle(FCoreStyle::Get().GetFontStyle("ExpandableArea.TitleFont"));
	SectionHeaderFontStyle.Size = Style::Font::SectionHeaderFontSize;
	SectionHeaderFontStyle.TypefaceFontName = "Medium";
	StyleSet->Set(Style::Text::kSectionHeaderFontStyleName, SectionHeaderFontStyle);

	// Editable text style (SEditableText)
	const FEditableTextStyle& RegularEditableText = GetAppStyle().GetWidgetStyle<FEditableTextStyle>("NormalEditableText");
	StyleSet->Set(Style::EditableText::kParagraph, FEditableTextStyle(RegularEditableText).SetFont(DEFAULT_FONT("Regular", Style::Font::ParagraphFontSize)));
	StyleSet->Set(Style::EditableText::kField, FEditableTextStyle(RegularEditableText).SetFont(DEFAULT_FONT("Regular", Style::Font::FieldFontSize)));
	StyleSet->Set(Style::EditableText::kFieldMedium, FEditableTextStyle(RegularEditableText).SetFont(DEFAULT_FONT("Medium", Style::Font::FieldFontSize)));
	StyleSet->Set(Style::EditableText::kFieldBold, FEditableTextStyle(RegularEditableText).SetFont(DEFAULT_FONT("Bold", Style::Font::FieldFontSize)));

	// Editable text box style (SEditableTextBox)
	const FEditableTextBoxStyle& RegularEditableTextBox = GetAppStyle().GetWidgetStyle<FEditableTextBoxStyle>("NormalEditableTextBox");
	StyleSet->Set(Style::EditableTextBox::kField, FEditableTextBoxStyle(RegularEditableTextBox).SetFont(DEFAULT_FONT("Regular", Style::Font::FieldFontSize)));

	// Hyperlink text style
	FHyperlinkStyle NewHyperLinkStyle(GetAppStyle().GetWidgetStyle<FHyperlinkStyle>("Common.GotoBlueprintHyperlink"));
	NewHyperLinkStyle.SetTextStyle(FTextBlockStyle(RegularText).SetFont(DEFAULT_FONT("Bold", Style::Font::LinkFontSize)).SetColorAndOpacity(RegularText.ColorAndOpacity));
	StyleSet->Set(Style::kLinkStyleName, NewHyperLinkStyle);
}

void FGameLiftPluginStyle::ConfigureIcons(TSharedRef<FSlateStyleSet> StyleSet)
{
	StyleSet->Set(Style::Brush::kExternalLinkIconName, new SVG_PREFERRED_BRUSH(TEXT("ExternalLink"), Icon16x16));
	StyleSet->Set(Style::Brush::kStatusSuccessIconName, new SVG_PREFERRED_BRUSH(TEXT("StatusSuccess"), Icon16x16));
	StyleSet->Set(Style::Brush::kStatusWarningIconName, new SVG_PREFERRED_BRUSH(TEXT("StatusWarning"), Icon16x16));
	StyleSet->Set(Style::Brush::kStatusErrorIconName, new SVG_PREFERRED_BRUSH(TEXT("StatusError"), Icon16x16));
	StyleSet->Set(Style::Brush::kStatusInactiveIconName, new SVG_PREFERRED_BRUSH(TEXT("StatusInactive"), Icon16x16));
	StyleSet->Set(Style::Brush::kStatusInfoIconName, new SVG_PREFERRED_BRUSH(TEXT("StatusInfo"), Icon16x16));
	StyleSet->Set(Style::Brush::kStatusHelpIconName, new SVG_PREFERRED_BRUSH(TEXT("StatusHelp"), Icon20x20));
	StyleSet->Set(Style::Brush::kFolderOpenIconName, new SVG_PREFERRED_BRUSH(TEXT("FolderOpen"), Icon16x16));
	StyleSet->Set(Style::Brush::kTooltipIconName, new SVG_PREFERRED_BRUSH(TEXT("Tooltip"), Icon16x16));
	StyleSet->Set(Style::Brush::kCopyPasteIconName, new SVG_PREFERRED_BRUSH(TEXT("CopyPaste"), Icon16x16));
	StyleSet->Set(Style::Brush::kResetIconName, new SVG_PREFERRED_BRUSH(TEXT("Reset"), Icon16x16));
	StyleSet->Set(Style::Brush::kStartIconName, new SVG_PREFERRED_BRUSH(TEXT("Start"), Icon16x16));


	StyleSet->Set(Style::Brush::kGameLiftTabIconName, new IMAGE_BRUSH(TEXT("GameLiftTab"), Icon16x16));
	StyleSet->Set(Style::Brush::kGameLiftContainersTabIconName, new IMAGE_BRUSH(TEXT("GameLiftContainersTab"), Icon18x18));
	StyleSet->Set(Style::Brush::kGameLiftToolbarIconName, new IMAGE_BRUSH(TEXT("GameLiftToolbar"), Icon40x40));

	StyleSet->Set(Style::Brush::kBorderImageName, new FSlateBrush(*GetAppStyle().GetBrush("WhiteBrush")));

	StyleSet->Set(Style::Brush::kAccountIconName, new IMAGE_BRUSH(TEXT("Account"), Icon80x80));
	StyleSet->Set(Style::Brush::kAccountMissingIconName, new IMAGE_BRUSH(TEXT("AccountMissing"), Icon80x80));

	StyleSet->Set(Style::Brush::kGameLiftAnywhereIconName, new IMAGE_BRUSH(TEXT("GameLiftAnywhere"), Icon20x20));
	StyleSet->Set(Style::Brush::kGameLiftManagedEC2IconName, new IMAGE_BRUSH(TEXT("GameLiftManagedEC2"), Icon20x20));

	StyleSet->Set(Style::Brush::kGameLiftLogoIconName, new IMAGE_BRUSH(TEXT("GameLiftLogo"), Style::Brush::kGameLiftLogoIconSize));

	StyleSet->Set(Style::Brush::kGameLiftDivider, new SVG_PREFERRED_BRUSH(TEXT("Divider"), Icon100x2));

	StyleSet->Set(Style::Brush::kDocumentationIcon, new SVG_PREFERRED_BRUSH(TEXT("Documentation"), Icon16x16));
	StyleSet->Set(Style::Brush::kGuidanceIcon, new SVG_PREFERRED_BRUSH(TEXT("Guidance"), Icon16x16));
	StyleSet->Set(Style::Brush::kWhitepaperIcon, new SVG_PREFERRED_BRUSH(TEXT("Whitepaper"), Icon16x16));

	// Progress bar
	StyleSet->Set(Style::Brush::kProgressCompleteIconName, new SVG_PREFERRED_BRUSH(TEXT("ProgressCompleteIcon"), Icon18x18));
	StyleSet->Set(Style::Brush::kProgressCompleteBarName, new SVG_PREFERRED_BRUSH(TEXT("ProgressCompleteBar"), Icon2x50));
	StyleSet->Set(Style::Brush::kProgressIncompleteIconName, new SVG_PREFERRED_BRUSH(TEXT("ProgressIncompleteIcon"), Icon18x18));
	StyleSet->Set(Style::Brush::kProgressIncompleteBarName, new SVG_PREFERRED_BRUSH(TEXT("ProgressIncompleteBar"), Icon2x50));
	StyleSet->Set(Style::Brush::kInProgressIconName, new SVG_PREFERRED_BRUSH(TEXT("InProgressIcon"), Icon18x18));
	StyleSet->Set(Style::Brush::kProgressWarningIconName, new SVG_PREFERRED_BRUSH(TEXT("ProgressWarningIcon"), Icon18x18));
	StyleSet->Set(Style::Brush::kProgressErrorIconName, new SVG_PREFERRED_BRUSH(TEXT("ProgressErrorIcon"), Icon18x18));
}

void FGameLiftPluginStyle::ConfigureButtons(TSharedRef<FSlateStyleSet> StyleSet)
{
#if(ENGINE_MAJOR_VERSION >= 5)
	StyleSet->Set(Style::Button::kFlatButtonStyleName, GetAppStyle().GetWidgetStyle<FButtonStyle>("SimpleButton"));
#else
	StyleSet->Set(Style::Button::kFlatButtonStyleName, GetAppStyle().GetWidgetStyle<FButtonStyle>("NoBorder"));
#endif

	const FButtonStyle& DefaultButtonStyle = GetAppStyle().GetWidgetStyle<FButtonStyle>("Button");
	FButtonStyle NormalButtonStyle(DefaultButtonStyle);
	StyleSet->Set(Style::Button::kNormalButtonStyleName, NormalButtonStyle);

	FButtonStyle SuccessButtonStyle(DefaultButtonStyle);
	SuccessButtonStyle.Normal.TintColor = StyleSet->GetColor(Style::Color::kSuccessButtonNormal);
	SuccessButtonStyle.Hovered.TintColor = StyleSet->GetColor(Style::Color::kSuccessButtonHovered);
	SuccessButtonStyle.Pressed.TintColor = StyleSet->GetColor(Style::Color::kSuccessButtonPressed);

	StyleSet->Set(Style::Button::kSuccessButtonStyleName, SuccessButtonStyle);

	FButtonStyle ErrorButtonStyle(DefaultButtonStyle);
	ErrorButtonStyle.Normal.TintColor = StyleSet->GetColor(Style::Color::kErrorButtonNormal);
	ErrorButtonStyle.Hovered.TintColor = StyleSet->GetColor(Style::Color::kErrorButtonHovered);
	ErrorButtonStyle.Pressed.TintColor = StyleSet->GetColor(Style::Color::kErrorButtonPressed);
	StyleSet->Set(Style::Button::kErrorButtonStyleName, ErrorButtonStyle);

	FButtonStyle CloseButtonStyle = FButtonStyle();
	CloseButtonStyle.SetNormal(SVG_PREFERRED_BRUSH(TEXT("CloseX"), Icon16x16));
	CloseButtonStyle.SetHovered(SVG_PREFERRED_BRUSH(TEXT("CloseX"), Icon16x16));
	CloseButtonStyle.SetPressed(SVG_PREFERRED_BRUSH(TEXT("CloseX"), Icon16x16));
	StyleSet->Set(Style::Button::kCloseButtonStyleName, CloseButtonStyle);

	// Launch bar button styles
	FButtonStyle LaunchBarSuccessButtonStyle(SuccessButtonStyle);
	LaunchBarSuccessButtonStyle.Disabled.TintColor = StyleSet->GetColor(Style::Color::kDisabledButton);
	StyleSet->Set(Style::Button::kLaunchBarSuccessButtonStyle, LaunchBarSuccessButtonStyle);

	FButtonStyle LaunchBarNormalButtonStyle(NormalButtonStyle);
	LaunchBarNormalButtonStyle.Disabled.TintColor = StyleSet->GetColor(Style::Color::kDisabledButton);
	StyleSet->Set(Style::Button::kLaunchBarNormalButtonStyle, LaunchBarNormalButtonStyle);
}

#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH
#undef TTF_FONT
#undef OTF_FONT
#undef DEFAULT_FONT

void FGameLiftPluginStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FGameLiftPluginStyle::Get()
{
	return *StyleInstance;
}
