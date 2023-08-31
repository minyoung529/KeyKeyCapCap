// Fill out your copyright notice in the Description page of Project Settings.

#include "KeycapActor.h"
#include "MyKeyLibrary.h"

// Sets default values
AKeycapActor::AKeycapActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeycapMesh"));
	baseMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AKeycapActor::BeginPlay()
{
	Super::BeginPlay();
	
	curState = KEY_STATE::IDLE;
	PrimaryActorTick.bCanEverTick = true;
}

// Called every frame
void AKeycapActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const char* fkey = MyKeyLibrary::GetKey(key);

	// INPUT
	if (GetWorld()->GetFirstPlayerController()->WasInputKeyJustPressed(FKey(FName(fkey))))
	{
		ChangeState(KEY_STATE::PRESS);
	}

	if (fsmDict.find(curState) != fsmDict.end())
	{
		fsmDict[curState].OnUpdate();
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

void AKeycapActor::ChangeState(KEY_STATE state)
{
	if (fsmDict.find(curState) != fsmDict.end())
	{
		fsmDict[curState].OnExit();
	}

	if (fsmDict.find(state) != fsmDict.end())
	{
		fsmDict[state].OnEnter();
	}

	curState = state;
}
