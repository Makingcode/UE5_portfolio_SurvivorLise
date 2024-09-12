// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SLSkillBeam.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "DataTable/SkillTable.h"
#include "Skill/SLSkillSpawner.h"
#include "Character/SLEnemyCharacter.h"


ASLSkillBeam::ASLSkillBeam()
{
	BeamComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("BeamComponent"));
	BeamComponent->SetupAttachment(RootComponent);
	BeamComponent->SetAutoActivate(false);

}

void ASLSkillBeam::BeginPlay()
{
	Super::BeginPlay();

	Init();

	Attack();

}

void ASLSkillBeam::Attack()
{
	Start = GetActorLocation();
	End = Start + (GetActorForwardVector() * MaxRange);
	BeamComponent->SetActive(true);
	BeamComponent->SetWorldScale3D(FVector(MaxRange * 0.001f, BeamWidth*0.1f, BeamHeight * 0.01f));
	GetWorldTimerManager().SetTimer(CheckerHandle, this, &ASLSkillBeam::FindEnemyChecker, 0.1f, true, 0.f);
	GetWorldTimerManager().SetTimer(BeamDestroyTimer, this, &ASLSkillBeam::BeamDestroy, 2.f, false, -1.f);
	
}

void ASLSkillBeam::FindEnemyChecker()
{
	FCollisionShape BeamShape = FCollisionShape::MakeCapsule(BeamWidth, BeamHeight);
	TArray<FHitResult> HitResults;
	bool bHit = GetWorld()->SweepMultiByChannel(HitResults, Start, End, FQuat::Identity, ECC_GameTraceChannel6, BeamShape);
	if (bHit)
	{
		for (FHitResult HitResult : HitResults)
		{
			if (ASLEnemyCharacter* Enemy = Cast<ASLEnemyCharacter>(HitResult.GetActor()))
			{
				UGameplayStatics::ApplyDamage(HitResult.GetActor(), Damage, nullptr, this, nullptr);
			}
		}

		//DrawDebugCapsule(GetWorld(), (Start + End) * 0.5f, BeamHeight, BeamWidth, FRotationMatrix::MakeFromZ(End - Start).ToQuat(), FColor::Blue,false,5.f);
	}
}

void ASLSkillBeam::Init()
{
	if (ASLSkillSpawner* OwnerSpawner = Cast<ASLSkillSpawner>(GetOwner()))
	{
		Damage = OwnerSpawner->GetCurrentSkillData().Skill_Damage;
	}

	if (BeamEffect)
	{
		BeamComponent->SetAsset(BeamEffect);
	}
}

void ASLSkillBeam::BeamDestroy()
{
	GetWorld()->GetTimerManager().ClearTimer(CheckerHandle);
	SkillDestroy();
}
