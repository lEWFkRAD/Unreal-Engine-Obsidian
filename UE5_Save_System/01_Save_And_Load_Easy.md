---
title: "How to Save and Load your Game In Unreal Engine 5 (Easy)"
source: "https://www.youtube.com/watch?v=14wmGdbhLOA"
video_id: "14wmGdbhLOA"
type: "youtube-summary"
series: "UE5 Save System"
episode: 1
tags: [ue5, save-system, load, blueprint, beginner]
---

# How to Save and Load your Game In Unreal Engine 5 (Easy)

**Duration:** 8:05 | **Creator:** Gorka Games | **Published:** October 26, 2022 | **Views:** 133K+

## Overview

A quick and simple tutorial on creating a save and load system in Unreal Engine 5 using the built-in SaveGame framework. This is the simplest approach to persisting game data across sessions.

## Core Concept

UE5's save system revolves around the `USaveGame` class — a special UObject subclass designed to serialize game data to disk. You create a custom SaveGame class with your variables, populate it, and save/load it using `UGameplayStatics`.

## Step-by-Step Implementation

### Step 1: Create a SaveGame Blueprint

1. Content Browser → Right-click → Blueprint Class
2. Click "All Classes" → Search for `SaveGame`
3. Select `SaveGame` as parent class
4. Name it `BP_MySaveGame`
5. Open it and add variables you want to save:
   - `PlayerName` (String)
   - `PlayerLevel` (Integer)
   - `PlayerLocation` (Vector)
   - `PlayerHealth` (Float)
   - `InventoryItems` (Array of structs)

### Step 2: Save Game Function

Create a function or use this in your GameMode/Character:

**Blueprint nodes:**
```
1. Create Save Game Object
   - Save Game Class: BP_MySaveGame
   - → Save Game Object (output)

2. Set Save Game Variables
   - Cast to BP_MySaveGame
   - Set PlayerName, PlayerLevel, PlayerLocation, etc.

3. Save Game to Slot
   - Save Game Object: (from step 2)
   - Slot Name: "SaveSlot1"
   - User Index: 0
   - → Success (Boolean)
```

**Full Blueprint flow:**
```
[Create Save Game Object] → [Cast to BP_MySaveGame] → 
[Set variables] → [Save Game to Slot "SaveSlot1"]
```

### Step 3: Load Game Function

**Blueprint nodes:**
```
1. Does Save Game Exist
   - Slot Name: "SaveSlot1"
   - User Index: 0
   - → (branch on Exists)

2. Load Game from Slot
   - Slot Name: "SaveSlot1"
   - User Index: 0
   - → Save Game Object (output)

3. Cast to BP_MySaveGame
   - Get variables and apply to game state
```

### Step 4: C++ Implementation

**SaveGame class:**
```cpp
// MySaveGame.h
UCLASS()
class UMySaveGame : public USaveGame
{
    GENERATED_BODY()
public:
    UPROPERTY(SaveGame, Category = "Save Data")
    FString PlayerName;
    
    UPROPERTY(SaveGame, Category = "Save Data")
    int32 PlayerLevel;
    
    UPROPERTY(SaveGame, Category = "Save Data")
    FVector PlayerLocation;
    
    UPROPERTY(SaveGame, Category = "Save Data")
    float PlayerHealth;
};
```

**Save function:**
```cpp
void AMyGameMode::SaveGame()
{
    UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(
        UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
    
    SaveGameInstance->PlayerName = CurrentPlayerName;
    SaveGameInstance->PlayerLevel = CurrentLevel;
    SaveGameInstance->PlayerLocation = PlayerCharacter->GetActorLocation();
    SaveGameInstance->PlayerHealth = PlayerHealth;
    
    UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("SaveSlot1"), 0);
}
```

**Load function:**
```cpp
void AMyGameMode::LoadGame()
{
    if (UGameplayStatics::DoesSaveGameExist(TEXT("SaveSlot1"), 0))
    {
        UMySaveGame* LoadedGame = Cast<UMySaveGame>(
            UGameplayStatics::LoadGameFromSlot(TEXT("SaveSlot1"), 0));
        
        if (LoadedGame)
        {
            CurrentPlayerName = LoadedGame->PlayerName;
            CurrentLevel = LoadedGame->PlayerLevel;
            PlayerCharacter->SetActorLocation(LoadedGame->PlayerLocation);
            PlayerHealth = LoadedGame->PlayerHealth;
        }
    }
}
```

## Async Save/Load (Recommended for Production)

```cpp
// Async save — avoids frame hitches
FAsyncSaveGameToSlotDelegate SavedDelegate;
SavedDelegate.BindUObject(this, &AMyGameMode::OnSaveComplete);
UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, TEXT("SaveSlot1"), 0, SavedDelegate);

// Async load
FAsyncLoadGameFromSlotDelegate LoadedDelegate;
LoadedDelegate.BindUObject(this, &AMyGameMode::OnLoadComplete);
UGameplayStatics::AsyncLoadGameFromSlot(TEXT("SaveSlot1"), 0, LoadedDelegate);
```

## Save File Location

- **Development:** `.sav` files in `Saved/SaveGames/` folder
- **Consoles:** Platform-specific file system

## Best Practices

1. Use **async** save/load for large data to avoid hitches
2. Use **structs** to organize complex save data
3. Always check `DoesSaveGameExist` before loading
4. Use descriptive slot names for multiple save files
5. Add `UPROPERTY(SaveGame)` tag to C++ variables that should serialize

## Creator Links

- [Gorka Games Channel](https://www.youtube.com/@GorkaGames)
- [Patreon](https://bit.ly/GorkaGames_Patreon)
- [Steam Game: Bromeliad](https://bit.ly/3rVlXU1)


---

## Related

- → Next: [[02_Organised_Save_System_Structs]]
- 📚 Series: [[_MOC_UE5_Save_System]]
