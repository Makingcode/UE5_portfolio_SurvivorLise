// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/SLMainCharacterController.h"
#include "EnhancedInputcomponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/SLMainCharacter.h"


void ASLMainCharacterController::BeginPlay()
{
	Super::BeginPlay();
	
	SetShowMouseCursor(false);

	//키매핑
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(IMC_Character, 0);
	}

}

void ASLMainCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComp->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASLMainCharacterController::CharacterMove);
		EnhancedInputComp->BindAction(DashAction, ETriggerEvent::Triggered, this, &ASLMainCharacterController::Dash);
		EnhancedInputComp->BindAction(CameraRotateAction, ETriggerEvent::Triggered, this, &ASLMainCharacterController::CameraMove);
		EnhancedInputComp->BindAction(MouseWheelAction, ETriggerEvent::Triggered, this, &ASLMainCharacterController::CameraArmLength);
		EnhancedInputComp->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ASLMainCharacterController::AttackMovement);
	}
	
}

void ASLMainCharacterController::CharacterMove(const FInputActionValue& Value)
{
	//컨트롤러가 빙의가 안되어있으면 기능X
	if (ASLMainCharacter* MyControlledCharacter = Cast<ASLMainCharacter>(GetCharacter()))
	{
		const FVector2D MoveValue = Value.Get<FVector2D>();
		const FRotator Rotation = MyControlledCharacter->GetControlRotation();
		const FRotator YawRotation= FRotator(0, Rotation.Yaw, 0);

		FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		MyControlledCharacter->AddMovementInput(ForwardDirection, MoveValue.X);
		MyControlledCharacter->AddMovementInput(RightDirection, MoveValue.Y);

	}
}

void ASLMainCharacterController::Dash()
{
	if (ASLMainCharacter* MyControlledCharacter = Cast<ASLMainCharacter>(GetCharacter()))
	{
		MyControlledCharacter->DashFunction();
	}
}



void ASLMainCharacterController::CameraMove(const FInputActionValue& Value)
{
	//컨트롤러가 빙의가 안되어있으면 기능X
	if (ASLMainCharacter* MyControlledCharacter = Cast<ASLMainCharacter>(GetCharacter()))
	{
		const FVector2D XYValue = Value.Get<FVector2D>();
		const float XValue = XYValue.X;
		const float YValue = (XYValue.Y * -1.f)*0.5f;

		AddYawInput(XValue);
		AddPitchInput(YValue);
	}
}

void ASLMainCharacterController::CameraArmLength(const FInputActionValue& Value)
{
	if (ASLMainCharacter* MyControlledCharacter = Cast<ASLMainCharacter>(GetCharacter()))
	{
		const float ArmLength = Value.Get<float>();
		MyControlledCharacter->SetTargetArmLength(ArmLength);
	}
}

void ASLMainCharacterController::AttackMovement()
{
	if (ASLMainCharacter* MyControlledCharacter = Cast<ASLMainCharacter>(GetCharacter()))
	{
		MyControlledCharacter->Attack();
	}
}


