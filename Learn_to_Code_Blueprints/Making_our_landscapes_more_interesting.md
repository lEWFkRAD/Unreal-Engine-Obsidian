---
title: "Making our landscapes more interesting"
source: "https://www.youtube.com/watch?v=4DZFX-YGBg4"
video_id: "4DZFX-YGBg4"
type: "youtube-summary"
series: "Learn to Code Blueprints"
episode: 0
tags: [ue5, tutorial, blueprint, gamedev, coding]
---

# Making Our Landscapes More Interesting

## Overview
Tutorial on enhancing a landscape by strategically placing and rotating a small number of rock meshes to create natural variety and avoid repetitive patterns.

## Key Techniques

### 1. Asset Selection and Placement
- **Source Assets**: Used rocks from **Paragon Props ("monolith rocks")** and the **Kite Demo**.
- **Closed Mesh Principle**: Choose rocks that are "closed meshes" (full 3D models). This allows rotation to reveal entirely different shapes.
  > "This rock works almost like having eight rocks because if I put it like this... If I just rotate it is a completely different rock."
- **Scale and Proportion**: Use the approximate size viewer to gauge suitability. Scale rocks up to fit the scene.

### 2. Creating Variety from a Single Asset
- **Core Strategy**: Duplicate, rotate, and scale a single high-quality rock mesh.
  > "A new rock. A new rock. And the change shapes... The change in this shape is what is selling this type of thing."
- **Avoiding Patterns**: Brains easily detect repeated patterns. Using rotation breaks this illusion.
  > "If we only have one face... and then I'll just copy and paste it and immediately, oh, there is a pattern here because our brain is designed to pick up on that."

### 3. Post-Processing for Cohesion
- **Problem**: Rocks placed in the distance can clash with the scene's colors.
- **Solutions**:
  - Adjust **exponential fog** density to obscure distant details.
  - Modify materials or the **post-process** volume to alter color perception.
  - Ensure settings are applied to the correct effect (e.g., "Extension Scale" parameter).

### 4. Workflow and Final Steps
- **Focus on Key Shots**: Only enhance areas visible from intended camera angles.
- **Social Media Ready**: Take before-and-after screenshots to showcase improvements.
  > "Don't forget to take your screenshot. Very important step. Also, that's how you can start posting on your socials."

## Key Quote
> "We can start just messing around and covering a bit of my landscape... I just added a bunch of rocks, rotated them... this is the same rock in all... you won't be able to notice that."

## Tools and Assets Used
- **Engine**: Unreal Engine 5
- **Assets**: Paragon Props, Kite Demo Rock Meshes
- **Techniques**: Mesh rotation/scaling, exponential fog, post-process adjustments

---

## Related

- ← Previous: [[Is_your_ground_flat_Try_enabling_tessellation_in_your_landscape_material]]
- → Next: [[Making_your_level_playable_using_the_Game_Mode]]
- 📚 Series: [[_MOC_Learn_to_Code_Blueprints]]
