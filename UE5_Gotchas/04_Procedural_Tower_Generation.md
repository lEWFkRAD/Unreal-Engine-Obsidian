---
title: "Procedural Tower / Roguelike Floor Generation"
created: 2026-06-13
updated: 2026-06-13
type: concept
tags: [unreal-engine, pcg, procedural-generation, roguelike, determinism, navmesh, gotchas]
composes: []
composed_by: []
topics: [unreal-engine, game-development, rpg, procedural-generation]
workflow: developing
confidence: high
sources: ["https://dev.epicgames.com/documentation/en-us/unreal-engine/procedural-content-generation-overview", "https://forums.unrealengine.com/t/unreal-engine-5-7-released/2673913"]
---

# Procedural Tower / Roguelike Floor Generation

How to build a 100-floor procedural dungeon (the Tower of Ascension) without it becoming non-reproducible, un-navigable, or soft-locked. UE 5.7's PCG framework is now production-ready — but knowing *what not to use it for* matters more than knowing how to use it.

## Overview

A roguelike floor has two layers: **layout** (rooms, connectivity, the guaranteed path) and **decoration** (props, foliage, clutter). PCG is excellent at the second and a poor fit for the first. The whole system hangs on one property: **determinism** — a seed must reproduce a floor exactly.

## Determinism & seeding (non-negotiable)

- **One source of truth:** thread a single `FRandomStream`, seeded from the run's master seed, through *all* generation. Every choice draws from it in a fixed order.
- **Never `FMath::Rand`** or other global RNG — non-deterministic across runs and threads, and it breaks reproducibility.
- A given seed must reproduce the floor **exactly**. This is required for:
  - **Resumable runs** — reload from the seed + floor index (see [[02_OpenWorld_Save_Architecture]]).
  - **Debugging** — reproduce a bug by replaying its seed.
  - **Future co-op** — every client must generate the identical floor from the shared seed (see [[03_Multiplayer_From_Day_One]]).

```cpp
// Seed once per floor; order of draws is part of the contract
FRandomStream GenStream(FloorSeed);          // deterministic from the seed
int32 RoomCount = GenStream.RandRange(6, 10);
FBiomeType Biome = PickWeightedRandom(Candidates, GenStream);
```

## PCG strategy: layout vs decoration

- **Layout → your own deterministic algorithm.** Room graph / BSP / a hand-rolled connectivity pass gives you control over reachability, boss placement, and the guaranteed path. PCG graphs are awkward for "rooms must connect and the exit must be reachable."
- **Decoration → UE 5.7 PCG.** Generate the layout first, then feed room bounds / spline points into PCG graphs for set-dressing, props, and foliage scatter. PCG in 5.7 is production-ready and roughly 2× faster than prior versions, with a dedicated PCG editor mode.

## Runtime vs build-time generation

- PCG **can** run at runtime, but runtime generation is heavier than build-time. For a roguelike, generate the floor **once on floor-entry**, not continuously.
- Bake/pre-compute what can be static; reserve runtime PCG for the variation that actually needs the seed.

## Don't use World Partition for bounded floors

```text
[Enter Floor N]
   -> Load floor as a discrete sublevel / instanced level
   -> Generate layout (your deterministic algorithm)
   -> Build NavMesh (runtime/dynamic)
   -> Run PCG decoration pass
   -> ...play...
[Exit Floor N] -> unload the sublevel, free memory
```

WP exists to stream a large continuous world. A bounded tower floor is the opposite problem — load it as a discrete level and unload it on exit. Reaching for WP here is over-engineering.

## Navigation gotcha (enemies stand still)

AI will not path on freshly generated geometry unless the navigation system regenerates at runtime:

- **Project Settings → Navigation Mesh → Runtime Generation = `Dynamic`.**
- Ensure the NavMesh rebuild completes **after** layout generation and before enemies activate (it rebuilds async; gate enemy spawn on it).
- Symptom of getting this wrong: a perfectly generated floor where every enemy is frozen because there's no nav data under them.

## Biome constraint: no consecutive repeats

A weighted bag that excludes the previous pick:

```cpp
TArray<FBiomeType> Candidates = AllBiomes;
Candidates.Remove(PreviousFloorBiome);            // forbid immediate repeat
FBiomeType Next = PickWeightedRandom(Candidates, GenStream);
```

## Aetheric Champions: adaptive difficulty

- Track player metrics (damage types used, preferred range, mobility) in a stats component.
- Weight enemy/modifier selection from a `UDataAsset`/`DataTable` by those metrics — e.g. heavy fire use → bias toward fire-resistant champions.
- Keep the weighting deterministic from the seed + the recorded metrics, so a run stays reproducible.

## Validation & fallback (never ship a soft-lock)

```cpp
if (!CheckPathConnectivity(Entrance, Exit))   // entrance must reach exit
{
    GenerateFallbackLayout(FloorSeed);        // deterministic, pre-validated
}
```

Always verify a guaranteed entrance→exit path before exposing the floor. If a generation pass fails connectivity, fall back to a known-good deterministic layout rather than risking an unbeatable floor.

## Echoes of Ascension mapping

- **13 biome types**, **100 floors**, **no consecutive biome repeats** — the weighted-bag-minus-last rule above.
- **Seven Legendary Challengers** → fixed boss floors. Place them at deterministic positions in the sequence (from the seed) so progression milestones are stable while the biomes between them vary.

```text
Floors 1..N    Biome A (seeded)
Floor  ~15     Legendary Challenger 1  (fixed boss floor)
Floors ..M     Biome B (seeded, != A)
...
Floor  100     Final encounter
```

---

- ← Previous: [[03_Multiplayer_From_Day_One]]
- → Next: [[05_Performance_Budget_Reality]]
- 📚 Series: [[_MOC_UE5_Gotchas]]
