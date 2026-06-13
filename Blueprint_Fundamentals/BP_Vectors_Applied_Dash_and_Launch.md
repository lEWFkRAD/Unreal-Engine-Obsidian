---
title: "Vectors Applied: Dash & Launch | Unreal Engine Tutorial"
source: "https://www.youtube.com/watch?v=qc0_NvSXhuA"
video_id: "qc0_NvSXhuA"
type: "youtube-summary"
series: "Blueprint Fundamentals"
episode: 0
tags: [ue5, tutorial, blueprint, fundamentals, gamedev, visual-scripting]
---

# Vectors Applied: Dash & Launch | Unreal Engine Tutorial Summary

## Overview
- **Duration**: 58:38 | **Topics**: Vectors, Blueprint Logic, Character Movement in Unreal Engine 5.4
- **Project**: Third Person Template starting point

## Core Concepts Covered

### 1. Enhanced Input System Setup for Dash
- **Input Action Creation**: Duplicated jump input action → renamed to `IA_Dash`
- **Configuration**: Removed release trigger, set to "Triggered" only
- **Key Binding**: Mapped to `F` key in Input Mapping Context
- **Verification**: Used "Print String" node to confirm input triggers correctly

### 2. Vector Dash Implementation
**Key Insight**: Vectors represent **direction + magnitude** (arrow in 3D space)

```
// Basic dash direction setup
GetActorRotation → GetForwardVector → Launch Character
```

**Problem**: Normalized forward vector has magnitude of 1 → insufficient launch force

**Solution**: Multiply vector by scalar value
```
GetForwardVector × 1000 (float) → Launch Character
```

**Adding Vertical Component**:
- Option 1: Modify vector before multiplication
  ```
  Break Vector → Set Z to 0.1-0.2 → Recombine → Multiply by 1000
  ```
- Option 2: Add vertical after multiplication
  ```
  (GetForwardVector × 1000) + (0, 0, 400) → Launch Character
  ```

**Parameter Control**:
- **Horizontal distance**: Adjust multiplication scalar (1000-2000)
- **Vertical arc**: Adjust Z value (200-400)
- **Result**: Customizable dash feel (fast horizontal vs. jumping arc)

### 3. Launch Pad (Boost Pad) Implementation
**Blueprint Setup**:
1. Create Actor Blueprint (`BP_PadBase`)
2. Add static mesh cube (visual) + collision box
3. Set mesh collision to "No Collision"

**Basic Vertical Launch**:
```
OnComponentBeginOverlap → CastToCharacter → Launch Character(Z: 2000)
```

**Critical Concept: Z Override**
- **Without Override**: Launch velocity added to current velocity (can cancel out)
- **With Override**: Replaces Z velocity component (consistent bounce height)

### 4. Directional Launch Pads
**Forward-Directional Speed Boost**:
```
GetActorForwardVector → Multiply by 2500 → Launch Character
```
- Character launches in pad's facing direction regardless of approach angle

**Player-Directional Speed Boost**:
```
GetCharacterVelocity → Break Vector → Keep XY, Set Z:0 → Multiply by 500
```
- Boosts player in their current facing direction

**Rotation Affects Outcome**:
- Rotating pad 45° changes launch direction 45°
- Demonstrates vector direction property

## Important Technical Details

### Vector Fundamentals Reminder
- Vectors = Direction + Magnitude (strength/length)
- Normalized vectors have magnitude 1
- ForwardVector: X-axis direction in Unreal
- RightVector: Y-axis direction
- UpVector: Z-axis direction

### Launch Character Parameters
- **Velocity**: Direction × Magnitude
- **XY Override**: Replaces horizontal velocity components
- **Z Override**: Replaces vertical velocity component
- **Air Control**: Affects trajectory after launch (0-1 scale)

### Character Movement Considerations
- **Air Control Value**: Default 35 in template
- **Movement Component**: Required for `LaunchCharacter`
- **Physics vs. Animation**:
  - `LaunchCharacter`: Gameplay-driven (collisions considered)
  - Root Motion: Animation-driven (may ignore collisions)

## Q&A Highlights

### Casting Best Practices
```
// Preferred (performance)
Cast to Character (parent class)

// Works but less optimal
Cast to ThirdPersonCharacter (child class)
```
**Reason**: Higher parent classes likely already loaded in memory

### Input Placement
- Third Person Template: Input on **Character Blueprint**
- Top Down Template: Input on **Controller**
- **Pro of Controller**: Survives pawn swapping/destruction

## Useful Hotkeys
1. **Ctrl+Tab**: Switch between last two open blueprints
2. **Q**: Align selected nodes to left/top
3. **Shift+A**: Align nodes to left

## Implementation Tips
1. **Start Simple**: Use `Print String` to verify input triggers
2. **Vector Multiplication Order Matters**: Multiply before adding vertical → controls ratio
3. **Test with Air Control**: Set to 0 for pure launch behavior

---

## Related

← Previous: [[BP_Interface_Demystified]]
→ Next: [[BP_Class_2-1_Arrays_and_Maps]]
- 📚 Series: [[_MOC_Blueprint_Fundamentals]]
