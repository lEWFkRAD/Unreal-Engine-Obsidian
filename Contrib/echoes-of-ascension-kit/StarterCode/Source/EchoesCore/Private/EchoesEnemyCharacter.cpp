// Echoes of Ascension - starter scaffold.

#include "EchoesEnemyCharacter.h"
#include "AbilitySystemComponent.h"
#include "EchoesAttributeSet.h"
#include "GameplayEffect.h"

AEchoesEnemyCharacter::AEchoesEnemyCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);

	AttributeSet = CreateDefaultSubobject<UEchoesAttributeSet>(TEXT("AttributeSet"));
}

UAbilitySystemComponent* AEchoesEnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AEchoesEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Clients init here (the pawn-owned ASC has replicated down).
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void AEchoesEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!HasAuthority() || !AbilitySystemComponent)
	{
		return;
	}

	// Server: owner and avatar are both this pawn.
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	if (DefaultAttributesEffect)
	{
		FGameplayEffectContextHandle Context = AbilitySystemComponent->MakeEffectContext();
		Context.AddSourceObject(this);
		// Pass the CLASS (TSubclassOf), not a CDO pointer.
		const FGameplayEffectSpecHandle SpecHandle =
			AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributesEffect, 1.f, Context);
		if (SpecHandle.IsValid())
		{
			AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}
