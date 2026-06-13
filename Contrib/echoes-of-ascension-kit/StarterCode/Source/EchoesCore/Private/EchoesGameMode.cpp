// Echoes of Ascension - starter scaffold.

#include "EchoesGameMode.h"
#include "EchoesCharacter.h"
#include "EchoesPlayerState.h"

AEchoesGameMode::AEchoesGameMode()
{
	DefaultPawnClass = AEchoesCharacter::StaticClass();
	PlayerStateClass = AEchoesPlayerState::StaticClass();
	// PlayerControllerClass / HUDClass / GameStateClass: set here if you subclass them.
}
