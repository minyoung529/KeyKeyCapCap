// Fill out your copyright notice in the Description page of Project Settings.

#include "KeycapActor.h"
#include "MyKeyLibrary.h"
#include "GameManager.h"
//#include "C:/Program Files/Epic Games/UE/UE_5.1/Engine/Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
AKeycapActor::AKeycapActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeycapMesh"));
	baseMesh->SetupAttachment(RootComponent);

	upgradeColors.Add(FVector(1.0f, 0.f, 0.f));
	upgradeColors.Add(FVector(1.0f, 0.368627f, 0.f));
	upgradeColors.Add(FVector(1.0f, 0.894118, 0.f));
	upgradeColors.Add(FVector(0.048889f, 0.893333f, 0.017778));
	upgradeColors.Add(FVector(0.16f, 0.533333f, 1.0f));
	upgradeColors.Add(FVector(1.0f, 0.f, 0.564444f));
	upgradeColors.Add(FVector(0.422222f, 0.f, 1.0f));

	level = 0;

	ConstructorHelpers::FObjectFinder<UParticleSystem> keycapParticle(TEXT("/Script/Engine.ParticleSystem'/Game/Realistic_Starter_VFX_Pack_Vol2/Particles/Sparks/P_Sparks_C.P_Sparks_C'"));

	if (keycapParticle.Succeeded())
	{
		upgradeParticle = keycapParticle.Object;
	}

}
void AKeycapActor::UClickEvent()
{
}
// Called when the game starts or when spawned
void AKeycapActor::BeginPlay()
{
	Super::BeginPlay();

	PrimaryActorTick.bCanEverTick = true;
}

void AKeycapActor::SetLevel()
{
	if (level >= MAX_LEVEL)
		return;

	if (clickNum >= 10)
	{
		clickNum = 0;
		level += 1;

		if (level >= 1 && level <= MAX_LEVEL)
		{
			//UGamePlayStatics::Spawn(, FName("Muzzle"));

			FBox box = GetComponentsBoundingBox();
			UGameplayStatics::SpawnEmitterAttached(upgradeParticle, baseMesh, TEXT("Upgrade Particle"),
				GetActorLocation() + box.GetCenter() + FVector::UpVector * 5);
			baseMesh->SetVectorParameterValueOnMaterials(TEXT("Color"), upgradeColors[level - 1]);
		}
	}
}

// Called every frame
void AKeycapActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const char* fkey = MyKeyLibrary::GetKey(key);

	if (GetWorld() == nullptr)return;
	if (GetWorld()->GetFirstPlayerController() == nullptr)return;

	// INPUT
	if (GetWorld()->GetFirstPlayerController()->WasInputKeyJustPressed(FKey(FName(fkey))))
	{
		if (OnClickDelegate.IsBound() == true) OnClickDelegate.Broadcast();

		FVector	currentLocation = GetActorLocation();
		currentLocation -= FVector::UpVector * moveDistance;
		SetActorLocation(currentLocation);

		clickNum++;

		UGameplayStatics::PlaySound2D(this, ClickSound);

		if (level >= 1)
		{
			GameManager::GetInstance()->Shoot(level, upgradeColors[level - 1]);
		}
		else
		{
			GameManager::GetInstance()->Shoot(0, FVector::ZeroVector);
		}

		//UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), enterEffect, GetActorLocation(), baseMesh->GetComponentRotation());
	}

	if (GetWorld()->GetFirstPlayerController()->WasInputKeyJustReleased(FKey(FName(fkey))))
	{
		FVector	currentLocation = GetActorLocation();
		currentLocation += FVector::UpVector * moveDistance;
		SetActorLocation(currentLocation);
	}
}

void AKeycapActor::SetMesh()
{
	const char* fkey = MyKeyLibrary::GetMeshKey(key);
	const size_t cSize = strlen(fkey) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, fkey, cSize);

	TCHAR szDec[128] = { 0, };

	swprintf(szDec, _T("/Script/Engine.StaticMesh'/Game/Computer/macintosh-128k-computer-1984/source/Mac128K_%ws.Mac128K_%ws'"), wc, wc);

	UStaticMesh* NewMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, szDec));

	if (NewMesh)
	{
		baseMesh->SetStaticMesh(NewMesh);
	}
}