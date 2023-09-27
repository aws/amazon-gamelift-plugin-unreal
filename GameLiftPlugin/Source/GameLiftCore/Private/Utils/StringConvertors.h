// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <string>
#include <Containers/StringConv.h>

namespace Convertors
{
	inline std::string FSToStdS(const FString & String)
	{
		if (String.IsEmpty())
		{
			return {};
		}

		auto CastedString = StringCast<ANSICHAR>(*String);
		auto* Chars = CastedString.Get();
		return std::string(Chars, strlen(Chars));
	}

	inline FString ASToFS(const char* RawString)
	{
		return FString(StringCast<TCHAR>(RawString).Get());
	}
} // namespace Convertors
