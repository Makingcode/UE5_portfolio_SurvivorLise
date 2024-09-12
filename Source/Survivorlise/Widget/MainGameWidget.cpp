// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MainGameWidget.h"
#include "Components/WidgetSwitcher.h"
#include "GameMode/SLGameStateBase.h"
#include "GameMode/SLPlayerState.h"
#include "Kismet/GamePlayStatics.h"

void UMainGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	WS_MainWGSwitch->SetActiveWidgetIndex(0);
	MyGS = Cast<ASLGameStateBase>(GetWorld()->GetGameState<ASLGameStateBase>());
	MyPS = Cast<ASLPlayerState>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPlayerState<ASLPlayerState>());


	if (IsValid(MyGS))
	{
		MyGS->GameOverDelegate.AddDynamic(this, &UMainGameWidget::SetResultWidget);
		//0 = playwidget, 1 = result widget;
	}
	if (IsValid(MyPS))
	{
		MyPS->SkillChoiceDelegate.BindDynamic(this, &UMainGameWidget::ShowSkillChoiceScreen);
		MyPS->SkillSelectedDelegate.AddDynamic(this, &UMainGameWidget::AfterSkillSelected);
	}

	
	
}

void UMainGameWidget::SetResultWidget()
{
	WS_MainWGSwitch->SetActiveWidgetIndex(1);
}

void UMainGameWidget::ShowSkillChoiceScreen()
{
	WS_MainWGSwitch->SetActiveWidgetIndex(2);
}

void UMainGameWidget::AfterSkillSelected()
{
	WS_MainWGSwitch->SetActiveWidgetIndex(0);
}
