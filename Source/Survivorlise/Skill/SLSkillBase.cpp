// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SLSkillBase.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"

// Sets default values
ASLSkillBase::ASLSkillBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);

}

// Called when the game starts or when spawned
void ASLSkillBase::BeginPlay()
{
	Super::BeginPlay();
	
	

}

void ASLSkillBase::SkillDestroy()
{
	if (SkillEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SkillEffect, GetActorLocation(), GetActorRotation(),SkillEffectSize);
	}
	Destroy();
}

// Called every frame
void ASLSkillBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

