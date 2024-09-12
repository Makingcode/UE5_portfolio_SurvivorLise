// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ItemActorBase.h"
#include "SLHealthItem.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORLISE_API ASLHealthItem : public AItemActorBase
{
	GENERATED_BODY()
	

protected:
	virtual void BeginPlay() override;


private:
	UFUNCTION()
	void HPRecovery(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
