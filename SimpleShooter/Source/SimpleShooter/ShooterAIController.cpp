// @Copyright DevDasTour 

#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	
	if (AIBehavior)
	{
		RunBehaviorTree(AIBehavior);
	}
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!PlayerPawn) return;

	FVector Location = PlayerPawn->GetActorLocation();
	
	// LineOfSightTo
	if (LineOfSightTo(PlayerPawn, GetPawn()->GetPawnViewLocation()))
	{
		GetBlackboardComponent()->SetValueAsVector("PlayerLocation", Location);
		GetBlackboardComponent()->SetValueAsVector("LastKnownPlayerLocation", Location);

		DrawDebugLine(GetWorld(), GetPawn()->GetPawnViewLocation(), GetPawn()->GetPawnViewLocation() + GetPawn()->GetViewRotation().Vector() * 1000, FColor::Red);
	}
	else
	{
		GetBlackboardComponent()->ClearValue("PlayerLocation");
	}
}