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

	defaultSize = FVector(0.0075f, 0.0075f, 0.0075f);
	direction = FVector::LeftVector;
	defaultSpeed = speed;

	SetActorRelativeScale3D(defaultSize);
	SetActorLocation(GetActorLocation() + FVector::UpVector);
}

// Called every frame
void AMyBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector destination = GetActorLocation();
	destination += direction * speed * DeltaTime;
	SetActorLocation(destination);
	timer += DeltaTime;
	if (timer >= 5.f)
	{
		Destroy();
	}
}

void AMyBullet::SetMesh()
{
	UStaticMesh* NewMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, L"/Script/Engine.StaticMesh'/Game/Bullet/sphere.sphere'"));

	if (NewMesh)
	{
		baseMesh->SetStaticMesh(NewMesh);
	}
}

void AMyBullet::SetDamage(int level, FVector color)
{
	baseMesh->SetVectorParameterValueOnMaterials(TEXT("Color"), color);
	baseMesh->SetVectorParameterValueOnMaterials(TEXT("EmissionColor"), color);

	damage = level + 1;
	speed = defaultSpeed + 10 * level;
}