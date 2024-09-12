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


## 레벨업 시스템

플레이어의 레벨은 플레이어 스테이트에서 관리

-전체적인 흐름-

![LevelupSequence](https://github.com/user-attachments/assets/c197ef9a-1186-4296-9296-0de8604343a4)
&nbsp;




