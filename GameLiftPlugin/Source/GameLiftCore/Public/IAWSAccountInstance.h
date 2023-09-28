// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once 

class IAWSAccountInstance
{
public:
	virtual ~IAWSAccountInstance() = default;

	virtual bool IsValid() const = 0;
	virtual void* GetInstance() const = 0;
	virtual FString GetBucketName() const = 0;
	virtual const char* GetGameName() const = 0;
	virtual const char* GetAccountId() const = 0;
	virtual const char* GetBuildConfiguration() const = 0;
	virtual FString GetLastErrorMessage() const = 0;
};
