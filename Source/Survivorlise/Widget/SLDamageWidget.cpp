// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SLDamageWidget.h"
#include "Character/SLCharacterBase.h"
#include "Components/TextBlock.h"


void USLDamageWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void USLDamageWidget::WidgetRemove()
{
	RemoveFromParent();
}

void USLDamageWidget::SetDamageAndPlayAnim(const float Damage)
{
	//데미지 설정 및 위젯의 애니메이션 실행
	TB_Damage->SetText(FText::FromString(FString::FromInt((int32)Damage)));
	FWidgetAnimationDynamicEvent WidgetAnimEvent;
	WidgetAnimEvent.BindDynamic(this, &USLDamageWidget::WidgetRemove);
	BindToAnimationFinished(IndicatorStart, WidgetAnimEvent);
	PlayAnimation(IndicatorStart);

}
