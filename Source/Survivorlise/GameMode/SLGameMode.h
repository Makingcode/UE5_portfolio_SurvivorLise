// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Enum/LevelType.h"
#include "SLGameMode.generated.h"



DECLARE_DYNAMIC_DELEGATE(FDel_QuitGameDelegate);

UCLASS()
class SURVIVORLISE_API ASLGameMode : public AGameMode
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void ExitGame();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setting|LevelType", meta = (AllowPrivateAccess = true))
	ELevelType Level = ELevelType::None;

public:
	FDel_QuitGameDelegate ExitGameDelegate;



};
