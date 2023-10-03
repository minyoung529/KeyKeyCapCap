// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class KEYKEYCAPCAP_API GameManager
{
public:
	GameManager();
	~GameManager();

public:
	static GameManager* GetInstance()
	{
		static GameManager mgr;
		return &mgr;
	}

public:
	static void CreateInstance();

private:
	TArray<class AKeycapActor*> keycaps;
	TArray<class AMyGun*> guns;

	int curGunIdx = 0;
	const int MAX_HP = 100;
	int hp = MAX_HP;

public:
	void AddKeyCap(AKeycapActor* keycap);
	void AddGun(AMyGun* gun);
	void Shoot(int level, FVector color);

	int GetLevel();

	void AddHp(int hp);
	int GetHp();

	void ResetGameManager();
};
