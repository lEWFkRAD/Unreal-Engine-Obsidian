// Echoes of Ascension - starter scaffold.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EchoesBiomeDataAsset.generated.h"

/**
 * Defines one of the Tower's biomes for procedural selection. Data-driven so designers add
 * biomes without code. LevelAsset is a soft pointer — never hard-load every biome at startup.
 */
UCLASS(BlueprintType)
class ECHOESCORE_API UEchoesBiomeDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/** Unique identifier (used for the "no consecutive repeats" rule). */
	UPROPERTY(EditAnywhere, Category = "Biome")
	FName BiomeId;

	UPROPERTY(EditAnywhere, Category = "Biome")
	FText DisplayName;

	/** Higher weight = more likely to be picked. */
	UPROPERTY(EditAnywhere, Category = "Biome", meta = (ClampMin = "0.0"))
	float SelectionWeight = 1.f;

	/** The level/sublevel to stream for this biome (soft — loaded on demand). */
	UPROPERTY(EditAnywhere, Category = "Biome")
	TSoftObjectPtr<UWorld> LevelAsset;
};
