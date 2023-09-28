// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GameLiftPluginConstants.h"

enum class EDeploymentMessageState
{
	NoDeploymentMessage,
	InProgressMessage,
	AbortInProgressMessage,
	FailureMessage,
	ActiveMessage
};

constexpr bool IsInProgressState(EDeploymentMessageState MessageState)
{
	return MessageState == EDeploymentMessageState::InProgressMessage ||
		MessageState == EDeploymentMessageState::AbortInProgressMessage;
}

constexpr auto EDeploymentMessageStateFromInt(int v)
{
	if (v < int(EDeploymentMessageState::NoDeploymentMessage) || v > int(EDeploymentMessageState::ActiveMessage))
	{
		return EDeploymentMessageState::NoDeploymentMessage;
	}
	return EDeploymentMessageState(v);
}

constexpr auto* EDeploymentMessageStateToString(EDeploymentMessageState MessageState)
{
	switch (MessageState)
	{
		case EDeploymentMessageState::NoDeploymentMessage: return Menu::DeployManagedEC2::kNoDeployment;
		case EDeploymentMessageState::InProgressMessage: return Menu::DeployManagedEC2::kInProgressDeployment;
		case EDeploymentMessageState::AbortInProgressMessage: return Menu::DeployManagedEC2::kAbortInProgressDeployment;
		case EDeploymentMessageState::FailureMessage: return Menu::DeployManagedEC2::kFailedDeployment;
		case EDeploymentMessageState::ActiveMessage: return Menu::DeployManagedEC2::kActiveDeployment;
		default:
			break;
	}
	ensure(false);

	return Menu::DeployManagedEC2::kNoDeployment;
}

inline EDeploymentMessageState EDeploymentMessageStateFromString(const FString& StateString)
{
	if (StateString.Compare(Menu::DeployManagedEC2::kNoDeployment) == 0 || 
		StateString.Compare(Menu::DeployManagedEC2::kNoDeployment_Alternate) == 0)
	{
		return EDeploymentMessageState::NoDeploymentMessage;
	}
	else if (StateString.Compare(Menu::DeployManagedEC2::kInProgressDeployment) == 0)
	{
		return EDeploymentMessageState::InProgressMessage;
	}
	else if (StateString.Compare(Menu::DeployManagedEC2::kAbortInProgressDeployment) == 0)
	{
		return EDeploymentMessageState::AbortInProgressMessage;
	}
	else if (StateString.Compare(Menu::DeployManagedEC2::kFailedDeployment) == 0)
	{
		return EDeploymentMessageState::FailureMessage;
	}
	else if (StateString.Compare(Menu::DeployManagedEC2::kActiveDeployment) == 0 || 
		StateString.Compare(Menu::DeployManagedEC2::kActiveDeployment_Alternate) == 0)
	{
		return EDeploymentMessageState::ActiveMessage;
	}
	ensure(false);

	return EDeploymentMessageState::NoDeploymentMessage;
}
