// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Class.h"
#include<unordered_map>
using namespace std;

enum class STAT_TYPE
{
	ATTACK,
	SHIELD,
	HEAL,

	COUNT
};

UENUM(BlueprintType)
enum class KEY_TYPE : uint8
{
	Zero, One, Two,
	Three, Four, Five,
	Six, Seven, Eight, Nine,

	A, B, C, D, E,
	F, G, H, I, J,
	K, L, M, N, O,
	P, Q, R, S, T,
	U, V, W, X, Y, Z,

	Tab,
	Enter,
	Space,

	Count
};

/**
 *
 */
class KEYKEYCAPCAP_API MyKeyLibrary
{
public:
	MyKeyLibrary();
	~MyKeyLibrary();

public:
	static unordered_map<int, const char*> keyMap;
	static unordered_map<int, const char*> meshKeyMap;

public:
	static void SetKeyMap();

	static void SetMeshKeyMap();

	static const char* GetKey(KEY_TYPE keyType)
	{
		if (keyMap.size() == 0)
		{
			SetKeyMap();
		}

		return keyMap[(int)keyType];
	}

	static const char* GetMeshKey(KEY_TYPE keyType)
	{
		if (meshKeyMap.size() == 0)
		{
			SetMeshKeyMap();
		}

		return meshKeyMap[(int)keyType];
	}
};
