---
title: "How To Create An Organised Save System In UE5.1 with structs"
source: "https://www.youtube.com/watch?v=a37tLeTZugc"
video_id: "a37tLeTZugc"
type: "youtube-summary"
series: "UE5 Save System"
episode: 2
tags: [ue5, save-system, structs, game-instance, event-dispatchers, umg]
---

# How To Create An Organised Save System In UE5.1 with Structs

**Duration:** 44:59 | **Creator:** GDXR | **Source:** YouTube

## Overview

This tutorial covers building an **organized, scalable save system** in UE5.1 using Structs, UMG (UI), Casting, Event Dispatchers, and Game Instance. Unlike basic save tutorials, this approach structures data cleanly for complex games with multiple systems.

## Why Organized Saves Matter

A basic save system works for simple games, but as your game grows you need:
- **Structs** to group related data (player stats, inventory, quest progress)
- **Game Instance** to persist data between level loads
- **Event Dispatchers** to notify UI and systems when save/load happens
- **Multiple save slots** with clean data management

## Architecture Overview

```
Game Instance (persists between levels)
    └── Save Game Object
         ├── FPlayerData (struct)
         ├── FInventoryData (struct)
         ├── FQuestData (struct)
         └── FSettingsData (struct)
```

## Step-by-Step Implementation

### Step 1: Create Data Structs

Create Struct assets in the Content Browser:

**Struct: S_PlayerData**
```
- PlayerName (String)
- PlayerLevel (Integer)
- CurrentXP (Float)
- PlayerLocation (Vector)
- PlayerRotation (Rotator)
- CurrentHealth (Float)
- MaxHealth (Float)
```

**Struct: S_InventoryData**
```
- Items (Array of FItemStruct)
  - ItemID (Name)
  - ItemName (String)
  - Quantity (Integer)
  - SlotIndex (Integer)
- Gold (Integer)
- EquippedWeaponID (Name)
```

**Struct: S_QuestData**
```
- ActiveQuests (Array of FQuestStruct)
  - QuestID (Name)
  - QuestState (Enum: NotStarted, Active, Complete)
  - Objectives (Array of FObjectiveStruct)
- CompletedQuests (Array of Name)
```

**Struct: S_SettingsData**
```
- MasterVolume (Float)
- MusicVolume (Float)
- SFXVolume (Float)
- MouseSensitivity (Float)
- GraphicsQuality (Integer)
- bInvertYAxis (Boolean)
```

### Step 2: Create SaveGame Blueprint

1. Create `BP_MasterSaveGame` (parent: SaveGame)
2. Add struct variables:
   - `PlayerData` (S_PlayerData)
   - `InventoryData` (S_InventoryData)
   - `QuestData` (S_QuestData)
   - `SettingsData` (S_SettingsData)
   - `SaveTimestamp` (DateTime)
   - `SaveSlotName` (String)

### Step 3: Game Instance Setup

Create `GI_SaveManager` (parent: GameInstance):

```cpp
// Game Instance persists between level loads
// Store the current save data here

UPROPERTY()
UMySaveGame* CurrentSaveData;

// Save function
UFUNCTION(BlueprintCallable)
void SaveToSlot(FString SlotName);

// Load function
UFUNCTION(BlueprintCallable)
bool LoadFromSlot(FString SlotName);

// Event Dispatcher for UI updates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSaveComplete);
UPROPERTY(BlueprintAssignable)
FOnSaveComplete OnSaveComplete;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLoadComplete);
UPROPERTY(BlueprintAssignable)
FOnLoadComplete OnLoadComplete;
```

### Step 4: Save/Load with Game Instance

```cpp
void UGI_SaveManager::SaveToSlot(FString SlotName)
{
    UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(
        UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
    
    // Populate from current game state
    SaveGameInstance->PlayerData = GatherPlayerData();
    SaveGameInstance->InventoryData = GatherInventoryData();
    SaveGameInstance->QuestData = GatherQuestData();
    SaveGameInstance->SettingsData = GatherSettingsData();
    SaveGameInstance->SaveTimestamp = FDateTime::Now();
    SaveGameInstance->SaveSlotName = SlotName;
    
    // Save to disk
    UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, 0);
    
    // Store in memory
    CurrentSaveData = SaveGameInstance;
    
    // Notify listeners
    OnSaveComplete.Broadcast();
}

bool UGI_SaveManager::LoadFromSlot(FString SlotName)
{
    if (!UGameplayStatics::DoesSaveGameExist(SlotName, 0))
        return false;
    
    UMySaveGame* LoadedGame = Cast<UMySaveGame>(
        UGameplayStatics::LoadGameFromSlot(SlotName, 0));
    
    if (!LoadedGame) return false;
    
    CurrentSaveData = LoadedGame;
    
    // Apply data to game systems
    ApplyPlayerData(LoadedGame->PlayerData);
    ApplyInventoryData(LoadedGame->InventoryData);
    ApplyQuestData(LoadedGame->QuestData);
    ApplySettingsData(LoadedGame->SettingsData);
    
    OnLoadComplete.Broadcast();
    return true;
}
```

### Step 5: UMG Save Slot UI

Create `WBP_SaveSlotMenu`:
- List of save slot buttons
- Each slot shows: timestamp, player level, location
- Save/Load/Delete buttons per slot

Bind to Game Instance dispatchers:
```
Event Construct →
  Get Game Instance (cast to GI_SaveManager)
  Bind Event to OnSaveComplete → Refresh slot list
  Bind Event to OnLoadComplete → Close menu
```

### Step 6: Using Cast to Access Save Data

From any Blueprint:
```
Get Game Instance → Cast to GI_SaveManager → Get CurrentSaveData
  → Cast to BP_MasterSaveGame
  → Get PlayerData / InventoryData / QuestData
```

## Blueprint-Only Approach (No C++)

For pure Blueprint implementation:
1. Create BP structs (Data Tables or Blueprint Structs)
2. Create BP_MasterSaveGame with struct variables
3. Use Game Instance Blueprint for save/load logic
4. Use Event Dispatchers for UI communication
5. Call `Save Game to Slot` / `Load Game from Slot` from Game Instance

## Tips for Complex Games

1. **Separate concerns** — player data, world state, and settings in different structs
2. **Use Event Dispatchers** — don't directly reference UI from gameplay code
3. **Version your saves** — add a `SaveVersion` integer for migration support
4. **Auto-save** — use a Timer or level transition triggers
5. **Save thumbnails** — capture a screenshot and store as texture in save data

## Related Resources

- [GDXR Discord](https://discord.gg/xw65fg7)
- [Event Dispatchers Tutorial](https://www.youtube.com/watch?v=r-Qm5dYQFEA)


---

## Related

- ← Previous: [[01_Save_And_Load_Easy]]
- → Next: [[03_Save_Not_How_You_Think]]
- 📚 Series: [[_MOC_UE5_Save_System]]
