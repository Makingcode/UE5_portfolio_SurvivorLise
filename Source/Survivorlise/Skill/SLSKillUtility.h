// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SLSkillBase.h"
#include "SLSKillUtility.generated.h"

/**
 * 
 */

class UNiagaraComponent;

UCLASS()
class SURVIVORLISE_API ASLSKillUtility : public ASLSkillBase
{
	GENERATED_BODY()
	
public:
	ASLSKillUtility();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UNiagaraComponent* SkillEffectComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FX", meta = (AllowPrivateAccess = true))
	class UNiagaraSystem* SkillNiagara;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting", meta=(AllowPrivateAccess=true))
	float SkillRange = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Setting", meta = (AllowPrivateAccess = true))
	float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting", meta = (AllowPrivateAccess = true))
	float SkillDelay = 0.f;

	void Init();

	float SkillRemoveTime = 0.f;

	class ASLSkillSpawner* OwnerSpawner;

	FTimerHandle DOTTimer;
	void DOT();

};
