// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/SLExpItem.h"
#include "Components/SphereComponent.h"
#include "Character/SLMainCharacter.h"
#include "Controller/SLMainCharacterController.h"
#include "GameMode/SLPlayerState.h"
#include "Kismet/GameplayStatics.h"

void ASLExpItem::BeginPlay()
{
	Super::BeginPlay();

	MainCharacter = Cast<ASLMainCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	ItemCollision->OnComponentBeginOverlap.AddDynamic(this, &ASLExpItem::ExpGet);

}

void ASLExpItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MagnetFunction(DeltaTime);

}



void ASLExpItem::ExpGet(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == MainCharacter)
	{
		if (class ASLMainCharacterController* MainController = Cast<ASLMainCharacterController>(MainCharacter->GetController()))
		{
			class ASLPlayerState* MyPlayerState = Cast<ASLPlayerState>(MainController->GetPlayerState<ASLPlayerState>());

			MyPlayerState->ExpDelegate.ExecuteIfBound(GetExpAmount());
		}
		Destroy();
	}
}

void ASLExpItem::MagnetFunction(const float Value)
{
	float PlayerDistance = FVector::Dist(MainCharacter->GetActorLocation(), GetActorLocation());

	if (!bTest)
	{
		if (PlayerDistance <= 600.f)
		{
			bMagnetOn = true;
		}
		if (bMagnetOn)
		{
			FVector Direction = (MainCharacter->GetActorLocation() - GetActorLocation()).GetSafeNormal();
			SetActorLocation(GetActorLocation() + Direction * Itemflyspeed);
		}
	}
}

