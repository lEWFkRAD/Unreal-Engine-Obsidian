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
A reviewed UE 5.7 C++ module, `EchoesCore`:
- **Core systems:** the GAS triad (ASC-on-PlayerState), an async save system, a deterministic floor planner.
- **Slice scaffold:** native gameplay tags, a damage Execution Calc + Damage meta-attribute, an AI enemy + AIController, a GameMode, input-tag ability activation, and the **Echoes** data-asset + bind library — the C++ spine of milestones M1–M4.
- **[`StarterCode/FIRST_BUILD.md`](StarterCode/FIRST_BUILD.md)** — per-file compile-confidence table + the exact first-build errors and fixes, so the "reviewed-not-yet-compiled" caveat is a 15-minute checklist.

See [`StarterCode/README.md`](StarterCode/README.md) for the file map, wiring steps, and the full list of corrections applied during review.

## C — Hermes skill + eval harness (`hermes-skill/`, `eval-harness/`)
- [`hermes-skill/unreal-engine-dev/SKILL.md`](hermes-skill/unreal-engine-dev/SKILL.md) — makes a Hermes agent useful for UE5 (vault + kit paths, locked decisions, offload-and-review-don't-fabricate). Copy into a Hermes `skills/` dir; loads on gateway restart.
- [`hermes-skill/PROFILE-PROMPTS.md`](hermes-skill/PROFILE-PROMPTS.md) — tuned system prompts for local-model UE5 profiles (`ue5-coder`/`abilities`/`arch`/`worldbuilder`).
- [`eval-harness/`](eval-harness/README.md) — a UE5 code-gen eval that **measures your local model's API-hallucination rate** (run it against your own endpoint before/after a prompt change). Validated against a reference 27B (scored 5/8).

## D — Concept art (`concept-art/`)
Four 1024×1024 dark-fantasy mood pieces (Tower biome, flame faction, Echo fragment, HUD) for early visual identity — generated on a local ComfyUI pipeline. See [`concept-art/README.md`](concept-art/README.md). Mood refs, not final assets.

## Companion knowledge base
This kit pairs with the **Unreal-Engine-Obsidian** vault (the `UE5_Gotchas/` docs especially). The design docs and code comments reference `UE5_Gotchas/0X` throughout — read the matching gotcha doc before building each system.

---
*Built 2026-06-13. Code drafted on a local model and corrected by hand (see each README's correction list). Nothing here is committed to anyone's repo — it's a kit to hand over.*
