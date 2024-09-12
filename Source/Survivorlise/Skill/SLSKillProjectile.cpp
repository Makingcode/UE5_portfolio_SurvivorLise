// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SLSKillProjectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Skill/SLSkillSpawner.h"
#include "DataTable/SkillTable.h"

ASLSKillProjectile::ASLSKillProjectile()
{
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereCollision->SetupAttachment(RootComponent);

	HomingCollision = CreateDefaultSubobject<USphereComponent>(TEXT("HomingCollision"));
	HomingCollision->SetupAttachment(RootComponent);

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(SphereCollision);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovement->bIsHomingProjectile = false;
}

void ASLSKillProjectile::BeginPlay()
{
	Super::BeginPlay();

	Init();
	

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ASLSKillProjectile::ProjectileOverlap);
	//SetLifeSpan(3.f);
}

void ASLSKillProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRotatePitch)
	{
		RotatePitchMesh();
	}

}

void ASLSKillProjectile::ProjectileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		switch (ProjectileType)
		{
		case EProjecttileType::None:
			break;
		case EProjecttileType::EPT_Single:
			UGameplayStatics::ApplyDamage(OtherActor, ProjectileDamage, nullptr, this, nullptr);
			break;
		case EProjecttileType::EPT_AOE:
		{
			TArray<AActor*> IgnoredActors;
			IgnoredActors.AddUnique(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
			UGameplayStatics::ApplyRadialDamage(GetWorld(), ProjectileDamage, GetActorLocation(), SkillRange, nullptr, IgnoredActors, this, nullptr);
		}break;
		case EProjecttileType::EPT_Homing:
			UGameplayStatics::ApplyDamage(OtherActor, ProjectileDamage, nullptr, this, nullptr);
			break;
		default:
			break;
		}

	}
	SkillDestroy();
}

void ASLSKillProjectile::Init()
{
	OwnerSpawner = Cast<ASLSkillSpawner>(GetOwner());
	if (IsValid(OwnerSpawner))
	{
		ProjectileDamage = OwnerSpawner->GetCurrentSkillData().Skill_Damage;

		if (ProjectileType == EProjecttileType::EPT_Homing)
		{
			HomingCollision->OnComponentBeginOverlap.AddDynamic(this, &ASLSKillProjectile::FindTarget);
		}
	}

}

void ASLSKillProjectile::RotatePitchMesh()
{
	if (ProjectileMovement)
	{
		FRotator CurrentRotation = BodyMesh->GetComponentRotation();

		CurrentRotation.Roll += 2.f;

		BodyMesh->SetWorldRotation(CurrentRotation);
		
	}
}

void ASLSKillProjectile::FindTarget(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//호밍 미사일용
	if (OtherActor)
	{
		ProjectileMovement->HomingTargetComponent = OtherActor->GetRootComponent();
		ProjectileMovement->bIsHomingProjectile = true;
	}
}
