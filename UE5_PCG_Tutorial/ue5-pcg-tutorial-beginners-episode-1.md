---
title: "UE5 PCG Tutorial for Beginners – Episode 1: Step-by-Step Guide to Procedural Generation"
source: "https://www.youtube.com/watch?v=O6xDcOylcCs"
video_id: "O6xDcOylcCs"
type: "youtube-summary"
series: "UE5 PCG Tutorial"
episode: 0
tags: [ue5, tutorial, pcg, procedural, beginner, gamedev]
---

# UE5 PCG Tutorial for Beginners – Episode 1

**Channel:** PolyBoost | **Published:** 2025-05-16 | **Length:** 25:18

## Overview
The foundational episode of the beginner PCG series. Covers UE5's PCG framework fundamentals for automatically generating game environments based on rules and input data. Goal: build a procedural forest environment.

## Prerequisites
- Create a **Third Person** project in UE5 (5.5.4 used in tutorial).
- Enable **PCG** and **PCG Geometry Script** plugins. Restart editor.

## Core PCG Nodes

### 1. Get Landscape Data Node
- Starting point — reads the entire landscape and generates points on its surface.
- **Debug**: Press `D` to visualize points, `E` to activate/deactivate a node.

### 2. Surface Sampler Node
- Generates points for asset placement across a surface.
- **Key Parameters**: Point Extents, Points per Square Meter (density), Looseness (randomness).
- **Warning**: Avoid `Unbounded` — can crash by generating points over the entire landscape.

### 3. Static Mesh Spawner Node
- Assigns 3D mesh to each point via Mesh Selector entries.

### 4. Transform Points Node
- Adds variation: position (Offset), rotation, and scale randomization.

### 5. Self Pruning Node
- Removes points too close together, creating gaps between assets.

### 6. Density Filter Node
- Lower/Upper Bound filtering for sparse distributions of high-poly assets.

### 7. Bound Modifier Node
- Adjusts collision/volume of points without changing visual mesh size.
- Enlarges points to force greater pruning distance.

### 8. Difference Node
- Subtracts one layer's points from another to prevent clipping.

## Building the Forest

### Layer 1: Simple Trees
`Get Landscape Data` → `Surface Sampler` → `Static Mesh Spawner` → `Transform Points`

### Layer 2: Detailed Trees
Second `Surface Sampler` (lower density) → `Density Filter` → `Static Mesh Spawner` → `Bound Modifier` → `Self Pruning`

### Combine Layers
`Difference` node subtracts high-poly tree points from simple tree points.

### Layer 3: Ground Cover
Dense `Surface Sampler` for grass → `Static Mesh Spawner`.

## Key Takeaways
- Self Pruning should come after transforms/bound modifiers that expand point volumes.
- High-poly assets require lower point densities for performance.
- Difference node is essential for multi-layer environments.

---

## Related

- ← Previous: [[ue-5-7-pcg-episode-1-forest-path-splines]]
- → Next: [[ue5-pcg-tutorial-beginners-episode-2-full]]
- 📚 Series: [[_MOC_UE5_PCG_Tutorial]]
