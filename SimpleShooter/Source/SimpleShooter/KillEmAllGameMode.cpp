// @Copyright DevDasTour 

#include "KillEmAllGameMode.h"
#include "ShooterPlayerController.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	APlayerController* PC = Cast<APlayerController>(PawnKilled->GetController());
	if (PC)
	{
		PC->GameHasEnded(nullptr, false);
	}
}