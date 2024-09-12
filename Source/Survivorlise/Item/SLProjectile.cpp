// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/SLProjectile.h"

ASLProjectile::ASLProjectile()
{
}

void ASLProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void ASLProjectile::SetProjectileDamage(const int32 Value)
{
	ProjectileDamage = Value;
}
