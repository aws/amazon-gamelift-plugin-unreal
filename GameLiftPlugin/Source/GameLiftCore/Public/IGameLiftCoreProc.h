// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once 

class IGameLiftCoreProc
{
public:
	virtual ~IGameLiftCoreProc() = default;
	virtual bool LaunchProcess(const FString& path, TArray<FString> arguments) = 0;
};
