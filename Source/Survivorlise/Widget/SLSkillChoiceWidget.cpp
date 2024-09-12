// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SLSkillChoiceWidget.h"
#include "Components/Button.h"
#include "GameMode/SLPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "DataTable/SkillTable.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void USLSkillChoiceWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_SkillChoice->OnClicked.AddDynamic(this, &USLSkillChoiceWidget::SkillSelect);
	
	
}

void USLSkillChoiceWidget::SkillSelect()
{
	if (ASLPlayerState* MyPS = Cast<ASLPlayerState>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPlayerState<ASLPlayerState>()))
	{
		MyPS->SetReceivedData(ReceiveData);
		MyPS->SkillSelectedDelegate.Broadcast();
	}
}

void USLSkillChoiceWidget::SkillDataLoad(FSkillDataTable Data)
{
	ReceiveData = Data;

	TB_SkillName->SetText(FText::FromName(Data.Skill_Name));
	TB_SkillLevel->SetText(FText::FromString(FString::Printf(TEXT("Level : %d"), Data.Skill_Level)));
	TB_SkillExplain->SetText(Data.Skill_Text);
	IMG_Skill->SetBrushFromTexture(Data.Skill_Image);


}
