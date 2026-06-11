---
title: "UE5 PCG Tutorial for Beginners – Episode 2 (Full Tutorial)"
source: "https://www.youtube.com/watch?v=RIfY3CjtSnA"
video_id: "RIfY3CjtSnA"
type: "youtube-summary"
series: "UE5 PCG Tutorial"
episode: 0
tags: [ue5, tutorial, pcg, procedural, beginner, gamedev]
---

# UE5 PCG Tutorial for Beginners – Episode 2 (Full Tutorial)

**Channel:** PolyBoost | **Published:** 2025-05-23 | **Length:** 22:33

## Overview
The full-length version of Episode 2 in the beginner PCG series. Covers adding environmental details, refining point distributions, and troubleshooting common PCG issues in UE5.

## Key Steps

### 1. Cleaning Areas Around Trees
- Remove grass points embedded within tree meshes.
- Use **Difference** operation + **Bounds Modifier** to clear space around smaller trees.

### 2. Create Points Grid Node
- Generates uniform grid of points within defined area.
- Connect to **Copy Points** node: source = grid, target = tree positions.
- Use **Absolute** method and **Transform Points** for uniform sizing.

### 3. Density Noise Node
- Introduces natural randomness to point distributions for organic appearance.
- Apply after grid creation, then **Density Filter** to reduce point count.

### 4. Landscape Sculpt & Troubleshooting
- **Issue**: Trees deform and follow landscape contours.
- **Fix**: Enable **Absolute Rotation** in Transform Points node.

### 5. Projection Node
- Projects points onto target surface (landscape, mesh).
- **Critical**: Perform projection **before** rotation transforms.

### 6. Density Ramp Node
- Opposite of Density Noise — controls overlap between elements.
- Use on one element's points, then **Difference** to separate assets.

## Workflow Summary
1. Clean existing assets with Difference + Bounds.
2. Add detail grids with Create Points Grid → Copy Points.
3. Introduce randomness: Density Noise → Density Filter.
4. Fix placement with Projection node.
5. Control rotation with Transform Points (Absolute Rotation if needed).
6. Add new elements with Static Mesh Spawners.
7. Prevent overlap with Density Ramp → Difference.

## Key Takeaways
- Projection must happen before rotation in the PCG graph.
- Density Ramp + Difference = clean separation between asset types.
- Absolute Rotation prevents terrain-following deformation on trees.

---

## Related

- ← Previous: [[ue5-pcg-tutorial-beginners-episode-1]]
- → Next: [[unreal-5-7-pcg-episode-2-linear-grammar-tool]]
- 📚 Series: [[_MOC_UE5_PCG_Tutorial]]
