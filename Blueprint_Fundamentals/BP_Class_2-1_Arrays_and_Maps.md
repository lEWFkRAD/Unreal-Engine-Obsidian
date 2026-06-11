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
**Video**: UE Blueprint Fundamentals | Class #2-1 | Variables : Array & Maps
**Channel**: Ask A Dev
**Duration**: 27:41 | **Published**: May 6, 2023 | **Views**: 38.5K | **Likes**: 1.76K
**Category**: Education | **Tags**: #ue5 #beginner #tutorial #unreal #blueprint #gamedevelopment

**Description**: Essential addendum to variables training covering Array and Map container types for efficient game development. Suitable for beginners and experienced developers.

## Key Concepts: Container Types

### 1. Container Type Basics
- **Single**: Default type - holds one value per variable (one item in the "bucket")
- **Arrays & Maps**: Special container types holding multiple values
- **Container Type Selection**: Found next to variable type in Blueprint editor

## Arrays (Lists)

### Core Concept
> "A very important container type in Unreal Engine because an array you can think of it as a list or a series of variables inside your bucket."

### Practical Example: Fruit List
1. Create variable "fruits" as **string array**
2. Set default values in editor:
   - Index 0: Apple
   - Index 1: Banana
   - Index 2: Mango

### Accessing Array Elements
- **Indexing**: Arrays use **zero-based indexing** (0, 1, 2...)
- **Get Operation**: Drag from array → select "Get" → specify index

### Setting Array Elements
Two Methods:
1. **Set Entire Array**: Use "Make Array" node (replaces all elements)
2. **Set Single Element**: Use "Set Array Element" node (changes specific index)

### Common Use Cases
- Enemies in scene
- Inventory items
- Weapons carried
- Obstacles/cameras
- Characters in radius

> "Anytime you would want to store multiple of a group of things we're going to be using array and we do this a lot."

## Maps (Lookup Tables)

### Core Concept
> "A map is a little bit different than an array but it works very similarly... A map has two parts: an address that you decide and a value."

### Practical Example: Weapons Map
1. Create variable "weapons" as **string to integer map**
2. Set default values:
   - Address: "pistol" → Value: 8 (ammo)
   - Address: "rifle" → Value: 5
   - Address: "shotgun" → Value: 2

### Accessing Map Elements
- Use "Find" node with address (key) → returns associated value

### Flexible Type System
- **Configurable Types**: Both address and value can be different types
- **Example Change**: String→String map
  - "pistol" → "Glock"
  - "rifle" → "sniper"
  - "shotgun" → "case"

### Maps vs Arrays
| Feature | Arrays | Maps |
|---------|--------|------|
| **Access Method** | Numeric index (0,1,2) | Custom keys (any type) |
| **Use Case** | Ordered lists | Key-value associations |
| **Example** | Fruit list | Weapon→ammo count |

## Key Insights & Best Practices

### 1. Container Type Selection
> "Container types... determine when you look inside the bucket is there one value is there five values."

### 2. Zero-Based Indexing
> "The address or the index starts at zero... the First Dimension in this case they mean index so the index 2 refers to Mango."

### 3. Practical Recommendations
- **Focus on Arrays**: More commonly used than Maps
- **Maps for Lookups**: Use when you need custom addressing
- **Visual Scripting Advantage**: UE provides visual feedback for container operations

### 4. Common Pitfalls to Avoid
- Confusing "Set Array" (entire array) with "Set Array Element" (single item)
- Assuming second item is at index 1 (actually index 0 is first)
- Using wrong method to access map elements (use "Find" not "Get")

---

## Related

- ← Previous: [[BP_Class_1_Workbook]]
- → Next: [[BP_Class_2-1_Variables_Array_Maps]]
- 📚 Series: [[_MOC_Blueprint_Fundamentals]]
