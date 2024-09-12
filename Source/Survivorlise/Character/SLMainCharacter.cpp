// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SLMainCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Widget/HealthBarWidgetBase.h"
#include "Controller/SLMainCharacterController.h"
#include "Component/SkillComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"
#include "GameMode/SLGameStateBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"


ASLMainCharacter::ASLMainCharacter()
{
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	MainCharCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));

	CameraSpringArm->SetupAttachment(RootComponent);
	MainCharCamera->SetupAttachment(CameraSpringArm);

	SkillComponent = CreateDefaultSubobject<USkillComponent>(TEXT("SkillComponent"));
	
	HealthBarWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidgetComp"));
	HealthBarWidgetComp->SetupAttachment(RootComponent);

	EnemyCheckCollision = CreateDefaultSubobject<USphereComponent>(TEXT("EnemyCheckCollision"));
	EnemyCheckCollision->SetupAttachment(RootComponent);

	LeftWeapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftWeapon"));
	LeftWeapon->SetupAttachment(GetMesh(), "LeftWeaponSocket");
	RightWeapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightWeapon"));
	RightWeapon->SetupAttachment(GetMesh(), "RightWeaponSocket");

	DashFXComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("DashFXComponent"));
	DashFXComponent->SetupAttachment(RootComponent);
}

void ASLMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	EnemyCheckCollision->OnComponentBeginOverlap.AddDynamic(this, &ASLMainCharacter::AddEnemyCount);
	EnemyCheckCollision->OnComponentEndOverlap.AddDynamic(this, &ASLMainCharacter::SubstractEnemyCount);

}

void ASLMainCharacter::Dead(const bool Value)
{
	if (Value)
	{
		GetController()->UnPossess();
	}


	//죽었을때 죽음 관련 애니메이션 재생필요

	PlayerDeadDelegate.Broadcast();
	if (ASLGameStateBase* MyGS = Cast<ASLGameStateBase>(UGameplayStatics::GetGameState(GetWorld())))
	{
		MyGS->GameOver();
	}

	Destroy();

}

void ASLMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void ASLMainCharacter::DashFunction()
{
	if (bAvaliableDash)
	{
		DashDelegate.ExecuteIfBound();
		bAvaliableDash = false;
		bInvincible = true;

		ActiveDashParticle();
		GetMesh()->SetVisibility(false);
		LeftWeapon->SetVisibility(false);
		RightWeapon->SetVisibility(false);

		FVector Direction = GetLastMovementInputVector().GetSafeNormal();
		if (Direction.IsZero())
		{
			Direction = GetActorForwardVector();
		}
		
		FVector LaunchDirection = Direction * CharacterDashDistance;
		//대쉬
		LaunchCharacter(LaunchDirection, true, true);

		FTimerHandle DashTimer;
		GetWorldTimerManager().SetTimer(DashTimer, this, &ASLMainCharacter::DashControll, CharacterDashCoolTime, false);
		FTimerHandle InvincibleTimer;
		GetWorldTimerManager().SetTimer(InvincibleTimer, this, &ASLMainCharacter::InvincibleControll, DashInvicibleTime, false);
	}

}

void ASLMainCharacter::DashControll()
{
	bAvaliableDash = true;
}

void ASLMainCharacter::InvincibleControll()
{
	DashFXComponent->SetActive(false);
	GetMesh()->SetVisibility(true);
	LeftWeapon->SetVisibility(true);
	RightWeapon->SetVisibility(true);
	bInvincible = false;
}

void ASLMainCharacter::ActiveDashParticle()
{
	if (DashFX && !DashFXComponent->IsActive())
	{
		DashFXComponent->SetAsset(DashFX);
		DashFXComponent->SetActive(true);
	}
}

void ASLMainCharacter::Attack()
{
	if (!bAttacking)
	{
		bAttacking = true;

		UAnimInstance* MyAnimInstance = GetMesh()->GetAnimInstance();
		if (MyAnimInstance && AttackMontage)
		{
			FName AttackSectionName = (AttackIndex == 0) ? FName("AttackStart") : FName("Attack_1");

			MyAnimInstance->Montage_Play(AttackMontage);
			MyAnimInstance->Montage_JumpToSection(AttackSectionName, AttackMontage);

			float AttackDuration = AttackMontage->GetSectionLength(AttackIndex);
			

			GetWorldTimerManager().SetTimer(StopAttackHandle, this, &ASLMainCharacter::ResetAttack, AttackDuration, false);
			
		}

	}
	
}

