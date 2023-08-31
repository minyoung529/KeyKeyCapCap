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
	UFUNCTION(BlueprintCallable, Category = "Action")
	void SetValue(float scale);
	
	void SetScaleTime(float maxScale);
	
	void Success();
	void Fail();

protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	const float MIN_SCALETIME = 0;
	float MAX_SCALETIME = 10;
	
	float scaleTime = 0;
	float speed = 0.5;
	bool isStopped = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float TotalDamage = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float addScale = 0.25;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	bool gameOver = false;
};
