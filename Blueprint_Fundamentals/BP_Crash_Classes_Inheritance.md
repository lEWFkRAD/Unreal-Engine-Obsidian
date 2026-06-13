---
title: "Unreal Blueprints Crash Course for Creatives: Learn Classes, Inheritance & Blueprint Relationships!"
source: "https://www.youtube.com/watch?v=w9d2aVRjBrU"
video_id: "w9d2aVRjBrU"
type: "youtube-summary"
series: "Blueprint Fundamentals"
episode: 0
tags: [ue5, tutorial, blueprint, fundamentals, gamedev, visual-scripting]
---

# Unreal Blueprints Crash Course Summary: Classes, Inheritance & Relationships

## Overview
Practical tutorial using a **weapon system** as a framework to learn foundational Blueprint concepts: classes, inheritance, child blueprints, casting, and multi-actor control patterns.

> "I'm going to teach you how to sort of be a hacker... giving you some foundational pieces that you can use as guideposts."

## 1. Blueprint Classification & The Actor
*   **Class = Classification:** When creating a Blueprint, you must define its type (e.g., Actor, Player Controller, AI).
*   **Tutorial Choice:** An `Actor` class was selected as the base for the weapon system.

## 2. Building the Parent: Weapon Actor
1.  **Visual Element:** Added a `Static Mesh` component (sword mesh) under the `DefaultSceneRoot`.
2.  **Event Graph Basics:**
    *   **`Begin Play`:** Executes when the actor is spawned/level starts.
    *   Used `Print String` for debugging/tracing execution flow.
3.  **Custom Events & Logic:**
    *   Created `Event Show Weapon Actor` and `Event Hide Weapon Actor` for reusable functionality.
    *   Used `Set Visibility` on the static mesh component.
    *   Implemented `Delay` nodes to sequence actions.
4.  **Variables (Data Buckets):**
    *   Created a `Float` variable named `Attack Range` (default: 100.0). Accessed with **Get** nodes.

## 3. Inheritance: Child Blueprints
> "The child inherits everything that the parent has... what we do to the child does not go back up to the parent."

*   **Creating a Child:** Right-click a parent Blueprint -> `Create Child Blueprint Class`.
*   **Inheritance Behavior:**
    *   Child **automatically inherits** all components, variables, and events from the parent.
    *   Child **does not** inherit changes made *to* other children.
    *   Parent **does not** inherit new variables/events created in children.
*   **Overriding:**
    *   **Visuals:** Can change the `Static Mesh` in the child (e.g., katana vs. greatsword).
    *   **Variables:** Can override default values (e.g., set `Attack Range` to 75 in a child).
    *   **Events:** Can override events like `Begin Play`. Crucially, must use **`Add Call to Parent Function`** within the child's event to also run the parent's logic.

## 4. Advanced Patterns: Ranged Weapon & Weapon Controller
*   **Creating Specialized Children:** Made `Ranged Child` blueprint inheriting from `Weapon Actor`.
*   **Adding Child-Specific Data:** Created an `Integer` variable `Number of Bullets` (default: 8) only in the `Ranged Child`.

### Weapon Controller Pattern
*   **Purpose:** To control multiple weapons from a central point (e.g., a player character).
*   **Implementation:**
    1.  Use `Get All Actors Of Class` targeting the `Weapon Actor` class.
    2.  Loop through the returned array using `For Each Loop`.
    3.  Perform actions (e.g., call `Hide Weapon Actor` event) on each weapon.
*   **Conditional Logic:** Use `Branch` nodes with variable checks (e.g., `Is Melee`) to affect specific weapons.

## 5. Casting: Accessing Child-Specific Data
> "Casting... forces Unreal to understand that this can be considered a ranged child."

*   **Problem:** A list of `Weapon Actor` (parent) references **cannot** access `Number of Bullets` (child variable).
*   **Solution: Casting**
    1.  **`Cast To` Node:** Attempts to convert a parent reference into a specific child type.
    2.  **Success:** If the actor is of that child type (or inherits from it), you gain access to its unique variables/events.
    3.  **Failure:** Use the **Fail** pin for fallback logic (e.g., access parent variables like `Attack Range`).

### Critical Troubleshooting Tip
**If child blueprints don't show inherited variables:**
> In the **Variables** panel, click the **cog wheel (settings)** and ensure **"Show Inherited Variables"** is checked.

## Blueprint Architecture Summary
```
Weapon Actor (Parent)
├── Variables: Attack Range (Float), Is Melee (Bool)
├── Events: Begin Play, Show/Hide Weapon Actor
├── Children:
│   ├── Great Sword Child (Override: Static Mesh, Is Melee)
│   ├── Katana Child (Override: Static Mesh, Attack Range, Begin Play)
│   └── Ranged Child
│       ├── Variables: Number of Bullets (Integer)  -- CHILD ONLY
│       └── Events: Check Num Bullets  -- CHILD ONLY
└── Controlled by: Weapon Controller Actor
```

---

## Related

- ← Previous: [[BP_Class_6-5_UI_Reusable_Widgets]]
- → Next: [[BP_Interface_Demystified]]
- 📚 Series: [[_MOC_Blueprint_Fundamentals]]
