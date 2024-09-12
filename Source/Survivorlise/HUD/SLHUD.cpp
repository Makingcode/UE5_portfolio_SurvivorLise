// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/SLHUD.h"
#include "Kismet/GameplayStatics.h"

#include "GameMode/SLGameInstance.h"
#include "Widget/SLStartWidget.h"
#include "Widget/SLLoadingWidget.h"
#include "Widget/MainGameWidget.h"



void ASLHUD::BeginPlay()
{
	if (USLGameInstance* MyGI = Cast<USLGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		switch (MyGI->GetLevelType())
		{
			case ELevelType::None :
			{
				UE_LOG(LogTemp, Warning, TEXT("Current LevelType : ELT_None"));
				break;
			}
			case ELevelType::ELT_Start :
			{
				//레벨타입이 스타트
				UE_LOG(LogTemp, Warning, TEXT("Current LevelType : ELT_Start"));
				if (IsValid(StartWidget))
				{
					class USLStartWidget* GameStartWidget = CreateWidget<USLStartWidget>(GetWorld(), StartWidget);
					GameStartWidget->AddToViewport();
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("HUD : Please Select StartWidget"));
				}
				break;
			}
			case ELevelType::ELT_Loading :
			{
				UE_LOG(LogTemp, Warning, TEXT("Current LevelType : ELT_Loading"))

				if (IsValid(LoadingWidget))
				{
					class USLLoadingWidget* LoadingWG = CreateWidget<USLLoadingWidget>(GetWorld(), LoadingWidget);
					LoadingWG->AddToViewport();
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("HUD : Please Select LoadingWidget"));
				}
				break;
			}
			case ELevelType::ELT_Main :
			{
				UE_LOG(LogTemp, Warning, TEXT("Current LevelType : ELT_Main"));
				if (IsValid(MainPlayWidget))
				{
					UMainGameWidget* MainGameWidget = CreateWidget<UMainGameWidget>(GetWorld(), MainPlayWidget);
					MainGameWidget->AddToViewport();
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("HUD : Please Select MainPlayWidget"));
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MyGI cast Failed"));
	}

}

void ASLHUD::LoadingWidgetTurnOnOff(const bool IsTurnOn)
{
	if (IsValid(LoadingWidget))
	{
		if (IsValid(GameLoadingWidget))
		{
			if (IsTurnOn)
			{
				UE_LOG(LogTemp, Warning, TEXT("GameLoadingWidget On"));
				GameLoadingWidget->AddToViewport();
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("GameLoadingWidget Off"));
				GameLoadingWidget->RemoveFromParent();
			}
		}
		else
		{
			GameLoadingWidget = CreateWidget<USLLoadingWidget>(GetWorld(), LoadingWidget);
			GameLoadingWidget->AddToViewport();
		}
		
		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HUD : Not Selected LoadingScreenWidget"));
	}
}
