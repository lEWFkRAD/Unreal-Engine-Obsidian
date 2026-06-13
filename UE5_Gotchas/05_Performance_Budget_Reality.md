---
title: "Performance Budget Reality (Nanite + Lumen + Niagara + Chaos at 60 FPS)"
created: 2026-06-13
updated: 2026-06-13
type: concept
tags: [unreal-engine, performance, optimization, lumen, nanite, niagara, chaos, async-loading, gotchas]
composes: []
composed_by: []
topics: [unreal-engine, game-development, rpg, optimization]
workflow: developing
confidence: high
sources: ["https://dev.epicgames.com/documentation/en-us/unreal-engine/lumen-global-illumination-and-reflections-in-unreal-engine", "https://dev.epicgames.com/documentation/en-us/unreal-engine/nanite-virtualized-geometry-in-unreal-engine", "https://tomlooman.com/"]
---

# Performance Budget Reality

A reality check on "60 FPS with Nanite, Lumen, Niagara, and Chaos." None of those are free, and an open-world RPG that wants all four at 60 FPS has to treat frame time as a budget it *spends*, not a result it hopes for.

## Overview

60 FPS = a **16.6 ms** frame budget, split across the **game thread**, **render thread**, and **GPU** — and the frame is gated by the slowest of the three. Overspend in one system and you go into debt everywhere. The single highest-leverage decision is to pick a **min-spec GPU now** and profile on it monthly, not on your dev machine.

## The 16.6 ms budget

- Assign per-system **ms caps** up front. If Lumen costs 4 ms on the GPU, the rest of the GPU frame has ~12 ms.
- Define min-spec early (e.g. an RTX 3060 / RX 6600 class card) and **profile on it regularly** — dev-machine performance lies.

## Lumen: software vs hardware is an art-direction decision

- **Software Lumen** (mesh distance fields + screen traces) is the realistic baseline for a 60 FPS mid-range target — cheaper, lower fidelity.
- **Hardware-RT Lumen** is substantially more expensive; 60 FPS open-world with HW Lumen on mid-range GPUs is aggressive and often unsustainable.
- Choose **early**: SW Lumen shapes your lighting workflow (more reliance on well-authored static lighting and proxies). Switching late is a lighting rework across the whole game.
- Lumen GI + reflections can eat several ms of GPU on their own. Isolate cost with `ProfileGPU`, `stat GPU`, and the Lumen visualization view modes (Lumen Scene / Surface Cache).

## Nanite: not free, and foliage is the caveat

- Nanite shines on **dense, opaque, static** geometry (architecture, terrain, rocks) — that's where it pays off.
- Historically weak on **small / overlapping / masked foliage**; those cases can fall back or cost more than instanced static meshes.
- UE 5.7 adds **experimental Nanite Foliage** (Assemblies + Skinning + Voxels). Promising, but experimental — validate it against traditional ISM/HISM on your target hardware before committing core foliage to it.

## Async loading: the #1 cause of open-world hitching

Hard references pull an asset's **entire dependency chain** into memory synchronously — the classic open-world hitch when you cross into a new area.

```cpp
// BAD — hard ref: the mesh (and its deps) load with the owning object
UPROPERTY(EditAnywhere) UStaticMesh* Mesh;

// GOOD — soft ref: nothing loads until you ask
UPROPERTY(EditAnywhere) TSoftObjectPtr<UStaticMesh> SoftMesh;

// Async load on demand via the StreamableManager
TSharedPtr<FStreamableHandle> Handle =
    UAssetManager::GetStreamableManager().RequestAsyncLoad(
        SoftMesh.ToSoftObjectPath(),
        FStreamableDelegate::CreateUObject(this, &AMyClass::OnMeshLoaded));
```

Use `TSoftObjectPtr` / `TSoftClassPtr` + the AssetManager for anything not needed immediately. Audit Blueprints especially — a single hard ref in a widely-used BP can drag half your content into the boot set.

## Niagara: the "priority system" is real — it's Scalability + Effect Types

The GDD's "Niagara priority system to maintain 60 FPS" is a correct instinct, and Unreal already provides the mechanism:

- **Effect Types** with **Significance Handling** — assign each system a significance so low-priority effects cull (by distance, by budget) before high-priority ones.
- **Scalability modes** per Effect Type to scale spawn rates/quality by platform.
- Cap concurrent emitters/particles per type rather than chasing a single global limit. Profile with the **Niagara Debugger** and `stat GPU`.

## Chaos: destruction discipline

- Chaos destruction is CPU/physics-heavy; "everything is destructible" does not hit 60 FPS.
- Drive activation with **Chaos Fields** / proximity so only relevant geometry simulates.
- Cap active rigid bodies; use damage thresholds and cluster LODs so distant debris is cheap.
- Reserve destruction for **key moments**, not ambient set dressing.

## Profiling discipline

- **Profile, don't guess.** `stat unit` (game vs render vs GPU split), `stat GPU`, and **Unreal Insights** for deep dives.
- Keep a **per-system ms budget table** and treat overruns as a feature-cut trigger, not a "fix later."
- Re-profile on **min-spec monthly** — performance regresses silently as content lands.

## Sample frame-budget table (illustrative, target 16.6 ms)

Per-thread, not additive across columns — the frame is gated by the worst thread:

| System | Game (ms) | Render (ms) | GPU (ms) |
|--------|:---:|:---:|:---:|
| Game logic / AI / input | 4.0 | – | – |
| Lumen (software) | – | 3.0 | 4.0 |
| Nanite geometry | – | 1.5 | 2.0 |
| Niagara | – | 1.0 | 2.0 |
| Chaos | 2.0 | 0.5 | 0.5 |
| Post-process | – | 1.0 | 3.0 |
| **Headroom** | **~10** | **~10** | **~5** |

## Verdict on "60 FPS with all of the above"

**Achievable** — with **software Lumen**, disciplined **async loading**, **Niagara/Chaos budgets**, and a **defined min-spec** profiled regularly. **Risky** if 60 FPS is assumed to come for free, or if hardware-RT Lumen is mandated on mid-range hardware. The claim isn't wrong; it's a budget that has to be actively managed from the first vertical slice.

---

- ← Previous: [[04_Procedural_Tower_Generation]]
- 📚 Series: [[_MOC_UE5_Gotchas]]
- 🔗 Related: [[unreal-engine-solo-rpg-learning-path]]
