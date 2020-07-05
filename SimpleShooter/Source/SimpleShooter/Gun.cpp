// @Copyright DevDasTour 

#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "DrawDebugHelpers.h"
#include "Sound/SoundBase.h"

AGun::AGun()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	RootComponent = Root;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(RootComponent);

	TraceLength = 10000;
}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFX, SkeletalMesh, "MuzzleFlashSocket");
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, SkeletalMesh, "MuzzleFlashSocket");

	FHitResult Hit;
	FVector ShotDirection;

	bool bSuccess = GunTrace(Hit, ShotDirection);
	

	if (bSuccess)
	{

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactFX, Hit.Location, ShotDirection.Rotation());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ImpactSound, Hit.Location);

		AActor* HitActor = Hit.GetActor();
		if (!HitActor) return;

		FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);

		AController* Controller = GetOwnerController();

		HitActor->TakeDamage(Damage, DamageEvent, Controller, this);
	}
}

void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	FVector Location;
	FRotator Rotation;

	AController* Controller = GetOwnerController();
	if (!Controller) return false;

	Controller->GetPlayerViewPoint(Location, Rotation);
	ShotDirection = -Rotation.Vector();

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = true;
	QueryParams.bReturnPhysicalMaterial = true;

	FVector TraceEnd = Location + (Rotation.Vector() * TraceLength);

	return GetWorld()->LineTraceSingleByChannel(Hit, Location, TraceEnd, ECollisionChannel::ECC_GameTraceChannel1, QueryParams);
}

AController* AGun::GetOwnerController() const
{
	APawn* MyPawn = Cast<APawn>(GetOwner());
	if (!MyPawn) return nullptr;
	return MyPawn->GetController();
}