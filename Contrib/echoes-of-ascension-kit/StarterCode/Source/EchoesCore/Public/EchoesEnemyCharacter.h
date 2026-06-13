// Echoes of Ascension - starter scaffold.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "EchoesEnemyCharacter.generated.h"

class UAbilitySystemComponent;
class UEchoesAttributeSet;
class UGameplayEffect;

/**
 * AI enemy. Unlike the player, the ASC lives on the pawn itself (Full replication) — enemies don't
 * persist across respawns, so co-locating the ASC with the body is simpler. See UE5_Gotchas/01.
 */
UCLASS()
class ECHOESCORE_API AEchoesEnemyCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AEchoesEnemyCharacter(const FObjectInitializer& ObjectInitializer);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEchoesAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
	TSubclassOf<UGameplayEffect> DefaultAttributesEffect;
};
