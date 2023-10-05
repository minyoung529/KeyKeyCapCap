// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatCharacter.h"

// Sets default values
ACombatCharacter::ACombatCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InitCharacter();
}

// Called when the game starts or when spawned
void ACombatCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACombatCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACombatCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACombatCharacter::InitCharacter(float attackVal, float maxHpVal, float levelVal, float healVal, float shieldVal,float speedVal)
{
	attack = 20;
	maxHp = 100;
	hp = 100;
	level = 1;
	heal = 0;
	shield = 0;
	speed = 13;
}

void ACombatCharacter::Act()
{}

