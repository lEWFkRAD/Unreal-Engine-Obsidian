# Echoes of Ascension — System Design Map (Vertical Slice)

How the slice's systems connect, which starter file implements each, and the load-bearing decisions. This is the bridge between the *plan* (`01`, `02`), the *code* (`../StarterCode/`), and the *why* (the `UE5_Gotchas/` docs in the knowledge vault). Keep it short on purpose — design that fits on a page gets followed.

```
                         ┌─────────────────────────┐
                         │   EchoesSaveSubsystem    │  (GameInstance)
                         │  Profile save ◄─► Run    │
                         └───────────┬─────────────┘
                                     │ seed, unlocks
                  ┌──────────────────▼───────────────────┐
   New/Resume ──► │           Run / Tower flow            │
                  │  FloorGenerator(seed,floor,prevBiome) │──► FloorPlan
                  └───────┬───────────────────────┬───────┘
                          │ loads biome level     │ boss cadence
                          ▼                        ▼
                  ┌───────────────┐        ┌───────────────┐
                  │  Combat (GAS) │◄──────►│   Enemies/AI  │
                  │  PlayerState  │ damage │  ASC on pawn  │
                  │   ▸ ASC       │ via GE └───────────────┘
                  │   ▸ AttributeSet
                  │  Character (avatar)     Elite death ──► Echo drop
                  └───────┬───────┘                 │
                          │ bind                     ▼
                          └──────────────►  Shrine: appraise + bind Echo (GE modifier)
```

---

## System 1 — Abilities & Combat (GAS)

**Decision:** ASC lives on **PlayerState**, not the Character.
**Why:** survives respawn/floor transitions for free, and makes the future co-op Tower a config change instead of a rewrite. Mixed replication mode from day one.
**Starter files:** `EchoesPlayerState`, `EchoesAbilitySystemComponent`, `EchoesAttributeSet`, `EchoesCharacter`, `EchoesGameplayAbility`.
**Gotcha doc:** `UE5_Gotchas/01_GAS_Replication_Gotchas.md` — read the InitAbilityActorInfo timing section before touching `EchoesCharacter`; it's the #1 "client has no abilities" bug.
**Slice content you add:** `GE_InitStats`, `GE_Damage` (+ Execution Calc), 3 abilities, cooldown/cost GEs.

## System 2 — Save & Persistence

**Decision:** two save objects — **Profile** (permanent meta) and **Run** (disposable per-run).
**Why:** a roguelike run is throwaway; only the seed + meta-progression deserve to persist. Mixing them bloats saves and creates resume bugs.
**Starter files:** `EchoesSaveGame` (both classes), `EchoesSaveSubsystem` (async save/load), `EchoesPersistentIdComponent` (for any placed actor that must persist later).
**Gotcha doc:** `UE5_Gotchas/02_OpenWorld_Save_Architecture.md` — versioning + async-flush-on-quit.
**Slice content you add:** the Profile fields you actually track (one Renown counter, unlock list); the "Resume Run" menu logic.

## System 3 — Procedural Tower

**Decision:** **deterministic** generation from the run seed; your own room/layout logic; **PCG for decoration only**; floors are **discrete sublevels**, not World Partition.
**Why:** determinism makes runs resumable, debuggable, and co-op-safe. PCG isn't a layout engine. WP is for open worlds, not bounded floors.
**Starter files:** `EchoesFloorGenerator`, `EchoesBiomeDataAsset`.
**Gotcha doc:** `UE5_Gotchas/04_Procedural_Tower_Generation.md` — the Dynamic-NavMesh requirement and the connectivity-validation rule.
**Slice content you add:** room modules, the real `ValidateConnectivity`, the boss-floor cadence, biome level assembly.

## System 4 — Echoes (the hook)

**Decision:** an Echo is **data** — a `GameplayEffect` modifier + display info — bound to an ability via the ASC.
**Why:** build variety from few authored assets is the highest-ROI content in the whole game. Because abilities are GAS, an Echo is just "apply this modifier/grant this tag," which is cheap to author and infinitely combinable later.
**Starter files:** none yet (this is your game-specific layer) — but it sits directly on the GAS triad. Model `UEchoesEcho` as a `UPrimaryDataAsset` holding a `TSubclassOf<UGameplayEffect>` + tags.
**Slice content you add:** 4–6 Echo assets, the shrine appraise/bind flow, the UI that shows the change.

---

## Cross-cutting decisions (lock these now)

| Decision | Choice for the slice | Doc |
|---|---|---|
| ASC location | PlayerState | `01` |
| Replication mode | Mixed (players), Full (AI) | `01` |
| Lighting | **Software** Lumen | `05` |
| Min-spec GPU | **pick one before M6** (e.g. RTX 3060) | `05` |
| Open-world tech | World **Partition** (NOT World Composition) — but not in the slice | `02` |
| Multiplayer | SP ships first; authority-correct from M1 | `03` |
| References | `TSoftObjectPtr` for meshes/levels | `05` |

## What to read, in order
1. `01_VERTICAL_SLICE_SPEC.md` — what you're building and why this much.
2. This doc — how it fits together.
3. `02_MILESTONE_BACKLOG.md` — the order to build it in.
4. The matching `UE5_Gotchas/0X` doc, just before you start each system.
5. The `../StarterCode/` files for that system.
