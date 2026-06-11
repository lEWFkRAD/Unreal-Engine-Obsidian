---
title: "Create Procedural WWII Battlefield in Unreal Engine 5 – Full Tutorial"
source: "https://www.youtube.com/watch?v=Jdm1aQv3zNo"
video_id: "Jdm1aQv3zNo"
type: "youtube-summary"
series: "UE5 PCG Tutorial"
episode: 0
tags: [ue5, tutorial, pcg, procedural, battlefield, wwii, gamedev]
---

# Create Procedural WWII Battlefield in Unreal Engine 5

**Channel:** PolyBoost | **Published:** 2025-06-04 | **Length:** 40:29

## Overview
A fully procedural, scalable WWII battlefield environment for games or cinematics using UE 5.5's PCG tools. Covers terrain modification, procedural pathways, world population, and material setup.

**Free Models:** [WWII Battlefield Models](https://www.cgtrader.com/free-3d-models/military/other/procedural-wwii-battlefield-models) | [Tiger Tank](https://www.cgtrader.com/free-3d-models/military/military-vehicle/tiger-tank-a75abe1f-3c99-416d-bc24-c6b407c7f4fd)

## Key Concepts

### Essential Plugins
- **PCG Plugin** and **Landscape Patch Plugin** (non-destructive terrain modification).

### Foundational Blueprints
- **Landscape Circle Height Patch**: Controls height in circular areas (Radius + Fall-off).
- **Spline Blueprint**: Guides PCG point generation with custom tags.

## Step-by-Step Process

### Phase 1: Terrain Foundation
- Create landscape, PCG folder, foundational blueprints.
- Use Landscape Circle Height Patch to sculpt hills/mounds in real-time.

### Phase 2: Procedural Pathways
- **Road/Trench**: Spline → Spline Sampler (Interior mode) → density filters → spawn point patch Blueprint.
- **Tunnel System**: Separate spline with `Unbounded` sampling. Place beams (Static Mesh Spawner) and panels (Spawn Spline Mesh).

### Phase 3: Populating the World
- Import assets from Quixel Bridge.
- Use `Point Filter` and `Difference` nodes to exclude assets from paths.
- Mountain models to cover landscape edges.

### Phase 4: Material & Final Detail
- 4-layer landscape material with **Attribute Blend Mode** and displacement.
- Enable **Nanite** for landscape mesh.
- Manual painting by disabling PCG graph.

## Key Takeaways
- Landscape Patch Plugin enables non-destructive terrain modification.
- Unbounded spline sampling for structures extending beyond PCG volumes.
- Combine PCG point generation with manual landscape painting for final polish.

---

## Related

- ← Previous: [[procedural-vegetation-editor-ue-5-7-full-forest]]
- → Next: [[realistic-searchlight-animation-in-ue5]]
- 📚 Series: [[_MOC_UE5_PCG_Tutorial]]
