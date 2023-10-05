// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/CapsuleComponent.h"
#include "MyBullet.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AEnemy::AEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	fsm = CreateDefaultSubobject<UEnemyFSM>(TEXT("FSM"));
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	UCapsuleComponent* capCom = GetCapsuleComponent();
	capCom->OnComponentHit.AddDynamic(this, &AEnemy::OnHit);

	InitPreferance();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::OnChangeStateEvent(EEnemyState state)
{
}

void AEnemy::InitPreferance()
{
	srand((unsigned)time(NULL));
	//0 : high priority
	//4 : low priority
	TArray<int32> randomList = { 0, 1, 2 };
	for (int i = 0; i < 3; i++)
	{
		int32 ran = FMath::RandRange(0, randomList.Num() - 1); //find random between 0~2

		preferenceArr.Add((EEnemyPreference)ran);
		randomList.RemoveAt(ran);
	}
	preferenceArr.Add(EEnemyPreference::Heal);
}

void AEnemy::ChangeState()
{
	if (OnChangeStateDelegate.IsBound())
	{
		OnChangeStateDelegate.Broadcast(fsm->mState); // This will call MyFunction with the parameter
	}

	UE_LOG(LogTemp, Log, TEXT("CHAGNE STATE - %d"), (int)fsm->mState);

	// 일단 여기에 작성
	if (fsm->mState == EEnemyState::Defence)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), defenceVfx, GetActorLocation(), FRotator::ZeroRotator, defenceVfxScale);
		UE_LOG(LogTemp, Log, TEXT("EFFECT VFX"));
	}
}

EEnemyState AEnemy::GetMap()
{
	EEnemyState result = EEnemyState::Move;
	if (hp > maxHp / 2)
	{
		result = GetRandomVal(40, 35, 15, 10);
	}
	else
	{
		result = GetRandomVal(40, 35, 25, 0);
	}
	return result;
}

void AEnemy::ChangeHp(int changeHp)
{
	hp += changeHp;
}
UFUNCTION(BlueprintCallable)
void AEnemy::InitTarget(AActor* target)
{
	fsm->target = target;
}


EEnemyState AEnemy::GetRandomVal(int first, int second, int third, int fourth)
{
	int ranNum = FMath::RandRange(1, 100);
	int chooseVal = 0;

	if (first >= ranNum)
		chooseVal = 0;
	else if (first + second >= ranNum)
		chooseVal = 1;
	else if (first + second + third >= ranNum)
		chooseVal = 2;
	else
		chooseVal = 3;

	UE_LOG(LogTemp, Log, TEXT("Enemy_RandomVal %d"), chooseVal);
	const EEnemyPreference prefer = preferenceArr[chooseVal];
	EEnemyState state;
	switch (prefer)
	{
	case EEnemyPreference::BigAttack:
		state = EEnemyState::BigAttack;
		break;
	case EEnemyPreference::SmallAttack:
		state = EEnemyState::SmallAttack;
		break;
	case EEnemyPreference::Defence:
		state = EEnemyState::Defence;
		break;
	case EEnemyPreference::Heal:
		state = EEnemyState::Heal;
		break;
	default:
		state = EEnemyState::SmallAttack;
		break;
	}
	return state;
}

void AEnemy::InitCharacter()
{
}

void AEnemy::Act()
{
}

void AEnemy::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	auto bullet = Cast<AMyBullet>(OtherActor);
	if (bullet)
	{
		bullet->Destroy();
		fsm->Damage(bullet->GetDamage());
	}
}
