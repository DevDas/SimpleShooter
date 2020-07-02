// @Copyright DevDasTour 

#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	
	AcceptanceRadius = 200;
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!PlayerPawn) return;

	// LineOfSightTo
	if (LineOfSightTo(PlayerPawn, GetPawn()->GetPawnViewLocation(), true))
	{
		MoveToActor(PlayerPawn, AcceptanceRadius);
		SetFocus(PlayerPawn);

		DrawDebugLine(GetWorld(), GetPawn()->GetPawnViewLocation(), GetPawn()->GetPawnViewLocation() + GetPawn()->GetViewRotation().Vector() * 1000, FColor::Red);
	}
	else
	{
		ClearFocus(EAIFocusPriority::Gameplay);
		StopMovement();
	}
}