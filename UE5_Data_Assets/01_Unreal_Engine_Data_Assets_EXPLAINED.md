---
title: "Unreal Engine Data Assets EXPLAINED"
source: "https://www.youtube.com/watch?v=GQyo3q31jTQ"
video_id: "GQyo3q31jTQ"
type: "youtube-summary"
series: "UE5 Data Assets"
episode: 1
tags: [ue5, data-assets, udataasset, gamedev, c++, unreal-engine]
---

# Unreal Engine Data Assets EXPLAINED

**Channel:** The Game Dev Cave | **Duration:** 11:22

## Content

### What Are Data Assets?

Data Assets (`UDataAsset`) are purpose-built data containers in Unreal Engine designed to hold configuration data for game systems. Unlike Blueprints (which can contain logic), Data Assets are purely for **storing and organizing data**.

They inherit from `UDataAsset`, which itself derives from `UObject`:

```
UObjectBase → UObjectBaseUtility → UObject → UDataAsset
```

### Why Use Data Assets?

- **Designer-Friendly:** Designers can edit values in the editor without touching code
- **No Hardcoded Values:** Expose all configuration to the editor
- **Type-Safe References:** Use `UMyDataAsset*` for clean, safe references
- **Supports UObject References:** Unlike Data Tables, Data Assets can reference other UObjects (meshes, textures, sounds, etc.)
- **Inheritance Support:** You can subclass Data Assets to create hierarchies

### Step 1: Create a Custom Data Asset Class in C++

Create a new C++ class that inherits from `UDataAsset`:

```cpp
// MyItemDataAsset.h
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MyItemDataAsset.generated.h"

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
    Common,
    Uncommon,
    Rare,
    Epic,
    Legendary
};

UCLASS(BlueprintType)
class MYPROJECT_API UMyItemDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    // Display name for the item
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Info")
    FText DisplayName;

    // Description shown in UI
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Info")
    FText Description;

    // Item icon for UI display
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Info")
    TSoftObjectPtr<UTexture2D> Icon;

    // The 3D mesh used when the item is in the world
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visual")
    TSoftObjectPtr<UStaticMesh> WorldMesh;

    // Rarity tier
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Info")
    EItemRarity Rarity = EItemRarity::Common;

    // Base price for buying/selling
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Economy")
    int32 BasePrice = 100;

    // Maximum stack size in inventory
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
    int32 MaxStackSize = 1;

    // Is this item consumable?
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties")
    bool bIsConsumable = false;

    // Sound played on pickup
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
    TSoftObjectPtr<USoundBase> PickupSound;
};
```

### Step 2: Create Data Asset Instances in the Editor

1. Compile your project
2. In the **Content Browser**, right-click
3. Select **Miscellaneous → Data Asset**
4. Choose your `UMyItemDataAsset` class
5. Name it (e.g., `DA_Sword_Iron`, `DA_Potion_Health`)
6. Fill in the properties in the Details panel

> **Important:** Create instances via "Miscellaneous > Data Asset", NOT by creating a Blueprint subclass of your Data Asset class. Blueprint subclasses add new properties, which is different from creating data instances.

### Step 3: Reference and Use Data Assets

```cpp
// In your Actor or Component header
UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
UMyItemDataAsset* ItemData;

// Or for soft loading (doesn't load until needed)
UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
TSoftObjectPtr<UMyItemDataAsset> ItemDataSoft;
```

Using the data at runtime:

```cpp
void AMyPickupActor::OnPickedUp(ACharacter* Character)
{
    if (!ItemData) return;

    // Access the stored data
    UE_LOG(LogTemp, Log, TEXT("Picked up: %s"), *ItemData->DisplayName.ToString());

    // Use soft references for lazy loading
    if (!ItemData->Icon.IsNull())
    {
        UTexture2D* LoadedIcon = ItemData->Icon.LoadSynchronous();
        // Apply to UI...
    }

    if (ItemData->PickupSound.IsValid())
    {
        UGameplayStatics::PlaySoundAtLocation(
            this,
            ItemData->PickupSound.LoadSynchronous(),
            GetActorLocation()
        );
    }
}
```

### Step 4: Bulk Editing with Property Matrix

When you have many Data Asset instances:
1. Select multiple Data Asset instances in the Content Browser
2. Right-click → **Property Matrix**
3. Edit values in a spreadsheet-like view across all selected assets
4. Supports pinning columns for easy comparison

### Advantages of Data Assets over Data Tables

| Feature | Data Asset | Data Table |
|---------|-----------|------------|
| UObject references | ✅ Yes | ❌ No |
| Subclassing/Inheritance | ✅ Yes | ❌ No |
| Bulk tabular editing | ✅ (Property Matrix) | ✅ (Native) |
| CSV/JSON import | ❌ No | ✅ Yes |
| Single asset per entry | ✅ (individual files) | ❌ (one table) |
| Public functions | ✅ Yes | ❌ No |

### Best Practices

1. **Use `TSoftObjectPtr`** for mesh/texture references to avoid loading everything at once
2. **Organize in folders** (e.g., `/Data/Items/Weapons/`, `/Data/Items/Potions/`)
3. **Use a naming convention** like `DA_` prefix for Data Assets
4. **Combine with Data Tables** when you need both structured data and UObject references (store soft references to Data Assets in Data Table rows)

### When to Choose Data Assets

- You need to reference UObjects (meshes, sounds, textures)
- You want inheritance hierarchies (base weapon → sword, bow, staff)
- You have a moderate number of entries (dozens to low hundreds)
- You want each entry to be its own distinct asset in the Content Browser


---

## Related

- → Next: [[02_UE5_Data_Tables_with_CPP]]
- 📚 Series: [[_MOC_UE5_Data_Assets]]
