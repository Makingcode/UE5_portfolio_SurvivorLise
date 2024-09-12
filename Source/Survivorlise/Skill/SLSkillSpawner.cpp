// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SLSkillSpawner.h"
#include "DataTable/SkillTable.h"
#include "GameMode/SLPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Widget/SLSkillslotWidget.h"
#include "Component/SkillComponent.h"
#include "Character/SLMainCharacter.h"


#include "Skill/SLSKillProjectile.h"
#include "Skill/SLSKillAOE.h"
#include "Skill/SLSKillUtility.h"
#include "Skill/SLSkillBeam.h"

// Sets default values
ASLSkillSpawner::ASLSkillSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASLSkillSpawner::BeginPlay()
{
	Super::BeginPlay();

	
	MyMainCharacter = Cast<ASLMainCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	this->AttachToActor(GetOwner(),FAttachmentTransformRules::KeepWorldTransform);
	if (ASLPlayerState* MyPS = Cast<ASLPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0)))
	{
		SetMySkillData(MyPS->GetReceivedData());

	}
	if (USkillComponent* MySkillComp = Cast<USkillComponent>(MyMainCharacter->GetComponentByClass<USkillComponent>()))
	{
		MySkillComp->AddCurrentEquipSkill(this);
		MySkillComp->SetCurrentUsedSkillData();
	}
	
	
}

// Called every frame
void ASLSkillSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ASLSkillSpawner::SpawnSkillReady()
{
	//��ų �߻�(Ÿ�Կ� ���� �߻�)
	
	GetWorldTimerManager().SetTimer(SkillSpawnHandle, this, &ASLSkillSpawner::SpawnSkill, Cooltime, true, 0.f);
}

void ASLSkillSpawner::SetMySkillData(FSkillDataTable Value)
{
	CurrentSkillData = Value;

	GetWorldTimerManager().ClearTimer(SkillSpawnHandle);
	SkillLevel = CurrentSkillData.Skill_Level;
	SkillName = CurrentSkillData.Skill_Name;
	Cooltime = CurrentSkillData.Skill_CoolDown;

	SpawnSkillReady();
}

void ASLSkillSpawner::SpawnSkill()
{
	//����ġ�� �����
	switch (CurrentSkillData.Skill_Type)
	{
	case ESkillType::EST_Linear:
	{
		MyMainCharacter->GetNearEnemyArr();
		TArray<FVector> EnemyLocationArr;

		for (int i = 0; i < MyMainCharacter->GetNearEnemyArr().Num(); i++)
		{
			EnemyLocationArr.AddUnique(MyMainCharacter->GetNearEnemyArr()[i]->GetActorLocation());
		}
		
			
		for (int i = 0; i < CurrentSkillData.Skill_Amount; i++)
		{
			if (EnemyLocationArr.IsValidIndex(i))
			{
				FVector EnemyLocation = EnemyLocationArr[i];
				FVector SpawnLocation = GetOwner()->GetActorLocation();
				FRotator SpawnRotation = (EnemyLocation - SpawnLocation).Rotation();
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				GetWorld()->SpawnActor<ASLSKillProjectile>(CurrentSkillData.SkillBPClass, SpawnLocation, SpawnRotation, SpawnParams);
			}
			else
			{
				//��ų�� �߻�ü �����ٵ� Ž���� �ɸ� ������ ���� ��� (���� �������� �߻�)
				FVector SpawnLocation = GetOwner()->GetActorLocation();
					
				float RandomYaw = FMath::FRandRange(0.f, 360.f);

				FRotator SpawnRotation = FRotator(0, RandomYaw, 0);
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				GetWorld()->SpawnActor<ASLSKillProjectile>(CurrentSkillData.SkillBPClass, SpawnLocation, SpawnRotation, SpawnParams);
			}	
		}
		break;
	
	}
	case ESkillType::EST_AOE:
	{
		FVector SpawnLocation = GetOwner()->GetActorLocation();

		float RandomYaw = FMath::FRandRange(0.f, 360.f);

		FRotator SpawnRotation = FRotator(0, RandomYaw, 0);
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		GetWorld()->SpawnActor<ASLSKillAOE>(CurrentSkillData.SkillBPClass, SpawnLocation, SpawnRotation, SpawnParams);
		
		break;
	}
	case ESkillType::EST_Utility:
	{
		FVector SpawnLocation = GetOwner()->GetActorLocation();
		FRotator SpawnRotation = FRotator::ZeroRotator;
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		GetWorld()->SpawnActor<ASLSKillUtility>(CurrentSkillData.SkillBPClass, SpawnLocation, SpawnRotation, SpawnParams);
		break; 
	}
	case ESkillType::EST_Beam:
	{
		MyMainCharacter->GetNearEnemyArr();
		TArray<FVector> EnemyLocationArr;

		for (int i = 0; i < MyMainCharacter->GetNearEnemyArr().Num(); i++)
		{
			EnemyLocationArr.AddUnique(MyMainCharacter->GetNearEnemyArr()[i]->GetActorLocation());
		}

		for (int i = 0; i < CurrentSkillData.Skill_Amount; i++)
		{
			if (EnemyLocationArr.IsValidIndex(i))
			{
				FVector EnemyLocation = EnemyLocationArr[i];
				FVector SpawnLocation = GetOwner()->GetActorLocation();
				FRotator SpawnRotation = (EnemyLocation - SpawnLocation).Rotation();
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				GetWorld()->SpawnActor<ASLSkillBeam>(CurrentSkillData.SkillBPClass, SpawnLocation, SpawnRotation, SpawnParams);
			}
			else
			{
				//��ų�� �߻�ü �����ٵ� Ž���� �ɸ� ������ ���� ��� (���� �������� �߻�)
				FVector SpawnLocation = GetOwner()->GetActorLocation();

				float RandomYaw = FMath::FRandRange(0.f, 360.f);

				FRotator SpawnRotation = FRotator(0, RandomYaw, 0);
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				GetWorld()->SpawnActor<ASLSkillBeam>(CurrentSkillData.SkillBPClass, SpawnLocation, SpawnRotation, SpawnParams);
			}
		}
		break;
	}
	
	default:
		break;
	}

	

	//��ų��ٿ� �������� ��ų�� ��������� �˸�
	NoticeSkillUsedDelegate.Broadcast(Cooltime);

}







