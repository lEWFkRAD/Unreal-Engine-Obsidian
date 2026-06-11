---
title: "Unreal Engine 5 Beginner Tutorial Part 12: Importing Assets"
source: "https://www.youtube.com/watch?v=rTNkIrQ0xHM"
video_id: "rTNkIrQ0xHM"
type: "youtube-summary"
series: "UE5 Starter Course"
episode: 13
tags: [ue5, tutorial, beginner, importing, assets, sketchfab, glb, fbx, skeletal-mesh]
---

# UE5 Beginner Tutorial Part 12: Importing Assets

**Instructor:** Bad Decisions Studio

## Overview
Importing external 3D assets (static and skeletal meshes with animation) from Sketchfab into UE5, using Lambda shuttle and TIE fighters as examples.

## Finding & Downloading from Sketchfab
- Search for models, identify free ones by download icon
- **GLB format preferred:** Textures packed into single file, simple drag-and-drop
- **FBX format:** Common but requires manual material/texture setup

## Importing into UE5
1. Create organized folders in Content Drawer
2. Drag and drop `.glb` file into Content Drawer
3. Import Options dialog appears — default settings usually fine
4. Click Import

## Understanding Imported Asset Types

### For Animated Assets (e.g., Lambda Shuttle)
- **Skeletal Mesh:** 3D model with bone structure (main asset to drag into scene)
- **Skeleton:** Underlying bone hierarchy for advanced editing
- **Animation Sequence:** Pre-baked animation data
- **Physics Asset:** Collision volumes for physics simulations

### For Static Meshes (e.g., TIE Fighter)
- If model imports as many separate parts → enable **Combine Static Meshes** in Import Options
- This merges all parts into single manageable mesh

## Controlling Animation in Viewport
- Select actor → Details Panel → Animation > Initial Position slider to scrub through frames

## Placing & Duplicating
- Use transform tools (W, E, R) to position
- `Alt + Drag` to duplicate
- `Ctrl + Shift + S` for snap to grid toggle
- Mirror duplicated objects along axis using transform tool options

## Best Practices
- Sketchfab is top resource for free/paid 3D assets
- GLB format recommended for simplicity
- Don't panic at multiple files for animated assets — start with Skeletal Mesh or Animation Sequence
- If import fails, revisit Import Options (e.g., enable Combine Static Meshes)

---

## Related

- ← Previous: [[12_Hdri]]
- → Next: [[14_Importing_Character_Animation]]
- 📚 Series: [[_MOC_UE5_7_Starter_Course]]
