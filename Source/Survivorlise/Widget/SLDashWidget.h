// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SLDashWidget.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORLISE_API USLDashWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void SetDashCoolTimeBar();

	UFUNCTION()
	void StartCoolDown();

	float ElapsedTime;
	float Cooltime;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* DashCoolTimeBar;
	
	FTimerHandle DashTimerhandle;
	
	class ASLMainCharacter* MyCharacter;
};
