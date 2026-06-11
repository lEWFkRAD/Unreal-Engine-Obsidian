---
title: "Advanced Glass Material"
source: "https://www.youtube.com/watch?v=bahRaP4uA3o"
video_id: "bahRaP4uA3o"
type: "youtube-summary"
series: "UE5 Materials"
episode: 1
tags: [ue5, materials, glass, shaders]
---

# Advanced Glass Material

**Source:** https://www.youtube.com/watch?v=bahRaP4uA3o

## Overview

- **Creator:** WorldofLevelDesign (83.5K subscribers)
- **Published:** Sep 25, 2025
- **Duration:** 36:26
- **Focus:** Creating a highly customizable glass material in Unreal Engine 5 with granular controls

## Content

### Core Objective

Create a glass material with extensive, artist-friendly controls for:
- **Opacity** — transparency and refraction
- **Roughness** — surface smoothness vs. frosted appearance
- **Normal Maps** — surface detail and imperfections
- **Base Color** — tinting and coloring the glass

### Tutorial Chapters

1. **Introduction** (0:00)
2. **Setup and Creating Material** (1:12)
   - Create a new Material asset in the Content Browser
   - Set Material Domain to **Surface**
   - Set Blend Mode to **Translucent**
   - Set Shading Model to **Surface TranslucencyVolume** (for realistic glass)
3. **Glass Material Properties** (1:51)
   - Configure the Material for physically-based glass rendering
   - Enable Screen Space Refractions in material settings
4. **Initial Glass Setup** (2:55)
   - Connect basic Opacity and Base Color nodes
   - Set up a Fresnel node for edge-vs-center opacity falloff
   - Use **Scalar Parameter** nodes to expose controls to material instances
5. **Expanding Roughness Controls** (8:05)
   - Add roughness parameter with 0.0–1.0 range
   - Layer procedural noise for subtle surface variation
   - Connect normal map to roughness for frosted glass effects
6. **Expanding Normal Map Controls** (20:46)
   - Add normal map parameter slots
   - Use **FlattenNormal** node to control normal intensity
   - Blend multiple normal maps for layered detail (base + scratches + fingerprints)
7. **Expanding Opacity Controls** (24:46)
   - Drive opacity with Fresnel for natural glass falloff
   - Add scalar parameter for global opacity multiplier
   - Wire **Refraction** node for light bending through glass
8. **Expanding Base Color Controls** (30:51)
   - Add color parameter for glass tinting
   - Use Fresnel to darken edges naturally
   - Optional: connect a texture parameter for patterned/stained glass
9. **Master Material Creation** (35:51)
   - Review all exposed parameters
   - Create **Material Instance** from the master material
   - Demonstrate switching between clear, frosted, colored, and textured glass

### Key Node Setup

```
Material Domain: Surface
Blend Mode: Translucent
Shading Model: Surface TranslucencyVolume

Nodes:
- Fresnel (Exponent: 3-5) → Opacity
- ScalarParameter "Opacity" → Multiply with Fresnel → Opacity
- ScalarParameter "Roughness" → Roughness
- TextureSampleParameter "NormalMap" → FlattenNormal → Normal
- VectorParameter "GlassColor" → BaseColor
- ScalarParameter "Refraction" → Refraction
```

### Creating a Material Instance

1. Right-click the master material → **Create Material Instance**
2. In the Material Instance, adjust exposed parameters without recompiling
3. Create presets for: clear glass, frosted glass, tinted glass, stained glass

### Tips

- Use **Fresnel** heavily — real glass has edge-to-center opacity variation
- Keep roughness low (0.0–0.1) for clear glass, higher (0.3–0.8) for frosted
- For refraction, values near 1.0 are subtle; 1.3–1.5 mimics real glass IOR
- Material Instances are more performant than duplicating master materials

## Related

- Next: [[02_Layered_Material_Workflow|Layered Material Workflow]] (Episode 2)
- Series MOC: [[UE5_Materials_MOC|UE5 Materials MOC]]
