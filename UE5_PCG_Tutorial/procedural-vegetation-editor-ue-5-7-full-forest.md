---
title: "Procedural Vegetation Editor in UE 5.7 | Building a Full Forest with PCG"
source: "https://www.youtube.com/watch?v=pakeUlNWYZo"
video_id: "pakeUlNWYZo"
type: "youtube-summary"
series: "UE5 PCG Tutorial"
episode: 0
tags: [ue5, tutorial, pcg, procedural, vegetation, forest, gamedev]
---

# Procedural Vegetation Editor in UE 5.7: Building a Full Forest with PCG

**Channel:** PolyBoost | **Published:** 2025-11-17 | **Length:** 16:27

## Overview
A tutorial on using UE5.7's **Procedural Vegetation Editor** and **PCG** tools to create a dynamic, data-driven forest. Aimed at environment artists and technical designers building large open worlds.

## Prerequisites
- Enable `Procedural Vegetation Editor` and `Nanite Foliage` plugins.
- Explore the example: `procedural vegetation editor maps` > `Zoo` from the plugin folder.

## Procedural Vegetation Editor (Tree Creation)
Open via `Foliage Menu` > `Procedural Vegetation`. Uses a node-based graph system.

### Core Node Groups
- **Crown**: Controls tree size and shape (Radius setting).
- **Gravity**: Applies directional pull to branches.
- **Phototropism**: Bends branches toward simulated light.
- **Build 3D Mesh**: Critical for optimization – reduces mesh density.
- **Foliage Pallet**: Assigns branch and leaf types.
- **Foliage Distributor**: Controls quantity and variation.

### Output Options
- **Static Mesh**: For PCG placement.
- **Skeletal Mesh**: Creates skeletal mesh, skeleton, and physics asset. Allows animation pose adjustments.

### Blueprint for Wind Animation
1. Create Blueprint, add `Instanced Skeletal Mesh Component`.
2. Set tree as `Skeletal Mesh`.
3. Add `Wind Transform Provider` component for wind interaction.

## Building the Forest with PCG
1. Create PCG Graph and Spline Blueprint with tag.
2. `Get Spline Data` (World Actor mode) → `Spline Sampler` (Interior mode).
3. Refine with `Density Noise` and `Density Filter`.
4. **Multiple Tree Types**: Use `Spawn Actor` node + `Transform` for variation.
5. **Density Variations**: Copy setup and invert `Density Filter` for different zones.
6. **Difference Node**: Subtract points to create zones for additional varieties.
7. Enable `Unbounded Spline Sampler` to spawn trees beyond PCG boundary.

## Key Outcomes
- Dynamic, data-driven environment that updates based on terrain, slopes, masks, and biome rules.
- Full customization from individual tree meshes to large-scale ecosystem placement.
- Ideal for efficiently populating large open worlds.

---

## Related

- ← Previous: [[procedural-road-spline-sampler-ue-5-5]]
- → Next: [[procedural-wwii-battlefield-full-tutorial]]
- 📚 Series: [[_MOC_UE5_PCG_Tutorial]]
