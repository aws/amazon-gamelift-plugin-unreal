// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "ScenarioWithParameters.h"

#include "aws/gamelift/core/errors.h"

namespace AwsScenarios
{
	class ScenarioWithoutGameServer : public ScenarioWithParameters
	{
	public:
		virtual int UploadGameServer(
			IAWSAccountInstance* AwsAccountInstance, 
			const std::string& ServerFolderPath, 
			const std::string& ExtraServerResourcesPath
		) override
		{
			return GameLift::GAMELIFT_SUCCESS;
		}
		
		virtual int CreateLaunchPathParameter(
			const FString& BuildOperatingSystem,
			const FString& BuildFolderPath,
			const FString& BuildFilePath,
			std::string& StdLaunchPathParameter
		) override
		{
			StdLaunchPathParameter = "";
			return GameLift::GAMELIFT_SUCCESS;
		}
	};
} // namespace AwsScenarios
