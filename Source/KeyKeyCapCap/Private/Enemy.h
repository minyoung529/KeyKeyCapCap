// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyFSM.h"
#include "CombatCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "NiagaraSystem.h"
#include "Enemy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChangeStateSignature, EEnemyState, State);

UENUM(BlueprintType)
enum class EEnemyPreference : uint8
{
	BigAttack, //����
	SmallAttack, //���
	Defence,
	Heal,
};
UCLASS()
class AEnemy : public ACombatCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundCue* DeadSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	virtual void InitCharacter(float, float, float, float, float, float) override;
	virtual void Act() override;
public:
	UFUNCTION()
	//void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameInfo)
	TArray<EEnemyPreference> preferenceArr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSMComp)
	class UEnemyFSM* fsm;

	UFUNCTION()
	void OnChangeStateEvent(EEnemyState state);
	UPROPERTY(BlueprintAssignable, Category = "FSM")
	FChangeStateSignature OnChangeStateDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VFX)
	class UNiagaraSystem* defenceVfx;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VFX)
	FVector defenceVfxScale;

private:
	void InitPreferance();
	EEnemyState GetRandomVal(int, int, int, int);
public:
	void ChangeState();
	EEnemyState GetMap();
	void ChangeHp(int);
public:
	UFUNCTION(BlueprintCallable)
	void InitTarget(class AActor* target);

};