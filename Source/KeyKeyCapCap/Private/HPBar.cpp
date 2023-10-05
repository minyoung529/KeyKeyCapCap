// Fill out your copyright notice in the Description page of Project Settings.


#include "HPBar.h"
#include "GameManager.h"
#include "Kismet/GameplayStatics.h"

void UHPBar::NativeConstruct()
{
	Super::NativeConstruct();
	hpValue = GameManager::GetInstance()->GetHp() / 100.0f;
}

void UHPBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	hpValue = GameManager::GetInstance()->GetHp() / 100.0f;

	if (GameManager::GetInstance()->GetHp() <= 0)
	{
		UGameplayStatics::OpenLevel(this, L"/Game/Level/GameOverLevel", TRAVEL_Absolute);
	}

}
