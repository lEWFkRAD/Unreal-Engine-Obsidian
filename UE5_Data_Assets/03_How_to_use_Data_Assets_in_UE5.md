---
title: "How to use Data Assets in UE5"
source: "https://www.youtube.com/watch?v=ORye2_bkz3M"
video_id: "ORye2_bkz3M"
type: "youtube-summary"
series: "UE5 Data Assets"
episode: 3
tags: [ue5, data-assets, udataasset, primary-data-asset, gameplay, inventory, c++, blueprint]
---

# How to use Data Assets in UE5

**Channel:** GDXR | **Duration:** 17:00

## Content

### Data Assets vs Data Tables: When to Use Which

**Data Assets** are ideal when:
- You need to store complex data with UObject references (meshes, sounds, textures, particle systems)
- Each entry is unique enough to deserve its own asset file
- You want inheritance hierarchies (BaseItem → Weapon → Sword)
- You have a moderate number of entries (dozens to hundreds)

**Data Tables** are better when:
- You have large, uniform datasets (hundreds of entries with the same structure)
- You need CSV/JSON import/export
- You're storing only primitive types and structs

### Step 1: Create a UDataAsset Subclass

```cpp
// AbilityDataAsset.h
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AbilityDataAsset.generated.h"

// Enum for ability categories
UENUM(BlueprintType)
enum class EAbilityCategory : uint8
{
    Offensive,
    Defensive,
    Utility,
    Ultimate
};

// Struct for ability cost
USTRUCT(BlueprintType)
struct FAbilityCost
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float ManaCost = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float Cooldown = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 RequiredLevel = 1;
};

UCLASS(BlueprintType)
class MYPROJECT_API UAbilityDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    // Basic info
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Info")
    FText AbilityName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Info")
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Info")
    EAbilityCategory Category = EAbilityCategory::Offensive;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Info")
    TSoftObjectPtr<UTexture2D> AbilityIcon;

    // Cost and cooldown
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cost")
    FAbilityCost Cost;

    // Damage / Effect values
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect")
    float BaseDamage = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect")
    float AreaOfEffect = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect")
    float Duration = 0.0f;

    // VFX and SFX references
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "VFX")
    TSoftObjectPtr<UNiagaraSystem> CastEffect;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "VFX")
    TSoftObjectPtr<UNiagaraSystem> ImpactEffect;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
    TSoftObjectPtr<USoundBase> CastSound;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
    TSoftObjectPtr<USoundBase> ImpactSound;

    // Animation montage
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
    TSoftObjectPtr<UAnimMontage> CastMontage;

    // Child abilities (for upgrade chains)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Progression")
    TArray<UAbilityDataAsset*> UpgradedVersions;
};
```

### Step 2: Create Instances in the Content Browser

1. Right-click in Content Browser
2. **Miscellaneous → Data Asset**
3. Select `UAbilityDataAsset` as the class
4. Name it: `DA_Fireball`, `DA_IceShield`, `DA_HealingWave`
5. Configure all properties in the Details panel
6. Repeat for each ability

Folder structure example:
```
/Data/
    /Abilities/
        /Offensive/
            DA_Fireball
            DA_LightningBolt
            DA_IceShard
        /Defensive/
            DA_IceShield
            DA_StoneArmor
        /Utility/
            DA_HealingWave
            DA_Teleport
```

### Step 3: Reference Data Assets in Your Actor

```cpp
// MyCharacter.h
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
TArray<UAbilityDataAsset*> EquippedAbilities;

// Single ability reference
UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
UAbilityDataAsset* CurrentAbility;
```

### Step 4: Use Data Asset Data at Runtime

```cpp
void AMyCharacter::CastAbility(int32 AbilityIndex)
{
    if (!EquippedAbilities.IsValidIndex(AbilityIndex)) return;

    UAbilityDataAsset* Ability = EquippedAbilities[AbilityIndex];
    if (!Ability) return;

    // Check cooldown
    if (GetWorld()->GetTimeSeconds() < LastCastTime[AbilityIndex] + Ability->Cost.Cooldown)
    {
        UE_LOG(LogTemp, Warning, TEXT("Ability %s is on cooldown!"),
            *Ability->AbilityName.ToString());
        return;
    }

    // Check mana
    if (CurrentMana < Ability->Cost.ManaCost)
    {
        UE_LOG(LogTemp, Warning, TEXT("Not enough mana for %s!"),
            *Ability->AbilityName.ToString());
        return;
    }

    // Check level requirement
    if (PlayerLevel < Ability->Cost.RequiredLevel)
    {
        UE_LOG(LogTemp, Warning, TEXT("Level %d required for %s!"),
            Ability->Cost.RequiredLevel, *Ability->AbilityName.ToString());
        return;
    }

    // Consume mana
    CurrentMana -= Ability->Cost.ManaCost;

    // Play cast animation
    if (!Ability->CastMontage.IsNull())
    {
        UAnimMontage* Montage = Ability->CastMontage.LoadSynchronous();
        PlayAnimMontage(Montage);
    }

    // Spawn VFX
    if (!Ability->CastEffect.IsNull())
    {
        UNiagaraSystem* VFX = Ability->CastEffect.LoadSynchronous();
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(
            GetWorld(), VFX, GetActorLocation()
        );
    }

    // Play sound
    if (!Ability->CastSound.IsNull())
    {
        USoundBase* Sound = Ability->CastSound.LoadSynchronous();
        UGameplayStatics::PlaySoundAtLocation(this, Sound, GetActorLocation());
    }

    // Apply damage
    ApplyAbilityDamage(Ability);

    // Set cooldown
    LastCastTime[AbilityIndex] = GetWorld()->GetTimeSeconds();

    UE_LOG(LogTemp, Log, TEXT("Cast: %s (Damage: %.1f)"),
        *Ability->AbilityName.ToString(), Ability->BaseDamage);
}
```

