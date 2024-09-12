# UE5_portfolio_SurvivorLise

언리얼5 클라이언트 포트폴리오 입니다.

&nbsp;

## 플레이 영상

[![언리얼엔진5 포트폴리오(Unreal Engine5 Portfolio)](http://img.youtube.com/vi/sh3eEuVhegQ/0.jpg)](https://youtu.be/sh3eEuVhegQ?si=cgK1m-Z9dWvMizYW)

&nbsp;
----------------------

## 구성
1. 엔진 : 언리얼엔진5 (5.2.1)
2. IDE : Visual Studio 2022
3. 개발언어 : c++ 
4. 개발기간 : 2024/08/21 ~ 2024/09/11 (21일)
5. 개발인원 : 1명

------------------------


## 레벨구조

![Level](https://github.com/user-attachments/assets/14aea421-86d5-4926-84bb-0ffb02c7634a)


&nbsp;


## 게임흐름


![GameSequence](https://github.com/user-attachments/assets/efe103fe-2db2-4c35-b012-35fa46f286f5) &nbsp;


--------------------------



## 로딩

비동기방식 레벨 로딩
SLGameInstance에서 관리
레벨이동시 로딩레벨로 이동 이후
이동할 레벨을 LoadStreaming LatentActionInfo의 ExecutionFunction에 의해 로드가 완료되면 OnLevelLoaded 함수가 호출되고
로드된 레벨로 이동

&nbsp;


## 플레이어 Movement

![Input](https://github.com/user-attachments/assets/cf125126-c67c-4bd8-9117-344cfa431781) 


&nbsp;
EnhancedInput을 이용해 플레이어 Movement 구현

&nbsp;


## 레벨업 시스템

플레이어의 레벨은 플레이어 스테이트에서 관리

-전체적인 흐름-

![LevelupSequence](https://github.com/user-attachments/assets/c197ef9a-1186-4296-9296-0de8604343a4)
&nbsp;

코드간 결합도를 낮추고 재사용성을 높이기 위해 델리게이트 사용



## 스킬선택 위젯

DataTable에서 모든 스킬데이터를 가져오고

![SkillData](https://github.com/user-attachments/assets/6bbb7222-beb3-4fb5-b5e7-fbed329b110a)

&nbsp;

SkillComponent에서 현재 장착중인 나의스킬 배열을 가져와서 조건문을 통해 스킬선택 데이터를 뽑아 랜덤으로 3개를 위젯으로 보여줌

- 장착된 스킬이 없을때
  DataTable의 스킬레벨 1인 데이터들만 찾아 배열에 추가 후 랜덤 3개 위젯으로 보여줌

- 장착된 스킬이 있을때
  장착된 스킬의 경우 
```c
//현재 스킬이 장착되어 있는 경우
TMap<FName, int32>EquipSkillLevels;
for (FSkillDataTable CurrentSkillData : SkillComponent->GetCurrentUsedSkillData())
{
	//현재 장착중인 스킬이름 및 레벨
	EquipSkillLevels.Add(CurrentSkillData.Skill_Name, CurrentSkillData.Skill_Level);
}

//장착중인 스킬의 경우
for (FSkillDataTable CurrentSkillData : SkillComponent->GetCurrentUsedSkillData())
{
	int32* CurrentLevel = EquipSkillLevels.Find(AvaliableSkill->Skill_Name);
	//레벨 1올리기
	if (CurrentLevel)
	{
		if (AvaliableSkill->Skill_Level == *CurrentLevel + 1)
		{
			AvaliableSkillArr.AddUnique(*AvaliableSkill);
		}
	}
	else
	{	
		//장착중이지 않은 스킬은 레벨 1
		if (AvaliableSkill->Skill_Level == 1)
		{
			AvaliableSkillArr.AddUnique(*AvaliableSkill);
		}
	}
}
```

## Dash

LaunchCharacter 함수를 이용하여 대쉬 구현

```c
FVector Direction = GetLastMovementInputVector().GetSafeNormal();
if (Direction.IsZero())
{
	Direction = GetActorForwardVector();
}

FVector LaunchDirection = Direction * CharacterDashDistance;
//대쉬
LaunchCharacter(LaunchDirection, true, true);
```



## 근접 공격

휘두르는 동안 콜리전 생성을 위해 무기 메쉬의 본에 소켓 생성
SweepMultibyChannel 함수를 이용하여 콜리전에 히트한 액터에게 ApplyDamage를 이용하여 데미지를 부여

```c
FVector Start = RightWeapon->GetSocketLocation("SwordStart");
FVector End = RightWeapon->GetSocketLocation("SwordEnd");
float Radius = 20.f;

TArray<FHitResult> HitResults;
FCollisionQueryParams QueryParams;
QueryParams.AddIgnoredActor(this);

//ECC_GameTraceChannel6 = Weapon 채널
float bHit = GetWorld()->SweepMultiByChannel(HitResults, Start, End, FQuat::Identity, ECC_GameTraceChannel6, FCollisionShape::MakeSphere(Radius), QueryParams);

if (bTest)
{
	DrawDebugLine(GetWorld(), Start, End, FColor::Red,false ,5.f);
}

if (bHit)
{
	for (FHitResult HitResult : HitResults)
	{
		if (!DamagedActors.Contains(HitResult.GetActor()))
		{
			UGameplayStatics::ApplyDamage(HitResult.GetActor(), 10.f, GetController(), this, nullptr);
			DamagedActors.Add(HitResult.GetActor());
		}

	}
}
```

### 콤보 공격

몽타주안에 무기 공격 애니메이션이 2개가 존재하고 2개의 섹션으로 나눔

공격을 할때마다 Attack Index가 0과 1을 왔다갔다하며 삼항연산에 의해 해당 값에 해당하는 몽타주 섹션이 작동하게 됨

```c
if (MyAnimInstance && AttackMontage)
{
	FName AttackSectionName = (AttackIndex == 0) ? FName("AttackStart") : FName("Attack_1");
	MyAnimInstance->Montage_Play(AttackMontage);
	MyAnimInstance->Montage_JumpToSection(AttackSectionName, AttackMontage);
	float AttackDuration = AttackMontage->GetSectionLength(AttackIndex);
	GetWorldTimerManager().SetTimer(StopAttackHandle, this, &ASLMainCharacter::ResetAttack, AttackDuration, false);
	
}

void ASLMainCharacter::ResetAttack()
{
	bAttacking = false;
	DamagedActors.Empty();
	AttackIndex = (AttackIndex + 1) % 2;
}
```




## 스킬

&nbsp;

### AOE (Area of Effect)

ApplyRadialDamage를 이용하여 데미지 발생, IgnoreActor로 플레이어 캐릭터를 추가하여 플레이어 캐릭터는 본인 스킬에 데미지를 안입게 설정

```c
void ASLSKillAOE::RadialDamageApply()
{
	TArray<AActor*> IgnoreActor;
	IgnoreActor.Add(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), SkillRange, nullptr, IgnoreActor, this, nullptr);
	RangeIndicator_Decal->DestroyComponent();

	SkillDestroy();
}
```


### Beam

MakeCapsule을 통해 콜리전을 만들고 SweepMultibyChannel을 통해 콜리전에 히트한 액터들을 찾아내고 데미지를 부여
SetTimer를 이용하여 스킬 유지시간동안 콜리전 히트 체크 및 데미지 부여

```c
void ASLSkillBeam::Attack()
{
	Start = GetActorLocation();
	End = Start + (GetActorForwardVector() * MaxRange);
	BeamComponent->SetActive(true);
	BeamComponent->SetWorldScale3D(FVector(MaxRange * 0.001f, BeamWidth*0.1f, BeamHeight * 0.01f));
	GetWorldTimerManager().SetTimer(CheckerHandle, this, &ASLSkillBeam::FindEnemyChecker, 0.1f, true, 0.f);
	GetWorldTimerManager().SetTimer(BeamDestroyTimer, this, &ASLSkillBeam::BeamDestroy, 2.f, false, -1.f);
	
}

void ASLSkillBeam::FindEnemyChecker()
{
	FCollisionShape BeamShape = FCollisionShape::MakeCapsule(BeamWidth, BeamHeight);
	TArray<FHitResult> HitResults;
	bool bHit = GetWorld()->SweepMultiByChannel(HitResults, Start, End, FQuat::Identity, ECC_GameTraceChannel6, BeamShape);
	if (bHit)
	{
		for (FHitResult HitResult : HitResults)
		{
			if (ASLEnemyCharacter* Enemy = Cast<ASLEnemyCharacter>(HitResult.GetActor()))
			{
				UGameplayStatics::ApplyDamage(HitResult.GetActor(), Damage, nullptr, this, nullptr);
			}
		}

	}
}
```


&nbsp;


## 최적화

Tick 사용 최소화 -> Tick이 필요한 부분 SetTimer로 대체
플레이어 캐릭터와 일정거리 이상이면 스폰되어 있어도 SetVisibility를 false하여 렌더링 중지

```c
void ASLEnemyCharacter::SetCharacterVisible()
{
	float Distance = FVector::Dist(GetActorLocation(), MainCharacter->GetActorLocation());

	if (Distance >= 2500.f)
	{
		GetMesh()->SetVisibility(false);
	}
	else
	{ 
		GetMesh()->SetVisibility(true);
	}
}
```

&nbsp;
---------------------------------------------

## 결론




### 프로젝트를 하며 배운점

* 이전 포트폴리오들에서는 사용을 거의 안했던 델리게이트를 적극 사용하며 코드의 결합도를 낮추고 재사용성을 높였다

* 매니저에 해당하는 게임인스턴스, 플레이어스테이트, 게임스테이트도 적극 이용하였고 게임의 전반적인 흐름이나 관리가 이전 포트폴리오 보단 더욱 잘되었다

* 기존에 잘 사용안했던 데이터테이블을 이용하였고 캐릭터 레벨별에 따른 경험치양이나 스킬데이터 관리가 용이했다



### 개선이 필요한점

* Beam 발사되었을때 끝부분의 콜리전에 히트해도 데미지가 안들어가는 경우가 있어 이펙트상으로는 레이저에 맞았는데도 데미지가 아예 안들어가는 경우가 있음

* DOT 스킬의 경우 스킬이 시전되고 있는 중에 레벨업하여 DOT스킬을 선택하면 스킬이 중복으로 들어가는 문제가 있음

-> DOT스킬의 경우 시전시간동안 스킬스포너에 Attach 되어 있기 때문에 해당 Spawner에 Attach된 스킬이 있는 것을 검사하여 만약 있으면 스킬 생성이 안되고
스킬의 데미지를 업데이트 하는 방향으로 가면 되지 않을까 생각됨

