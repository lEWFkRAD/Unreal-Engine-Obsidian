---
title: "Fix tiling issues and add the normal to your Landscape Material"
source: "https://www.youtube.com/watch?v=AuNyfnJhkgM"
video_id: "AuNyfnJhkgM"
type: "youtube-summary"
series: "Learn to Code Blueprints"
episode: 0
tags: [ue5, tutorial, blueprint, gamedev, coding]
---

# Fixing Landscape Material Tiling and Adding Normals in UE5

## Overview
Tutorial addressing two main issues: fixing visible tiling and adding normal maps to create depth in landscape materials.

## Key Steps and Techniques

### 1. Fixing Texture Tiling
**Problem**: Texture repetition is obvious across the landscape.

**Solution**:
- Add a **Texture Coordinate** node
- Multiply it by a scalar parameter to control scale
- Create a **Scalar Parameter** called `global UV tiling` (default: 1)
- Adjust value in material instance (e.g., 0.3 works well for some cases)

Lower values = larger texture scale (less visible tiling).

### 2. Adding Normal Maps
- Connect normal texture to material's **Normal** input
- Normal maps contain lighting direction information:
  - Red channel: Left/Right light response
  - Green channel: Front/Back light response
  - Blue channel: Top/Down light response

### 3. Efficient Material Setup with Material Attributes
- Use **Make Material Attributes** node
- Connect: Base Color, Normal, Ambient Occlusion (AO), and Roughness
- Enable "Use Material Attributes" in material properties
- Connect directly to landscape layer nodes

### 4. Organizing UV Tiling with Named Reroutes
- Create a **Named Reroute** node called `global UV tiling`
- Connect to all texture sample UV inputs
- Ensures consistent scaling across all textures

## Key Takeaways
- Fix tiling by scaling texture coordinates via parameter
- Normal maps add essential depth and lighting detail
- Use material attributes for cleaner node graphs
- Named reroutes maintain organization and consistency
- Always test tiling values from player's perspective

---

## Related

- ← Previous: [[Create_your_first_world_partition_level]]
- → Next: [[Is_your_ground_flat_Try_enabling_tessellation_in_your_landscape_material]]
- 📚 Series: [[_MOC_Learn_to_Code_Blueprints]]
