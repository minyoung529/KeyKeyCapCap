// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSystem.h"

void ULevelSystem::Success()
{
	Reset(10);
}

void ULevelSystem::ResetValue(float maxScale)
{
	isStopped = false;
	levelValue = initValue;
	level = initLevel;
}
void ULevelSystem::Reset(float maxScale)
{
	ResetValue(10);
	level = 0;
}

void ULevelSystem::AddLevel()
{
	levelValue += 0.1;
	if (levelValue >= 1) LevelUP();
}

void ULevelSystem::LevelUP()
{
	level++;
	ResetValue(10);
}

void ULevelSystem::NativeConstruct()
{
	Super::NativeConstruct();

	Reset(10);
}

void ULevelSystem::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
