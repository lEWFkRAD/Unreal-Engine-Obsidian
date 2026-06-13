// Echoes of Ascension - starter scaffold.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "EchoesAbilitySystemComponent.generated.h"

/**
 * Project ASC subclass. Empty for now — exists so you have a place to add input-tag binding,
 * ability-input handling, and gameplay-event helpers later without touching the engine class.
 */
UCLASS()
class ECHOESCORE_API UEchoesAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UEchoesAbilitySystemComponent();
};
