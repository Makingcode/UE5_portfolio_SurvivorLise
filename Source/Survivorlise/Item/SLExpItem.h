// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ItemActorBase.h"
#include "SLExpItem.generated.h"

/**
 * 
 */


UCLASS()
class SURVIVORLISE_API ASLExpItem : public AItemActorBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setting|Exp", meta=(AllowPrivateAccess=true))
	int32 ExpAmount = 0;

	UFUNCTION()
	void ExpGet(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void MagnetFunction(const float Value);

	class ASLMainCharacter* MainCharacter;

	UPROPERTY(VisibleAnywhere)
	bool bMagnetOn = false;

	UPROPERTY(EditAnywhere, Category = "TEST")
	bool bTest = false;

public:
	
	FORCEINLINE const int32 GetExpAmount() { return ExpAmount; }

};
