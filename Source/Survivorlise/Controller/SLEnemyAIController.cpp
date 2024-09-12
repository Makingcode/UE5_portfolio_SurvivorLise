// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/SLEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

ASLEnemyAIController::ASLEnemyAIController()
{
	BlackBoardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComponent"));
}

void ASLEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	
	if (BlackBoardComp)
	{
		BlackBoardComp->SetValueAsObject("TargetActor", UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	}

	if (EnemyBehaviorTree)
	{
		RunBehaviorTree(EnemyBehaviorTree);
	}

}
