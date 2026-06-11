---
title: "Unreal Engine 5 Beginner Tutorial Part 7: Materials & Textures Basics"
source: "https://www.youtube.com/watch?v=xmFNjkq-c-o"
video_id: "xmFNjkq-c-o"
type: "youtube-summary"
series: "UE5 Starter Course"
episode: 8
tags: [ue5, tutorial, beginner, materials, textures, quixel-bridge, megascans, tiling, variation]
---

# UE5 Beginner Tutorial Part 7: Materials & Textures Basics

**Instructor:** Bad Decisions Studio | **Length:** 27:16 | **Published:** 2024-03-07

## Overview
Creating non-repetitive floor materials using Quixel Bridge and advanced variation techniques. Solves the common problem of repetitive textures on large surfaces.

## Core Concepts
- **Quixel Bridge:** Free library (~14,572 assets) of high-quality 3D assets including 8K textures, accessible directly in UE5
- **The Repetition Problem:** Materials look unrealistic when tiled on large surfaces
- **Solution:** Use variation techniques from UE5's Starter Content

## Step-by-Step Workflow

### 1. Sourcing Assets from Quixel Bridge
- Access via `+` icon in UE5 toolbar
- Search for materials (e.g., "Metal Panel Facade")
- Select **Highest Quality** (8K), Download then Add
- Assets imported to `Megascans/Surfaces` folder as Material Instances

### 2. Initial Material Adjustments
- Apply Material Instance to floor mesh
- Adjust **Tiling** U and V values (e.g., 23 and 33)
- Reduce **Max Roughness** (0.5-0.7) for more reflective surface

### 3. Solving Texture Repetition
- **Key Insight:** Variation comes from multiple texture samples (imperfection maps) mixed at different scales
- **"Stealing" the technique:**
  1. Duplicate a Starter Content material (e.g., `Metal_Burnish_Steel`)
  2. Create Material Instance for parameter control
  3. Open Parent Material to inspect node graph
  4. Identify variation nodes (texture samplers at different scales)
  5. Replace base color and normal maps with your Quixel textures

### 4. ORD Texture Format
- **O** = Occlusion (Red Channel)
- **R** = Roughness (Green Channel)
- **D** = Displacement/Height (Blue Channel)
- Three maps in one color image for performance

### 5. Adding Color Tint
- Add Multiply + RGB node chain
- Convert RGB to Parameter named "Color Tint"
- Increase value beyond 1 for brightness boost

## Pro Tips
- `Z` to zoom in, `C` to zoom out in material editor
- All variation values can be converted to parameters for Material Instance control

---

## Related

- ← Previous: [[07_Intro_Materials_Textures]]
- → Next: [[09_Materials_Textures_Advanced]]
- 📚 Series: [[_MOC_UE5_7_Starter_Course]]
