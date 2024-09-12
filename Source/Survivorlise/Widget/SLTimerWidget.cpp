// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SLTimerWidget.h"
#include "GameMode/SLGameStateBase.h"
#include "Components/TextBlock.h"

void USLTimerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MyGS = Cast<ASLGameStateBase>(GetWorld()->GetGameState());

	if (IsValid(MyGS))
	{
		MyGS->TimeUpdateDelegate.BindDynamic(this, &USLTimerWidget::UpdateTime);
	}

}

void USLTimerWidget::UpdateTime()
{
	int32 GameElapsedTime = MyGS->GetGameElapsedTime();
	int32 Hour = GameElapsedTime / 60;
	int32 Minute = GameElapsedTime % 60;
	
	FText CurrentTime = FText::FromString(FString::Printf(TEXT("%02d : %02d"), Hour, Minute));
	TB_Timer->SetText(CurrentTime);
}
