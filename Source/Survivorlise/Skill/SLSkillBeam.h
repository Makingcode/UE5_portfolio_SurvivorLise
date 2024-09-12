// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SLSkillBase.h"
#include "SLSkillBeam.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORLISE_API ASLSkillBeam : public ASLSkillBase
{
	GENERATED_BODY()

public:
	ASLSkillBeam();

protected:
	virtual void BeginPlay() override;
	
private:
	void Attack();

	FVector Start;
	FVector End;

	FTimerHandle CheckerHandle;
	UFUNCTION()
	void FindEnemyChecker();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting", meta = (AllowPrivateAccess = true))
	float MaxRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting", meta = (AllowPrivateAccess = true))
	float BeamWidth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting", meta = (AllowPrivateAccess = true))
	float BeamHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting", meta = (AllowPrivateAccess = true))
	float Damage = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class UNiagaraComponent* BeamComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting", meta = (AllowPrivateAccess = true))
	class UNiagaraSystem* BeamEffect;

	void Init();
	
	UFUNCTION()
	void BeamDestroy();

	FTimerHandle BeamDestroyTimer;
};
