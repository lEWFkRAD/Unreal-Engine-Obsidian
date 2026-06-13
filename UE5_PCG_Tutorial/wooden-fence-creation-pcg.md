---
title: "AAA Wooden Fence Creation | From Modeling & Sculpting to Unreal Engine PCG Fence"
source: "https://www.youtube.com/watch?v=MpoaDYPDgRI"
video_id: "MpoaDYPDgRI"
type: "youtube-summary"
series: "UE5 PCG Tutorial"
episode: 0
tags: [ue5, tutorial, pcg, zbrush, substance-painter, blender, gamedev, procedural]
---

# AAA Wooden Fence Creation Pipeline

**Channel:** PolyBoost | **Published:** 2026-01-18 | **Length:** 28:45

## Overview
A comprehensive AAA game-ready pipeline for creating a modular, procedural wooden fence system. Covers high-poly sculpting in ZBrush, optimization, texturing in Substance Painter, and procedural assembly in UE5 using PCG.

**Asset Download:** [Google Drive](https://drive.google.com/file/d/185RBIzdiqhJjbq_LoPDLnxWc3SXe4oQZ/view?usp=sharing)

## Key Workflow Steps

### 1. Modeling & Sculpting (Blender & ZBrush)
- **Base Meshes (Blender)**: Simple shapes with bevels to preserve form during sculpting.
- **Variation Strategy**: 5 versions of sharp-tip pieces, 2 versions of other pieces.
- **High-Poly Sculpting (ZBrush)**: Use Dam Standard (borders), Clay Buildup (surface), Snake Hook (forms), Trim Dynamic (chipped edges).
- **Damage Techniques**: Lasso select + delete hidden geometry + Dynamesh with Group for realistic broken edges.

### 2. Optimization & Texturing
- **Decimation Master**: ~1,250,000 → ~1,250 polygons while preserving shape.
- **Weighted Normals** for shading fixes. **Ryzen UV** for clean unwraps.
- **Critical**: High-poly and low-poly must be in exact same position before export.
- **Substance Painter**: Bake pieces individually, use generators for surface effects, create reusable Smart Materials.

### 3. Unreal Engine PCG Setup
- **Two PCG Methods**:
    1. **Full Fence Spawner**: `Get Spline Data` → `Spline Sampler` (Distance mode) → `Transform Points` → `Static Mesh Spawner`.
    2. **Individual Piece Control**: Spawn connection pieces first, use `Copy Points` and `Grid Points` for plank positions.
- **Extensibility**: System can spawn additional props using filter and transform nodes.

## Key Takeaways
- Create multiple damaged and clean versions of each piece for realism.
- Use grouping in ZBrush and Smart Materials in Substance Painter for efficiency.
- PCG setup allows both fully automated spline-based generation and granular control.

---

## Related

- ← Previous: [[post-apocalyptic-car-wall-pcg-splines-part1]]
- → Next: [[auto-landscape-generator-in-ue5-7]]
- 📚 Series: [[_MOC_UE5_PCG_Tutorial]]
