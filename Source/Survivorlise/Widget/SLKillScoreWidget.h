// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SLKillScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORLISE_API USLKillScoreWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* TB_Score;
	
	UFUNCTION()
	void SetKillScore(const int32 Value);

};
