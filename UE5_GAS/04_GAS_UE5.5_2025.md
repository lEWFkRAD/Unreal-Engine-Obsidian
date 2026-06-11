---
title: "Intro to Gameplay Ability System - Unreal Engine 5.5 2025"
source: "https://www.youtube.com/watch?v=APHw7NzLSzo"
video_id: "APHw7NzLSzo"
type: "youtube-summary"
series: "UE5 GAS"
episode: 4
tags: [ue5, gas, gameplay-ability-system, ue5.5, 2025, blueprints, codewithro]
---

# Intro to Gameplay Ability System - Unreal Engine 5.5 2025

**Channel:** Code With Ro | **Duration:** 28:02

## Overview

An introduction to the Gameplay Ability System (GAS) in Unreal Engine 5.5, updated for 2025. Code With Ro covers the fundamentals of GAS including setup, core components, and a working implementation.

**Related Videos from Code With Ro:**
- Intro to GAS - Gameplay Ability System in Unreal Engine 5 C++ (22:58)
- Ultimate Intro to GAS (Gameplay Ability System) In Unreal Engine 5 (53:08)
- Gameplay Ability System: Game Designer Examples at Unreal Fest Bali 2025 (51:11)
- Create a Spell with Cooldowns using GAS in Blueprints (11:37)
- Health and Damage - Top-Down Shooter UE5 Beginners Guide (11:00)

---

## What is the Gameplay Ability System?

The Gameplay Ability System (GAS) is Unreal Engine built-in framework for creating complex gameplay mechanics. It provides:

- **Abilities** - Actions characters can perform (spells, attacks, movement)
- **Attributes** - Numeric values (Health, Mana, Stamina, Damage)
- **Effects** - Modify attributes over time or instantly
- **Tags** - Hierarchical labels for state management
- **Cues** - Visual/audio feedback system

## Setting Up GAS in UE5.5

### Step 1: Enable the Plugin

1. Edit > Plugins
2. Search for Gameplay Abilities
3. Enable and restart

### Step 2: Module Dependencies

Add to your .Build.cs:
```csharp
PublicDependencyModuleNames.AddRange(new string[] {
    "GameplayAbilities",
    "GameplayTags",
    "GameplayTasks"
});
```

### Step 3: Create the Ability System Component

On your character class, create and initialize the ASC:

```cpp
// In your character header
UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
UAbilitySystemComponent* AbilitySystemComponent;

UPROPERTY()
UMyAttributeSet* AttributeSet;

// In constructor
AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
AttributeSet = CreateDefaultSubobject<UMyAttributeSet>(TEXT("AttributeSet"));
```

Implement the interface:
```cpp
class AMyCharacter : public ACharacter, public IAbilitySystemInterface
{
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
```

### Step 4: Initialize Actor Info

```cpp
void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();
    AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
```

## Core Components Deep Dive

### Gameplay Tags

Tags use a hierarchical naming convention:
```
Ability.Spell.Fireball
Ability.Spell.IceBlast
State.Dead
State.Stunned
State.Buff.Speed
```

Tags can be used for:
- Identifying abilities and states
- Blocking/activating abilities based on conditions
- Categorizing damage types
- Managing cooldowns

### Gameplay Effects (GE)

Gameplay Effects are data-driven objects that modify attributes:

| Duration Type | Description | Example |
|---------------|-------------|---------|
| Instant | Immediate, permanent | Damage, healing |
| Duration | Temporary with timer | Buff lasting 10 seconds |
| Infinite | Until manually removed | Passive stat bonus |

Effect Modifiers:
- **Add** - Adds a value to the attribute
- **Multiply** - Multiplies the attribute
- **Override** - Sets the attribute to a specific value
- **Divide** - Divides the attribute

Magnitude Types:
- **Scalable Float** - Simple value (can use curves)
- **Attribute Based** - Derived from another attribute
- **Set By Caller** - Set programmatically at runtime
- **Custom Calculation** - C++ custom logic

### Gameplay Cues

Tags prefixed with GameplayCue.* trigger visual/audio effects:
- Particles
- Sound effects
- Screen effects
- UI feedback

### Attribute Sets

Groups of related attributes:

```cpp
UCLASS()
class UMyAttributeSet : public UAttributeSet
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health)
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UMyAttributeSet, Health)

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth)
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(UMyAttributeSet, MaxHealth)
};
```

## Creating a Gameplay Ability

1. Create a new Blueprint class inheriting from GameplayAbility
2. Override ActivateAbility
3. Add ability logic (apply effects, play montages, etc.)
4. Call EndAbility when complete

## Applying Effects from Abilities

```cpp
// Create effect spec
FGameplayEffectSpecHandle Spec = MakeOutgoingGameplayEffectSpec(
    EffectClass, GetAbilityLevel());

// Apply to self or target
ApplyGameplayEffectSpecToOwner(CurrentSpecHandle, CurrentActorInfo,
    CurrentActivationInfo, Spec);
```

## Cooldowns

Abilities can have cooldowns managed by gameplay effects:
1. Create a Duration GE with the cooldown tag
2. Set the ability CooldownGameplayEffectClass
3. The system automatically blocks activation during cooldown

## Key Takeaways

1. GAS is Epics recommended system for complex gameplay mechanics
2. Its heavily data-driven - configure in Blueprints and data assets
3. Tags are the connective tissue between all GAS components
4. Effects are the primary way to modify attributes
5. Cues handle all cosmetic feedback separately from gameplay logic
6. UE5.5 brings stability improvements to GAS

## Additional Resources

- Epic GAS Documentation: https://dev.epicgames.com/documentation/en-us/unreal-engine/gameplay-ability-system-for-unreal-engine
- Code With Ro Channel: https://www.youtube.com/@CodeWithRo


---

## Related

- ← Previous: [[03_Full_Course]]
- → Next: [[05_GAS_Combat]]
- 📚 Series: [[_MOC_UE5_GAS]]
