// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SLSkillSpawner.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDel_NoticeSkillUsed, float, Cooltimes);


UCLASS()
class SURVIVORLISE_API ASLSkillSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASLSkillSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:


	void SpawnSkillReady();

	FSkillDataTable CurrentSkillData;

	FTimerHandle SkillSpawnHandle;

	UFUNCTION()
	void SpawnSkill();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooltime", meta = (AllowPrivateAccess = true))
	TSubclassOf<UUserWidget> CoolTimeWidget;

	class USLSkillslotWidget* MySkillSlotWidget;
	
	class ASLMainCharacter* MyMainCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property", meta = (AllowPrivateAccess = true))
	int32 SkillLevel = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property", meta = (AllowPrivateAccess = true))
	FName SkillName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property", meta = (AllowPrivateAccess = true))
	float Cooltime = 0.f;

public:
	FDel_NoticeSkillUsed NoticeSkillUsedDelegate;

	void SetMySkillData(FSkillDataTable Value);
	
	FORCEINLINE const FSkillDataTable GetCurrentSkillData() { return CurrentSkillData; }

	
};
