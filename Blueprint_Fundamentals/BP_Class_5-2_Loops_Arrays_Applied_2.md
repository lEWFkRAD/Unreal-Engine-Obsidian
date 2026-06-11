---
title: "UE Blueprint Fundamentals | Class #5-2 | Loops & Arrays Applied #2"
source: "https://www.youtube.com/watch?v=6Muuo4sGx2k"
video_id: "6Muuo4sGx2k"
type: "youtube-summary"
series: "Blueprint Fundamentals"
episode: 5
tags: [ue5, tutorial, blueprint, fundamentals, gamedev, visual-scripting]
---

# UE Blueprint Fundamentals: Finding Closest Object Using Two Arrays

## Overview
**Method B** for finding the closest object to a character using UE Blueprints. Uses two parallel arrays: one for objects, one for distances.

## Core Concept
> "We have our array of objects, we have our array of distances — they are the same length... index 3 of the largest number is the same index as our object."

**Index alignment** is critical: the distance for object at index 0 is stored at index 0 in the distances array.

## Implementation Steps

### 1. Setup the Input Array
```blueprint
Get All Actors Of Class -> (Array of Actors)
```

### 2. Create a Parallel Distances Array
- Add local variable `Distances` (Float, Array type)

### 3. Loop and Calculate Distances
```blueprint
For Loop (over Actor Array) ->
    Get Actor Location (Item) & Get Actor Location (Self) ->
        Get Distance ->
            Add to (Distances Array)
```

### 4. Find Min/Max Index
```blueprint
Min Of Float Array (Distances) -> (Min Index)
Get (Actor Array, Min Index) -> (Closest Object)
```

### 5. Return the Result
- Add Return Node with closest object connected

### 6. Visualization
```blueprint
Get Closest Object Method B ->
    Get Actor Location (Returned Object) ->
        Draw Debug Sphere (Duration: 1, Thickness: 1, Color: Blue, Radius: 40)
```

## Key Applications
- Find **closest** or **furthest** object (Min or Max of float array)
- Find **object with most/least of a value** (e.g., bag with most gold by storing amounts in second array)

## Comparison with Method A
- Method A: Updates closest object inside the loop (single pass)
- Method B: Builds distance array first, then uses built-in `Min Of Float Array` (two passes but leverages UE built-ins)

---

## Related

- ← Previous: [[BP_Class_5-1_Loops_Arrays_Applied_1]]
- → Next: [[BP_Class_5-3_Loops_Arrays_Applied_3]]
- 📚 Series: [[_MOC_Blueprint_Fundamentals]]
