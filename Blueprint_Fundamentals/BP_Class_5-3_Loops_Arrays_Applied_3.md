---
title: "UE Blueprint Fundamentals | Class #5-3 | Loops & Arrays Applied #3"
source: "https://www.youtube.com/watch?v=HIEHZY26EcM"
video_id: "HIEHZY26EcM"
type: "youtube-summary"
series: "Blueprint Fundamentals"
episode: 5
tags: [ue5, tutorial, blueprint, fundamentals, gamedev, visual-scripting]
---

# UE Blueprint Fundamentals: Finding Closest Object via Sorting

## Overview
Third method in the series — sorts an array of objects by distance to character, enabling access to not just the closest but also the farthest or any item in order.

## Why Learn This When `Find Nearest Actor` Exists?
> "The whole point of this is to learn how arrays and for loops work... you may not always be looking for the closest actor — we may be looking for the most ammo or the least amount of health... and so you need to be able to find the max, sort them, etc."

## The Problem with Standard For Each Loops
When removing items from an array during a `For Each` loop, indices shift, causing the loop to skip items or error.

**Solution**: Use a Reverse For Loop or an Index-Driven For Loop.

## Method C: Sorting with a Reverse For Loop

### Process:
1. Get all actors of class and store them
2. Calculate distances from character to each actor → `Local_Distances`
3. Use a **Reverse For Loop** on `Local_Distances`
4. Inside loop:
   - Find **Max Float** value in `Local_Distances` and get its **Index**
   - **Promote index to local variable** to avoid re-evaluation errors
   - **Add** actor at that index to new `Sorted_Actors` array
   - **Remove** item at that index from **both** `Local_Distances` and original actor array
5. Result: `Sorted_Actors` sorted from farthest to closest

## Method D: Sorting with Index-Driven (Counting) For Loop

### Process:
1. Steps 1 & 2 identical to Method C
2. Get Length of `Local_Distances` → store as `Total_Loop_Count`, subtract 1
3. Use standard **For Loop** with `First Index: 0`, `Last Index: (Total_Loop_Count - 1)`
4. Inside loop: same as Method C (find max, promote index, add to sorted, remove from both)

### Key Pattern:
```blueprint
Max Float (Array) -> Local_Distances -> output "Index"
Promote "Index" to Local Variable ("Index_of_Max")
Use this variable for all Get and Remove operations in this iteration
```

## Practical Applications
- **Find closest actor with specific property**: Iterate sorted list until first actor meets condition
- **Scale effects by distance**: Apply damage/UI that varies based on rank in sorted list
- **Foundation for complex queries**: Sort by any metric (health, threat level, etc.)

---

## Related

- ← Previous: [[BP_Class_5-2_Loops_Arrays_Applied_2]]
- → Next: [[BP_Class_5-4_Nested_Loops_and_Bubble_Sort]]
- 📚 Series: [[_MOC_Blueprint_Fundamentals]]
