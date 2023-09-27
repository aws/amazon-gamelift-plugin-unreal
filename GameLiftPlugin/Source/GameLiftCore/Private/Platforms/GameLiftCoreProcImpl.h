// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#if PLATFORM_WINDOWS || PLATFORM_HOLOLENS
#include "Windows/WinGameLiftCoreProc.h"
#elif PLATFORM_MAC
#include "Mac/MacGameLiftCoreProc.h"
#elif PLATFORM_LINUX
#include "Linux/LinuxGameLiftCoreProc.h"
#endif
