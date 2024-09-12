// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SLCharacterBase.h"
#include "SLEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORLISE_API ASLEnemyCharacter : public ASLCharacterBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void Dead(const bool Value) override;

private:
	class ASLMainCharacter* MainCharacter;
	


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting", meta = (AllowPrivateAccess = true))
	float HitDamage = 10.f;

	UFUNCTION()
	void OverlapFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category = "Setting")
	TSubclassOf<class AItemActorBase> ExpItem;

	UPROPERTY(EditAnywhere, Category = "Setting")
	TSubclassOf<class AItemActorBase> HealthItem;

	UPROPERTY(EditAnywhere, Category = "Setting")
	TSubclassOf<class AItemActorBase> ShieldItem;


	UFUNCTION()
	void ExpItemCreate();

	UFUNCTION()
	void RecoveryItemCreate();


	void SetCharacterVisible();

	FTimerHandle VisibleTimer;

};
