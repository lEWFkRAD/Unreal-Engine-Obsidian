---
title: "Add blocking volumes to prevent your players from leaving the game"
source: "https://www.youtube.com/watch?v=5SV2zjyuSHc"
video_id: "5SV2zjyuSHc"
type: "youtube-summary"
series: "Learn to Code Blueprints"
episode: 0
tags: [ue5, tutorial, blueprint, gamedev, coding]
---

# Add Blocking Volumes to Prevent Players from Leaving the Game

## Overview
Tutorial on adding blocking volumes to prevent players from leaving the intended play area, particularly around water planes.

## Key Concepts

### The Problem
- Players can walk through water planes since they're just geometry.
- Need invisible barriers to keep players in the playable area.

### Solution: Blocking Volumes
- Add **Blocking Volumes** from Place Actors > Volumes.
- Scale and position them to cover areas where players shouldn't go.
- Rotate volumes to match the terrain and prevent entry from multiple angles.

### Removing Unnecessary Collision
- For objects players don't need to collide with (like water planes), remove collision.
- This saves performance for more important collision tasks.
- Select the object, find collision settings, and disable.

### Collision Visualization
- Use the **Collision Visualizer** to check where collisions exist.
- Switch from "Lit" view to "Player Collision" view.
- Green areas show collision - gaps indicate where players can pass through.
- Use this to find missing blocking volumes.

### Workflow
1. Play the game and identify areas where players can escape.
2. Add blocking volumes to those areas.
3. Scale and rotate to fit the terrain.
4. Use collision visualizer to verify coverage.
5. Test again to ensure no gaps remain.

## Key Takeaways
- Always add blocking volumes around water and map edges.
- Remove collision from objects that don't need it for performance.
- Use collision visualizer to find gaps in coverage.
- Test by playing the game and trying to escape the play area.

---

## Related

- ← Previous: [[Add_Water_Easily]]
- → Next: [[Add_foliage_to_your_level_in_Unreal_Engine]]
- 📚 Series: [[_MOC_Learn_to_Code_Blueprints]]
