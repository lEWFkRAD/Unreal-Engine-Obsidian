---
title: "Unreal Engine Blueprint Fundamentals | Class #5 | For Loops & Arrays"
source: "https://www.youtube.com/watch?v=YvG5XPw_3tw"
video_id: "YvG5XPw_3tw"
type: "youtube-summary"
series: "Blueprint Fundamentals"
episode: 5
tags: [ue5, tutorial, blueprint, fundamentals, gamedev, visual-scripting]
---

# Unreal Engine Blueprint Fundamentals: For Loops & Arrays

## Overview
- **Channel**: Ask A Dev
- **Duration**: 34:25
- **Focus**: For Loops and Arrays for flexible, efficient data management

## The Problem: Manual Array Access
Without loops, accessing each array element requires manually referencing each index. This is:
- Not scalable
- Error-prone
- Inefficient

## For Each Loop (Simplest & Most Common)
Iterates through each element in an array automatically.

### Node Structure:
- **Input**: Takes an array (e.g., `Fruits`)
- **Output Pins**:
  - `Array Element`: Current item in the iteration
  - `Array Index`: Current index number
  - `Loop Body`: Execution path for each element
  - `Completed`: Execution path when loop finishes

```blueprint
[Begin Play] -> [Fruits Array] -> [For Each Loop] -> [Loop Body: Print String]
```

## For Loop (More Control)
Manual iteration with specific start/end indices.

### Dynamic Length Handling:
```blueprint
[Fruits Array] -> [Length] -> [Subtract] (value: 1) -> [For Loop: Last Index]
```

## Key Array Operations
- **Getting All Actors**: Use `Get All Actors of Class` to create an array of specific objects
- **Modifying Array Elements**: Use `Set Array Element` with index to update values

## Practical Examples

### Example 1: Printing All Array Items
```blueprint
[Fruits Array] -> [For Each Loop] -> [Loop Body: Print String]
[Completed] -> [Print String] ("Finished Printing")
```

### Example 2: Modifying Array Values
```blueprint
For Loop (0 to Array Length - 1)
[Get Array Item] -> [Append "s"] -> [Set Array Element]
```
Result: `Apple` → `Apples`, `Banana` → `Bananas`, etc.

### Example 3: Real-World Application - Scaling Houses
```blueprint
[Get All Actors of Class] (House Template) -> [For Each Loop]
[Loop Body]: [Set World Scale 3D] to target scale
```

Using index with modulo for conditional processing:
```blueprint
[Index] -> [Modulo] (value: 2) -> [Branch]
True: Scale = Target Scale × 1.5
False: Scale = Target Scale
```

## When to Use Which Loop
- **For Each Loop**: Preferred for simplicity when you just need to process each element
- **For Loop**: More control when you need to modify elements using indices, process subsets, or perform conditional operations based on index

---

## Related

- ← Previous: [[BP_Class_5-4_Nested_Loops_and_Bubble_Sort]]
- → Next: [[BP_Class_5_For_Loops_and_Arrays]]
- 📚 Series: [[_MOC_Blueprint_Fundamentals]]
