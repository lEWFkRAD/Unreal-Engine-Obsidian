---
title: "UE Blueprint Fundamentals | Class #6-4 | UI Button Materials"
source: "https://www.youtube.com/watch?v=cVh0JWg3ff8"
video_id: "cVh0JWg3ff8"
type: "youtube-summary"
series: "Blueprint Fundamentals"
episode: 6
tags: [ue5, tutorial, blueprint, fundamentals, gamedev, visual-scripting]
---

# UE Blueprint Fundamentals: UI Button Materials

## Overview
- **Channel**: Ask A Dev
- **Duration**: 25:06
- **Focus**: Create a single reusable material for UI buttons using texture channel separation

## Core Concept
Use a texture with separated channels (red = border, green = fill) to enable color customization via material instances without recompiling.

## Material Creation & Setup

### 1. Material Domain
- Change material domain to **User Interface** (not Surface)
- Set **Blend Mode** to **Masked** (not Translucent)

### 2. Texture Channel Separation
- **Red Channel**: Border mask
- **Green Channel**: Fill mask
- **Alpha Channel**: Shape (button outline)

### 3. Masking Math
```
Border Mask = Red Channel × Alpha Channel
Fill Mask = Green Channel × Alpha Channel
```

**Debugging Tip**: Right-click any node → "Start Previewing Node" to visualize intermediate steps

### 4. Color Customization with Parameters
- **BorderColor**: Convert constant to parameter
- **FillColor**: Convert constant to parameter
- **Final Color**: `(Border Mask × BorderColor) + (Fill Mask × FillColor)`

### 5. Gradient Control System
- **Linear Gradient Node**: Applied to fill
- **Direction Flip**: `OneMinus` node (1 - Gradient Value)
- **Erosion Control**: `Power` node — higher exponent = more erosion
- Create parameter: `GradientErode` (default: 1, min: 1)

### 6. Transparency & Final Output
- **Opacity Mask**: Alpha channel directly to opacity mask output
- **Value Clamping**: Use `Saturate` node (free on modern GPUs)

## Implementation in UMG

### Material Instance Creation
- Right-click master material → **Create Material Instance**
- Instances allow real-time parameter editing without recompilation

### Applying to UI
1. Select button/image element in UMG widget
2. Details panel → Style → Image → Select material instance
3. Adjust Border Margin settings to prevent stretching

### Parameter Customization
- **BorderColor**: Change any color instantly
- **FillColor**: Change any color instantly
- **GradientErode**: Control gradient intensity

## Best Practices
- **Saturate > Clamp**: Free on most modern GPUs
- **Single Material Instance**: Reduces draw calls
- **Texture Design**: Red channel (border), Green channel (fill), Alpha (shape)
- Use `Power` node for gradient falloff control

---

## Related

- ← Previous: [[BP_Class_6-3_UI_Buttons_Style_Variables]]
- → Next: [[BP_Class_6-5_UI_Reusable_Widgets]]
- 📚 Series: [[_MOC_Blueprint_Fundamentals]]
