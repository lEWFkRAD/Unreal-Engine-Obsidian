---
title: "Unreal Engine Material Fundamentals: Material Instances"
source: "https://www.youtube.com/watch?v=a7BDJ5zRRL0"
video_id: "a7BDJ5zRRL0"
type: "youtube-summary"
series: "Learn to Code Blueprints"
episode: 0
tags: [ue5, tutorial, blueprint, gamedev, coding]
---

# Unreal Engine Material Instances - Summary

## Key Concepts

### What are Material Instances?
- **Definition**: A "compiled version" or child of a master material. They allow modification of material properties (like color) **without recompiling or editing the original master material**.
- **Core Benefit**: Enables **real-time** or near real-time adjustments in the viewport, dramatically speeding up iteration.
- **Analogy**: Similar to how a **Blueprint** instance works - it uses a pre-compiled parent but allows changes to exposed variables/parameters.

### Parameters: The Gateway to Modification
- In the **Material Editor**, exposed variables are called **Parameters**.
- To make a value changeable in a Material Instance, you must:
    1. **Convert** a **Constant** node into a **Parameter**.
    2. **Name** the parameter meaningfully (e.g., `PlatformColor`, `Metallic`).

## Step-by-Step Process

### Creating and Using a Material Instance
1. **Create the Instance**: Right-click on a Master Material asset > Create Material Instance.
2. **Prepare the Master Material**: Convert Constant nodes to Parameters, save and apply.
3. **Use the Material Instance**: Open it, modify parameter values directly in the Details Panel.
4. **Apply to Actors**: Replace Master Material with Material Instance on mesh components.

## Parameter Types
- **Scalar Parameter**: Single float value (e.g., Metallic, Roughness).
- **Vector Parameter**: 2D, 3D, or 4D values (e.g., Color RGB).
- **Texture Parameter**: For changing textures.

## Key Takeaways
1. Material Instances enable **non-destructive, real-time adjustments**.
2. Convert values to **named Parameters** within the master material.
3. They drastically **reduce iteration time** with immediate visual feedback.
4. They facilitate **material variants and dynamic material control** via Blueprints.

---

## Related

- ← Previous: [[Making_your_level_playable_using_the_Game_Mode]]
- → Next: [[Material_Fundamentals_Working_with_Textures_and_Previewing_Changes]]
- 📚 Series: [[_MOC_Learn_to_Code_Blueprints]]
