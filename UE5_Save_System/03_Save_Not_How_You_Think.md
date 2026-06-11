---
title: "How To Save In Unreal (It's Not How You Think!)"
source: "https://www.youtube.com/watch?v=F1jyiy-Gx-s"
video_id: "F1jyiy-Gx-s"
type: "youtube-summary"
series: "UE5 Save System"
episode: 3
tags: [ue5, save-system, beginner, persistence, game-state]
---

# How To Save In Unreal (It's Not How You Think!)

**Duration:** 7:15 | **Creator:** Digital Alchemy (John Waynick) | **Source:** YouTube

## Overview

This beginner tutorial challenges the common assumption that saving a game means saving everything. The key insight: **you don't save the world — you save the *changes* to the world.** This approach is more efficient and scalable than trying to serialize entire game states.

## The Core Philosophy

### What Most Beginners Think
"I need to save every object's position, rotation, state, inventory contents, dialogue progress, quest status..."

### The Better Approach
"Save only what the player has **changed** from the default state."

This means:
- Don't save the entire level layout (it's already defined in the level file)
- Don't save every NPC's default position
- **DO** save: which doors the player opened, which items were picked up, which enemies were defeated, player position/inventory/progress

## Implementation Strategy

### Step 1: Identify What Changes

Categorize your game state:

**Always Save:**
- Player location and rotation
- Player health/stats
- Inventory contents
- Quest progress
- Current level/area

**Save If Changed:**
- Destroyed actors (enemies killed, objects broken)
- Opened doors/chests
- Picked up items
- Triggered events
- NPC states that changed

**Never Save:**
- Static geometry
- Default NPC positions
- Pre-placed items (unless picked up)
- Level structure

### Step 2: Use Actor Tags and Interfaces

Create a `SaveGameInterface` that saveable actors implement:

```cpp
// ISaveGameInterface
UINTERFACE()
class USaveGameInterface : public UInterface { GENERATED_BODY() }

class ISaveGameInterface
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintNativeEvent)
    FSaveActorData CaptureSaveData();
    
    UFUNCTION(BlueprintNativeEvent)
    void ApplySaveData(const FSaveActorData& Data);
};
```

### Step 3: Save Actor State Delta

```cpp
// FSaveActorData struct
struct FSaveActorData
{
    FName ActorID;           // Unique identifier
    FTransform Transform;    // Position/rotation/scale
    bool bIsAlive;           // For destructible actors
    bool bIsOpen;            // For doors/chests
    TArray<uint8> CustomData; // Actor-specific data
};
```

### Step 4: Scan and Collect Changes

```cpp
void AMyGameMode::CollectSaveData()
{
    SaveData->SavedActors.Empty();
    
    // Get all actors that implement the save interface
    TArray<AActor*> SaveableActors;
    UGameplayStatics::GetAllActorsWithInterface(GetWorld(), USaveGameInterface::StaticClass(), SaveableActors);
    
    for (AActor* Actor : SaveableActors)
    {
        ISaveGameInterface* Saveable = Cast<ISaveGameInterface>(Actor);
        FSaveActorData ActorData = Saveable->Execute_CaptureSaveData(Actor);
        SaveData->SavedActors.Add(ActorData);
    }
}
```

### Step 5: Restore on Load

```cpp
void AMyGameMode::RestoreSaveData()
{
    for (const FSaveActorData& ActorData : SaveData->SavedActors)
    {
        // Find the actor by ID
        AActor* FoundActor = FindActorByID(ActorData.ActorID);
        if (FoundActor)
        {
            ISaveGameInterface* Saveable = Cast<ISaveGameInterface>(FoundActor);
            Saveable->Execute_ApplySaveData(FoundActor, ActorData);
        }
    }
}
```

### Step 6: Handle Destroyed Actors

For actors that were destroyed (enemies killed, crates broken):
- Store their IDs in a "DestroyedActors" array
- On load, check if the actor exists — if it's in the destroyed list, destroy it again
- This avoids needing to spawn actors from save data

## Blueprint Approach

For Blueprint-only projects:

1. Create `BPI_SaveGame` interface with `CaptureSaveData` and `ApplySaveData` functions
2. Implement in each saveable actor Blueprint
3. On save: `Get All Actors With Interface` → loop → collect data
4. On load: loop through saved data → find actors → apply data

## Why This Is Better

| Traditional Approach | Delta Approach |
|---------------------|----------------|
| Save entire world state | Save only changes |
| Large save files | Small save files |
| Slow to save/load | Fast save/load |
| Breaks if level changes | Resilient to updates |
| Complex serialization | Simple data collection |

## Quick Tips

1. **Give every saveable actor a unique ID** — use Actor Tags or a custom component
2. **Use interfaces** — keeps save logic decoupled from gameplay
3. **Save the "recipe" not the "meal"** — save what changed, not the result
4. **Test with level updates** — your saves should survive minor level changes
5. **Consider a SaveGameSubsystem** — centralize save/load in a Game Instance Subsystem

## Creator Info

- **John Waynick** — Unreal Authorized Instructor, founder of Learn Digital Alchemy
- [learndigitalalchemy.com](https://learndigitalalchemy.com/)


---

## Related

- ← Previous: [[02_Organised_Save_System_Structs]]
- 📚 Series: [[_MOC_UE5_Save_System]]
