---
title: "Creating Open World Landscapes with Partitioning and Level Streaming in UE5"
source: "https://www.youtube.com/watch?v=B2f6EoOXRHg"
video_id: "B2f6EoOXRHg"
type: "youtube-summary"
series: "UE5 World Partition"
episode: 2
tags: [ue5, world-partition, landscape, open-world, height-map, level-streaming, terrain]
---

# Creating Open World Landscapes with Partitioning and Level Streaming in UE5

**Creator:** Aziel Arts
**Duration:** ~20 min | **Published:** April 8, 2025

## Overview

A practical tutorial on creating **large open-world landscapes** in UE5, covering landscape generation, height map import, and World Partition configuration for efficient streaming. Aimed at environment artists and game developers building expansive outdoor environments.

## Step-by-Step Implementation

### Step 1: Create a Large Landscape

1. **Open the Landscape Tool:** Landscape mode in the toolbar
2. **Configure landscape settings:**
   - **Section Size**: Determines the resolution per landscape component
   - **Sections Per Component**: How many sections per component
   - **Number of Components**: Total grid of components (e.g., 8x8 for a large landscape)
   - **Overall Resolution**: Total vertex count — higher = more detail but more memory

**For a 4km x 4km landscape:**
```
Section Size: 63x63
Sections Per Component: 1
Components: 8x8
Total Resolution: 505x505
```

3. **Enable "Open World"** in the landscape creation dialog — this automatically enables World Partition

### Step 2: Import a Height Map

1. In the Landscape tool, select **Import from File**
2. Use a **RAW 16-bit** or **PNG** height map
3. **Free height map sources:**
   - [Motion Forge Pictures](https://www.motionforgepictures.com/height-maps/)
   - TerrainParty for real-world elevation data
   - World Machine or Gaea for procedural generation
4. **Import settings:**
   - Match the resolution to your landscape dimensions
   - Select the appropriate **Layer Info** for material assignment

### Step 3: Configure World Partition for the Landscape

1. Open **World Settings** > **World Partition**
2. Configure the **Runtime Grid:**
   - **Cell Size**: Match to your landscape sections (e.g., 256m per cell)
   - **Loading Range**: Set based on your visibility needs (e.g., 2-3x cell size)
3. The landscape components will automatically be assigned to grid cells

### Step 4: Set Up Level Streaming

World Partition handles streaming automatically, but you can fine-tune:

1. **Landscape Streaming Proxies** are created automatically for each landscape component
2. **Non-landscape actors** (foliage, props, lights) use the same grid
3. Set **"Is Spatially Loaded"** appropriately per actor

### Step 5: Apply Landscape Materials

1. Create a **Landscape Material** with landscape-specific nodes:
   - **Landscape Layer Blend** — blends materials based on painted layers
   - **Landscape Coords** — maps UVs correctly across the landscape
2. Paint layers (grass, rock, dirt, etc.) using the Landscape Paint tool
3. Material automatically applies per-component through World Partition

### Step 6: Add Foliage

1. Use the **Foliage Tool** to paint foliage across the landscape
2. Foliage instances are automatically managed by World Partition
3. For large landscapes, consider:
   - **Nanite-enabled foliage meshes** for static foliage
   - **PCG (Procedural Content Generation)** for automated placement
   - Appropriate **cull distances** on foliage types

## Landscape Optimization Tips

- Use **LOD Bias** on landscape components to reduce triangle count at distance
- Enable **Virtual Texturing** for landscape materials to reduce texture memory
- Use **HLODs** to merge distant landscape regions with their props into simplified representations
- Keep landscape material layers to a reasonable number — each layer adds shader cost

## Free Resources

- [Free UE5 Landscape Material](https://www.azielarts.com/aa-material)
- [GPU Foliage Scattering Tool](https://www.azielarts.com/aa-material-thankyou-qs)
- [Epic's Landscape Technical Guide](https://dev.epicgames.com/documentation/en-us/unreal-engine/landscape-technical-guide-in-unreal-engine)
- [Free Height Maps](https://www.motionforgepictures.com/height-maps/)

## Related Resources

- [Epic Documentation: World Partition](https://dev.epicgames.com/documentation/unreal-engine/world-partition-in-unreal-engine)
- [Epic Documentation: Landscape Technical Guide](https://dev.epicgames.com/documentation/en-us/unreal-engine/landscape-technical-guide-in-unreal-engine)
- [Smart Poly: Make An Open World Map in 20 Mins — UE5](https://www.youtube.com/watch?v=make-open-world-20-mins)


---

## Related

- ← Previous: [[01_UE5_World_Partition_Tool_Tutorial]]
- → Next: [[03_UE5_5_4_World_Partition_and_HLODs]]
- 📚 Series: [[_MOC_UE5_World_Partition]]
