---
title: "Contributed Files — Gotchas & Canonical References (Review)"
type: "review"
tags: [ue5, review, index, contribution]
---

# Contributed Files — Review Document

**Date:** 2026-06-13
**Contributor:** drafted on a local model (Qwen3.6-27B), fact-checked & corrected against Epic 5.7 docs + canonical community sources
**Files:** 7 new (1 new folder `UE5_Gotchas/` + 1 Articles entry)
**Overlaps with existing vault:** 0 — complements the tutorial folders (the *how*) and `Architecture/` (the *how to think*) with a *what breaks and why* layer.

All facts were verified before writing; several first-draft API names were wrong and were corrected (noted below) so nothing in these files is fabricated.

---

## New folder: `UE5_Gotchas/`

Architecture-style `type: concept` notes, each pairing a general UE5 pattern with a concrete mapping onto an open-world RPG stack (GAS, World Partition, a procedural co-op tower, 60 FPS with Nanite/Lumen/Niagara/Chaos).

| File | Covers |
|------|--------|
| `UE5_Gotchas/01_GAS_Replication_Gotchas.md` | Replication modes (Full/Mixed/Minimal); ASC on PlayerState vs Pawn; the Mixed-mode Owner trap; `InitAbilityActorInfo` timing; AttributeSet replication; prediction |
| `UE5_Gotchas/02_OpenWorld_Save_Architecture.md` | Persistence under World Partition; GUID identity; `UPROPERTY(SaveGame)` + proxy-archive serialization; load order; versioning; profile-vs-run saves |
| `UE5_Gotchas/03_Multiplayer_From_Day_One.md` | Why retrofitting co-op is a rewrite; authority discipline; network-aware systems; scoping co-op to the instanced Tower |
| `UE5_Gotchas/04_Procedural_Tower_Generation.md` | Deterministic seeding (`FRandomStream`); PCG for decoration not layout; sublevels over WP for bounded floors; the runtime-NavMesh gotcha; connectivity validation |
| `UE5_Gotchas/05_Performance_Budget_Reality.md` | The 16.6 ms budget; software vs hardware Lumen; Nanite foliage caveats; async loading; Niagara Effect Types; Chaos discipline |
| `UE5_Gotchas/_MOC_UE5_Gotchas.md` | Map of Content for the folder |

## New Articles entry

| File | Covers |
|------|--------|
| `Articles/ue5-canonical-references.md` | Stable authoritative external sources (Epic 5.7 docs, tranek GASDocumentation, vorixo Devtricks, GAS Companion, Cedric's Network Compendium, Tom Looman, Lyra, benui) grouped by system, each with a "why it matters" note |

## Corrections applied during review (for transparency)

- `UGameplayAbilityComponent` → `UAbilitySystemComponent` (correct class name).
- `UAbilitySystemLibrary::SetOwner(...)` (does not exist) → `AActor::SetOwner(NewController)`, with the clarification that ASC-on-PlayerState avoids the problem entirely.
- AttributeSet replication rewritten to the correct `DOREPLIFETIME_CONDITION_NOTIFY(... COND_None, REPNOTIFY_Always)` + `GAMEPLAYATTRIBUTE_REPNOTIFY` pattern (the draft had conflated effect-replication mode with per-attribute conditions).
- Save: invented `USaveGameComponent` base → plain `UActorComponent`; `SetObjectReferenceMap` (not real) removed; serialization rewritten to the canonical `FMemoryWriter`/`FMemoryReader` + `FObjectAndNameAsStringProxyArchive(Ar.ArIsSaveGame=true)` pattern.
- MP: corrected a logic slip where a `Server_` RPC was called from inside a `HasAuthority()` block (the request must originate on the client).
- Tower: `FRandomStream` init fixed (`GenerateSeed()`+`SetSeed()` was contradictory → seeded constructor).
- Perf: async-load example rewritten to the real `UAssetManager::GetStreamableManager().RequestAsyncLoad(... FStreamableDelegate ...)` API (draft used non-existent `GetAsyncLoadHandle`/`FOnAssetLoaded`); removed invented `r.Niagara.MaxParticles` cvar in favor of the actual Effect Types / Scalability mechanism.

## Suggested README addition

Under "Architecture (Added in v1.2.0)", add a row or a new section:

> `UE5_Gotchas/` (6 files) — *what breaks and why*: GAS replication, open-world save, multiplayer-from-day-one, procedural generation, performance budgets. Pattern + concrete RPG mapping.
> `Articles/ue5-canonical-references.md` — stable external references (Epic docs, tranek, vorixo, Cedric, Tom Looman, Lyra, benui).
