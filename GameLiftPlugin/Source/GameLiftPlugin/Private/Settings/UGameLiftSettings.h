// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"

#include "GameLiftPluginConstants.h"

#include "UGameLiftSettings.generated.h"

UCLASS(config = EditorPerProjectUserSettings)
class UGameLiftSettings
	: public UObject
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(config, EditAnywhere, Category = "AWS Credentials")
	FText ProfileName;
	UPROPERTY(config, EditAnywhere, Category = "AWS Credentials")
	FText AwsRegion;
	UPROPERTY(config, EditAnywhere, Category = "AWS Credentials")
	FText S3Bucket;
	UPROPERTY(config, EditAnywhere, Category = "AWS Credentials")
	int BootstrapStatus;
	UPROPERTY(config, EditAnywhere, Category = "AWS Credentials")
	FText BootstrapError;
};
