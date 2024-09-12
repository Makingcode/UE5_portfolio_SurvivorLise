// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SLSelectSkillScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORLISE_API USLSelectSkillScreenWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class USLSkillChoiceWidget* Skill1;
	UPROPERTY(meta = (BindWidget))
	class USLSkillChoiceWidget* Skill2;
	UPROPERTY(meta = (BindWidget))
	class USLSkillChoiceWidget* Skill3;

	UFUNCTION()
	void ApplySkillData(TArray<FSkillDataTable> LoadedData);
};
