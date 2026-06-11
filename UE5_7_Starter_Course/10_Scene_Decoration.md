---
title: "Unreal Engine 5 Beginner Tutorial Part 9: Scene Decoration"
source: "https://www.youtube.com/watch?v=8Hm4JirJmk8"
video_id: "8Hm4JirJmk8"
type: "youtube-summary"
series: "UE5 Starter Course"
episode: 10
tags: [ue5, tutorial, beginner, scene-decoration, pattern-tool, merge-actors, emissive, lights]
---

# UE5 Beginner Tutorial Part 9: Scene Decoration

**Instructor:** Bad Decisions Studio | **Length:** 33:51 | **Published:** 2024-03-08 | **Views:** 99,607

## Overview
Decorating a spaceship scene with arrays of lights on pillars and columns. Key tools: Pattern Tool for duplicating objects, Merge Actors for optimizing meshes, and material control for multiple lights.

## Key Techniques

### 1. Creating Light Assets
- **Base Shape:** Modeling Tab > Rectangle primitive
- Change type to `rounded` for softer edges
- Use PolyGroup Edit > Extrude for depth
- Duplicate and scale for metallic base

### 2. Material Creation & Assignment
- Create emissive Material with Material Instance for parameter control
- Add RGB node (color) + Multiply node with parameter (emissive_strength)
- Apply emissive to light surfaces, metallic to bases

### 3. Merging Actors
- **Purpose:** Combine separate meshes into single static mesh for efficiency
- **Steps:** Select all → Actor > Merge Actors → Name and save
- **Critical:** Apply materials *before* merging to preserve separate material slots

### 4. Using the Pattern Tool
- **Access:** Modeling Tab > Pattern
- **Linear Arrays:** Choose Line pattern, set axis/extent/count, adjust spacing
- **Mirroring:** Right-Click > Transform > Mirror on desired axis
- Toggle between World and Local transform gizmo for alignment

### 5. Emissive Edge Lights (Advanced)
- Use PolyGroup Edit to select outer faces
- Duplicate faces, extrude outward
- Insert Edge Loop for emissive area
- Use Attribute > Edit Materials to paint selected polygons
- Assign emissive material to new slot

## Pro Tips
- Use Pattern Tool for efficient, non-destructive duplication
- Merge Actors to reduce mesh count and optimize performance
- Material Instances enable global control of color/intensity
- Pre-merge material setup ensures slots remain separate after merging

---

## Related

- ← Previous: [[09_Materials_Textures_Advanced]]
- → Next: [[11_Post_Process_Volume]]
- 📚 Series: [[_MOC_UE5_7_Starter_Course]]
