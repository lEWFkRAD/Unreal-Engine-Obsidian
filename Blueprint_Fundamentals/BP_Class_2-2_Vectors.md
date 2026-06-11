---
title: "UE Blueprint Fundamentals | Class #2-2 | Vectors"
source: "https://www.youtube.com/watch?v=68j4XXVw4Eg"
video_id: "68j4XXVw4Eg"
type: "youtube-summary"
series: "Blueprint Fundamentals"
episode: 2
tags: [ue5, tutorial, blueprint, fundamentals, gamedev, visual-scripting]
---

# UE Blueprint Fundamentals: Vectors

## Overview
Demystifies vectors in UE Blueprints. The term "vector" has two primary meanings:
1. A **list of numbers** (e.g., a point in 3D space or a color value)
2. A **geometric/physics representation** of a direction with magnitude

## 1. Vector as a List of Numbers
Represents a point or set of coordinates, not direction.
- **In Blueprints**: `Vector` variable with `X, Y, Z` for location in space
- **In Materials**: Used for multi-value data (2Vector for UV, 3Vector for RGB, 4Vector for RGBA)

**Naming Convention**: Use `StartPosition` or `TargetLocation` to indicate a point, not direction.

## 2. Geometric/Physics Vector
A **direction + magnitude (length)**, visualized as an arrow.

**Core Concept**: A vector has **no inherent position**. Two identical vectors drawn at different points are still the same vector.

### Fundamental Operations
- **Get Forward Vector**: Returns unit vector (length 1) in actor's facing direction
- **Scaling**: Multiply by float to change length (`ForwardVector * 200.0`)
- **Normalize**: Adjusts components so length becomes exactly 1 (unit vector)
- **Draw Debug Arrow**: Draws line between two points (start + end)

**Common Mistake**: Using actor's location as start and ForwardVector as end. Solution: Use vector addition.
```
End Point = ActorLocation + (ForwardVector * 200.0)
```

## Vector Addition & Subtraction

### Addition (A + B)
Order does NOT matter. Use case: Repositioning direction vector.
```
ArrowEnd = ActorLocation + (ForwardVector * 200)
```

### Subtraction (A - B)
Order matters. Result points from B to A.
- `A - B` → Points toward A
- `B - A` → Points toward B
- **Use Case**: Finding direction from enemy to target: `DirectionToTarget = TargetLocation - EnemyLocation`

## Dot Product & Cross Product

### Dot Product (A · B)
Scalar value (-1 to 1) indicating alignment of unit vectors:
- **1.0**: Parallel (same direction)
- **0.0**: Perpendicular (90° apart)
- **-1.0**: Anti-parallel (opposite directions)
- **Use Case**: One-way door — check if character faces forward or backward relative to door's normal

### Cross Product (A × B)
Returns vector **perpendicular** to both inputs. Order determines direction.
- **Use Case**: Calculate surface normal of polygon or which way a wall is facing for wall-running

## Key Takeaways
1. Clarify whether "vector" means a list of numbers or a direction with magnitude
2. Vectors have no inherent position
3. Dot product for alignment checking, cross product for perpendicular vectors

---

## Related

- ← Previous: [[BP_Class_2-1_Variables_Array_Maps]]
- → Next: [[BP_Class_2_Variables]]
- 📚 Series: [[_MOC_Blueprint_Fundamentals]]
