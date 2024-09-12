// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SLSKillUtility.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Skill/SLSkillSpawner.h"
#include "DataTable/SkillTable.h"
#include "Kismet/GameplayStatics.h"

ASLSKillUtility::ASLSKillUtility()
{
	SkillEffectComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("SkillEffectComp"));
	SkillEffectComp->SetupAttachment(RootComponent);
	SkillEffectComp->SetAutoActivate(false);
	SkillEffectComp->SetRelativeLocation(FVector(0.f, 0.f, -75.f));
}

void ASLSKillUtility::BeginPlay()
{
	Super::BeginPlay();

	Init();

	GetWorldTimerManager().SetTimer(DOTTimer, this, &ASLSKillUtility::DOT, SkillDelay, true);
}

void ASLSKillUtility::Init()
{


	AttachToActor(GetOwner(), FAttachmentTransformRules::KeepWorldTransform);

	SkillEffectComp->SetRelativeRotation(FRotator(0, 0, 0));

	if (SkillNiagara)
	{
		SkillEffectComp->SetAsset(SkillNiagara);
		SkillEffectComp->SetWorldScale3D(FVector(SkillRange / 100.f));	
		SkillEffectComp->SetActive(true);
	}

	OwnerSpawner = Cast<ASLSkillSpawner>(GetOwner());
	if (OwnerSpawner)
	{
		Damage = OwnerSpawner->GetCurrentSkillData().Skill_Damage;
		SkillRemoveTime = OwnerSpawner->GetCurrentSkillData().Skill_CoolDown - 10.f;
	}

}

void ASLSKillUtility::DOT()
{
	TArray<AActor*> IgnoredActors;
	IgnoredActors.AddUnique(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	//Damage of time
	if (SkillRemoveTime > 0)
	{
		SkillRemoveTime -= SkillDelay;

		bool bHit = UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), SkillRange, nullptr, IgnoredActors, this, nullptr);

	}
	else
	{
		SkillEffectComp->SetActive(false);
		GetWorldTimerManager().ClearTimer(DOTTimer);
		SkillDestroy();
	}

}
