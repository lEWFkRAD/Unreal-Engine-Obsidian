// Echoes of Ascension - starter scaffold.

#include "EchoesPersistentIdComponent.h"

UEchoesPersistentIdComponent::UEchoesPersistentIdComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UEchoesPersistentIdComponent::OnRegister()
{
	Super::OnRegister();
	// Bakes a stable GUID into placed actors at author time so it serialises with the level.
	EnsureId();
}

void UEchoesPersistentIdComponent::EnsureId()
{
	if (!PersistentId.IsValid())
	{
		PersistentId = FGuid::NewGuid();
	}
}
