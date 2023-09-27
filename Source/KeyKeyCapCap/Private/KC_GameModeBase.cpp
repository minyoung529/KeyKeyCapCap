// Fill out your copyright notice in the Description page of Project Settings.


#include "KC_GameModeBase.h"
#include "KeyCapPlayerController.h"
AKC_GameModeBase::AKC_GameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> CamPawnRef(TEXT("/Game/BP/Camera.Camera_C"));
	if (CamPawnRef.Class)
	{
		DefaultPawnClass = CamPawnRef.Class;
	}
	PlayerControllerClass = AKeyCapPlayerController::StaticClass();
}
