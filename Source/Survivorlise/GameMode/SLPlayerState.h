// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DataTable/SkillTable.h"
#include "SLPlayerState.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_DELEGATE_OneParam(FDel_ExpDelegate, int32, EarnExp);
DECLARE_DYNAMIC_DELEGATE_OneParam(FDel_ExpBar, float, ExpPercentage);
DECLARE_DYNAMIC_DELEGATE_OneParam(FDel_Level, int32, LevelValue);
DECLARE_DYNAMIC_DELEGATE(FDel_SkillChoice);
DECLARE_DYNAMIC_DELEGATE_OneParam(FDel_SkillDataLoad, TArray<FSkillDataTable>, SkillData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDel_SkillSelected);
DECLARE_DYNAMIC_DELEGATE(FDel_KillCount);
DECLARE_DYNAMIC_DELEGATE_OneParam(FDel_KillCountWidget, int32, KillCount);


UCLASS()
class SURVIVORLISE_API ASLPlayerState : public APlayerState
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus", meta=(AllowPrivateAccess=true))
	int32 CharacterLevel = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus", meta = (AllowPrivateAccess = true))
	int32 CurrentExp = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus", meta = (AllowPrivateAccess = true))
	int32 GoalExp = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterStatus", meta = (AllowPrivateAccess = true))
	int64 KillScore = 0;

	UFUNCTION()
	void CalculateExp(const int32 EarnedExp);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (AllowPrivateAccess = true))
	class UDataTable* ExpDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (AllowPrivateAccess = true))
	class UDataTable* SkillDataTable;

	UFUNCTION()
	void UpdateGoalExp();

	UFUNCTION()
	void SkillChoice();

	UFUNCTION()
	void SkillSelected();

	FSkillDataTable ReceivedData;

	UFUNCTION()
	void UpdateSkillChoiceData();

	UPROPERTY(VisibleAnywhere, Category="Count")
	int32 DeathCount = 0;

	UFUNCTION()
	void SetKillScore();

public:

	FDel_ExpDelegate ExpDelegate;
	FDel_ExpBar ExpBarDelegate;
	FDel_Level LevelDelegate;
	FDel_SkillChoice SkillChoiceDelegate;
	FDel_SkillDataLoad SkillDataLoadDelegate;
	FDel_SkillSelected SkillSelectedDelegate;
	FDel_KillCount KillCountDelegate;
	FDel_KillCountWidget KillCountWidgetDelegate;

	FORCEINLINE const int32 GetCharacterLevel() { return CharacterLevel; }
	FORCEINLINE const int32 GetCurrentExp() { return CurrentExp; }
	FORCEINLINE const int32 GetGoalExp() { return GoalExp; }
	FORCEINLINE const int32 GetKillScore() { return KillScore; }
	FORCEINLINE const FSkillDataTable GetReceivedData() { return ReceivedData; }
	

	void SetReceivedData(FSkillDataTable Value);

	

	TArray<FSkillDataTable*> GetAllSkillDataArr(UDataTable* Skill_DT);
	

};
