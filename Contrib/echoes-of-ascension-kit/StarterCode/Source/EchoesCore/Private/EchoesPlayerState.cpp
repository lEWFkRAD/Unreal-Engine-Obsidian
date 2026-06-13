// Echoes of Ascension - starter scaffold.

#include "EchoesPlayerState.h"
#include "EchoesAbilitySystemComponent.h"
#include "EchoesAttributeSet.h"

AEchoesPlayerState::AEchoesPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UEchoesAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	// Mixed: GameplayEffects replicate to the owning client only; tags + cues to everyone.
	// Correct mode for player-controlled heroes in (future) co-op.
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UEchoesAttributeSet>(TEXT("AttributeSet"));

	// PlayerState defaults to a low update frequency; raise it so attribute/ability state is responsive.
	SetNetUpdateFrequency(100.f);
}

UAbilitySystemComponent* AEchoesPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
