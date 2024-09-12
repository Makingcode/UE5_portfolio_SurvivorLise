// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SLPlayerState.h"
#include "DataTable/ExpTable.h"
#include "DataTable/SkillTable.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DataTable.h"
#include "Component/SkillComponent.h"
#include "Skill/SLSkillSpawner.h"

void ASLPlayerState::BeginPlay()
{
	Super::BeginPlay();

	UpdateGoalExp();

	ExpDelegate.BindDynamic(this, &ASLPlayerState::CalculateExp);
	SkillSelectedDelegate.AddDynamic(this, &ASLPlayerState::SkillSelected);
	KillCountDelegate.BindDynamic(this, &ASLPlayerState::SetKillScore);
}

void ASLPlayerState::CalculateExp(const int32 EarnedExp)
{
	//경험치 계산
	if (GoalExp > CurrentExp)
	{
		//목표치 경험치가 더 많은경우
		CurrentExp += EarnedExp;

		if (CurrentExp >= GoalExp)
		{
			//레벨업을 한경우
			const int32 RemainExp = CurrentExp - GoalExp;
			//GoalExp는 데이터테이블에서 가져온 값을 대입함
			CurrentExp = RemainExp;
			CharacterLevel += 1;
			UpdateGoalExp();
			SkillChoice();
		}
		
	}
	
	float ExpPercent = (float)CurrentExp / (float)GoalExp;

	//ExpBar Widget 업데이트
	ExpBarDelegate.ExecuteIfBound(ExpPercent);

}



void ASLPlayerState::UpdateGoalExp()
{
	//목표경험치 업데이트 
	FString ContextString = TEXT("ExpData LookUp");
	FExpDataTable* LevelData = ExpDataTable->FindRow<FExpDataTable>(FName(*FString::FromInt(CharacterLevel)), ContextString);

	if (IsValid(ExpDataTable))
	{
		if (LevelData)
		{
			GoalExp = LevelData->GoalExpValue;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerState : Not Selected ExpDataTable"));
	}
	LevelDelegate.ExecuteIfBound(CharacterLevel);
}

void ASLPlayerState::SkillChoice()
{
	//스킬위젯에 데이터 업데이트
	UpdateSkillChoiceData();

	//Pause
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
	//스킬선택창 오픈
	SkillChoiceDelegate.ExecuteIfBound();
}

void ASLPlayerState::SkillSelected()
{
	//스킬 선택 후
	//스킬컴포넌트에서 장착된 스킬스포너 갯수 확인 후 스폰 (갯수보다 적을때만)
	if (USkillComponent* SkillComponent = Cast<USkillComponent>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetComponentByClass<USkillComponent>()))
	{
		if (SkillComponent->GetCurrentEquipSkillArr().Num() < 6)
		{
			if (SkillComponent->GetCurrentEquipSkillArr().Num() == 0)
			{
				SkillComponent->SpawnSkillSpawner();
			}
			else
			{
				TArray<ASLSkillSpawner*> CurrentSkillSpawnerArr = SkillComponent->GetCurrentEquipSkillArr();
				bool bNeedSpawn = true;
				for (ASLSkillSpawner* CurrentSkillSpawner : CurrentSkillSpawnerArr)
				{
					if (CurrentSkillSpawner->GetCurrentSkillData().Skill_Name == GetReceivedData().Skill_Name)
					{
						CurrentSkillSpawner->SetMySkillData(GetReceivedData());
						SkillComponent->UpdateSkillSpawner();
						bNeedSpawn = false;
						break;
					}
				}
				if (bNeedSpawn)
				{
					SkillComponent->SpawnSkillSpawner();
				}
			}
			//이미 사용중인 스킬인 경우	

		}
	}
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
	
}

void ASLPlayerState::UpdateSkillChoiceData()
{
	//먼저 모든 스킬데이터를 가져옴
	TArray<FSkillDataTable> AvaliableSkillArr;
	if (USkillComponent* SkillComponent = Cast<USkillComponent>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetComponentByClass<USkillComponent>()))
	{
		for (FSkillDataTable* AvaliableSkill  : GetAllSkillDataArr(SkillDataTable))
		{
			if (SkillComponent->GetCurrentEquipSkillArr().Num() == 0)
			{
				if (AvaliableSkill->Skill_Level == 1)
				{
					AvaliableSkillArr.AddUnique(*AvaliableSkill);
				}
			}
			else
			{
				//현재 스킬이 장착되어 있는 경우
				TMap<FName, int32>EquipSkillLevels;
				for (FSkillDataTable CurrentSkillData : SkillComponent->GetCurrentUsedSkillData())
				{
					//현재 장착중인 스킬이름 및 레벨
					EquipSkillLevels.Add(CurrentSkillData.Skill_Name, CurrentSkillData.Skill_Level);
				}

				//장착중인 스킬의 경우
				for (FSkillDataTable CurrentSkillData : SkillComponent->GetCurrentUsedSkillData())
				{
					int32* CurrentLevel = EquipSkillLevels.Find(AvaliableSkill->Skill_Name);
					//레벨 1올리기
					if (CurrentLevel)
					{
						if (AvaliableSkill->Skill_Level == *CurrentLevel + 1)
						{
							AvaliableSkillArr.AddUnique(*AvaliableSkill);
						}
					}
					else
					{	
						//장착중이지 않은 스킬은 레벨 1
						if (AvaliableSkill->Skill_Level == 1)
						{
							AvaliableSkillArr.AddUnique(*AvaliableSkill);
						}
					}
				}
			}
		}	
	}
	if (AvaliableSkillArr.Num() != 0)
	{
		SkillDataLoadDelegate.ExecuteIfBound(AvaliableSkillArr);
	}

}

void ASLPlayerState::SetKillScore()
{
	KillScore += 1;
	KillCountWidgetDelegate.ExecuteIfBound(KillScore);
}

void ASLPlayerState::SetReceivedData(FSkillDataTable Value)
{
	ReceivedData = Value;
}

TArray<FSkillDataTable*> ASLPlayerState::GetAllSkillDataArr(UDataTable* Skill_DT)
{
	TArray<FSkillDataTable*> SkillAllDataArr;

	if (Skill_DT)
	{
		FString ContextString;
		Skill_DT->GetAllRows<FSkillDataTable>(ContextString, SkillAllDataArr);
	}

	return SkillAllDataArr;
}
