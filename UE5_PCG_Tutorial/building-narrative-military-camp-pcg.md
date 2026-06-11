---
title: "Building a Narrative Military Camp with PCG in Unreal Engine 5"
source: "https://www.youtube.com/watch?v=6bI6407BtjQ"
video_id: "6bI6407BtjQ"
type: "youtube-summary"
series: "UE5 PCG Tutorial"
episode: 0
tags: [ue5, tutorial, pcg, procedural, blender, marvelous-designer, gamedev]
---

# Building a Narrative Military Camp with PCG in Unreal Engine 5

**Channel:** PolyBoost | **Published:** 2026-03-08 | **Length:** 23:14

## Overview
A complete workflow for creating a procedural military camp environment using **PCG in UE5**, integrated with **Marvelous Designer** (cloth simulation) and **Blender** (mesh refinement) for asset creation.

## Key Workflow Steps

### 1. Creating the Camp Perimeter with Splines & Sandbags
- Use `Get Spline Data` node set to "all world actors" with a specified tag.
- Connect to `Spline Sampler` → `Static Mesh Spawner` for sandbags.
- **Critical**: If the mesh gizmo is not centered, PCG will have placement problems. Position pivot at center on import.
- Use `Transform Point` node to offset points upward on Z-axis for stacked layers.
- Enable **Closed Loop** in blueprint settings for enclosed perimeter.

### 2. Placing Content Inside the Camp
- Use `Spline Sampler` with mode set to **"On Interior"** for interior points.
- `Density Noise` and `Density Filter` control scatter density.
- **Self Healing** node prevents mesh overlap.
- **Central Tent Placement**: Manipulate density falloff curve (bright center, dark edges), apply Density Filter. Use Self Healing to ensure single instance.
- **Clear space around tent**: Duplicate central point, enlarge with `Bound Modifier`, subtract from interior points.

### 3. Creating the Military Tent Asset
- **Base Structure**: Rigid frame in Blender.
- **Cloth Simulation (Marvelous Designer)**: Use "Basic Curve Measure" and "Attach to Measure" for cloth-frame connections. Use W key for pins and manual tension control.
- **Mesh Refinement (Blender)**: Sculpt, connect vertices, create attachment points with holes and rope modeling.

### 4. Final Assembly
- Add variation with Transform Point node for random rotations/scales.
- Create entrance by moving central tent point and subtracting from sandbag perimeter.
- System is reusable — swap tent mesh with other assets to change camp function.

## Key Takeaways
- Mesh pivot/gizmo must be centered for accurate PCG placement.
- PCG's Self Healing node is essential for preventing mesh overlap.
- Combining Marvelous Designer cloth simulation with PCG procedural placement creates realistic narrative environments.

---

## Related

- ← Previous: [[auto-landscape-generator-in-ue5-7]]
- → Next: [[building-procedural-farm-pcg-landscape-texture-patch]]
- 📚 Series: [[_MOC_UE5_PCG_Tutorial]]
