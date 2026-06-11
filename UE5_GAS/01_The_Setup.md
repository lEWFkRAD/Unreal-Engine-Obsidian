---
title: "Unreal Engine's Gameplay Ability System — Part 1: The Setup — Tutorial"
source: "https://www.youtube.com/watch?v=1QgGyndH_u4"
video_id: "1QgGyndH_u4"
type: "youtube-summary"
series: "UE5 GAS"
episode: 1
tags: [ue5, gas, gameplay-ability-system, c++, setup, tutorial, ali-elzoheiry]
---

# Unreal Engine's Gameplay Ability System — Part 1: The Setup — Tutorial

**Channel:** Ali Elzoheiry | **Duration:** 21:30

## Overview

This is Part 1 of Ali Elzoheiry's comprehensive GAS tutorial series. Ali is an Unreal Authorized Instructor, Game Developer, Software Engineer & Studio Owner. This video covers the foundational setup needed to integrate the Gameplay Ability System into your Unreal Engine project.

**Series Description:** This GAS tutorial series covers everything you need to master the Gameplay Ability System: Abilities, attributes, effects, gameplay tags & cues.

## Prerequisites

- Unreal Engine 5.x installed
- C++ project (not Blueprint-only)
- Basic understanding of Unreal Engine classes and inheritance

## Step 1: Enable the Gameplay Abilities Plugin

1. Open your UE5 project
2. Go to **Edit → Plugins**
3. Search for **"Gameplay Abilities"**
4. Enable the plugin
5. Restart the editor when prompted

## Step 2: Add Module Dependencies

In your project's `[ModuleName].Build.cs` file, add the required module dependencies:

```csharp
PublicDependencyModuleNames.AddRange(new string[] {
    "Core",
    "CoreUObject",
    "Engine",
    "InputCore",
    "GameplayAbilities",
    "GameplayTags",
    "GameplayTasks"
});
```

These three modules are essential:
- **GameplayAbilities** — Core GAS functionality
- **GameplayTags** — Tag system used throughout GAS
- **GameplayTasks** — Async tasks for abilities

## Step 3: Create a Base Character with Ability System Component

Create a C++ character class that implements the `IAbilitySystemInterface`:

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "BaseCharacter.generated.h"

UCLASS()
class YOURPROJECT_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    ABaseCharacter();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
    UAbilitySystemComponent* AbilitySystemComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
    UAttributeSet* AttributeSet;

    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
    virtual void BeginPlay() override;
};
```

## Step 4: Initialize the Ability System Component

In the constructor, create the ASC as a default subobject:

```cpp
ABaseCharacter::ABaseCharacter()
{
    AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

    AttributeSet = CreateDefaultSubobject<UAttributeSet>(TEXT("AttributeSet"));
}
```

## Step 5: Set Up Ability Actor Info

In `BeginPlay()` or `PostInitializeComponents()`, call `InitAbilityActorInfo` to link the ASC to the owner and avatar actors:

```cpp
void ABaseCharacter::BeginPlay()
{
    Super::BeginPlay();
    if (AbilitySystemComponent)
    {
        AbilitySystemComponent->InitAbilityActorInfo(this, this);
    }
}
```

## Step 6: Create Player and Enemy Character Classes

Inherit from the base character to create specialized classes:

```cpp
// PlayerCharacter.h
UCLASS()
class APlayerCharacter : public ABaseCharacter
{
    GENERATED_BODY()
public:
    APlayerCharacter();
    // Add input component, camera, etc.
};

// EnemyCharacter.h
UCLASS()
class AEnemyCharacter : public ABaseCharacter
{
    GENERATED_BODY()
public:
    AEnemyCharacter();
    // Add AI-specific functionality
};
```

## Key Concepts Covered

- **Ability System Component (ASC):** The central component that manages all GAS functionality — granting abilities, applying effects, managing attributes
- **IAbilitySystemInterface:** Interface that provides `GetAbilitySystemComponent()` for any actor that owns an ASC
- **Owner vs Avatar Actor:** The ASC uses two actor references — the Owner (persistent state holder) and Avatar (the physical representation in the world)
- **Replication Mode:** `Minimal` for enemies/AI, `Mixed` for player characters (controls how GAS data replicates in multiplayer)

## Replication Modes Explained

| Mode | Use Case | Description |
|------|----------|-------------|
| Full | Single Player | All GAS data replicates to all clients |
| Mixed | Player Characters | Gameplay effects replicate to owning client, tags/attributes replicate to all |
| Minimal | AI/Enemies | Only tags and gameplay cues replicate to all; owner gets full data |

## Next Steps

- **Part 2: Dash Ability** — Creating your first gameplay ability
- **Part 3: Attributes & Effects** — Setting up attribute sets and gameplay effects
- **Part 4: UI/Widgets** — Connecting GAS data to the UI

## Additional Resources

- **Project Files:** Available on Patreon (https://www.patreon.com/Alizoh)
- **Discord Community:** https://discord.gg/AEnM4wvYzN
- **Epic's GAS Docs:** https://dev.epicgames.com/documentation/en-us/unreal-engine/gameplay-ability-system-for-unreal-engine


---

## Related

- → Next: [[02_GAS_Overview]]
- 📚 Series: [[_MOC_UE5_GAS]]
