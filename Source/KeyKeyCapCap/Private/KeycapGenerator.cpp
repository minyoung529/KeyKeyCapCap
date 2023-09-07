// Fill out your copyright notice in the Description page of Project Settings.


#include "KeycapGenerator.h"
#include "GameManager.h"
#include "KeycapActor.h"
#include "KeycapGenerator.h"

// Sets default values
AKeycapGenerator::AKeycapGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AKeycapGenerator::BeginPlay()
{
	Super::BeginPlay();
	UWorld* world = GetWorld();

	FActorSpawnParameters spawnParams;
	FRotator rotator;
	FVector spawnLocation = FVector::ZeroVector;

	for (int i = 0; i < (int)KEY_TYPE::Count; i++)
	{
		AKeycapActor* keycap =
		world->SpawnActor<AKeycapActor>(AKeycapActor::StaticClass(), spawnLocation, rotator, spawnParams);

		keycap->key = (KEY_TYPE)i;
		keycap->SetMesh();
	}
}

// Called every frame
void AKeycapGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

