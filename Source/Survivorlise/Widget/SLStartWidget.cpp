// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SLStartWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/SizeBox.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/SLGameMode.h"
#include "GameMode/SLGameInstance.h"


void USLStartWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	TB_Title->SetText(FText::FromString(TEXT("Survivor Lise")));
	TB_Start->SetText(FText::FromString(TEXT("StartGame")));
	TB_Exit->SetText(FText::FromString(TEXT("ExitGame")));
}

void USLStartWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_Start->OnClicked.AddDynamic(this, &USLStartWidget::StartGame);
	Btn_Exit->OnClicked.AddDynamic(this, &USLStartWidget::ExitGame);

}

void USLStartWidget::StartGame()
{
	UE_LOG(LogTemp, Warning, TEXT("StartGame"));
	if (USLGameInstance* GI = Cast<USLGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		GI->MoveLevelDelegate.ExecuteIfBound(ELevelType::ELT_Main);
	}

}

void USLStartWidget::ExitGame()
{
	class ASLGameMode* MyGameMode = Cast<ASLGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (MyGameMode)
	{
		MyGameMode->ExitGameDelegate.ExecuteIfBound();
	}
}
