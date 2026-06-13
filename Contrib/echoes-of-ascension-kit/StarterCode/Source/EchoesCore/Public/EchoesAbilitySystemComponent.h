// Echoes of Ascension - starter scaffold.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "EchoesAbilitySystemComponent.generated.h"

/**
 * Project ASC subclass. Adds input-tag ability activation: bind your Enhanced Input actions to
 * AbilityInputTagPressed() and abilities tagged with the matching UEchoesGameplayAbility::InputTag fire.
 */
UCLASS()
class ECHOESCORE_API UEchoesAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UEchoesAbilitySystemComponent();

	/** Try-activate every granted ability whose UEchoesGameplayAbility::InputTag equals InputTag. */
	void AbilityInputTagPressed(const FGameplayTag& InputTag);
};
