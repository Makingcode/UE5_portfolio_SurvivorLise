// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SLSKillAOE.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Skill/SLSkillSpawner.h"
#include "DataTable/SkillTable.h"

ASLSKillAOE::ASLSKillAOE()
{
	RangeIndicator_Decal = CreateDefaultSubobject<UDecalComponent>(TEXT("RangeIndicator_Decal"));
	RangeIndicator_Decal->SetupAttachment(RootComponent);
	RangeIndicator_Decal->SetWorldRotation(FRotator(90.f, 0, 0));
}

void ASLSKillAOE::BeginPlay()
{
	Super::BeginPlay();

	Init();

	FTimerHandle AOETimerHandle;
	GetWorld()->GetTimerManager().SetTimer(AOETimerHandle, this, &ASLSKillAOE::RadialDamageApply, SkillDelay, false);

}

void ASLSKillAOE::Init()
{
	OwnerSpawner = Cast<ASLSkillSpawner>(GetOwner());
	if (OwnerSpawner)
	{
		Damage = OwnerSpawner->GetCurrentSkillData().Skill_Damage;
	}

	FHitResult HitResult;
	FVector Start = GetActorLocation() + FVector(0,0, 3000.f);
	FVector End = GetActorLocation() + FVector(0, 0, -10000.f);

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Camera);
	if (bHit)
	{
		if (RangeIndicator_Decal->GetDecalMaterial())
		{
			RangeIndicator_Decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), RangeIndicator_Decal->GetDecalMaterial(), FVector(10.f, SkillRange, SkillRange), HitResult.Location, FRotator(90, 0, 0));
			
		}
	}

}

void ASLSKillAOE::RadialDamageApply()
{
	TArray<AActor*> IgnoreActor;
	IgnoreActor.Add(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), SkillRange, nullptr, IgnoreActor, this, nullptr);
	RangeIndicator_Decal->DestroyComponent();

	SkillDestroy();
}
