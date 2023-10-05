// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyKeyLibrary.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "KeycapActor.generated.h"

const int MAX_LEVEL = 7;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FClickSignature);

UCLASS()
class KEYKEYCAPCAP_API AKeycapActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKeycapActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundCue* ClickSound;


	UFUNCTION()
	void UClickEvent();
	UPROPERTY(BlueprintAssignable, Category = "Action")
	FClickSignature OnClickDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SetLevel();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetMesh();

	int GetKeycapLevel()
	{
		return level;
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KeyInput)
	KEY_TYPE key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UStaticMeshComponent* baseMesh;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect)
	//class UNiagaraSystem* enterEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (MakeEditWidget = true))
	TArray<FVector> upgradeColors;

	UPROPERTY()
	class UParticleSystem* upgradeParticle;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float moveDistance = 1.f;

private:
	int level = 0;
	int clickNum = 0;
};
