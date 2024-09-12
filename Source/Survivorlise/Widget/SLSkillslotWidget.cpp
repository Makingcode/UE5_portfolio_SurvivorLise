// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SLSkillslotWidget.h"
#include "Component/SkillComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DataTable/SkillTable.h"
#include "Widget/SLSkillCoolDownWidget.h"
#include "Skill/SLSkillSpawner.h"

void USLSkillslotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SkillTimerArr.Add(SkillTimer1);
	SkillTimerArr.Add(SkillTimer2);
	SkillTimerArr.Add(SkillTimer3);
	SkillTimerArr.Add(SkillTimer4);
	SkillTimerArr.Add(SkillTimer5);

	if (USkillComponent* MySkillComponent = Cast<USkillComponent>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetComponentByClass<USkillComponent>()))
	{
		MySkillComponent->SkillCoolDownDelegate.AddDynamic(this, &USLSkillslotWidget::BindSpawnerAndWidget);
	}

}



void USLSkillslotWidget::BindSpawnerAndWidget()
{
	if (USkillComponent* MySkillComponent = Cast<USkillComponent>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetComponentByClass<USkillComponent>()))
	{
		for (int32 i = 0; i < MySkillComponent->GetCurrentEquipSkillArr().Num(); i++)
		{
			SkillTimerArr[i]->BindSpawnerInfo(MySkillComponent->GetCurrentEquipSkillArr()[i]);
		}
	}

}



