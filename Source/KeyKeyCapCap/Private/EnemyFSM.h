// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyFSM.generated.h"
UENUM()
enum class EEnemyState : uint8
{
	Move,
	Damage,
	Death,
	TotalAttack, //전체 인원 공격
	SingleAttack, //한 명 공격
	Defence,
	Heal,
	HethalMove, // 필살기
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
		EEnemyState mState = EEnemyState::Move;
private:
	void Attack();
	void FindTargets();
	void FindTarget();
	EEnemyState ChooseNextAct();
public://fsm function
	void Move();
	void TotalAttack();
	void SingleAttack();
	void Defence();
	void Heal();
	void HethalMove();
	void Damage();
	void Death();
public:
	//own actor
	UPROPERTY()
		class AEnemy* me;
	UPROPERTY(EditAnywhere, Category = FSM)
		float dieSpeed = 50.f;
	UPROPERTY(EditAnywhere, Category = FSM)
		float attackRange = 150.f;
	UPROPERTY(EditAnywhere, Category = FSM)
		float attackDelayTime = 2.f;
	UPROPERTY(EditAnywhere, Category = FSM)
		bool canHethalMove = false;
	UPROPERTY(EditAnywhere, Category = FSM)
		bool canUseHethalMove = false;
public:
	void CoolTime();
};
