// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonAction.h"

void UButtonAction::Reset(float _clickCount)
{
	isStopped = false;
	clickCount = _clickCount;
	addScale = MAX_SCALETIME / clickCount;
	Value = 0.5;
}

void UButtonAction::SetValue(float scale)
{
	Value = scale;

	if (Value <= MIN_SCALETIME) Fail();
	else if (Value >= MAX_SCALETIME) Success();
}

void UButtonAction::OnSuccessEvent()
{
}

void UButtonAction::OnFailEvent()
{
}

void UButtonAction::Success()
{
	if (OnSuccessDelegate.IsBound() == true) OnSuccessDelegate.Broadcast();
	Reset(clickCount * 2);
}

void UButtonAction::Fail()
{
	if (OnFailDelegate.IsBound() == true) OnFailDelegate.Broadcast();
	Reset(clickCount);
}

// Native Func

// Active 될 때 한번
void UButtonAction::NativeConstruct()
{
	Super::NativeConstruct();

	Reset(10);
}

// Update
void UButtonAction::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!isStopped) SetValue((Value - (InDeltaTime * speed)));
}
