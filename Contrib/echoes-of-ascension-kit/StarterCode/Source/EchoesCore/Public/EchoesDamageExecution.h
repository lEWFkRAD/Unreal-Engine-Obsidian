// Echoes of Ascension - starter scaffold.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "EchoesDamageExecution.generated.h"

/**
 * Damage execution: reads the source's AttackPower (+ optional SetByCaller Data.Damage) and writes
 * the result into the target's transient Damage meta-attribute, which the AttributeSet then converts
 * into a Health loss. Assign this as the Execution on a GE_Damage GameplayEffect.
 */
UCLASS()
class ECHOESCORE_API UEchoesDamageExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UEchoesDamageExecution();

protected:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
