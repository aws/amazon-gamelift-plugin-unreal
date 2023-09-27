// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Async/Async.h"

#include "GameLiftPluginConstants.h"
#include "SWidgets/SSetupMessage.h"

#include "SocketSubsystem.h"

namespace Utils
{
	namespace Splitters
	{
		inline FString ExtractPathArgs(const FText& Path, TArray<FString>& Args)
		{
			FString RunPath = Path.ToString();
			FString Left, Right;
			if (RunPath.Split(TEXT(" "), &Left, &Right)) {
				RunPath = Left;
				bool GoAhead = true;
				do {
					if (Right.Split(TEXT(" "), &Left, &Right)) {
						Args.Add(Left);
					}
					else {
						Args.Add(Right);
						GoAhead = false;
					}
				} while (GoAhead);
			}
			return RunPath;
		}
	}

	inline void ShowLaunchProcessMessage(TSharedRef<SSetupMessage> MessageWidget, bool IsLaunched)
	{
		if (IsLaunched)
		{
			MessageWidget->SetSetupState(ESetupMessageState::ReadyToGoMessage);
		}
		else
		{
			MessageWidget->SetSetupState(ESetupMessageState::FailureMessage);
		}
		Async(EAsyncExecution::TaskGraphMainThread, [MessageWidget]
		{
			MessageWidget->DisableAfterTime(Menu::kStatusMessageActiveTimeSec);
		});
	}

	template<typename T>
	inline FText BuildLastestErrorMessage(const T& ErrorMessageProvider)
	{
		FString LastErorrMessage = ErrorMessageProvider.GetLastErrorMessage();
		if (!LastErorrMessage.IsEmpty())
		{
			return FText::Format(FText::FromString("{0}\n{1}"), FText::FromString(LastErorrMessage), Menu::kErrorUserMessageWithLog);
		}

		FString LastErorr = ErrorMessageProvider.GetLastError();
		return FText::Format(FText::FromString("{0}\n{1}"), Menu::kErrorUserMessageNoLog, FText::FromString(LastErorr));
	}

	inline FString GetLocalHostIPv4Address()
	{
		bool bCanBindAll;
		return ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLocalHostAddr(*GLog, bCanBindAll)->ToString(false);
	}

	inline FString GetLocalHostName()
	{
		FString LocalHostName;
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetHostName(LocalHostName);
		return LocalHostName;
	}
}
