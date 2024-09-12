// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SLStartWidget.generated.h"

/**
 * 
 */
class UTextBlock;
class USizeBox;
class UButton;
class ASLPlayerControllerBase;

UCLASS()
class SURVIVORLISE_API USLStartWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	USizeBox* SB_Title;

	UPROPERTY(meta = (BindWidget))
	USizeBox* SB_Menu;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TB_Title;

	UPROPERTY(meta = (BindWidget))
	UButton* Btn_Start;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TB_Start;

	UPROPERTY(meta = (BindWidget))
	UButton* Btn_Exit;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TB_Exit;

private:
	UFUNCTION()
	void StartGame();
	UFUNCTION()
	void ExitGame();

};
