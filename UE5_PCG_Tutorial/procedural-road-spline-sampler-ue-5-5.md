---
title: "Creating a Procedural Road with Spline Sampler in Unreal Engine 5.5"
source: "https://www.youtube.com/watch?v=v37pMIK0zD8"
video_id: "v37pMIK0zD8"
type: "youtube-summary"
series: "UE5 PCG Tutorial"
episode: 0
tags: [ue5, tutorial, pcg, procedural, splines, road, gamedev]
---

# Creating a Procedural Road with Spline Sampler in UE 5.5

**Channel:** PolyBoost | **Published:** 2025-05-26 | **Length:** 24:15

## Overview
Build a **100% procedural forest road** in UE 5.5 using PCG Graphs and the Spline Sampler node. Part 3 of a beginner-friendly PCG series. Creates a dynamic road with mesh, guard rails, electrical poles, cables, and signs.

**Free Models:** [PBR Road Models](https://www.cgtrader.com/free-3d-models/exterior/cityscape/free-pbr-models-for-road)

## Step-by-Step Process

### 1. Spline Setup
- Create Actor Blueprint, add Spline component.
- Shape spline in level, add points with Ctrl+Click.

### 2. Building the Road
- Import road mesh.
- `Transform Points` to rotate mesh to align with spline.
- `Spawn Spline Mesh` node to deform road along spline curve.

### 3. Adding Props
- **Guard Rails**: `Transform Points` for offset, dedicated Spline Sampler with smaller distance.
- **Electrical Poles**: `Static Mesh Spawner` (not Spawn Spline Mesh — poles shouldn't deform). Rotate one pole correctly in 3D app before export.
- **Cables**: `Spawn Spline Mesh` for alignment and deformation.
- **Signs**: Same process as poles/rails.

### 4. Integrating Road with Forest
- Clear trees from road path:
    1. Use road's spline points.
    2. `Bounds Modifier` to expand clearance area.
    3. `Difference` node (Binary mode) → connect to forest's Static Mesh Spawner.

### 5. Key Node: Create Spline
- **Close Loop**: Closes spline path.
- **Convert to Linear**: Straightens segments.
- Essential for connecting Transform Points when deforming meshes.

## Key Takeaways
- Reshape spline in editor → entire road system updates instantly.
- Spawn Spline Mesh deforms along curves; Static Mesh Spawner doesn't.
- Bounds Modifier + Difference node clears vegetation from road path.

---

## Related

- ← Previous: [[post-apocalyptic-car-wall-pcg-splines-part1]]
- → Next: [[procedural-vegetation-editor-ue-5-7-full-forest]]
- 📚 Series: [[_MOC_UE5_PCG_Tutorial]]
