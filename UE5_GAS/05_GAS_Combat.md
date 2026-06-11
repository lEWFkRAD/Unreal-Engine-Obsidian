---
title: "Intro to Combat using Gameplay Ability System (GAS) in Unreal Engine 5"
source: "https://www.youtube.com/watch?v=dqJy_n44BgM"
video_id: "dqJy_n44BgM"
type: "youtube-summary"
series: "UE5 GAS"
episode: 5
tags: [ue5, gas, gameplay-ability-system, combat, damage, blueprints, ryan-laley]
---

# Intro to Combat using Gameplay Ability System (GAS) in Unreal Engine 5

**Channel:** Ryan Laley | **Duration:** 24:06

## Overview

Ryan Laley walks through implementing a combat system using the Gameplay Ability System (GAS) in Unreal Engine 5. This tutorial focuses on the practical application of GAS for melee and damage-based combat, covering how to set up abilities, apply damage effects, and handle hit detection.

**Channel Info:** Ryan Laley creates Unreal Engine tutorials covering Blueprint and C++ gameplay systems. His GAS content focuses on practical combat implementation.

---

## Combat System Architecture with GAS

A GAS-based combat system typically consists of:

1. **Melee Attack Abilities** - GameplayAbilities triggered by player input
2. **Damage Effects** - GameplayEffects that reduce Health attribute
3. **Hit Detection** - Collision traces during attack animations
4. **Attribute Sets** - Health, MaxHealth, AttackPower, etc.
5. **Gameplay Cues** - Hit VFX, sound effects, camera shake

## Step 1: Set Up the Character with GAS

Your character needs an Ability System Component:

```cpp
UCLASS()
class ACombatCharacter : public ACharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    ACombatCharacter();

    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
    UAbilitySystemComponent* AbilitySystemComponent;

    UPROPERTY()
    UCombatAttributeSet* AttributeSet;

    virtual void BeginPlay() override;
};
```

## Step 2: Define Combat Attributes

Create an attribute set for combat-related values:

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

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackPower)
    FGameplayAttributeData AttackPower;
    ATTRIBUTE_ACCESSORS(UCombatAttributeSet, AttackPower)

    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
};
```

## Step 3: Create the Melee Attack Ability

Create a GameplayAbility for melee attacks:

1. Create a new Blueprint class inheriting from GameplayAbility
2. In ActivateAbility:
   - Play attack animation montage using an AbilityTask
   - Wait for animation notify to perform hit trace
   - Apply damage effect to hit targets
   - End ability after montage completes

```cpp
void UMeleeAttackAbility::ActivateAbility(...)
{
    // Play attack montage
    UAbilityTask_PlayMontageAndWait* MontageTask =
        UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
            this, NAME_None, AttackMontage, 1.0f);

    MontageTask->OnCompleted.AddDynamic(this, &ThisClass::OnMontageCompleted);
    MontageTask->OnCancelled.AddDynamic(this, &ThisClass::OnMontageCancelled);
    MontageTask->ReadyForActivation();
}
```

## Step 4: Implement Hit Detection

During the attack animation, use a GameplayEvent or Animation Notify to trigger hit detection:

```cpp
void UMeleeAttackAbility::PerformHitTrace()
{
    AActor* AvatarActor = GetAvatarActorFromActorInfo();
    if (!AvatarActor) return;

    FVector Start = AvatarActor->GetActorLocation();
    FVector End = Start + (AvatarActor->GetActorForwardVector() * AttackRange);

    FHitResult HitResult;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(AvatarActor);

    if (GetWorld()->SweepSingleByChannel(HitResult, Start, End,
        FQuat::Identity, ECC_Pawn, FCollisionShape::MakeSphere(AttackRadius), Params))
    {
        if (AActor* HitActor = HitResult.GetActor())
        {
            ApplyDamageToTarget(HitActor);
        }
    }
}
```

## Step 5: Create and Apply Damage Effect

Create a GameplayEffect for dealing damage:

1. Create a new GameplayEffect Blueprint
2. Set Duration Policy to **Instant**
3. Add a Modifier:
   - Attribute: Health
   - Operation: **Add** (negative value for damage)
   - Magnitude: **Set By Caller** or **Attribute Based** (from AttackPower)

Apply the damage effect:
```cpp
void UMeleeAttackAbility::ApplyDamageToTarget(AActor* Target)
{
    UAbilitySystemComponent* TargetASC =
        UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
    if (!TargetASC) return;

    FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(
        DamageEffectClass, GetAbilityLevel());

    // Set damage amount via SetByCaller
    SpecHandle.Data.Get()->SetSetByCallerMagnitude(
        FGameplayTag::RequestGameplayTag(FName("Data.Damage")),
        CalculatedDamage);

    ApplyGameplayEffectSpecToTarget(
        CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo,
        SpecHandle, UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(Target));
}
```

## Step 6: Handle Death

In the Attribute Set PostGameplayEffectExecute, check for death:

```cpp
void UCombatAttributeSet::PostGameplayEffectExecute(
    const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
        SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));

        if (GetHealth() <= 0.0f)
        {
            // Broadcast death event or apply death tag
            FGameplayEventData Payload;
            Payload.Instigator = Data.EffectSpec.GetEffectContext().GetInstigator();
            Payload.Target = GetOwningActor();

            UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
                GetOwningActor(),
                FGameplayTag::RequestGameplayTag(FName("Event.Death")),
                Payload);
        }
    }
}
```

## Step 7: Add Gameplay Cues for Visual Feedback

Add GameplayCue tags to your damage effect for visual feedback:
- Hit particles
- Sound effects
- Damage numbers UI
- Camera shake on hit

## Step 8: Combo System (Optional Extension)

To implement combos:
1. Create multiple attack abilities with increasing combo index
2. Use GameplayTags to track combo state
3. Chain abilities together using input buffering
4. Reset combo after timeout or on specific conditions

---

## Key Concepts for Combat with GAS

1. **Separation of concerns** - Ability handles the attack logic, Effect handles damage numbers, Cue handles visuals
2. **Data-driven design** - Damage values, ranges, cooldowns all configured in data assets
3. **Event-driven** - Use GameplayEvents for communication between systems
4. **Tag-based state** - Use tags like State.Dead, State.Stunned instead of boolean flags

## Common Combat Patterns

| Pattern | Implementation |
|---------|---------------|
| Melee Attack | Montage + SphereTrace + DamageEffect |
| Ranged Attack | Projectile + OverlapEvent + DamageEffect |
| Area of Effect | SphereOverlap + DamageEffect to all targets |
| Block/Parry | Ability with tag requirements + damage reduction effect |
| Combo Chain | Multiple abilities with combo tags + input buffer |

## Additional Resources

- **Ryan Laley Channel:** https://www.youtube.com/@RyanLaley
- **Epic GAS Docs:** https://dev.epicgames.com/documentation/en-us/unreal-engine/gameplay-ability-system-for-unreal-engine
- **Ali Elzoheiry GAS Series:** https://www.youtube.com/watch?v=1QgGyndH_u4


---

## Related

- ← Previous: [[04_GAS_UE5.5_2025]]
- 📚 Series: [[_MOC_UE5_GAS]]
