---
title: "Unreal Engine 5 Beginner Tutorial Part 4: Modeling Tools Advanced"
source: "https://www.youtube.com/watch?v=-GtqvZfuCSY"
video_id: "-GtqvZfuCSY"
type: "youtube-summary"
series: "UE5 Starter Course"
episode: 5
tags: [ue5, tutorial, beginner, modeling, extrude, bevel, inset, edge-loop]
---

# UE5 Beginner Tutorial Part 4: Modeling Tools Advanced

**Instructor:** Bad Decisions Studio | **Length:** 29:32 | **Published:** 2024-03-05 | **Views:** 208,185

## Overview
Transforms a basic hexagonal shape into a detailed sci-fi spaceship hangar using advanced modeling tools. Focus on manipulating faces, edges, and vertices with precision.

## Core Modeling Concepts
- **Three Selection Types:** Faces, Edges, and Vertices (points)
- **Access Modeling Tools:** Shortcut `Shift + 5`
- **Polygroup Edit Mode:** Similar to Blender's Edit Mode, reveals wireframe for direct mesh manipulation

## Critical Workflow Settings
- **Disable "Hit Back Faces":** In selection settings to avoid selecting unseen faces
- **Undo/Redo:** `Ctrl+Z` / `Ctrl+Y` (not Ctrl+Shift+Z)

## Advanced Tool Techniques

### Insert Edge Loop
- **Purpose:** Evenly subdivide mesh to create sections for pillars
- **Setting:** Change from "Proportion Offset" to **"Even"** for precise divisions
- **Application:** 8 loops for small pillars (9 sections), 2 loops for large pillars

### Extrude
- **Distance Mode:** Change to "Fixed" (uses slider, not mouse)
- **Direction Mode:** Change to "Selected Triangle Normals" (extrudes outward from each face)
- **Values:** Small pillars: 170, Large pillars: 400
- Check wireframe to ensure mesh integrity

### Inset
- **Purpose:** Create recessed areas/windows
- Use mouse drag to size inset relative to first selected face
- Follow-up with **Extrude** at negative value (e.g., -70) to push inward

### Bevel
- **Purpose:** Soften sharp 90° edges for realism
- Select faces around which you want beveled edges
- Adjust **Weight** value (e.g., 4) to control bevel size

## Pro Tips
- Save frequently after complex operations
- Periodically toggle wireframe to check for deformed geometry
- "Normals" = direction a face is pointing; "Selected Triangle Normals" ensures perpendicular extrusion

## Final Result
Spaceship model with four detailed small pillars, three larger pillars with inset "windows" and beveled edges, and a modified base with pulled-in sections.

---

## Related

- ← Previous: [[04_Modeling_Tools_Basics]]
- → Next: [[06_Lighting]]
- 📚 Series: [[_MOC_UE5_7_Starter_Course]]
