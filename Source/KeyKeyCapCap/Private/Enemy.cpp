// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

// Sets default values
AEnemy::AEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	fsm = CreateDefaultSubobject<UEnemyFSM>(TEXT("FSM"));
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::InitMap()
{
	srand((unsigned)time(NULL));

	TArray<int32> randomList = { 0,1,2,3 };
	for (int i = 0; i <= 3; i++)
	{
		int32 ran = FMath::RandRange(0, randomList.Num());
		preference.Add((EEnemyPreference)i, ran);
		randomList.RemoveAt(ran);
		preference.Add(TTuple<EEnemyPreference, int32>(EEnemyPreference::Heal, ran));
	}
}

void AEnemy::SetMap(EEnemyPreference prefer, int32 num)
{
	if (preference.Find(prefer))
		preference[prefer] = num;
	else
		preference.Add(TTuple<EEnemyPreference, int32>(prefer, num));
}

void AEnemy::SetCharacter()
{
}

void AEnemy::Act()
{
}

