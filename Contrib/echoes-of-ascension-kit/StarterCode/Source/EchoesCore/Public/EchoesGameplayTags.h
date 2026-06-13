// Echoes of Ascension - starter scaffold.

#pragma once

#include "NativeGameplayTags.h"

// Native gameplay tags, resolved at startup. Reference as EchoesTags::InputTag_Attack etc.
namespace EchoesTags
{
	ECHOESCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Attack);
	ECHOESCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Ability1);
	ECHOESCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Dash);
	ECHOESCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Attack);
	ECHOESCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Dash);
	ECHOESCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Cooldown_Dash);
	ECHOESCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Data_Damage);
	ECHOESCORE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Dead);
}
