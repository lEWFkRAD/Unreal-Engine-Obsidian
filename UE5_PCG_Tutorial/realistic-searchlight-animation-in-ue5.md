---
title: "Realistic Searchlight Animation in UE5 | Blender + Rig + Sequencer"
source: "https://www.youtube.com/watch?v=0oUuSxLWE4k"
video_id: "0oUuSxLWE4k"
type: "youtube-summary"
series: "UE5 PCG Tutorial"
episode: 0
tags: [ue5, tutorial, blender, animation, gamedev, pcg, procedural]
---

# Realistic Searchlight Animation in UE5 | Blender + Rig + Sequencer

**Channel:** PolyBoost | **Published:** 2026-03-24 | **Length:** 19:55

## Overview
This tutorial demonstrates creating realistic animated military searchlights for a cinematic environment in Unreal Engine 5. It explores **two distinct workflows**:
1. **Blender → UE5**: Rigging and animating in Blender, then importing into Unreal Engine.
2. **Direct in UE5**: Creating the animation entirely within Unreal Engine.

Key capabilities include parenting a spotlight to the animated searchlight so the light follows the motion, and using **Sequencer** to control and combine multiple animations.

**Free Model:** [Google Drive Link](https://drive.google.com/file/d/1mpwzQHTAs1NhB7-ETbjlAtLTs0qjmrl3/view?usp=sharing)

## Key Workflow Steps

### 1. Blender: Rigging & Animation
- **Searchlight Structure**: Two parts—base (rotates on Z-axis) and upper light section (rotates on Y-axis).
- **Rigging**: Add armature, duplicate bones, parent meshes to bones, assign vertex groups.
- **Animation**: Use **Dope Sheet** in Action Mode, set keyframes for rotation, extend to ~140 frames for looping.
- **Export**: Select mesh and rig, export as FBX with Armatures, Mesh, and Animation enabled.

### 2. Unreal Engine: Import & Setup
- Import FBX file; the animation sequence and skeletal mesh are generated.
- Add the mesh to a **Level Sequence** and import the rotation animation.

### 3. Animation in Unreal Engine (Alternative)
- Create a new Level Sequence and add the searchlight mesh.
- Use the **FK Controller Rig** to clear existing keyframes and create new animations.
- **Bake the animation** and name it for reuse.

### 4. Lighting & Cinematic Setup
- **Parent a Spotlight**: Create a spotlight and drag it onto the searchlight in the Outliner.
- Adjust *Intensity*, *Inner Cone Angle*, and *Outer Cone Angle*.
- Duplicate spotlights for multiple towers and apply animations via Sequencer.

## Key Takeaways
- The searchlight mesh itself does not emit light; a separate spotlight must be parented to it.
- Animations created in Blender or UE5 can be mixed and controlled via Sequencer.
- Two-pronged approach: choose Blender for detailed rigging or UE5 for quicker iteration.

---

## Related

- ← Previous: [[procedural-wwii-battlefield-full-tutorial]]
- → Next: [[ue-5-7-pcg-episode-1-forest-path-splines]]
- 📚 Series: [[_MOC_UE5_PCG_Tutorial]]
