// Echoes of Ascension - starter scaffold.

#include "EchoesAbilitySystemComponent.h"
#include "EchoesGameplayAbility.h"

UEchoesAbilitySystemComponent::UEchoesAbilitySystemComponent()
{
}

void UEchoesAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}

	// Collect first, then activate — TryActivateAbility can mutate the activatable list.
	TArray<FGameplayAbilitySpecHandle> ToActivate;
	for (const FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (const UEchoesGameplayAbility* Ability = Cast<UEchoesGameplayAbility>(Spec.Ability))
		{
			if (Ability->InputTag == InputTag)
			{
				ToActivate.Add(Spec.Handle);
			}
		}
	}

	for (const FGameplayAbilitySpecHandle& Handle : ToActivate)
	{
		TryActivateAbility(Handle);
	}
}
