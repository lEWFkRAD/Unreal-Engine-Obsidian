---
title: "Unreal Gameplay Ability System - FULL COURSE"
source: "https://www.youtube.com/watch?v=RrMQy9pGF-k"
video_id: "RrMQy9pGF-k"
type: "youtube-summary"
series: "UE5 GAS"
episode: 3
tags: [ue5, gas, gameplay-ability-system, full-course, c++, gamedev-tv, the-game-dev-cave]
---

# Unreal Gameplay Ability System - FULL COURSE

**Channel:** The Game Dev Cave | **Duration:** 2:43:57

## Overview

A comprehensive, step-by-step full course on setting up and using Unreal Engine's Gameplay Ability System (GAS). This 2.5+ hour course addresses the lack of official Epic documentation and takes learners from zero to a working GAS implementation.

**Creator's Perspective:** "Unreal's gameplay ability system, better known as GAS, is a fantastic system to create actions for your game characters. Almost any real-time combat system could benefit from using it. It's just sad that there isn't much documentation from Epic Games to make this easy to learn."

---

## Course Structure

### Part 1: Project Setup and GAS Plugin

1. Create a new UE5 C++ project
2. Enable the **Gameplay Abilities** plugin (Edit > Plugins)
3. Add module dependencies in `.Build.cs`:

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

### Part 2: Ability System Component Setup

Create a character class implementing `IAbilitySystemInterface`:

```cpp
UCLASS()
class AMyCharacter : public ACharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    AMyCharacter();
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
    UPROPERTY()
    UAbilitySystemComponent* AbilitySystemComponent;

    UPROPERTY()
    UMyAttributeSet* AttributeSet;

    virtual void BeginPlay() override;
};
```

Initialize in constructor:
```cpp
AMyCharacter::AMyCharacter()
{
    AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

    AttributeSet = CreateDefaultSubobject<UMyAttributeSet>(TEXT("AttributeSet"));
}
```

Call `InitAbilityActorInfo` in BeginPlay:
```cpp
void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();
    AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
```

### Part 3: Gameplay Tags

Gameplay Tags are hierarchical labels used throughout GAS:

```
Ability.Skill.Fireball
State.Dead
State.Buff.Speed
Damage.Type.Physical
```

Define tags in:
- **Project Settings > GameplayTags** (DataTable)
- **C++ native tags** with `UE_DEFINE_GAMEPLAY_TAG`

### Part 4: Creating Gameplay Abilities

Base ability class structure:

```cpp
UCLASS()
class UMyGameplayAbility : public UGameplayAbility
{
    GENERATED_BODY()

public:
    UMyGameplayAbility();

    UPROPERTY(EditAnywhere, Category = "Input")
    EAbilityInputID AbilityInputID;

    virtual void ActivateAbility(...) override;
    virtual void EndAbility(...) override;
};
```

Key ability lifecycle methods:
- `CanActivateAbility()` - Checks prerequisites
- `ActivateAbility()` - Main execution logic
- `EndAbility()` - Cleanup and completion

### Part 5: Gameplay Effects

Gameplay Effects modify attributes. Create them as Blueprint data assets.

**Types:**
- **Instant** - Immediate, permanent attribute change
- **Duration** - Temporary effect with a timer
- **Infinite** - Permanent until removed

**Key components:**
- **Modifiers** - Target attribute + operation (Add/Multiply/Override) + magnitude
- **Duration Policy** - How long the effect lasts
- **Granted Tags** - Tags given to target while effect is active
- **Application Requirements** - Tag conditions for application

### Part 6: Attribute Sets

Define attributes in Attribute Set classes:

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

    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    UFUNCTION()
    void OnRep_Health(const FGameplayAttributeData& OldValue);
    UFUNCTION()
    void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);
};
```

### Part 7: Applying Gameplay Effects

Apply effects from abilities or directly:

```cpp
FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(
    DamageEffectClass, GetAbilityLevel());

SpecHandle.Data.Get()->SetSetByCallerMagnitude(
    FGameplayTag::RequestGameplayTag(FName("Data.Damage")),
    DamageAmount);

ApplyGameplayEffectSpecToTarget(CurrentSpecHandle, CurrentActorInfo,
    CurrentActivationInfo, SpecHandle, TargetData);
```

### Part 8: Gameplay Cues

Handle cosmetic effects (particles, sounds):
- Tag-based system using `GameplayCue.*` prefix
- Triggered automatically by gameplay effects
- Can also be triggered manually
- Types: Static (singleton) and Actor (spawned)

### Part 9: Ability Tasks

Async operations during ability execution:

```cpp
UAbilityTask_WaitGameplayEvent* Task = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
    this, FGameplayTag::RequestGameplayTag(FName("Event.MontageComplete")));
Task->EventReceived.AddDynamic(this, &ThisClass::OnEventReceived);
Task->ReadyForActivation();
```

Common ability tasks:
- `WaitGameplayEvent` - Listen for events
- `PlayMontageAndWait` - Play animation montage
- `WaitTargetData` - Wait for targeting input
- `WaitDelay` - Timer-based delay

### Part 10: Input Binding

Bind abilities to input using the ASC:

```cpp
AbilitySystemComponent->BindAbilityActivationToInputComponent(
    InputComponent,
    FGameplayAbilityInputBinds(
        "Confirm", "Cancel",
        "EAbilityInputID",
        static_cast<int32>(EAbilityInputID::Confirm),
        static_cast<int32>(EAbilityInputID::Cancel))
);
```

---

## Key Takeaways

1. GAS is data-driven - most configuration happens in Blueprint/Data assets
2. The ASC is the central hub - every actor using GAS needs one
3. Tags are the glue - they connect abilities, effects, and cues
4. Effects modify attributes - abilities trigger effects
5. Attribute Sets define your data model - health, mana, damage, etc.
6. Ability Tasks enable async behavior - waiting for animations, events, targeting

## Additional Resources

- **Discord Community** - Available for help and support
- **Patreon** - Channel development support
- **Personalized Coaching** - Via Fiverr
- **Related Courses:**
  - Unreal Dialogue System - Full Course FREE
  - Unreal Basics Course - FULL COURSE FOR FREE


---

## Related

- ← Previous: [[02_GAS_Overview]]
- → Next: [[04_GAS_UE5.5_2025]]
- 📚 Series: [[_MOC_UE5_GAS]]