### Step 5: Using UPrimaryDataAsset for Asset Management

For more advanced use cases, use `UPrimaryDataAsset` instead of `UDataAsset`:

```cpp
#include "Engine/DataAsset.h"

UCLASS(BlueprintType)
class MYPROJECT_API UItemDefinition : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    // Unique identifier for asset management
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Identity")
    FName ItemID;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Info")
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Info")
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Info")
    TSoftObjectPtr<UTexture2D> Icon;

    // Override to provide asset type identification
    virtual FPrimaryAssetId GetPrimaryAssetId() const override
    {
        return FPrimaryAssetId("Item", ItemID);
    }
};
```

Benefits of `UPrimaryDataAsset`:
- **Async loading** through the Asset Manager
- **Bundle support** for loading related assets together
- **Automatic discovery** of all assets of a type
- **Memory management** — load/unload on demand

### Step 6: Combining Data Tables and Data Assets

The best architecture often combines both:

```cpp
// Data Table row struct — holds references to Data Assets
USTRUCT(BlueprintType)
struct FItemTableRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName ItemID;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FText ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 BasePrice;

    // Link to the Data Asset for complex data
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSoftObjectPtr<UItemDefinition> ItemDefinition;
};
```

**Usage pattern:**
- Data Table (`DT_Items`) holds structured metadata (name, price, category)
- Data Asset (`DA_Sword_Epic`) holds complex data (meshes, VFX, sounds, behavior)
- The Data Table row references the Data Asset via `TSoftObjectPtr`

### Step 7: Using Property Matrix for Bulk Editing

When you have many Data Asset instances:
1. Select multiple Data Asset instances in Content Browser (Ctrl+click or box select)
2. Right-click → **Property Matrix**
3. View all properties in a spreadsheet-like grid
4. Pin columns you frequently edit
5. Edit values across all selected assets simultaneously

### Step 8: Using Data Assets with Blueprints

Data Assets work seamlessly with Blueprints:

```blueprint
// In a Blueprint:
1. Add a variable of type "Ability Data Asset" (Object Reference)
2. Set it to your DA_Fireball asset
3. Access properties: Get Ability Name, Get Base Damage, etc.
4. Use soft references with "Async Load Asset" for large assets
```

### Architecture Patterns

#### Pattern 1: Ability System
```
DA_Fireball (UAbilityDataAsset)
├── CastEffect → NS_FireCast (Niagara)
├── ImpactEffect → NS_FireExplosion
├── CastSound → SFX_FireCast
├── CastMontage → AM_FireCast
└── UpgradedVersions → [DA_Fireball_T2, DA_Fireball_T3]
```

#### Pattern 2: Item System with Table + Asset
```
DT_Items (DataTable)
├── Row: "IronSword" → references DA_Sword_Iron
├── Row: "SteelSword" → references DA_Sword_Steel
└── Row: "MagicSword" → references DA_Sword_Magic

DA_Sword_Iron (UDataAsset)
├── WorldMesh → SM_Sword_Iron
├── Icon → T_Sword_Iron
├── SwingSound → SFX_SwordSwing
└── HitEffect → NS_SwordHit
```

#### Pattern 3: Character Class Definitions
```
DA_Warrior (UDataAsset)
├── BaseStats → {HP: 200, Mana: 50, Armor: 30}
├── StartingAbilities → [DA_Slash, DA_ShieldBlock]
├── ClassMesh → SK_Warrior
└── ClassPortrait → T_WarriorPortrait

DA_Mage (UDataAsset)
├── BaseStats → {HP: 100, Mana: 200, Armor: 10}
├── StartingAbilities → [DA_Fireball, DA_FrostNova]
├── ClassMesh → SK_Mage
└── ClassPortrait → T_MagePortrait
```

### Common Pitfalls

1. **Don't create Blueprint subclasses** of your Data Asset for instances — use "Miscellaneous > Data Asset" instead
2. **Always use soft references** (`TSoftObjectPtr`) for meshes and textures to avoid loading everything into memory at startup
3. **Data Assets are binary** — they don't diff well in version control. Consider locking or using asset merging tools
4. **No automatic discovery** — to find all Data Assets of a type at runtime, use the Asset Registry or maintain a manual list/Data Table
5. **Instanced properties** (`UPROPERTY(Instanced)`) on Data Assets are serialized with the asset and allow embedded UObject sub-objects for modular data


---

## Related

- ← Previous: [[02_UE5_Data_Tables_with_CPP]]
- 📚 Series: [[_MOC_UE5_Data_Assets]]
