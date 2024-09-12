// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "SLGameStateBase.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_DELEGATE(FDel_TimeUpdate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDel_GameOver);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDel_OneMinuteOver);


UCLASS()
class SURVIVORLISE_API ASLGameStateBase : public AGameState
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	FDel_TimeUpdate TimeUpdateDelegate;
	FDel_GameOver GameOverDelegate;
	FDel_OneMinuteOver OneMinuteOverDelegate;

private:
	FTimerHandle GameTimerHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Setting", meta=(AllowPrivateAccess=true))
	int32 GameElapsedTime = 0;

	UFUNCTION()
	void UpdateTime();


public:
	UFUNCTION()
	void GameOver();
	FORCEINLINE const int32 GetGameElapsedTime() { return GameElapsedTime; }
};
