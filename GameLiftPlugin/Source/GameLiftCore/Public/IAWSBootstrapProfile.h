// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once 

#include "IAWSConfigFileProfile.h"

class FString;
class IAWSAccountInstance;

class IAWSBootstrapProfile
{
public:
	virtual ~IAWSBootstrapProfile() = default;

	virtual bool ConfigureAccount(const FString& ProfileName, TSharedRef<IAWSConfigFileProfile> ProfileReader, const FString& ExistingBucketName = "") = 0;
	virtual bool Bootstrap(const FString& NewBucketName = "") = 0;
	virtual FString GetLastError() const = 0;
	virtual FString GetLastErrorMessage() const = 0;
	virtual FString GetDefaultBucketName(const FString& ProfileName, TSharedRef<IAWSConfigFileProfile> ProfileReader) const = 0;
	virtual IAWSAccountInstance* GetAccountInstance() = 0;
};
