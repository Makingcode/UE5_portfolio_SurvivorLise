// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SLGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Character/SLMainCharacter.h"

void ASLGameStateBase::BeginPlay()
{
	Super::BeginPlay();

	

	GetWorldTimerManager().SetTimer(GameTimerHandle, this, &ASLGameStateBase::UpdateTime, 1.f, true);

}

void ASLGameStateBase::UpdateTime()
{



	if (GameElapsedTime <= 1800)
	{
		GameElapsedTime++;
		TimeUpdateDelegate.ExecuteIfBound();

		if (GameElapsedTime % 60 == 0)
		{
			OneMinuteOverDelegate.Broadcast();
		}
	}
	else
	{
		//30분 게임 오버
		GameOver();
	}
}

void ASLGameStateBase::GameOver()
{
	GetWorldTimerManager().ClearTimer(GameTimerHandle);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
	//결과창 오픈
	GameOverDelegate.Broadcast();
	
}
