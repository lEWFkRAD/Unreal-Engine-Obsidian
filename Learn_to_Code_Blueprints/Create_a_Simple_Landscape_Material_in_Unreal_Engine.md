---
title: "How to Create a Simple Landscape Material in Unreal Engine"
source: "https://www.youtube.com/watch?v=IArkYsjkLMg"
video_id: "IArkYsjkLMg"
type: "youtube-summary"
series: "Learn to Code Blueprints"
episode: 0
tags: [ue5, tutorial, blueprint, gamedev, coding]
---

# How to Create a Simple Landscape Material in Unreal Engine

## Overview
Tutorial on creating and painting a multi-layer landscape material in Unreal Engine to replace a default gray landscape.

## Key Steps

### 1. Create a New Material
- Right-click in Content Browser > **Material**. Name it (e.g., `Arena_one_landscape`).
- Open the material and add a temporary constant color node to test.
- Create a **Material Instance** from the new material for easier parameter control.

### 2. Assign Material to Landscape
- Select the Landscape actor.
- In the **Details** panel, find the **Landscape Material** slot and assign your material.

### 3. Source Textures (Using Fab)
- **Fab Marketplace Filter Setup**: Filter by Price: Free, Publisher: Quixel.
- **Recommended Texture Packs**: Forest Floor, Rock Cliff, Mossy Forest Floor.
- Import textures: Base Color (diffuse), Normal, Packed Texture (AO, Roughness, Height).

### 4. Critical Step for Landscapes
- For each texture sample node, set the **Sampler Source** to **Shared: Wrap**.
- This increases available texture slots beyond the default 16.

### 5. Set Up Landscape Layer Blend
- Add **Landscape Layer Blend** node.
- Use generic names like `L1`, `L2`, `L3` (not descriptive names like "dirt") for flexibility.
- Connect Base Color from each texture sample to a corresponding Layer input.

### 6. Create Layer Info Assets and Paint
- Switch to **Landscape Mode** > **Paint** sub-mode.
- Use **"Create Layer Info from Assigned Material"** button if layers are missing.
- For each layer: click `+` next to "No Layer Info", save to create a Layer Info asset.
- **Painting Workflow**: Select a layer and paint; use **Shift + Click** to erase.

## Key Technical Insights
- **Shared: Wrap Sampler** is essential for multiple textures in landscape materials.
- **Landscape Layer Blend** nodes are required for painting multiple materials.
- **Layer Info assets** are mandatory data objects that store painted layer data.
- Paint layers on top of each other with Shift + Click to subtract for non-destructive workflow.

---

## Related

- ← Previous: [[Create_a_Landscape]]
- → Next: [[Create_your_first_world_partition_level]]
- 📚 Series: [[_MOC_Learn_to_Code_Blueprints]]
