// Echoes of Ascension - starter scaffold.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "EchoesAttributeSet.generated.h"

// Standard GAS accessor macro (getter / value getter / setter / initter) for each attribute.
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * Core attribute set for Echoes of Ascension.
 * Lives on the ASC (which lives on the PlayerState). Initialize VALUES via a GameplayEffect
 * (GE_InitStats), not in the constructor — the ctor defaults below are only a safety net.
 */
UCLASS()
class ECHOESCORE_API UEchoesAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UEchoesAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, Category = "Echoes|Attributes", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UEchoesAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, Category = "Echoes|Attributes", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UEchoesAttributeSet, MaxHealth)

	// Aether — the elemental resource (mana) spent by abilities.
	UPROPERTY(BlueprintReadOnly, Category = "Echoes|Attributes", ReplicatedUsing = OnRep_Aether)
	FGameplayAttributeData Aether;
	ATTRIBUTE_ACCESSORS(UEchoesAttributeSet, Aether)

	UPROPERTY(BlueprintReadOnly, Category = "Echoes|Attributes", ReplicatedUsing = OnRep_MaxAether)
	FGameplayAttributeData MaxAether;
	ATTRIBUTE_ACCESSORS(UEchoesAttributeSet, MaxAether)

	UPROPERTY(BlueprintReadOnly, Category = "Echoes|Attributes", ReplicatedUsing = OnRep_AttackPower)
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UEchoesAttributeSet, AttackPower)

	// Damage — transient META attribute. NOT replicated, NOT in GetLifetimeReplicatedProps.
	// The damage Execution Calc writes here; PostGameplayEffectExecute converts it into a Health loss.
	UPROPERTY(BlueprintReadOnly, Category = "Echoes|Attributes|Meta")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UEchoesAttributeSet, Damage)

protected:
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

	UFUNCTION()
	void OnRep_Aether(const FGameplayAttributeData& OldAether);

	UFUNCTION()
	void OnRep_MaxAether(const FGameplayAttributeData& OldMaxAether);

	UFUNCTION()
	void OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower);
};
