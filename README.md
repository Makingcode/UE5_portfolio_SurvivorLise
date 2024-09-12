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



## 스킬

&nbsp;

### AOE



