// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SLDebugWidget.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FDel_DebugCheck, bool, IsDebug);

class UTextBlock;

UCLASS()
class SURVIVORLISE_API USLDebugWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TB_LevelName;

	UFUNCTION()
	void TurnOnOffDebugWidget(const bool IsDebug);

	void SetCurrentLevelName();

public:
	FDel_DebugCheck DebugCheckDelegate;

};
