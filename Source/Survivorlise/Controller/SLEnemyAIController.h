// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SLEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORLISE_API ASLEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	ASLEnemyAIController();


protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BehaviorTree", meta = (AllowPrivateAccess = true))
	class UBehaviorTree* EnemyBehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BehaviorTree", meta = (AllowPrivateAccess = true))
	class UBlackboardComponent* BlackBoardComp;

	

public:
	FORCEINLINE UBehaviorTree* GetEnemyBehaviorTree() { return EnemyBehaviorTree; }
};
