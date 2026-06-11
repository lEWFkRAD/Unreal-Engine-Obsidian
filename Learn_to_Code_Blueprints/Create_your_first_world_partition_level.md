---
title: "Create your first world partition level"
source: "https://www.youtube.com/watch?v=5oLVeACxSXs"
video_id: "5oLVeACxSXs"
type: "youtube-summary"
series: "Learn to Code Blueprints"
episode: 0
tags: [ue5, tutorial, blueprint, gamedev, coding]
---

# Create Your First World Partition Level

## Core Tutorial Steps

### 1. Creating a New Level
- Navigate to **File > New Level**.
- Options: Open World, Empty Open World, Basic, Empty Basic Level.
- **Key Distinction**: "Open World" options enable World Partition; "Basic" options do not.

### 2. World Partition vs. Basic Levels
- **Basic Level**: Everything loads at once. Suitable for small, contained spaces.
- **World Partition**: Loads only specific parts of the map as needed. For large open worlds.

### 3. Collaborative Workflow: One File Per Actor
- Each actor creates a separate asset linked to the main UMAP file.
- Multiple team members can work on the same map simultaneously without conflicts.

### 4. Saving and Identifying the Level
- Save immediately (**File > Save Current Level**).
- World Partition levels show **World Data** and **World Partition Minimap** in Outliner.

### 5. Adding Basic Lighting
- Use **Environment Light Mixer** (Window > Environment Light Mixer).
- Components: Skylight, Directional Light, Sky Atmosphere, Volumetric Clouds, Height Fog.

### 6. Important Note on Default Lighting
- Default UE lighting is recognizable and makes projects look generic.
- Tweak lighting to add unique visual identity.

---

## Related

- ← Previous: [[Create_a_Simple_Landscape_Material_in_Unreal_Engine]]
- → Next: [[Fix_tiling_issues_and_add_the_normal_to_your_Landscape_Material]]
- 📚 Series: [[_MOC_Learn_to_Code_Blueprints]]
