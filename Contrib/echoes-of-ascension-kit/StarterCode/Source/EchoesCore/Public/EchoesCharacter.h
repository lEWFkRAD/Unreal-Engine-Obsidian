// Echoes of Ascension - starter scaffold.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "EchoesCharacter.generated.h"

class UAbilitySystemComponent;
class UGameplayAbility;
class UGameplayEffect;

/**
 * Player avatar. The ASC lives on the PlayerState, not here — this forwards to it.
 *
 * The load-bearing detail is InitAbilityActorInfo timing: it must be called on the SERVER in
 * PossessedBy AND on the OWNING CLIENT in OnRep_PlayerState, or the client gets no abilities.
 * See UE5_Gotchas/01.
 */
UCLASS()
class ECHOESCORE_API AEchoesCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AEchoesCharacter();

	//~ IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/** Abilities granted on possession (server only). */
	UPROPERTY(EditDefaultsOnly, Category = "GAS")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	/** Instant GameplayEffect that seeds the starting attribute values (GE_InitStats). */
	UPROPERTY(EditDefaultsOnly, Category = "GAS")
	TSubclassOf<UGameplayEffect> DefaultAttributesEffect;

	void GiveDefaultAbilities();
	void InitDefaultAttributes();

private:
	void InitAbilityActorInfoFor(AActor* InOwnerActor, AActor* InAvatarActor);
};
