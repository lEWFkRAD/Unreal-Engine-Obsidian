---
title: "UE5 Data Tables with C++"
source: "https://www.youtube.com/watch?v=hXZR3udztWE"
video_id: "hXZR3udztWE"
type: "youtube-summary"
series: "UE5 Data Assets"
episode: 2
tags: [ue5, data-tables, datatable, ftablerowbase, c++, unreal-engine, csv, json]
---

# UE5 Data Tables with C++

**Channel:** Scripted Adventure | **Duration:** 4:36

## Content

### What Are Data Tables?

Data Tables (`UDataTable`) are spreadsheet-like data structures in Unreal Engine that store rows of structured data. They're ideal for large datasets like weapon stats, character attributes, loot tables, and experience curves.

Each Data Table is based on a `USTRUCT` that inherits from `FTableRowBase`. This inheritance is what allows the struct to be used as row data.

### Step 1: Define the Row Struct

Create a struct that inherits from `FTableRowBase`:

```cpp
// WeaponData.h
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "WeaponData.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
    Sword,
    Bow,
    Staff,
    Axe,
    Dagger
};

USTRUCT(BlueprintType)
struct FWeaponData : public FTableRowBase
{
    GENERATED_BODY()

public:
    // Display name
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    FText WeaponName;

    // Type of weapon
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    EWeaponType WeaponType = EWeaponType::Sword;

    // Base damage
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float BaseDamage = 10.0f;

    // Attack speed (attacks per second)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float AttackSpeed = 1.0f;

    // Critical hit chance (0.0 - 1.0)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float CritChance = 0.05f;

    // Range of the weapon
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float Range = 100.0f;

    // Price in the shop
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economy")
    int32 Price = 100;

    // Description for tooltip
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
    FText Description;

    // Icon for UI (use soft reference)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
    TSoftObjectPtr<UTexture2D> Icon;

    // Mesh (note: UObject references in DataTables have limitations)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
    TSoftObjectPtr<UStaticMesh> WeaponMesh;
};
```

### Step 2: Create the Data Table Asset

1. In the Content Browser, right-click
2. Select **Miscellaneous → Data Table**
3. Choose `FWeaponData` as the row structure
4. Name it (e.g., `DT_Weapons`)
5. Open it and add rows:
   - Click **Add** to add a new row
   - Set the Row Name (e.g., `IronSword`, `LongBow`)
   - Fill in all the properties

### Step 3: Read Data from a Data Table in C++

#### Option A: Direct Property Reference

```cpp
// In your header
UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
UDataTable* WeaponDataTable;
```

#### Option B: Load at Runtime via Constructor

```cpp
// In your constructor
static ConstructorHelpers::FObjectFinder<UDataTable> DataTableFinder(
    TEXT("DataTable'/Game/Data/DT_Weapons.DT_Weapons'")
);

if (DataTableFinder.Succeeded())
{
    WeaponDataTable = DataTableFinder.Object;
}
```

### Step 4: Query a Specific Row

```cpp
void AMyWeaponActor::LoadWeaponData(FName WeaponRowName)
{
    if (!WeaponDataTable) return;

    static const FString ContextString(TEXT("Weapon Data Lookup"));
    FWeaponData* Row = WeaponDataTable->FindRow<FWeaponData>(
        WeaponRowName,
        ContextString,
        true  // bWarnIfRowMissing
    );

    if (Row)
    {
        // Use the data
        WeaponName = Row->WeaponName;
        CurrentDamage = Row->BaseDamage;
        AttackSpeed = Row->AttackSpeed;

        UE_LOG(LogTemp, Log, TEXT("Loaded weapon: %s (Damage: %.1f)"),
            *Row->WeaponName.ToString(), Row->BaseDamage);

        // Load the mesh (soft reference, loads on demand)
        if (!Row->WeaponMesh.IsNull())
        {
            UStaticMesh* Mesh = Row->WeaponMesh.LoadSynchronous();
            WeaponMeshComponent->SetStaticMesh(Mesh);
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Weapon row '%s' not found!"),
            *WeaponRowName.ToString());
    }
}
```

### Step 5: Iterate Over All Rows

