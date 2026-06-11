---
title: "UE Blueprint Fundamentals | Class #6-3 | UI Buttons, Style, & Variables"
source: "https://www.youtube.com/watch?v=aFHI-rsAt4Y"
video_id: "aFHI-rsAt4Y"
type: "youtube-summary"
series: "Blueprint Fundamentals"
episode: 6
tags: [ue5, tutorial, blueprint, fundamentals, gamedev, visual-scripting]
---

# UE Blueprint Fundamentals: UI Buttons, Style, & Variables

## Overview
- **Channel**: Ask A Dev
- **Focus**: Making UI interactive with buttons, styling them, and using UI elements as variables

## Button Basics & Styling

### Creating a Button
- Drag a **Button** widget from the Palette into your UI widget

### Styling Options (Details Panel)
- **Tint**: Changes button's base color
- **Outline Settings**: Color, Width, Corner Radius
- **Hovered/Pressed/Disabled Styles**: Each state has its own Color and Outline settings
- **Tip**: Use `Ctrl+D` to duplicate widgets for quick style testing

## Adding Text to Buttons
- A Button has no built-in text property
- **Method**: Drag a **Text** widget directly onto the Button — it becomes parented to the button
- Style the Text widget: Font, Size, Color

## UI Elements as Variables
**Critical for making UI interactive.**
- Select widget → check **"Is Variable"** box in Details Panel
- Allows you to reference the widget in code to change properties and respond to events

## Making Buttons Functional (OnClicked Events)
1. Select the Button variable in Designer
2. Details Panel → Events section → click **+** next to **OnClicked**
3. Connect logic (e.g., `Print String`)

```blueprint
[OnClicked (ButtonA)] -> [Print String: "Hello"]
```

## Updating UI Dynamically
1. Make the **Text widget** a variable
2. In Button's OnClicked event, drag off Text variable
3. Use **"Set Text (Text)"** function with new text string

```blueprint
[OnClicked (ButtonA)] -> [Set Text (TextStatus): "Hello"]
```

### Changing Style Dynamically
```blueprint
[OnClicked (ButtonA)] -> [Set Color and Opacity (TextStatus): (R=0, G=1, B=0, A=1)]
```

## UI Interacting with Gameplay
UI buttons can trigger character actions (e.g., jumping):
```blueprint
[OnClicked (ButtonC)] -> [Get Player Controller] -> [Get Controlled Pawn] ->
  [Cast To ThirdPersonCharacter] -> [Jump]
```

## Using Images as Buttons & Fixing Stretching
- Change **Draw As** setting to **Box** (preserves corners and borders)
- Set **Margin** values to define stretch regions
- Recommended formats: PNG, TGA with alpha

## Key Takeaways
- "Is Variable" checkbox is essential for interactive UI
- OnClicked events connect buttons to logic
- UI can trigger gameplay through Get Player Controller → Cast → Call function
- Use Box drawing mode for custom button images

---

## Related

- ← Previous: [[BP_Class_6-2_UI_Input_Modes]]
- → Next: [[BP_Class_6-4_UI_Button_Materials]]
- 📚 Series: [[_MOC_Blueprint_Fundamentals]]
