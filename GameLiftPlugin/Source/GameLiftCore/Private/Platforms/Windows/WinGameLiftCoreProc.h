// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#if !PLATFORM_WINDOWS && !PLATFORM_HOLOLENS
#error Only Widows platform is supported
#endif

#include "IGameLiftCoreProc.h"

class GameLiftCoreProc : public IGameLiftCoreProc
{
public:
	GameLiftCoreProc();

	bool LaunchProcess(const FString& Path, TArray<FString> Arguments) override;
};
