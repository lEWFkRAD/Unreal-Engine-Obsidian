---
title: Open-Source UE5 Game References
created: 2026-05-29
updated: 2026-05-29
type: concept
tags: [unreal-engine, cpp, game-development, architecture, solo-development, coding]
composes: [unreal-engine-cpp-foundations, unreal-engine-rpg-systems]
composed_by: []
topics: [unreal-engine, game-development, cpp]
workflow: developing
confidence: high
sources: [github.com/tomlooman/ActionRoguelike, github.com/fallintodusk/alis]
---

# Open-Source UE5 Game References

Two open-source Unreal Engine 5 projects that serve as primary references for C++ game architecture, AI-assisted coding patterns, and plugin-based project organization.

## ActionRoguelike (Tom Looman)

**Repo:** [tomlooman/ActionRoguelike](https://github.com/tomlooman/ActionRoguelike)
**Stats:** 4.5k stars, 800 forks | C++ 98.7% | UE 5.6
**Origin:** Expansion on the "Professional Game Development in C++ and Unreal Engine 5" course.

### Why This Matters

This is THE canonical UE5 C++ learning project. LLMs are trained extensively on this codebase — when you ask Claude or GPT to generate UE5 C++ code, Tom Looman's patterns are the style it most likely produces (if correct). It IS the "known-good reference" for verifying LLM-generated code.

### Key Systems (all in C++)

| System | Implementation |
|--------|---------------|
| Action System | GAS-like: Dash, Blackhole, Magic Projectile, Thorns buff, Burning DoT |
| AttributeComponent | Health, stats — maps to UAttributeSet |
| Enhanced Input | Third-person character movement |
| GameplayTags | Markup for actors, buffs, actions |
| AI | Behavior Trees with custom C++ BT nodes, EQS for spawn/attack/cover |
| SaveGame | Persisting character + world state |
| Data | DataTable + DataAsset for bot configs, enemy definitions |
| Asset Manager | Async loading of data assets and UI icons |
| UMG UI | Main menu, player HUD, projected widgets |
| Multiplayer | Full networking support |
| Experimental | Actor pooling, aggregate ticking, DOD projectiles, async line traces, PSO precaching |

### C++ / Blueprint Hybrid Pattern

Tom demonstrates the optimal split:
- **C++** → Core systems, action logic, AI, networking, architecture
- **Blueprint** → Content iteration, visual tuning, level logic, designer-facing content

This is the recommended approach for solo dev. See [[unreal-engine-blueprint-hybrid-workflow]].

### What to Study

- `Source/ActionRoguelike/` for C++ class hierarchy
- How ActionSystem maps to GAS patterns (see [[unreal-engine-gameplay-ability-system]])
- BT node implementation in C++
- The C++/Blueprint boundary decisions
- Multiplayer replication patterns

### AI Coding Value

- LLMs are most familiar with this codebase's style
- Use as verification: compare LLM-generated code against Tom's patterns
- Course branches available: `UE5.6-CourseProject` for lesson-aligned code

## ALIS (fallintodusk/alis)

**Repo:** [fallintodusk/alis](https://github.com/fallintodusk/alis)
**Type:** Open-source UE5 survival game + architecture reference
**Philosophy:** Public reference for Unreal Engine architecture, not just a game

### Why This Matters

ALIS is explicitly designed as a modular architecture template. Plugin-based C++ core, data-driven workflows, contract-first integration. This is how to organize a UE5 project for scale and AI-assisted development.

### Plugin Structure (the template)

```
Plugins/
  Boot/        — Early boot, plugin lifecycle management
  Editor/      — Data generation, sync, propagation tools
  Foundation/  — Contracts, shared types, low-level utilities
  Systems/     — Runtime services (loading, save, settings)
  UI/          — Framework and feature UI plugins
  Gameplay/    — Gameplay framework, shared patterns
  Features/    — Optional capabilities (inventory, combat, dialogue)
  World/       — World tools, world-specific implementations
```

### Key Systems (all as plugins)

| System | Description |
|--------|------------|
| Inventory | Server-authoritative, equip/use/drop, weight/volume, depth stacking |
| Vitals | Server-side metabolism tick, threshold states, condition regen/drain |
| Dialogue | Universal data-driven system for NPCs, objects, terminals |
| Mind | Inner-voice thought guidance system |
| Interaction | Trace + prompt based player-world interaction |
| Object Capabilities | Composable components (lockable, loot container, pickup) |
| GAS | Gameplay Ability System integration layer |
| Loading | 6-phase content pipeline with loading screens |

### Data Pipeline (JSON-first)

1. **Asset Sync** — JSON path updates on rename
2. **Definition Generation** — JSON → DataAsset via `x-alis-generator` schema extensions
3. **Propagation** — Cascading actor updates in placed scenes

AI can easily generate/modify JSON definitions. This is the ideal data-driven workflow.

### Contract-First Design

- Explicit ownership boundaries between plugins
- Clear integration contracts
- Each plugin is independently testable
- This is what makes AI-assisted coding work — clear boundaries mean clear context windows for LLMs

### What to Study

- Plugin structure as a template for new projects
- JSON → DataAsset pipeline for data-driven design
- Contract-first integration patterns
- Object Capabilities composable component pattern
- How GAS integration layer wraps the plugin boundary

## Beyond All Reason (BAR) — Limited Relevance

**Repo:** [beyond-all-reason/Beyond-All-Reason](https://github.com/beyond-all-reason/Beyond-All-Reason)
**Stats:** 4k stars, 284 contributors | Lua 90.1% | Recoil engine (Spring fork)

BAR is NOT a C++ UE project — it's Lua on the Spring/Recoil RTS engine. However, it teaches:

- **Data-driven unit definitions** (gamedata/, units/, weapons/ separated from logic)
- **Automated testing at scale** (Busted test framework + CI)
- **Community contribution model** (284 contributors = clear architecture boundaries)
- **Custom shader pipeline** (GLSL fog of war, effects)

Useful for studying game architecture patterns at scale, but not a direct C++/UE reference.

## Recommended Usage

| Purpose | Use |
|---------|-----|
| C++ code style reference | ActionRoguelike — compare LLM output against Tom's patterns |
| Project architecture template | ALIS — plugin structure, contract-first, JSON data pipeline |
| GAS patterns | ActionRoguelike + [[unreal-engine-gameplay-ability-system]] |
| Data-driven design study | BAR (data separation) + ALIS (JSON → DataAsset pipeline) |
| AI coding verification | ActionRoguelike as "known-good" baseline |

## Related

- [[unreal-engine-cpp-foundations]] — UObject, GC, reflection, containers
- [[unreal-engine-blueprint-hybrid-workflow]] — C++/Blueprint split strategy
- [[unreal-engine-gameplay-ability-system]] — GAS architecture
- [[unreal-engine-rpg-systems]] — Inventory, quests, dialogue patterns
- UE5 LLM tooling — MCP servers, skills, model recommendations
- [[unreal-engine-solo-rpg-learning-path]] — Priority-ordered learning plan
