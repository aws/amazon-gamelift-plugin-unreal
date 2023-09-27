// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#pragma once

struct FTextIntPair
{
	FText Text;
	int32 Int;
	FText Description;

	FTextIntPair() {}
	FTextIntPair(FText InText, int32 InInt, FText InDescription = FText::FromString(TEXT("")) )
		: Text(InText), Int(InInt), Description(InDescription) {}
};
