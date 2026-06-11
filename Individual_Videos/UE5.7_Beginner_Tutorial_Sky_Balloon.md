---
title: "Unreal Engine 5.7 Is Out Now! – Beginner Tutorial Create A Game - Full Course 2025"
source: "https://www.youtube.com/watch?v=zN8iQmXOSr0"
video_id: "zN8iQmXOSr0"
type: "youtube-summary"
series: "Individual Videos"
episode: 0
tags: [ue5, tutorial, beginner, blueprint, enhanced-input, ai, save-system, niagara]
---

# Unreal Engine 5.7 Beginner Tutorial: Sky Balloon Freakout

**URL:** https://www.youtube.com/watch?v=zN8iQmXOSr0  
**Channel:** Unreal University  
**Length:** 1:11:33  
**Assets:** https://www.unreal-university.io/blog/unreal-engine-5-7-tutorial-game-assets

---

## Course Overview
Top-down balloon dodging jets and bullets in a sky environment. Full beginner course covering project setup through polish.

---

## Project Setup & Core Architecture

### Key Steps
1. **Project Creation**: Blank template named "Sky Balloon"
2. **Folder Structure**: `Levels/`, `Assets/`, `Blueprints/`, `Input/`, `Widgets/`, `Materials/`, `Niagara/`, `Sounds/`
3. **Level Setup**: Basic sky atmosphere + floor mesh saved as `SkyBalloonLevel`
4. **Game Mode**: `BP_SkyBalloonGameMode` with default pawn set to `BP_Balloon`

### Camera Setup (Top-Down View)
```blueprint
// Level Blueprint
Event BeginPlay → Set View Target with Blend (Target: CameraActor)
```
- Rotate 90° downward
- Uncheck *Constrain Aspect Ratio*

---

## Character & Input System

### Balloon Character (`BP_Balloon`)
- **Components**: Static Mesh (scale: 2.0), Capsule (radius: 45, height: 79)
- **Optimization**: Disable *Cast Shadow* to fix visual artifacts
- **Movement Setup**:
  ```blueprint
  // Enhanced Input Setup
  IA_Move (Axis 2D) + IMC_Balloon
  Arrow Keys:
  - Up/Down: Swizzle + Negate modifiers
  - Left/Right: Negate modifiers
  
  Event Graph:
  X → Add Movement Input (Control Rotation → Right Vector)
  Y → Add Movement Input (Control Rotation → Forward Vector)
  ```

### Rotation Animation
```blueprint
Event Tick:
Current Rotation → FInterpTo (Target: 90°, Speed: 100) → Set World Rotation (Z-axis)
```
- Boundary Behavior: Target rotation clamped to [60°, 120°]
- Reset: `IA_Move.Completed` → Reset target to 90°

---

## Game Mechanics

### Scoring System
1. **Player HUD Widget**: `Widget_Blueprint_PlayerHUD` with text anchored top-center
2. **Logic**:
   ```blueprint
   BP_Balloon BeginPlay:
   Create Player HUD Widget → Add to Viewport
   Set Timer (1s, looping) → Increment Score → Update Widget
   ```

### Enemy Jet (`BP_Jet`)
```blueprint
BeginPlay:
Set Timer (0.5s) → AI Move To (Get Player Character)
On Hit: Cast to BP_Balloon → Call Death()
```
- Movement Speed: 400 (Character Movement)
- `Orient Rotation to Movement: Enabled` (Rotation Rate: 360)
- Nav Mesh Volume required for pathfinding

### Bullet System
1. **Bullet (`BP_Bullet`)**:
   - Projectile Movement (Gravity: 0, Speed: 250-1300 random)
   - Sphere Collision → On Overlap: Cast to BP_Balloon → Death()
2. **Spawner (`BP_BulletSpawner`)**:
   ```blueprint
   BeginPlay:
   Set Timer (0.3-1s random) → Sequence:
   1. Spawn Bullet (Random Y: [-1000, 1000], Random Z Rotation: [-30°, 30°])
   2. 50% Chance: Spawn second bullet
   ```
   - Auto-despawn after 15 seconds

---

## World & UI Systems

### Sky Environment
- **Clouds**: UI Material (`M_Cloud`) using cloud noise texture + panner (speed: 0.5)
- **Opacity**: `Texture Sample (Red Channel) → Clamp (Max: 0.5)`

### Save System & Game Over
1. **Save Game**: `BP_Save` with `HighScore` integer
2. **Flow**:
   ```blueprint
   Death():
   - Stop Score Timer
   - Hide Player HUD
   - Check/Create Save: "score" slot
   - Update High Score if current > saved
   - Create End Score Widget
   ```
3. **End Score Widget**:
   - Current Score: "You lasted [X] seconds"
   - High Score: "Your record: [Y] seconds"
   - Retry Button: Open "SkyBalloonLevel"

### Polish & Effects
- **Particles**: Niagara "BalloonPop" system (yellow, from point)
- **Sound**: Background wind (looping), pop on death, randomized bullet SFX
- **Input Handling**:
  ```blueprint
  Death: Set Show Mouse Cursor (true) → Set Input Mode UI Only
  BeginPlay: Set Show Mouse Cursor (false) → Set Input Mode Game Only
  ```

---

## Key Timestamps
| Timestamp | Topic |
|-----------|-------|
| 0:00 | Project Setup |
| 2:41 | Character Blueprint |
| 17:09 | Rotation Animations |
| 30:36 | Enemy AI |
| 44:56 | Cloud Materials |
| 1:03:21 | Polish Effects |

---

## Related

- ← Previous: [[Make_Your_Character_Feel_AAA]]
