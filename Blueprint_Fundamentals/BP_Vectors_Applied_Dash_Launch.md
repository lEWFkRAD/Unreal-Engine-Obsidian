---
title: "Vectors Applied: Dash & Launch | Unreal Engine Tutorial"
source: "https://www.youtube.com/watch?v=qc0_NvSXhuA"
video_id: "qc0_NvSXhuA"
type: "youtube-summary"
series: "Blueprint Fundamentals"
episode: 0
tags: [ue5, tutorial, blueprint, fundamentals, gamedev, visual-scripting]
---

# Vectors Applied: Dash & Launch | Unreal Engine Tutorial

## Overview
- **Channel**: Ask A Dev
- **Duration**: 58:38
- **UE Version**: 5.4 (Preview)
- **Focus**: Practical vector applications — implementing dash ability and launch/speed boost pads

## Key Concept: Vectors
> A vector is literally a **direction** and a **magnitude** (strength/length). Think of it as an arrow in 3D space.

- A normalized vector has length of exactly **1** — it's pure direction
- To increase reach: multiply the vector by a scalar value

## Part 1: Implementing Dash

### Step 1: Enhanced Input Setup
1. Duplicate jump input action → rename to `IA_Dash`
2. Set trigger to **Pressed only**
3. Bind to **F key** in input mapping context

### Step 2: Get Dash Direction
**Preferred**: `Get Actor Forward Vector` (simpler than Get Actor Rotation → Get Rotation X Vector)

### Step 3: Launch Character with Proper Magnitude
Forward vector is normalized (length=1), so plugging directly into `Launch Character` produces almost no movement.

**Solution**: Multiply by scalar:
```
Forward Vector × 1000 → Velocity vector for Launch Character
```

### Step 4: Adding Verticality
**Recommended approach** — Add vertical after multiplication:
```blueprint
Get Actor Forward Vector → Multiply × 1000 → Add (Z: 200) → Launch Character
```
- Changing forward distance: increase scalar (e.g., 1500 → 2000)
- Changing vertical height: adjust added Z value (e.g., 200 → 400)

### Alternatives
- **Gameplay Ability System (GAS)**: `Apply Constant Force` or `Apply Root Motion Constant Force`
- **Root Motion Animation**: Animate dash; distance determined by animation

## Part 2: Launch Pad / Jump Pad

### Creating the Pad Blueprint
1. Create Actor Blueprint → `BP_PadBase`
2. Add **Cube** (visual) + **Collision Cube** (slightly larger) for overlap detection
3. Set visual cube: No Collision, no overlap events

### Basic Vertical Launch
```blueprint
On Component Begin Overlap → Cast To Character → Launch Character (Z: 2000)
```

**Why cast to Character (not Third Person Character)?**
> "When you do a cast, Unreal has to load that class if not already loaded. Character is always loaded. Casting to the highest applicable class avoids unnecessary loading costs."

### Understanding Z Override
**Problem**: Launching up with 2000, but character coming down at -1000 → result only +1000

**Solution**: Enable **Z Override** — replaces Z component instead of adding to it

### Understanding XY Override
- **Without**: Speed boost adds to current movement direction
- **With**: Replaces current direction entirely

### Incorporating Character Momentum
```blueprint
Get Velocity → Break Vector → Use X, Y values → Add custom Z → Launch Character
```

### Air Control
Character Movement Component has **Air Control** setting that affects how much the player can steer while airborne after a launch.

## Key Takeaways
1. Vectors = direction + magnitude; normalized vectors are pure direction
2. Always multiply normalized vectors by scalar before using for movement
3. Z Override ensures consistent launches regardless of incoming velocity
4. Cast to the highest applicable class to minimize memory loading
5. Use separate controls for horizontal distance and vertical height

---

## Related

- ← Previous: [[BP_Interface_Demystified]]
- → Next: [[BP_Vectors_Applied_Dash_and_Launch]]
- 📚 Series: [[_MOC_Blueprint_Fundamentals]]
