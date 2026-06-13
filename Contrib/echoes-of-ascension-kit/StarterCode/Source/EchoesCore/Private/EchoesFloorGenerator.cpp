// Echoes of Ascension - starter scaffold.

#include "EchoesFloorGenerator.h"

FEchoesFloorPlan UEchoesFloorGenerator::GenerateFloor(int32 FloorSeed, int32 FloorIndex, FName PreviousBiomeId)
{
	// Single deterministic source of randomness for the whole floor.
	FRandomStream Stream(FloorSeed);

	const UEchoesBiomeDataAsset* SelectedBiome = PickWeightedBiome(Stream, PreviousBiomeId);

	FEchoesFloorPlan Plan;
	Plan.Seed = FloorSeed;
	Plan.BiomeId = SelectedBiome ? SelectedBiome->BiomeId : NAME_None;
	Plan.RoomCount = Stream.RandRange(6, 10);
	// Floor 0 (the hub/entry) is never a boss floor; guard against the %==0 edge.
	Plan.bIsBossFloor = (FloorIndex > 0) && (BossFloorInterval > 0) && (FloorIndex % BossFloorInterval == 0);

	return Plan;
}

bool UEchoesFloorGenerator::ValidateConnectivity(const FEchoesFloorPlan& Plan) const
{
	// TODO: build the room graph and verify a guaranteed entrance->exit path exists;
	// fall back to a deterministic known-good layout if it doesn't. See UE5_Gotchas/04.
	return true;
}

UEchoesBiomeDataAsset* UEchoesFloorGenerator::PickWeightedBiome(FRandomStream& Stream, FName ExcludeId) const
{
	if (Biomes.IsEmpty())
	{
		return nullptr;
	}

	float TotalWeight = 0.f;
	for (const TObjectPtr<UEchoesBiomeDataAsset>& Biome : Biomes)
	{
		if (Biome && Biome->BiomeId != ExcludeId)
		{
			TotalWeight += Biome->SelectionWeight;
		}
	}

	if (TotalWeight <= 0.f)
	{
		return nullptr;
	}

	const float Roll = Stream.FRand() * TotalWeight;
	float Cumulative = 0.f;
	for (const TObjectPtr<UEchoesBiomeDataAsset>& Biome : Biomes)
	{
		if (Biome && Biome->BiomeId != ExcludeId)
		{
			Cumulative += Biome->SelectionWeight;
			if (Roll <= Cumulative)
			{
				return Biome.Get();
			}
		}
	}

	// Float-precision fallback: return the last eligible biome.
	for (int32 i = Biomes.Num() - 1; i >= 0; --i)
	{
		if (Biomes[i] && Biomes[i]->BiomeId != ExcludeId)
		{
			return Biomes[i].Get();
		}
	}
	return nullptr;
}
