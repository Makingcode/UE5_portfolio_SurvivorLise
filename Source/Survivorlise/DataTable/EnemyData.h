// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EnemyData.generated.h"

USTRUCT(BlueprintType)
struct FEnemyDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EnemyLevel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HP;
	
	

};

