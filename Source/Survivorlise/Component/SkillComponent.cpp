// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SkillComponent.h"
#include "DataTable/SkillTable.h"
#include "GameMode/SLPlayerState.h"
#include "Kismet/Gameplaystatics.h"
#include "Skill/SLSkillSpawner.h"
#include "Widget/SLSkillslotWidget.h"


// Sets default values for this component's properties
USkillComponent::USkillComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void USkillComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void USkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USkillComponent::SpawnSkillSpawner()
{
	if (SkillSpawner)
	{
		FVector SpawnLocation = GetOwner()->GetActorLocation();
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOwner();
		GetWorld()->SpawnActor<ASLSkillSpawner>(SkillSpawner, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
	}

}

void USkillComponent::UpdateSkillSpawner()
{
	
	SetCurrentUsedSkillData();
	
}

void USkillComponent::SetCurrentUsedSkillData()
{
	if (CurrentEquipSkillArr.Num() != 0)
	{
		for (ASLSkillSpawner* CurrentSkillSpawner : CurrentEquipSkillArr)
		{
			CurrentUsedSkillData.AddUnique(CurrentSkillSpawner->GetCurrentSkillData());
		}
	}
	if (CurrentEquipSkillArr.Num() <= 5)
	{
		SkillCoolDownDelegate.Broadcast();
	}
}

void USkillComponent::AddCurrentEquipSkill(ASLSkillSpawner* Value)
{
	if (CurrentEquipSkillArr.Num() <= 5)
	{
		CurrentEquipSkillArr.Add(Value);
	}
}



