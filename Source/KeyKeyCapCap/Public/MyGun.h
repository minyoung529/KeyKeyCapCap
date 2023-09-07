// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "MyGun.generated.h"

UCLASS()
class KEYKEYCAPCAP_API AMyGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	float duration = 1.f;

private:
	float timer = 0.f;

	UPROPERTY()
	USceneComponent* fireTransform;

public:
	void Fire();
};
