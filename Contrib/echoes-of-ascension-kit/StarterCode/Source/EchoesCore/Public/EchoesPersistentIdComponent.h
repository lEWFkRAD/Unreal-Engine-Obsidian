// Echoes of Ascension - starter scaffold.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EchoesPersistentIdComponent.generated.h"

/**
 * Gives a placed actor a stable identity that survives sessions and (later) World Partition
 * streaming. Add to any actor whose state must persist. The GUID is assigned once at author
 * time (OnRegister) and serialized with the level. See UE5_Gotchas/02.
 */
UCLASS(ClassGroup = (Echoes), meta = (BlueprintSpawnableComponent))
class ECHOESCORE_API UEchoesPersistentIdComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UEchoesPersistentIdComponent();

	UPROPERTY(SaveGame, VisibleAnywhere, BlueprintReadOnly, Category = "Echoes|Save")
	FGuid PersistentId;

	/** Assigns a new GUID if one isn't set yet. */
	UFUNCTION(BlueprintCallable, Category = "Echoes|Save")
	void EnsureId();

protected:
	virtual void OnRegister() override;
};
