---
title: "Animation Blueprint: Jump Turn in Place"
source: "https://www.youtube.com/watch?v=9wksRrMJXtQ"
video_id: "9wksRrMJXtQ"
type: "youtube-summary"
series: "UE5 Animation"
episode: 3
tags: [ue5, animation, jump, turn-in-place, animation-blueprint, root-motion]
---

# Animation Blueprint: Jump Turn in Place

**Duration:** 1:34:51 | **Source:** YouTube

## Overview

This advanced tutorial takes a different approach to "Turn in Place" — instead of the traditional pivot turn while standing, it implements a **Jump Turn** where the character performs a small hop to reorient. This simplifies animation assets and creation while still solving the common problem of character rotation during idle aiming.

## What is "Turn in Place"?

"Turn in Place" solves a common issue: when the player rotates the camera while standing still, the character's feet should adjust to face the new direction. Without this, the character's feet slide or stay locked while the upper body rotates unnaturally.

### Traditional Approach vs Jump Turn

| Traditional Turn in Place | Jump Turn |
|--------------------------|-----------|
| Pivot animation while standing | Small hop to reorient |
| Requires many rotation-angle animations | Fewer animation assets needed |
| Complex blend logic | Simpler state machine |
| Smooth but asset-heavy | Snappy and stylized |

## Implementation Architecture

### Core Concept

When the character is idle and the accumulated rotation offset exceeds a threshold:
1. Trigger a jump turn animation
2. Physically rotate the character to match the camera
3. Return to idle

### State Machine Addition

```
Locomotion State Machine:
  ├── Idle State
  │     Transition to Turn: RotationOffset > Threshold AND !IsInAir
  │     Transition to Walk: Speed > 10
  │     Transition to Jump: IsInAir
  │
  ├── Turn in Place State → Jump Turn Animation
  │     Transition to Idle: TurnComplete == true
  │
  ├── Locomotion State → Blend Space
  │     ...
  │
  └── Jump State → Jump animations
        ...
```

## Step-by-Step Implementation

### Step 1: Track Camera/Controller Rotation

In the AnimBP Event Graph:

```blueprint
Event Blueprint Update Animation:
  → Try Get Pawn Owner
  → Get Control Rotation (camera rotation)
  → Get Actor Rotation (character rotation)
  → Calculate delta: ControlRotation.Yaw - ActorRotation.Yaw
  → Normalize to -180 to 180
  → SET RotationOffset (Float variable)
```

### Step 2: Accumulate Rotation Offset

Track how far the character's facing has drifted from the camera:

```blueprint
// In Event Graph, each frame:
DeltaRotation = NormalizeDeltaRotation(ControlRotation.Yaw - ActorRotation.Yaw)
AccumulatedRotation += DeltaRotation

// Clamp to prevent extreme values
AccumulatedRotation = FMath::Clamp(AccumulatedRotation, -180.0, 180.0)

SET RotationOffset = AccumulatedRotation
SET ShouldTurn = (FMath::Abs(RotationOffset) > TurnThreshold) // e.g., 45 degrees
```

### Step 3: Create Jump Turn Animation

1. Use an existing jump animation or create one where the character:
   - Leaves the ground briefly
   - Rotates during the airborne phase
   - Lands facing the new direction
2. In the animation, add **Root Motion** rotation (or handle it in code)
3. Mark the animation as **Root Motion Enabled** if using root motion

### Step 4: Build the Turn State

In the State Machine, create the "Turn in Place" state:

**Animation setup inside the state:**
```
Jump Turn Animation Sequence Player
  → Root Motion: Enabled (if using root motion)
  → Loop: Disabled (play once)
```

**Transition Rule (Idle → Turn):**
```
ShouldTurn == true AND IsInAir == false
```

**Transition Rule (Turn → Idle):**
```
Animation Complete (automatic rule) OR IsInAir == true
```

### Step 5: Rotate Character During Turn

**Option A: Root Motion**
- Let the animation drive the rotation
- Enable Root Motion on the AnimBP: Class Settings → Root Motion Mode: "Root Motion from Everything"
- The jump animation's rotation curve handles the turn

**Option B: Manual Rotation (Blueprint)**
```cpp
// In Character Blueprint, triggered by Anim Notify
void AMyCharacter::PerformJumpTurn()
{
    FRotator TargetRotation = GetControlRotation();
    TargetRotation.Pitch = 0;
    TargetRotation.Roll = 0;
    
    // Smoothly interpolate to target
    FRotator CurrentRotation = GetActorRotation();
    FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, 
                                             GetWorld()->GetDeltaSeconds(), 10.0f);
    SetActorRotation(NewRotation);
}
```

**Option C: Anim Notify State**
1. Add a Notify State to the jump turn animation ("RotateToCamera")
2. In the AnimBP, detect this notify
3. While active, rotate the character toward the camera direction each frame

### Step 6: Reset Accumulated Rotation

After the turn completes:
```blueprint
// On transition out of Turn state
AccumulatedRotation = 0.0
ShouldTurn = false
```

### Step 7: Handle Different Turn Directions

For smoother results, create two variants:
- **Turn Left** — when RotationOffset is negative
- **Turn Right** — when RotationOffset is positive

```blueprint
// In Turn state, select animation:
TurnDirection = (RotationOffset > 0) ? "TurnRight" : "TurnLeft"
→ Use Select node to pick the correct animation
```

## Advanced: Blending with Upper Body

If your character has upper body actions (aiming, holding weapon):

```
AnimGraph Flow:
  [Locomotion State Machine (lower body)]
       ↓
  [Layered Blend per Bone]
    - Base Pose: Locomotion (including turn)
    - Blend 0: Upper body aim offset (starts at Spine_01)
       ↓
  [Output Pose]
```

This allows the character to:
- Turn feet via jump turn
- Keep upper body aiming at a target
- Blend naturally between the two

## Animation Asset Requirements

For the jump turn to work well:

1. **Jump animation** with clear airborne phase
2. **Root Motion rotation** (preferred) OR manual rotation logic
3. **Matching landing pose** — the landing frame should match the idle pose
4. **Quick duration** — 0.5 to 1.0 seconds total (not too long)
5. **Subtle vertical movement** — small hop, not a full jump

## Optimization Tips

1. **Threshold tuning** — 45° is a good default; too low causes constant turning
2. **Cooldown** — add a small delay after a turn before allowing another
3. **Interrupt handling** — allow walk/run to interrupt a turn if the player starts moving
4. **Animation compression** — keep turn animations small and fast
5. **Preview with different camera speeds** — test with slow and fast mouse movement

## Comparison with Traditional Turn in Place

| Aspect | Jump Turn | Traditional Pivot |
|--------|-----------|-------------------|
| Asset count | 1-2 animations | 4-8+ (per angle) |
| Visual style | Stylized/arcade | Realistic |
| Implementation | Simpler | More complex blending |
| Best for | Action games, stylized | Realistic, military sims |
| Root Motion | Optional | Usually required |

## Related Resources

- [Turn in Place with Root Motion](https://www.youtube.com/watch?v=Ddy4Dsu_mHE)
- [Animation Blueprint Basics](https://www.youtube.com/watch?v=WUXvq6At6pE)
- [UE5 Animation Documentation](https://dev.epicgames.com/documentation/unreal-engine/animation-in-unreal-engine)


---

## Related

- ← Previous: [[02_Animation_Blueprint_State_Machine]]
- 📚 Series: [[_MOC_UE5_Animation]]
