// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyFSM.h"
#include "MyTESTKeyboard.h"
#include "Enemy.h"
#include "GameManager.h"
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
	default:
		break;
	}
}

EEnemyState UEnemyFSM::ChooseNextAct()
{
	me->ChangeState();
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
	currentAttackTime += GetWorld()->DeltaTimeSeconds;
	if (currentAttackTime > attackDelayTime)
	{
		UE_LOG(LogTemp, Log, TEXT("FSM_attack"));
		GameManager* mgr;
		mgr->GetInstance()->AddHp(-damage);
		currentAttackTime = 0;
		mState = ChooseNextAct();
		return true;
	}
	float distance = FVector::Distance(target->GetActorLocation(), me->GetActorLocation());
	if (distance > attackRange)
	{
		mState = EEnemyState::Move;
		me->ChangeState();
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
UFUNCTION()
void UEnemyFSM::Damage(float damage)
{
	UE_LOG(LogTemp, Log, TEXT("FSM_Damage"));
	me->hp -= damage;
	if (me->hp <= 0)
	{
		mState = EEnemyState::Death;
		me->ChangeState();
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

