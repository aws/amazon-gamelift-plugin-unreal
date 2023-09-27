// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

using UnrealBuildTool;
using System.IO;
using System.Net;
using System.Text.RegularExpressions;

public class AWSSDK : ModuleRules
{
	private string[] LibraryNames =
	{
		// AWS SDK
		"aws-checksums",
		"aws-c-http",
		"aws-c-io",
		"aws-c-mqtt",
		"aws-c-auth",
		"aws-c-cal",
		"aws-c-common",
		"aws-c-compression",
		"aws-c-event-stream",
		"aws-c-s3",
		"aws-c-sdkutils",
		"aws-crt-cpp",
		"aws-cpp-sdk-access-management",
		"aws-cpp-sdk-apigateway",
		"aws-cpp-sdk-cloudformation",
		"aws-cpp-sdk-cognito-identity",
		"aws-cpp-sdk-cognito-idp",
		"aws-cpp-sdk-core",
		"aws-cpp-sdk-iam",
		"aws-cpp-sdk-kinesis",
		"aws-cpp-sdk-lambda",
		"aws-cpp-sdk-s3",
		"aws-cpp-sdk-secretsmanager",
		"aws-cpp-sdk-ssm",
		"aws-cpp-sdk-sts",
		"aws-cpp-sdk-gamelift",
	};

	// Reference: https://aws.amazon.com/blogs/gametech/how-to-integrate-the-aws-c-sdk-with-unreal-engine/
	public AWSSDK(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Include"));

		PublicDefinitions.Add("USE_IMPORT_EXPORT");

		if (Target.Type == TargetRules.TargetType.Editor || Target.Type == TargetRules.TargetType.Client)
		{
			PublicDefinitions.Add("AWS_USE_IO_COMPLETION_PORTS=1");
			PublicDefinitions.Add("__clang_analyzer__=0");
			PublicDefinitions.Add("AWS_DEEP_CHECKS=0");

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
