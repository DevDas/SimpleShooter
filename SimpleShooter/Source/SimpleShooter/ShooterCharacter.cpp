// @Copyright DevDasTour

#include "ShooterCharacter.h"
#include "DrawDebugHelpers.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "ShooterAIController.h"
#include "SimpleShooterGameModeBase.h"

AShooterCharacter::AShooterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Health = MaxHealth;

	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	if (Gun)
	{
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "WeaponSocket");
		Gun->SetOwner(this);
	}
}

void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShooterCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnRight", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AShooterCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &AShooterCharacter::StopJumping);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AShooterCharacter::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AShooterCharacter::EndCrouch);

	//Shoot
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AShooterCharacter::StartFire);

	// XBox Controller
	PlayerInputComponent->BindAxis("LookUpRate", this, &AShooterCharacter::LookUpRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AShooterCharacter::LookRightRate);
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;



	if (IsDied())
	{
		OnDead.Broadcast();
		//DetachFromControllerPendingDestroy();  // Changed To SetViewTargetWithBlend in Blueprint
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		ASimpleShooterGameModeBase* GM = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if (GM)
		{
			GM->PawnKilled(this);
		}
	}

	FString HealthToString = FString::FromInt(Health);
	DrawDebugString(GetWorld(), GetActorLocation(), HealthToString, NULL, FColor::Red, 2, false, 3.f);
	return DamageToApply;
}

void AShooterCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}

void AShooterCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}

void AShooterCharacter::BeginCrouch()
{
	Crouch();
}

void AShooterCharacter::EndCrouch()
{
	UnCrouch();
}

 void AShooterCharacter::LookUpRate(float Value)
{
	 AddControllerPitchInput(Value * RotationRate * GetWorld()->GetDeltaSeconds());
}

 void AShooterCharacter::LookRightRate(float Value)
 {
	 AddControllerYawInput(Value * RotationRate * GetWorld()->GetDeltaSeconds());
 }

 void AShooterCharacter::StartFire()
 {
	 Gun->PullTrigger();
 }

 void AShooterCharacter::StopFire()
 {
 }