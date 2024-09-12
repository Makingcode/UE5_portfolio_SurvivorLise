// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SLSelectCharacterIcon.generated.h"

/**
 * 
 */
class UButton;
class UImage;



UCLASS()
class SURVIVORLISE_API USLSelectCharacterIcon : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:

	UPROPERTY(meta = (BindWidget))
	UButton* Btn_SelectCharacter;





public:


public:
	
};
