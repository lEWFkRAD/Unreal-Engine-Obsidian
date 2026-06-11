---
title: "Add Water Easily in Unreal Engine 5"
source: "https://www.youtube.com/watch?v=Eto2J0RE9Tc"
video_id: "Eto2J0RE9Tc"
type: "youtube-summary"
series: "Learn to Code Blueprints"
episode: 0
tags: [ue5, tutorial, blueprint, gamedev, coding]
---

# Add Water Easily in Unreal Engine 5

## Overview
Tutorial on adding water to Unreal Engine 5 levels using two different methods.

## Method 1: Using Built-in Water Plugin (Creates Landscapes)
1. **Enable the Plugin**:
   - Go to `Edit` > `Plugins`.
   - Search for and enable the **Water** plugin.
   - **Restart Unreal Engine** when prompted.
   - On project reload, click **"Add it yes"** to resolve collision profile warning.
   - Note: This is an experimental feature.

2. **Add Water Body**:
   - In Content Browser, search for "water".
   - Drag in different water bodies: **Lake, Ocean, River, Water Zone**, etc.
   - Adding a Lake will automatically modify your landscape to create the water feature.

## Method 2: Using a Plane with Water Material (Faster, More Control)
1. **Create a Water Surface**:
   - Add a basic **Plane** (Shapes > Plane) to your level.

2. **Assign the Water Material**:
   - In Content Browser settings (cog icon), enable **"Show Engine Content"** and **"Show Plugin Content"**.
   - Navigate to: Engine > Plugins > Water Content > Content > Examples.
   - Find and copy the **Water Material Instance** to your project folder.
   - Drag and drop this material onto your plane.

3. **Scale and Position**:
   - Scale the plane to cover your entire map (e.g., scale of 200).
   - Adjust Z-axis position so it sits correctly within your landscape.

## Pro Tips
- **Creating a Lakebed**: Use Landscape Sculpt tool with **Shift + Click** to dig down and create valleys for your water plane.
- **Visual Boundaries**: Use water as a visual cue to block players, combined with Blocking Volumes.
- **Underwater Effects**: The Water Plugin includes automatic camera effects when submerged.

---

## Related

- ← Previous: [[Add_FAB_assets_to_your_Unreal_Engine_project]]
- → Next: [[Add_blocking_volumes_to_prevent_your_players_from_leaving_the_game]]
- 📚 Series: [[_MOC_Learn_to_Code_Blueprints]]
