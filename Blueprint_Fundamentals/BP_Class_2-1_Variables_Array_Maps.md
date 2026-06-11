---
title: "UE Blueprint Fundamentals | Class #2-1 | Variables : Array & Maps"
source: "https://www.youtube.com/watch?v=wmY17-a9xpc"
video_id: "wmY17-a9xpc"
type: "youtube-summary"
series: "Blueprint Fundamentals"
episode: 2
tags: [ue5, tutorial, blueprint, fundamentals, gamedev, visual-scripting]
---

# UE Blueprint Fundamentals: Arrays & Maps

## Overview
Addendum to the variables training focusing on **container types** in UE Blueprints: **Arrays** and **Maps**.

## Core Concept: The Bucket Analogy
- **Single**: Holds one value (e.g., a string or integer)
- **Array**: Holds an ordered list of values
- **Map**: Holds key-value pairs for flexible lookups

## Arrays

### Definition & Structure
An **array** is an ordered list of values of the **same type**. Each item has an **index** (starting at 0).

Example: `Fruits` array: `["Apple", "Banana", "Mango"]`
- Index 0 = "Apple", Index 1 = "Banana", Index 2 = "Mango"

### Key Operations
- **Creating**: Set variable Type, change Container Type to `Array`, add default values
- **Accessing**: `GET Fruits (Index: 0)` → "Apple"
- **Setting Individual Elements**: Use `Set Array Element` with index and value
- **Important**: Setting an array with `Set` replaces the entire array

### Key Considerations
- **Zero-based indexing**: First item is at index 0
- **Use Cases**: Enemies, inventory, weapons, cameras

## Maps

### Definition & Structure
A **map** stores **key-value pairs** where:
- **Key**: Unique identifier (any type)
- **Value**: Data associated with the key (can be different type)

Example: `Weapons` map: `{"Pistol": "Glock", "Rifle": "Sniper"}`

### Key Operations
- **Creating**: Set types for key and value, change Container Type to `Map`
- **Accessing**: `FIND Weapons (Key: "Rifle")` → "Sniper"
- **Setting**: `SET Weapons Map (Key: "Knife", Value: "Deathblade")`
- Maps support `Clear`, `Remove`, `Keys`, `Values`, and `Length`

## Key Differences: Arrays vs. Maps

| Feature | Array | Map |
|---------|-------|-----|
| **Structure** | Ordered list | Key-value pairs |
| **Access Method** | By index | By key |
| **Common Uses** | Lists of similar items | Lookup tables |

## Instructor Insights
- **Arrays are fundamental**: Used extensively for handling multiple objects
- **Maps are less common** but useful for custom lookups
- **Upcoming topics**: Control flow structures (loops) for iterating through arrays

---

## Related

- ← Previous: [[BP_Class_2-1_Arrays_and_Maps]]
- → Next: [[BP_Class_2-2_Vectors]]
- 📚 Series: [[_MOC_Blueprint_Fundamentals]]
