---
title: "Unreal Engine Blueprint Fundamentals | Class #5 | For Loops & Arrays"
source: "https://www.youtube.com/watch?v=YvG5XPw_3tw"
video_id: "YvG5XPw_3tw"
type: "youtube-summary"
series: "Blueprint Fundamentals"
episode: 5
tags: [ue5, tutorial, blueprint, fundamentals, gamedev, visual-scripting]
---

# Unreal Engine Blueprint Fundamentals: For Loops & Arrays Summary

## Core Concepts
This tutorial teaches efficient data manipulation using **Arrays** (lists of data) and **For Loops** (automated iteration). It demonstrates why manual array access is inefficient and introduces two powerful loop types for dynamic operations.

> "The for Loop helps us work with arrays much more efficiently... allows us to work with large lists or arrays of information."

## 1. The Problem: Manual Array Access
- To print array items, you must manually get each by index (e.g., index 0, 1, 2, 3).
- **Issue:** This is static, not scalable. If the array changes (items added/removed), code must be updated manually.
- Adding/removing an item can cause errors if indices are out of bounds.

## 2. Solution: `For Each` Loop
The simplest and most common loop for arrays.

**How it works:**
1. Takes an **Array** as input.
2. **Loop Body:** Executes for every item in the array.
3. **Array Element:** Output pin that holds the current item.
4. **Array Index:** Output pin that holds the integer index (address) of the current item.
5. **Completed:** Executes after the entire array has been processed.

**Key Advantage:** Automatically adapts to array size changes. No code modification needed.

## 3. Solution: Traditional `For Loop`
A more manual loop that provides precise index control.

**How it works:**
1. Takes **First Index** and **Last Index** as inputs.
2. **Loop Body:** Executes for each integer from start to end.
3. **Index:** Output pin for the current integer index.
4. Use this index to **Get** items from the array.

**Example - Getting Array Length Dynamically:**
- To loop through a dynamic array, get its length: `Get (Fruits) -> Length`.
- Connect length to **Last Index**. Subtract 1 to avoid an "index out of range" error (since indices start at 0).

## 4. Practical Examples & Patterns

### A. Modifying Array Values
Use the traditional `For Loop` to update items by index.
- **Goal:** Append "S" to each fruit string in the array.
- **Steps:**
  1. Loop from `0` to `(Array Length - 1)`.
  2. In the loop: `Get (Fruits)` at current **Index** → `Append` "S" → `Set Array Element` at the same **Index**.

### B. Operating on Scene Actors
**Pattern:** `Get All Actors of Class` → `For Each` Loop → Perform Action.
- **Example:** Scale all "House Template" actors in the level.
- **Steps:**
  1. `Get All Actors of Class` (e.g., `BP_House_Template`) returns an **Array**.
  2. Connect to a `For Each` loop.
  3. In the loop body: `Get Display Name` (for debugging) or **Set World Scale 3D** on the actor's root.

**Advanced Pattern:** Use the **Index** to conditionally modify odd/even items.
- **Example:** Use `Mod (2)` on the index + a **Branch** to set different scales for odd vs. even numbered houses.

## Key Takeaways
1. **Prefer `For Each` Loop** for simplicity and direct access to array elements.
2. **Use Traditional `For Loop`** when you need the integer index for calculation or direct modification.
3. **Loops are essential** for operating on multiple game objects (actors, enemies, items) efficiently.
4. **`Get All Actors of Class`** is a common method to obtain an array of scene objects to iterate over.
5. Always consider array length and index bounds to avoid runtime errors.

---

## Related

- ← Previous: [[BP_Class_5-4_Nested_Loops_and_Bubble_Sort]]
- → Next: [[BP_Class_6-1_UI_Layout]]
- 📚 Series: [[_MOC_Blueprint_Fundamentals]]
