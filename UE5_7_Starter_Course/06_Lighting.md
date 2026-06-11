---
title: "Unreal Engine 5 Beginner Tutorial Part 5: Lighting"
source: "https://www.youtube.com/watch?v=19p7M8fvluo"
video_id: "19p7M8fvluo"
type: "youtube-summary"
series: "UE5 Starter Course"
episode: 6
tags: [ue5, tutorial, beginner, lighting, directional-light, point-light, spot-light, area-light, fog]
---

# UE5 Beginner Tutorial Part 5: Lighting

**Instructor:** Bad Decisions Studio | **Part of 19-part series**

## Overview
Fundamental lighting concepts in UE5 — common light types, settings, fog systems, and practical workflow for building atmospheric scenes.

## Key Quote
"Lighting is probably one of the most important parts of 3D — without it, your models as beautiful as they might be will look like crap because the lighting is bad."

## Environment Light Mixer
- **Access:** Window → Environment Light Mixer
- Quickly create realistic outdoor lighting with sky, clouds, and sun
- Enable all components: Skylight, Atmospheric Light, Sky Atmosphere, Volumetric Cloud, Height Fog
- `Ctrl + L` to adjust sun position

## Light Types & Settings

### 1. Directional Light (Sun/Global)
- **Intensity:** Measured in Lux
- **Source Angle:** Larger = softer shadows
- **Color:** Disable "Use Temperature" for stylized colors
- **Indirect Lighting Intensity:** Controls light bounce/ambient
- **Volumetric Scattering Intensity:** Works with fog for light rays

### 2. Point Light (Light Bulb)
- Omnidirectional, more performance-intensive
- **Attenuation Radius:** How far light reaches
- **Source Radius/Length:** Affects shadow characteristics

### 3. Spot Light (Theater Spotlight)
- Directional cone light
- **Inner/Outer Cone Angles:** Control light falloff
- **E** to rotate direction, **G** to toggle overlays

### 4. Rectangular/Area Light (Instructor Favorite)
- Emits light from a rectangular surface
- **Width/Height:** Control source size and shadow softness
- **Barn Door Angle/Length:** Creates directional shutters

## Exponential Height Fog
- Enable via Environment Light Mixer
- **Critical:** Enable "Volumetric Fog" for visible light rays
- **Fog Density:** Controls thickness

## Pro Tips
- Slider values can exceed default limits — type manually
- Point lights are more expensive than directional lights
- Light in phases — rough first, then refine
- Use blockout geometry to plan lighting placement

---

## Related

- ← Previous: [[05_Modeling_Tools_Advanced]]
- → Next: [[07_Intro_Materials_Textures]]
- 📚 Series: [[_MOC_UE5_7_Starter_Course]]
