// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CombatCharacter.generated.h"

UCLASS()
class ACombatCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACombatCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = GameInfo)
		float atk = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = GameInfo)
		float hp = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = GameInfo)
		float lv = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = GameInfo)
		float heal = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = GameInfo)
		float def = 0;
public:
	virtual void SetCharacter();
	virtual void Act();
};
