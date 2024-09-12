// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillComponent.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FDel_UsedSkill, TArray<FSkillDataTable>, UsedSkillArr);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDel_SkillCoolDown);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVORLISE_API USkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = true))
	TSubclassOf<class ASLSkillSpawner> SkillSpawner;
	
	//현재 사용중인 스킬데이터
	UPROPERTY()
	TArray<struct FSkillDataTable> CurrentUsedSkillData;

	//현재 사용중인 스킬스포너
	UPROPERTY()
	TArray<ASLSkillSpawner*> CurrentEquipSkillArr;


public:
	FDel_UsedSkill CurrentUsedSkillDelegate;
	FDel_SkillCoolDown SkillCoolDownDelegate;
	FORCEINLINE const TArray<struct FSkillDataTable> GetCurrentUsedSkillData() { return CurrentUsedSkillData; }
	FORCEINLINE const TArray<ASLSkillSpawner*> GetCurrentEquipSkillArr() { return CurrentEquipSkillArr; }

	void AddCurrentEquipSkill(ASLSkillSpawner* Value);
	UFUNCTION()
	void SpawnSkillSpawner();
	UFUNCTION()
	void SetCurrentUsedSkillData();
	UFUNCTION()
	void UpdateSkillSpawner();



};
