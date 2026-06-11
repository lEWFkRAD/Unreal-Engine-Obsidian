---
title: "Unreal Engine 5 Beginner Tutorial Part 14 - Clone Characters"
source: "https://www.youtube.com/watch?v=FQQy2tLncpE"
video_id: "FQQy2tLncpE"
type: "youtube-summary"
series: "UE5 Starter Course"
episode: 15
tags: [ue5, tutorial, beginner, clone-characters, nanite, optimization, pattern-tool, static-mesh]
---

# UE5 Beginner Tutorial Part 14: Clone Characters

**Instructor:** Bad Decisions Studio | **Length:** 35:21 | **Published:** 2024-03-11 | **Views:** 83,572

## Overview
Populating scenes with cloned characters using static meshes from skeletal animations, adding blaster props, Pattern Tool for cloning, and Nanite optimization.

## Core Techniques

### 1. Creating Static Meshes from Skeletal Animations
- Open animation sequence → pause at desired pose → use **"Make Static Mesh"** (top toolbar)
- Save as multiple poses (e.g., ST1, ST2, ST3, ST4)
- **Why:** Skeletal meshes are performance-heavy; static meshes optimize background armies

### 2. Adding Blasters
- Download blaster model from Sketchfab
- Select character → Details Panel → Add Component → Static Mesh → assign blaster
- Align manually using local-axis rotation/scaling → copy transform values to others

### 3. Pattern Tool for Cloning
- Select multiple static meshes → Modeling Tab → XForm → Pattern (Grid/Circle/Line)
- Adjust count and spacing
- **Jitter:** Scale Jitter (0.1-0.3) for height/width variation, Translation Jitter for positional offsets

## Optimization: Nanite

### Enable Nanite
- Select static meshes → Right-Click → Nanite → Enable
- Meshes use LODs (polycount reduces with distance)
- Verify via Viewport → Show → Nanite Visualization → Triangles

### Fix Ugly Shadows
- **Cause:** Nanite fallback mesh conflicts with ray tracing
- **Fix:** Console command: `r.RayTracing.Nanite.Mode 1`
- Forces ray tracing to use high-poly mesh

## Key Workflow Steps
1. Create 4 static meshes with distinct poses/blasters
2. Arrange in patterned grids (Front Army, Middle Army)
3. Mirror duplicates (Ctrl+Alt+Drag → Right-Click → Mirror Transform)
4. Enable Nanite + apply shadow fix command

## Pro Tips
- Avoid repetition with multiple animation sequences/poses
- Reduce Scalability Settings if FPS drops
- Nanite only works with static meshes (not skeletal)
- Console commands: use `r.` prefix + `?` in Output Log for function details

---

## Related

- ← Previous: [[14_Importing_Character_Animation]]
- → Next: [[17_Cameras_Rig_Rail_Crane]]
- 📚 Series: [[_MOC_UE5_7_Starter_Course]]
