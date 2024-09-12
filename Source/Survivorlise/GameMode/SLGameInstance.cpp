// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SLGameInstance.h"
#include "SLGameInstance.h"
#include "Kismet/GameplayStatics.h"


void USLGameInstance::Init()
{
	Super::Init();

	MoveLevelDelegate.BindDynamic(this, &USLGameInstance::LoadGameLevel);

}

void USLGameInstance::SetLevelType(ELevelType NextLevelType)
{
	LevelType = NextLevelType;
}

void USLGameInstance::LoadGameLevel(ELevelType WantLevel)
{
	//현재는 하드코딩 사용하지만 추후 데이터테이블 등을 이용하여 하드코딩 제거
	//로딩 레벨로 이동
	ToLevel = WantLevel;
	UGameplayStatics::OpenLevel(GetWorld(), "LV_Loading");
	
	//이동하는 레벨 로드

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = FName("OnLevelLoaded");
	LatentInfo.UUID = 1;
	LatentInfo.Linkage = 0;
	
	

	switch (WantLevel)
	{
	case ELevelType::None:
		break;
	case ELevelType::ELT_Start:
	{
		UGameplayStatics::LoadStreamLevel(GetWorld(), "LV_StartLevel", false, false, LatentInfo);
		break;
	}
	case ELevelType::ELT_Loading:
	{
		break;
	}
	case ELevelType::ELT_Main:
	{
		UE_LOG(LogTemp, Warning, TEXT("WantLevel : ELT_Main"));
		UGameplayStatics::LoadStreamLevel(GetWorld(), "LV_MainLevel", false, false, LatentInfo);
		//UGameplayStatics::LoadStreamLevel(GetWorld(), "Mediterranean_Coasts", false, false, LatentInfo);
		break;
	}
	default:
		break;
	}
	//UGameplayStatics::LoadStreamLevel(GetWorld(),)

}

void USLGameInstance::OnLevelLoaded()
{
	FTimerHandle LevelLoadHandle;
	const float OpenDelay = 3.f;
	GetTimerManager().SetTimer(LevelLoadHandle, this, &USLGameInstance::ToOpenLevel, OpenDelay, false);
}

void USLGameInstance::ToOpenLevel()
{
	switch (ToLevel)
	{
	case ELevelType::None:
		break;
	case ELevelType::ELT_Start:
		UGameplayStatics::OpenLevel(GetWorld(), "LV_StartLevel");
		break;
	case ELevelType::ELT_Loading:

		break;
	case ELevelType::ELT_Main:
		UGameplayStatics::OpenLevel(GetWorld(), "LV_MainLevel");
		break;
	default:
		break;
	}
}

//디버그
void USLGameInstance::SetIsDebugMode(const bool Value)
{
	IsDebugMode = Value;
}
