// @Copyright DevDasTour

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDead);

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapons")
	TSubclassOf<class AGun> GunClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapons")
	class AGun* Gun;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	float Health;

	UFUNCTION(BlueprintPure)
	bool IsDied() const { return Health <= 0; };

	void StartFire();
	void StopFire();

	UPROPERTY(BlueprintAssignable, Category = "CustomDelegate")
	FOnDead OnDead;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);

	void BeginCrouch();
	void EndCrouch();

	void LookUpRate(float Value);
	void LookRightRate(float Value);

	UPROPERTY(EditAnywhere)
	float RotationRate = 10;
};