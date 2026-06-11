---
title: "Unreal Engine 5 Beginner Tutorial Part 13: Importing Character Animation"
source: "https://www.youtube.com/watch?v=UQWz7A5_vpI"
video_id: "UQWz7A5_vpI"
type: "youtube-summary"
series: "UE5 Starter Course"
episode: 14
tags: [ue5, tutorial, beginner, animation, mixamo, character, rigging, stormtrooper]
---

# UE5 Beginner Tutorial Part 13: Importing Character Animation

**Instructor:** Bad Decisions Studio

## Overview
Rigging and animating a 3D character (Stormtrooper) using free Mixamo tool, batch importing multiple animations into UE5, and fixing FBX textures.

## Step-by-Step Workflow

### 1. Prepare Character Model
- Download Stormtrooper from SketchFab in **FBX format** (includes .fbx and textures folder)

### 2. Rig & Animate with Mixamo
- **Upload Character:** Upload FBX to Mixamo. If not recognized, place markers on key joints (chin, wrists, knees, groin)
- **First Download — T-Pose:**
  - Character must be in T-Pose (arms out) as base for rigging
  - Download T-Pose animation **"with skin"** (includes mesh) — becomes master skeleton/mesh in UE5
- **Additional Animations:**
  - Download other animations **"without skin"** (bone/animation data only)
  - **Critical:** Check **"In Place"** option for walk cycles (prevents character moving through scene)

### 3. Batch Import into UE5
- Create folder for character (e.g., "Storm Troopers")
- **Import T-Pose First:** Import Mesh: Yes, Import Animations: Yes, Skeleton: None (create new)
- **Import Additional Animations:** Import Mesh: No, Skeleton: Select existing skeleton from T-Pose
- Result: Single skeletal mesh + multiple animation sequences

### 4. Fix Textures (FBX Imports)
- FBX imports often don't auto-apply textures — must manually map
- Open material for each part → delete default white texture node → drag texture maps into graph
- Connect diffuse/albedo to Base Color
- Some textures use packed channels (R=roughness, G/B=specular/opacity)

## Important Notes
- **"In Place" is crucial:** Without it, character snaps back to origin in UE5
- **Optimization:** Import animations "without skin" with shared skeleton — avoids duplicating mesh per animation
- **Material Testing:** Disable individual R/G/B channels to see what data each holds
- **Scene Variation:** Multiple animation sequences on cloned characters creates natural-looking army

## Final Workflow
Model → Rig/Animate in Mixamo (T-Pose base + animations "in place") → Batch Import (mesh first, then animations to existing skeleton) → Manually assign textures

---

## Related

- ← Previous: [[13_Importing_Assets]]
- → Next: [[15_Clone_Characters]]
- 📚 Series: [[_MOC_UE5_7_Starter_Course]]
