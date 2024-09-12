// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SLDashWidget.h"
#include "Character/SLMainCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ProgressBar.h"

void USLDashWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MyCharacter = Cast<ASLMainCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
	if (MyCharacter)
	{
		MyCharacter->DashDelegate.BindDynamic(this, &USLDashWidget::StartCoolDown);
	}
}

void USLDashWidget::SetDashCoolTimeBar()
{
	if (MyCharacter)
	{
		ElapsedTime += 0.1f;

		float CoolDownPercent = FMath::Clamp(1.f-(ElapsedTime / Cooltime), 0.f, 1.f);
		if (DashCoolTimeBar)
		{
			DashCoolTimeBar->SetPercent(CoolDownPercent);
		}

		if (ElapsedTime >= Cooltime)
		{
			GetWorld()->GetTimerManager().ClearTimer(DashTimerhandle);
		}
	}
}

void USLDashWidget::StartCoolDown()
{
	if (MyCharacter)
	{
		ElapsedTime = 0.f;
		Cooltime = MyCharacter->GetCharacterDashCoolTime();
		GetWorld()->GetTimerManager().SetTimer(DashTimerhandle, this, &USLDashWidget::SetDashCoolTimeBar, 0.1f, true);
	}
}
