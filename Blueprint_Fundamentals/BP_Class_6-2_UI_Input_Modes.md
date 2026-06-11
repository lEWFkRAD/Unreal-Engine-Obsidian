---
title: "UE Blueprint Fundamentals | Class #6-2 | UI Input Modes"
source: "https://www.youtube.com/watch?v=PjrsXxIZ6Ow"
video_id: "PjrsXxIZ6Ow"
type: "youtube-summary"
series: "Blueprint Fundamentals"
episode: 6
tags: [ue5, tutorial, blueprint, fundamentals, gamedev, visual-scripting]
---

# UE Blueprint Fundamentals: UI Input Modes

## Overview
- **Channel**: Ask A Dev
- **Duration**: 31:02
- **Focus**: Implementing toggleable UI elements with proper input mode management

## 1. Separating UI Widgets
Split combined UI into two separate widgets:
- **Persistent HUD** (e.g., health bar)
- **Toggleable Debug Menu**

## 2. Input Modes Explained

| Mode | Behavior | Use Case |
|------|----------|----------|
| **Game Only** | All input goes to game controls | Standard gameplay |
| **Game and UI** | Input to UI first, then game if not consumed | Overlays, HUDs |
| **UI Only** | All input consumed by UI, game controls disabled | Full-screen menus (use sparingly) |

## 3. Implementing a Robust Toggle

### Show/Hide with Input Modes
**On Widget Creation (Show):**
- `Set Input Mode to Game and UI`
- `Set Show Mouse Cursor` to True

**On Widget Removal (Hide):**
- `Set Input Mode to Game Only`
- `Set Show Mouse Cursor` to False

### Toggle Logic
Instead of Show on Press / Hide on Release:
1. Check if widget is already visible
2. If visible: Remove, reset input mode and cursor
3. If not visible: Create, add to viewport, set input mode and cursor

## 4. Garbage Collection & Widget Reuse

**Problem**: `Remove from Parent` doesn't guarantee widget destruction.

**Solution**: Reuse widget instances:
1. If variable is **not valid**: Create new widget instance
2. If **is valid**: Add existing widget to viewport, set visibility to Visible
3. On hide: Set visibility to Hidden (don't remove)

> "When you remove it from the parent it might not actually get destroyed... we need to be a little bit smarter about this."

## 5. Key Bindings Within Widgets (UI Only Mode)
When using UI Only mode, game keys are blocked. Create key bindings within the widget:

Override **`On Key Down`** event in widget Blueprint:
```blueprint
On Key Down (Key Event)
  -> Branch: If (Key == Q)
     -> True: Close menu → Return Handled
     -> False: Return Unhandled
```

## 6. Pausing the Game
- Use `Set Game Paused` when showing full-screen UI
- When paused, game loop and timers stop — internal key bindings become crucial

## Key Takeaways
1. Separate persistent HUD from toggleable menus
2. Always set Input Mode and Show Mouse Cursor explicitly
3. Prefer `Game and UI` for menus where gameplay continues
4. Reuse widget instances to avoid memory leaks
5. Handle key bindings within widgets for UI Only mode

---

## Related

- ← Previous: [[BP_Class_6-1_UI_Layout]]
- → Next: [[BP_Class_6-3_UI_Buttons_Style_Variables]]
- 📚 Series: [[_MOC_Blueprint_Fundamentals]]
