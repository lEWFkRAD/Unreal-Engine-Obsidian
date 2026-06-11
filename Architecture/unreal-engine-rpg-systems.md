---
title: Unreal Engine RPG Systems
created: 2026-05-19
updated: 2026-05-19
type: concept
tags: [unreal-engine, rpg, inventory, quests, dialogue, save-system, game-systems]
composes: []
composed_by: []
topics: [unreal-engine, game-development, rpg]
workflow: developing
confidence: high
sources: [raw/articles/unreal-engine-skills]
---

# Unreal Engine RPG Systems

Architecture patterns for the core systems of a solo-developed RPG in Unreal Engine 5.

## Inventory — Composition Architecture

**Pattern:** A `UActorComponent` on the player (or any actor) that manages `TArray<FInventorySlot>`, with item definitions stored as `UPrimaryDataAsset` subclasses.

```
UInventoryComponent (on player/NPC/chest)
├── TArray<FInventorySlot> Items
├── AddItem() / RemoveItem() / SwapItems()
│
UShItemDefinition (UPrimaryDataAsset)
├── DisplayName, Icon, Description
├── TSoftObjectPtr<UStaticMesh> Mesh   ← not loaded at startup
├── FGameplayTagContainer ItemTags
└── TArray<TSubclassOf<UGameplayEffect>> UseEffects

URPGInventorySubsystem (UGameInstanceSubsystem)
└── Global item catalog, persists across levels
```

**Key rules:**
- `TSoftObjectPtr` for meshes/icons — never block loading with hard references
- `DECLARE_DYNAMIC_MULTICAST_DELEGATE` for UI binding
- Editor-time validation via `IsDataValid()` in `UPrimaryDataAsset`
- Any actor can have an inventory — it's a component

## Quest System — Data-Driven

**Pattern:** Quest definitions in `UPrimaryDataAsset` with `FGameplayTag` identifiers. A `UGameInstanceSubsystem` manager tracks active/completed quests.

```
UQuestManager (UGameInstanceSubsystem)
├── ActiveQuests / CompletedQuests
├── TrackProgress(QuestID, ObjectiveID, Delta)
└── OnQuestUpdated / OnQuestCompleted delegates
```

**Pattern:** Use `FGameplayTag` for all IDs (`Quest.MainQuest.DragonSlayer`). GAS handles reward effects.

## Dialogue System

**Pattern:** `UDialogueAsset` (UDataAsset) with `FDialogueNode` array. Conditions evaluated by `UGameplayTag` queries. Dialogue can grant quests, advance objectives, trigger cutscenes.

**Key insight:** Store all dialogue text externally in DataTables so the LLM can edit content without touching C++.

## Save/Load — Subsystem Pattern

**Pattern:** `URPGSaveSubsystem (UGameInstanceSubsystem)` that serializes to `USaveGame`. Saves GAS attributes via `GetAllAttributes()` + custom FArchive.

- Auto-save on level transition
- Manual save at rest points
- Each subsystem saves its own state

## Related

- [[unreal-engine-gameplay-ability-system]] — GAS powers item effects, rewards, status
- [[unreal-engine-cpp-foundations]] — UObject patterns for all RPG systems
- [[unreal-engine-blueprint-hybrid-workflow]] — content in BP, systems in C++
- [[unreal-engine-solo-rpg-learning-path]] — what to learn first
