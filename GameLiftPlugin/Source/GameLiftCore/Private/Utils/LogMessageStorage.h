// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <mutex>

namespace Logs
{
	class MessageStorage
	{
	public:
		void Set(const char* NewMessage)
		{
			std::lock_guard<std::mutex> Guard(Mutex);
			Message = Convertors::ASToFS(NewMessage);
		}

		void Set(FString&& NewMessage)
		{
			std::lock_guard<std::mutex> Guard(Mutex);
			Message = std::move(NewMessage);
		}

		void Set(const FText& NewMessage)
		{
			std::lock_guard<std::mutex> Guard(Mutex);
			Message = NewMessage.ToString();
		}

		FString Get()
		{
			std::lock_guard<std::mutex> Guard(Mutex);
			return Message;
		}

		void Clear()
		{
			std::lock_guard<std::mutex> Guard(Mutex);
			Message.Reset();
		}

	private:
		FString Message = {};
		std::mutex Mutex = {};
	};
} // namespace Logs