void ASLMainCharacter::ResetAttack()
{
	bAttacking = false;
	DamagedActors.Empty();
	AttackIndex = (AttackIndex + 1) % 2;
}



void ASLMainCharacter::AddEnemyCount(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		NearEnemyArr.Add(OtherActor);
	}
}

void ASLMainCharacter::SubstractEnemyCount(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		NearEnemyArr.Remove(OtherActor);
	}
}

void ASLMainCharacter::SetTargetArmLength(const float Value)
{
	const float CurrentTargetArmlength = CameraSpringArm->TargetArmLength + (CameraBoomSpeed * (Value * -1.f));
	CameraSpringArm->TargetArmLength = CurrentTargetArmlength;

	//TargetArmLength가 200.f 보다 작아질시
	if (CurrentTargetArmlength < MinSpringArmLength)
	{
		CameraSpringArm->TargetArmLength = MinSpringArmLength;
	}
	else if (CurrentTargetArmlength > MaxSpringArmLength)
	{
		CameraSpringArm->TargetArmLength = MaxSpringArmLength;
	}
}

void ASLMainCharacter::AttackHitCheck()
{
	if (RightWeapon&&LeftWeapon)
	{
		switch (AttackIndex)
		{
		case 0:
		{
			FVector Start = RightWeapon->GetSocketLocation("SwordStart");
			FVector End = RightWeapon->GetSocketLocation("SwordEnd");
			float Radius = 20.f;
		
			TArray<FHitResult> HitResults;
			FCollisionQueryParams QueryParams;
			QueryParams.AddIgnoredActor(this);

			//ECC_GameTraceChannel6 = Weapon 채널
			float bHit = GetWorld()->SweepMultiByChannel(HitResults, Start, End, FQuat::Identity, ECC_GameTraceChannel6, FCollisionShape::MakeSphere(Radius), QueryParams);
		
			if (bTest)
			{
				DrawDebugLine(GetWorld(), Start, End, FColor::Red,false ,5.f);
			}

			if (bHit)
			{
				for (FHitResult HitResult : HitResults)
				{
					if (!DamagedActors.Contains(HitResult.GetActor()))
					{
						UGameplayStatics::ApplyDamage(HitResult.GetActor(), 10.f, GetController(), this, nullptr);
						DamagedActors.Add(HitResult.GetActor());
					}

				}
			}
			break;
		}
		case 1:
		{
			FVector Start = LeftWeapon->GetSocketLocation("SwordStart");
			FVector End = LeftWeapon->GetSocketLocation("SwordEnd");
			float Radius = 20.f;

			TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
			ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel6));

			TArray<FHitResult> HitResults;
			FCollisionQueryParams QueryParams;
			QueryParams.AddIgnoredActor(this);

			float bHit = GetWorld()->SweepMultiByChannel(HitResults, Start, End, FQuat::Identity, ECC_GameTraceChannel6, FCollisionShape::MakeSphere(Radius), QueryParams);

			if (bTest)
			{
				DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 5.f);
			}

			if (bHit)
			{
				for (FHitResult HitResult : HitResults)
				{
					if (!DamagedActors.Contains(HitResult.GetActor()))
					{
						UGameplayStatics::ApplyDamage(HitResult.GetActor(), 10.f, GetController(), this, nullptr);
						DamagedActors.Add(HitResult.GetActor());
					}
				}
			}
			break;
		}
		default:
			break;
		}

	}
}

void ASLMainCharacter::AttackHitCheckEnd()
{
	GetWorldTimerManager().ClearTimer(AttackTraceHandle);
}

void ASLMainCharacter::AttackTimer()
{
	GetWorldTimerManager().SetTimer(AttackTraceHandle, this, &ASLMainCharacter::AttackHitCheck, 0.01f, true);
}


