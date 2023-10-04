// Copyright Epic Games, Inc. All Rights Reserved.


#include "KeyKeyCapCapGameModeBase.h"
#include "MyKeyLibrary.h"
#include "GameManager.h"

void AKeyKeyCapCapGameModeBase::StartPlay()
{
	AGameModeBase::StartPlay();
	GameManager::GetInstance()->CreateInstance();
}