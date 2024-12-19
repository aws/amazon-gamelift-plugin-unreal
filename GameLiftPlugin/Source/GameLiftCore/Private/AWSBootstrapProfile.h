// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once 

#include "IAWSBootstrapProfile.h"

class AWSBootstrapProfile : public IAWSBootstrapProfile
{
public:
	AWSBootstrapProfile();

	bool ConfigureAccount(const FString& ProfileName, TSharedRef<IAWSConfigFileProfile> ProfileReader, const FString& ExistingBucketName = "") override;
	bool Bootstrap(const FString& NewBucketName = "") override;
	FString GetLastError() const override;
	FString GetLastErrorMessage() const override;
	FString GetDefaultBucketName(const FString& ProfileName, TSharedRef<IAWSConfigFileProfile> ProfileReader) const override;
	IAWSAccountInstance* GetAccountInstance() override;

private:
	int LastError = 0;
	TUniquePtr<IAWSAccountInstance> AwsAccountInstance;
};
