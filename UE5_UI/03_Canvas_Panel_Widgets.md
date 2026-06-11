---
title: "Unreal Engine 5 Tutorial - Widgets Part 1: Canvas Panel"
source: "https://www.youtube.com/watch?v=u4tfL6UpRWE"
video_id: "u4tfL6UpRWE"
type: "youtube-summary"
series: "UE5 UI"
episode: 3
tags: [ue5, umg, ui, canvas-panel, anchors, layout, widgets, positioning]
---

# Widgets Part 1: Canvas Panel

**Creator:** Ryan Laley (126K subscribers, established UE5 tutorial creator)
**Duration:** 12:54 | **Views:** 27K | **Published:** April 17, 2024
**Series:** Part 1 of 5 in the Widgets series

## Overview

This tutorial covers the Canvas Panel widget in Unreal Engine 5 UMG. The Canvas Panel is the most commonly used root container for UI layouts, providing absolute positioning with anchoring support for responsive design.

## Widgets Series by Ryan Laley

| Part | Topic | Views |
|------|-------|-------|
| 1 | Canvas Panel (this video) | 27K |
| 2 | Bindings | 11K |
| 3 | Custom Buttons | 14K |
| 4 | Animations | 11K |
| 5 | Controller Support | 22K |

## Key Concepts

### What is a Canvas Panel?
- The default root widget in most Widget Blueprints
- Provides absolute positioning for child widgets
- Children are positioned using X/Y coordinates relative to their anchor
- Supports anchoring for responsive layouts across different screen sizes

### Anchoring System
Anchors determine how a widget's position is calculated and how it responds to screen size changes.

**Anchor Types:**
- **Fixed Anchors** (point): widget stays at a fixed pixel offset from the anchor point
- **Stretch Anchors**: widget stretches to fill a percentage of the parent

**Anchor Presets:**
- Top-Left, Top-Center, Top-Right
- Middle-Left, Center, Middle-Right
- Bottom-Left, Bottom-Center, Bottom-Right
- Full screen stretch (horizontal and vertical)

## Implementation Steps

### 1. Canvas Panel Basics
- Every Widget Blueprint starts with a root widget (usually Canvas Panel)
- Drag widgets from the Palette onto the Canvas Panel
- Position widgets by dragging in the Designer or setting X/Y in Details

### 2. Understanding Position and Offset
Each widget in a Canvas Panel has:
- **Anchors**: define the reference point (0-1 range, where 0.5 is center)
- **Alignment**: which part of the widget is placed at the position (0,0 = top-left, 0.5,0.5 = center)
- **Position (X, Y)**: offset from the anchor point in pixels
- **Size**: width and height (can be fixed or auto-sized)

### 3. Setting Up Anchors
1. Select a widget in the Canvas Panel
2. In Details > Layout > Anchors, choose a preset
3. Or manually set the Minimum and Maximum anchor values:
   - Point anchor: Min and Max are the same value (e.g., 0.5, 0.5)
   - Stretch anchor: Min and Max differ (e.g., 0.0 to 1.0 for full width)

**Example: Centered Title Text**
- Anchor: Center (0.5, 0.5)
- Alignment: Center (0.5, 0.5)
- Position: X=0, Y=-100 (slightly above center)

**Example: Bottom-Right Health Bar**
- Anchor: Bottom-Right (1.0, 1.0)
- Alignment: Bottom-Right (1.0, 1.0)
- Position: X=-20, Y=-20 (20px margin from corner)

**Example: Full-Width Top Bar**
- Anchor: Stretch Horizontal (Min: 0,0 Max: 1,0)
- Position: Left/Right offsets for margins
- Height: fixed value

### 4. Offset Properties
When using stretch anchors:
- **Left**: distance from the left edge of the parent
- **Top**: distance from the top edge of the parent
- **Right**: distance from the right edge of the parent
- **Bottom**: distance from the bottom edge of the parent
- These replace X/Y position for stretched widgets

### 5. Auto-Size vs Fixed Size
- **Auto-Size**: widget sizes to fit its content
  - Enable: Size to Content = true
  - Good for: text labels, buttons that wrap their text
- **Fixed Size**: explicit width and height
  - Set Fill and Size values
  - Good for: images, progress bars, fixed-layout elements

### 6. Nesting Layouts
Canvas Panel works best with nested layout containers:
```
Canvas Panel (root)
  +-- Vertical Box (centered menu)
  |     +-- Text Block (title)
  |     +-- Button (Play)
  |     +-- Button (Settings)
  |     +-- Button (Quit)
  +-- Horizontal Box (top-right HUD)
        +-- Image (health icon)
        +-- Progress Bar (health)
```

### 7. Z-Order
- Widgets drawn later in the hierarchy appear on top
- Set Z-Order in Details > Advanced > Slot > ZOrder
- Higher Z-Order = drawn on top
- Useful for layered UI (background panels behind content)

### 8. Responsive Design Tips
- Always set anchors before positioning
- Use stretch anchors for elements that should fill the screen
- Use point anchors with margins for elements that should stay at edges
- Test at multiple resolutions (16:9, 21:9, 4:3) using Preview Size
- Use DPI Scaling settings in Project Settings for consistent sizing

## Common Patterns

### Centered Menu
```
Canvas Panel
  -> Size Box (width=400, height=auto)
       -> Vertical Box (centered anchor)
            -> Title text
            -> Button 1
            -> Button 2
```

### HUD Corners
```
Canvas Panel
  -> Top-Left: Health bar (anchor 0,0)
  -> Top-Right: Ammo counter (anchor 1,0)
  -> Bottom-Left: Minimap (anchor 0,1)
  -> Bottom-Right: Quest tracker (anchor 1,1)
```

### Full-Screen Overlay
```
Canvas Panel
  -> Image (stretch all sides, semi-transparent background)
       -> Content (centered)
```

## Resources
- Ryan Laley: https://www.ryanlaley.com
- Patreon: https://patreon.com/ryanlaley
- Private Sessions: https://ryanlaley.com/sessions
- Related: Widget Anchors Tutorial by Ryan Laley: https://www.youtube.com/watch?v=hIz9Ft6a4mY
- Epic Widget Blueprints Docs: https://dev.epicgames.com/documentation/unreal-engine/widget-blueprints-in-umg-for-unreal-engine


---

## Related

- ← Previous: [[02_Widget_Best_Practices]]
- 📚 Series: [[_MOC_UE5_UI]]
