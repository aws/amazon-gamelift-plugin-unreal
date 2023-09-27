// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "IAWSAccountInstance.h"
#include "AwsAccount/AwsAccountInfo.h"

class AwsAccountInstanceManager : public IAWSAccountInstance
{
public:
	AwsAccountInstanceManager();
	virtual ~AwsAccountInstanceManager();

	int BuildInstance(const FString& Profile, TSharedRef<IAWSConfigFileProfile> ProfileReader, const FString& RootPath, const FString& PluginRootPath);
	void ReleaseInstance();

	void SetBucketName(const FString& NewBucketName);

	virtual void* GetInstance() const override;
	virtual bool IsValid() const override;
	virtual FString GetBucketName() const override;
	virtual const char* GetGameName() const override;
	virtual const char* GetAccountId() const override;
	virtual const char* GetBuildConfiguration() const override;
	virtual FString GetLastErrorMessage() const override;

private:
	AwsAccountInfo AccountInfo;
	void* AccountInstance;
	FString BucketName;
};
