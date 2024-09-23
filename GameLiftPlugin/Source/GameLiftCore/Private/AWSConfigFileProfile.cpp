// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "AWSConfigFileProfile.h"

#include "GameLiftCoreLog.h"
#include "Utils/StringConvertors.h"

#define LOCTEXT_NAMESPACE "AWSConfigFileProfile"

AWSConfigFileProfile::AWSConfigFileProfile()
{
	auto LogProxy = [](unsigned int InLevel, const char* InMessage, int InSize)
	{
		UE_LOG(GameLiftCoreLog, Log, TEXT("********* %s"), UTF8_TO_TCHAR(InMessage));
	};

	ConfigManagerInstance = GameLiftConfigManagerInstanceCreate(LogProxy);
}

AWSConfigFileProfile::~AWSConfigFileProfile()
{
	GameLiftConfigManagerInstanceRelease(ConfigManagerInstance);
	ConfigManagerInstance = nullptr;
}

TArray<FString> AWSConfigFileProfile::GetProfileNames() const
{
	TArray<FString> ProfilesNames;

	auto ProfileNameCallback = [](DISPATCH_RECEIVER_HANDLE ProfileNamesArray, const char* ProfileName)
	{
		((TArray<FString>*)(ProfileNamesArray))->Emplace(Convertors::ASToFS(ProfileName));
	};

	GameLiftConfigManagerGetProfileNames(ConfigManagerInstance, (void*)(&ProfilesNames), ProfileNameCallback);
	return ProfilesNames;
}

void AWSConfigFileProfile::CreateProfile(const FString& ProfileName)
{
	std::string StdProfileName = Convertors::FSToStdS(ProfileName);
	GameLiftConfigManagerCreateProfile(ConfigManagerInstance, StdProfileName.c_str());
}

void AWSConfigFileProfile::RenameProfile(const FString& ProfileName, const FString& NewProfileName)
{
	auto StdProfileName = Convertors::FSToStdS(ProfileName);
	auto stdNewProfileName = Convertors::FSToStdS(NewProfileName);
	GameLiftConfigManagerRenameProfile(ConfigManagerInstance, StdProfileName.c_str(), stdNewProfileName.c_str());
}

FString AWSConfigFileProfile::GetAccessKey(const FString& ProfileName) const
{
	auto StdProfileName = Convertors::FSToStdS(ProfileName);
	return Convertors::ASToFS(GameLiftConfigManagerGetAccessKey(ConfigManagerInstance, StdProfileName.c_str()));
}

void AWSConfigFileProfile::SetAccessKey(const FString& ProfileName, const FString& AccessKey)
{
	std::string StdProfileName = Convertors::FSToStdS(ProfileName);
	std::string stdAccessKey = Convertors::FSToStdS(AccessKey);
	GameLiftConfigManagerSetAccessKey(ConfigManagerInstance, StdProfileName.c_str(), stdAccessKey.c_str());
}

FString AWSConfigFileProfile::GetSecretAccessKey(const FString& ProfileName) const
{
	std::string StdProfileName = Convertors::FSToStdS(ProfileName);
	return Convertors::ASToFS(GameLiftConfigManagerGetSecretAccessKey(ConfigManagerInstance, StdProfileName.c_str()));
}

void AWSConfigFileProfile::SetSecretAccessKey(const FString& ProfileName, const FString& SecretAccessKey)
{
	std::string StdProfileName = Convertors::FSToStdS(ProfileName);
	std::string stdSecretKey = Convertors::FSToStdS(SecretAccessKey);
	GameLiftConfigManagerSetSecretAccessKey(ConfigManagerInstance, StdProfileName.c_str(), stdSecretKey.c_str());
}

FString AWSConfigFileProfile::GetSessionToken(const FString& ProfileName) const
{
	std::string StdProfileName = Convertors::FSToStdS(ProfileName);
	return Convertors::ASToFS(GameLiftConfigManagerGetSessionToken(ConfigManagerInstance, StdProfileName.c_str()));
}

void AWSConfigFileProfile::SetSessionToken(const FString& ProfileName, const FString& SessionToken)
{
	std::string StdProfileName = Convertors::FSToStdS(ProfileName);
	std::string stdSessionToken = Convertors::FSToStdS(SessionToken);
	GameLiftConfigManagerSetSessionToken(ConfigManagerInstance, StdProfileName.c_str(), stdSessionToken.c_str());
}

FString AWSConfigFileProfile::GetRegion(const FString& ProfileName) const
{
	std::string StdProfileName = Convertors::FSToStdS(ProfileName);
	return Convertors::ASToFS(GameLiftConfigManagerGetRegion(ConfigManagerInstance, StdProfileName.c_str()));
}

void AWSConfigFileProfile::SetRegion(const FString& ProfileName, const FString& Region)
{
	std::string StdProfileName = Convertors::FSToStdS(ProfileName);
	std::string StdRegion = Convertors::FSToStdS(Region);
	GameLiftConfigManagerSetRegion(ConfigManagerInstance, StdProfileName.c_str(), StdRegion.c_str());
}

void AWSConfigFileProfile::Save()
{
	GameLiftConfigManagerSave(ConfigManagerInstance);
}

#undef LOCTEXT_NAMESPACE
