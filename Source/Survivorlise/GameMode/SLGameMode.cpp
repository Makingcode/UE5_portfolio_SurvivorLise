// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SLGameMode.h"
#include "HUD/SLHUD.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GamePlayStatics.h"
#include "GameMode/SLGameInstance.h"

void ASLGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (USLGameInstance* GI = Cast<USLGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		GI->SetLevelType(Level);
	}
	ExitGameDelegate.BindDynamic(this, &ASLGameMode::ExitGame);
}

void ASLGameMode::ExitGame()
{
	//게임종료
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit,false);
}
