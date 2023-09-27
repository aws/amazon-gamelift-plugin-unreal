// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "Serializer.h"

#if WITH_GAMELIFT_CLIENT

namespace AWSSerializer
{
	std::string FSToStdS(const FString& String)
	{
		if (String.IsEmpty())
		{
			return {};
		}

		auto* Chars = StringCast<ANSICHAR>(*String).Get();
		return std::string(Chars, strlen(Chars));
	}

	FString ASToFS(const char* String)
	{
		return FString(StringCast<TCHAR>(String).Get());
	}
} // namespace AWSSerializer

#endif
