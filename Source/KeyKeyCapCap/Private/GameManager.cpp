// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager.h"
#include "KeycapActor.h"
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