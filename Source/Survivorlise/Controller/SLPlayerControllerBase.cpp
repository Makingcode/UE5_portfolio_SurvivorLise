// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/SLPlayerControllerBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Widget/SLDebugWidget.h"


void ASLPlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	SetShowMouseCursor(true);
}

