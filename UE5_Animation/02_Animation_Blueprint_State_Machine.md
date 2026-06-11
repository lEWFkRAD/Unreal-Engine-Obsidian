---
title: "UE5 Animation Blueprint Fundamentals | Building Your First State Machine"
source: "https://www.youtube.com/watch?v=BnUxJScdkQY"
video_id: "BnUxJScdkQY"
type: "youtube-summary"
series: "UE5 Animation"
episode: 2
tags: [ue5, animation, state-machine, animation-blueprint, animgraph]
---

# UE5 Animation Blueprint Fundamentals — Building Your First State Machine

**Duration:** 9:40 | **Source:** YouTube

## Overview

This tutorial focuses on the **State Machine** — the backbone of Animation Blueprints. State Machines manage high-level animation states (Idle, Walk, Jump, Attack) and the transitions between them. Understanding state machines is essential for any character animation system.

## What is a State Machine?

A State Machine is a graph inside the AnimGraph that:
- Contains **States** (each with its own animation logic)
- Defines **Transitions** between states (with conditions)
- Automatically evaluates the active state and blends during transitions

Think of it as a flowchart: "If the character is on the ground and moving, play walk animation. If they jump, switch to jump animation."

## Core Components

### States
Each state contains a sub-graph with animation nodes:
- A single Animation Sequence
- A Blend Space Player
- A Blend Nodes (multiple animations blended)
- Or any AnimGraph node combination

### Transitions
Arrows connecting states that define:
- **Transition Rule** — A boolean condition that must be true
- **Blend Time** — How long to crossfade between states
- **Blend Logic** — Linear, cubic, custom curve

### Conduit
A transition-only node (no animation) used for branching:
- Multiple transitions enter, one or more exit
- Useful for shared logic (e.g., "Is In Air?" → branches to Jump or Fall)

## Step-by-Step: Building a Locomotion State Machine

### Step 1: Open AnimGraph and Add State Machine

1. Open your Animation Blueprint (`ABP_Character`)
2. Go to the **AnimGraph** tab
3. Right-click → Add State Machine → Name it "Locomotion"
4. Connect the State Machine output to the **Output Pose** node

### Step 2: Create States

Double-click the State Machine to enter it:

**State 1: Idle**
- Add an Animation Sequence Player node
- Set to your Idle animation
- Loop: Enabled

**State 2: Locomotion**
- Add a Blend Space Player node
- Set to your locomotion blend space (BS_Locomotion)
- Feed `Speed` variable to the blend input
- (For 2D: feed `Speed` and `Direction`)

**State 3: Jump**
- Add an Animation Sequence Player (or multiple for start/fall/land)
- Set to Jump_Start animation
- Can chain: Jump_Start → Jump_Fall → Jump_Land within the state

### Step 3: Define Transitions

Draw arrows between states:

**Idle → Locomotion**
```
Transition Rule: Speed > 10.0
Blend Time: 0.2 seconds
Blend Mode: Linear
```

**Locomotion → Idle**
```
Transition Rule: Speed <= 10.0
Blend Time: 0.2 seconds
```

**Locomotion → Jump**
```
Transition Rule: IsInAir == true
Blend Time: 0.1 seconds
```

**Jump → Locomotion** (or Idle)
```
Transition Rule: IsInAir == false
Blend Time: 0.2 seconds
```

**Idle → Jump**
```
Transition Rule: IsInAir == true
Blend Time: 0.1 seconds
```

### Step 4: Advanced State — Jump with Sub-states

Inside the Jump state, create a nested state machine:

```
Jump State Machine:
  ├── Jump_Start → Plays Jump_Start animation
  │     Auto transition after: animation length
  │
  ├── Jump_Fall → Plays Jump_Fall loop
  │     Transition to Land: IsInAir == false
  │
  └── Jump_Land → Plays Jump_Land animation
        Auto transition after: animation length → exit state machine
```

### Step 5: Using Variables from Character

In the AnimBP Event Graph:

```blueprint
Event Blueprint Update Animation:
  → Try Get Pawn Owner (cast to your character class)
  → Get Velocity → Vector Length → SET Speed
  → Get Character Movement → Is Falling → SET IsInAir
  → Calculate Direction (Velocity, Actor Rotation) → SET Direction
```

### Step 6: State Machine Best Practices

1. **Keep states focused** — one state = one behavioral concept
2. **Use conduits for shared conditions** — avoids duplicating transition rules
3. **Set appropriate blend times:**
   - Locomotion transitions: 0.15–0.25s
   - Jump transitions: 0.1–0.15s (snappier)
   - Combat transitions: 0.1s or instant
4. **Use "Automatic Rule"** for timed transitions (e.g., after an animation finishes)
5. **Preview in editor** — use the AnimBP preview panel to test states

## Transition Rule Expressions

Common transition conditions:

| Transition | Condition |
|-----------|-----------|
| Idle → Walk | `Speed > 10` |
| Walk → Idle | `Speed <= 10` |
| Any → Jump | `IsInAir == true` |
| Jump → Any | `IsInAir == false` |
| Walk → Sprint | `Speed > 300` |
| Any → Crouch | `IsCrouching == true` |
| Idle → Attack | `IsAttacking == true` |
| Attack → Idle | `IsAttacking == false AND AttackAnimDone` |

## Using Blend Nodes Inside States

Instead of a single animation, states can contain complex logic:

```
Locomotion State Internal Graph:
  [Blend Space Player: BS_Locomotion]
       ↓
  [Layered Blend per Bone] ← [Aim Offset: Upper body aiming]
       ↓
  [Slot 'DefaultSlot'] ← [Montage Layer: Attack animations]
       ↓
  [Output Pose of this state]
```

## Debugging State Machines

1. **Preview in Editor:** Open AnimBP → click states to preview
2. **Play in Editor:** Watch the active state highlight during gameplay
3. **Print variables:** Add Print String in Event Graph to verify Speed/IsInAir values
4. **Animation Notifies:** Use Notifies to trigger events at specific animation frames

## Related Resources

- [Ryan Laley AnimBP Series](https://www.youtube.com/watch?v=etRZu5UG_S0)
- [Blend Space Tutorial](https://www.youtube.com/watch?v=0Ab_MeAh6_k)
- [Epic's Animation Documentation](https://dev.epicgames.com/documentation/unreal-engine/animation-blueprints-in-unreal-engine)


---

## Related

- ← Previous: [[01_Animation_Blueprint_Blendspaces]]
- → Next: [[03_Jump_Turn_In_Place]]
- 📚 Series: [[_MOC_UE5_Animation]]
