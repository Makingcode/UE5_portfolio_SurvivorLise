// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SLDebugWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/SLGameInstance.h"

void USLDebugWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	SetCurrentLevelName();
	
	if (USLGameInstance* MyGI = Cast<USLGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		if (MyGI->GetIsDebugMode())
		{
			SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			SetVisibility(ESlateVisibility::Collapsed);
		}
	}

	DebugCheckDelegate.BindDynamic(this, &USLDebugWidget::TurnOnOffDebugWidget);


}

void USLDebugWidget::TurnOnOffDebugWidget(const bool IsDebug)
{
	if (IsDebug)
	{
		SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		
		SetVisibility(ESlateVisibility::Collapsed);
	}
}

void USLDebugWidget::SetCurrentLevelName()
{
	FString CurrentLevelName = GetWorld()->GetMapName();
	TB_LevelName->SetText(FText::FromString(CurrentLevelName));
}


