// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

using UnrealBuildTool;

public class GameLiftPlugin : ModuleRules
{
	public GameLiftPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[]
			{
				// ... add public include paths required here ...
			});
				
		
		PrivateIncludePaths.AddRange(
			new string[]
			{
				"GameLiftPlugin/Private",
			});
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			});
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Projects",
				"InputCore",
				"UnrealEd",
				"ToolMenus",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"Sockets",
				"EditorStyle",
				"PropertyEditor",

				"WorkspaceMenuStructure",
				"GameLiftCore",

				"Blutility",
				"UMG",
				"DesktopPlatform",
				"SharedSettingsWidgets",
				"AutomationDriver",
				"ApplicationCore",

				// ... add private dependencies that you statically link with here ...	
			});
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			});
	}
}
