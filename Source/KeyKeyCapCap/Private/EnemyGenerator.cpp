// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyGenerator.h"

// Sets default values
AEnemyGenerator::AEnemyGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OpponentClass = AEnemy::StaticClass();
}

// Called when the game starts or when spawned
void AEnemyGenerator::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemyGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GenerateEnemyLoop();
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
	//mouse pos ³Ö¾îÁÖ°í ·£´ýÀ¸·Î µ¹·Á¼­ Å¸°Ù Àæ±â
	AActor* randomTargetPos = mousePos[FMath::RandRange(0, mousePos.Num() - 1)];
	const FVector SpawnLocation = randomTargetPos->GetActorLocation() + FVector::UpVector * 88.0f;
	AActor* OpponentActor = GetWorld()->SpawnActor(OpponentClass, &SpawnLocation, &FRotator::ZeroRotator);

	AEnemy* OpponentEnemy = Cast<AEnemy>(OpponentActor);
	if (OpponentEnemy)
	{
		OpponentEnemy->InitTarget(randomTargetPos);
	}
}

