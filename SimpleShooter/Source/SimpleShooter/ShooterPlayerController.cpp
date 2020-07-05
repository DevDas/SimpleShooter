// @Copyright DevDasTour 

#include "ShooterPlayerController.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "ShooterCharacter.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	if (bIsWinner)
	{
		UUserWidget* GameWinScreen = CreateWidget(this, GameWinWidgetClass, "GameWinScreen");
		if (!GameWinScreen) return;
		GameWinScreen->AddToViewport();
	}
	else
	{
		UUserWidget* GameOverScreen = CreateWidget(this, GameOverWidgetClass, "GameOverScreen");
		if (!GameOverScreen) return;
		GameOverScreen->AddToViewport();
	}

	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay, false);
}