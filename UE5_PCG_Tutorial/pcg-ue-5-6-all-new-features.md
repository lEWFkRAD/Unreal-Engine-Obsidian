---
title: "PCG in Unreal Engine 5.6 – All New Features"
source: "https://www.youtube.com/watch?v=xR4So-MYWq0"
video_id: "xR4So-MYWq0"
type: "youtube-summary"
series: "UE5 PCG Tutorial"
episode: 0
tags: [ue5, tutorial, pcg, features, gamedev, procedural]
---

# PCG in Unreal Engine 5.6 – All New Features

**Channel:** PolyBoost | **Published:** 2025-06-08 | **Length:** 02:45

## Overview
UE 5.6 brings a major leap forward in PCG workflows. From multi-threaded graph execution to GPU-accelerated point scattering, this version gives developers powerful tools to build massive, dynamic worlds faster.

## New Features

### 1. Multi-Threaded Execution
- PCG graphs now automatically run across multiple CPU cores.
- Graph evaluation can be **3 to 5x faster** in heavy scenes with thousands of points.
- Demonstrated with 2,500 high-detail trees.

### 2. GPU Scattering & Optimization
- PCG now supports **GPU-based scattering**.
- Nodes like Copy Points and Scatter can process data on the GPU.
- Perfect for micro details: foliage, pebbles, moss.
- **Lazy GPU Readbacks**: Data only returns to CPU when absolutely necessary = faster rendering, lower overhead.

### 3. PCG Biome Core V2 (Experimental)
- Layer multiple biomes (e.g., snowy tundra → forest) using **weight maps and masks**.
- Each biome can have its own local caching and PCG graph.
- Great for massive open worlds or stylized zones.

### 4. Metadata Improvements
- New metadata domains: `@points`, `@data`, `@control points` for precise filtering.
- Point storage now uses **structure of arrays** format = reduced memory, better performance.

## Key Takeaways
- 3-5x faster graph execution via multi-threading.
- GPU scattering enables micro-detail at scale.
- Biome Core V2 allows layered ecosystem blending.
- Structure of arrays metadata = significant memory savings.

---

## Related

- ← Previous: [[create-dynamic-cables-in-ue5]]
- → Next: [[post-apocalyptic-car-wall-pcg-splines-part1]]
- 📚 Series: [[_MOC_UE5_PCG_Tutorial]]
