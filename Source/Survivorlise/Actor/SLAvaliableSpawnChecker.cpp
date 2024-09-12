// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/SLAvaliableSpawnChecker.h"
#include "Components/BoxComponent.h"
#include "Character/SLMainCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASLAvaliableSpawnChecker::ASLAvaliableSpawnChecker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CheckerCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("CheckerCollision"));
	CheckerCollision->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ASLAvaliableSpawnChecker::BeginPlay()
{
	Super::BeginPlay();
	
	CheckerCollision->OnComponentBeginOverlap.AddDynamic(this, &ASLAvaliableSpawnChecker::CharacterCheck);
	CheckerCollision->OnComponentEndOverlap.AddDynamic(this, &ASLAvaliableSpawnChecker::UnCheck);
	

}


// Called every frame
void ASLAvaliableSpawnChecker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ASLAvaliableSpawnChecker::CharacterCheck(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ASLMainCharacter* MyCharacter = Cast<ASLMainCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		if (OtherActor == MyCharacter)
		{
			if (EastSide)
			{
				MyCharacter->SpawnCheckerDelegate.Broadcast(1);
			}
			else if (WestSide)
			{
				MyCharacter->SpawnCheckerDelegate.Broadcast(2);
			}
			else if (SouthSide)
			{
				MyCharacter->SpawnCheckerDelegate.Broadcast(3);
			}
			else if (NorthSide)
			{
				MyCharacter->SpawnCheckerDelegate.Broadcast(4);
			}
		}
	}
}

void ASLAvaliableSpawnChecker::UnCheck(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ASLMainCharacter* MyCharacter = Cast<ASLMainCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		if (OtherActor == MyCharacter)
		{
			if (EastSide)
			{
				MyCharacter->SpawnCheckerDelegate.Broadcast(1);
			}
			else if (WestSide)
			{
				MyCharacter->SpawnCheckerDelegate.Broadcast(2);
			}
			else if (SouthSide)
			{
				MyCharacter->SpawnCheckerDelegate.Broadcast(3);
			}
			else if (NorthSide)
			{
				MyCharacter->SpawnCheckerDelegate.Broadcast(4);
			}
		}
	}
}

