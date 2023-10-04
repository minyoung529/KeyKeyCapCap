// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Enemy.h>
#include "EnemyGenerator.generated.h"

UCLASS()
class KEYKEYCAPCAP_API AEnemyGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	void GenerateEnemyLoop();
	void GenerateEnemy();
public:
	UPROPERTY(EditAnywhere, Category = Generate)
	float generateDelayTime = 4.f;
public:
	UPROPERTY(EditAnywhere, Category = Generate)
	TArray<AActor*>mousePos;

private:
	float currentGenerateTime = 0.f;
private:
	UPROPERTY(EditAnywhere, Category = Generate, Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AEnemy> OpponentClass;

	UPROPERTY(EditAnywhere, Category = Generate, Meta = (AllowPrivateAccess = "true"))
	float OpponentSpawnTime;
};
