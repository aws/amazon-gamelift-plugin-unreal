// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <sstream>
#include <string>

#include "IAWSAccountInstance.h"

namespace AwsScenarios
{
	inline std::string GetLambdaS3Key(const std::string& GameName, const std::string& FunctionsReplacementId)
	{
		std::stringstream StringStream;

		StringStream << GameName;
		StringStream << "/functions/" << GameLift::GetFeatureTypeString(GameLift::FeatureType::Main);
		StringStream << "/" << "requests" << "." << FunctionsReplacementId << ".zip";

		return StringStream.str();
	}

	struct InstanceTemplateParams
	{
		std::string GameNameParameter;
		std::string BuildOperatingSystemParameter;
		std::string BuildS3BucketParameter;
		std::string LambdaZipS3BucketParameter;
		std::string LambdaZipS3KeyParameter;
		std::string ApiGatewayStageNameParameter;
		std::string AccountId;
		std::string LaunchPathParameter;
	};

	class IAWSScenario
	{
	public:
		virtual ~IAWSScenario() = default;

		virtual const char* const* GetParamNames() const = 0;
		virtual FText GetTooltip() const = 0;
		virtual FString GetFolderName() const = 0;
		virtual FText GetUserName() const = 0;
		virtual FString GetScenarioPath() const = 0;
		virtual FString GetScenarioInstancePath() const = 0;

		virtual int SaveFeatureInstanceTemplate(IAWSAccountInstance* AwsAccountInstance, const InstanceTemplateParams& InParams) = 0;
		virtual int UploadGameServer(IAWSAccountInstance* AwsAccountInstance, const std::string& ServerFolderPath, const std::string& ExtraServerResourcesPath) = 0;
		virtual int CreateLaunchPathParameter(const FString& BuildOperatingSystem, const FString& BuildFolderPath, const FString& BuildFilePath, std::string& StdLaunchPathParameter) = 0;
	};
} // namespace AwsScenarios
