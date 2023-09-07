// Copyright Epic Games, Inc. All Rights Reserved.


#include "KeyKeyCapCapGameModeBase.h"
#include "MyKeyLibrary.h"
#include "GameManager.h"

void AKeyKeyCapCapGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	AGameModeBase::InitGame(MapName, Options, ErrorMessage);
	GameManager::GetInstance()->CreateInstance();
}