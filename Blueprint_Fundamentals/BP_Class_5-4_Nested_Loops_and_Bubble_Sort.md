---
title: "UE Blueprint Fundamentals | Class #5-4 | Nested Loops & Bubble Sort"
source: "https://www.youtube.com/watch?v=rI0WS9Rw7ds"
video_id: "rI0WS9Rw7ds"
type: "youtube-summary"
series: "Blueprint Fundamentals"
episode: 5
tags: [ue5, tutorial, blueprint, fundamentals, gamedev, visual-scripting]
---

# UE Blueprint Fundamentals | Class #5-4 | Nested Loops & Bubble Sort Summary

## Overview
This tutorial demonstrates **nested for loops** in Unreal Engine Blueprints and implements the **Bubble Sort** algorithm. It's part of a visual scripting crash course for creatives. Key techniques include iterating through arrays within arrays and optimizing sort operations.

## Key Concepts
- **Nested Loops**: A loop inside another loop. Practical for multi-dimensional searches (e.g., checking items in all characters' inventories).
- **Bubble Sort**: A basic sorting algorithm using nested loops to swap adjacent elements until an array is ordered. Largest values "bubble up" to the end with each pass.

## Implementation Details

### 1. Setting Up Arrays & Characters
- Created `ItemBase` actors with:
  - `ItemStash` (variable array of possible items)
  - `Inventory` (variable array of carried items)
- Populated inventories randomly on `BeginPlay`:
  ```
  For Loop (0 to RandomInt(4,10)):
      RandomIndex = RandomInt(0, StashLength - 1)
      Add Stash[RandomIndex] to Inventory
  ```

### 2. Nested Loop Example: Finding "Golden Gun"
- **Goal**: Identify characters possessing a "Golden Gun".
- **Logic**:
  ```
  For Every Actor (ItemBase):
      For Every Item in Actor's Inventory:
          If Item == "Golden Gun" (String Equal):
              Draw Debug Cone at Actor Location
  ```
- **Outcome**: Debug cones mark actors with the Golden Gun.

### 3. Bubble Sort Algorithm
- **Structure**:
  - **Supervisor Loop**: Runs `(ArrayLength - 1)` times (ensures full sort).
  - **Worker Loop**: Compares/swaps adjacent elements each pass.
- **Steps**:
  1. Generate a random integer array (e.g., 20 values 0–50).
  2. **Supervisor Loop** (`0` to `ArrayLength - 1`):
  3. **Worker Loop** (`0` to `ArrayLength - 2 - SupervisorIndex`):
     - If `Array[i] > Array[i+1]`:
       - Swap elements using `Swap Array Elements` node.
       - Set `SwapFound = true`.
  4. **Early Exit**: If no swaps occur in a worker loop pass, break out early (array is sorted).
- **Visual Output**:
  - Unsorted array (red print).
  - Sorted array (green print).

## Efficiency Tips
1. **Skip Sorted Elements**:
   - Reduce worker loop upper bound by subtracting `SupervisorIndex`:
     ```
     Worker Loop Upper Bound = ArrayLength - 2 - SupervisorIndex
     ```
   *Rationale: After `n` passes, last `n` elements are correctly positioned.*

2. **Early Termination**:
   - Track swaps with a `SwapFound` boolean.
   - If no swaps occur in a worker loop pass, exit supervisor loop early.

3. **Note**: Bubble Sort is **inefficient for large datasets** (O(n²) time complexity). Prefer faster algorithms (e.g., insertion sort) for real-world use.

## Key Takeaways
- **Nested Loops** solve problems requiring iteration over multiple levels (e.g., actors → inventories).
- **Bubble Sort** is a foundational algorithm demonstrating nested loop mechanics but has limited practical efficiency.
- **Optimizations** (reducing passes, early exit) significantly improve performance.
- Use **debug drawing** (e.g., `Draw Debug Cone`) for visual verification in Blueprints.

---

## Related

- ← Previous: [[BP_Class_5-4_Nested_Loops_Bubble_Sort]]
- → Next: [[BP_Class_5_For_Loops_Arrays]]
- 📚 Series: [[_MOC_Blueprint_Fundamentals]]
