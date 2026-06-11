---
title: "Unreal Engine 5 Beginner Tutorial Part 3: Modelling Tools Basics"
source: "https://www.youtube.com/watch?v=nXOwczODahY"
video_id: "nXOwczODahY"
type: "youtube-summary"
series: "UE5 Starter Course"
episode: 4
tags: [ue5, tutorial, beginner, modeling, 3d-modeling, primitives, path-extrude]
---

# UE5 Beginner Tutorial Part 3: Modelling Tools Basics

**Instructor:** Bad Decisions Studio | **Length:** 33:39 | **Published:** 2024-03-05 | **Views:** 364,056

## Overview
Introduction to UE5's built-in Modeling Tools (beta plugin). Covers enabling the tools, primitives, Cube Grid for level blocking, and Path Extrude for complex shapes.

## Enabling Modeling Tools
1. Go to **Edit > Plugins**
2. Search for "Modeling"
3. Enable **"Modeling Tools Editor Mode"**
4. Restart the engine — Modeling tab appears in viewport toolbar

## Core Modeling Tools

### 1. Primitives (Create Tab)
- Create cubes, spheres, stairs directly in engine with extra controls
- **Subdivisions:** Controls polygon count (low poly vs high poly)
- Always click **Accept** to confirm changes

### 2. Cube Grid
- **Purpose:** Quickly block out scenes/levels (like Minecraft/Roblox)
- Create grid on floor, click and drag to select areas
- **E** (Push) and **Q** (Pull) to extrude shapes
- Change **Blocks per Step** for faster building

### 3. Path Extrude
- **Purpose:** Extrude a 2D path into 3D for complex shapes
- **Enable Snapping:** Set Move Snap to 100 for grid-aligned drawing
- **Rounded Corners:** Toggle in left toolbar during creation
- **Interactive Mode:** Use sliders (avoid "Fixed" mode — crash risk)
- Used to create hexagonal spaceship hangar base shape

## Essential Workflow Techniques

### Reference & Measurement
- **PureRef:** Free tool to overlay reference images on screen
- **Measuring:** Switch to Orthographic View → Wireframe Mode → Middle Mouse Button drag
- Set units to meters: Edit > Editor Preferences > Viewports > Measuring Tool Units

### Pivot Point Editing
- Select mesh → Modeling > XForm > Edit Pivot
- Use predefined options (Front, Center, Bottom) or manual sliders

### Material Quick-Swap
- **Folder with Magnifying Glass:** Locates asset in Content Browser
- **Left Arrow Button:** Applies currently selected asset from Content Browser to mesh

## Project Application
- Built Star Wars Imperial hangar (~100m length, ~50m height)
- Used Path Extrude for hexagonal base, measured and scaled to correct dimensions

---

## Related

- ← Previous: [[03_Navigating_The_Interface]]
- → Next: [[05_Modeling_Tools_Advanced]]
- 📚 Series: [[_MOC_UE5_7_Starter_Course]]
