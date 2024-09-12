
// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SLSkillCoolDownWidget.h"
#include "DataTable/SkillTable.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"
#include "Component/SkillComponent.h"
#include "Skill/SLSkillSpawner.h"

void USLSkillCoolDownWidget::NativeConstruct()
{
	Super::NativeConstruct();

	IMG_Skill->SetOpacity(0.f);
	CooldownBar->SetPercent(1.f);
}



void USLSkillCoolDownWidget::SetupProgressBar()
{
	//1은 쿨타임중 0은 쿨타임 없음 0.1초마다 업데이트
	ElapsedTime += 0.1f;

	float CoolDownPercent = FMath::Clamp(1.f - (ElapsedTime / CoolDown),0.f,1.f);

	if (CooldownBar)
	{
		CooldownBar->SetPercent(CoolDownPercent);
	}

	if (ElapsedTime >= CoolDown)
	{
		//타이머 끝내기
		GetWorld()->GetTimerManager().ClearTimer(CoolDownTimer);
	}

}



void USLSkillCoolDownWidget::StartCoolDown(float CoolTime)
{
	ElapsedTime = 0.f;
	CoolDown = CoolTime;
	GetWorld()->GetTimerManager().SetTimer(CoolDownTimer, this, &USLSkillCoolDownWidget::SetupProgressBar, 0.1f, true);
}

void USLSkillCoolDownWidget::BindSpawnerInfo(ASLSkillSpawner* Spawner)
{
	if (Spawner)
	{
		SetSkillCoolDown(Spawner->GetCurrentSkillData());

		if (!Spawner->NoticeSkillUsedDelegate.IsBound())
		{
			Spawner->NoticeSkillUsedDelegate.AddDynamic(this, &USLSkillCoolDownWidget::StartCoolDown);
		}

	}
	
}


void USLSkillCoolDownWidget::SetSkillCoolDown(FSkillDataTable Value)
{
	IMG_Skill->SetOpacity(1.f);
	IMG_Skill->SetBrushFromTexture(Value.Skill_Image);

	CoolDown = Value.Skill_CoolDown;
	


}


