// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.

#pragma once

extern "C"
{
    typedef void(*FuncResourceInfoCallback)(const char* logicalResourceId, const char* resourceType, const char* resourceStatus);
}
