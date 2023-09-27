// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "IAWSConfigFileProfile.h"
#include "aws/gamelift/core/config/exports.h"

class AWSConfigFileProfile : public IAWSConfigFileProfile
{
public:

	AWSConfigFileProfile();
	virtual ~AWSConfigFileProfile() override;

	virtual TArray<FString> GetProfileNames() const override;

	virtual void CreateProfile(const FString& ProfileName) override;
	virtual void RenameProfile(const FString& ProfileName, const FString& NewProfileName) override;

	virtual FString GetAccessKey(const FString& ProfileName) const override;
	virtual void SetAccessKey(const FString& ProfileName, const FString& AccessKey) override;
	virtual FString GetSecretAccessKey(const FString& ProfileName) const override;
	virtual void SetSecretAccessKey(const FString& ProfileName, const FString& SecretAccessKey) override;
	virtual FString GetSessionToken(const FString& ProfileName) const override;
	virtual void SetSessionToken(const FString& ProfileName, const FString& SessionToken) override;
	virtual FString GetRegion(const FString& ProfileName) const override;
	virtual void SetRegion(const FString& ProfileName, const FString& Region) override;

	virtual void Save() override;

private:
	GAMELIFT_CONFIGMANAGER_INSTANCE_HANDLE ConfigManagerInstance;
};
