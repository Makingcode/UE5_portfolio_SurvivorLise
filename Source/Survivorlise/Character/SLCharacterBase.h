// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SLCharacterBase.generated.h"



UENUM(BlueprintType)
enum class ERecoveryType : uint8
{
	None,
	ERDT_HPRecovery,		//체력회복
	ERDT_ShieldRecovery		//쉴드회복
};

DECLARE_DYNAMIC_DELEGATE_TwoParams(FDel_RecoveryType, int32, AmountValue, ERecoveryType, RecoveryType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDel_Damage, float,HPPer, float, SPPer);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FDel_Recovery, float, HPPer, float, SPPer);


UCLASS()
class SURVIVORLISE_API ASLCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASLCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status", meta = (AllowPrivateAccess = true))
	int32 Health = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status", meta = (AllowPrivateAccess = true))
	int32 MaxHealth = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Status", meta = (AllowPrivateAccess = true))
	int32 ShieldPoint = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status", meta = (AllowPrivateAccess = true))
	int32 MaxShieldPoint = 0;

	float HPPercent = 0.f;
	float SPPercent = 0.f;

	UPROPERTY(VisibleAnywhere, Category = "Property")
	bool bInvincible = false;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status", meta=(AllowPrivateAccess=true))
	bool IsDead = false;

	class UHealthBarWidgetBase* WGHealthBar = nullptr;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class USLDamageWidget> DamageWidgetBP;

	class USLDamageWidget* DamageWidget;


public:
	FDel_RecoveryType RecoveryTypeDelegate;
	FDel_Damage DamageDelegate;
	FDel_Recovery RecoveryDelegate;
	

	UFUNCTION()
	void HPSPCalculate(int32 Amount, ERecoveryType Type);
	
	void SetIsDead(const bool Value);

	FORCEINLINE const float GetHPPercent() { return HPPercent; }
	FORCEINLINE const bool GetIsDead() { return IsDead; }
	FORCEINLINE const int32 GetMaxHealth() { return MaxHealth; }
	FORCEINLINE const int32 GetMaxShieldPoint() { return MaxShieldPoint; }
	
	

protected:
	virtual void Dead(const bool Value);
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};
