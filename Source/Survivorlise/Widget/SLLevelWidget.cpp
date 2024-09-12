// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SLLevelWidget.h"
#include "Components/TextBlock.h"
#include "GameMode/SLPlayerState.h"
#include "Kismet/GamePlayStatics.h"

void USLLevelWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ASLPlayerState* MyPS = Cast<ASLPlayerState>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPlayerState<ASLPlayerState>()))
	{
		MyPS->LevelDelegate.BindDynamic(this, &USLLevelWidget::UpdateLevelText);
	}

}

void USLLevelWidget::UpdateLevelText(const int32 CurrentLevel)
{
	FText LevelText = FText::FromString(FString::Printf(TEXT("LV : %d"), CurrentLevel));
	TB_Level->SetText(LevelText);
}
