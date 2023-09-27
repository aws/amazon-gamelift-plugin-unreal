// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Framework\Docking\TabManager.h"
#include "WorkspaceMenuStructureModule.h"
#include "WorkspaceMenuStructure.h"

class FGameLiftTab
{
public:
	virtual ~FGameLiftTab() = default;

	virtual FName FTabName() = 0;
	virtual void Register() = 0;

	virtual void UnRegister()
	{
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(FTabName());
	}
	
	virtual void Invoke()
	{
		FGameLiftTab::Invoke(FTabName());
	}

	virtual bool IsAvailable()
	{
		return FGameLiftTab::IsAvailable(FTabName());
	}

	static inline void Invoke(FName TabId)
	{
		ensure(FGlobalTabmanager::Get()->HasTabSpawner(TabId));
		FGlobalTabmanager::Get()->TryInvokeTab(TabId);
	}

	static inline bool IsAvailable(FName TabId)
	{
		return FGlobalTabmanager::Get()->HasTabSpawner(TabId);
	}

protected:
	TSharedRef<SDockTab> MakeTab(const FSpawnTabArgs& SpawnTabArgs, TSharedRef<SWidget> Widget);

private:
	FName TabId;
};
