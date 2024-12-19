// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

enum class EContainersDeploymentScenario
{
    NoContainerImageNoExistingEcrRepo,
    NoContainerImageUseExistingEcrRepo,
    HaveContainerImageInDocker,
    HaveContainerImageInEcr
};

enum class EDeploymentScenarioFleetRegionType {
    SingleRegion,
    MultiRegionFlexMatch
};

enum class EContainerFleetDeploymentStatus {
    DeploymentNotStart,
    DeploymentInProgress,
    DeploymentComplete
};