// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SLCharacterBase.h"
#include "SLMainCharacter.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDel_CharacterDead);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDel_AvailableSpawnCheck,int32, Value);
DECLARE_DYNAMIC_DELEGATE(FDel_Dash);

UCLASS()
class SURVIVORLISE_API ASLMainCharacter : public ASLCharacterBase
{
	GENERATED_BODY()
	
public:
	ASLMainCharacter();

	FDel_CharacterDead PlayerDeadDelegate;

protected:
	virtual void BeginPlay() override;
	virtual void Dead(const bool Value) override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta=(AllowPrivateAccess=true))
	class UWidgetComponent* HealthBarWidgetComp;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = true))
	class USpringArmComponent* CameraSpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = true))
	class UCameraComponent* MainCharCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = true))
	float CameraBoomSpeed = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component|Skill", meta = (AllowPrivateAccess = true))
	class USkillComponent* SkillComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class USphereComponent* EnemyCheckCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class USkeletalMeshComponent* LeftWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class USkeletalMeshComponent* RightWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect", meta = (AllowPrivateAccess = true))
	class UNiagaraSystem* DashFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect", meta = (AllowPrivateAccess = true))
	class UNiagaraComponent* DashFXComponent;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Setting", meta = (AllowPrivateAccess = true))
	float MinSpringArmLength = 200.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|Setting", meta = (AllowPrivateAccess = true))
	float MaxSpringArmLength = 1500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation|Montage", meta = (AllowPrivateAccess = true))
	class UAnimMontage* AttackMontage;


	UFUNCTION()
	void AddEnemyCount(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void SubstractEnemyCount(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY()
	TArray<AActor*> NearEnemyArr;

	bool bAttacking = false;

	UPROPERTY(VisibleAnywhere, Category = "Property")
	int32 Damage = 10;

	FTimerHandle StopAttackHandle;
	FTimerHandle AttackTraceHandle;

	UPROPERTY()
	TArray<AActor*> DamagedActors;

	bool bAvaliableDash = true;

	UPROPERTY(EditAnywhere, Category = "Property|Dash")
	float CharacterDashDistance = 0.f;
	UPROPERTY(EditAnywhere, Category = "Property|Dash")
	float CharacterDashCoolTime = 0.f;
	UPROPERTY(EditAnywhere, Category = "Property|Dash")
	float DashInvicibleTime = 0.f;
	
	UFUNCTION()
	void DashControll();
	UFUNCTION()
	void InvincibleControll();

	void ActiveDashParticle();

	UPROPERTY(EditAnywhere, Category = "Test")
	bool bTest = false;


public:
	void DashFunction();

	UFUNCTION()
	void Attack();
	UFUNCTION()
	void ResetAttack();

	float TestHit = 0.f;

	int32 AttackIndex = 0;

	void SetTargetArmLength(const float Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillData")
	class UDataTable* SkillData;

	UFUNCTION()
	void AttackHitCheck();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void AttackHitCheckEnd();
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void AttackTimer();

	FDel_AvailableSpawnCheck SpawnCheckerDelegate;
	FDel_Dash DashDelegate;

	FORCEINLINE const TArray<AActor*> GetNearEnemyArr() { return NearEnemyArr; }
	FORCEINLINE const USphereComponent* GetEnemyCheckCollision() { return EnemyCheckCollision; }
	FORCEINLINE const float GetCharacterDashCoolTime() { return CharacterDashCoolTime; }
};
