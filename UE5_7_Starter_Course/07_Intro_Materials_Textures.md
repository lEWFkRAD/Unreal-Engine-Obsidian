---
title: "Unreal Engine 5 Beginner Tutorial Part 6: Intro to Materials & Textures"
source: "https://www.youtube.com/watch?v=Sic_goW0bPQ"
video_id: "Sic_goW0bPQ"
type: "youtube-summary"
series: "UE5 Starter Course"
episode: 7
tags: [ue5, tutorial, beginner, materials, textures, pbr, material-instance, material-graph]
---

# UE5 Beginner Tutorial Part 6: Intro to Materials & Textures

**Instructor:** Bad Decisions Studio

## Overview
Introduction to UE5's material system — creating materials, understanding PBR properties, material instances for dynamic control, and importing/using PBR texture maps.

## Core Concepts
- **Materials:** Define optical properties (color, shininess, metallicity)
- **Textures:** Patterns (PNG files) applied within materials for detail
- **Material Graph:** Node-based interface for constructing materials
- **Material Instance:** "Child" material allowing real-time parameter tweaking without editing parent graph

## Material Node Shortcuts
- `3 + LMB`: RGB (Color) node
- `1 + LMB`: Constant (float value) node
- `M + LMB`: Multiply node
- `RMB + Drag`: Pan in graph
- `Ctrl + Click` on connection: Break link

## Key Material Properties
- **Base Color:** Overall color (RGB node)
- **Metallic:** 0.0 = non-metal, 1.0 = full metal
- **Specular:** Non-metallic highlight intensity
- **Roughness:** 0.0 = mirror-like, 1.0 = completely rough
- **Emissive Color:** Light emitted by material
- **Emissive Strength:** Multiply Emissive Color by a Constant

## Material Instances Workflow
1. Create Master Material with complex node graph
2. **Convert to Parameter:** RMB on node → Convert to Parameter (name it)
3. **Create Instance:** RMB on Master Material → Create Material Instance
4. Open Instance, enable parameters, adjust in real-time

## Importing PBR Textures
Download from textures.com — typically includes:
- **Albedo** → Base Color
- **Normal** → Normal
- **Roughness** → Roughness
- **Metallic** → Metallic
- **AO** → Ambient Occlusion

## Fixing Texture Tiling
- Use **MF Tiling** material function node
- Connect Result output to UVs input on each texture node
- Control via Material Instance Tiling X/Y parameters

---

## Related

- ← Previous: [[06_Lighting]]
- → Next: [[08_Materials_Textures_Basics]]
- 📚 Series: [[_MOC_UE5_7_Starter_Course]]
