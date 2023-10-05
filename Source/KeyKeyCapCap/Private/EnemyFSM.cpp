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
	me->ChangeState();

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

void UEnemyFSM::ChooseNextAct()
{
	mState = me->GetMap();
	me->ChangeState();
}
void UEnemyFSM::Move()
{
	if (target == NULL) return;
	FVector dest = target->GetActorLocation();
	// 방향
	FVector dir = dest - me->GetActorLocation();
	// 방향으로 이동
	me->AddMovementInput(dir.GetSafeNormal());
<<<<<<< HEAD
	/*UE_LOG(LogTemp, Log, TEXT("FSM_Move \n  my pos x : %f y : %f z : %f\n my dest x : %f y : %f z : %f\n dir x : %f y : %f z : %f"), me->GetActorLocation().X, me->GetActorLocation().Y, me->GetActorLocation().Z, dest.X, dest.Y, dest.Z, dir.X, dir.Y, dir.Z);*/
	if (dir.Size() < attackRange)
	{
		ChooseNextAct();
		UE_LOG(LogTemp, Log, TEXT("FSM_endMove"));
=======
	if (dir.Size() < attackRange)
	{
		mState = ChooseNextAct();
>>>>>>> KeyCapStructure
	}
}
void UEnemyFSM::Attack(float damage)
{
	currentAttackTime += GetWorld()->DeltaTimeSeconds;
	float distance = FVector::Distance(target->GetActorLocation(), me->GetActorLocation());
	if (distance > attackRange)
	{
		mState = EEnemyState::Move;
		me->ChangeState();
	}
	if (currentAttackTime > attackDelayTime)
	{
		GameManager* mgr;
		mgr->GetInstance()->AddHp(-damage);
		currentAttackTime = 0;
		ChooseNextAct();
	}
}
void UEnemyFSM::BigAttack()
{
	Attack(me->attack * FMath::RandRange(1.1f, 1.4f));
}

void UEnemyFSM::SmallAttack()
{
	Attack(me->attack * FMath::RandRange(0.7f, 0.9f));
}

void UEnemyFSM::Defence()
{
	UE_LOG(LogTemp, Log, TEXT("FSM_Defence"));
	isDefence = true;
	
	currentDefenceTime += GetWorld()->DeltaTimeSeconds;
	if (currentDefenceTime > defenceDelayTime)
	{
		isDefence = false;
		ChooseNextAct();
		currentHealTime = 0;
	}
}

void UEnemyFSM::Heal()
{
	currentHealTime += GetWorld()->DeltaTimeSeconds;
	// 힐 할 시 짐시 기다리기
	if (currentHealTime > healDelayTime)
	{
		me->ChangeHp(me->heal);
		ChooseNextAct();
		currentHealTime = 0;
	}
}
UFUNCTION()
void UEnemyFSM::Damage(float damage)
{
	me->hp -= damage;
	if (isDefence)
		me->hp += me->shield;
	if (me->hp <= 0)
	{
		mState = EEnemyState::Death;
		me->ChangeState();
		me->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else
		ChooseNextAct();
}

void UEnemyFSM::Death()
{
	//등속운동 P = P0 + vt
	FVector P0 = me->GetActorLocation();
	FVector vt = FVector::UpVector * dieSpeed * GetWorld()->DeltaTimeSeconds;
	FVector P = P0 + vt;
	me->SetActorLocation(P);

	if (P.Z < -200.f)
	{
		//die call!
		me->Destroy();
	}
}

