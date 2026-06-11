---
title: "Start Decorating Your Level"
source: "https://www.youtube.com/watch?v=ddwVGO_2Vrs"
video_id: "ddwVGO_2Vrs"
type: "youtube-summary"
series: "Learn to Code Blueprints"
episode: 0
tags: [ue5, tutorial, blueprint, gamedev, coding]
---

# Start Decorating Your Level

## Overview
Tutorial on replacing prototype cube grid geometry with real assets from FAB asset packs, focusing on collision setup and iterative level decoration.

## Key Concepts

### Asset Replacement Process
- Browse available assets from your imported asset packs (e.g., ruins, arcs, rocks).
- Drag and drop assets to replace cube grid prototype geometry.
- Use `Alt` + drag to duplicate assets for creating matching pairs.
- Not everything will fit perfectly - iteration and adjustment is expected.

### Collision Setup
- Open static mesh assets to check collision: Right-click > Open Asset, or `Ctrl + E`.
- **Simple Collision**: Simplified collision meshes (preferred for gameplay).
- **Complex Collision**: Per-polygon collision (too expensive for shipped games).
- Check if assets already come with simplified collision - many FAB assets do.
- If no collision exists, add it manually:
  - Use **Collision** menu to add box collisions.
  - Can add multiple boxes to fit the mesh shape.
  - **Auto Convex Collision**: Automatically generates simplified collision.

### Iteration Approach
- Replace cube grid pieces one by one with real assets.
- Bookmark important locations for special attention.
- The process takes time - expect hours of work for a basic decorated level.
- Use landscape flattening for floor areas instead of mesh replacements.

### Key Workflow Tips
- Set cube grid tool to negative values (e.g., -1000) to hide it while decorating.
- Use landscape's **Flatten** tool for floor areas.
- Create bookmarks (`Ctrl + Number`) for areas needing special attention.
- Always verify collision on imported assets before committing to them.

## Design Philosophy
- This is just the start - levels always evolve through iteration.
- Focus on having something playable rather than perfection.
- Consider using multiple variations of rocks and props for visual variety.

---

## Related

- ← Previous: [[Realistic_Landscape_Erosion_in_Unreal_Engine]]
- → Next: [[Stop_your_game_from_looking_like_other_Unreal_Engine_games]]
- 📚 Series: [[_MOC_Learn_to_Code_Blueprints]]