```cpp
void AMyWeaponActor::GetAllWeapons()
{
    if (!WeaponDataTable) return;

    TArray<FName> RowNames = WeaponDataTable->GetRowNames();

    for (const FName& RowName : RowNames)
    {
        static const FString ContextString(TEXT("Weapon Iteration"));
        FWeaponData* Row = WeaponDataTable->FindRow<FWeaponData>(
            RowName, ContextString, false
        );

        if (Row)
        {
            UE_LOG(LogTemp, Log, TEXT("Weapon: %s | Damage: %.1f | Price: %d"),
                *RowName.ToString(), Row->BaseDamage, Row->Price);
        }
    }
}
```

### Step 6: Add Rows Programmatically at Runtime

```cpp
void AMyWeaponActor::AddNewWeapon()
{
    if (!WeaponDataTable) return;

    FWeaponData NewWeapon;
    NewWeapon.WeaponName = FText::FromString("Mystic Blade");
    NewWeapon.WeaponType = EWeaponType::Sword;
    NewWeapon.BaseDamage = 50.0f;
    NewWeapon.AttackSpeed = 1.2f;
    NewWeapon.CritChance = 0.15f;
    NewWeapon.Price = 500;
    NewWeapon.Description = FText::FromString("A blade forged in ancient magic.");

    WeaponDataTable->AddRow(FName(TEXT("MysticBlade")), NewWeapon);
}
```

### Step 7: Import from CSV/JSON

**Import from CSV:**
1. Prepare your CSV file with the first column as Row Name
2. In the Data Table editor, click **Import**
3. Select your CSV file
4. UE will parse and populate rows automatically

**Import from JSON:**
```json
[
    {
        "Name": "IronSword",
        "WeaponName": "Iron Sword",
        "WeaponType": "Sword",
        "BaseDamage": 15.0,
        "AttackSpeed": 1.0,
        "CritChance": 0.05,
        "Range": 120.0,
        "Price": 100,
        "Description": "A sturdy iron sword."
    },
    {
        "Name": "LongBow",
        "WeaponName": "Long Bow",
        "WeaponType": "Bow",
        "BaseDamage": 20.0,
        "AttackSpeed": 0.6,
        "CritChance": 0.10,
        "Range": 500.0,
        "Price": 250,
        "Description": "A longbow with excellent range."
    }
]
```

### Filtering Data Table References with UPROPERTY Meta

You can filter which struct types appear when selecting a Data Table:

```cpp
UPROPERTY(EditAnywhere, meta = (RowType="/Script/MyProject.WeaponData"))
UDataTable* WeaponTableOnly;
```

### Composite Data Tables (Merging)

To avoid single-file checkout conflicts in teams, use **Composite Data Tables** to merge multiple tables:

- Split your data into themed tables (e.g., `DT_Weapons_Swords`, `DT_Weapons_Bows`)
- Create a Composite Data Table that combines them
- Useful for DLC and modular content via **Data Registries**

### Curve Data Tables

For values that scale with level or progression, use **Curve Data Tables**:

```cpp
USTRUCT(BlueprintType)
struct FDamageCurveRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    FSimpleCurve DamageCurve;  // Defines damage scaling per level
};
```

### Key Limitations

- **Cannot store UObject references directly** (meshes, textures, sounds). Use `TSoftObjectPtr` for asset references or combine with Data Assets.
- **Tabular view is read-only** — you must select a row to edit its properties vertically.
- **No inheritance** between rows — changing defaults across many rows requires manual editing.
- **Binary `.uasset` files** make version control diffs difficult (consider locking files in source control).

### Best Practices

1. **Always use `BlueprintReadWrite` or `BlueprintReadOnly`** on UPROPERTY to allow Blueprint access
2. **Use `FName` keys** for row lookups (fastest comparison)
3. **Validate data** — set `bWarnIfRowMissing = true` in `FindRow`
4. **Use soft references** (`TSoftObjectPtr`) for any asset references to avoid loading everything into memory
5. **Import from CSV/JSON** when working with large datasets or when non-programmers need to edit data
6. **Combine with Data Assets** for complex items that need both tabular data and UObject references


---

## Related

- ← Previous: [[01_Unreal_Engine_Data_Assets_EXPLAINED]]
- → Next: [[03_How_to_use_Data_Assets_in_UE5]]
- 📚 Series: [[_MOC_UE5_Data_Assets]]
