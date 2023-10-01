// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelSystem.generated.h"

/**
 * 
 */
UCLASS()
class KEYKEYCAPCAP_API ULevelSystem : public UUserWidget
{
	GENERATED_BODY()
public:
	void Success();

public:
	UFUNCTION(BlueprintCallable, Category = "Level")
		void Reset(float maxScale);
	UFUNCTION(BlueprintCallable, Category = "Level")
		void ResetValue(float maxScale);
	UFUNCTION(BlueprintCallable, Category = "Level")
		void AddLevel();
		void LevelUP();

protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value")
	int initLevel = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value")
	int initValue = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value")
	int level = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value")
	float levelValue = 0;

	const float MIN_SCALETIME = 0;
	const float MAX_SCALETIME = 1;
	float speed = 0.1;

	bool isStopped = false;
};
