// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <Logging/LogVerbosity.h>
#include "aws/gamelift/core/logging.h"

namespace Convertors
{
	inline ELogVerbosity::Type FromAwsLogLevelToUe(unsigned int AwsLogLevel)
	{
		using namespace GameLift::Logger;

		Level EnumAwsLogLevel = Level(AwsLogLevel);

		switch (AwsLogLevel)
		{
			case Level::Verbose: return ELogVerbosity::Log;
			case Level::Info: return ELogVerbosity::Display;
			case Level::Warning: return ELogVerbosity::Warning;
			case Level::Error: return ELogVerbosity::Error;
			default:
				break;
		}

		return ELogVerbosity::VeryVerbose;
	}
} // namespace Convertors
