# Changelog

All notable changes to the UE5 Tutorial Knowledge Base will be documented in this file.

Format based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).

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
