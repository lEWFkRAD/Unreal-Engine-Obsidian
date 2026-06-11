---
title: "Unreal Engine Blueprint Fundamentals | Class #1 Workbook"
source: "https://www.youtube.com/watch?v=mx-2oV5tbyk"
video_id: "mx-2oV5tbyk"
type: "youtube-summary"
series: "Blueprint Fundamentals"
episode: 1
tags: [ue5, tutorial, blueprint, fundamentals, gamedev, visual-scripting]
---

# Unreal Engine Blueprint Fundamentals - Class #1 Workbook

## Overview
Hands-on workbook for learning Blueprint fundamentals. Uses a deliberately step-by-step, "arts and crafts" approach to build foundational muscles in visual scripting. This is a **"wax on, wax off"** exercise — the laborious process teaches essential skills that become second nature.

## Part 1: Building a Template House Manually

### Purpose
Create a visual reference ("cheat sheet") of a simple house built from basic static meshes.

### Steps & Key Actions
1. **Create Blueprint**: Right-click → Blueprint Class → Actor → `Blueprint_House_Template`
2. **Viewport Navigation**:
   - Orbit: `Alt` + Left-Click
   - Zoom: `Alt` + Right-Click
   - Pan: `Alt` + Middle-Click
   - Frame Selection: `F`
3. **Transform Tools**: Move (`W`), Rotate (`E`), Scale (`R`)
4. **Build the House**:
   - Foundation: Cube scaled to `(1, 1, 0.1)`
   - Walls: Cubes scaled to `(0.05, 0.676, 0.5)`
   - Roof: Ramps, rotated and positioned
   - **Pro Tip**: Duplicate walls with `Ctrl+C`, `Ctrl+V`

## Part 2: Rebuilding the House with Blueprints

### Steps & Key Actions
1. **Create Blueprint**: Actor → `MyHouse`
2. **Event Graph Setup**: BeginPlay → Print String ("Starting Construction")
3. **Rebuild with Nodes**:
   - Add Static Mesh Component → Set Static Mesh to Cube
   - Set Transform: Use `Set Relative Location`, `Set Relative Rotation`, `Set Relative Scale 3D`
   - **Alternative**: `Set Relative Transform` with **Split Struct Pin**
4. **Organize Code**: Select nodes → Press `C` → Create Comment from Selection

**Key Difference**: Blueprint house is only visible at runtime (press Play).

## Core Concepts & Skills Practiced
- **Static Mesh Components**: Visual building blocks
- **Transforms**: Location, Rotation, Scale
- **Blueprint Workflow**: BeginPlay → Add Component → Set Mesh → Set Transform
- **Code Organization**: Comment Boxes to annotate blueprint graph

## Key Takeaways
1. This is a foundation exercise — the point is learning to connect nodes and set values
2. Always build a manual version first as a "cheat sheet" for exact values
3. Unreal offers multiple methods (separate transform nodes vs. single Set Relative Transform)
4. Use Print String for debugging
5. These skills form the backbone for everything that follows

---

## Related

- → Next: [[BP_Class_2-1_Arrays_and_Maps]]
