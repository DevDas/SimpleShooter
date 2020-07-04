// @Copyright DevDasTour 

#include "BTTaskNode_Shoot.h"
#include "ShooterCharacter.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"

UBTTaskNode_Shoot::UBTTaskNode_Shoot()
{
	NodeName = "Shoot";
}

EBTNodeResult::Type UBTTaskNode_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!OwnerComp.GetAIOwner()) return EBTNodeResult::Failed;

	AShooterCharacter* Pawn = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (!Pawn) return EBTNodeResult::Failed;

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!PlayerPawn) return EBTNodeResult::Failed;

	AShooterCharacter* PlayerCharacter = Cast<AShooterCharacter>(PlayerPawn);

	if (PlayerCharacter && !PlayerCharacter->IsDied())
	{
		Pawn->StartFire();
	}

	return EBTNodeResult::Succeeded;
}
