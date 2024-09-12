// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SLSkillCoolDownWidget.generated.h"

/**
 * 
 */
//��ų ��ٿ� ����

UCLASS()
class SURVIVORLISE_API USLSkillCoolDownWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UImage* IMG_Skill;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* CooldownBar;

	UPROPERTY()
	float CoolDown = 0.f;

	void SetupProgressBar();

	UFUNCTION()
	void StartCoolDown(float Cooltime);

	FTimerHandle CoolDownTimer;

	UPROPERTY()
	float ElapsedTime;

public:
	UFUNCTION()
	void SetSkillCoolDown(FSkillDataTable Value);
	UFUNCTION()
	void BindSpawnerInfo(ASLSkillSpawner* Spawner);
};
