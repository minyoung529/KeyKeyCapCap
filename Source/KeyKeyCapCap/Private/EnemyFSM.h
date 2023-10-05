// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "EnemyFSM.generated.h"
UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	BigAttack, //전체 인원 공격
	SmallAttack, //한 명 공격
	Defence,
	Heal,
	Move,
	Idle,
	Death,
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UEnemyFSM : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEnemyFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundCue* DeadSound;

	UPROPERTY(EditAnywhere, Category = FSM)
		EEnemyState mState = EEnemyState::Move;
private:
	void Attack(float damage);
	void ChooseNextAct();
public://fsm function
	void Move();
	void BigAttack();
	void SmallAttack();
	void Defence();
	void Heal();
	UFUNCTION()
	void Damage(float damage);
	void Death();
public:
	//own actor
	UPROPERTY()
		class AEnemy* me;
	UPROPERTY(EditAnywhere, Category = FSM)
		class AActor* target;
	UPROPERTY(EditAnywhere, Category = FSM)
		float dieSpeed = 50.f;
	UPROPERTY(EditAnywhere, Category = FSM)
		float attackRange = 150.f;
private: // cool time
	UPROPERTY(EditAnywhere, Category = FSM)
		float attackDelayTime = 2.f;
	UPROPERTY(EditAnywhere, Category = FSM)
		float healDelayTime = 3.f;
	UPROPERTY(EditAnywhere, Category = FSM)
		float defenceDelayTime = 5.f;
public:
	bool isDefence = false; 
	float currentHealTime = 0;
	float currentDefenceTime = 0;
	float currentAttackTime = 0;
	
};
