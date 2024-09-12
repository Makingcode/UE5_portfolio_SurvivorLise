// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LevelType.generated.h"

UENUM(BlueprintType)
enum class ELevelType : uint8
{
	None UMETA(DisplayName = "None"),
	ELT_Start UMETA(DisplayName = "Start"),
	ELT_Loading UMETA(DisplayName = "Loading"),
	ELT_Main UMETA(DisplayName = "Main")
};

