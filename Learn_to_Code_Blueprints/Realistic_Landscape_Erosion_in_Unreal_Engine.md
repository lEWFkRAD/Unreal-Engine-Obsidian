---
title: "Realistic Landscape Erosion in Unreal Engine"
source: "https://www.youtube.com/watch?v=ZeTXIZK2xvw"
video_id: "ZeTXIZK2xvw"
type: "youtube-summary"
series: "Learn to Code Blueprints"
episode: 0
tags: [ue5, tutorial, blueprint, gamedev, coding]
---

# Realistic Landscape Erosion in Unreal Engine

## Overview
Tutorial on creating realistic landscape erosion using UE5's built-in erosion tool. Involves sculpting base terrain, applying erosion simulation, and fixing resulting artifacts.

## Key Tutorial Steps

### 1. Erosion Tool Access and Setup
- Navigate to **Landscape Mode** > **Manage** > **Blueprint** tab.
- Select the **Erosion brush**.
- **Critical Step**: Create a **new Landscape Edit Layer** before applying erosion (allows non-destructive editing).

### 2. Erosion Simulation Process
- In the layer properties, locate **"Launch Erosion Timeline"**.
- Load default settings initially.
- Click **"Simulate Erosion"** - watch as particles drive the erosion process.
- The tool creates natural-looking shapes mimicking rain/wind erosion.

### 3. Terrain Sculpting for Better Erosion
- **Improve base terrain** before erosion:
  - Push down certain parts to create interesting shadows.
  - Sculpt peaks and indentations to guide erosion paths.
  - Use **subtractive sculpting** (hold Shift) to create natural features.
- Focus only on **visible areas** to optimize workflow.
- Use **noise tool** with adjustable strength/brush size for rough terrain.
- Smooth harsh transitions between areas.

### 4. Handling Post-Erosion Issues
- **Create a separate layer** for erosion fixes (non-destructive workflow).
- Use **Sculpt tool** with **Flatten** function to restore playable areas.
- **Smooth** transitions to avoid harsh cliffs.
- Use character reference points to determine proper terrain height.
- Test collisions and walkability (e.g., under bridges).

## Critical Considerations
1. **Map Size Matters**: Smaller maps may not show dramatic erosion results.
2. **Layer Management**: Keep erosion on separate layers for easy toggling.
3. **Performance**: Switch to high resolution during complex operations if needed.
4. **Material Alignment**: Ensure materials align with new erosion shapes.
5. **Visible vs. Non-Visible Areas**: Only invest time in areas players will see.

## Final Workflow Summary
1. Sculpt base terrain with interesting features (peaks, valleys).
2. Create dedicated erosion layer.
3. Apply erosion simulation with default settings.
4. Create separate fix layer to restore playable areas.
5. Smooth transitions and test collisions.
6. Use post-processing and nanite displacement for final visual polish.

---

## Related

- ← Previous: [[Prototype_Your_Playing_Area_Using_Cube_Grid_in_Unreal_Engine]]
- → Next: [[Start_Decorating_Your_Level]]
- 📚 Series: [[_MOC_Learn_to_Code_Blueprints]]
