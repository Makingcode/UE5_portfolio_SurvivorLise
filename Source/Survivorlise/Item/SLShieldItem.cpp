// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/SLShieldItem.h"
#include "Components/SphereComponent.h"
#include "Character/SLMainCharacter.h"

void ASLShieldItem::BeginPlay()
{
	Super::BeginPlay();

	ItemCollision->OnComponentBeginOverlap.AddDynamic(this, &ASLShieldItem::SPRecovery);
}

void ASLShieldItem::SPRecovery(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (class ASLMainCharacter* OverlappedCharacter = Cast<ASLMainCharacter>(OtherActor))
	{
		//�������� ĳ���Ͱ� SLMainCharacter(����ĳ����) �϶�
		const int32 CurrentMaxShield = OverlappedCharacter->GetMaxShieldPoint();

		//30�� ȸ��
		const float WillShieldPoint = CurrentMaxShield * 0.3f;

		OverlappedCharacter->RecoveryTypeDelegate.ExecuteIfBound((int32)WillShieldPoint, ERecoveryType::ERDT_ShieldRecovery);
	}

	Destroy();
}