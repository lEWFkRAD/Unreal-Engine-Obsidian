---
title: "Unreal Engine 5.4 World Partition & HLODs"
source: "https://www.youtube.com/watch?v=oaon_1huRoI"
video_id: "oaon_1huRoI"
type: "youtube-summary"
series: "UE5 World Partition"
episode: 3
tags: [ue5, world-partition, hlod, hierarchical-lod, optimization, ue5-4, foliage]
---

# Unreal Engine 5.4 World Partition & HLODs

**Creator:** Unknown (YouTube)
**Duration:** 22:09 | **UE5 Version:** 5.4

## Overview

This tutorial covers the **World Partition** and **Hierarchical Level of Detail (HLOD)** systems in UE5.4, focusing on world settings configuration, HLOD setup and behaviors, and practical optimization techniques for large open worlds.

## Video Structure

| Timestamp | Topic |
|-----------|-------|
| 0:00 | Intro |
| 1:41 | World Settings Update |
| 2:34 | World Settings HLOD Setup Section |
| 4:26 | HLOD Setup and Behaviours |
| 6:04 | HLOD Behaviour Configuration |

## What are HLODs?

**Hierarchical Levels of Detail (HLODs)** are UE5's system for automatically generating simplified representations of distant world regions. Instead of rendering thousands of individual meshes at far distances:

- Nearby cells: render individual actors normally
- Distant cells: render a **merged, simplified HLOD proxy** instead
- This dramatically reduces draw calls, overdraw, and geometry cost at distance

## Step-by-Step HLOD Setup

### Step 1: Configure World Settings for HLODs

1. Open **World Settings** > **World Partition Setup**
2. Ensure **Enable World Partition** is checked
3. Find the **HLOD** section:
   - **HLOD Layer**: Assign an HLOD layer to define the build behavior
   - **Cell Size**: Controls the granularity of HLOD cells
   - **Loading Range**: Distance at which HLOD representations switch in

### Step 2: Set Up HLOD Layers

1. **Create HLOD Layer assets:**
   - Content Browser > Right-click > World Partition > HLOD Layer
   - Or access through the **HLOD Outliner**

2. **HLOD Layer settings:**
   - **Layer Type**: Choose from Merge, Mesh Merge, Mesh Simplify, or Spline
   - **Cell Size**: How large each HLOD cell is
   - **Loading Range**: Distance at which the HLOD activates

3. **Assign actors to HLOD Layers:**
   - Select actors in the world
   - In Details panel > World Partition > **HLOD Layer** > assign your layer
   - Or bulk-assign through the HLOD Outliner

### Step 3: Build HLODs

1. **Menu:** Build > World Partition > Build HLODs
2. Or use the commandlet:
   ```
   UnrealEditor.exe YourProject -run=HLODBuilder YourMap.umap
   ```
3. The build process:
   - Groups actors by HLOD cell
   - Generates merged/simplified meshes for each cell
   - Stores HLOD actors in a hidden layer

### Step 4: Configure HLOD Behaviors

**Key behavior options:**

- **Merge Actors**: Combines multiple static meshes into a single mesh per cell
  - Best for props and environmental details
  - Reduces draw calls significantly

- **Mesh Simplify**: Generates a low-poly version of the merged geometry
  - Better for complex geometry where merge alone isn't enough
  - Controls triangle reduction percentage

- **Mesh Merge + Simplify**: Both techniques combined
  - Maximum optimization for distant regions

- **Spline-based HLODs**: For roads, rivers, and spline-based content

### Step 5: Handle Foliage HLODs

Foliage requires special attention for HLODs:

1. In the **HLOD Outliner**, assign foliage actors to appropriate HLOD layers
2. Configure foliage settings to work with HLOD generation
3. **Known issue in UE 5.4:** Some foliage meshes may disappear during HLOD build
   - **Workaround:** Set HLOD layer to "Do Not Load Sub Levels" before building
   - This resolves partial mesh issues but may not fix all cases

## HLOD Debugging

**Console commands:**
```
wp.Runtime.HLOD 0                     # Disable HLODs (show original actors)
wp.Runtime.HLOD 1                     # Enable HLODs (default)
wp.Runtime.ToggleDrawRuntimeHash2D    # Visualize the grid
wp.Runtime.OverrideRuntimeSpatialHashLoadingRange -grid=0 -range=1000  # Override range
```

**In editor:**
- Use the **World Partition window** to see which regions have HLODs built
- The **HLOD Outliner** shows all HLOD layers and their assigned actors
- **Build > World Partition > Build HLODs** to rebuild after changes

## HLOD Optimization Tips

1. **Start with large cells** and refine — smaller cells = more HLOD actors = more overhead
2. **Use appropriate layer types** — don't simplify what just needs merging
3. **Test the transition** — walk through your world and check for popping between HLOD levels
4. **Rebuild after major changes** — HLODs are baked, not dynamic
5. **Combine with Nanite** — Nanite meshes in HLOD cells get the best of both systems
6. **Monitor memory** — HLOD meshes add to disk/memory; audit unused ones

## Common Pitfalls

- **Foliage disappearing:** Known UE5.4 issue; see workaround above
- **HLODs not building:** Ensure actors have HLOD Layers assigned and World Partition is enabled
- **Popping at transitions:** Adjust loading range to smooth the switch
- **Build times:** Large worlds can take significant time to build HLODs — plan accordingly
- **Performance regression:** More HLOD layers doesn't always mean better performance; profile after changes

## Related Resources

- [Epic Documentation: World Partition](https://dev.epicgames.com/documentation/unreal-engine/world-partition-in-unreal-engine)
- [Generate HLODs in a World Partition Level — NanceDevDiaries](https://www.youtube.com/watch?v=LUvPi0Y-MzU)
- [UE 5.4 — Foliage HLOD Forum Discussion](https://forums.unrealengine.com/t/ue-5-4-foliage-hlod-in-world-partition-maps/1896500)
- [UE5 World Partition Part 1: Concepts — Demenzun Media](https://www.youtube.com/watch?v=pB-4buUcA5I)


---

## Related

- ← Previous: [[02_Creating_Open_World_Landscapes_with_Partitioning]]
- 📚 Series: [[_MOC_UE5_World_Partition]]
