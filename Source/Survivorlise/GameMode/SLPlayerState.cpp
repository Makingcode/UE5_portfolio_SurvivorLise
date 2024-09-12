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
	//����ġ ���
	if (GoalExp > CurrentExp)
	{
		//��ǥġ ����ġ�� �� �������
		CurrentExp += EarnedExp;

		if (CurrentExp >= GoalExp)
		{
			//�������� �Ѱ��
			const int32 RemainExp = CurrentExp - GoalExp;
			//GoalExp�� ���������̺��� ������ ���� ������
			CurrentExp = RemainExp;
			CharacterLevel += 1;
			UpdateGoalExp();
			SkillChoice();
		}
		
	}
	
	float ExpPercent = (float)CurrentExp / (float)GoalExp;

	//ExpBar Widget ������Ʈ
	ExpBarDelegate.ExecuteIfBound(ExpPercent);

}



void ASLPlayerState::UpdateGoalExp()
{
	//��ǥ����ġ ������Ʈ 
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
	//��ų������ ������ ������Ʈ
	UpdateSkillChoiceData();

	//Pause
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
	//��ų����â ����
	SkillChoiceDelegate.ExecuteIfBound();
}

void ASLPlayerState::SkillSelected()
{
	//��ų ���� ��
	//��ų������Ʈ���� ������ ��ų������ ���� Ȯ�� �� ���� (�������� ��������)
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
			//�̹� ������� ��ų�� ���	

		}
	}
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
	
}

void ASLPlayerState::UpdateSkillChoiceData()
{
	//���� ��� ��ų�����͸� ������
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
				//���� ��ų�� �����Ǿ� �ִ� ���
				TMap<FName, int32>EquipSkillLevels;
				for (FSkillDataTable CurrentSkillData : SkillComponent->GetCurrentUsedSkillData())
				{
					//���� �������� ��ų�̸� �� ����
					EquipSkillLevels.Add(CurrentSkillData.Skill_Name, CurrentSkillData.Skill_Level);
				}

				//�������� ��ų�� ���
				for (FSkillDataTable CurrentSkillData : SkillComponent->GetCurrentUsedSkillData())
				{
					int32* CurrentLevel = EquipSkillLevels.Find(AvaliableSkill->Skill_Name);
					//���� 1�ø���
					if (CurrentLevel)
					{
						if (AvaliableSkill->Skill_Level == *CurrentLevel + 1)
						{
							AvaliableSkillArr.AddUnique(*AvaliableSkill);
						}
					}
					else
					{	
						//���������� ���� ��ų�� ���� 1
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
