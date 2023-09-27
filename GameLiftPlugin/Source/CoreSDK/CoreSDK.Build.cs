// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

using UnrealBuildTool;
using System.IO;
using System.Net;
using System.Text.RegularExpressions;

public class CoreSDK : ModuleRules
{
	private string[] LibraryNames =
	{
		"aws-gamelift-profiles",
		"aws-gamelift-authentication",
		"aws-gamelift-core",
	};

	public CoreSDK(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Include"));

		if (Target.Type == TargetRules.TargetType.Editor || Target.Type == TargetRules.TargetType.Client)
		{
			// yaml-cpp
			string ThirdPartyPath = Path.Combine(ModuleDirectory, "ThirdParty");
			string YamlCppIncludePath = Path.Combine(Path.Combine(ThirdPartyPath, "yaml-cpp"), "include");
			string YamlCppLibPath = Path.Combine(Path.Combine(ThirdPartyPath, "yaml-cpp"), "lib");
			PublicIncludePaths.Add(YamlCppIncludePath);
			PublicAdditionalLibraries.Add(Path.Combine(YamlCppLibPath, "yaml-cpp.lib"));
			
			// Core SDK
			string LibrarysPath = Path.Combine(ModuleDirectory, "Binaries", UnrealTargetPlatform.Win64.ToString());
			string OutputDir = Path.Combine("$(ProjectDir)", "Binaries", UnrealTargetPlatform.Win64.ToString());

			foreach (string LibName in LibraryNames)
			{
				string LibFileName = LibName + ".lib";
				string DllFileName = LibName + ".dll";

				// Add the import library
				PublicAdditionalLibraries.Add(Path.Combine(LibrarysPath, LibFileName));

				// Do not load the DLL during startup. Delay-load the DLL when it is actually used.
				PublicDelayLoadDLLs.Add(DllFileName);

				// This stages the DLL next to the executable when you package your game.
				RuntimeDependencies.Add(Path.Combine(OutputDir, DllFileName), Path.Combine(LibrarysPath, DllFileName));
			}
		}
	}
}
