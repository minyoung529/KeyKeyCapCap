// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyKeyLibrary.h"
#include "GameFramework/Actor.h"
#include "MyState.h"
#include "KeycapActor.generated.h"

UENUM()
enum KEY_STATE
{
	IDLE,
	PRESS,
	UPGRADE,
	FIGHT,

	COUNT
};

UCLASS()
class KEYKEYCAPCAP_API AKeycapActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKeycapActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetMesh();

private:
	void ChangeState(KEY_STATE state);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KeyInput)
	KEY_TYPE key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UStaticMeshComponent* baseMesh;


private:
	unordered_map<KEY_STATE, MyState> fsmDict;
	KEY_STATE curState;
};
