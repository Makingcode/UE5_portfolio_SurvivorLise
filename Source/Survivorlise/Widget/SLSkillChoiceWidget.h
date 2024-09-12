// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SLSkillChoiceWidget.generated.h"

/**
 * 
 */

class UTextBlock;

UCLASS()
class SURVIVORLISE_API USLSkillChoiceWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_SkillChoice;
	
	UPROPERTY(meta=(BindWidget))
	class UImage* IMG_Skill;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TB_SkillExplain;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TB_SkillLevel;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TB_SkillName;

	UFUNCTION()
	void SkillSelect();

	FSkillDataTable ReceiveData;

public:
	UFUNCTION()
	void SkillDataLoad(FSkillDataTable Data);



};
