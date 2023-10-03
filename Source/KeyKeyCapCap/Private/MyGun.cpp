#include "MyGun.h"
#include "GameManager.h"
#include "MyBullet.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
AMyGun::AMyGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	fireTransform = CreateDefaultSubobject<USceneComponent>(TEXT("Fire Transform"));
}

// Called when the game starts or when spawned
void AMyGun::BeginPlay()
{
	Super::BeginPlay();

	if (GameManager::GetInstance() == nullptr)
	{
		return;
	}

	FName path = TEXT("Class'/Game/BP/MyBullet_BP.MyBullet_BP_C'");
	GeneratedBP = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *path.ToString()));

	GameManager::GetInstance()->AddGun(this);
}

// Called every frame
void AMyGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	timer += DeltaTime;

	if (timer > duration)
	{
		timer = 0.0f;
		//Fire();
	}
}

void AMyGun::Fire(int level, FVector color)
{
	if (GeneratedBP == nullptr)return;
	UWorld* world = GetWorld();
	if (world == nullptr)return;
	
	FVector location = GetActorLocation();
	AMyBullet* bullet = world->SpawnActor<AMyBullet>(GeneratedBP, location, FRotator::ZeroRotator);
	bullet->SetDamage(level, color);
}