// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBullet.h"

// Sets default values
AMyBullet::AMyBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeycapMesh"));
	baseMesh->SetupAttachment(RootComponent);
	SetMesh();
}

// Called when the game starts or when spawned
void AMyBullet::BeginPlay()
{
	Super::BeginPlay();
	SetActorRelativeScale3D(FVector(0.001f, 0.001f, 0.001f));
}

// Called every frame
void AMyBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector destination = GetActorLocation();
	destination += direction * speed * DeltaTime;
	SetActorLocation(destination);
}

void AKeycapActor::SetMesh()
{
	UStaticMesh* NewMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, L"/Script/Engine.StaticMesh'/Game/Bullet/sphere.sphere'"));

	if (NewMesh)
	{
		baseMesh->SetStaticMesh(NewMesh);
	}
}