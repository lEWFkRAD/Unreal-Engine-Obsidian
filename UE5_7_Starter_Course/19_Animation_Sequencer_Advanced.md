---
title: "Unreal Engine 5 Beginner Tutorial Part 18: Animation & Sequencer Advanced"
source: "https://www.youtube.com/watch?v=YBNUC6GD5ho"
video_id: "YBNUC6GD5ho"
type: "youtube-summary"
series: "UE5 Starter Course"
episode: 19
tags: [ue5, tutorial, beginner, animation, sequencer, camera-animation, anamorphic, cinematic]
---

# UE5 Beginner Tutorial Part 18: Animation & Sequencer Advanced

**Instructor:** Bad Decisions Studio

## Overview
Advanced Sequencer techniques for cinematic shots. Demonstrates two example scenes: Stormtrooper walking sequence and crowd/side-scrolling shot.

**Key Insight:** Set up cameras early to build only what the camera sees.

## Sequencer Fundamentals
- Open from Outliner or Content Drawer
- Add cameras: Cinematics > Camera Actor
- **Camera Cuts Track:** Enables multiple camera angles within single Sequencer

## Shot 1: Stormtrooper Walk & Ship Opening

### Camera Placement
- Ground level between Stormtroopers
- Adjust **Focal Length** (e.g., 35) for zoom/wideness

### Animation Adjustments
- Extend walk animation by increasing timeline length (e.g., 500 frames)
- Keyframe X Location for starting positions and distance
- **Play Rate:** Right-click animation → Properties → Play Rate = 0.5 for half speed
- Keyframe Spaceship Door opening to sync with walk

### Camera Animation & Focus
- Keyframe camera Location to animate rising
- Enable **Draw Debug Focus Plane** to visualize
- Lower **Aperture** for more blur, keyframe **Focus Distance** over time

### Anamorphic Lens Effect
- Adjust **Sensor** values (e.g., 34, 14) in Film Back settings
- Set **Squeeze Factor** to 2 for widescreen anamorphic look

## Shot 2: Crowd / Side-Scrolling Shot

### Camera Setup
- Use **Look At Tracking** with Eyedropper to select Stormtrooper
- **Relative Offset** on Z-axis (e.g., 150) to aim at head
- Increase **Inter Speed** (e.g., 4) for smoother tracking

### Animation & Depth
- Keyframe camera transform for side-scroll movement
- High **Focal Length** (long lens) for compression and background blur
- Shallow depth of field with low Aperture

### Shadow Fix
- **Console Command:** `r.RayTracing.Culling 0` (disables culling, fixes distant shadows)
- Issue occurs with Lumen, not Path Tracing

## Important Console Commands
```
r.RayTracing.Nanite.Mode 1    # Enable Nanite Raytracing
r.RayTracing.Culling 0         # Fix distant shadow culling
```

## Cinematic Tips
- Adjust lighting per camera shot/angle — lighting should not be static
- Uncheck **Receive Decals** on characters to prevent artifacts

---

## Related

- ← Previous: [[18_Animation_Sequencer_Basics]]
- → Next: [[20_Render_Settings_Console_Commands]]
- 📚 Series: [[_MOC_UE5_7_Starter_Course]]
