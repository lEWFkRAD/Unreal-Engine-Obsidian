---
title: "Unreal Engine 5 - Ground Slash VFX - Niagara Tutorial"
source: "https://www.youtube.com/watch?v=EXWwZ4F_reA"
video_id: "EXWwZ4F_reA"
type: "youtube-summary"
series: "UE5 Niagara"
episode: 2
tags: [ue5, niagara, vfx, ground-slash, mesh-particles, blender]
---

# Ground Slash VFX - Niagara Tutorial

**Creator:** Gabriel Aguiar Prod. (VFX specialist for games)
**Duration:** 20:40 | **Published:** VFX-focused channel

## Overview

This tutorial demonstrates how to create a Ground Slash VFX effect using Niagara in Unreal Engine 5. The effect uses Blender for mesh creation and Niagara for the particle system. This is a practical, game-ready VFX tutorial.

## Key Concepts

### Mesh-Based Particles
- Unlike sprite particles (2D quads), mesh particles use 3D geometry
- Mesh Renderers replace Sprite Renderers for 3D effects
- Custom meshes created in Blender give unique visual identity to VFX

### Ground Slash Effect Components
A typical ground slash VFX consists of multiple emitters:
1. **Main Slash Mesh** - the core 3D slash shape
2. **Ground Dust/Debris** - particles kicked up from the ground
3. **Trail/Glow** - energy trail following the slash
4. **Impact Sparks** - small particles at the point of impact

## Implementation Steps

### 1. Create the Slash Mesh in Blender
- Model a curved, elongated shape (like a crescent or arc)
- UV unwrap for proper material mapping
- Export as FBX and import into UE5
- Create a material with emissive properties and transparency

### 2. Set Up the Niagara System
- Create a new Niagara System (NS_GroundSlash)
- Add multiple emitters for different visual layers

### 3. Main Slash Emitter (Mesh Renderer)
- Change Renderer from Sprite to Mesh Renderer
- Assign your imported slash mesh
- Configure Material with:
  - Emissive color (blue, purple, or energy-colored)
  - Opacity/Transparency for fade effect
  - Panning UVs for animated energy flow

### 4. Configure Particle Behavior
- **Spawn**: Burst at creation (not continuous)
- **Lifetime**: Short (0.5 to 1.5 seconds)
- **Velocity**: Forward direction matching slash direction
- **Scale**: Start large, shrink over lifetime
- **Color**: Fade from bright to transparent

### 5. Dust/Debris Emitter (Sprite)
- Use sprite renderer with smoke/dust material
- Spawn at the ground level beneath the slash
- Velocity: upward and outward from slash center
- Gravity: slight downward pull
- Drag: slow particles down over time

### 6. Trail Emitter
- Use Ribbon Renderer for smooth trails
- Spawn particles along the slash path
- Width: narrow, tapering from start to end
- Color: brighter in center, fading at edges

### 7. Sparks Emitter
- Small, fast particles
- High initial velocity with random spread
- Short lifetime (0.2 to 0.5 seconds)
- Gravity-affected for natural arc
- Bright emissive color

### 8. Assembly and Timing
- Stagger emitter spawns for visual flow
- Slash mesh appears first
- Dust and sparks follow immediately
- Trail fades last
- Use Dynamic Material Parameters for runtime control

## Niagara Module Tips
- Use Curl Noise for organic, turbulent motion
- Shape Location modules control spawn area (Box, Sphere, Cylinder)
- Add Drag module to slow particles naturally
- Use Color module with curves for smooth fade transitions
- Conform to ground plane using Collision module

## Material Setup
- Create M_Slash_Glow material:
  - Base Color: dark or transparent
  - Emissive: bright color (multiply by scalar parameter)
  - Opacity: use a gradient texture for soft edges
  - Material Domain: Surface, Blend Mode: Translucent

## Resources
- Gabriel Aguiar Patreon (project files): https://patreon.com/GabrielAguiarProd
- Discord: https://discord.gg/AN7CrC3QBB
- Related tutorials by Gabriel Aguiar:
  - Slash Attack VFX: https://www.youtube.com/watch?v=meig8T9uWNc
  - Stylized Explosion VFX Course: https://www.youtube.com/watch?v=tZKiAZYeF4Q
  - Vertical Beam VFX: https://www.youtube.com/watch?v=NbbFytz-JDk


---

## Related

- ← Previous: [[01_Introduction_to_Niagara]]
- → Next: [[03_Smoke_Particles]]
- 📚 Series: [[_MOC_UE5_Niagara]]
