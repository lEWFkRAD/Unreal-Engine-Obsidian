---
title: "How to Make a Simple Behavior Tree in UE5 - Advanced AI"
source: "https://www.youtube.com/watch?v=QJuaB2V79mU"
video_id: "QJuaB2V79mU"
type: "youtube-summary"
series: "UE5 AI"
episode: 2
tags: [ue5, ai, behavior-trees, blueprint, enemy-ai, pawn-sensing]
---

# How to Make a Simple Behavior Tree in UE5 - Advanced AI

**Creator:** Gorka Games (7+ years Unity/UE experience)
**Duration:** 20:46 | **Views:** 214K | **Published:** December 25, 2022

## Overview

A quick and concise tutorial on creating basic enemy AI using Behavior Trees in Unreal Engine 5. This covers the essentials of setting up a behavior tree, creating the necessary blueprints, handling rotation, decorators, and pawn sensing -- all in under 21 minutes.

## Video Chapters

| Timestamp | Topic |
|-----------|-------|
| 0:00 | Intro |
| 1:10 | Behavior Tree setup |
| 7:30 | Blueprint creation |
| 13:40 | Rotation handling |
| 13:45 | Changing player target |
| 14:55 | Decorators |
| 17:53 | Pawn Sensing |
| 18:32 | Casting in tasks |
| 19:43 | Final play test |

## Implementation Steps

### 1. Create the Behavior Tree Asset
- Content Browser > Right-click > Artificial Intelligence > Behavior Tree
- The tree structure uses a Root node that runs its children in order

### 2. AI Controller Blueprint
- Create a new Blueprint based on AIController
- This controller will possess your enemy character and run the behavior tree
- In the Event Graph, use Event On Possess to Run Behavior Tree

### 3. Behavior Tree Structure
- Use a Selector node as the main branch
- Add a Sequence for "Chase Player" behavior
- Add tasks: Move To (targeting the player via Blackboard key)
- The tree evaluates top-down; higher priority branches check first

### 4. Handling Rotation
- In the character blueprint, enable "Use Controller Rotation Yaw"
- Alternatively, use "Rotate to Face BB Entry" task in the behavior tree
- This ensures the enemy smoothly turns toward the player while chasing

### 5. Decorators
- Add a Blackboard Decorator to the Chase branch
- Set it to check if the player key is set (Is Set = true)
- This prevents chasing when no player has been detected
- Observer Aborts: set to "Both" so the tree can interrupt other branches

### 6. Pawn Sensing
- Add a PawnSensing component to the enemy character
- Configure Sight Radius and Peripheral Vision Angle
- On See Pawn event:
  1. Cast to your player character type
  2. Set the Blackboard key for the player actor
- This triggers the behavior tree decorator to activate the chase branch

### 7. Casting in Tasks
- Custom BTTaskNode blueprints need to cast the Controlled Pawn
- Use Get Controlled Pawn -> Cast to your enemy character class
- This gives access to character-specific variables and functions

## Key Takeaways
- Behavior Trees provide a clean, visual way to organize AI logic
- PawnSensing is a simpler alternative to the full AI Perception system
- Decorators control when branches of the tree are active
- Always set up NavMesh in your level for pathfinding to work
- Keep behavior tree structure simple; add complexity incrementally

## Related Tutorials by Gorka Games
- Simple Enemy AI (easier approach): https://www.youtube.com/watch?v=xm-7m5Fw1HU
- Simple Blendspace: https://www.youtube.com/watch?v=DST2bMbRxEQ
- Animal AI: https://www.youtube.com/watch?v=yYfhsJNL5QE
- State Trees (newer approach): check the Gorka Games channel

## Resources
- Patreon (project files): https://bit.ly/GorkaGames_Patreon
- Discord: https://discord.com/invite/7qfQTQu5yG
- Game on Steam (Bromeliad): https://bit.ly/3rVlXU1


---

## Related

- ← Previous: [[01_Behavior_Trees_Basics]]
- → Next: [[03_AI_Perception_System]]
- 📚 Series: [[_MOC_UE5_AI]]
