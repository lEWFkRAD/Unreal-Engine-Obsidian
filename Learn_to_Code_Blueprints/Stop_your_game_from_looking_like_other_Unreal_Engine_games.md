---
title: "Stop your game from looking like other Unreal Engine games"
source: "https://www.youtube.com/watch?v=GWCe11YhqSQ"
video_id: "GWCe11YhqSQ"
type: "youtube-summary"
series: "Learn to Code Blueprints"
episode: 0
tags: [ue5, tutorial, blueprint, gamedev, coding]
---

# Stop Your Game from Looking Like Other Unreal Engine Games

## Overview
Tutorial on customizing default UE5 lighting and post-processing to achieve a unique visual style.

## Core Philosophy
The default Unreal Engine lighting is common and not ideal for creating a distinctive game. Use **Post-Process Volumes** and environmental adjustments to create a personalized, higher-quality result.

## Step-by-Step Customization

### 1. Post-Process Volume Setup
- Add a **Post Process Volume** from the Visual Effects category.
- Enable **"Infinite Extent (Unbound)"** to apply the effect globally.

### 2. Key Adjustments Within the Post-Process Volume
- **Exposure Control**:
  - Change Exposure Method from `Auto` to `Manual`.
  - Adjust **Exposure Compensation** to **`10`** as a starting value.
  - Toggle the volume on/off and use High-Resolution Screenshots to compare results.
- **Lens Flares**:
  - Enable Lens Flares for subtle effects when looking towards light sources.
  - Adjust **Intensity** (start with `1`) and **Tint**.

### 3. Environment and Atmosphere
- **Sky Atmosphere**: Modify **Mie Scattering Scale** to **`0.098`**.
- **Volumetric Fog**: Add **Exponential Height Fog**, enable **Volumetric Fog**, set **Volumetric Scattering Scale** to **`26`**.

### 4. Directional Light Effects (God Rays)
- Select your **Directional Light**.
- Enable **"Light Shaft"** settings (Bloom, Occlusion) for volumetric "god rays."
- Adjust Bloom settings to control brightness and range.

## Key Result
The combination creates a dramatic visual difference - "night and day" compared to the default engine look. Features controlled exposure, atmospheric scattering, volumetric fog, and stylized light rays.

## Final Takeaway
> "Whatever you have created, remember it's your work. You can only go up from here."

---

## Related

- ← Previous: [[Start_Decorating_Your_Level]]
- → Next: [[Using_a_Paragon_asset_for_our_main_character]]
- 📚 Series: [[_MOC_Learn_to_Code_Blueprints]]
