// Echoes of Ascension - starter scaffold.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "EchoesEchoDataAsset.generated.h"

class UGameplayEffect;
class UTexture2D;

/**
 * An Echo — an Arcanthi power fragment. Data-driven: it's a display payload plus an (infinite)
 * GameplayEffect that's applied to the wielder's ASC when the Echo is bound at a shrine.
 * The hook of the game is build variety, so new Echoes should be new assets, not new code.
 */
UCLASS(BlueprintType)
class ECHOESCORE_API UEchoesEchoDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Echo")
	FName EchoId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Echo")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Echo")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Echo")
	TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Echo")
	FGameplayTagContainer GrantedTags;

	/** The infinite GameplayEffect applied while this Echo is bound. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Echo")
	TSubclassOf<UGameplayEffect> ModifierEffect;
};
