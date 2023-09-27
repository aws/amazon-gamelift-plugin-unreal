// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"

class FGameLiftPluginStyle
{
public:
	static void Initialize();

	static void Shutdown();

	// Reload textures used by slate renderer.
	static void ReloadTextures();

	// Return the GameLift plugin's style set instance.
	static const ISlateStyle& Get();

	// Return the Unreal Editor's style set instance.
	// Note that it returns FEditorStyle::Get in UE4.
	static inline const ISlateStyle& GetAppStyle()
	{
#if(ENGINE_MAJOR_VERSION == 5)			
		return FAppStyle::Get();
#else
		return FEditorStyle::Get();
#endif
	}

	static FName GetStyleSetName();

private:
	static TSharedRef< class FSlateStyleSet > Create();

	static void ConfigureColors(TSharedRef<FSlateStyleSet> StyleSet);
	static void ConfigureFonts(TSharedRef<FSlateStyleSet> StyleSet);
	static void ConfigureIcons(TSharedRef<FSlateStyleSet> StyleSet);
	static void ConfigureButtons(TSharedRef<FSlateStyleSet> StyleSet);

private:
	static TSharedPtr< class FSlateStyleSet > StyleInstance;
};
