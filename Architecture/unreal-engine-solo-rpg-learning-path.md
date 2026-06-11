---
title: Unreal Engine Solo RPG Learning Path
created: 2026-05-19
updated: 2026-05-19
type: concept
tags: [unreal-engine, learning-path, solo-development, rpg]
sources: []
topics: [unreal-engine, game-development, learning]
workflow: seedling
confidence: medium
---

# Unreal Engine Solo RPG Learning Path

Priority-ordered plan for a solo developer building an RPG in UE5.

## Priority Order

### 1. GAS Foundation (Week 1-2)
**Why first:** GAS is your RPG backbone — spells, damage, buffs, stats.
- Read `tranek/GASDocumentation` (cloned at `github.com/tranek/GASDocumentation`)
- Follow Epic's official GAS course
- Build: a character with health/mana, one spell, one buff

### 2. Composition & Components (Week 2-3)
**Why:** Every RPG system (inventory, dialogue, quest) is a component.
- Load the `ue-actor-component-architecture` skill
- Build: character with swappable component sets

### 3. Data-Driven Design (Week 3-4)
**Why:** RPGs are data-heavy — items, enemies, quests, dialogue all need external data.
- Load the `ue-data-assets-tables` skill
- Pattern: `UPrimaryDataAsset` for everything configurable

### 4. Hybrid C++/BP Workflow (Ongoing)
- Core in C++, content in Blueprint
- Every C++ class has Blueprint hooks
- Data Assets for content that changes often

### 5. Save/Load (When needed)
- RPG persistence via `UGameInstanceSubsystem` + `USaveGame`
- Load `ue-serialization-savegames` skill

### 6. Enhanced Input (When needed)
- Modern UE5 input system
- Load `ue-input-system` skill

## Recommended Courses

- **Stephen Ulibarri** — "UE5 GAS Top Down RPG" (Udemy) — best GAS-specific RPG course
- **Tom Looman** — "Professional Game Dev in C++ and Unreal" — project-based action game
- **Epic Official GAS Course** — Free on Epic Developer Community

## Recommended LLMs for UE C++

Community consensus from forums and Reddit: **Claude** (Sonnet/Opus) is the most reliable for UE C++. Use the LLM supplementally — learn fundamentals from a structured course first.

## Related

- [[unreal-engine-cpp-foundations]] — start here conceptually
- [[unreal-engine-gameplay-ability-system]] — step 1 in practice
- [[unreal-engine-rpg-systems]] — what you're building toward
- [[unreal-engine-blueprint-hybrid-workflow]] — ongoing pattern
- AI-assisted coding — LLM prompting patterns for UE
