// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyCapPlayerController.h"

void AKeyCapPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}
