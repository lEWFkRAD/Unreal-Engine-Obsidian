---
name: unreal-engine-dev
description: Help build the Unreal Engine 5.7 RPG "Echoes of Ascension" (and UE5 game systems generally) — GAS combat, save/persistence, procedural Tower generation, multiplayer-readiness, performance. Use whenever the user asks to design, scaffold, debug, or review UE5 C++/Blueprint gameplay code, mentions GAS / AbilitySystemComponent / AttributeSet / GameplayEffect / GameplayAbility, World Partition, PCG, Niagara, Nanite/Lumen, save games, or the Echoes of Ascension project, Eldrath, the Tower of Ascension, Aether Mastery, Aetheric Renown, or Echoes power fragments. This skill knows where the local UE5 knowledge vault and starter code live, the project's locked architecture decisions, and the offload-and-review workflow for generating engine code without hallucinating APIs.
version: 1.0.0
author: Claude (Forge), 2026-06-13 — built to help NOUS member Noctis (theheavenlyd3mon) with Echoes of Ascension
license: MIT
metadata:
  hermes:
    tags: [unreal-engine, ue5, gas, game-development, rpg, echoes-of-ascension, scaffolding, code-review]
    related_skills: [contributing-to-hermes, autonomous-ai-agents]
---

# Unreal Engine 5 Dev — helping build Echoes of Ascension

You have a local UE5 knowledge base and a reviewed C++ starter scaffold on this machine. When the
user asks for UE5 help, **use them** instead of answering from memory — UE APIs are version-specific
and easy to get subtly wrong.

## Where everything is (on Forge)

- **Knowledge vault:** `<vault>/` — 230+ wikilinked notes. The highest-signal
  folder is `UE5_Gotchas/` (what breaks and why), plus `Architecture/` and
  `Articles/ue5-canonical-references.md`. Grep/read these; don't guess.
- **Starter code:** `<vault>/Contrib/echoes-of-ascension-kit/StarterCode/Source/EchoesCore/` — reviewed UE 5.7
  C++ scaffolding (GAS triad, save subsystem, floor generator). Read it before writing new gameplay
  code so new code matches its patterns.
- **Production plan:** `<vault>/Contrib/echoes-of-ascension-kit/design/` — vertical-slice spec, milestone
  backlog, system-design map. Use these to keep work scoped to the slice.

> If running on a machine that is NOT Forge, these paths won't exist locally — clone the vault from
> `github.com/theheavenlyd3mon/Unreal-Engine-Obsidian` and adjust the paths.

## The workflow: offload generation, always review (never fabricate APIs)

This is the load-bearing rule. A local model drafting UE C++ **will invent class/macro/function
names** (observed: `UGameplayAbilityComponent`, `UAbilitySystemLibrary::SetOwner`,
`Data.EvaluatedAttributes.ContainsAttribute`, `ASC->GetLevel()`). So:

1. **Draft** larger code (>~50 lines) on the local vLLM node (`127.0.0.1:8001`, 4 concurrent) with a
   tight, signature-accurate prompt that names the real APIs you expect.
2. **Review every line** against the vault's gotchas docs and the starter code. Fix invented APIs,
   wrong override signatures, and non-idiomatic includes.
3. **Cite the gotcha doc** you used. Tiny fixes / debugging stay local to you (the agent); don't
   offload a 3-line change.

For each system, read the matching gotcha doc *first*:

| Task | Read first |
|------|-----------|
| Abilities, attributes, combat, replication | `UE5_Gotchas/01_GAS_Replication_Gotchas.md` |
| Save / load / persistence / World Partition | `UE5_Gotchas/02_OpenWorld_Save_Architecture.md` |
| Anything co-op / networking | `UE5_Gotchas/03_Multiplayer_From_Day_One.md` |
| Procedural tower / PCG / nav | `UE5_Gotchas/04_Procedural_Tower_Generation.md` |
| Framerate / Lumen / Nanite / hitching | `UE5_Gotchas/05_Performance_Budget_Reality.md` |

## Locked architecture decisions (don't relitigate without the user)

- **ASC on PlayerState**, **Mixed** replication for players, **Full** for AI. (`01`)
- Init attributes via an instant **GameplayEffect**, not C++ constants. Math in GEs, not Tick.
- **InitAbilityActorInfo** on server (`PossessedBy`) AND owning client (`OnRep_PlayerState`).
- Two saves: **Profile** (permanent) vs **Run** (disposable); version-stamp both; async save. (`02`)
- Procedural floors are **deterministic** from a seed; **PCG decorates, doesn't lay out**; floors are
  **discrete sublevels**, not World Partition; NavMesh runtime gen = **Dynamic**. (`04`)
- **Software Lumen**, defined min-spec, soft references + async loading. (`05`)
- It's **World Partition**, not the legacy "World Composition." (`02`)
- Build **authority-correct from day one** even though single-player ships first; co-op is scoped to
  the (instanced) Tower. (`03`)

## Scope discipline (the project's #1 risk)

Echoes of Ascension is scoped like a 200-person studio's game. The plan is to prove the **Tower
roguelite loop** in one biome first (see `design/01_VERTICAL_SLICE_SPEC.md`), then expand. If the user
starts building the open world / 8 factions / 16 companions / crafting economy before the vertical
slice passes its fun gate, gently point back at the spec. Cheap-to-prove first, expensive-to-build later.

## When reviewing the user's UE5 code

Check, in order: authority (`HasAuthority()` on state mutations), replication correctness
(`GetLifetimeReplicatedProps`, `REPNOTIFY_Always` on attributes), `InitAbilityActorInfo` timing,
hard references that should be soft, and Tick logic that belongs in a GameplayEffect. Reference the
specific gotcha doc for each finding.
