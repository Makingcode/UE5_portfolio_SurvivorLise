// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controller/SLPlayerControllerBase.h"
#include "SLMainCharacterController.generated.h"

/**
 * 
 */
class UInputAction;
class UInputMappingContext;

UCLASS()
class SURVIVORLISE_API ASLMainCharacterController : public ASLPlayerControllerBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta=(AllowPrivateAccess=true))
	UInputMappingContext* IMC_Character;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = true))
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = true))
	UInputAction* MouseWheelAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = true))
	UInputAction* CameraRotateAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess=true))
	UInputAction* DashAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = true))
	UInputAction* AttackAction;


	UFUNCTION()
	void CharacterMove(const FInputActionValue& Value);
	UFUNCTION()
	void Dash();
	
	UFUNCTION()
	void CameraMove(const FInputActionValue& Value);
	UFUNCTION()
	void CameraArmLength(const FInputActionValue& Value);

	UFUNCTION()
	void AttackMovement();

	

public:

	
};
