// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORLISE_API UMainGameWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* WS_MainWGSwitch;

	class ASLGameStateBase* MyGS = nullptr;

	class ASLPlayerState* MyPS = nullptr;

	UFUNCTION()
	void SetResultWidget();

	UFUNCTION()
	void ShowSkillChoiceScreen();

	UFUNCTION()
	void AfterSkillSelected();
};
