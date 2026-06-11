---
title: "Simplified Guide: UE5's World Partition Tool Tutorial"
source: "https://www.youtube.com/watch?v=FP0BNaeHok4"
video_id: "FP0BNaeHok4"
type: "youtube-summary"
series: "UE5 World Partition"
episode: 1
tags: [ue5, world-partition, level-streaming, data-layers, hlod, one-file-per-actor, spatial-loading]
---

# Simplified Guide: UE5's World Partition Tool Tutorial

**Creator:** BlackShinobi956 Game Dev (10 years UE experience)
**Duration:** 12:58 | **Published:** September 21, 2023

## Overview

A beginner-friendly walkthrough of UE5's **World Partition** system — the replacement for UE4's manual level streaming. This video covers the core concepts, editor workflow, and all the related subsystems (One File Per Actor, Data Layers, HLODs, Level Instances).

## What is World Partition?

World Partition is UE5's **automatic distance-based level streaming system** for large world management. Instead of manually dividing your world into sublevels:

- The world lives in a **single persistent level file**
- Space is subdivided into **streamable grid cells**
- Cells are automatically loaded/unloaded based on distance from **streaming sources** (typically the player)

## Step-by-Step Implementation

### Step 1: Enable World Partition

**For a new level:**
1. File > New Level > Select **Open World** or **Basic**
2. In the dialog, ensure **World Partition** is checked
3. This also enables One File Per Actor, Data Layers, and HLODs

**For an existing level (conversion):**
1. Tools > Convert Level
2. Or use commandlet:
   ```
   UnrealEditor.exe YourProject -run=WorldPartitionConvertCommandlet YourMap.umap -AllowCommandletRendering
   ```

### Step 2: Configure the Runtime Grid (02:55)

1. Open **World Settings** > **World Partition Setup**
2. Find the **2D Runtime Hash Grid** settings:
   - **Cell Size**: Controls how large each streaming cell is (default ~256m)
   - **Loading Range**: Distance from player at which cells load (default ~768m)
   - **Preview Grids**: Enable to visualize the grid in editor

**Tuning tips:**
- Smaller cells = more granular loading/unloading (more overhead)
- Larger cells = less overhead but coarser streaming
- Loading Range should be larger than the cell size
- **Using more than one grid negatively impacts performance**

### Step 3: Use the Minimap (05:22)

1. Window > World Partition > Editor
2. The minimap shows your entire world with loaded/unloaded regions

**Keyboard shortcuts:**
- **Shift+Drag**: Snap to grid size
- **Double Click**: Move camera to location
- **Shift+Double Click**: Start PIE at location
- **Ctrl+Double Click**: Load region around click
- **MMB+Drag**: Measure distance

### Step 4: Understand "Is Spatially Loaded" (07:20)

Every actor in a World Partition level has this setting in the Details panel:

- **Enabled (checked):** Actor loads/unloads based on proximity to streaming sources. This is the default for most actors.
- **Disabled (unchecked):** Actor is **always loaded** regardless of player position. Use for critical gameplay systems, persistent UI, etc.

**To load a region in editor:**
1. In the World Partition window, drag-select a region
2. Right-click > **Load Region from Selection**

### Step 5: Level Streaming Migration (09:34)

UE4's **Level Streaming Volumes** are replaced by:
- **Location Volumes**: Editor-only volumes for loading/unloading regions
- **Data Layers**: For managing different world states
- World Partition handles runtime streaming automatically

### Step 6: One File Per Actor (10:48)

**What it is:** Each actor is saved as an individual file, enabling:
- Better **version control** (fewer merge conflicts)
- **Collaborative editing** — multiple team members can work on the same world simultaneously
- Enabled by default with World Partition

### Step 7: Data Layers (11:23)

**What they are:** A system for managing different gameplay scenarios in the same world:
- Layer for "Day" vs "Night" — different actors active
- Layer for "Tutorial" vs "Full Game" content
- Actors can be assigned to Data Layers and toggled on/off

### Step 8: Level Instances (11:49)

**What they are:** Reusable level templates that can be instanced across your world:
- Create a level (e.g., a building interior)
- Instance it multiple times in the world
- Edit the source level, all instances update

### Step 9: HLODs — Hierarchical Levels of Detail (12:12)

**What they are:** Automatic LOD generation for distant objects:
- Distant regions are merged into simplified representations
- Reduces draw calls and geometry cost at distance
- Built via: Build > World Partition > Build HLODs

## Essential Console Commands

```
wp.Runtime.ToggleDrawRuntimeHash2D    # Toggle 2D grid debug display
wp.Runtime.ToggleDrawRuntimeHash3D    # Toggle 3D grid debug display
wp.Runtime.OverrideRuntimeSpatialHashLoadingRange -grid=0 -range=1000  # Override loading range
wp.Runtime.HLOD 0                     # View world without HLODs
wp.Runtime.MaxLoadingLevelStreamingCells  # Limit concurrent cell loading
```

## Related Resources

- [Epic Documentation: World Partition](https://dev.epicgames.com/documentation/unreal-engine/world-partition-in-unreal-engine)
- [World Building Guide — Epic Developer Community](https://dev.epicgames.com/community/learning/knowledge-base/r6wl/unreal-engine-world-building-guide)
- [BlackShinobi956: Level Instances Tutorial](https://www.youtube.com/watch?v=simplified-guide-level-instances)


---

## Related

- → Next: [[02_Creating_Open_World_Landscapes_with_Partitioning]]
- 📚 Series: [[_MOC_UE5_World_Partition]]
