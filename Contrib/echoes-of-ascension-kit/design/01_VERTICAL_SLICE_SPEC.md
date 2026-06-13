# Echoes of Ascension — Vertical Slice Spec (v1 "Proof of Fun")

**Purpose of this document:** define the *smallest* thing you can build that proves the core game is fun. Everything in the GDD is downstream of one bet — *that ascending the procedural Tower with GAS combat and Echo-driven builds is fun.* If that's true, the rest is expansion. If it's not, no amount of open world saves it. So we prove that bet first, cheaply.

> **The one question this slice answers:**
> *"Is one biome of the Tower fun enough to play through twice — with a different Echo build the second time?"*
> If yes → greenlight expansion (more biomes are cheap once the loop works). If no → fix the loop before spending a single hour on the open world.

---

## In scope (build exactly this)

### 1. One playable character with GAS
- ASC-on-PlayerState (so co-op and respawn are free later — see `UE5_Gotchas/01`).
- Core attributes: Health, MaxHealth, Aether (resource), MaxAether, AttackPower.
- **One elemental affinity** (pick Flame) with **3 abilities**: a basic attack, one resource-spender (e.g. Flame Lance), one utility (e.g. Dash). That's enough to feel a kit.
- Damage flows through GameplayEffects, never Tick.

### 2. A combat encounter
- **2 enemy types**: a melee minion and one **Elite** (the Echo dropper).
- Server-authoritative damage + death. Player death → return to hub (run ends).
- No fancy AI — Behavior Tree with chase + attack is plenty.

### 3. The procedural Tower — ONE biome, 3–5 floors
- Deterministic generation from a run seed (`UE5_Gotchas/04`, starter `EchoesFloorGenerator`).
- 3–5 floors built from a small kit of hand-made room modules (PCG for decoration only).
- Floor N = a **boss floor** (one of the Seven Challengers, scripted not procedural).
- Runtime NavMesh = Dynamic (or enemies stand still — the classic trap).

### 4. The Echoes loop — the actual hook
- Elite dies → drops **one Echo** (a data-driven power fragment).
- Player carries it to a **shrine** → **appraise** (reveal its modifier) → **bind** it to one ability.
- The bound Echo visibly changes that ability (e.g. "Flame Lance now chains to 2 targets").
- **One** modifier is enough. The point is to feel a build *change mid-run*.

### 5. Save + meta-loop
- **Profile save**: unlocks + a single faction's Renown counter (persists across runs).
- **Run save**: seed + current floor (so "Resume Run" works).
- Starter `EchoesSaveSubsystem` (`UE5_Gotchas/02`).

### 6. A minimal hub
- One small room. A portal into the Tower. A board showing Renown. That's it — the hub is a frame, not content.

---

## Explicitly OUT of scope (do NOT build for the slice)

These are real features for *later* — listing them here is how you protect the slice from scope creep:

- ❌ The open world / 8 kingdoms / World Partition streaming
- ❌ Faction questlines, dialogue trees, reputation gameplay (keep ONE Renown counter as a number)
- ❌ Companions (all 16)
- ❌ Crafting, economy, the Aether Bazaar, traveling blacksmiths
- ❌ Multiplayer / co-op / arena / social hub *(but build authority-correct now — `UE5_Gotchas/03`)*
- ❌ Biomes 2–13 and floors beyond ~5
- ❌ The other 6 elemental affinities
- ❌ Skill trees (one affinity, 3 abilities — no tree yet)

If you find yourself building any of the above "real quick," stop. That's the scope cliff the whole plan exists to avoid.

---

## Success criteria (measurable, not vibes)

The slice passes if a fresh playtester (not you):
1. Completes a Tower run (entrance → boss) without a tutorial.
2. Picks up, appraises, and binds an Echo **without being told how**.
3. **Plays a second run** voluntarily, and the build difference is noticeable to them.
4. Holds a stable framerate on your **defined min-spec** (`UE5_Gotchas/05`) — pick the GPU now.

If 1–3 happen, you have a game. If only 1–2, the loop works but the hook is weak — iterate on Echoes before expanding. If 1 fails, the moment-to-moment combat isn't there yet — fix that first.

---

## Content budget for the slice (keep it brutally small)

| Asset class | Slice budget | Notes |
|---|---|---|
| Abilities | 3 + basic attack | One affinity only |
| Enemies | 2 (minion + elite) + 1 boss | Boss can reuse minion rig |
| Room modules | 6–10 | Hand-built; PCG decorates |
| Echoes (distinct) | 4–6 | Each = one GameplayEffect modifier |
| Biomes | 1 | The other 12 are post-slice |
| VO / dialogue | 0 | None in the slice |

Lower budgets are *better* here. The slice is a question, not a demo.

---

## How this maps to the starter code

The `StarterCode/EchoesCore` module ships the scaffolding for items 1, 5, and 3:
- GAS triad → `EchoesPlayerState` / `EchoesAbilitySystemComponent` / `EchoesAttributeSet` / `EchoesCharacter`
- Save → `EchoesSaveSubsystem` / `EchoesSaveGame` / `EchoesPersistentIdComponent`
- Tower → `EchoesFloorGenerator` / `EchoesBiomeDataAsset`

You write the *game-specific* parts (the 3 abilities, the Echo modifiers, the room art) on top. The boilerplate that's easy to get subtly wrong is done.

See `02_MILESTONE_BACKLOG.md` for the build order and `03_SYSTEM_DESIGN.md` for how the pieces connect.
