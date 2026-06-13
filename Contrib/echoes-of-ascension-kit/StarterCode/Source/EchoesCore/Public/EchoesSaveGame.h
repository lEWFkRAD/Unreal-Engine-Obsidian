// Echoes of Ascension - starter scaffold.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "EchoesSaveGame.generated.h"

/**
 * PROFILE save — permanent meta-progression. Survives runs.
 * Bump SaveVersion when the layout changes and migrate in the save subsystem.
 */
UCLASS()
class ECHOESCORE_API UEchoesProfileSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(SaveGame)
	int32 SaveVersion = 1;

	UPROPERTY(SaveGame)
	TMap<FName, int32> FactionRenown;

	UPROPERTY(SaveGame)
	TArray<FName> UnlockedSkills;

	UPROPERTY(SaveGame)
	TArray<FName> EchoesInventory;
};

/**
 * RUN save — one Tower run. Disposable; persist only what's needed to resume.
 * The seed reconstructs the floors deterministically (see EchoesFloorGenerator).
 */
UCLASS()
class ECHOESCORE_API UEchoesRunSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(SaveGame)
	int32 SaveVersion = 1;

	UPROPERTY(SaveGame)
	int32 TowerSeed = 0;

	UPROPERTY(SaveGame)
	int32 CurrentFloor = 0;

	UPROPERTY(SaveGame)
	TArray<FName> RunBuffs;
};
