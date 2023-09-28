// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Utils/LogLevelConvertors.h"

namespace Logs
{
	template<typename TextChar>
	inline auto PrintAwsLog(unsigned int Level, const char* Message, int Size, TextChar* Tag)
	{
#define PRINT_LOG_AND_EXIT(__x__) UE_LOG(GameLiftCoreLog, __x__, TEXT("%s %s"), Tag, *FString(Message)); return UeLogLevel

		auto UeLogLevel = Convertors::FromAwsLogLevelToUe(Level);

		switch (UeLogLevel)
		{
			case ELogVerbosity::Log: PRINT_LOG_AND_EXIT(Log);
			case ELogVerbosity::Display: PRINT_LOG_AND_EXIT(Display);
			case ELogVerbosity::Warning: PRINT_LOG_AND_EXIT(Warning);
			case ELogVerbosity::Error: PRINT_LOG_AND_EXIT(Error);
		}

		PRINT_LOG_AND_EXIT(VeryVerbose);

#undef PRINT_LOG
	}
} // namespace Logs
