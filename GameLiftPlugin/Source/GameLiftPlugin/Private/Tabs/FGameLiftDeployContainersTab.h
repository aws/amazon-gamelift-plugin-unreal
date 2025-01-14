// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "FGameLiftTab.h"

class FGameLiftDeployContainersTab : public FGameLiftTab
{
public:
    static constexpr auto sTabName = TEXT("FGameLiftDeploymentGameTab");

    FName FTabName() override
    {
        return { sTabName };
    }

    void Register() override;

private:
    TSharedRef<SDockTab> HandleSpawnTab(const FSpawnTabArgs& SpawnTabArgs);
};
