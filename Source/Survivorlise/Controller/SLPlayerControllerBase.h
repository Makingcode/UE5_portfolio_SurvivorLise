// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameMode/SLGameInstance.h"
#include "SLPlayerControllerBase.generated.h"


UCLASS()
class SURVIVORLISE_API ASLPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	

private:


public:

#pragma region DebugTest

#pragma endregion
};
