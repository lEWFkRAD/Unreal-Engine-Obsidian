// Echoes of Ascension - starter scaffold.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EchoesGameMode.generated.h"

/** Wires the Echoes default pawn + player state. Set this as the GameMode for your slice map. */
UCLASS()
class ECHOESCORE_API AEchoesGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AEchoesGameMode();
};
