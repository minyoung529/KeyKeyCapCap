// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyFSM.h"
#include "CombatCharacter.h"
#include "Enemy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChangeStateSignature, EEnemyState, State);

UENUM(BlueprintType)
enum class EEnemyPreference : uint8
{
	BigAttack, //강공
	SmallAttack, //약공
	Defence,
	Heal,
	HethalMove, // 필살기
};
UCLASS()
class AEnemy : public ACombatCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	virtual void InitCharacter() override;
	virtual void Act() override;
public:
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameInfo)
		TMap<EEnemyPreference, int32> preference;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = GameInfo)
		float needHethalMoveTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSMComp)
		class UEnemyFSM* fsm;

		UFUNCTION()
		void OnChangeStateEvent(EEnemyState state);
		UPROPERTY(BlueprintAssignable, Category = "FSM")
		FChangeStateSignature OnChangeStateDelegate;

private:
	void InitMap();
	void SetMap(EEnemyPreference, int32);
	EEnemyState GetRandomVal(int, int, int, int);
public:
	void ChangeState();
	EEnemyState GetMap();
	void ChangeHp(int);
};