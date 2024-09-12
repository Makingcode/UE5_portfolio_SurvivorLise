
// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SLEnemyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Character/SLMainCharacter.h"
#include "GameMode/SLPlayerState.h"
#include "Item/SLExpItem.h"
#include "Item/SLHealthItem.h"


void ASLEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	MainCharacter = Cast<ASLMainCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
	if (UCapsuleComponent* MyCapsuleComp = Cast<UCapsuleComponent>(GetCapsuleComponent()))
	{
		MyCapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &ASLEnemyCharacter::OverlapFunc);
	}


	GetWorldTimerManager().SetTimer(VisibleTimer, this, &ASLEnemyCharacter::SetCharacterVisible,0.5f,true);
}

void ASLEnemyCharacter::Dead(const bool Value)
{
	if (Value)
	{
		if (ASLPlayerState* MyPS = Cast<ASLPlayerState>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetPlayerState<ASLPlayerState>()))
		{
			MyPS->KillCountDelegate.ExecuteIfBound();
			ExpItemCreate();
			RecoveryItemCreate();
			GetWorldTimerManager().ClearTimer(VisibleTimer);

			Super::Dead(Value);
		}
	}
}

void ASLEnemyCharacter::OverlapFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == MainCharacter)
	{
		if (OtherComp != MainCharacter->GetEnemyCheckCollision())
		{
			UGameplayStatics::ApplyDamage(OtherActor, HitDamage, GetController(), this, nullptr);
		}
	}

}

void ASLEnemyCharacter::ExpItemCreate()
{
	int32 CreateNum = FMath::RandRange(0, 1);

	if (CreateNum != 0)
	{
		if (ExpItem)
		{
			FVector SpawnLocation = GetActorLocation();
			FRotator SpawnRotation = FRotator::ZeroRotator;
			FActorSpawnParameters SpawnParams;
			GetWorld()->SpawnActor<ASLExpItem>(ExpItem, SpawnLocation, SpawnRotation, SpawnParams);
		}
	}

}

void ASLEnemyCharacter::RecoveryItemCreate()
{
	int32 CreateNum = FMath::RandRange(0, 9);

	if (CreateNum <= 0)
	{
		//아이템 생성
		//쉴드아이템인지 체력생성템인지 고르기
		int ItemSelectNum = FMath::RandRange(0, 1);
		if (ItemSelectNum == 0)
		{
			if (HealthItem)
			{
				FVector SpawnLocation = GetActorLocation();
				FRotator SpawnRotation = FRotator::ZeroRotator;
				FActorSpawnParameters SpawnParams;
				GetWorld()->SpawnActor<class ASLHealthItem>(HealthItem, SpawnLocation, SpawnRotation, SpawnParams);
			}
		}
		else
		{
			if (ShieldItem)
			{
				FVector SpawnLocation = GetActorLocation();
				FRotator SpawnRotation = FRotator::ZeroRotator;
				FActorSpawnParameters SpawnParams;
				GetWorld()->SpawnActor<class ASLShieldItem>(ShieldItem, SpawnLocation, SpawnRotation, SpawnParams);
			}
		}

	}
}

void ASLEnemyCharacter::SetCharacterVisible()
{
	float Distance = FVector::Dist(GetActorLocation(), MainCharacter->GetActorLocation());

	if (Distance >= 2500.f)
	{
		GetMesh()->SetVisibility(false);
	}
	else
	{ 
		GetMesh()->SetVisibility(true);
	}
}


