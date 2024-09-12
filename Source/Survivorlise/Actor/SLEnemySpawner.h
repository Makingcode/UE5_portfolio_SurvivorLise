// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SLEnemySpawner.generated.h"



UCLASS()
class SURVIVORLISE_API ASLEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASLEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void SpawnEnemy();

	UFUNCTION()
	void StopSpawnEnemy();

	class ASLGameStateBase* MyGS = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn", meta = (AllowPrivateAccess = true))
	TSubclassOf<class ASLCharacterBase> EnemyBP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn", meta = (AllowPrivateAccess = true))
	TSubclassOf<class ASLCharacterBase> SpeedEnemyBP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn", meta = (AllowPrivateAccess = true))
	TSubclassOf<class ASLCharacterBase> TankEnemyBP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn", meta = (AllowPrivateAccess = true))
	TSubclassOf<class ASLCharacterBase> SuperEnemyBP;
	
	FTimerHandle EnemySpawnTimerHandle;

	UPROPERTY(EditAnywhere, Category = "SpawnSetting")
	float SpawnTimer = 0;

	void Init();

	UPROPERTY(VisibleAnywhere, Category="SpawnSetting")
	bool bStopSpawnWest = false;
	UPROPERTY(VisibleAnywhere, Category = "SpawnSetting")
	bool bStopSpawnEast = false;
	UPROPERTY(VisibleAnywhere, Category = "SpawnSetting")
	bool bStopSpawnNorth = false;
	UPROPERTY(VisibleAnywhere, Category = "SpawnSetting")
	bool bStopSpawnSouth = false;

	UFUNCTION()
	void SpawnLocationControll(const int32 Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="SpawnSetting|Time", meta=(AllowPrivateAccess=true))
	int32 SpawnLevel = 1;

	UFUNCTION()
	void SpawnLevelUp();


};
