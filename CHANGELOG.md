# Changelog

All notable changes to the UE5 Tutorial Knowledge Base will be documented in this file.

Format based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).

## [v1.4.0] — 2026-06-13

### Added
- **Merged PR #1** from lEWFkRAD (Jeff) — community contribution with 54 new files:
  - `UE5_Gotchas/` — 5 concept docs + MOC covering GAS replication, open-world save architecture, multiplayer-from-day-one, procedural tower generation, performance budgets
  - `Contrib/echoes-of-ascension-kit/` — full dev kit: vertical-slice spec, milestone backlog, system design, starter UE 5.7 C++ module (EchoesCore with GAS triad, async save, deterministic floor gen), eval harness, Hermes skill
  - `Articles/ue5-canonical-references.md` — stable external references (Epic docs, tranek, Lyra, benui, Tom Looman, Cedric's Network Compendium)
  - `_REVIEW_Contributed_Gotchas.md` — review notes for contributed content

### Fixed
- Modernized `UE5_Gameplay_Framework_Reference.md` per errata (PR #1 review):
  - `AttachTo()` → `SetupAttachment()` (deprecated since UE4.12)
  - Removed legacy module headers (`Engine.h`, `EnginePrivate.h`, `*Classes.h`)
  - `IMPLEMENT_PRIMARY_GAME_MODULE` — added missing `FDefaultGameModuleImpl` first arg
  - `TargetInfo` → `ReadOnlyTargetRules` with `: base(Target)`
  - Replaced obsolete INI module registration with `.uproject` Modules array + `.Target.cs` ExtraModuleNames
  - `OutExtraModuleNames` → `ExtraModuleNames`
  - `FClassFinder` → `ConstructorHelpers::FClassFinder`
- Modernized `UE5_GAS_Reference.md` per errata (PR #1 review):
  - `InstancedPerExecution` / `NonInstanced` marked deprecated in UE 5.5+
  - `InstancedPerActor` set as default instancing policy

### Sources
- PR #1 authored with Claude Code, reviewed against UE 5.7 API
- Starter code reviewed for API correctness but not yet compiled against engine (no UE install available at authoring time)

---

## [v1.3.0] — 2026-06-13

### Added
- **UE5_CPP/UE5_Cpp_Reference_Guide.md** — Comprehensive C++ reference (897 lines):
  - Epic C++ Coding Standard — naming, formatting, portable types, modern C++
  - UObject System — CDO, creation rules, GC, ticking
  - Smart Pointers — TSharedPtr/TSharedRef/TWeakPtr/TUniquePtr, thread safety
  - UFUNCTION — all specifiers, metadata, parameter specifiers
  - Metadata Specifiers — class, enum, function, property meta tags (full reference)
  - UPROPERTY — all property specifiers, bitmask patterns, data types
  - TSubclassOf — type-safe UClass pointers
  - Containers — TArray, TMap/TMultiMap, TSet with full API reference
  - Delegates & Lambdas — declaration, binding, execution, examples
  - Low-Level Memory Tracker (LLM) — setup, tags, custom tags
- **UE5_CPP/UE5_Gameplay_Framework_Reference.md** — Gameplay architecture:
  - Class hierarchy & lifecycle (GameInstance → GameMode → GameState → Controller → Pawn)
  - Constructor patterns (ObjectInitializer, ConstructorHelpers, subobjects)
  - Gameplay Modules — DLL structure, Build.cs, module registration
  - Module categories (Runtime, Editor, Developer)
- **UE5_CPP/UE5_GAS_Reference.md** — Gameplay Ability System:
  - ASC setup with IAbilitySystemInterface
  - Gameplay Abilities — lifecycle, granting/revoking, tag interactions, network replication, instancing
  - Attributes & Attribute Sets — creation, helper macros, dual values, PostGameplayEffectExecute
  - Gameplay Effects — duration types, GE components, stacking, Gameplay Cues
  - Ability Tasks — async execution, custom tasks
  - GAS networking summary (prediction, rollback)
- Updated `_MOC_UE5_CPP.md` — new "Reference Guides" section with wikilinks
- Updated `README.md` — UE5_CPP file count 5→8

### Sources
- Epic Games UE 5.7 official documentation (11 pages extracted)
  - Coding Standard, Programming with C++, Delegates & Lambdas
  - Objects, Smart Pointers, UFunctions, Metadata, UProperties, Typed Object Pointers
  - Gameplay Framework, Gameplay Classes, Gameplay Modules
  - GAS: Understanding GAS, GAS Component, Abilities, Attributes, Effects, Ability Tasks

---

## [v1.2.1] — 2026-06-11

### Fixed
- Updated README.md to reflect all 26 folders, topic folders, architecture docs, and current file counts
- Added "Update README" step to release workflow skill

---

## [v1.2.0] — 2026-06-11

### Added
- **Architecture/** folder — 7 design decision docs from Hermes knowledge base:
  - `unreal-engine-rpg-systems.md` — Inventory, quests, dialogue, save system architecture patterns
  - `unreal-engine-solo-rpg-learning-path.md` — Priority-ordered learning plan for solo RPG dev
  - `unreal-engine-gameplay-ability-system.md` — GAS overview with RPG system mapping
  - `unreal-engine-blueprint-hybrid-workflow.md` — C++/Blueprint split strategy
  - `unreal-engine-cpp-foundations.md` — UObject system, reflection, garbage collection
  - `GASDocumentation.md` — Reference to tranek's GAS documentation (324KB)
  - `open-source-ue5-game-references.md` — ActionRoguelike and Alis as reference projects
- MOC index file for Architecture folder
- Wikilinks between architecture docs

### Notes
- Architecture docs are complementary to tutorials — they teach design decisions, not implementation steps
- 3 tooling docs (LLM tooling, MCP servers, skills) excluded pending audit
- Reviewed by 3 independent profiles (Senna, Architect, Secretary) before merge

---

## [v1.1.0] — 2026-06-11

### Added
- **14 new topic folders** with 45 tutorial files (255.5KB of new content):
  - `UE5_GAS/` — Gameplay Ability System (5 files) — abilities, effects, attributes, combat
  - `UE5_CPP/` — C++ for UE5 (5 files) — macros, components, Blueprint communication
  - `UE5_Data_Assets/` — Data Assets & Data Tables (3 files)
  - `UE5_AI/` — Behavior Trees, Blackboards, AI Perception (3 files)
  - `UE5_Niagara/` — Particle effects (3 files) — emitters, VFX, mesh particles
  - `UE5_UI/` — UMG widgets, Canvas Panel, HUD (3 files)
  - `UE5_Enhanced_Input/` — Input Actions, Mapping Contexts, triggers (3 files)
  - `UE5_Save_System/` — SaveGame, structs, checkpoints, autosave (3 files)
  - `UE5_Animation/` — Animation Blueprints, State Machines, Blend Spaces (3 files)
  - `UE5_Optimization/` — Profiling, Unreal Insights, GPU tips (3 files)
  - `UE5_World_Partition/` — Grid system, HLODs, landscape streaming (3 files)
  - `UE5_Audio/` — MetaSounds (2 files)
  - `UE5_Materials/` — Glass, layered materials, parallax occlusion (3 files)
  - `UE5_Multiplayer/` — Replication, RPCs, RepNotify (3 files)
- 14 new MOC (Map of Content) index files
- `_REVIEW_New_Tutorials.md` — review document with file-by-file overviews

### Verified
- All 45 new files checked against existing vault — 0 duplicates
- Content quality reviewed by Architect and Secretary profiles
- All files target UE5.6/5.7 — 0 deprecated features
- Frontmatter (title, source, video_id, type, series, episode, tags) consistent across all files

### Fixed
- 3 broken MOC wikilinks in UE5_Multiplayer/

---

## [v1.0.0] — 2026-06-11

### Added
- Initial vault with 155 files across 9 tutorial series
- Series covered:
  - `UE5_RPG_Framework/` — Gorka Games RPG series (12 files)
  - `Blueprint_Fundamentals/` — Ask A Dev visual scripting (28 files)
  - `UE5_Beginner_Tutorials/` — Coqui Games coding (17 files)
  - `UE5_7_Starter_Course/` — Bad Decisions beginner (21 files)
  - `UE5_PCG_Tutorial/` — PolyBoost procedural generation (34 files)
  - `Learn_to_Code_Blueprints/` — UNF Games landscape/world (22 files)
  - `Step_by_Step_Guides/` — Extracted step-by-step instructions (14 files)
  - `Individual_Videos/` — Standalone tutorials (4 files)
  - `Articles/` — Non-video content (2 files)
- YAML frontmatter on all files
- Wikilinks between episodes (previous/next + series MOC)
- MOC index files per folder
- `.obsidian/` configuration for graph view, backlinks, tags
- `.gitignore` for workspace files and macOS artifacts
- README with vault overview and usage instructions

### Notes
- 91 files moved to `_non_educational/` (YouTube descriptions without tutorial content)
- 170 files in `_duplicates/` from earlier extraction runs (safe to delete)
