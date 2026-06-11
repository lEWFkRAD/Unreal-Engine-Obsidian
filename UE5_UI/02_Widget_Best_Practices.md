---
title: "Best Practices for Creating and Managing Widgets"
source: "https://www.youtube.com/watch?v=7b7a20j0azc"
video_id: "7b7a20j0azc"
type: "youtube-summary"
series: "UE5 UI"
episode: 2
tags: [ue5, umg, ui, widgets, hud, best-practices, macro-library, performance]
---

# Best Practices for Creating and Managing Widgets

**Creator:** Kekdot (Two-person game studio)
**Duration:** 47:21 | **Views:** 138K | **Published:** January 1, 2023

## Overview

This tutorial covers best practices for creating and managing UI Widgets within the Blueprint HUD class in UE5. It focuses on performance optimization, organization patterns, and using Macros and Function Libraries to streamline UI development.

## Video Chapters

| Timestamp | Topic |
|-----------|-------|
| 0:00 | Intro |
| 0:25 | Overview |
| 1:55 | Blueprint Function Libraries |
| 3:18 | Base User Interface |
| 7:50 | HUD Class |
| 13:12 | Create another widget |
| 13:19 | Create a canvas panel |
| 18:12 | Create a widget list |
| 22:37 | Collapse widgets |
| 29:42 | Blueprint Macro Library |
| 30:00 | Macro Library setup |
| 30:53 | Timeout Period |
| 35:00 | Toggle Widgets |
| 37:35 | Remove Widgets |
| 41:45 | Focus Widgets |
| 45:42 | Outro |

## Key Best Practices

### 1. Use the HUD Class as a Central Manager
- The HUD class provides a centralized location for all UI management
- Create a custom HUD Blueprint (based on HUD class)
- Assign it in your Game Mode > HUD Class setting
- The HUD class owns all core widgets and manages their lifecycle

**Why HUD Class?**
- Single source of truth for UI state
- Clean separation between gameplay logic and UI logic
- Easy to reference from Player Controller

### 2. Toggle Visibility Instead of Create/Remove
**The Golden Rule:** Toggle widget visibility ON/OFF instead of creating and removing widgets from their parent.

**Why Toggle?**
- Creating widgets is expensive (allocates memory, runs constructors)
- Removing widgets loses any state/data stored in them
- Toggling visibility is nearly instant and preserves state
- Much better performance for frequently shown/hidden UI (inventory, map, etc.)

**How to Toggle:**
- Set Visibility node: Visible vs Collapsed
- Collapsed: hidden and takes no layout space
- Hidden: hidden but still occupies layout space
- Use Collapsed for most toggle scenarios

### 3. Communication Pattern: Player Controller -> HUD -> Widgets
The recommended communication flow:
```
Player Controller (gameplay events)
    -> HUD Class (UI management)
        -> Individual Widgets (display updates)
```

- Player Controller detects gameplay events (pause, open inventory, etc.)
- Player Controller calls functions on the HUD class
- HUD class toggles widget visibility and passes data
- Widgets update their display based on received data

### 4. Blueprint Function Libraries
- Create a Blueprint Function Library for reusable UI helper functions
- Examples:
  - ShowWidget(Widget)
  - HideWidget(Widget)
  - ToggleWidgetVisibility(Widget)
- These functions are globally accessible from any Blueprint
- Reduces duplicate code across multiple widgets

### 5. Widget List Pattern
- Maintain an array/list of all managed widgets in the HUD class
- Iterate through the list for batch operations:
  - Hide all widgets when pausing
  - Show/hide based on game state
  - Update all widgets on resolution change

### 6. Blueprint Macro Library
- Create a Macro Library for repetitive Blueprint patterns
- Macros can have multiple execution pins (unlike functions)
- Useful for:
  - Common widget creation patterns
  - Error handling with UI feedback
  - Repeated animation sequences
- Access: Right-click > Macro Library in Content Browser

### 7. Focus Management
- When showing a UI widget, set input focus properly
- Use Set Input Mode UI Only for full-screen menus
- Use Set Input Mode Game and UI for overlay menus
- Remember to restore Game Only input mode when closing UI
- Use Set Game Paused if the menu should pause gameplay

### 8. Canvas Panel Organization
- Use Canvas Panel as the root for complex layouts
- Child widgets can be anchored to edges, corners, or center
- Use Size Box to constrain widget dimensions
- Horizontal/Vertical Boxes for organized content layout

## Architecture Pattern

```
BP_MyHUD (HUD Class)
  |
  |-- WBP_MainMenu (Widget Blueprint)
  |-- WBP_InGameHUD (Widget Blueprint)
  |-- WBP_Inventory (Widget Blueprint)
  |-- WBP_PauseMenu (Widget Blueprint)
  |
  |-- Function: ShowMainMenu()
  |-- Function: ShowInventory()
  |-- Function: TogglePauseMenu()
  |-- Function: HideAllWidgets()
  |-- Variable: WidgetArray (all managed widgets)
```

## Performance Tips
- Avoid creating/destroying widgets at runtime; toggle visibility instead
- Use Is Visible checks before updating hidden widgets
- Batch UI updates; don't update every frame if data hasn't changed
- Use Widget Reflector (Window > Developer Tools > Widget Reflector) to debug
- Minimize the number of widgets in the viewport simultaneously

## Resources
- Kekdot Website: https://Kekdot.com
- Patreon (project files): https://www.patreon.com/kekdot
- Game on Steam (The Anomaly Project): https://store.steampowered.com/app/2960770/The_Anomaly_Project/
- Related: Modular Widgets Tutorial by Kekdot: https://www.youtube.com/watch?v=dWx6hIL5Gko
- Related: UI Toggle Tutorial: https://www.youtube.com/watch?v=ZMccVNOlGpI


---

## Related

- ← Previous: [[01_Building_Menus_and_UI]]
- → Next: [[03_Canvas_Panel_Widgets]]
- 📚 Series: [[_MOC_UE5_UI]]
