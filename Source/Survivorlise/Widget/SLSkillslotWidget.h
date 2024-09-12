// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SLSkillslotWidget.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORLISE_API USLSkillslotWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class USLSkillCoolDownWidget* SkillTimer1;
	UPROPERTY(meta = (BindWidget))
	class USLSkillCoolDownWidget* SkillTimer2;
	UPROPERTY(meta = (BindWidget))
	class USLSkillCoolDownWidget* SkillTimer3;
	UPROPERTY(meta = (BindWidget))
	class USLSkillCoolDownWidget* SkillTimer4;
	UPROPERTY(meta = (BindWidget))
	class USLSkillCoolDownWidget* SkillTimer5;
	
	UFUNCTION()
	void BindSpawnerAndWidget();



	UPROPERTY()
	TArray<USLSkillCoolDownWidget*> SkillTimerArr;

};
