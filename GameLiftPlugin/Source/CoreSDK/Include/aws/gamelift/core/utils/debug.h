// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.

#pragma once

/**
* Define GameLiftInternalAssert helper macro. This is a wrapper for C++ assert() that is only compiled in
* debug builds. No-op in Release builds.
*/

#ifdef _DEBUG
#include <assert.h>

#define GameLiftInternalAssert(value)    assert(value)

#else

#define GameLiftInternalAssert(value)    (void)(value)

#endif