// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ExpTable.generated.h"

USTRUCT(BlueprintType)
struct FExpDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentLevel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 GoalExpValue;

};

