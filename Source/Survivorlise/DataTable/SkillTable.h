// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Skill/SLSkillBase.h"
#include "SkillTable.generated.h"

UENUM(BlueprintType)
enum class ESkillType : uint8
{
	None UMETA(DisplayName="None"),
	EST_AOE UMETA(DisplayName="AOE_Type"),
	EST_Linear UMETA(DisplayName="Linear_Type"),
	EST_Utility UMETA(DisplayName="Utility_Type"),
	EST_Beam UMETA(DisplayName="Beam_Type")
};

USTRUCT(BlueprintType)
struct FSkillDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Skill_Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Skill_Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Skill_Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Skill_Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Skill_CoolDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Skill_Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Skill_Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESkillType Skill_Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ASLSkillBase> SkillBPClass;

	//AddUnique ¿ë
	bool operator==(const FSkillDataTable& DataTable) const
	{
		return (Skill_Name == DataTable.Skill_Name && Skill_Level == DataTable.Skill_Level);
	}
};

