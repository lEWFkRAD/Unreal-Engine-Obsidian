---
title: "Unreal Engine 5 Beginner Tutorial Part 19: Render Setting & Console Commands"
source: "https://www.youtube.com/watch?v=lhGweZQIQ6s"
video_id: "lhGweZQIQ6s"
type: "youtube-summary"
series: "UE5 Starter Course"
episode: 20
tags: [ue5, tutorial, beginner, rendering, lumen, path-tracing, movie-render-queue, console-commands]
---

# UE5 Beginner Tutorial Part 19: Render Setting & Console Commands

**Instructor:** Bad Decisions Studio

## Overview
Two primary rendering methods (Lumen vs Path Tracing), essential console variables, pre-render steps, and Movie Render Queue workflow.

## Essential Console Commands

```bash
# Enable Nanite Raytracing (fixes shadow artifacts)
r.RayTracing.Nanite.Mode 1

# Disable Raytracing Culling (prevents objects disappearing at distance)
r.RayTracing.Culling 0

# Control Render Resolution Percentage
r.ScreenPercentage
```

### Saving Console Variable Presets
1. Window > Console Variables
2. Adjust variables → Click **Save Preset** (e.g., "Star_Wars")
3. Load via Console Variables > Load Preset

## Pre-Render Setup
- **Fix Lighting Flickering:** Increase Samples Per Pixel on light sources (default is 1)
- **Lock Camera Angles:** Sequencer → right-click camera → Transform → Lock Actor Movement
- **Camera Cut Track:** Add multiple cameras, defines what renders when
- **Frame Rate:** Typically 30 FPS

## Lumen Render Settings (Movie Render Queue)

### Configuration
- **Output:** Set directory, file name format (e.g., `SD_[frame]`), resolution 4K (1920*2 x 1080*2)
- **Rendering:** Use Deferred Rendering (Lumen)
- **Console Variables:** Add saved preset + `r.ScreenPercentage 125` or `150`
- **Export:** Delete JPEG, add PNG (8-bit). Professional: EXR (16-bit)
- Click Accept > Render Local

## Path Tracer Render Settings
- Remove Deferred Rendering, add **Path Tracer**
- **Anti-Aliasing:** Override AA: None
- **Samples:** Spatial × Temporal (e.g., 32×32 = 1024). **1000+ recommended for clean output**
- **Screen Percentage:** Set to 100
- **Performance:** Extremely slow — single frame can take minutes

## Lumen vs Path Tracer Comparison

| Aspect | Lumen | Path Tracer |
|--------|-------|-------------|
| Speed | Very Fast (~300 frames in ~4 mins) | Extremely Slow (1 frame in minutes) |
| Quality | High-quality, real-time | Physically accurate, highest |
| Use Case | Most projects, animations | Final hero shots, high-end stills |

## Pro Tips
- Per-shot lighting for different camera angles
- Use DJV Viewer to review image sequences

---

## Related

- ← Previous: [[19_Animation_Sequencer_Advanced]]
- → Next: [[21_Ultimate_Unreal_Engine_Program]]
- 📚 Series: [[_MOC_UE5_7_Starter_Course]]
