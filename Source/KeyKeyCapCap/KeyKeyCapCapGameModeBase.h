// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KeyKeyCapCapGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class KEYKEYCAPCAP_API AKeyKeyCapCapGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);

	// TODO: UPDATE(tick) Ãß°¡
};
