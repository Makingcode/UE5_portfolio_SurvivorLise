// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SLLevelWidget.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORLISE_API USLLevelWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TB_Level;

	UFUNCTION()
	void UpdateLevelText(const int32 CurrentLevel);
};
