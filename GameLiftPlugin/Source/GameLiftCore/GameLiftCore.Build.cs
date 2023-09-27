// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

using UnrealBuildTool;
using System.IO;

namespace UnrealBuildTool.Rules
{
	public class GameLiftCore : ModuleRules
	{
		public GameLiftCore(ReadOnlyTargetRules Target)
			: base(Target)
		{
			PrivateIncludePaths.AddRange(
				new string[]
				{
					"GameLiftCore/Private",
					"AWSSDK",
					"CoreSDK",
				}
			);

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core", 
					"AWSSDK",
					"CoreSDK",
				}
			);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"CoreUObject",
					"Engine",
					"InputCore",
					"Slate",
					"UnrealEd",
					"Projects",
					"DesktopPlatform",
					"ApplicationCore",
					"AutomationDriver",
					"EngineSettings",
				}
			);

			PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));
			PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private"));

			PublicDefinitions.Add("USE_IMPORT_EXPORT");

			if (Target.Platform == UnrealTargetPlatform.Win64)
			{
				PublicDefinitions.Add("WITH_BASE=1");
			}
			else
			{
				PublicDefinitions.Add("WITH_BASE=0");
			}
		}
	}
}
