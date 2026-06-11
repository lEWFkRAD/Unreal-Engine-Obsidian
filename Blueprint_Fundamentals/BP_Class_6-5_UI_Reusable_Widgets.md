---
title: "UE Blueprint Fundamentals | Class #6-5 | UI Reusable Widgets"
source: "https://www.youtube.com/watch?v=Pdt_l77I-so"
video_id: "Pdt_l77I-so"
type: "youtube-summary"
series: "Blueprint Fundamentals"
episode: 6
tags: [ue5, tutorial, blueprint, fundamentals, gamedev, visual-scripting]
---

# UE Blueprint Fundamentals: UI Reusable Widgets

## Overview
- **Channel**: Ask A Dev
- **Focus**: Creating reusable widget blueprints that can be customized per instance
- **Benefits**: Single-source updates, inheritance flexibility, reduced workload

## Creating a Reusable Button Widget

### Setup Process
1. **Create Widget Blueprint**: New User Interface → Widget Blueprint (e.g., `ButtonBase`)
2. **Structure**: Overlay → Button → Text Block
3. **Visual Configuration**: Set button image with material instance, adjust font/size/colors
4. **Text Customization**: Convert text block to variable, set in PreConstruct
5. **Instance Customization**: Create variable marked as `Instance Editable` and `Expose on Spawn`

## Handling Click Events with Dispatchers

### Why Dispatchers?
> "These are instances of a button base... Unreal doesn't know that the whole thing is meant to be a button"

### Implementation Steps
1. **Create Event Dispatcher**: Name `OnClicked`, connect to button's OnClicked event
2. **Using in Parent Widget**: Add OnClicked event to button instances, assign custom functionality

```blueprint
// In button base graph:
Button (ButtonMain) → OnClicked → Call Dispatcher (OnClicked)

// In parent widget:
ButtonBase (ButtonHello) → OnClicked → Print String ("Hello")
```

## Creating a Reusable Inventory Tile

### Widget Structure (`InventoryTile`)
- Vertical Box with:
  - Text Block (Item Name) — Variable: `ItemName`
  - Image (Thumbnail) — Variable: `ItemThumbnail`
  - Text Block (Quantity) — Variable: `ItemQuantity`

### Configuration
- All variables: `Instance Editable` + `Expose on Spawn`
- Use `UniformGridPanel` for inventory layout
- Grid cell size: 128x128 with padding

## Key Implementation Tips

### PreConstruct vs Construct
- **PreConstruct**: Values visible in editor preview
- **Construct**: Values set at runtime only

### Variable Exposure
> "Make sure all these elements are variables and set to instance editable and exposed on spawn"

### Style Updates
- Modify `ButtonBase` once → All instances update automatically
- Changing font, colors, or materials propagates everywhere

## Key Takeaways
1. **Widget Reusability**: Create once, use everywhere
2. **Dispatchers**: Essential for event handling across widget boundaries
3. **PreConstruct**: Use for editor-visible customization
4. **Variable Exposure**: Key for per-instance customization

---

## Related

- ← Previous: [[BP_Class_6-4_UI_Button_Materials]]
- → Next: [[BP_Crash_Classes_Inheritance]]
- 📚 Series: [[_MOC_Blueprint_Fundamentals]]
