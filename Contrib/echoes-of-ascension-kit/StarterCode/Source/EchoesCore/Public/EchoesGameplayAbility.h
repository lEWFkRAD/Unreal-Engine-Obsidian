// Echoes of Ascension - starter scaffold.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayTagContainer.h"
#include "EchoesGameplayAbility.generated.h"

/**
 * Base GameplayAbility for Echoes of Ascension (Aether Mastery skills derive from this).
 * InstancedPerActor is the right default for most RPG abilities (per-actor cooldown/state).
 */
UCLASS()
class ECHOESCORE_API UEchoesGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UEchoesGameplayAbility();

	/** Tag used to bind this ability to an Enhanced Input action (input-tag binding). */
	UPROPERTY(EditDefaultsOnly, Category = "Echoes")
	FGameplayTag InputTag;
};
