// @Copyright DevDasTour 

#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "DrawDebugHelpers.h"

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

	FVector Location;
	FRotator Rotation;

	APawn* MyPawn = Cast<APawn>(GetOwner());
	if (!MyPawn) return;
	AController* Controller = MyPawn->GetController();
	if (!Controller) return;

	Controller->GetPlayerViewPoint(Location, Rotation);

	FHitResult Hit;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = true;
	QueryParams.bReturnPhysicalMaterial = true;

	FVector TraceEnd = Location + (Rotation.Vector() * TraceLength);

	bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, TraceEnd, ECollisionChannel::ECC_GameTraceChannel1, QueryParams);

	if (bSuccess)
	{
		FVector ShotDirection = -Rotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactFX, Hit.Location, ShotDirection.Rotation());

		AActor* HitActor = Hit.GetActor();
		if (!HitActor) return;

		FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
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