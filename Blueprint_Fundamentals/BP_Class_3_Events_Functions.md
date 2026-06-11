---
title: "UE Blueprint Fundamentals | Class #3 | Events & Functions"
source: "https://www.youtube.com/watch?v=Wc9pdjJysi4"
video_id: "Wc9pdjJysi4"
type: "youtube-summary"
series: "Blueprint Fundamentals"
episode: 3
tags: [ue5, tutorial, blueprint, fundamentals, gamedev, visual-scripting]
---

# UE Blueprint Fundamentals: Class #3 - Events & Functions

## Overview
- **Channel**: Ask A Dev
- **Duration**: 37:16
- **Focus**: Events and Functions in Unreal Engine Blueprints — creation, usage, and fundamental differences

## Events in Blueprints

### What are Events?
- **Predefined events** (Begin Play, Tick, Destroyed) are provided by Unreal Engine
- **Custom events** can be created for reusable logic chunks
- Events are **called** and executed when triggered

### Creating Custom Events
1. Right-click in Event Graph → **Add Event** → **Custom Event**
2. Name it descriptively (e.g., `Event_DoStuff`, `Event_AnimateHouse`)
3. Add logic by connecting execution pins

### Benefits of Events:
- **Reusability** of logic chunks
- **Organization** of complex blueprints
- **Control flow** management

## Functions in Blueprints

### What are Functions?
- Defined in **My Blueprint** panel under **Functions**
- Can have **inputs** and **outputs**
- Support **local variables** (accessible only within the function)

### Creating Functions:
1. Click **+** next to Functions in My Blueprint panel
2. Name the function
3. Add logic nodes
4. Connect to execution pins

### Function Features:
- **Input Parameters**: Give information to functions
- **Output Parameters**: Get results back from functions
- **Local Variables**: Variables only accessible within the function

## Events vs. Functions: Key Differences

| **Aspect** | **Events** | **Functions** |
|------------|------------|---------------|
| **Return Values** | ❌ Cannot return values | ✅ Can have return values |
| **Time-Based Nodes** | ✅ Can use delays, timelines | ❌ Cannot use delays/timelines |
| **Asynchronous** | ✅ Start time known, end unknown | ❌ Synchronous execution |
| **Replication** | ✅ Can be replicated (multiplayer) | ❌ Not replicated |
| **Creation Location** | Event Graph | My Blueprint Panel |
| **Local Variables** | ❌ No | ✅ Yes |

## Practical Example: House Blueprint
```blueprint
Begin Play Flow:
1. Call Event_DoStuff
2. Print "Returning to original begin play"
3. Call Event_ConstructHouse (builds house meshes)
4. Call Event_AnimateHouse (scales house with delays)
```

## When to Use Events:
- When you need **asynchronous** execution
- When you need **time-based** operations (delays, timelines)
- For **organizing** and **reusing** blueprint sections
- When you need **replication** (multiplayer scenarios)

## When to Use Functions:
- When you need **return values** or **outputs**
- For **calculations** or **pure logic** that doesn't involve time
- When you want **local variables** to keep blueprints clean
- For **reusable utility logic**

---

## Related

- ← Previous: [[BP_Class_2_Variables]]
- → Next: [[BP_Class_3_Events_and_Functions]]
- 📚 Series: [[_MOC_Blueprint_Fundamentals]]
