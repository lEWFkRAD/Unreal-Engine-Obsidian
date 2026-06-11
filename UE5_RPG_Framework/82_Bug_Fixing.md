---
title: "Unreal Engine 5 RPG Tutorial Series - #82: Bug Fixing"
source: "https://www.youtube.com/watch?v=MYHOvp0_jcs"
video_id: "MYHOvp0_jcs"
type: "youtube-summary"
series: "UE5 RPG Framework"
episode: 82
tags: [ue5, tutorial, blueprint, gamedev, rpg, bug-fixing, ai, combat]
---

# UE5 RPG Tutorial #82: Bug Fixing

**Instructor:** Gorka Games | **Length:** 12:22 | **Published:** 2024-08-03

## Overview
Critical bug fixes before the planned series finale. Addresses AI behavior, combat state, and camera clipping issues.

## Bugs Fixed

### 1. AI Continues Attacking After Death
- **Problem:** AI still attacks player after dying if within range.
- **Fix:** Implement `is_dead` variable. Set to `true` after death in `AnyDamage` event. Use to disable `can_attack`.

### 2. AI Can Be Assassinated Twice
- **Problem:** Dead AI could be assassinated again.
- **Fix:** In `StealthBackAssassin` interface, add branch checking `is_dead` before proceeding.

### 3. XP Gain / Damage Taken on Dead Enemies
- **Problem:** Multiple XP gains or damage from dead enemies.
- **Fix:** Add `is_dead` checks to player's Health System `AnyDamage` event. Also prevents XP being awarded multiple times via "Do Once" node logic.

### 4. Player Attack System Breaks When Hit
- **Problem:** Receiving damage while attacking interrupts montage, leaving `is_attacking` stuck as `true`.
- **Fix:** In player's `AnyDamage` event (Third Person Blueprint), after playing damage montage, get Attack System component and call `StopCombo` (not `StopTrace`) to reset combo state.

### 5. Camera Clipping on Enemies
- **Problem:** Player camera clips through enemy models.
- **Fix:**
  - AI mesh: Set collision to **Ignore** the **Camera** channel.
  - UI elements (health bars): Set collision to **Custom** with **No Collision**.
  - Assassination Radius: Set collision to **Custom**, **Ignore** Camera channel.

## Context
- One of the final bug-fixing episodes before the showcase finale.
- Project files available via Patreon.

---

## Related

- ← Previous: [[10_Sword_Trace_Damage_and_Hit_Reactions]]
- → Next: [[83_The_Final_Episode]]
- 📚 Series: [[_MOC_UE5_RPG_Framework]]
