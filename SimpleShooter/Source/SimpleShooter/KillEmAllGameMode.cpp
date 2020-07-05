// @Copyright DevDasTour 

#include "KillEmAllGameMode.h"
#include "ShooterPlayerController.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	AShooterPlayerController* PC = Cast<AShooterPlayerController>(PawnKilled->GetController());
	if (PC)
	{
		EndGame(false);
		return;
	}

	for (AShooterAIController* AIController : TActorRange<AShooterAIController>(GetWorld()))
	{
		if (!AIController->IsDead())
		{
			return;
		}
	}
	EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;

		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}