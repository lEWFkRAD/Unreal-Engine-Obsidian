---
title: "How To Build Menus And UI In UE5 - Beginner Tutorial"
source: "https://www.youtube.com/watch?v=198AMGtdo-E"
video_id: "198AMGtdo-E"
type: "youtube-summary"
series: "UE5 UI"
episode: 1
tags: [ue5, umg, ui, menus, widget-blueprint, hud, blueprint]
---

# How To Build Menus And UI In UE5

**Creator:** Tinkr Academy (VR and UE5 tutorials)
**Duration:** 35:39 | **Published:** Introductory UMG tutorial

## Overview

This tutorial provides an introduction to creating user interfaces inside Unreal Engine 5 using UMG (Unreal Motion Graphics). It covers the fundamentals of Widget Blueprints, how to display UI on screen, and how to create functional menus with buttons.

## Key Concepts

### UMG (Unreal Motion Graphics)
- UE5's visual UI design framework
- Widget Blueprints are the core asset type
- Two modes: Designer (visual layout) and Graph (Blueprint logic)

### Widget Blueprint Structure
- **Designer Tab**: drag-and-drop UI elements, arrange layout
- **Graph Tab**: Blueprint logic for interactivity
- **Palette Panel**: list of available UI widgets
- **Hierarchy Panel**: widget tree structure
- **Details Panel**: selected widget properties

## Implementation Steps

### 1. Create a Widget Blueprint
- Content Browser > Right-click > User Interface > Widget Blueprint
- Name it (e.g., WBP_MainMenu)
- Double-click to open the Widget Blueprint Editor

### 2. Design the Menu Layout
Common menu elements:
- **Canvas Panel**: root container for absolute positioning
- **Vertical Box**: stacks elements vertically (great for menus)
- **Horizontal Box**: stacks elements horizontally
- **Text Block**: static text display
- **Button**: clickable, interactive element
- **Image**: display graphics/icons

For a main menu:
1. Add a Canvas Panel as root
2. Add a Vertical Box centered on screen
3. Add Text Block for title ("Main Menu")
4. Add Buttons for each menu option (Play, Settings, Quit)

### 3. Style the Buttons
- Select the Button in the Designer
- In Details > Style:
  - Normal: default appearance
  - Hovered: color/appearance when mouse is over
  - Pressed: color/appearance when clicked
- Add a Text Block child to each button for the label
- Use Padding and Size settings for spacing

### 4. Add Button Functionality
In the Graph tab:
1. Select the button and add OnClicked event
2. For "Play" button:
   - Use Open Level node to load the game level
   - Or use Set Game Mode to switch modes
3. For "Settings" button:
   - Create and display a settings widget
4. For "Quit" button:
   - Use Quit Game node

### 5. Display the Widget on Screen
From your Game Mode or Player Controller:
1. Create Widget: use Create Widget node, select your WBP class
2. Add to Viewport: use Add to Viewport node
3. Set Input Mode: use Set Input Mode UI Only (for menus)
   - This shows the cursor and routes input to UI
   - For in-game HUD, use Set Input Mode Game Only

### 6. Set Up the Game Mode
- Create a new Game Mode Blueprint
- In Event BeginPlay:
  1. Create the main menu widget
  2. Add to viewport
  3. Set input mode to UI Only
  4. Set Show Mouse Cursor = true

### 7. Navigation Between Menus
- Each menu is a separate Widget Blueprint
- When opening a submenu:
  1. Remove current widget from viewport (or set visibility to collapsed)
  2. Create and add the new submenu widget
- When going back:
  1. Remove current submenu
  2. Re-add the previous menu

### 8. Anchoring
- Anchors control how UI elements respond to different screen sizes
- Set anchors in the Designer for each widget
- Center anchor: stays centered regardless of resolution
- Corner anchors: stick to corners
- Stretch anchors: scale with screen size

## Blueprint Function Libraries
- Create reusable functions for common UI operations
- Example: ShowWidget(), HideWidget(), ToggleWidgetVisibility()
- Access from any Blueprint without direct reference

## Common Patterns
- Main Menu: full screen, UI Only input mode, shows cursor
- In-Game HUD: Game Only input mode, no cursor, overlaid on gameplay
- Pause Menu: toggle visibility, switch input mode temporarily
- Settings Menu: sliders for volume, dropdowns for graphics quality

## Tips
- Use Size Box to constrain widget dimensions
- Use Spacer widgets for consistent gaps between elements
- Test at multiple resolutions using the Preview Size settings
- Widget Components can be attached to 3D objects for world-space UI

## Resources
- Tinkr Academy: https://tinkr.academy
- VR Ultimate Course: https://tinkr.academy/vr-ultimate-course
- Epic UMG Documentation: https://dev.epicgames.com/documentation/unreal-engine/widget-blueprints-in-umg-for-unreal-engine


---

## Related

- → Next: [[02_Widget_Best_Practices]]
- 📚 Series: [[_MOC_UE5_UI]]
