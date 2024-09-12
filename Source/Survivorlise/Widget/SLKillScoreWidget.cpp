// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SLKillScoreWidget.h"
#include "Components/TextBlock.h"
#include "GameMode/SLPlayerState.h"
#include "Kismet/GameplayStatics.h"

void USLKillScoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ASLPlayerState* MyPS = Cast<ASLPlayerState>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetPlayerState<ASLPlayerState>()))
	{
		MyPS->KillCountWidgetDelegate.BindDynamic(this, &USLKillScoreWidget::SetKillScore);
	}

}

void USLKillScoreWidget::SetKillScore(const int32 Value)
{
	TB_Score->SetText(FText::FromString(FString::FromInt(Value)));
}
