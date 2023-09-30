// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyFSM.h"
#include "MyTESTKeyboard.h"
#include "Enemy.h"
#include <Kismet/GameplayStatics.h>
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
	//UE_LOG(LogTemp, Display, TEXT(Cast<AMyTESTKeyboard>(actor)->GetName()));
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
	case EEnemyState::BigAttack:
		BigAttack();
		break;
	case EEnemyState::SmallAttack:
		SmallAttack();
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
		canUseHethalMove = false;
		currentCoolTime = 0;
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
		UE_LOG(LogTemp, Log, TEXT("FSM_endMove"));
	}
}
bool UEnemyFSM::Attack(float damage)
{
	UE_LOG(LogTemp, Log, TEXT("FSM_attack"));
	currentAttackTime += GetWorld()->DeltaTimeSeconds;
	if (currentAttackTime > attackDelayTime)
	{
		currentAttackTime = 0;
		mState = ChooseNextAct();
		return true;
	}
	float distance = FVector::Distance(target->GetActorLocation(), me->GetActorLocation());
	if (distance > attackRange)
	{
		mState = EEnemyState::Move;
	}
	return false;
}
void UEnemyFSM::BigAttack()
{
	UE_LOG(LogTemp, Log, TEXT("FSM_BigAttack"));
	if (Attack(me->attack * FMath::RandRange(1.1f, 1.4f)))
	{
		//animation
	}
}

void UEnemyFSM::SmallAttack()
{
	UE_LOG(LogTemp, Log, TEXT("FSM_SmallAttack"));
	if (Attack(me->attack * FMath::RandRange(0.7f, 0.9f)))
	{
		//animation
	}
}

void UEnemyFSM::Defence()
{
	UE_LOG(LogTemp, Log, TEXT("FSM_Defence"));
}

void UEnemyFSM::Heal()
{
	UE_LOG(LogTemp, Log, TEXT("FSM_Heal"));
	me->ChangeHp(me->heal);
	currentHealTime += GetWorld()->DeltaTimeSeconds;
	// 힐 할 시 짐시 기다리기
	if (currentHealTime > healDelayTime)
	{
		mState = ChooseNextAct();
		currentHealTime = 0;
	}
}

void UEnemyFSM::HethalMove()
{
	UE_LOG(LogTemp, Log, TEXT("FSM_HethalMove"));
	if (canHethalMove)
		return;
	//미니게임. 
	canUseHethalMove = false;
	currentCoolTime = 0;
}
UFUNCTION()
void UEnemyFSM::Damage()
{
	UE_LOG(LogTemp, Log, TEXT("FSM_Damage"));
	me->hp--;
	if (me->hp <= 0)
	{
		mState = EEnemyState::Death;
		me->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else
		mState = ChooseNextAct();
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
		UE_LOG(LogTemp, Log, TEXT("FSM_CoolTimeFinished"));
	}
}

