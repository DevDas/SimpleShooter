// @Copyright DevDasTour 

#include "BTTaskNode_Shoot.h"
#include "ShooterCharacter.h"
#include "AIController.h"

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

	Pawn->StartFire();

	return EBTNodeResult::Succeeded;
}
