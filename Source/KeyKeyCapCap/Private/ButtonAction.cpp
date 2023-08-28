// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonAction.h"

void UButtonAction::StartAction()
{
}

void UButtonAction::SetScaleTime(float maxScale, float clickCount)
{
	MAX_SCALETIME = maxScale;
	TotalDamage = MAX_SCALETIME / 2;

	addScale = 1 / clickCount;
}

void UButtonAction::SetValue(float scale)
{
	TotalDamage = scale;
	if (TotalDamage <= MIN_SCALETIME)
	{
		Fail();
	}
	else if (TotalDamage >= MAX_SCALETIME)
	{
		Success();
	}
}


void UButtonAction::Success()
{
	SetScaleTime(10, 10);
}

void UButtonAction::Fail()
{
	SetScaleTime(10, 10);
}

// Native Func

// Active 될 때 한번
void UButtonAction::NativeConstruct()
{
	Super::NativeConstruct();

	SetScaleTime(10, 10);
}

// Update
void UButtonAction::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(!isStopped)	SetValue((TotalDamage - InDeltaTime)*speed);
}
