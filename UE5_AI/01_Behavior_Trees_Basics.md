---
title: "Smart Enemy AI - Part 1: Behavior Trees"
source: "https://www.youtube.com/watch?v=-t3PbGRazKg"
video_id: "-t3PbGRazKg"
type: "youtube-summary"
series: "UE5 AI"
episode: 1
tags: [ue5, ai, behavior-trees, blackboard, blueprint, enemy-ai]
---

# Smart Enemy AI - Part 1: Behavior Trees

**Creator:** Ali Elzoheiry (Unreal Authorized Instructor)
**Duration:** 45:30 | **Views:** 537K+ | **Published:** May 30, 2023
**Series:** Part 1 of 23-video "Smart Enemy AI Tutorial Series"

## Overview

This tutorial covers the fundamentals of Behavior Trees and Blackboards in Unreal Engine 5. You will learn how to set up an AI Controller, create custom tasks and decorators, and build a behavior tree that makes an enemy chase and attack the player.

## Key Concepts

### Behavior Trees vs State Machines
- Behavior Trees are a visual, hierarchical way to define AI logic
- They use a tree structure with Selector, Sequence, and Task nodes
- More scalable and debuggable than traditional state machines

### Blackboard
- A key-value store that acts as the AI's "brain"
- Keys can be Objects (actors), Booleans, Vectors, etc.
- Behavior Tree tasks read from and write to the Blackboard

### Core Node Types
| Node | Purpose |
|------|---------|
| **Selector** | Tries children left-to-right, stops at first success (priority) |
| **Sequence** | Executes children left-to-right, fails on first failure |
| **Task** | Atomic actions (Move To, Wait, custom tasks) |
| **Decorator** | Conditional checks on branches |
| **Service** | Background logic that runs periodically |

## Implementation Steps

### 1. Enemy and Player Setup
- Create an Enemy Character Blueprint (copy from third-person character)
- Set Character Movement > Max Walk Speed to 120
- Create an AI Controller Blueprint (based on AIController)
- Set the Enemy Character's AI Controller Class to your new controller
- Add a NavMeshBoundsVolume to the level and scale it to cover walkable areas

### 2. Create Behavior Tree and Blackboard
- Right-click Content Browser > Artificial Intelligence > Behavior Tree (name: BT_Enemy)
- Right-click Content Browser > Artificial Intelligence > Blackboard (name: BB_Enemy)
- Add keys to Blackboard:
  - EnemyActor (Object, base class Actor)
  - HasLineOfSight (Bool)
  - PatrolLocation (Vector)
- Set the Behavior Tree's Blackboard asset to BB_Enemy

### 3. Build the Behavior Tree Structure
```
Root
  -> Selector (AI Root)
       -> Sequence (Chase Player) [higher priority]
            Decorator: HasLineOfSight == true
            Rotate to Face BBEntry (EnemyActor)
            Custom Task: BTT_ChasePlayer
            Move To (EnemyActor)
       -> Sequence (Patrol) [lower priority]
            Custom Task: BTT_FindRandomPatrol
            Move To (PatrolLocation)
            Wait (4.0 +/- 1.0 seconds)
```

### 4. Create Custom Task: BTT_ChasePlayer
- Right-click Content Browser > Blueprint Class > BTTaskNode
- In Event Receive Execute AI:
  1. Cast to Enemy_Character
  2. Update Walk Speed to 500.0 (chase speed)
  3. Finish Execute with Success
- Add an editable variable ChaseSpeed for tuning

### 5. Create Custom Task: BTT_FindRandomPatrol
- In Event Receive Execute AI:
  1. Cast to Enemy_Character
  2. Update Walk Speed to 125.0 (patrol speed)
  3. Use GetRandomReachablePointInRadius (Radius: 1000)
  4. Set Blackboard Value for PatrolLocation
  5. Finish Execute with Success
  6. Fallback: use current location if no point found

### 6. AI Controller Setup
- In Event On Possess: Run Behavior Tree (BT_Enemy)
- Add AIPerceptionComponent for sight detection

### 7. Create Decorator
- Add a Blackboard Decorator to the "Chase Player" branch
- Observer Aborts: Both
- Blackboard Key: HasLineOfSight
- This causes the tree to abort patrol when the player is spotted

## Tips and Best Practices
- Use naming prefixes: BTT_ for tasks, BTS_ for services, BB_ for blackboards
- Use instance-editable variables on tasks for easy tuning in the editor
- Toggle NavMesh visibility with the P key to verify coverage
- Services are better than tasks for recurring checks (no Finish Execute needed)

## Series Continuation
- Part 2: Patrolling and States (199K views)
- Part 3: Perception (149K views)
- Part 4: EQS (147K views)
- Part 5: Enemy Types (93K views)
- Part 6: Ranged Enemy Behavior (84K views)

## Resources
- Full Series Playlist: https://www.youtube.com/playlist?list=PLNwKK6OwH7eW1n49TW6-FmiZhqRn97cRy
- Epic BT Quick Start Guide: https://dev.epicgames.com/documentation/unreal-engine/behavior-tree-in-unreal-engine---quick-start-guide
- Project Files (Patreon): https://www.patreon.com/Alizoh


---

## Related

- → Next: [[02_Simple_Behavior_Tree]]
- 📚 Series: [[_MOC_UE5_AI]]
