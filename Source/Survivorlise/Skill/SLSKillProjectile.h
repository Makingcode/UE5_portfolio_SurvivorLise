// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SLSkillBase.h"
#include "SLSKillProjectile.generated.h"


UENUM(BlueprintType)
enum class EProjecttileType : uint8
{
	None,
	EPT_Single UMETA(DisplayName = "Single"),
	EPT_AOE UMETA(DisplayName="AOE"),
	EPT_Homing UMETA(DisplayName="Homing")
};
/**
 * 
 */
UCLASS()
class SURVIVORLISE_API ASLSKillProjectile : public ASLSkillBase
{
	GENERATED_BODY()
	
public:
	ASLSKillProjectile();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class USphereComponent* HomingCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* BodyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	float ProjectileDamage;

	class ASLSkillSpawner* OwnerSpawner;

	UFUNCTION()
	void ProjectileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void Init();

	UPROPERTY(EditAnywhere, Category = "Setting")
	bool bRotatePitch = false;

	void RotatePitchMesh();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting", meta = (AllowPrivateAccess = true))
	EProjecttileType ProjectileType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting", meta = (AllowPrivateAccess = true))
	float SkillRange = 0.f;

	UFUNCTION()
	void FindTarget(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
