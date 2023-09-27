// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "AwsAccountCredentials.h"

#include <future>

#include "aws/gamelift/core/exports.h"

#include "GameLiftCoreLog.h"
#include "GameLiftCoreConstants.h"
#include "Utils/NativeLogPrinter.h"
#include "AwsErrors/Converter.h"

namespace AwsAccountCredentialsInternal
{
	void LogCallback(unsigned int InLevel, const char* InMessage, int InSize)
	{
		auto Level = Logs::PrintAwsLog(InLevel, InMessage, InSize, Credentials::Logs::kLogReceived);
	}
} // namespace AwsAccountCredentialsInternal

inline AwsAccountCredentials::AwsAccountCredentials(const FString& ProfileName, TSharedRef<IAWSConfigFileProfile> ProfileReader)
{
	StdRegion = Convertors::FSToStdS(ProfileReader->GetRegion(ProfileName));
	StdAccessKey = Convertors::FSToStdS(ProfileReader->GetAccessKey(ProfileName));
	StdSecretKey = Convertors::FSToStdS(ProfileReader->GetSecretAccessKey(ProfileName));
}

int AwsAccountCredentials::BuildCredentials()
{
	std::promise<std::string> Promise;

	CharPtrCallback DispatchReceiver = [](DISPATCH_RECEIVER_HANDLE InPromise, const char* CharPtr)
	{
		((std::promise<std::string>*) InPromise)->set_value(CharPtr);
	};

	unsigned int Status = GameLiftGetAwsAccountId(&Promise, DispatchReceiver, StdAccessKey.c_str(),
		StdSecretKey.c_str(), &AwsAccountCredentialsInternal::LogCallback);

	if (Status != GameLift::GAMELIFT_SUCCESS)
	{
		UE_LOG(GameLiftCoreLog, Error, TEXT("%s %s"), Credentials::Logs::kUnableToGetAccountId, *GameLiftErrorAsString::Convert(Status));
		return Status;
	}

	StdAccountId = Promise.get_future().get();

	return Status;
}

GameLift::AccountCredentials AwsAccountCredentials::GetCredentials() const
{
	GameLift::AccountCredentials GameLiftCredentials;

	GameLiftCredentials.region = StdRegion.c_str();
	GameLiftCredentials.accessKey = StdAccessKey.c_str();
	GameLiftCredentials.accessSecret = StdSecretKey.c_str();
	GameLiftCredentials.accountId = StdAccountId.c_str();

	return GameLiftCredentials;
}
