// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "AwsScenarios/IAWSScenario.h"

#include "aws/gamelift/core/exports.h"

namespace AwsScenarios
{
	class ScenarioWithParameters : public IAWSScenario
	{
	public:
		virtual const char* const* GetParamNames() const override
		{
			static const char* paramNames[] =
			{
				"GameNameParameter",
				"BuildOperatingSystemParameter",
				"BuildS3BucketParameter",
				"LambdaZipS3BucketParameter",
				"LambdaZipS3KeyParameter",
				"ApiGatewayStageNameParameter",
				"AccountId",
				"BuildS3KeyParameter",
				"LaunchPathParameter",
			};
			return paramNames;
		}

		virtual int SaveFeatureInstanceTemplate(IAWSAccountInstance* AwsAccountInstance, const InstanceTemplateParams& InParams) override
		{
			const char* ParamValues[] =
			{
				InParams.GameNameParameter.c_str(),
				InParams.BuildOperatingSystemParameter.c_str(),
				InParams.BuildS3BucketParameter.c_str(),
				InParams.LambdaZipS3BucketParameter.c_str(),
				InParams.LambdaZipS3KeyParameter.c_str(),
				InParams.ApiGatewayStageNameParameter.c_str(),
				InParams.AccountId.c_str(),
				BuildS3Path.c_str(),
				InParams.LaunchPathParameter.c_str(),
			};

			auto* ParamNames = GetParamNames();
			size_t Size = sizeof(ParamValues) / sizeof(*ParamValues);

			return GameLiftAccountSaveFeatureInstanceTemplates(AwsAccountInstance->GetInstance(), ParamNames, ParamValues, Size);
		}

		virtual FString GetScenarioPath() const override
		{
			return Paths::ScenarioPath(GetFolderName());
		}

		virtual FString GetScenarioInstancePath() const override
		{
			return Paths::ScenarioInstancePath(GetFolderName());
		}

		void SetBuildS3Path(const std::string& NewBuildS3Path)
		{
			BuildS3Path = NewBuildS3Path;
		}

	private:
		std::string BuildS3Path;
	};
} // namespace AwsScenarios
