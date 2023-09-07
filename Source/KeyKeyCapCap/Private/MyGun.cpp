#include "MyGun.h"
#include "MyBullet.h"

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
}

// Called every frame
void AMyGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	timer += DeltaTime;

	if (timer > duration)
	{
		timer = 0.0f;
		Fire();
	}
}

void AMyGun::Fire()
{
	AMyBullet* bullet =
		GetWorld()->SpawnActor<AMyBullet>(AMyBullet::StaticClass(),
			GetActorLocation() /*+ fireTransform->GetRelativeLocation()*/,
			FRotator(), FActorSpawnParameters());
}
