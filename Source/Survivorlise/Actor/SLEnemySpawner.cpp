// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/SLEnemySpawner.h"
#include "GameMode/SLGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Character/SLMainCharacter.h"

// Sets default values
ASLEnemySpawner::ASLEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASLEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	MyGS = Cast<ASLGameStateBase>(GetWorld()->GetGameState<ASLGameStateBase>());
	if (ASLMainCharacter* PlayerCharacter = Cast<ASLMainCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		PlayerCharacter->PlayerDeadDelegate.AddDynamic(this, &ASLEnemySpawner::StopSpawnEnemy);
		PlayerCharacter->SpawnCheckerDelegate.AddDynamic(this, &ASLEnemySpawner::SpawnLocationControll);
	}
	if (MyGS)
	{
		MyGS->OneMinuteOverDelegate.AddDynamic(this, &ASLEnemySpawner::SpawnLevelUp);
	}

	GetWorldTimerManager().SetTimer(EnemySpawnTimerHandle, this, &ASLEnemySpawner::SpawnEnemy, SpawnTimer, true);

}

// Called every frame
void ASLEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASLEnemySpawner::SpawnEnemy()
{
	TArray<FVector> SpawnLocationArr;
	FVector PlayerLocation = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation();

	
	if (!bStopSpawnEast&&!bStopSpawnWest&&!bStopSpawnNorth&&!bStopSpawnSouth)
	{
		SpawnLocationArr.Add(PlayerLocation + FVector(-2000.f, 0, 0));
		SpawnLocationArr.Add(PlayerLocation + FVector(0,2000.f, 0));
		SpawnLocationArr.Add(PlayerLocation + FVector(0, -2000.f, 0));
		SpawnLocationArr.Add(PlayerLocation + FVector(2000.f, 0, 0));
	}
	else
	{
		if (bStopSpawnEast)
		{
			SpawnLocationArr.Add(PlayerLocation + FVector(-2000.f, 0, 0));
			if (bStopSpawnNorth)
			{
				SpawnLocationArr.Add(PlayerLocation + FVector(0, 2000.f, 0));
			}
			else if (bStopSpawnSouth)
			{
				SpawnLocationArr.Add(PlayerLocation + FVector(0, -2000.f, 0));
			}
			else
			{
				SpawnLocationArr.Add(PlayerLocation + FVector(0, 2000.f, 0));
				SpawnLocationArr.Add(PlayerLocation + FVector(0, -2000.f, 0));
			}
		}
		else if (bStopSpawnWest)
		{
			SpawnLocationArr.Add(PlayerLocation + FVector(2000.f, 0, 0));
			if (bStopSpawnNorth)
			{
				SpawnLocationArr.Add(PlayerLocation + FVector(0, 2000.f, 0));
			}
			else if (bStopSpawnSouth)
			{
				SpawnLocationArr.Add(PlayerLocation + FVector(0, -2000.f, 0));
			}
			else
			{
				SpawnLocationArr.Add(PlayerLocation + FVector(0, 2000.f, 0));
				SpawnLocationArr.Add(PlayerLocation + FVector(0, -2000.f, 0));
			}
		}

		if (bStopSpawnNorth)
		{
			SpawnLocationArr.Add(PlayerLocation + FVector(0, -2000.f, 0));
			if (bStopSpawnEast)
			{
				SpawnLocationArr.Add(PlayerLocation + FVector(-2000.f, 0, 0));
			}
			else if (bStopSpawnWest)
			{
				SpawnLocationArr.Add(PlayerLocation + FVector(2000.f, 0, 0));
			}
			else
			{
				SpawnLocationArr.Add(PlayerLocation + FVector(-2000.f, 0, 0));
				SpawnLocationArr.Add(PlayerLocation + FVector(2000.f, 0, 0));
			}
		}
		else if (bStopSpawnSouth)
		{
			SpawnLocationArr.Add(PlayerLocation + FVector(0, 2000.f, 0));
			if (bStopSpawnEast)
			{
				SpawnLocationArr.Add(PlayerLocation + FVector(-2000.f, 0, 0));
			}
			else if (bStopSpawnWest)
			{
				SpawnLocationArr.Add(PlayerLocation + FVector(2000.f, 0, 0));
			}
			else
			{
				SpawnLocationArr.Add(PlayerLocation + FVector(-2000.f, 0, 0));
				SpawnLocationArr.Add(PlayerLocation + FVector(2000.f, 0, 0));
			}
		}
	}

	int32 RandomIndex = FMath::RandRange(0, SpawnLocationArr.Num() - 1);
	FVector SpawnLocation = SpawnLocationArr[RandomIndex];
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	//EnemySpawn
	//추후 데이터테이블에서 EnemyBP를 가져와 적용하는 식으로 
	if (EnemyBP && SpeedEnemyBP && TankEnemyBP && SuperEnemyBP)
	{
		GetWorld()->SpawnActor<ASLCharacterBase>(EnemyBP, SpawnLocation,FRotator::ZeroRotator ,SpawnParams);
		if (SpawnLevel >= 2)
		{
			GetWorld()->SpawnActor<ASLCharacterBase>(SpeedEnemyBP, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
		}
		if (SpawnLevel >= 4)
		{
			GetWorld()->SpawnActor<ASLCharacterBase>(TankEnemyBP, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
		}
		if (SpawnLevel % 5 == 0)
		{
			GetWorld()->SpawnActor<ASLCharacterBase>(SuperEnemyBP, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
		}
	}
	
}

void ASLEnemySpawner::StopSpawnEnemy()
{
	GetWorldTimerManager().ClearTimer(EnemySpawnTimerHandle);
}

void ASLEnemySpawner::Init()
{
	MyGS = Cast<ASLGameStateBase>(GetWorld()->GetGameState<ASLGameStateBase>());
	if (ASLMainCharacter* PlayerCharacter = Cast<ASLMainCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		PlayerCharacter->PlayerDeadDelegate.AddDynamic(this, &ASLEnemySpawner::StopSpawnEnemy);
	}

	GetWorldTimerManager().SetTimer(EnemySpawnTimerHandle, this, &ASLEnemySpawner::SpawnEnemy, 1.f, true, -1.f);
}

void ASLEnemySpawner::SpawnLocationControll(const int32 Value)
{
	//Value =  1:동, 2:서, 3:남, 4:북

	switch (Value)
	{
	case 1:
	{
		if (bStopSpawnEast)
		{
			bStopSpawnEast = false;
		}
		else
		{
			bStopSpawnEast = true;
		}
		break;
	}
	case 2:
	{
		if (bStopSpawnWest)
		{
			bStopSpawnWest = false;
		}
		else
		{
			bStopSpawnWest = true;
		}
		break;
	}
	case 3:
	{
		if (bStopSpawnSouth)
		{
			bStopSpawnSouth = false;
		}
		else
		{
			bStopSpawnSouth = true;
		}
		
		break;
	}
	case 4:
	{
		if (bStopSpawnNorth)
		{
			bStopSpawnNorth = false;
		}
		else
		{
			bStopSpawnNorth = true;
		}
		break;
	}
	default:
		break;
	}
}

void ASLEnemySpawner::SpawnLevelUp()
{
	SpawnLevel += 1;
}



