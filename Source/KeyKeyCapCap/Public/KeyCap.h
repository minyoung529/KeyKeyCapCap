// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <iostream>
using namespace std;

enum class STAT_TYPE
{
	ATTACK,
	SHIELD,
	HEAL,

	COUNT
};

/**
 * 
 */
class /*KEYKEYCAPCAP_API*/ KeyCap
{
public:
	KeyCap();
	~KeyCap();

private:
	float attack;
	float shield;
	float heal;
	int level;
	float hp;
	FKey key;

	STAT_TYPE statType;

public:	// Set
	void SetAttack(float _attack)
	{
		attack = _attack;
	}

	void SetShield(float _shield)
	{
		shield = _shield;
	} 

	void SetHeal(float _heal)
	{
		heal = _heal;
	}

	void SetStatType(STAT_TYPE _statType)
	{
		statType = _statType;
	}

	void SetKey(FKey _key)
	{
		this->key = _key;
	}

	void SetHp(float _hp)
	{
		hp = _hp;
	}

	void SetLevel(int _level)
	{
		level = _level;
	}

	void AddLevel()
	{
		SetLevel(level + 1);
	}

public:	// Get
	float GetAttack(){ return attack; }	
	float GetShield(){ return shield; }
	float GetHeal(){ return heal; }
	FKey GetKey(){ return key; }
	float GetHp() { return hp; }
	int GetLevel() { return level; }
};