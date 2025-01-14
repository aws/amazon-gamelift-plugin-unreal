// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"

class SHelpfulResourcesSection : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SHelpfulResourcesSection) {}

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);
};

