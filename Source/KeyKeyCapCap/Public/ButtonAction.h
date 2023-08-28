// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ButtonAction.generated.h"

class UProgressBar;
UCLASS(HideDropdown)

class KEYKEYCAPCAP_API UButtonAction : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Action")
	void StartAction();

	void SetScaleTime(float maxScale, float clickCount);
	UFUNCTION(BlueprintCallable, Category = "Action")
	void SetValue(float scale);

	void Success();
	void Fail();

protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	float MAX_SCALETIME = 10;
	const float MIN_SCALETIME = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float TotalDamage = 0;

	float scaleTime = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float addScale = 0.25;
	float speed = 0.2;

	bool isStopped = false;
};
