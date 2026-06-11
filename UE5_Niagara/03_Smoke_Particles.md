---
title: "Making Smoke Particles In Unreal Engine 5 - Niagara Tutorial"
source: "https://www.youtube.com/watch?v=omDpFnDi9fs"
video_id: "omDpFnDi9fs"
type: "youtube-summary"
series: "UE5 Niagara"
episode: 3
tags: [ue5, niagara, vfx, smoke, particles, environment, sprite]
---

# Making Smoke Particles In Unreal Engine 5

**Creator:** Peyton Varney (Senior Environment Artist)
**Duration:** 28:50 | **Published:** Environment art focused channel

## Overview

This tutorial shows how to set up a simple smoke particle effect using Niagara in UE5. The smoke effect is designed for use in environments (campfires, chimneys, industrial areas, etc.) and covers the complete workflow from system creation to final polish.

## Key Concepts

### Smoke Particle Characteristics
- Slow, rising movement with drift
- Gradual size increase (scale over life)
- Fade in at start, fade out at end
- Turbulent, organic motion (not linear)
- Gray/dark colors with transparency

### Niagara Workflow for Smoke
1. Create the Niagara System
2. Set up Sprite Renderer with smoke material
3. Configure spawn rate and particle lifetime
4. Add velocity for upward movement
5. Apply forces for turbulence
6. Set color/opacity curves for natural fade

## Implementation Steps

### 1. Create the Niagara System
- Content Browser > Right-click > FX > Niagara System
- Select "New system from selected emitters" > Simple Sprite Burst
- Rename to NS_Smoke or similar
- Open in Niagara Editor

### 2. Configure the Sprite Renderer
- Select the Sprite Renderer in System Overview
- Set Material: use a smoke material (M_smoke_subuv from Starter Content, or create custom)
- For custom smoke material:
  - Texture: soft, cloud-like alpha map
  - Blend Mode: Translucent
  - Two Sided: enabled
  - Panning UVs for animated smoke (optional)

### 3. Emitter Update Settings
- Delete the default Spawn Burst module
- Add Spawn Rate module:
  - Spawn Rate: 20-50 particles/second (depends on density needed)
- Emitter State:
  - Life Cycle Mode: Self
  - Loop Behavior: Infinite

### 4. Particle Spawn Configuration
**Initialize Particle module:**
- Lifetime: Random Range Float (2.0 to 4.0 seconds)
- Sprite Size: Random Range Float (50.0 to 150.0)
- Sprite Rotation: Random Range Float (0.0 to 1.0)
- Color: start with gray (R=0.3, G=0.3, B=0.3, A=0.5)

**Spawn Location:**
- Use Box Location or Cylinder Location for spawn area
- Box: small area (50x50x10) for chimney-like sources
- Or Point Location for single-source smoke

**Add Velocity:**
- Z velocity: 100-200 (upward)
- X/Y: small random range (-10 to 10) for horizontal drift

### 5. Particle Update (Runtime Behavior)
These modules affect particles every frame during their lifetime:

**Scale Sprite Size:**
- Use a curve: start at 1.0, end at 2.0-3.0
- This makes smoke expand as it rises

**Color Over Life:**
- Start: mostly opaque gray
- End: fully transparent
- Use an alpha curve that fades from 0.5 to 0.0

**Drag:**
- Drag coefficient: 0.5-1.0
- Slows particles down naturally over time

**Curl Noise Force:**
- Strength: 50-100
- Adds organic, turbulent motion
- Frequency: controls how "wiggly" the motion is
- This is what makes smoke look natural vs. linear

**Gravity:**
- Very slight upward or neutral (smoke rises)
- Or use Acceleration Force with Z=100-300 upward

### 6. Polish and Refinement
- Adjust spawn rate until density looks right
- Tweak velocity and drag for desired speed
- Fine-tune curl noise for natural turbulence
- Add slight wind effect with a directional force
- Use SubUV animation if using a sprite sheet

### 7. Placement in Level
- Drag NS_Smoke into the level at the desired location
- Scale the system if needed
- For campfire: place slightly above the fire source
- For chimney: place at the chimney top
- Consider adding a light source below for fire-lit smoke

## Material Tips for Smoke
- Use soft, organic textures (not sharp-edged)
- Alpha maps should have feathered edges
- Consider using Flipbook/SubUV for animated smoke frames
- Brightness and contrast adjustments can enhance realism
- Lit smoke: enable "Receive Decals" and use dynamic lighting

## Performance Considerations
- Limit particle count for mobile (under 100 active particles)
- Use LOD (Level of Detail) to reduce particles at distance
- Disable collision on smoke particles
- Use GPU simulation for large particle counts
- Screen-space bounds help cull off-screen particles

## Resources
- Peyton Varney Channel: https://www.youtube.com/@PeytonVarney
- CGMA Environment Art Course (by Peyton)
- Epic Niagara Documentation: https://dev.epicgames.com/documentation/unreal-engine/niagara-effects


---

## Related

- ← Previous: [[02_Ground_Slash_VFX]]
- 📚 Series: [[_MOC_UE5_Niagara]]
