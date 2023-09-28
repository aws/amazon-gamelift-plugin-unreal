// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "WinGameLiftCoreProc.h"
#include "Misc/InteractiveProcess.h"
#include "Interfaces/IPluginManager.h"

#include "Utils/StringPaths.h"
#include "GameLiftCoreLog.h"
#include "GameLiftCoreConstants.h"

#include "Windows/AllowWindowsPlatformTypes.h"
#include <shellapi.h>
#include <ShlObj.h>
#include <LM.h>
#include <Psapi.h>
#include <TlHelp32.h>
#include "Windows/HideWindowsPlatformTypes.h"
#include "Windows/WindowsPlatformMisc.h"

#define LOCTEXT_NAMESPACE "GameLiftCoreProc"

namespace Internal
{
	bool IsCmd(const FString& Path)
	{
		return Path.Contains("cmd");
	}

	std::pair<bool, FProcHandle> RunExe(const FString& Path, const FString& Params = "")
	{
		UE_LOG(GameLiftCoreLog, Log, TEXT("Launch process %s : %s"), *Path, *Params);

		if (!IsCmd(Path) && !FPaths::FileExists(Path))
		{
			UE_LOG(GameLiftCoreLog, Error, TEXT("Launch process failed %s : %s. File not found"), *Path, *Params);
			return { false, {} };
		}
		auto Proc = FPlatformProcess::CreateProc(*Path, *Params, true, false, false, nullptr, 0, nullptr, nullptr);

		if (!Proc.IsValid())
		{
			FPlatformProcess::CloseProc(Proc);
			return { false, Proc };
		}

		return { true, Proc };
	}

	FString ArgumentArrayToString(TArray<FString> Arguments)
	{
		FString Params;

		for (const auto& Arg : Arguments)
		{
			Params += " " + Arg;
		}

		return Params;
	}

	std::pair<bool, FProcHandle> LaunchWindowsCmd(const FString& Path, TArray<FString> Arguments)
	{
		if (!FPaths::FileExists(Path))
		{
			UE_LOG(GameLiftCoreLog, Error, TEXT("Launch process failed %s. File not found"), *Path);
			return { false, {} };
		}

		auto CmdParams = "start cmd.exe @cmd /k \"" + Path + "\"";
		CmdParams += ArgumentArrayToString(Arguments);

		return RunExe(FString("cmd.exe"), CmdParams);
	}

	auto IsWinProcRunning(FProcHandle& ProcessHandle, unsigned int WaitMs = 0)
	{
		bool bApplicationRunning = true;
		uint32 WaitResult = ::WaitForSingleObject(ProcessHandle.Get(), WaitMs);

		if (WaitResult != WAIT_TIMEOUT)
		{
			FPlatformProcess::CloseProc(ProcessHandle);
			bApplicationRunning = false;
		}

		return bApplicationRunning;
	}

	bool ValidateProcessOutput(const FString& Path, TArray<FString> Arguments, const FString& ExpectedValue)
	{
		if (Path.IsEmpty())
		{
			return false;
		}

		FString Output;
		FInteractiveProcess process(Path, ArgumentArrayToString(Arguments), true);

		process.OnOutput().BindLambda([&Output](const FString& stdOut)
		{
			Output += stdOut;
		});

		process.Launch();

		auto processHandle = process.GetProcessHandle();
		::WaitForSingleObject(processHandle.Get(), Process::kWaitForProcMs);

		return Output.Contains(ExpectedValue);
	}
}

bool GameLiftCoreProc::LaunchProcess(const FString& Path, TArray<FString> Arguments)
{
	static const auto kWaitMs = 500;
	bool IsLaunched = false;
	auto Status = Internal::LaunchWindowsCmd(Path, Arguments);

	if (Status.first)
	{
		IsLaunched = Internal::IsWinProcRunning(Status.second, kWaitMs);
	}

	return IsLaunched;
}

#undef LOCTEXT_NAMESPACE

GameLiftCoreProc::GameLiftCoreProc()
{
}
