---
title: "UE Blueprint Fundamentals | Class #5-4 | Nested Loops & Bubble Sort"
source: "https://www.youtube.com/watch?v=rI0WS9Rw7ds"
video_id: "rI0WS9Rw7ds"
type: "youtube-summary"
series: "Blueprint Fundamentals"
episode: 5
tags: [ue5, tutorial, blueprint, fundamentals, gamedev, visual-scripting]
---

# UE Blueprint Fundamentals: Nested Loops & Bubble Sort

## Overview
- **Channel**: Ask A Dev
- **Duration**: 32:08
- **Focus**: Nested For Loops and implementing Bubble Sort algorithm in UE Blueprints

## 1. Nested For Loops: Practical Example

### Goal
Find which character in the scene has a specific item (e.g., "Golden Gun").

### Setup
- **Variables** on each actor:
  - `ItemStash` (Array of all possible items)
  - `Inventory` (Array of items character currently carries)
- **On Begin Play**: Fill each character's inventory with 4–10 random items from stash

```blueprint
Random Int in Range (4 to 10) -> For Loop (0 to RandomInt)
  Random Int in Range (0 to (Stash Length - 1)) -> Get Item -> Add to Inventory
```

### Nested Loop Implementation
- **Outer Loop**: Iterate through all actors using `Get All Actors Of Class`
- **Inner Loop**: For each actor, iterate through their `Inventory`
- **Condition**: Check if item name equals "Golden Gun" (String Equals node)
- **Action**: Draw debug cone above character if true

> "Nested loops are needed when you must check 'for every character, for every item in their backpack.'"

## 2. Bubble Sort Algorithm

### How It Works
1. **Supervisor Loop**: Runs `Array Length - 1` times
2. **Worker Loop**: Compares adjacent elements and swaps if left is greater
3. After each pass, largest unsorted element is in correct position

### Example Walkthrough
Array: `[20, 7, 21, 5, 11, 8, 2]`
- Pass 1: Compare 20 & 7 → swap → `[7, 20, 21, 5, 11, 8, 2]`
- Continue comparing each adjacent pair until largest (21) is at end

### Blueprint Implementation
1. Generate random array of 20 integers (0–50)
2. **Supervisor For Loop**: Indices 0 to Array Length - 1
3. **Worker For Loop**: Indices 0 to (Array Length - 1 - Supervisor Index - 2)
4. **Comparison**: If `Array[Worker Index] > Array[Worker Index + 1]`, swap
5. **Optimization**: Break early if no swaps occur in a pass

```blueprint
Supervisor For Loop (0 to Array Length - 1)
  Worker For Loop (0 to (Array Length - 1 - Supervisor Index - 2))
    Get Array[Worker Index] and Array[Worker Index + 1]
    If Greater Than → Swap Array Elements
```

## Efficiency Tips
1. **Reduce Work Each Pass**: Skip already-sorted end elements
2. **Early Exit**: Break if no swaps occur (array is sorted)
3. **Note**: Bubble sort is O(n²) — inefficient for large datasets, but valuable for learning

## Key Takeaways
- Nested loops enable multi-level iteration (characters × inventory items)
- Bubble sort demonstrates nested loops in a CS context
- Always consider efficiency optimizations

---

## Related

- ← Previous: [[BP_Class_5-3_Loops_Arrays_Applied_3]]
- → Next: [[BP_Class_5-4_Nested_Loops_and_Bubble_Sort]]
- 📚 Series: [[_MOC_Blueprint_Fundamentals]]
