// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SLResultWidget.h"
#include "GameMode/SLGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "GameMode/SLGameInstance.h"
#include "Components/TextBlock.h"
#include "GameMode/SLPlayerState.h"

void USLResultWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_Exit->OnClicked.AddDynamic(this, &USLResultWidget::MoveToStartLevel);

	if (ASLGameStateBase* MyGS = Cast<ASLGameStateBase>(UGameplayStatics::GetGameState(GetWorld())))
	{
		MyGS->GameOverDelegate.AddDynamic(this, &USLResultWidget::ShowRecordScore);
		MyGS->GameOverDelegate.AddDynamic(this, &USLResultWidget::AnimStart);
	}

}

void USLResultWidget::AnimStart()
{
	PlayAnimation(FadeIn);
}

void USLResultWidget::MoveToStartLevel()
{
	if (USLGameInstance* GI = Cast<USLGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		GI->MoveLevelDelegate.ExecuteIfBound(ELevelType::ELT_Start);
	}
}

void USLResultWidget::ShowRecordScore()
{
	if (ASLGameStateBase* MyGS = Cast<ASLGameStateBase>(UGameplayStatics::GetGameState(GetWorld())))
	{
		int32 GameElapsedTime = MyGS->GetGameElapsedTime();
		int32 Hour = GameElapsedTime / 60;
		int32 Minute = GameElapsedTime % 60;

		FText CurrentTime = FText::FromString(FString::Printf(TEXT("Time : %02d : %02d"), Hour, Minute));

		TB_Time->SetText(CurrentTime);
	}
	if (ASLPlayerState* MyPS = Cast<ASLPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0)))
	{
		int32 KillScore = MyPS->GetKillScore();

		FText CurrentKillScore = FText::FromString(FString::Printf(TEXT("Kill : %d "), KillScore));
		TB_KillScore->SetText(CurrentKillScore);
	}
}
