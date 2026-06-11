---
title: "Parallax Occlusion Mapping"
source: "https://www.youtube.com/watch?v=h0xytNFiqbQ"
video_id: "h0xytNFiqbQ"
type: "youtube-summary"
series: "UE5 Materials"
episode: 3
tags: [ue5, materials, pom, shaders]
---

# Parallax Occlusion Mapping

**Source:** https://www.youtube.com/watch?v=h0xytNFiqbQ

## Overview

- **Creator:** PrismaticaDev (78.4K subscribers)
- **Series:** 5-Minute Materials [UE5]
- **Focus:** Parallax Occlusion Mapping (POM) — creating fake 3D depth in 2D materials
- **Duration:** ~5 minutes

POM is described as the "older brother of BumpOffset" — a more advanced shader technique for simulating depth on flat surfaces.

## Content

### What is Parallax Occlusion Mapping?

Parallax Occlusion Mapping is a shader technique that creates the illusion of **3D depth on flat geometry** by:
1. Ray-marching through a height map in screen space
2. Finding the intersection point of the view ray with the heightfield
3. Offset-texturing the surface to simulate depth

Unlike simple BumpOffset (which does a single offset), POM uses **multiple steps** to trace the ray, producing:
- Self-occlusion (near geometry hides far geometry)
- Self-shadowing (shadows cast by depth features)
- Proper parallax at steep viewing angles

### Setting Up POM in UE5

1. **Create a Material** with the following texture inputs:
   - **Height Map** (grayscale) — drives the depth effect
   - **Normal Map** — for surface detail
   - **Base Color / Albedo** — surface color
   - **Roughness Map** — surface smoothness

2. **Add the Parallax Occlusion Mapping node:**
   - In the Material Editor, search for `ParallaxOcclusionMapping`
   - Connect your **Height Map** to the `Height` input
   - Set **Height Ratio** (controls depth intensity, typically 0.02–0.1)

3. **Key Parameters:**
   - **Height Ratio:** Controls depth intensity. Start with 0.05; higher = deeper
   - **Min/Max Steps:** Number of ray-march steps. More = higher quality, more expensive
     - Low: 8–16 steps
     - Medium: 16–32 steps
     - High: 32–64 steps
   - **Refinement Steps:** Additional steps at the intersection for accuracy

4. **Connect POM output to Texture Coordinates:**
   - The POM node outputs offset UVs
   - Feed these offset UVs into all texture samplers (Base Color, Normal, Roughness)
   - This ensures all maps sample from the same displaced position

### Example Node Graph

```
TextureCoordinate → ParallaxOcclusionMapping
                        ↑ Height Map
                        ↑ Height Ratio (0.05)
                        ↑ Min Steps (16)
                        ↑ Max Steps (32)
                        ↓ (offset UVs)
                    TextureSample (BaseColor)
                    TextureSample (Normal)
                    TextureSample (Roughness)
```

### POM vs BumpOffset vs Tessellation

| Feature | BumpOffset | POM | Tessellation |
|---------|-----------|-----|-------------|
| Quality | Low | Medium-High | Highest |
| Performance | Very cheap | Moderate | Expensive |
| Self-occlusion | No | Yes | Yes |
| Self-shadowing | No | Yes | Yes |
| Geometry displacement | No | No | Yes |
| Best for | Subtle depth | Bricks, tiles, cracks | Terrain, close-up detail |

### Optimization Tips

- **Adjust step count** based on distance — use fewer steps for distant surfaces
- Use **Quality Switch** nodes to reduce steps on lower quality settings
- POM works best on **flat or gently curved surfaces** — steep curves cause distortion
- Combine with **World Position Offset** for additional parallax tricks
- Profile GPU cost with `stat GPU` — POM can be expensive with high step counts

### Common Use Cases

- Brick walls and cobblestone paths
- Floor tiles with grout depth
- Cracked concrete surfaces
- Rock face detail on flat cliff meshes
- Decals with depth (road markings on asphalt)

### Related PrismaticaDev Resources

- Patreon: [prismaticadev](https://www.patreon.com/prismaticadev)
- Discord: [prismaticadevlearninghub](https://discord.gg/prismaticadevlearninghub)
- Marketplace Plugin: Prismatiscape Interaction Plugin

## Related

- Previous: [[02_Layered_Material_Workflow|Layered Material Workflow]] (Episode 2)
- Series MOC: [[UE5_Materials_MOC|UE5 Materials MOC]]
