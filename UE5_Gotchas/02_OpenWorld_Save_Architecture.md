---
title: "Open-World & Roguelike Save Architecture"
created: 2026-06-13
updated: 2026-06-13
type: concept
tags: [unreal-engine, save-system, world-partition, persistence, roguelike, c++, gotchas]
composes: []
composed_by: []
topics: [unreal-engine, game-development, rpg, save-system]
workflow: developing
confidence: high
sources: ["https://tomlooman.com/unreal-engine-cpp-save-system/", "https://dev.epicgames.com/documentation/en-us/unreal-engine/world-partition-in-unreal-engine", "https://xbloom.io/2025/10/24/unreals-world-partition-internals/"]
---

# Open-World & Roguelike Save Architecture

The naive "one SaveGame object that holds everything" pattern works in a single small level and falls apart the moment you add World Partition (WP) or a procedural roguelike. This is the architecture that survives both.

## Overview

WP changes the rules: actors **stream in and out** by distance, so at save or load time an actor you care about may not exist in the world. Persistence therefore can't be "store a pointer to the actor and restore it." It has to be: stable **identity** + serialized **state** + deterministic **reconstruction** on load.

## Identity: stable IDs, not instance pointers

- **Placed actors** (authored in the level) that must persist need a stable identifier — an `FGuid` (or stable `FName`) stored on a small custom save component (a plain `UActorComponent`, not an engine type). Generate the GUID at design time so it survives edits/re-cooks.
- **Spawned actors** (runtime: dropped loot, summoned enemies) can't rely on placement. Record a **spawn record** (class via `FSoftClassPath`, transform, seed, saved state) so the loader can re-spawn and re-hydrate them.

```cpp
// Custom component — gives a placed actor a save identity
UCLASS()
class UPersistentIdComponent : public UActorComponent
{
    GENERATED_BODY()
public:
    UPROPERTY(SaveGame, VisibleAnywhere)
    FGuid PersistentId;          // assigned once, stable across sessions
};
```

## Serialization: only `SaveGame`-flagged properties

The canonical pattern (Tom Looman's save system) serializes each actor's `UPROPERTY(SaveGame)` fields into a byte buffer using `FObjectAndNameAsStringProxyArchive`, which writes object references as string paths (so they survive across sessions):

```cpp
// SAVE — capture an actor's SaveGame properties into bytes
TArray<uint8> Bytes;
FMemoryWriter MemWriter(Bytes, /*bIsPersistent=*/true);
FObjectAndNameAsStringProxyArchive Ar(MemWriter, /*bLoadIfFindFails=*/true);
Ar.ArIsSaveGame = true;          // ONLY UPROPERTY(SaveGame) fields are touched
Actor->Serialize(Ar);            // store Bytes keyed by PersistentId

// LOAD — restore from bytes
FMemoryReader MemReader(SavedBytes, true);
FObjectAndNameAsStringProxyArchive Ar(MemReader, true);
Ar.ArIsSaveGame = true;
Actor->Serialize(Ar);            // re-applies saved values
```

Tag exactly the fields you want persisted with `UPROPERTY(SaveGame)`; everything else is ignored automatically.

## Load order with World Partition

You want world/actor state restored **before** `BeginPlay` runs on streamed actors, so nothing pops or runs with stale state:

1. Persistent level loads.
2. Deserialize the saved world state into a **persistence subsystem** (a `UGameInstanceSubsystem` or world subsystem) — a map of `PersistentId → bytes`.
3. As WP streams an actor in, the actor registers with that subsystem in `BeginPlay` and, if a record exists for its `PersistentId`, applies it immediately (before its own gameplay logic runs).

Epic ships a **Level Streaming Persistence** plugin that automates much of this for WP — evaluate it before hand-rolling. (It's underused but exactly on point.)

## Versioning is mandatory

Ship without it and the first content patch bricks every save.

- Store an `int32 SaveVersion` at the head of the file.
- On load, if `Loaded < Current`, run migration (add new fields, transform old layouts).
- If migration can't reconcile, fail gracefully (back up the old file, start fresh) — never crash on an old save.
- For structural changes to serialized types, UE's `FArchive` custom versions (`UsingCustomVersion` / `CustomVer`) handle it, but a plain int covers most gameplay data.

## Profile save vs Run save (the roguelike split)

A roguelike needs **two** save contexts. Mixing them bloats files and creates logic bugs:

| Save | Scope | Contents | When |
|------|-------|----------|------|
| **Profile** (persistent) | meta-progression | Aetheric Renown, unlocked classes/skills, Echoes inventory, settings | on exit, on milestone |
| **Run** (transient) | one tower run | tower **seed**, current floor index, run-only buffs/temp inventory | on floor clear, on quit-if-resumable |

A run is disposable — persist only the **seed** (+ floor index and minimal run state) if you allow "Resume Run," and discard it otherwise. The seed reconstructs the rest deterministically (see [[04_Procedural_Tower_Generation]]).

## Async save, no frame hitch

- Use `UGameplayStatics::AsyncSaveGameToSlot` so file I/O runs off the game thread.
- Don't autosave every frame — throttle to discrete events (floor clear, death, level exit).
- On shutdown, an in-flight async save may not finish: fall back to a synchronous `SaveGameToSlot` on quit, or block on the async completion callback.
- Compress large buffers (`FArchiveSaveCompressedProxy`) if save size grows.

## Common pitfalls

- **Saving hard object refs** (`AActor*`/`UObject*`) directly — invalid next session. Save `FGuid` / `FSoftObjectPath` instead.
- **Saving only the actor transform** but not component sub-state (current health, inventory contents).
- **Assuming the actor exists on load** — under WP it may not be streamed in yet; restore via the subsystem-on-`BeginPlay` hook, not a one-shot pass over `GetAllActors`.
- **No flush on quit** — async save silently dropped.

## Echoes of Ascension mapping

- **Profile** is the source of truth for meta-progression: Renown across the 8 factions, appraised Echoes, unlocks.
- **Run** holds the tower seed + floor index. On launch: load Profile; if a Run save exists, offer "Resume Run"; otherwise roll a fresh seed.

---

- ← Previous: [[01_GAS_Replication_Gotchas]]
- → Next: [[03_Multiplayer_From_Day_One]]
- 📚 Series: [[_MOC_UE5_Gotchas]]
- 🔗 Related: [[unreal-engine-rpg-systems]]
