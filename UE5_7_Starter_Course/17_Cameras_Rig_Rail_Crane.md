---
title: "Unreal Engine 5 Beginner Tutorial Part 16: Cameras, Rig Rail, and Crane"
source: "https://www.youtube.com/watch?v=htS5XBFm2w0"
video_id: "htS5XBFm2w0"
type: "youtube-summary"
series: "UE5 Starter Course"
episode: 17
tags: [ue5, tutorial, beginner, cameras, cine-camera, rig-rail, crane, cinematic, focus, lens]
---

# UE5 Beginner Tutorial Part 16: Cameras, Rig Rail, and Crane

**Instructor:** Bad Decisions Studio

## Overview
Essential cinematic camera techniques — adding/controlling cameras, lens/sensor settings, focus tracking, and complex camera movements using Rig Rails and Crane Rigs.

## Cine Camera Actor

### Adding & Controlling
- **Place Actors** panel or Cinematics > Cine Camera Actor
- **External View:** Move camera in scene, use Camera Preview panel (bottom-right)
- **Pilot Mode:** Right-click camera → Pilot Cine Camera Actor (directly inside view)
- Switch cameras via Perspective menu under Place Cameras

### Core Settings (Details Panel)

#### Filmback Settings
- **Sensor Width/Height:** Determines sensor size (IMAX 70, 16:9 Digital Film)
- Adjusting changes aspect ratio and black bars

#### Lens Settings
- **Focal Length:** 24mm = wider, 50-130mm = telephoto
- **Aperture (F-stop):** F/1.2 = more blur, F/8 = more in focus
- **Squeeze Factor:** 2.0 for anamorphic lenses (stretches bokeh to ovals)
- **Lens Presets:** e.g., "30 mm Prime Lens" locks focal length

#### Focus Settings
- **Manual:** Adjust focus distance, use Debug Focus Plane to visualize
- **Tracking:** Enable Look at Tracking → Eyedropper to select actor to track

### Camera Rig Rail (Path Animation)
1. Add via Cinematics > Camera Rig Rail
2. Create path with white dot gizmo, Alt + Drag to extend
3. Make camera a **child** of Rig Rail, reset transform
4. Animate via `Current Position on Rail` slider

### Camera Rig Crane (Mechanical Arm)
1. Add via Cinematics > Camera Rig Crane
2. Make camera a child, reset transform
3. Control: **Pitch** (up/down), **Yaw** (left/right), **Arm Length** (distance)

### Combining Tracking with Movement
- Set camera as child of Rail/Crane
- Switch Focus to Tracking → select target with Eyedropper

## Pro Tips
- Frame final shots *first* with cameras to know what to build
- Pin Camera Preview panel to keep it visible while working
- Multiple camera previews can impact performance

---

## Related

- ← Previous: [[15_Clone_Characters]]
- → Next: [[18_Animation_Sequencer_Basics]]
- 📚 Series: [[_MOC_UE5_7_Starter_Course]]
