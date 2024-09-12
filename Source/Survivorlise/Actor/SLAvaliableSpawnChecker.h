// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SLAvaliableSpawnChecker.generated.h"

UCLASS()
class SURVIVORLISE_API ASLAvaliableSpawnChecker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASLAvaliableSpawnChecker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision", meta = (AllowPrivateAccess = true))
	class UBoxComponent* CheckerCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting", meta = (AllowPrivateAccess = true))
	bool WestSide = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting", meta = (AllowPrivateAccess = true))
	bool EastSide = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting", meta = (AllowPrivateAccess = true))
	bool NorthSide = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting", meta = (AllowPrivateAccess = true))
	bool SouthSide = false;


	UFUNCTION()
	void CharacterCheck(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void UnCheck(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
