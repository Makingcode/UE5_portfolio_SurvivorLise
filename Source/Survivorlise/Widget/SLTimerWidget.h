// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SLTimerWidget.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORLISE_API USLTimerWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TB_Timer;

	UFUNCTION()
	void UpdateTime();

	class ASLGameStateBase* MyGS = nullptr;
};
