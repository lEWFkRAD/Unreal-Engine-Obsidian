// Echoes of Ascension - starter scaffold.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EchoesSaveSubsystem.generated.h"

class UEchoesProfileSaveGame;
class UEchoesRunSaveGame;
class USaveGame;

/**
 * Owns the two save contexts — PROFILE (permanent meta) and RUN (disposable per-run) — and
 * does all I/O asynchronously so saving never hitches the frame. See UE5_Gotchas/02.
 *
 * Accessors return a cached object, creating a default one on first use so callers never
 * touch null. Call LoadProfile()/LoadRun() at startup; the cache is populated on the callback.
 */
UCLASS()
class ECHOESCORE_API UEchoesSaveSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Echoes|Save")
	UEchoesProfileSaveGame* GetProfile();

	UFUNCTION(BlueprintCallable, Category = "Echoes|Save")
	UEchoesRunSaveGame* GetRun();

	UFUNCTION(BlueprintCallable, Category = "Echoes|Save")
	void SaveProfile();

	UFUNCTION(BlueprintCallable, Category = "Echoes|Save")
	void SaveRun();

	UFUNCTION(BlueprintCallable, Category = "Echoes|Save")
	void LoadProfile();

	UFUNCTION(BlueprintCallable, Category = "Echoes|Save")
	void LoadRun(int32 TowerSeed);

	UFUNCTION(BlueprintCallable, Category = "Echoes|Save")
	bool DoesRunExist(int32 TowerSeed) const;

	UFUNCTION(BlueprintCallable, Category = "Echoes|Save")
	void DeleteRun(int32 TowerSeed);

	static const FString ProfileSlot;

private:
	static FString RunSlotForSeed(int32 Seed);

	void HandleSaveCompleted(const FString& SlotName, int32 UserIndex, bool bSuccess);
	void HandleProfileLoaded(const FString& SlotName, int32 UserIndex, USaveGame* Loaded);
	void HandleRunLoaded(const FString& SlotName, int32 UserIndex, USaveGame* Loaded);

	UPROPERTY()
	TObjectPtr<UEchoesProfileSaveGame> CachedProfile;

	UPROPERTY()
	TObjectPtr<UEchoesRunSaveGame> CachedRun;
};
