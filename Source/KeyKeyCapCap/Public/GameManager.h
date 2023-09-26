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

public:
	void AddKeyCap(AKeycapActor* keycap);
	void AddGun(AMyGun* gun);
	void Shoot();
};
