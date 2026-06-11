---
title: "Is your ground flat? Try enabling tessellation in your landscape material"
source: "https://www.youtube.com/watch?v=YbHwPwl3S_s"
video_id: "YbHwPwl3S_s"
type: "youtube-summary"
series: "Learn to Code Blueprints"
episode: 0
tags: [ue5, tutorial, blueprint, gamedev, coding]
---

# Enabling Tessellation for Unreal Engine 5 Landscapes

## Overview
Tutorial on enhancing landscape details using displacement and tessellation with Nanite.

## Prerequisites
- Use **High-Quality** version of Quixel materials (e.g., "Mossy Rock Ground," "Forest Floor," "Rock Cliff").
- Medium Quality assets **do not include** the required displacement/height map texture.

## Step-by-Step Workflow

### 1. Import High-Quality Textures
- Re-download Quixel materials selecting the **High Quality** preset.
- This includes a **Height** (displacement) texture for each material.

### 2. Configure the Landscape Material
- Open your landscape **material** (not the material instance).
- For each material layer, find the **Height** texture in the high-quality package.
- Connect Height texture to the **Displacement** pin on your landscape material.
- Connect the **UV Tiling/Scaling** information to the height texture input.
- Ensure **Source Shared Wrap** mode is set correctly for all height textures.

### 3. Enable Tessellation and Nanite
- In the material editor, access the **Details Panel**.
- **Enable Tessellation**.
- Adjust the **Displacement Magnitude** (start with **0.15**).
- Save and apply the material.

### 4. Activate Nanite on the Landscape
- Select the **Landscape Actor** in your level.
- Enable **"Enable Nanite"** in the Details panel.
- Click **"Build Data"** (Nanite) to compile shaders and reveal the displacement effect.

### 5. Final Adjustment
- Tweak the **Displacement Magnitude** value for desired effect.
- Save all modified assets.

## Key Results
- Displacement adds geometric detail, creating **more interesting shapes and shadows**.
- Particularly effective for first-person cameras where ground detail is prominent.
- Take **screenshots** periodically to track visual progress.

## Common Mistakes
- Ensure you're using the correct **Height map** texture for each material layer.
- Don't accidentally use the grass height map for a rock material.

---

## Related

- ← Previous: [[Fix_tiling_issues_and_add_the_normal_to_your_Landscape_Material]]
- → Next: [[Making_our_landscapes_more_interesting]]
- 📚 Series: [[_MOC_Learn_to_Code_Blueprints]]
