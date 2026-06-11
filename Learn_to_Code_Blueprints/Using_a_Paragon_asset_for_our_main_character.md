---
title: "Using a Paragon asset for our main character"
source: "https://www.youtube.com/watch?v=bBuHB2-UBgg"
video_id: "bBuHB2-UBgg"
type: "youtube-summary"
series: "Learn to Code Blueprints"
episode: 0
tags: [ue5, tutorial, blueprint, gamedev, coding]
---

# Using a Paragon Asset as a Main Character in Unreal Engine 5

## Objective
Replace the default mannequin with the "Lieutenant Bellica" Paragon asset as the playable character.

## Key Requirements
- **Source**: The Paragon character "Lieutenant Bellica" (Epic Games publisher).
- **Core Problem**: The Paragon skeletal mesh has a **different bone hierarchy** than the default UE5 mannequin, requiring animation retargeting.
- **Critical Workflow Tools**: `IK Retargeter`, `Animation Blueprint`.

## Step-by-Step Process

### 1. Asset Acquisition and Setup
- Download "Lieutenant Bellica" from the **Fab** marketplace (filter for free characters by Epic Games).
- Locate the skeletal mesh: `Content/Paragon.Bellica/Heroes/Bellica/Meshes`.

### 2. Retargeting Animations
- The goal is to make the default mannequin animations work on the Bellica skeleton without manually re-exporting all animations.
- **Create IK Rigs and Retargeter**:
  1. Right-click on the mannequin's `Animation Blueprint`.
  2. Select **`Retarget Animations`**.
  3. Set the target skeletal mesh to `Bellica`.
  4. Click **`Export Retarget`** (instead of exporting animations).
  5. This auto-generates an **`IK Retargeter`** asset along with two IK Rig assets.

### 3. Create a Retarget Animation Blueprint
1. Create a new `Animation Blueprint` and select the **Bellica skeleton**.
2. Add the **`Retarget Pose From Mesh`** node.
3. Set the `Parent Skeletal Mesh Component` to the main character mesh.
4. Assign the auto-generated **IK Retargeter** asset to the `IK Retargeter Asset` pin.

### 4. Integrating into the Character Blueprint
- In the main character Blueprint (`ShooterCharacter`), add new Skeletal Mesh Components for both first-person and third-person views.
- For each new mesh:
  - Set the **Skeletal Mesh** asset to `Bellica`.
  - Set the **Animation Class** to your new Retarget Animation Blueprint.
- **Visibility Management**: Set original mannequin meshes to `Set Visibility: False` and `Hidden in Game: True`.

### 5. Adjustments and Fixes
- **Weapon Attachment**: Find the correct socket name for the new skeleton (e.g., `Hand_L`). Update the **`Attach Weapon Meshes`** function.
- **Hiding the Original Weapon Model**: In the original character's Animation Blueprint, add a **`Transform (Modify) Bone`** node targeting weapon bones, set Scale to `(0, 0, 0)` with `Replace Existing` mode.

## Key Insights
- The animation blueprint determines which animation plays depending on actions during gameplay.
- This is a "quick way to start" - creating a custom animation blueprint from scratch yields better results but is more time-intensive.
- First-person hands and weapon may not align perfectly with the new model - manual scaling adjustments may be needed.

## Resources
- **Course Link**: [Learn to create a game in Unreal Engine 5](https://www.unfgames.com/action-game)
- **Community**: [UNF Games Discord](https://discord.gg/zdcBWgqGKT)

---

## Related

- ← Previous: [[Stop_your_game_from_looking_like_other_Unreal_Engine_games]]
- → Next: [[package_your_Unreal_Engine_5.7_project_and_share_it_with_everyone]]
- 📚 Series: [[_MOC_Learn_to_Code_Blueprints]]
