// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <Interfaces/IPluginManager.h>
#include <Framework/Notifications/NotificationManager.h>
#include <Widgets/Notifications/SNotificationList.h>

#include "GameLiftPluginConstants.h"

namespace Notifier
{
	// Make sure to call from EAsyncExecution::TaskGraphMainThread
	inline TSharedPtr<SNotificationItem> CreateNotification(const FText& text)
	{
		FNotificationInfo Info(text);
		Info.bUseSuccessFailIcons = true;
		Info.bFireAndForget = false;
		Info.bUseThrobber = true;

		Info.Hyperlink = FSimpleDelegate::CreateLambda([]() { FGlobalTabmanager::Get()->TryInvokeTab(FName("OutputLog")); });
		Info.HyperlinkText = Menu::DeployCommon::kDeploymentShowOutputLog;

		auto NotificationItem = FSlateNotificationManager::Get().AddNotification(Info);

		if (GEditor)
		{
			GEditor->PlayEditorSound(TEXT("/Engine/EditorSounds/Notifications/CompileStart_Cue.CompileStart_Cue"));
		}

		NotificationItem->SetCompletionState(SNotificationItem::CS_Pending);
		return NotificationItem;
	}

	static constexpr auto kDefaultExpireDurationS = 5.0f;

	inline void CompleteNotification(TSharedPtr<SNotificationItem> NotificationItem, 
		SNotificationItem::ECompletionState State, const FString& Sound, const FText& NewText = FText::GetEmpty())
	{
		if (NotificationItem.IsValid())
		{
			Async(EAsyncExecution::TaskGraphMainThread, [NotificationItem, State, Sound = std::move(Sound), NewText = std::move(NewText)]()
			{
				if (!NewText.IsEmpty())
				{
					NotificationItem->SetText(NewText);
				}

				NotificationItem->SetExpireDuration(kDefaultExpireDurationS);
				NotificationItem->SetCompletionState(State);
				NotificationItem->ExpireAndFadeout();

				if (GEditor)
				{
					GEditor->PlayEditorSound(Sound);
				}
			});
		}
	}

	inline void UpdateTextNotification(TSharedPtr<SNotificationItem> NotificationItem, const FString& NewText)
	{
		if (NotificationItem.IsValid())
		{
			Async(EAsyncExecution::TaskGraphMainThread, [NotificationItem, NewText = std::move(NewText)]()
			{
				NotificationItem->SetText(FText::FromString(NewText));
			});
		}
	}

	inline void CompleteWithSuccess(TSharedPtr<SNotificationItem> NotificationItem, const FString& NewText = "")
	{
		CompleteNotification(NotificationItem, SNotificationItem::CS_Success, 
			TEXT("/Engine/EditorSounds/Notifications/CompileSuccess_Cue.CompileSuccess_Cue"), FText::FromString(NewText));
	}

	inline void CompleteWithFailure(TSharedPtr<SNotificationItem> NotificationItem, const FString& NewText = "")
	{		
		CompleteNotification(NotificationItem, SNotificationItem::CS_Fail,
			TEXT("/Engine/EditorSounds/Notifications/CompileFailed_Cue.CompileFailed_Cue"), FText::FromString(NewText));
	}
} // namespace Notifier
