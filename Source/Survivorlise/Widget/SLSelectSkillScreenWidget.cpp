// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SLSelectSkillScreenWidget.h"
#include "Widget/SLSkillChoiceWidget.h"
#include "GameMode/SLPlayerState.h"
#include "DataTable/SkillTable.h"
#include "Kismet/GameplayStatics.h"

void USLSelectSkillScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (ASLPlayerState* MyPS = Cast<ASLPlayerState>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPlayerState<ASLPlayerState>()))
	{
		MyPS->SkillDataLoadDelegate.BindDynamic(this, &USLSelectSkillScreenWidget::ApplySkillData);
	}
}

void USLSelectSkillScreenWidget::ApplySkillData(TArray<FSkillDataTable> LoadedData)
{
	if (LoadedData.Num() != 0)
	{
		if (IsValid(Skill1)&&IsValid(Skill2)&&IsValid(Skill3))
		{
			Skill1->SkillDataLoad(LoadedData[FMath::RandRange(0, LoadedData.Num() - 1)]);
			Skill2->SkillDataLoad(LoadedData[FMath::RandRange(0, LoadedData.Num() - 1)]);
			Skill3->SkillDataLoad(LoadedData[FMath::RandRange(0, LoadedData.Num() - 1)]);
		}
	}
}
