---
title: "Making your level playable using the Game Mode"
source: "https://www.youtube.com/watch?v=JSd_vcILesU"
video_id: "JSd_vcILesU"
type: "youtube-summary"
series: "Learn to Code Blueprints"
episode: 0
tags: [ue5, tutorial, blueprint, gamedev, coding]
---

# Making Your Level Playable Using Game Mode

## Core Objective
Transform a level prototype into a **playable game level** for testing gameplay before decorating it.

## Key Concepts and Actionable Steps

### 1. Level Design Philosophy
- **Test playability first**: Ensure the level's flow and combat zones work before adding visual details.
- Consider tactical design: sniping spots, cover, attack angles.

### 2. Setting Up Player Spawns
- Place `Player Start` actors in your level.
- **Critical Rule**: Every spawn point **must have nearby cover** to prevent players from dying immediately upon spawning.
- Distribute spawns in different areas, rotating each to face logical gameplay directions.

### 3. Understanding and Applying Game Mode
- **Game Mode**: A Blueprint class that defines the core rules of your game.
- **Key Default Classes**:
  - **Default Pawn Class**: The character you control.
  - **Player Controller**: Handles player input and possesses a Pawn.
- In your level's **World Settings**, set the **Game Mode** override to your project's custom game mode.

### 4. Possession and Player Control
- **Possession**: The act of a Player Controller taking control of a Pawn.
- Press `Shift+F1` to release the mouse and "unpossess" the character in the editor.

### 5. Placing Gameplay Elements
#### Weapons (Pickups)
- Found in Blueprints folder under `Pickups`.
- Each pickup has a property to set the **Weapon Type** (Pistol, Rifle, Grenade Launcher).
- Place basic weapons near spawn points and powerful weapons in riskier locations.

#### Enemies (AI)
- Found in Blueprints folder under `AI`.
- Place enemies near but **not directly on** spawn points.

### 6. Enabling AI Movement (Nav Mesh)
- Create a **Navigation Mesh** that defines walkable areas.
- Go to **Place Actors > Volumes** > drag a `Nav Mesh Bounds Volume` into your level.
- Scale the volume to cover the entire playable area.
- Press `P` to toggle Nav Mesh visualization (green areas = where AI can walk).

### 7. Final Gameplay Test
- Test correct character spawns with cover, weapon pickup functionality, and AI enemies moving correctly across the Nav Mesh.

## Key Insight
The entire process is about **functionality testing**. This phase validates your level's design for gameplay flow and combat before investing time in aesthetics.

---

## Related

- ← Previous: [[Making_our_landscapes_more_interesting]]
- → Next: [[Material_Fundamentals_Material_Instances]]
- 📚 Series: [[_MOC_Learn_to_Code_Blueprints]]
