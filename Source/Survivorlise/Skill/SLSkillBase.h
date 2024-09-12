// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SLSkillBase.generated.h"

UCLASS()
class SURVIVORLISE_API ASLSkillBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASLSkillBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particles", meta = (AllowPrivateAccess = true))
	class UParticleSystem* SkillEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particles", meta = (AllowPrivateAccess = true))
	FVector SkillEffectSize = FVector(0, 0, 0);
	void SkillDestroy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class USceneComponent* RootComp;
	

private:


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
