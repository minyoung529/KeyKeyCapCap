// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager.h"
#include "KeycapActor.h"
#include "MyGun.h"
#include "MyKeyLibrary.h"

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

void GameManager::Shoot()
{
	curGunIdx = (curGunIdx + 1) % guns.Num();
	guns[curGunIdx]->Fire();
}
