// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#if WITH_GAMELIFT_CLIENT

#include <string>
#include <Containers/StringConv.h>

namespace AWSSerializer
{
	std::string FSToStdS(const FString& String);
	FString ASToFS(const char* String);
}

#endif
