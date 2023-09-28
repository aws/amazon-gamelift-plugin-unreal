// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "GameLiftExports.generated.h"

UCLASS()
class GAMELIFTCORE_API UGameLiftExports : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category = "GameLiftExports")
	static FString GetGameLiftPluginName();
};
