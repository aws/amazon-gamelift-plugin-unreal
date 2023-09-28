// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"

#include "GameLiftPluginConstants.h"

#include "UGameLiftInternalSettings.generated.h"

UCLASS(config = EditorPerProjectUserSettings)
class UGameLiftInternalSettings
	: public UObject
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(config, EditAnywhere, Category = "Deploy Game Run")
	FFilePath DeployGameClientPath;
};
