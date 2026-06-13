---
title: "UE Blueprint Fundamentals | Visual Scripting Class #2 | Variables"
source: "https://www.youtube.com/watch?v=Tnd5WB5tqSc"
video_id: "Tnd5WB5tqSc"
type: "youtube-summary"
series: "Blueprint Fundamentals"
episode: 2
tags: [ue5, tutorial, blueprint, fundamentals, gamedev, visual-scripting]
---

# UE Blueprint Fundamentals: Variables Summary

## Overview
This tutorial (Part 2 of a visual scripting crash course) explains **variables in Unreal Engine 5 Blueprints** using a practical "bucket analogy" to build foundational understanding for creatives.

---

## Core Concept: The "Bucket Analogy" for Variables
> **Key Insight:** Forget technical definitions. Think of a variable as a **labeled bucket** that stores information.

- **A bucket holds items** (rocks, water, dirt) just like a **variable holds data** (numbers, text, true/false values).
- **Buckets can be labeled/named** so you know which one to use (e.g., "MyFirstVariable").
- **Buckets can be empty** (a variable can have no value).
- **Unreal requires specifying bucket type** (like a "water bucket" only holds water, an integer variable only holds whole numbers).

---

## Defining & Using Variables in the Blueprint Editor

### Location & Creation
- Find the **Variables panel** on the left in the Event Graph.
- Click the **"+"** icon to create a new variable (default name: "NewVar").

### Essential Properties (Right Panel)
1. **Variable Type:** Specify the data type (integer, float, boolean, etc.).
2. **Default Value:** Set the initial value (requires **Compile** to update).

### Two Key Actions: Get vs. Set
- **GET:** Retrieve the value currently inside the "bucket."
- **SET:** Put a new value into the "bucket."

```
Example Flow:
Begin Play → GET MyFirstVariable (prints 0) → SET MyFirstVariable to 2 → GET MyFirstVariable (prints 2)
```

---

## Common Variable Types Explained
| Type | Description | Use Cases |
|------|-------------|-----------|
| **Boolean** | `true` or `false` value | Is jumping? Is dead? Is out of ammo? |
| **Integer** | Whole number (e.g., `0`, `42`, `-5`) | Bullet count, day of month, score |
| **Float** | Decimal number (e.g., `0.0`, `3.14`, `-2.5`) | Health, animation blend, object scale, damage multipliers |
| **String/Name/Text** | Sequence of characters | Character names, UI text, dialogue |
| **Vector** | Three values (`X`, `Y`, `Z`) | 3D position, RGB color, directional force |
| **Rotator** | 3D rotation (pitch, yaw, roll) | Object orientation |
| **Transform** | Combines translation, rotation, scale | Full object placement data |

---

## Math Operations with Variables
You can perform math on variables to create dynamic behaviors.

```
Set SecondVariable = 2.0 * 5.0   // Result: 10.0
Set SecondVariable = 1 + 2        // Result: 3
Set SecondVariable = SecondVariable + 2  // Increment by 2
```

**Ammo Example Logic:**
1. On weapon fire → GET current ammo.
2. Subtract 1.
3. SET ammo to new value.

---

## The Power of Variables: Centralized Control

### Problem Without Variables:
If you hardcode a value (e.g., jump multiplier `2.0`) in multiple places, updating it requires finding and changing every instance—**error-prone and time-consuming**.

### Solution With Variables:
1. Create a variable called `JumpHeight` (default: `1.0`).
2. Use `Get JumpHeight` connected to all multiply nodes.
3. To change jump power globally, **just update the variable's default value**.

> **Maintenance Win:** "If I wanted it to be 4 times as high, I can just change this back down to 1.5... That's it. I'm done."

---

## Practical Example: Controlling House Scale

### Scenario: Scale a house model over time with delays
1. **Create `HouseScale` (Float)** and `DelayDuration` (Float).
2. Use `HouseScale` to multiply scale vectors.
3. Use `DelayDuration` for all delay nodes.

```
Begin Play → Delay(DelayDuration) → Set World Scale = (HouseScale * 2.0) → Delay → Set Scale = (HouseScale * 4.0)...
```

### Vector Control Bonus:
- Use a **Vector variable** for `HouseScale` to control `X`, `Y`, `Z` independently (e.g., make house taller without making it wider).
- **Pro Tip:** Right-click a vector pin → **Split Struct Pin** to access individual axes (`X`, `Y`, `Z`) directly.

---

## Additional Tips & Tricks
- **Promote to Variable:** Right-click any pin → `Promote to Variable` to auto-create and connect a variable.
- **Quick Connection:** Drag a variable directly onto a compatible pin to auto-connect (avoids manual `Get` node).
- **Conversion Nodes:** Unreal auto-inserts conversion nodes (e.g., `Integer to String` for printing).

---

## Key Takeaways
1. **Variables = Labeled Buckets** that store data in Unreal Blueprints.
2. **Define, Get, Set** are the three core operations.
3. **Choose the right type** (Boolean, Integer, Float, Vector, etc.) for your data.
4. **Use variables to centralize control**—change one value to update everywhere, reducing errors and maintenance.
5. **Vectors** provide multi-axis control for positions, scales, and colors.
6. Variables make Blueprints **easier to update, maintain, and debug**.

---

## Related

- ← Previous: [[BP_Class_2-2_Vectors]]
- → Next: [[BP_Class_3_Events_and_Functions]]
- 📚 Series: [[_MOC_Blueprint_Fundamentals]]
