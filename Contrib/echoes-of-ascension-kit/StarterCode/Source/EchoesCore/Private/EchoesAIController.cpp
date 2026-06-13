// Echoes of Ascension - starter scaffold.

#include "EchoesAIController.h"
#include "BehaviorTree/BehaviorTree.h"

AEchoesAIController::AEchoesAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Add a UAIPerceptionComponent here if you want sight/hearing-driven targeting.
}

void AEchoesAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
}
