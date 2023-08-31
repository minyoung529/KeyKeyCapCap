// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonAction.h"

void UButtonAction::StartAction()
{
	SetScaleTime(10);
}

void UButtonAction::SetScaleTime(float maxScale)
{
	gameOver = false;
	isStopped = false;
	MAX_SCALETIME = maxScale;
	TotalDamage = 0.5;
}

void UButtonAction::SetValue(float scale)
{
	TotalDamage = scale;
	if (TotalDamage <= MIN_SCALETIME)
	{
		Fail();
	}
	else if (TotalDamage >= 1)
	{
		Success();
	}
}


void UButtonAction::Success()
{
	if (gameOver) return;
	gameOver = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Success"));
	UE_LOG(LogTemp, Log, TEXT("Success"));
}

void UButtonAction::Fail()
{
	if (gameOver) return;
	gameOver = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Fail"));
	UE_LOG(LogTemp, Log, TEXT("Fail"));
}

// Native Func

// Active 될 때 한번
void UButtonAction::NativeConstruct()
{
	Super::NativeConstruct();

	SetScaleTime(10);
}

// Update
void UButtonAction::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(!isStopped && !gameOver)	SetValue((TotalDamage - (InDeltaTime*speed)));
}
