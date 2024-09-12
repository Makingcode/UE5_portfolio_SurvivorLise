// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Enum/LevelType.h"
#include "SLGameInstance.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_DELEGATE_OneParam(FDel_MoveLevel, ELevelType, WantgoLevel);

UCLASS()
class SURVIVORLISE_API USLGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
protected:
	virtual void Init() override;

#pragma region Level
public:
	void SetLevelType(ELevelType NextLevelType);

	FORCEINLINE ELevelType GetLevelType() { return LevelType; }

	FDel_MoveLevel MoveLevelDelegate;

private:
	
	ELevelType LevelType = ELevelType::None;

	UFUNCTION()
	void LoadGameLevel(ELevelType WantLevel);

	//레벨로드완료 후 호출
	UFUNCTION()
	void OnLevelLoaded();

	UPROPERTY()
	ELevelType ToLevel = ELevelType::None;

	UFUNCTION()
	void ToOpenLevel();

#pragma endregion

#pragma region Debug

private:
	UPROPERTY()
	bool IsDebugMode = false;


public:
	void SetIsDebugMode(const bool Value);
	FORCEINLINE const bool GetIsDebugMode() { return IsDebugMode; }
#pragma endregion



};
