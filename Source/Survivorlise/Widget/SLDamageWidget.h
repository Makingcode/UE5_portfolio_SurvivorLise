// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SLDamageWidget.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORLISE_API USLDamageWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TB_Damage;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* IndicatorStart;

	UFUNCTION()
	void WidgetRemove();

public:
	void SetDamageAndPlayAnim(const float Damage);
};
