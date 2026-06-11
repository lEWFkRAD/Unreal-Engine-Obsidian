---
title: "UE Blueprint Fundamentals | Class #5-1 | Loops & Arrays Applied #1"
source: "https://www.youtube.com/watch?v=1fRwoq0Z8y4"
video_id: "1fRwoq0Z8y4"
type: "youtube-summary"
series: "Blueprint Fundamentals"
episode: 5
tags: [ue5, tutorial, blueprint, fundamentals, gamedev, visual-scripting]
---

# UE Blueprint Fundamentals: Loops & Arrays Applied (Finding Closest Object)

## Overview
First of three methods to find the closest object to a character using For Loops and Arrays in UE Blueprints.

## Core Algorithm: Smallest Distance Search
1. Initialize `closest distance so far` to a very large number
2. Loop through each object in the array
3. Calculate distance from character to current object
4. **If** distance < `closest distance so far`:
   - Update `closest distance so far`
   - Update `closest object so far`
5. After loop, `closest object so far` holds the result

## Blueprint Implementation

### 1. Function Creation
Create function `Get_Closest_Object` with local variables:
- `Closest Distance So Far` (Float) — initialized to `100,000` or `1,000,000`
- `Closest Object So Far` (Object Reference)

### 2. Array Retrieval & Loop
- Use `Get All Actors Of Class` targeting item class → returns array
- Connect array to `For Each Loop`

### 3. Core Loop Logic
```blueprint
1. Get Actor Location of current loop item
2. Get Actor Location of self (character)
3. Calculate distance between the two
4. Less Than: check if distance < Closest Distance So Far
5. If true:
   - Set Closest Object So Far = current item
   - Set Closest Distance So Far = new distance
```

### 4. Function Output
- Return Node with `Closest Item` output pin
- Connect `Closest Object So Far` to return pin

### 5. Event Graph Integration
- Call `Get_Closest_Object` from custom event
- Visualize with `Draw Debug Sphere`
- Automate with `Set Timer By Event` (2 seconds, looping)

## Key Insights
- **Pattern**: Fundamental algorithm for finding min/max values in an array
- **Flexibility**: Same logic works for most ammo, highest health, etc.
- **Performance Note**: `Get All Actors Of Class` every iteration is not optimized; production code would cache the array
- **This is Method 1/3**: Two more methods coming in subsequent videos

---

## Related

- ← Previous: [[BP_Class_4_Branches_and_Booleans]]
- → Next: [[BP_Class_5-2_Loops_Arrays_Applied_2]]
- 📚 Series: [[_MOC_Blueprint_Fundamentals]]
