---
title: "Unreal Engine 5 Beginner Tutorial Part 10: Post Process Volume"
source: "https://www.youtube.com/watch?v=P5z6vRGGl8g"
video_id: "P5z6vRGGl8g"
type: "youtube-summary"
series: "UE5 Starter Course"
episode: 11
tags: [ue5, tutorial, beginner, post-process, bloom, exposure, color-grading, path-tracing, lumen]
---

# UE5 Beginner Tutorial Part 10: Post Process Volume

**Instructor:** Bad Decisions Studio | **Length:** 20:36 | **Published:** 2024-03-09

## Overview
Transform scenes from basic to cinematic using Post Process Volume. Covers core settings, Lumen vs Path Tracing rendering, and advanced ray tracing configuration.

## Core Concepts
- **Post Process Volume:** Final filter on top of render to enhance visual quality
- Add at the start of projects to control scene look
- Supports multiple volumes for region-specific effects

## Essential Settings

### Bloom (Glow)
- **Standard:** Scene-wide application
- **Convolution:** More realistic, applied mainly to lights, more expensive

### Exposure
- Auto Exposure enabled by default (simulates pupil adjustment)
- For consistent lighting: set Min & Max EV100 to same value (e.g., 0)

### Lens Effects
- **Chromatic Aberration:** ~0.2 for subtle photorealism
- **Vignette:** 0.45 recommended (darkens edges, focuses attention)
- **Film Grain:** 0.3 recommended (adds imperfection to reduce CG look)
- **Color Grading:** Temperature, tint, shadows/midtones/highlights channels

## Rendering Methods

### Lumen (Real-Time)
- Default renderer, fully dynamic GI and reflections
- ~80 FPS, smooth workflow
- Tunable: Scene Detail, Final Gather Quality, Max Reflection Bounces

### Path Tracing (Physically Accurate)
- Most realistic, like Blender's Cycles
- Very resource-intensive, noisy during preview
- Lower Samples (150) and Max Bounces (3) for faster iteration

## Advanced Ray Tracing Settings (Requires RTX GPU)
- **Project Settings > Rendering:**
  - Enable "Use Hardware Ray Tracing When Available"
  - **Reflections:** Change to "Hit Lighting for Reflection" (dramatically better quality)
  - **Shadows:** Enable Ray Traced Shadows

## Pro Tips
- Use separate non-unbound volumes for area-specific effects
- Use Lumen for editing, Path Tracing for final renders
- "The more imperfection you add... it's going to make everything look less CG"

---

## Related

- ← Previous: [[10_Scene_Decoration]]
- → Next: [[12_Hdri]]
- 📚 Series: [[_MOC_UE5_7_Starter_Course]]
