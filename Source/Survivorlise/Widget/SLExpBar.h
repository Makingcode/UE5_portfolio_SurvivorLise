// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SLExpBar.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORLISE_API USLExpBar : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* ExpBar;

	UFUNCTION()
	void UpdateExpBar(const float Value);

public:
	FORCEINLINE UProgressBar* GetExpBar() { return ExpBar; }
};
