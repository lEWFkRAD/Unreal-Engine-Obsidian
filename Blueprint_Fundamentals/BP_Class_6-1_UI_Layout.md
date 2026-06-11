---
title: "UE Blueprint Fundamentals | Class #6-1 | UI Layout"
source: "https://www.youtube.com/watch?v=GXkmR6bFQYI"
video_id: "GXkmR6bFQYI"
type: "youtube-summary"
series: "Blueprint Fundamentals"
episode: 6
tags: [ue5, tutorial, blueprint, fundamentals, gamedev, visual-scripting]
---

# UE Blueprint Fundamentals: UI Layout

## Overview
- **Channel**: Ask A Dev
- **Duration**: 58:13
- **Focus**: Beginners' guide to thinking about and building UI layouts in Unreal Engine
- **Core Concept**: Treat UI design like building with Legos — plan how to "cut" your interface into reusable pieces and assemble them using UE's layout panels

## Planning & Mockups
1. **Create a Visual Mockup** of the desired final UI
2. **"Slice and Dice" the Mockup** into individual image assets
   - Export as PNG or TGA (JPEG doesn't support transparency)
3. **Plan the Layout Hierarchy** as a tree structure

## Widget Blueprint Fundamentals
- **Create**: Content Browser > User Interface > Widget Blueprint > User Widget
- **Editor Layout**:
  - **Palette** (Top-Left): All available UI widgets
  - **Hierarchy** (Bottom-Left): Tree structure of UI
  - **Designer** (Middle): Visual canvas for layout
  - **Details** (Top-Right): Properties for selected widget

### Adding Widget to Game
1. **Via Component**: Add Widget component to character blueprint, set Draw Space to Screen
2. **Via Blueprint (Recommended)**: In BeginPlay, `Create Widget` → `Add to Viewport`
   - Advantage: Fills entire screen automatically, scales with viewport

## Layout Panels

### Border
Container for a single child, often used for padding or background.

### Overlay
Allows multiple children to be **stacked on top of each other**. Key property: Alignment.

### Canvas Panel
"Designer-friendly panel" for **absolute positioning**. Best for manually placing UI elements at exact pixel locations.

### Horizontal Box & Vertical Box
Flow layouts that arrange children in a row (Horizontal) or column (Vertical).
- **Auto**: Sizes to child's natural size
- **Fill**: Stretches to take up remaining space
- **Common Technique**: Nest boxes to create grid-like layouts

> "I often change the background color of a border or widget temporarily to visualize the actual size and position of my layout containers."

## Practical Workflow
1. Create a Master Widget (e.g., `WBP_HUD`)
2. Choose a Root Panel (Overlay used here)
3. Build Sub-Layouts using Vertical/Horizontal Boxes
4. Import art assets (PNGs with transparency)
5. Assign textures to Image widgets via Brush settings
6. Adjust spacing with Padding and Size Box widgets

## Best Practices
- Use **power-of-two** texture dimensions (64x64, 128x128)
- Use **Anchors** for responsive layouts
- Temporarily color backgrounds to visualize container sizes
- Keep font styles consistent (2-3 max)

---

## Related

- ← Previous: [[BP_Class_5_For_Loops_and_Arrays]]
- → Next: [[BP_Class_6-2_UI_Input_Modes]]
- 📚 Series: [[_MOC_Blueprint_Fundamentals]]
