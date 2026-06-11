---
title: "Building a Procedural Farm in Unreal Engine 5 | PCG + Landscape Texture Patch Workflow"
source: "https://www.youtube.com/watch?v=eY8756U-Eak"
video_id: "eY8756U-Eak"
type: "youtube-summary"
series: "UE5 PCG Tutorial"
episode: 0
tags: [ue5, tutorial, pcg, procedural, landscape, farm, gamedev]
---

# Building a Procedural Farm in UE5: PCG + Landscape Texture Patch Workflow

**Channel:** PolyBoost | **Published:** 2025-11-01 | **Length:** 32:59

## Overview
A tutorial for creating a fully procedural farm in UE 5.6.1 using **PCG** and **Landscape Texture Patch**. Enables dynamic, data-driven environment generation with minimal manual effort.

> "A dynamic, data-driven farm environment that reacts to your landscape automatically — no manual painting needed!"

## Key Workflow Steps

### 1. Plugin & Initial Setup
- Enable **PCG** and **Landscape Texture Patch** plugins.
- Create a Blueprint named "patch" with a **Landscape Texture Patch** component.

### 2. Configuring Landscape Texture Patch
- Set to use a **texture asset**.
- Assign a **black-and-white texture** to define farm grooves/patterns.

### 3. PCG System & Spline Integration
- Create a **Spline Blueprint** with a spline component and custom tag.
- PCG Graph: `Get Spline Data` → `Spline Sampler` → `Spawn Actor` (patch Blueprint).
- Rotate patch on Z-axis to align texture lines with spline.
- Enable "Multiply" on Get Spline Data to support multiple splines.

### 4. Placing Objects (e.g., Pumpkins)
- `Static Mesh Spawner` + `Projection Node` + `Get Landscape Data` to snap to terrain.
- `Transform Points` for randomization. `Create Points Grid` for density.
- `Density Noise` + `Density Filter` for randomness. `Self-Pruning` to prevent overlap.

### 5. Scene Extension
- Wooden boards: Merge Quixel assets in Modeling Mode, attach to spline.
- Trees: Closed-loop spline to spawn trees inside defined area.

## Key Technical Insights
- PCG + Texture Patch synergy: spline-driven placement + texture-based terrain deformation.
- Patches adjustable outside PCG for iterative design.
- Scalable: add more spline paths or objects to enrich environment.

---

## Related

- ← Previous: [[building-narrative-military-camp-pcg]]
- → Next: [[cinematic-post-apocalyptic-street-p2-pcg]]
- 📚 Series: [[_MOC_UE5_PCG_Tutorial]]
