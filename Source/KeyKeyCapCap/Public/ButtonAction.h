// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ButtonAction.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS(HideDropdown)
class KEYKEYCAPCAP_API UButtonAction : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void StartAction();
	void Success();
	void Fail();

public:
	const float MAX_SCALETIME = 10;
	const float MIN_SCALETIME = 0;

	float scaleTime = 0;
	float addScale = 0.25;

	bool isStopped = false;

protected:
	UPROPERTY(meta=(BindWidget))
	UProgressBar* ActionBar;
};
