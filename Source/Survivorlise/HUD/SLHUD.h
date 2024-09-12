// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SLHUD.generated.h"

class USLStartWidget;
class USLLoadingWidget;
class UMainGameWidget;

UCLASS()
class SURVIVORLISE_API ASLHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;


private:
	
	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	TSubclassOf<USLStartWidget> StartWidget;
	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	TSubclassOf<UMainGameWidget> MainPlayWidget;
	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	TSubclassOf<USLLoadingWidget> LoadingWidget;

	USLLoadingWidget* GameLoadingWidget = nullptr;

public:
	void LoadingWidgetTurnOnOff(const bool IsTurnOn);

};
