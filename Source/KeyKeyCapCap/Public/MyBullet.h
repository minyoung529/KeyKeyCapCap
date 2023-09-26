// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBullet.generated.h"

UCLASS()
class KEYKEYCAPCAP_API AMyBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FVector direction;
	float timer = 0.f;

public:
	void SetMesh();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UStaticMeshComponent* baseMesh;

public:
	void SetDirection(FVector vector)
	{
		direction = vector;
	}

	FVector GetDirection()
	{
		return direction;
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float speed = 50.f;
};
