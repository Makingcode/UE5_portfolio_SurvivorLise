// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SLCharacterBase.h"
#include "Components/WidgetComponent.h"
#include "Widget/HealthBarWidgetBase.h"
#include "Widget/SLDamageWidget.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASLCharacterBase::ASLCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

}

// Called when the game starts or when spawned
void ASLCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	RecoveryTypeDelegate.BindDynamic(this, &ASLCharacterBase::HPSPCalculate);
	
}

// Called every frame
void ASLCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASLCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASLCharacterBase::Dead(const bool Value)
{
	if (Value)
	{
		if (GetController())
		{
			GetController()->Destroy();
		}

		Destroy();
	}
}




void ASLCharacterBase::HPSPCalculate(int32 Amount, ERecoveryType Type)
{
	//���������� ���� ������
	int32 BreakDamage = 0;
	switch (Type)
	{
	case ERecoveryType::None:
		break;

	case ERecoveryType::ERDT_HPRecovery:
	{
		if (Health < MaxHealth)
		{
			Health += Amount;
		}
		else
		{
			Health = MaxHealth;
		}
		SPPercent = (float)ShieldPoint / (float)MaxShieldPoint;
		HPPercent = (float)Health / (float)MaxHealth;

		RecoveryDelegate.ExecuteIfBound(HPPercent, SPPercent);

		break;
	}
	case ERecoveryType::ERDT_ShieldRecovery:
	{
		if (ShieldPoint < MaxShieldPoint)
		{
			ShieldPoint += Amount;
		}
		else
		{
			ShieldPoint = MaxShieldPoint;
		}
		SPPercent = (float)ShieldPoint / (float)MaxShieldPoint;
		HPPercent = (float)Health / (float)MaxHealth;
		RecoveryDelegate.ExecuteIfBound(HPPercent, SPPercent);
		break;
	}
	default:
		break;
	}
}

void ASLCharacterBase::SetIsDead(const bool Value)
{
	IsDead = Value;
}

float ASLCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	//���� ����� ������� �ı�
	if (!bInvincible)
	{
		if (DamageWidgetBP)
		{
			DamageWidget = CreateWidget<USLDamageWidget>(GetWorld(), DamageWidgetBP);
			if (DamageWidget)
			{
				DamageWidget->AddToViewport();
				FVector WorldLocation = GetActorLocation();
				FVector2D ScreenLocation;
				UGameplayStatics::ProjectWorldToScreen(UGameplayStatics::GetPlayerController(GetWorld(), 0), WorldLocation, ScreenLocation);

				DamageWidget->SetPositionInViewport(ScreenLocation);
				DamageWidget->SetDamageAndPlayAnim(DamageAmount);

				FTimerHandle WidgetRemoveHandle;
				
			}

		}

		//�������°� �ƴҶ�
		if (ShieldPoint > 0)
		{
			if (ShieldPoint - DamageAmount < 0)
			{
				float RemainDamage = ShieldPoint - DamageAmount;
			
				ShieldPoint = 0;
				Health -= -RemainDamage;

				if (Health <= 0)
				{
					SetIsDead(true);
					Dead(GetIsDead());
				}
			}
			else
			{
				ShieldPoint -= DamageAmount;
			}
		}
		else
		{
			//���尡 ������
			Health -= DamageAmount;
			if (Health <= 0)
			{
				Health = 0;
				SetIsDead(true);
				Dead(GetIsDead());
			}
		}
	
		float CurrentHPPer = (float)Health / (float)MaxHealth;
		float CurrentSPPer = (float)ShieldPoint / (float)MaxShieldPoint;

		
		DamageDelegate.Broadcast(CurrentHPPer, CurrentSPPer);
	}

	return DamageAmount;
}










