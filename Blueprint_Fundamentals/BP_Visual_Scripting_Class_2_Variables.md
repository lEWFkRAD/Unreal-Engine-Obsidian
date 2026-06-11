---
title: "UE Blueprint Fundamentals | Visual Scripting Class #2 | Variables"
source: "https://www.youtube.com/watch?v=Tnd5WB5tqSc"
video_id: "Tnd5WB5tqSc"
type: "youtube-summary"
series: "Blueprint Fundamentals"
episode: 2
tags: [ue5, tutorial, blueprint, fundamentals, gamedev, visual-scripting]
---

# UE Blueprint Fundamentals: Variables

## Core Concept: What Variables Are
Variables are like **buckets that store information**:
- Put things in (set value)
- Take things out (get value)
- Each bucket has a specific type (only holds one kind of data)

## Defining Variables in UE Blueprints
- **Location**: Event Graph → Variables section (left panel)
- **Creation**: Click `+` to create new variable
- **Type Selection**: Must specify data type

## Common Variable Types

| Type | Description | Use Cases |
|------|-------------|-----------|
| **Boolean** | True/false value | `IsJumping`, `IsDying`, `OutOfAmmo` |
| **Integer** | Whole numbers | Bullet count, day of month |
| **Float** | Decimal numbers | Health, damage multipliers, animation blends |
| **String/Text/Name** | Character sequence | Character names, UI text |
| **Vector** | 3 values (X,Y,Z) | Positions, RGB colors |
| **Rotator** | 3D rotation | Object rotation |
| **Transform** | Translation + rotation + scale | Complex object transforms |

## Key Operations

### Basic Get/Set Pattern
```
Begin Play →
  Get MyFirstVariable (prints 0) →
  Set MyFirstVariable = 2 →
  Get MyFirstVariable (prints 2)
```

### Math Operations with Variables
- Multiplication: `Set SecondVariable = 2.0 * 5.0` → 10.0
- Addition: `Set SecondVariable = 1 + 2` → 3.0
- Incrementing: `Set SecondVariable = SecondVariable + 2`

### Why Variables Matter: Centralized Updates
Without variables, updating 10 instances of "2.0" scattered throughout blueprint requires hunting each one. With a `JumpHeight` variable, update once.

## Practical Example: House Scaling
- **Single Float**: `HouseScale` variable (float, default 1.0)
- **Vector Variable**: `HouseScaleVector` for per-axis control

## Pro Tips & Shortcuts
1. **Auto-connect variables**: Drag variable directly to pin
2. **Promote to Variable**: Right-click any pin → "Promote to Variable"
3. **Split struct pins**: Right-click vector pin → "Split Struct Pin"
4. **Conversion nodes**: Auto-created when connecting incompatible types

## Key Takeaway
Variables enable dynamic, maintainable Blueprints with reduced errors through centralized values.

---

## Related

- ← Previous: [[BP_Vectors_Applied_Dash_and_Launch]]
- 📚 Series: [[_MOC_Blueprint_Fundamentals]]
