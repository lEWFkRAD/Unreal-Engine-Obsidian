# Echoes of Ascension — Milestone Backlog (Vertical Slice)

Ordered build plan for the v1 slice defined in `01_VERTICAL_SLICE_SPEC.md`. Each milestone has a **Definition of Done (DoD)** — don't move on until it's met. Sequence matters: each milestone de-risks the next. Rough effort is in "focused solo-dev days," deliberately conservative.

> **Rule:** every milestone ends in something you can *run and click*. No milestone is "write a system you can't yet see." If you can't play it, it's not done.

---

## M0 — Project & module setup  ·  ~2–3 days
Get a clean UE 5.7 C++ project that compiles with GAS enabled.

- [ ] Create a UE 5.7 **C++** project (not Blueprint-only).
- [ ] Enable plugins: **Gameplay Abilities**, Enhanced Input, (later) PCG.
- [ ] Drop in the `EchoesCore` starter module; add `GameplayAbilities`, `GameplayTags`, `GameplayTasks` to `Build.cs` (already in the starter).
- [ ] Confirm it compiles and the editor opens with the module loaded.
- [ ] Init git + `.gitignore` (UE template). Commit the empty-but-compiling project.

**DoD:** editor opens, `EchoesCore` module shows in the class list, zero compile errors.

---

## M1 — GAS core comes alive  ·  ~3–5 days
Prove abilities + attributes replicate and a number on screen changes.

- [ ] Set `AEchoesPlayerState` + `AEchoesCharacter` + `UEchoesAttributeSet` as the game's pawn/state (GameMode wiring).
- [ ] Author `GE_InitStats` (instant GE) to seed Health/MaxHealth/Aether/MaxAether/AttackPower; wire it to `DefaultAttributesEffect`.
- [ ] Author **one** `UEchoesGameplayAbility` (basic attack) and add it to `DefaultAbilities`.
- [ ] Bind input (Enhanced Input) → activate the ability.
- [ ] On-screen debug HUD showing Health/Aether (UMG or `stat`/debug draw).
- [ ] **Test in net PIE (2 players)** even though slice ships SP — catch replication mistakes now (`UE5_Gotchas/01` + `/03`).

**DoD:** press a key, ability fires, an attribute changes, and it's correct on a second PIE client.

---

## M2 — Combat slice  ·  ~4–6 days
Make it a fight.

- [ ] Add the 2 remaining abilities (resource-spender + dash). Aether cost via GE cost; cooldown via GE.
- [ ] `GE_Damage` + an Execution Calculation that reads AttackPower → subtracts Health.
- [ ] Minion enemy: ACharacter + ASC-on-pawn (Full replication), Behavior Tree (chase + attack).
- [ ] Death handling: Health≤0 → death ability/tag → ragdoll/despawn. Player death → end run.
- [ ] Elite enemy variant (more health, telegraphed hit) — the future Echo dropper.

**DoD:** you can fight and kill minions, the elite can kill you, death ends the run cleanly.

---

## M3 — The Tower generates  ·  ~5–7 days
One biome, deterministic, navigable.

- [ ] 6–10 hand-built **room modules** (greybox is fine) for the chosen biome.
- [ ] Wire `UEchoesFloorGenerator`: seed → biome pick (single biome for slice) → room count → assemble modules into a floor.
- [ ] Stitch rooms with a guaranteed entrance→exit path; replace `ValidateConnectivity` stub with a real reachability check.
- [ ] **NavMesh Runtime Generation = Dynamic**; rebuild after assembly; gate enemy spawn on nav ready (`UE5_Gotchas/04`).
- [ ] Exit portal advances `CurrentFloor`; floor N (=15 cadence, or just floor 5 for the slice) loads the **boss room** (scripted).
- [ ] PCG pass for decoration only (optional for slice).

**DoD:** enter the Tower, traverse 3–5 generated floors with enemies, reach a boss room. Same seed = same floors.

---

## M4 — The Echoes loop (the hook)  ·  ~4–6 days
The reason to play twice.

- [ ] `UEchoesEcho` data asset (a GameplayEffect modifier + display data).
- [ ] Elite death → spawn an Echo pickup (1 of 4–6).
- [ ] Shrine actor: interact → **appraise** (reveal modifier) → **bind** to a chosen ability.
- [ ] Binding applies the Echo's modifier (e.g. extra projectile, chain, lifesteal) so the ability *visibly* changes.
- [ ] Surface the change in UI ("Flame Lance: +1 chain").

**DoD:** kill elite → get Echo → appraise → bind → the ability plays differently. Two runs feel different.

---

## M5 — Save & meta-loop  ·  ~3–4 days
Make runs persist and progress stick.

- [ ] Wire `UEchoesSaveSubsystem`: Profile (unlocks + one Renown counter) + Run (seed + floor).
- [ ] Main menu / hub: "New Run" (fresh seed) vs "Resume Run" (if a Run save exists).
- [ ] On boss kill or death: update Profile (Renown/unlock), discard or keep Run appropriately.
- [ ] Version stamp on both saves; handle a missing/old save gracefully (`UE5_Gotchas/02`).

**DoD:** quit mid-run, relaunch, Resume Run drops you back on the right floor; meta-progress persisted.

---

## M6 — Min-spec, polish & the FUN GATE  ·  ~4–5 days
The decision milestone.

- [ ] Pick the **min-spec GPU**; profile a full run on it (`stat unit`, `stat GPU`, Insights — `UE5_Gotchas/05`).
- [ ] Software Lumen; audit hard references for hitches; Niagara Effect Types on VFX.
- [ ] Onboarding-light: no tutorial, but readable affordances (shrine glows, exit is obvious).
- [ ] **Playtest with ≥3 people who aren't you.** Score against `01_VERTICAL_SLICE_SPEC.md` success criteria.

**DoD / GO–NO-GO:** testers complete a run, bind an Echo unprompted, and *choose* a second run. → Greenlight biome expansion. Otherwise, iterate the loop before expanding.

---

## Total slice estimate: ~25–36 focused days
That's the whole bet, made cheaply. Only after M6 passes do you open the `02 → open world` expansion — and by then the combat, save, and generation systems are proven, not hypothetical.

## What expansion looks like *after* the slice passes (not now)
1. Biomes 2–13 (cheap — the generator exists).
2. The other affinities + a real skill tree.
3. More Echoes (each is just a new modifier asset).
4. THEN the open world / factions, scoped down from the GDD.
5. Co-op in the Tower (the architecture's already correct from M1).
