// @Copyright DevDasTour 

#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	APawn* MyPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!MyPawn) return;
	SetFocus(MyPawn);

}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* MyPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!MyPawn) return;

	auto PawnLocation = MyPawn->GetActorLocation();
	auto AILoc = GetPawn()->GetActorLocation();
	auto Direc = (PawnLocation - AILoc).GetSafeNormal();

	
	if ((PawnLocation - AILoc).Size() >= 500)
	{
		GetPawn()->AddMovementInput(Direc);
	}
}