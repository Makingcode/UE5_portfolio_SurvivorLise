// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/SLHealthItem.h"
#include "Components/SphereComponent.h"
#include "Character/SLMainCharacter.h"

void ASLHealthItem::BeginPlay()
{
	Super::BeginPlay();

	ItemCollision->OnComponentBeginOverlap.AddDynamic(this, &ASLHealthItem::HPRecovery);
}

void ASLHealthItem::HPRecovery(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (class ASLMainCharacter* OverlappedCharacter = Cast<ASLMainCharacter>(OtherActor))
	{
		//오버랩된 캐릭터가 SLMainCharacter(메인캐릭터) 일때
		const int32 CurrentMaxHealth = OverlappedCharacter->GetMaxHealth();

		//30퍼 회복
		const float WillHealthPoint = CurrentMaxHealth * 0.3f;

		OverlappedCharacter->RecoveryTypeDelegate.ExecuteIfBound((int32)WillHealthPoint, ERecoveryType::ERDT_HPRecovery);
	}
	Destroy();
}

