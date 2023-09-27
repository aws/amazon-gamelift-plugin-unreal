// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once 

#include "Containers/UnrealString.h"
#include "Containers/Array.h"

class IAWSConfigFileProfile
{
public:
	virtual ~IAWSConfigFileProfile() = default;

	virtual TArray<FString> GetProfileNames() const  = 0;

	virtual void CreateProfile(const FString& ProfileName) = 0;
	virtual void RenameProfile(const FString& ProfileName, const FString& NewProfileName) = 0;

	virtual FString GetAccessKey(const FString& ProfileName) const = 0;
	virtual void SetAccessKey(const FString& ProfileName, const FString& accessKey) = 0;
	virtual FString GetSecretAccessKey(const FString& ProfileName) const = 0;
	virtual void SetSecretAccessKey(const FString& ProfileName, const FString& secretAccessKey) = 0;
	virtual FString GetSessionToken(const FString& ProfileName) const = 0;
	virtual void SetSessionToken(const FString& ProfileName, const FString& sessionToken) = 0;
	virtual FString GetRegion(const FString& ProfileName) const = 0;
	virtual void SetRegion(const FString& ProfileName, const FString& region) = 0;

	virtual void Save() = 0;

};
