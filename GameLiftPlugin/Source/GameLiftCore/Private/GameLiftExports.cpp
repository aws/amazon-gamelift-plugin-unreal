// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "GameLiftExports.h"

#include "IGameLiftCoreModule.h"

FString UGameLiftExports::GetGameLiftPluginName()
{
	return FString(Core::sGameLiftPluginName);
}
