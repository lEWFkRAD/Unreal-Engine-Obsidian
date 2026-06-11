---
title: "Create Dynamic Cables in UE5 with Blueprint In Cyberpunk Alley"
source: "https://www.youtube.com/watch?v=LT-YX0kisws"
video_id: "LT-YX0kisws"
type: "youtube-summary"
series: "UE5 PCG Tutorial"
episode: 0
tags: [ue5, tutorial, blueprint, physics, gamedev, pcg, procedural]
---

# Create Dynamic Cables in UE5 with Blueprint In Cyberpunk Alley

**Channel:** PolyBoost | **Published:** 2026-03-19 | **Length:** 09:34

## Overview
A tutorial on creating a fully dynamic cable system using Blueprints in Unreal Engine 5 for a cyberpunk/sci-fi alley environment. Covers flexible cables that can be placed anywhere, controlling shape/behavior, and adding physics for dynamic collision reactions.

**Free Asset:** [Cyber Lights from CGTrader](https://www.cgtrader.com/free-3d-models/exterior/other/2-cyber-lights)

## Key Steps

### 1. Creating the Cable Blueprint
- Create a Blueprint and add a **Box** component as the first connection point.
- Add a **Cable Component**. Moving the box changes the cable shape.
- Adjust **Cable Width** parameter to reduce thickness.

### 2. Controlling the Cable
- **End Location**: Adjust the end point.
- **Cable Length**: Increase/decrease length.
- **Cable Segments**: Higher values = smoother cable with better strength and flexibility.

### 3. Connecting Both Ends
- Create a second box at the end of the cable, scale it down.
- Set both **End Location** and **Cable Length** to zero.
- Enter the exact component name (e.g., `Q1`) into both **Component Name** and **Attach End To** fields.
- Use a **Billboard** component instead of a box for invisible handles in renders.

### 4. Adding Collision
- Enable collision in cable settings and reduce friction to the lowest value.
- Note: Cable collision in UE5 is not very accurate.

### 5. Materials & Scene Assembly
- Assign materials to cables.
- Use rectangle lights at different areas for better illumination on cable-connected props.

## Key Takeaways
- A single Blueprint system can create different cables for various props instead of building new meshes each time.
- Billboard components are better than boxes for handle positioning (invisible in renders).
- Cable collision exists but has limited accuracy.

---

## Related

- ← Previous: [[cinematic-post-apocalyptic-street-p2-pcg]]
- → Next: [[pcg-ue-5-6-all-new-features]]
- 📚 Series: [[_MOC_UE5_PCG_Tutorial]]
