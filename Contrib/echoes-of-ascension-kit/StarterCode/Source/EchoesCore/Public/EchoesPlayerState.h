// Echoes of Ascension - starter scaffold.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "EchoesPlayerState.generated.h"

class UEchoesAbilitySystemComponent;
class UEchoesAttributeSet;

/**
 * PlayerState that owns the AbilitySystemComponent (ASC-on-PlayerState pattern).
 *
 * Why PlayerState and not the Character: the ASC (and the player's attributes/active effects)
 * survive pawn death/respawn and floor transitions, and Mixed replication mode "just works"
 * because a PlayerState's Owner is already the Controller. See UE5_Gotchas/01.
 */
UCLASS()
class ECHOESCORE_API AEchoesPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AEchoesPlayerState();

	//~ IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UEchoesAttributeSet* GetAttributeSet() const { return AttributeSet; }

private:
	UPROPERTY(VisibleAnywhere, Category = "GAS")
	TObjectPtr<UEchoesAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, Category = "GAS")
	TObjectPtr<UEchoesAttributeSet> AttributeSet;
};
