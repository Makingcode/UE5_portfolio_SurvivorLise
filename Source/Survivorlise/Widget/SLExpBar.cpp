// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SLExpBar.h"
#include "Components/ProgressBar.h"
#include "GameMode/SLPlayerState.h"
#include "Kismet/GamePlayStatics.h"

void USLExpBar::NativeConstruct()
{
	Super::NativeConstruct();

	

	if (ASLPlayerState* PS = Cast<ASLPlayerState>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPlayerState<ASLPlayerState>()))
	{
		PS->ExpBarDelegate.BindDynamic(this,&USLExpBar::UpdateExpBar);

		float ExpPercent = (float)PS->GetCurrentExp() / (float)PS->GetGoalExp();
		ExpBar->SetPercent(ExpPercent);
	}
}

void USLExpBar::UpdateExpBar(const float Value)
{
	ExpBar->SetPercent(Value);
}
