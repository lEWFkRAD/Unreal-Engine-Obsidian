---
title: "[UE5] Learn Unreal Engine's GAS in 14.65 minutes 🤓"
source: "https://www.youtube.com/watch?v=wpAvEOZAlEs"
video_id: "wpAvEOZAlEs"
type: "youtube-summary"
series: "UE5 GAS"
episode: 2
tags: [ue5, gas, gameplay-ability-system, overview, quick-tutorial, umbral-studios]
---

# [UE5] Learn Unreal Engine's GAS in 14.65 minutes 🤓

**Channel:** Umbral Studios | **Duration:** 14:38

## Overview

A condensed, high-density tutorial covering ALL core concepts of Unreal Engine's Gameplay Ability System in under 15 minutes. The creator (Umbral Studios) developed this as a response to earlier, rougher tutorials — aiming to provide a short, effective overview of every major GAS component. The studio is developing a rogue-like tower-defense game that heavily uses GAS.

## Chapter Breakdown

1. **Introduction** — 0:00
2. **Setup** — 0:12
3. **Gameplay Abilities** — 1:49
4. **Gameplay Tags** — 2:48
5. **Gameplay Effects** — 4:30
6. **Gameplay Cues** — 7:48
7. **Gameplay Attributes** — 9:30
8. **Effect Modifier** — 11:43
9. **Attribute Set Override** — 12:44
10. **Gameplay Events** — 13:11
11. **Outro** — 14:19

---

## 1. Setup (0:12)

Enable the GAS plugin and add module dependencies:

```csharp
// [YourModule].Build.cs
PrivateDependencyModuleNames.AddRange(new string[] {
    "GameplayAbilities",
    "GameplayTags",
    "GameplayTasks"
});
```

## 2. Gameplay Abilities (1:49)

**Gameplay Abilities** are actions an actor can perform. They are the core of GAS.

Key properties of a Gameplay Ability:
- **Ability Tags** — Tags that describe this ability
- **Cancel Abilities With Tag** — Automatically cancel other abilities with matching tags
- **Block Abilities With Tag** — Prevent abilities with matching tags from activating
- **Activation Required Tags** — Actor MUST have these tags to activate
- **Activation Blocked Tags** — Actor CANNOT have these tags to activate

An ability has a lifecycle:
1. **CanActivateAbility** — Checks if conditions are met
2. **ActivateAbility** — Executes the ability logic
3. **EndAbility** — Cleans up and finishes

## 3. Gameplay Tags (2:48)

**Gameplay Tags** are a hierarchical labeling system used throughout GAS for identification and filtering.

```
Ability.Skill.Fireball
State.Dead
State.Buff.SpeedBoost
Damage.Type.Physical
```

Tags are defined in:
- **Project Settings → GameplayTags** — Define native tags
- **DataTable** — Define tags via data tables
- **C++** — `UE_DEFINE_GAMEPLAY_TAG` / `FNativeGameplayTag`

Key uses:
- Identify abilities, states, effects
- Filter and match with tag queries
- Used in ability activation requirements

## 4. Gameplay Effects (4:30)

**Gameplay Effects (GE)** modify attributes and apply state changes. They are data-only objects (no code needed for basic effects).

Three duration types:
- **Instant** — Applied immediately, modifies base value permanently
- **Duration** — Lasts for a set time, then removes
- **Infinite** — Lasts until manually removed

Properties:
- **Modifiers** — How the effect changes attribute values (Add, Multiply, Override)
- **Executions** — Custom logic via `UGameplayEffectExecutionCalculation`
- **Gameplay Cues** — Visual/audio feedback
- **Stacking** — How multiple applications of the same effect stack
- **Granted Tags** — Tags given to the target while the effect is active
- **Application Tag Requirements** — Conditions for applying

## 5. Gameplay Cues (7:48)

**Gameplay Cues** handle cosmetic effects (particles, sounds, UI feedback) that don't affect gameplay logic.

Two types:
- **GameplayCueNotify_Static** — Singleton, no instancing (simple effects)
- **GameplayCueNotify_Actor** — Spawned actor (complex, persistent effects)

They respond to events:
- **OnExecute** — One-shot effect trigger
- **OnActive** — Looping effect started
- **OnRemove** — Effect ended
- **WhileActive** — Ticked while active

Tagged with `GameplayCue.*` prefix (e.g., `GameplayCue.Damage.Fire`)

## 6. Gameplay Attributes (9:30)

**Attributes** are floating-point values representing gameplay data (Health, Mana, Damage, etc.).

Defined in **Attribute Sets** — classes that group related attributes:

```cpp
UCLASS()
class UCombatAttributeSet : public UAttributeSet
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health)
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UCombatAttributeSet, Health)

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth)
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(UCombatAttributeSet, MaxHealth)

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana)
    FGameplayAttributeData Mana;
    ATTRIBUTE_ACCESSORS(UCombatAttributeSet, Mana)

    UFUNCTION()
    void OnRep_Health(const FGameplayAttributeData& OldValue);
    UFUNCTION()
    void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);
    UFUNCTION()
    void OnRep_Mana(const FGameplayAttributeData& OldValue);
};
```

The `ATTRIBUTE_ACCESSORS` macro generates getter, setter, initter, and property getter functions.

## 7. Effect Modifier (11:43)

Effect Modifiers define HOW a Gameplay Effect changes an attribute:

| Operation | Description |
|-----------|-------------|
| Add | Adds value to current attribute |
| Multiply | Multiplies current attribute by value |
| Divide | Divides current attribute by value |
| Override | Sets attribute to the effect's value |

Modifier Magnitude types:
- **Scalable Float** — Simple value with a curve table
- **Attribute Based** — Value derived from another attribute
- **Custom Calculation Class** — C++ class with custom logic
- **Set By Caller** — Value set programmatically when applied

## 8. Attribute Set Override (12:44)

Override `PreAttributeChange` and `PostGameplayEffectExecute` to add custom logic:

```cpp
void UCombatAttributeSet::PreAttributeChange(
    const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);

    // Clamp Health between 0 and MaxHealth
    if (Attribute == GetHealthAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
    }
}

void UCombatAttributeSet::PostGameplayEffectExecute(
    const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    // Check if target died
    if (GetHealth() <= 0.0f)
    {
        // Handle death logic
    }
}
```

## 9. Gameplay Events (13:11)

**Gameplay Events** are custom events sent through the Ability System using tags and payloads.

```cpp
// Sending a gameplay event
FGameplayEventData EventData;
EventData.Instigator = InstigatorActor;
EventData.Target = TargetActor;
EventData.EventMagnitude = DamageAmount;

UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
    TargetActor,
    FGameplayTag::RequestGameplayTag(FName("Event.Damage")),
    EventData
);
```

Abilities can listen for events using the **WaitGameplayEvent** ability task.

## Additional Resources

- **Attribute Set Creation Guide:** https://dev.epicgames.com/community/learning/tutorials/zrEb/
- **Chain Lightning GAS Tutorial:** https://www.youtube.com/watch?v=2v19pmyPpuc
- **Ali Elzoheiry GAS Course (26 lessons):** https://www.youtube.com/watch?v=1QgGyndH_u4
- **GAS Tutorial Playlist:** https://www.youtube.com/watch?v=wpAvEOZAlEs&list=PLuS6-Pdt2hhYGZkME7K7ZDT2qf4vbY5c3


---

## Related

- ← Previous: [[01_The_Setup]]
- → Next: [[03_Full_Course]]
- 📚 Series: [[_MOC_UE5_GAS]]
