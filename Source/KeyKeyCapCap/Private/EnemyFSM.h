// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyFSM.generated.h"
UENUM()
enum class EEnemyState : uint8
{
	TotalAttack, //��ü �ο� ����
	SingleAttack, //�� �� ����
	Defence,
	Heal,
	HethalMove, // �ʻ��
	Move,
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
		class AActor* target;
	UPROPERTY(EditAnywhere, Category = FSM)
		float dieSpeed = 50.f;
	UPROPERTY(EditAnywhere, Category = FSM)
		float attackRange = 150.f;
	UPROPERTY(EditAnywhere, Category = FSM)
		float attackDelayTime = 2.f;
	UPROPERTY(EditAnywhere, Category = FSM)
		float healDelayTime = 5.f;
	UPROPERTY(EditAnywhere, Category = FSM)
		float hethalMoveDelayTime = 15.f;
	UPROPERTY(EditAnywhere, Category = FSM)
		bool canHethalMove = false;
	UPROPERTY(EditAnywhere, Category = FSM)
		bool canUseHethalMove = false;
	
	bool isDefence = false; 
private: // cool time
	float currentCoolTime = 0;
	float currentTime = 0;
public:
	void CoolTime();
};
