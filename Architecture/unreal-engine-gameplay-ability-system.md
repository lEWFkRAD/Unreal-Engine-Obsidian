---
title: Unreal Engine Gameplay Ability System
created: 2026-05-19
updated: 2026-05-19
type: concept
tags: [unreal-engine, gas, gameplay-ability-system, rpg, gameplay-framework]
composes: [unreal-engine-rpg-systems]
composed_by: []
topics: [unreal-engine, game-development, gameplay-systems]
workflow: developing
confidence: high
sources: [raw/articles/GASDocumentation, raw/articles/unreal-engine-skills]
---

# Unreal Engine Gameplay Ability System (GAS)

The Gameplay Ability System is a framework for building abilities, attributes, effects, and interactions — designed for RPGs, MOBAs, and action games. It's the backbone behind Fortnite, Genshin Impact, and most shipped UE action RPGs.

## Core Components

```
AbilitySystemComponent (ASC) — on player or NPC actor
├── Owns/grants GameplayAbility instances
├── Tracks AttributeSet (health, mana, strength, etc.)
├── Applies GameplayEffect (buffs, debuffs, damage)
├── Manages GameplayTags (Stunned, Invulnerable, etc.)
└── Replicates: attributes + tags (not full ability state) in multiplayer
```

## RPG System Mapping

| RPG Need | GAS Component |
|-----------|---------------|
| Spell casting | `UGameplayAbility` with cooldown, cost, montage |
| Damage formula | `UGameplayEffect` + `ModifierMagnitudeCalculation` |
| Stats (STR, INT, AGI) | `UAttributeSet` with gameplay tags |
| Buffs/debuffs | `UGameplayEffect` (duration-based) |
| Status effects (Stun/Freeze) | `FGameplayTag` blocking other abilities |
| Passive skills | Always-active `UGameplayAbility` |
| Item effects | Granted abilities via item's GameplayEffect |
| XP / Leveling | AttributeSet + level-up GameplayEffect |

## Ability Activation — Four Methods

1. **Explicit** — grant ability + call `TryActivateAbility()`
2. **Gameplay Event** — `SendGameplayEvent()` triggers matching abilities
3. **Input binding** — bind input to ASC
4. **Tag match** — effect with matching tag auto-triggers ability

## Gameplay Effects — Three Types

| Type | Behavior |
|------|----------|
| **Instant** | Modifies Base Value (direct damage) |
| **Duration** | Modifies Current Value, auto-reverts on expiry |
| **Infinite** | Applies until manually removed |

## Definitive Resource

The community bible: `tranek/GASDocumentation` — cloned at `github.com/tranek/GASDocumentation`. Covers everything from basic setup to advanced network prediction with working code examples.

## Related

- [[unreal-engine-cpp-foundations]] — UObject/GC patterns powering GAS
- [[unreal-engine-rpg-systems]] — inventory, quests, dialogue built on GAS
- [[unreal-engine-blueprint-hybrid-workflow]] — exposing GAS to Blueprint
- Model Context Protocol — MCP servers that can inspect GAS state live
