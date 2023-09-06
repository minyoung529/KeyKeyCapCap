// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyFSM.h"
#include "Enemy.h"
#include <Components/CapsuleComponent.h>

// Sets default values for this component's properties
UEnemyFSM::UEnemyFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyFSM::BeginPlay()
{
	Super::BeginPlay();


	me = Cast<AEnemy>(GetOwner());
	mState = EEnemyState::Move;
}


// Called every frame
void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CoolTime();
	switch (mState)
	{
	case EEnemyState::Move:
		Move();
		break;
	case EEnemyState::Death:
		Death();
		break;
	case EEnemyState::TotalAttack:
		break;
	case EEnemyState::SingleAttack:
		break;
	case EEnemyState::Defence:
		Defence();
		break;
	case EEnemyState::Heal:
		Heal();
		break;
	case EEnemyState::HethalMove:
		HethalMove();
		break;
	default:
		break;
	}
}
void UEnemyFSM::Attack()
{
}
void UEnemyFSM::FindTargets()
{
}
void UEnemyFSM::FindTarget()
{
}
EEnemyState UEnemyFSM::ChooseNextAct()
{
	if (canUseHethalMove && canHethalMove) //필살기 사용 가능
	{
		return EEnemyState::HethalMove;
	}
	
	return me->GetMap();
}
void UEnemyFSM::Move()
{
	if (target == NULL) return;
	FVector dest = target->GetActorLocation();
	// 방향
	FVector dir = dest - me->GetActorLocation();
	// 방향으로 이동
	me->AddMovementInput(dir.GetSafeNormal());
	if (dir.Size() < attackRange)
	{
		mState = ChooseNextAct();
	}
}
void UEnemyFSM::TotalAttack()
{
}

void UEnemyFSM::SingleAttack()
{
}

void UEnemyFSM::Defence()
{
}

void UEnemyFSM::Heal()
{
	me->ChangeHp(me->heal); 
	currentTime += GetWorld()->DeltaTimeSeconds;
	// 힐 할 시 짐시 기다리기
	if (currentTime > healDelayTime)
	{
		mState = ChooseNextAct();
		currentTime = 0;
	}
}

void UEnemyFSM::HethalMove()
{
	if (canHethalMove)
		return;
	//미니게임. 
	canUseHethalMove = false;
	currentCoolTime = 0;
}

void UEnemyFSM::Damage()
{
}

void UEnemyFSM::Death()
{
	//등속운동 P = P0 + vt
	FVector P0 = me->GetActorLocation();
	FVector vt = FVector::DownVector * dieSpeed * GetWorld()->DeltaTimeSeconds;
	FVector P = P0 + vt;
	me->SetActorLocation(P);

	if (P.Z < -200.f)
	{
		//die call!
		me->Destroy();
	}
}

void UEnemyFSM::CoolTime()
{
	currentCoolTime += GetWorld()->DeltaTimeSeconds;
	if (currentCoolTime > hethalMoveDelayTime)
	{
		canUseHethalMove = true;
	}
}

