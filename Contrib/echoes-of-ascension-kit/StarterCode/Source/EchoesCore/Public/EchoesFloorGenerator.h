// Echoes of Ascension - starter scaffold.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Math/RandomStream.h"
#include "EchoesBiomeDataAsset.h"
#include "EchoesFloorGenerator.generated.h"

/** A deterministic description of one Tower floor. Same seed => identical plan. */
USTRUCT(BlueprintType)
struct FEchoesFloorPlan
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Generation")
	int32 Seed = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Generation")
	FName BiomeId;

	UPROPERTY(BlueprintReadOnly, Category = "Generation")
	int32 RoomCount = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Generation")
	bool bIsBossFloor = false;
};

/**
 * Deterministic procedural floor planner. All randomness flows through a single FRandomStream
 * seeded from the floor seed, so runs are reproducible / resumable / co-op-safe. PCG handles
 * decoration; this handles which biome + how many rooms + whether it's a boss floor.
 * See UE5_Gotchas/04.
 */
UCLASS(BlueprintType)
class ECHOESCORE_API UEchoesFloorGenerator : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Generation")
	TArray<TObjectPtr<UEchoesBiomeDataAsset>> Biomes;

	/** Every Nth floor is a (scripted) boss floor. */
	UPROPERTY(EditAnywhere, Category = "Generation", meta = (ClampMin = "1"))
	int32 BossFloorInterval = 15;

	/** Deterministically plan a floor. PreviousBiomeId is excluded (no consecutive repeats). */
	UFUNCTION(BlueprintCallable, Category = "Generation")
	FEchoesFloorPlan GenerateFloor(int32 FloorSeed, int32 FloorIndex, FName PreviousBiomeId);

	/** Placeholder for the real entrance->exit reachability check. */
	UFUNCTION(BlueprintCallable, Category = "Generation")
	bool ValidateConnectivity(const FEchoesFloorPlan& Plan) const;

private:
	UEchoesBiomeDataAsset* PickWeightedBiome(FRandomStream& Stream, FName ExcludeId) const;
};
