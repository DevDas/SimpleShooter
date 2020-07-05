// @Copyright DevDasTour 

#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	
	if (AIBehavior)
	{
		RunBehaviorTree(AIBehavior);
	}
	GetBlackboardComponent()->SetValueAsVector("StartLocation", GetPawn()->GetActorLocation());
}

bool AShooterAIController::IsDead() const
{
	AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());
	if (ControlledCharacter)
	{
		return ControlledCharacter->IsDied();
	}

	return true;
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Detaching AI Pawn
	AShooterCharacter* MyPawn = Cast<AShooterCharacter>(GetPawn());
	if (MyPawn && MyPawn->IsDied())
	{
		GetPawn()->DetachFromControllerPendingDestroy();
	}
}