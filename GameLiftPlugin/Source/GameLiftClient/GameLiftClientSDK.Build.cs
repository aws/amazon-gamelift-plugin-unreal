// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

using UnrealBuildTool;
using System.IO;

public class GameLiftClientSDK : ModuleRules
{
	public GameLiftClientSDK(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(new string[] { "Engine", "Core", "CoreUObject", "InputCore", "Projects" });
		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));
		PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private"));

		// Add dependencies needed by the UI code for testing widgets.
        PublicDependencyModuleNames.AddRange(new string[] { "WebBrowserWidget", "SlateCore", "HTTP", "Json", "JsonUtilities", "HeadMountedDisplay", "UMG" });

        PublicDefinitions.Add("USE_IMPORT_EXPORT");

		if (Target.Type == TargetRules.TargetType.Editor || Target.Type == TargetRules.TargetType.Client)
		{
			PublicDependencyModuleNames.AddRange(new string[] { "AWSSDK", "CoreSDK" });

			PublicDefinitions.Add("WITH_GAMELIFT_CLIENT=1");
		}
		else
		{
			PublicDefinitions.Add("WITH_GAMELIFT_CLIENT=0");
		}
	}
}
