---
title: "Layered Material Workflow"
source: "https://www.youtube.com/watch?v=CPxU3pYZtyY"
video_id: "CPxU3pYZtyY"
type: "youtube-summary"
series: "UE5 Materials"
episode: 2
tags: [ue5, materials, layered, substance]
---

# Layered Material Workflow

**Source:** https://www.youtube.com/watch?v=CPxU3pYZtyY

## Overview

- **Creator:** Daniel Cormino (2.73K subscribers)
- **Published:** November 6, 2024
- **Duration:** 1 hour 20 minutes
- **Focus:** Intermediate workflow for creating layered materials in UE5 using Material Layers
- **Prerequisite:** Familiarity with UE5 basics; does not explain fundamental features

## Content

### Video Structure

1. **Intro** (0:00)
2. **Scene Demonstration** (0:20) — Final result showcase
3. **Overview of Material Layers** (1:07) — Concept and structure
4. **Breakdown** (6:45) — Step-by-step node graph walkthrough

### What Are Layered Materials?

Layered materials allow you to stack multiple material functions (layers) and blend them using masks. Instead of one monolithic material, you build modular layers:

- **Base Layer:** Primary surface material (metal, concrete, wood)
- **Detail Layers:** Dirt, rust, paint, scratches, moss, water stains
- **Blend Layers:** Edge wear, grime accumulation, damage

Each layer is a **Material Function** that outputs standard PBR channels (Base Color, Normal, Roughness, Metallic, AO).

### Setting Up Material Layers

1. **Create Material Functions** for each layer:
   - `MF_BaseMetal` — clean metal surface
   - `MF_Rust` — rust/corrosion layer
   - `MF_Dirt` — dirt/grime layer
   - `MF_Scratches` — scratch damage layer

2. **Each Material Function outputs:**
   - Base Color (Vector3)
   - Normal (Vector3)
   - Roughness (Scalar)
   - Metallic (Scalar)
   - Ambient Occlusion (Scalar)

3. **Create a Material Layer Blend:**
   - Use **Material Layer Blend** assets to define how layers combine
   - Common blend nodes: `Lerp`, `HeightLerp`, `MaskedBlend`

4. **Assemble in the main Material:**
   - Use **Material Attribute Layers** node
   - Connect each layer function and blend functions
   - Feed masks from texture channels (R, G, B, A) or procedural noise

### Node Graph Approach

```
Material Layer Stack:
  Layer 0: MF_BaseMetal (full base coverage)
    ↓ Blend: HeightLerp (using R channel mask)
  Layer 1: MF_Rust (rust in crevices/edges)
    ↓ Blend: MaskedBlend (using G channel mask)
  Layer 2: MF_Dirt (dirt accumulation)
    ↓ Blend: Lerp (using B channel mask)
  Layer 3: MF_Scratches (surface scratches)
```

### Mask Creation with Substance Painter

- Export masks as RGBA texture channels for efficiency (4 masks in 1 texture)
- Paint masks directly in Substance Painter:
  - **R channel:** Rust mask
  - **G channel:** Dirt mask
  - **B channel:** Scratch mask
  - **A channel:** Paint/wear mask
- Use generators in Substance (e.g., Edge Wear, Dirt, Curvature) for initial mask generation, then hand-paint refinements

### Performance Considerations

**Important community critique:** This approach uses many texture samples (potentially 20+), which is expensive for real-time games.

Guidelines for texture sample budgets:
- **1-2 samples:** Mobile games
- **3-4 samples:** Very fast desktop/console
- **5-6 samples:** Average game material
- **7-8 samples:** Getting expensive
- **20+ samples:** Portfolio/offline only

**Optimization tips:**
- Pack multiple maps into single textures (RGB masks, packed PBR)
- Use shared textures across layers where possible
- Reduce layer count for shipped games
- Consider **Virtual Texturing** for large open worlds
- Profile with **GPU Visualizer** (`stat GPU`) to measure actual cost

### Use Cases

- **Portfolio pieces** and art tests — excellent visual quality
- **Offline rendering** and cinematics — no real-time budget constraint
- **High-end PC/console** — with careful optimization
- **Prototyping** — quickly iterate on material looks before optimizing

## Related

- Previous: [[01_Advanced_Glass_Material|Advanced Glass Material]] (Episode 1)
- Next: [[03_Parallax_Occlusion_Mapping|Parallax Occlusion Mapping]] (Episode 3)
- Series MOC: [[UE5_Materials_MOC|UE5 Materials MOC]]
