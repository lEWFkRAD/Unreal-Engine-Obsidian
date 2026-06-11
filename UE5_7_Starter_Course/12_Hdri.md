---
title: "Unreal Engine 5 Beginner Tutorial Part 11: HDRI"
source: "https://www.youtube.com/watch?v=8Q1tupS8npY"
video_id: "8Q1tupS8npY"
type: "youtube-summary"
series: "UE5 Starter Course"
episode: 12
tags: [ue5, tutorial, beginner, hdri, backdrop, environment, lighting, glass-material]
---

# UE5 Beginner Tutorial Part 11: HDRI

**Instructor:** Bad Decisions Studio | **Length:** 12:22 | **Published:** 2024-03-09

## Overview
Using HDRI (High Dynamic Range Image) as realistic background and light source. Covers importing, configuring, and positioning HDRIs plus glass materials.

## Step-by-Step Guide

### 1. Downloading HDRI
- **Source:** Free space HDRIs from RenderCrate (e.g., "Orbital 10 Sunset")
- Download the **4K HDR version**

### 2. Importing & Preparing
- Drag HDR file into Content Browser
- **Critical:** Double-click texture → change **MIP Gen Settings** to **No MIP Maps** (prevents compression)

### 3. Adding HDRI Backdrop
- Add **HDRI Backdrop Actor**
- **Scale Size:** 3,500 (distant background)
- **Intensity:** 1 (adjust as needed)

### 4. Configuring the Dome
- Default dome includes floor (not suitable for space)
- **Solution:** Change mesh to **Skybox** (from Starter Content)

### 5. Positioning
- **Rotate** using Z-axis (E key) to face desired direction
- **Projection Center:** X: 90,000, Z: 75,000 (adjust 50K-80K to tilt)
- **Scale:** 3,500 recommended

### 6. Adding Glass Window
- Duplicate box mesh, position over opening
- Apply **M_GlassMaterial** from Starter Content
- Adjust Post Process Volume → Reflections for quality

## Performance Optimization
- If lagging: Settings → Engine Scalability Settings → change from Cinematic to High/Medium
- Keep settings low while editing, switch to Cinematic for final renders

## Key Insight
HDRI provides both visual backdrop and lighting, dramatically increasing scene realism with minimal setup. Glass materials + HDRI reflections create highly convincing environments.

---

## Related

- ← Previous: [[11_Post_Process_Volume]]
- → Next: [[13_Importing_Assets]]
- 📚 Series: [[_MOC_UE5_7_Starter_Course]]
