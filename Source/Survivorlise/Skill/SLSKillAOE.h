// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SLSkillBase.h"
#include "SLSKillAOE.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORLISE_API ASLSKillAOE : public ASLSkillBase
{
	GENERATED_BODY()
	
public:
	ASLSKillAOE();

protected:
	virtual void BeginPlay() override;

private:
	//스킬의 범위(지름)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting", meta = (AllowPrivateAccess = true))
	float SkillRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class UDecalComponent* RangeIndicator_Decal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting", meta = (AllowPrivateAccess = true))
	float SkillDelay = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting", meta = (AllowPrivateAccess = true))
	int32 Damage = 0.f;

	class ASLSkillSpawner* OwnerSpawner;

	void Init();

	UFUNCTION()
	void RadialDamageApply();
};
