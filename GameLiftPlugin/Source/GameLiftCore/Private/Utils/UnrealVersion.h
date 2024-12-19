// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Misc/EngineVersion.h"

namespace UnrealVersion
{
	inline const FString GetCurrentEngineVersion()
	{
		FEngineVersion CurrentVersion = FEngineVersion::Current();
		FString VersionString = FString::Printf(TEXT("%d.%d.%d"),
			CurrentVersion.GetMajor(),
			CurrentVersion.GetMinor(),
			CurrentVersion.GetPatch());

		return VersionString;
	}
} // namespace UnrealVersion
