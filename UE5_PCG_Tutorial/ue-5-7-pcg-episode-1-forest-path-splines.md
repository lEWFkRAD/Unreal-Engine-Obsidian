---
title: "UE 5.7 PCG – Building a Forest Path with Splines (Episode 1)"
source: "https://www.youtube.com/watch?v=7uddwTRs9Hk"
video_id: "7uddwTRs9Hk"
type: "youtube-summary"
series: "UE5 PCG Tutorial"
episode: 0
tags: [ue5, tutorial, pcg, procedural, splines, gamedev]
---

# UE 5.7 PCG: Building a Forest Path with Splines (Episode 1)

**Channel:** PolyBoost | **Published:** 2025-12-02 | **Length:** 22:31

## Overview
A foundational tutorial for creating a procedural forest walking path in UE5.7 using PCG tools and splines. Covers terrain sculpting, spline-based path definition, and PCG-driven mesh spawning.

## Key Workflow Steps

### 1. Setup
- Enable the **PCG plugin** in UE5.7.
- Sculpt a sloped path in the landscape.

### 2. Spline Fundamentals
- **Draw Mode**: Click and drag to create splines with gizmo control points.
- **Key Controls**: Count, Distance (overrides count), Start/End Offset, Max Random Offset & Seed for randomization.

### 3. Spawning Meshes Along Spline
- Assign mesh via **Static Mesh Spawner**.
- **Global Transform**: Rotates/moves/scales all spawned meshes at once. Absolute Global Rotation forces all meshes to face the same direction.
- **Random Transform**: Adds randomness for natural appearance.
- **Tip**: Use "Clear PCG Link" to preserve a spline if lost.

### 4. Creating Filled Regions (Draw Spline Surface)
- Creates an area/region instead of a line. PCG generates points within.
- **Points per Square Meter**: Controls mesh density.
- **Tree Placement**: Use Absolute Global Rotation + Random Transform + "Snap to Surface". Avoid "Align to Surface" for trees (rotates trunk with terrain angle).

### 5. Tree Integration
- Use **Procedural Vegetation Editor plugin** to create trees.
- Trees must be **exported as static meshes** for PCG placement. Animated trees require an actor.
- Use **LOD** for static meshes.

## Key Takeaways
- Foundation workflow: sculpt terrain → define paths with splines → spawn/regenerate meshes with PCG.
- Spline control + PCG's distance-based rules = powerful procedural environment generation.
- This is Episode 1; Episode 2 covers Linear Grammar Tool.

---

## Related

- ← Previous: [[realistic-searchlight-animation-in-ue5]]
- → Next: [[ue5-pcg-tutorial-beginners-episode-1]]
- 📚 Series: [[_MOC_UE5_PCG_Tutorial]]
