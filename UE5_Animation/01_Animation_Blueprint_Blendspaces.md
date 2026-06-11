---
title: "How to Animate Your Character in UE5 - Animation Blueprints and Blendspaces"
source: "https://www.youtube.com/watch?v=WUXvq6At6pE"
video_id: "WUXvq6At6pE"
type: "youtube-summary"
series: "UE5 Animation"
episode: 1
tags: [ue5, animation, animation-blueprint, blendspace, locomotion]
---

# How to Animate Your Character in UE5 - Animation Blueprints and Blendspaces

**Duration:** 11:53 | **Creator:** Gorka Games | **Views:** 542K+

## Overview

A beginner-friendly tutorial on setting up **Animation Blueprints** and **Blendspaces** in UE5 — the two core systems that drive character animation. This covers the fundamental workflow for getting a character to walk, run, and idle smoothly.

## What is an Animation Blueprint?

An Animation Blueprint (AnimBP) is a special Blueprint that controls character animation each frame. It:
- Reads game state (speed, direction, is in air, etc.)
- Selects and blends animations based on that state
- Outputs the final pose to the skeletal mesh

## What is a Blend Space?

A Blend Space interpolates between multiple animations based on one or two input values. For locomotion:
- **1D Blend Space:** Speed only (idle → walk → run)
- **2D Blend Space:** Speed + Direction (walk forward, strafe left, run backward, etc.)

## Step-by-Step Implementation

### Step 1: Import Animations

If using Mixamo or similar:
1. Import your character with skeleton
2. Import animation assets: Idle, Walk, Run (and strafe variants for 2D)
3. Ensure all animations use the **same skeleton**

### Step 2: Create a Blend Space

**For 1D Locomotion (Speed only):**
1. Content Browser → Right-click → Animation → Blend Space 1D
2. Select your skeleton
3. Name it `BS_Locomotion`
4. Set the axis:
   - Name: "Speed"
   - Min: 0, Max: 600
   - Snap to grid: 100
5. Place animations on the axis:
   - 0: Idle
   - 150: Walk
   - 600: Run

**For 2D Locomotion (Speed + Direction):**
1. Content Browser → Right-click → Animation → Blend Space
2. Select your skeleton
3. Name it `BS_Locomotion_2D`
4. Set axes:
   - Horizontal: "Direction" (-180 to 180)
   - Vertical: "Speed" (0 to 600)
5. Place animations at coordinates:
   - (0, 0): Idle
   - (0, 150): Walk Forward
   - (0, 600): Run Forward
   - (180, 150): Walk Backward
   - (-90, 150): Strafe Left
   - (90, 150): Strafe Right
   - etc.

### Step 3: Create the Animation Blueprint

1. Content Browser → Right-click → Animation → Animation Blueprint
2. Select your skeleton
3. Name it `ABP_Character`

### Step 4: Set Up Variables

In the AnimBP Event Graph, create variables:
- `Speed` (Float) — character movement speed
- `Direction` (Float) — movement direction relative to character
- `IsInAir` (Boolean) — whether character is falling

**Update variables each frame:**
```
Event Blueprint Update Animation:
  → Try Get Pawn Owner
  → Get Velocity → Vector Length → Set Speed
  → Calculate Direction (use Calculate Direction node)
  → Get Movement Component → Is Falling → Set IsInAir
```

The `Calculate Direction` node takes:
- Pawn's velocity
- Pawn's rotation
- Returns angle (-180 to 180)

### Step 5: Build the AnimGraph

In the AnimBP AnimGraph:

```
[State Machine "Locomotion"]
  ├── Idle State → Animation: Idle sequence
  │     Transition to Walk: Speed > 10
  │
  ├── Walk/Run State → Blend Space Player: BS_Locomotion
  │     Input: Speed
  │     Transition to Idle: Speed < 10
  │     Transition to Jump: IsInAir == true
  │
  └── Jump State → Animation: Jump sequence
        Transition back: IsInAir == false
```

For 2D Blend Space, feed both Speed and Direction:
```
Blend Space Player: BS_Locomotion_2D
  - Axis X: Direction
  - Axis Y: Speed
```

### Step 6: Assign AnimBP to Character

In your Character Blueprint:
1. Select the Mesh component
2. In Details panel → Animation → Anim Class
3. Set to `ABP_Character`

### Step 7: Transition Rules

For each transition between states:
1. Click the transition arrow
2. In Details panel, set the rule:
   - `Idle → Locomotion`: `Speed > 10.0`
   - `Locomotion → Idle`: `Speed <= 10.0`
   - `Locomotion → Jump`: `IsInAir == true`
   - `Jump → Locomotion`: `IsInAir == false`
3. Set blend time (0.2s typical for locomotion)

## Best Practices

1. **Keep Event Graph lightweight** — expensive logic belongs in the character BP
2. **Use Property Access nodes** for thread-safe reads (UE5 optimization)
3. **Enable Thread Safe Update** in AnimBP class settings for performance
4. **Organize with regions** — group Event Graph logic into labeled sections
5. **Use Sub-AnimBPs** for complex characters (separate upper/lower body)

## Common Mistakes

1. Wrong skeleton selected when creating AnimBP
2. Forgetting to set Anim Class on the character mesh
3. Blend Space axis ranges don't match actual speed values
4. Missing `Try Get Pawn Owner` null check
5. Transition rules too strict (causing animation snapping)

## Creator Links

- [Gorka Games](https://www.youtube.com/@GorkaGames)
- [Patreon](https://bit.ly/GorkaGames_Patreon)


---

## Related

- → Next: [[02_Animation_Blueprint_State_Machine]]
- 📚 Series: [[_MOC_UE5_Animation]]
