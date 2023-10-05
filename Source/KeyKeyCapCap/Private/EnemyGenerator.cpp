// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyGenerator.h"

// Sets default values
AEnemyGenerator::AEnemyGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FClassFinder<AEnemy> EnemyRefBP(TEXT("/Game/Battle/BP/BPBoss.BPBoss_c"));
	if (EnemyRefBP.Class)
	{
		OpponentClass = EnemyRefBP.Class;
	}
}

// Called when the game starts or when spawned
void AEnemyGenerator::BeginPlay()
{
	Super::BeginPlay();
	GenerateEnemy();
}

// Called every frame
void AEnemyGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GenerateEnemyLoop();
}

void AEnemyGenerator::GenerateEnemyLoop()
{
	UE_LOG(LogTemp, Log, TEXT("EnemyGenerate!"));
	currentGenerateTime += GetWorld()->DeltaTimeSeconds;
	if (currentGenerateTime > generateDelayTime)
	{
		GenerateEnemy();
		currentGenerateTime = 0;
	}
}

void AEnemyGenerator::GenerateEnemy()
{
	AActor* randomTargetPos = mousePos[FMath::RandRange(0, mousePos.Num() - 1)];
	const FVector SpawnLocation = randomTargetPos->GetActorLocation() + FVector::UpVector * 2.0f + FVector::YAxisVector * -120.0;
	AActor* OpponentActor = GetWorld()->SpawnActor(OpponentClass, &SpawnLocation, &FRotator::ZeroRotator);
	UE_LOG(LogTemp, Log, TEXT("EnemyGenerate!"));

	AEnemy* OpponentEnemy = Cast<AEnemy>(OpponentActor);
	if (OpponentEnemy)
	{
		OpponentEnemy->InitTarget(randomTargetPos);
	}
}

