---
title: "Unreal Engine 5 Beginner Tutorial Part 8: Materials & Textures Advanced"
source: "https://www.youtube.com/watch?v=ZHppYUsZLpA"
video_id: "ZHppYUsZLpA"
type: "youtube-summary"
series: "UE5 Starter Course"
episode: 9
tags: [ue5, tutorial, beginner, materials, textures, uv-unwrapping, emissive, normal-maps, jsplacement]
---

# UE5 Beginner Tutorial Part 8: Materials & Textures Advanced

**Instructor:** Bad Decisions Studio

## Overview
Creating realistic, detailed spaceship hangar using advanced material techniques — generating sci-fi textures with external software, emissive/normal maps, and combining multiple normal maps for intricate detail without additional modeling.

## Key Techniques

### 1. Material Application & Fixes
- **Base Material:** `M_Metal_Burnished_Steel` from Starter Content
- **Fix Sharp Normals:** Select mesh → Modeling Tools → Attributes → Normals → Split Normal Method = Face Normal Threshold (~60)

### 2. UV Unwrapping
- **Auto UV:** Use `Create and Edit UVs` in Modeling Tools
- **Method:** X Atlas (clean results)
- Increase Checker Density for visibility
- Adjust Max Iterations (e.g., 10) for optimization

### 3. Tiling Control
- Create Material Instance from parent material
- Connect MF Tiling parameter to Base Color and Normal Map
- Suggested Tiling Value: 50

### 4. Texture Generation with JSplacement
- Free tool for sci-fi texture generation
- Generate textures, export Height Map and Normal Map
- Import into UE5 Content Drawer

### 5. Emissive Maps
- Height Map → Multiply → RGB Node (set color) → Emissive Color
- Control intensity with Emissive Intensity parameter

### 6. Blending Multiple Normal Maps
- **Node:** `Blend Angle Corrected Normals`
- **Intensity Control:** `Flatten Normal` node with scalar parameter
- **Inverse Logic:** `One Minus` node (so 1 = full detail, 0 = flat)
- Blend original metal normal with JSplacement normal, then add panel normals

## Pro Tips
- Post-Process Volume adds bloom/glow to emissive lights (covered later)
- `Alt + drag` to duplicate nodes; `S + left-click` for scalar parameter
- All tiny imperfections and details make scenes much more realistic

## Resources
- **JSplacement:** https://jsplacementweb.pages.dev/
- **Textures.com:** https://www.textures.com/download/PBR0407/137280
- **PureRef:** https://www.pureref.com/

---

## Related

- ← Previous: [[08_Materials_Textures_Basics]]
- → Next: [[10_Scene_Decoration]]
- 📚 Series: [[_MOC_UE5_7_Starter_Course]]
