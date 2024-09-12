// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ItemActorBase.h"
#include "SLProjectile.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORLISE_API ASLProjectile : public AItemActorBase
{
	GENERATED_BODY()
	
public:
	ASLProjectile();
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	int32 ProjectileDamage = 0;

public:
	void SetProjectileDamage(const int32 Value);
};
