// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ButtonAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSignature);

class UProgressBar;
UCLASS(HideDropdown)

class KEYKEYCAPCAP_API UButtonAction : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void OnSuccessEvent();
	UPROPERTY(BlueprintAssignable, Category = "Action")
	FSignature OnSuccessDelegate;
	
	UFUNCTION()
	void OnFailEvent();
	UPROPERTY(BlueprintAssignable, Category = "Action")
	FSignature OnFailDelegate;


	void Success();
	void Fail();

public:
	UFUNCTION(BlueprintCallable, Category = "Action")
	void Reset(float maxScale);
	UFUNCTION(BlueprintCallable, Category = "Action")
	void SetValue(float scale);

protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value")
	float Value = 0;

	const float MIN_SCALETIME = 0;
	const float MAX_SCALETIME = 1;
	float clickCount = 10;
	float addScale = 0.1;
	float speed = 0.1;
	
	bool isStopped = false;
};
