// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SLResultWidget.generated.h"

/**
 * 
 */
class UTextBlock;

UCLASS()
class SURVIVORLISE_API USLResultWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TB_KillScore;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TB_Time;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Exit;

	UPROPERTY(Transient,meta = (BindWidgetAnim))
	class UWidgetAnimation* FadeIn;

	UFUNCTION()
	void AnimStart();

	UFUNCTION()
	void MoveToStartLevel();

	UFUNCTION()
	void ShowRecordScore();

};
