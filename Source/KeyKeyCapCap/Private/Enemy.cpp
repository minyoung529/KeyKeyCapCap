// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "MyBullet.h"

// Sets default values
AEnemy::AEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	fsm = CreateDefaultSubobject<UEnemyFSM>(TEXT("FSM"));
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	GetMesh()->OnComponentHit.AddDynamic(this, &AEnemy::OnHit);
	InitMap();


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

void AEnemy::InitMap()
{
	srand((unsigned)time(NULL));
	//0 : high priority
	//4 : low priority
	TArray<int32> randomList = { 1, 2,3 };
	preference.Add(TTuple<EEnemyPreference, int32>(EEnemyPreference::HethalMove, 0));
	for (int i = 1; i <= 3; i++)
	{
		int32 ran = FMath::RandRange(0, randomList.Num() - 1); //find random between 0~3
		SetMap((EEnemyPreference)i, ran);
		randomList.RemoveAt(ran);
	}
	preference.Add(TTuple<EEnemyPreference, int32>(EEnemyPreference::Heal, 4));
}

void AEnemy::SetMap(EEnemyPreference prefer, int32 num)
{
	if (preference.Find(prefer))
		preference[prefer] = num;
	else
		preference.Add(TTuple<EEnemyPreference, int32>(prefer, num));
}

void AEnemy::ChangeState()
{
	if (OnChangeStateDelegate.IsBound())
	{
		OnChangeStateDelegate.Broadcast(fsm->mState); // This will call MyFunction with the parameter
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

void AEnemy::InitTarget(AActor* target)
{
	fsm->target = target;
}


EEnemyState AEnemy::GetRandomVal(int first, int second, int third, int fourth)
{
	int ranNum = FMath::RandRange(1, 100);
	int chooseVal = 0;
	if (first >= ranNum)
		chooseVal = 1;
	else if (first + second >= ranNum)
		chooseVal = 2;
	else if (first + second + third >= ranNum)
		chooseVal = 3;
	else
		chooseVal = 4;

	UE_LOG(LogTemp, Log, TEXT("Enemy_RandomVal %d"), chooseVal);
	const EEnemyPreference prefer = *preference.FindKey(chooseVal);
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
	return EEnemyState::SmallAttack;
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
