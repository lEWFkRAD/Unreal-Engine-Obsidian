// Echoes of Ascension - starter scaffold.

#include "EchoesEchoLibrary.h"
#include "EchoesEchoDataAsset.h"
#include "AbilitySystemComponent.h"

FActiveGameplayEffectHandle UEchoesEchoLibrary::BindEcho(UAbilitySystemComponent* ASC, UEchoesEchoDataAsset* Echo)
{
	if (!ASC || !Echo || !Echo->ModifierEffect)
	{
		return FActiveGameplayEffectHandle();
	}

	FGameplayEffectContextHandle Context = ASC->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(Echo->ModifierEffect, 1.f, Context);
	if (!SpecHandle.IsValid())
	{
		return FActiveGameplayEffectHandle();
	}
	return ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

void UEchoesEchoLibrary::UnbindEcho(UAbilitySystemComponent* ASC, FActiveGameplayEffectHandle Handle)
{
	if (ASC)
	{
		ASC->RemoveActiveGameplayEffect(Handle);
	}
}
