// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "UGameLiftAnywhereStatus.h"

UGameLiftAnywhereStatus::UGameLiftAnywhereStatus(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UGameLiftAnywhereStatus::ResetStatus()
{
	UGameLiftAnywhereStatus* AnywhereStatus = GetMutableDefault<UGameLiftAnywhereStatus>();
	AnywhereStatus->DeployedRegion.Empty();
	AnywhereStatus->CustomLocation.Empty();
	AnywhereStatus->FleetName.Empty();
	AnywhereStatus->FleetId.Empty();
	AnywhereStatus->IsFleetDeployed = false;
	AnywhereStatus->ComputeName.Empty();
	AnywhereStatus->ComputeIPAddress.Empty();
	AnywhereStatus->IsComputeRegistered = false;
	AnywhereStatus->AuthToken.Empty();
	AnywhereStatus->AuthTokenExpirationTime = FDateTime(0);
	AnywhereStatus->PathToServerBuild.Empty();
	AnywhereStatus->PathToClientBuild.Empty();

	AnywhereStatus->SaveConfig();
}

bool UGameLiftAnywhereStatus::IsAnywhereReady()
{
	UGameLiftAnywhereStatus* AnywhereStatus = GetMutableDefault<UGameLiftAnywhereStatus>();

	// TODO: Check auth token expiration time.

	return !AnywhereStatus->CustomLocation.IsEmpty() &&
		AnywhereStatus->IsFleetDeployed &&
		AnywhereStatus->IsComputeRegistered;
}
