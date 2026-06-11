---
title: "Introduction To Niagara - Unreal Engine 5 Tutorial"
source: "https://www.youtube.com/watch?v=hnUQiwJweeg"
video_id: "hnUQiwJweeg"
type: "youtube-summary"
series: "UE5 Niagara"
episode: 1
tags: [ue5, niagara, particles, vfx, sprite-renderer, emitter]
---

# Introduction To Niagara - Unreal Engine 5 Tutorial

**Creator:** Unreal University (Authorized Unreal Engine Instructor)
**Duration:** 13:40 | **Views:** 18K | **Published:** October 27, 2025

## Overview

Niagara is Unreal Engine's modern particle effect system, replacing the legacy Cascade system. This tutorial covers all the fundamentals: the interface, the five main components, sprite renderers, emitter configuration, particle attributes, and velocity modules.

## Video Chapters

| Timestamp | Topic |
|-----------|-------|
| 0:00 | Introduction to Niagara |
| 0:26 | Creating a new blank Niagara system |
| 0:52 | Niagara interface panels and timeline |
| 2:14 | Five main Niagara components |
| 2:46 | Setting up sprite renderer |
| 3:00 | Emitter update with spawn rate module |
| 3:32 | Particle spawn settings and color |
| 4:49 | Particle state module for lifetime |
| 5:36 | Velocity modules with various modes |
| 9:55 | Particle attributes (size, rotation) |

## Implementation Steps

### 1. Create a Niagara System
- Right-click in Content Browser > FX > Niagara System
- Select "New system from selected emitters"
- Choose a template (e.g., Simple Sprite Burst) or start blank
- Name it descriptively (e.g., NS_MyEffect)

### 2. Understand the Five Main Components
Every Niagara system is built from these building blocks:

1. **System** - The top-level container; controls global settings
2. **Emitter** - A single particle source within the system
3. **Module** - Individual operations (spawn rate, velocity, color, etc.)
4. **Renderer** - How particles are displayed (Sprites, Meshes, Ribbons, Lights)
5. **Parameters** - Data that flows between modules

### 3. Configure the Sprite Renderer
- In System Overview, select the Sprite Renderer
- Set Material to your particle material (e.g., M_smoke_subuv from Starter Content)
- Sub Image Size: X=8, Y=8 (for sprite sheet grids)
- Enable Sub UV Blending for animated sprites

### 4. Set Up Emitter Update
- Open the Emitter Update group
- Add a Spawn Rate module
- Set Spawn Rate (e.g., 50 particles per second)
- In Emitter State:
  - Life Cycle Mode: Self
  - Loop Behavior: Infinite

### 5. Configure Particle Spawn
In the Particle Spawn group:
- **Initialize Particle** module:
  - Lifetime: Random Range Float (2.0 to 3.0)
  - Sprite Size: Random Range Float (75.0 to 200.0)
  - Sprite Rotation: Random Range Float (0.25 to 0.5)
- **Add Color** module: set RGBA values for your effect
- **Sphere Location** module: Sphere Radius = 64

### 6. Add Velocity
- Add Velocity module to Particle Spawn
- Use Random Range Vector for varied movement:
  - Minimum: X=0, Y=0, Z=50
  - Maximum: X=1, Y=1, Z=200
- Velocity modes: Absolute, Relative, Additive

### 7. Particle State and Update
- Add Particle State module to control lifetime
- In Particle Update group:
  - Add modules that affect particles over time
  - Example: Acceleration Force (Z=500 for upward smoke)

### 8. Preview and Save
- Drag the Niagara system into the Level to preview
- Save the emitter as its own asset (Gear icon > Create Asset From This)
- Save the system

## Key Concepts
- **Emitter Update**: runs once per emitter per frame (spawn logic)
- **Particle Spawn**: runs once per particle at creation
- **Particle Update**: runs every frame per particle (lifetime behavior)
- **Render**: defines visual representation
- Use Random Range for variation to make effects look natural

## Resources
- Unreal University: https://www.unreal-university.io
- Free Beginner Course: https://www.unreal-university.io/freecourse
- Epic Niagara Docs: https://dev.epicgames.com/documentation/unreal-engine/create-a-sprite-particle-effect-in-niagara


---

## Related

- → Next: [[02_Ground_Slash_VFX]]
- 📚 Series: [[_MOC_UE5_Niagara]]
