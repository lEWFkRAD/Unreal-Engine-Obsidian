// Echoes of Ascension - starter scaffold.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayEffectTypes.h"   // FActiveGameplayEffectHandle (used by value in UFUNCTIONs)
#include "EchoesEchoLibrary.generated.h"

class UAbilitySystemComponent;
class UEchoesEchoDataAsset;

/** Bind/unbind Echoes to an ASC by applying/removing their infinite ModifierEffect. */
UCLASS()
class ECHOESCORE_API UEchoesEchoLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Applies the Echo's ModifierEffect to the ASC. Returns the handle so it can be unbound later. */
	UFUNCTION(BlueprintCallable, Category = "Echoes")
	static FActiveGameplayEffectHandle BindEcho(UAbilitySystemComponent* ASC, UEchoesEchoDataAsset* Echo);

	UFUNCTION(BlueprintCallable, Category = "Echoes")
	static void UnbindEcho(UAbilitySystemComponent* ASC, FActiveGameplayEffectHandle Handle);
};
