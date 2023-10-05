// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager.h"
#include "KeycapActor.h"
#include "MyGun.h"
#include "MyKeyLibrary.h"
#include "Kismet/GameplayStatics.h"

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

void GameManager::CreateInstance()
{
}

void GameManager::AddKeyCap(AKeycapActor* keycap)
{
	keycaps.Add(keycap);
}

void GameManager::AddGun(AMyGun* gun)
{
	guns.Add(gun);
}

void GameManager::Shoot(int level, FVector color)
{
	curGunIdx = (curGunIdx + 1) % guns.Num();
	guns[curGunIdx]->Fire(level, color);
}

int GameManager::GetLevel()
{
	int minLevel = 999;

	for (int i = 0; i < keycaps.Num(); i++)
	{
		int keycapLevel = keycaps[i]->GetKeycapLevel();

		if (keycapLevel < minLevel)
		{
			minLevel = keycapLevel;
		}
	}

	return minLevel;
}

void GameManager::AddHp(int _hp)
{
	hp += _hp;
	UE_LOG(LogTemp, Log, TEXT("%d"), hp);
	if (hp <= 0)
	{
		// GameOver
	}
}

int GameManager::GetHp()
{
	return hp;
}

void GameManager::ResetGameManager()
{
	hp = MAX_HP;
	curGunIdx = 0;

	keycaps.Reset();
	guns.Reset();
}
