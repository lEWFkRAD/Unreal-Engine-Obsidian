---
title: "Auto Landscape Generator in UE5.7 | Heightmap + PCG + Blueprint Workflow"
source: "https://www.youtube.com/watch?v=WAwztI1NfIQ"
video_id: "WAwztI1NfIQ"
type: "youtube-summary"
series: "UE5 PCG Tutorial"
episode: 0
tags: [ue5, tutorial, pcg, procedural, gamedev]
---

# Auto Landscape Generator in UE5.7: Heightmap + PCG + Blueprint Workflow

**Channel:** PolyBoost | **Published:** 2026-05-03 | **Length:** 16:07

## Overview
A hybrid workflow for automated landscape generation in UE5.7 that combines **heightmap textures**, **Procedural Content Generation (PCG)**, and **Blueprints** to simultaneously generate terrain, materials, and scatter meshes, with integrated real-time manual painting controls.

## Key Workflow Steps

### 1. Initial Setup & Heightmap
- **Enable Plugins**: Activate the **PCG** and **Landscape Patch** plugins.
- **Create a Blueprint**: Add a **Landscape Texture Patch** component.
- **Configure Texture**: Set the **Source Mode** to `Texture Asset` to create elevation from a heightmap texture.

### 2. Material Generation
- **Create a Landscape Material**: Use a **Landscape Layered Material** with multiple layers (e.g., three). Name these layers clearly (e.g., `Ground`).
- **Setup Material Attributes**: Convert to material attributes and create material sets, assigning desired textures to each layer.
- **Control Texture Scaling**: Use a **Landscape Coordinates Node**.
- **Apply Material**: Create and assign a **Material Instance** to the landscape.

### 3. PCG Graph for Point Generation & Mesh Scattering
- **Initialize PCG**: Create a new **PCG Graph**, add a **Get Actor Data** node, and place the PCG actor in the scene.
- **Connect Texture Data**: Use **Sample Texture** and **Get Texture Data** nodes to generate points based on your heightmap. Pressing `D` on the node visualizes the points.
- **Project to Ground**: Use **Projection** with a **Get Landscape Data** node to align points to the terrain surface.
- **Scatter Meshes**: Assign meshes to the generated points.

### 4. Refining PCG with Blueprints & Tags
- **Tagging System**:
    1. In your Blueprint's **Class Defaults**, add a unique **Tag** (e.g., `LandscapePatch`).
    2. In the PCG's **Get Actor Data** node, set the mode to **All World Actors** and copy the same tag.
    3. Add a **Box Collision** component to limit point generation to a specific area.

### 5. Integrating Material Layers with PCG
- **Add Attribute Element Filter**: Generate points only where specific material layers exist.
- **Synchronize Texture & Material**: Set the **Weight Path** option so mesh scattering and material painting follow the same texture mask.

### 6. Live Paint Spawning System
- **Surface Sampler**: Generate points directly on the painted landscape surface.
- **Link to Painting**: Painting a material layer directly on the landscape simultaneously scatters associated procedural meshes in real-time.

## Pro Tips
- **Alpha Textures**: Import an alpha texture to generate materials and meshes in custom-defined areas.
- **Height Generation Issues**: Enable the **Override Plane** option if height is not generating correctly.
- **Enriching Scenes**: Use PCG graph nodes for scaling, density, rotation to add natural variation.

---

## Related

- ← Previous: [[aaa-wooden-fence-creation-pcg]]
- → Next: [[building-narrative-military-camp-pcg]]
- 📚 Series: [[_MOC_UE5_PCG_Tutorial]]
