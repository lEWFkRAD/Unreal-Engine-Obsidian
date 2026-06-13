// Echoes of Ascension - starter scaffold.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EchoesAIController.generated.h"

class UBehaviorTree;

/** AIController that runs a Behavior Tree on possession. Assign one to the enemy's AIControllerClass. */
UCLASS()
class ECHOESCORE_API AEchoesAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEchoesAIController(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

protected:
	virtual void OnPossess(APawn* InPawn) override;
};
