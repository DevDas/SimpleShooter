// @Copyright DevDasTour 

#include "ShooterPlayerController.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "ShooterCharacter.h"
#include "Blueprint/UserWidget.h"
void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	UUserWidget* GameOverScreen = CreateWidget(this, GameOverWidgetClass, "GameOverScreen");
	if (GameOverScreen)
	{
		GameOverScreen->AddToViewport();
	}

	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay, false);
}