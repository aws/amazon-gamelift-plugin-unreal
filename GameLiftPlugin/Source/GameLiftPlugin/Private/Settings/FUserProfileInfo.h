// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

#include "FUserProfileInfo.generated.h"

/**
 * Holds information about an aws profile.
 */

USTRUCT()
struct FUserProfileInfo
{
    GENERATED_USTRUCT_BODY()
 public:
 	UPROPERTY(config, EditAnywhere, Category = "AWS Credentials")
 	FString AwsRegion;
 	UPROPERTY(config, EditAnywhere, Category = "AWS Credentials")
    FString S3Bucket;
 	UPROPERTY(config, EditAnywhere, Category = "AWS Credentials")
 	int BootstrapStatus;
    UPROPERTY(config, EditAnywhere, Category = "AWS Credentials")
    FString BootstrapError;
 };