# Echoes of Ascension — Dev Kit

A starter kit to help build *Echoes of Ascension* (UE 5.7 open-world RPG) — assembled to go beyond
"here are some docs." Three lanes:

## A — Production plan (`design/`)
Turns the GDD into a *buildable* v1. Read in order:
1. [`design/01_VERTICAL_SLICE_SPEC.md`](design/01_VERTICAL_SLICE_SPEC.md) — the smallest thing that proves the game is fun (one Tower biome + GAS combat + the Echoes loop + save). Defines what's deliberately **out** of scope.
2. [`design/03_SYSTEM_DESIGN.md`](design/03_SYSTEM_DESIGN.md) — how the systems connect + the locked decisions.
3. [`design/02_MILESTONE_BACKLOG.md`](design/02_MILESTONE_BACKLOG.md) — ordered M0–M6 build plan, ~25–36 focused days, ending in a GO/NO-GO fun gate.

**The core message:** the scope is the existential risk. Prove the Tower loop in one biome (cheap), *then* expand to the open world (expensive). Don't invert that.

## B — Starter code (`StarterCode/`)
A reviewed UE 5.7 C++ module, `EchoesCore` — the GAS triad, an async save system, and a deterministic floor planner. The boilerplate that's easy to get subtly wrong, done. See [`StarterCode/README.md`](StarterCode/README.md) for drop-in steps and the honest "reviewed-not-yet-compiled" caveat.

## C — Hermes skill (`hermes-skill/`)
[`hermes-skill/unreal-engine-dev/SKILL.md`](hermes-skill/unreal-engine-dev/SKILL.md) — makes a Hermes agent genuinely useful for UE5: it knows where the knowledge vault + starter code live, the locked architecture decisions, and the offload-and-review workflow for generating engine code without hallucinating APIs. Install by copying the `unreal-engine-dev/` folder into a Hermes `skills/` directory; loads on the next gateway restart.

## Companion knowledge base
This kit pairs with the **Unreal-Engine-Obsidian** vault (the `UE5_Gotchas/` docs especially). The design docs and code comments reference `UE5_Gotchas/0X` throughout — read the matching gotcha doc before building each system.

---
*Built 2026-06-13. Code drafted on a local model and corrected by hand (see each README's correction list). Nothing here is committed to anyone's repo — it's a kit to hand over.*
