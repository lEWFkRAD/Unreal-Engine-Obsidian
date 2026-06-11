---
title: "Cinematic Post-Apocalyptic Street P2 – Built with PCG in Unreal Engine 5.6"
source: "https://www.youtube.com/watch?v=6M9AUl_MAvY"
video_id: "6M9AUl_MAvY"
type: "youtube-summary"
series: "UE5 PCG Tutorial"
episode: 0
tags: [ue5, tutorial, pcg, procedural, cinematic, post-apocalyptic, gamedev]
---

# Cinematic Post-Apocalyptic Street P2: PCG in UE 5.6

**Channel:** PolyBoost | **Published:** 2025-06-17 | **Length:** 19:02

## Overview
Procedural world-building using UE 5.6's PCG tools. **No hand-placed assets** — all content generated via modular workflows. Covers replacing placeholder buildings, adding streets/sidewalks/props, auto-generating debris, and cinematic Post Process settings.

**Part 1:** [Post-Apocalyptic Car Wall](https://www.youtube.com/watch?v=XY89zXWadeE)

## Key Workflow Steps

### 1. Asset Integration & Building Placement
- Import high-quality building models (e.g., Evermotion Kitbash).
- `Transform Points` node to adjust scale of large assets.
- `Bound Modifier` + `Difference` node to prevent mesh overlap.

### 2. Street & Sidewalk Creation
- Spline-based road layout (same technique as previous PCG tutorials).

### 3. Lighting & Atmosphere
- **HDRI Backdrop**: Intensity 100, Skylight Intensity 60.
- **Post Process Volume**: Infinite Extent (Unbound). Exposure Intensity 4, adjust Min/Max EV 100.
- **Fog**: Volumetric Fog enabled, adjust intensity, start/end distance, scattering value.
- **Color Grading**: Cool tone in midtones/gain, reduced saturation for apocalyptic atmosphere.
- **Directional Light**: Increased Volumetric Scattering for fog diffusion.

### 4. God Rays
- Create **Light Function Material** with black-and-white texture.
- Assign to directional light's Light Function slot.

### 5. Detailing with PCG
- Iteratively add more meshes (props, debris) to PCG graph for realism.

## Key Takeaways
- Entire environment built procedurally with PCG — non-destructive, time-efficient.
- Iterative refinement: basic layout → replace assets → add detail layers.
- Cinematic quality relies heavily on atmospheric effects + detailed assets.

---

## Related

- ← Previous: [[building-procedural-farm-pcg-landscape-texture-patch]]
- → Next: [[create-dynamic-cables-in-ue5]]
- 📚 Series: [[_MOC_UE5_PCG_Tutorial]]
