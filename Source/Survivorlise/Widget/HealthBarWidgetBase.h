// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidgetBase.generated.h"

/**
 * 
 */

class UProgressBar;

UCLASS()
class SURVIVORLISE_API UHealthBarWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* SP_ProgressBar;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HP_ProgressBar;

	UFUNCTION()
	void SetHPSPBar(float HPPercent, float SPPercent);
	
	void Init();



};
