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
}


// Called every frame
void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
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

	return EEnemyState::Move;
}
void UEnemyFSM::Move()
{
	/*if (dir.Size() < attackRange)
	{
		mState = ChooseNextAct();
	}*/
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
}

void UEnemyFSM::HethalMove()
{
	if (canHethalMove)
		return;
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
}

