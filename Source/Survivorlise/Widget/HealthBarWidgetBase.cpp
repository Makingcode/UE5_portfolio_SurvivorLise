// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/HealthBarWidgetBase.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"
#include "Character/SLMainCharacter.h"

void UHealthBarWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
	
	Init();

	if (ASLMainCharacter* MyCharacter = Cast<ASLMainCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		MyCharacter->DamageDelegate.AddDynamic(this, &UHealthBarWidgetBase::SetHPSPBar);
		MyCharacter->RecoveryDelegate.BindDynamic(this, &UHealthBarWidgetBase::SetHPSPBar);
	}

}

void UHealthBarWidgetBase::SetHPSPBar(float HPPercent, float SPPercent)
{
	HP_ProgressBar->SetPercent(HPPercent);
	SP_ProgressBar->SetPercent(SPPercent);
}

void UHealthBarWidgetBase::Init()
{
	HP_ProgressBar->SetPercent(1.f);
	SP_ProgressBar->SetPercent(0.f);
	SP_ProgressBar->SetVisibility(ESlateVisibility::Visible);
	HP_ProgressBar->SetVisibility(ESlateVisibility::Visible);
}


