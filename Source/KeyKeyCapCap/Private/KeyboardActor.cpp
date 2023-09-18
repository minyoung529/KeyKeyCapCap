// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyboardActor.h"

// Sets default values
AKeyboardActor::AKeyboardActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AKeyboardActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKeyboardActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

