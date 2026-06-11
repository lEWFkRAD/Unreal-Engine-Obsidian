---
title: "My Unreal Engine level disappeared when I reopened it! What do I do?"
source: "https://www.youtube.com/watch?v=UBBD6hRMrno"
video_id: "UBBD6hRMrno"
type: "youtube-summary"
series: "Learn to Code Blueprints"
episode: 0
tags: [ue5, tutorial, blueprint, gamedev, coding]
---

# My Unreal Engine Level Disappeared When I Reopened It!

## Problem
When using World Partition enabled maps, reopening a level may show nothing loaded - an empty editor with no visible content.

## Solution

### Understanding the Issue
- World Partition requires you to specify which areas you want loaded in the editor.
- When you close and reopen a level, loaded regions may not persist.

### Loading Regions
1. Open **Window > World Partition > World Partition Editor**.
2. The World Partition Editor shows your map with all regions.
3. **Select All**: Use left-click to select all regions.
4. **Load Selected Regions**: Right-click > "Load Region from Selection".
5. The full map will now be visible in the editor.

### Unloading Regions
- Select regions you want to unload.
- Right-click > "Unload Selected Region".
- Note: Unreal may prevent unloading areas with active Nav Mesh Bounds.

### Building the Minimap
- In the World Partition Editor, click **Build > Build World Partition Editor Minimap**.
- This process takes time depending on map size - best done at the end of development.

## Key Takeaways
- World Partition levels require manual region loading in the editor.
- Use the World Partition Editor to manage loaded/unloaded regions.
- Build the minimap at the end of development for navigation reference.
- If your level appears empty, check the World Partition Editor first.

---

## Related

- ← Previous: [[Material_Fundamentals_Working_with_Textures_and_Previewing_Changes]]
- → Next: [[Prototype_Your_Playing_Area_Using_Cube_Grid_in_Unreal_Engine]]
- 📚 Series: [[_MOC_Learn_to_Code_Blueprints]]
