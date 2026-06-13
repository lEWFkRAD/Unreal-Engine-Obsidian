---
title: "UE Blueprint Fundamentals | Class #4 | Branches & Booleans"
source: "https://www.youtube.com/watch?v=1UzBq36_54c"
video_id: "1UzBq36_54c"
type: "youtube-summary"
series: "Blueprint Fundamentals"
episode: 4
tags: [ue5, tutorial, blueprint, fundamentals, gamedev, visual-scripting]
---

# UE Blueprint Fundamentals | Class #4: Branches & Booleans

## Overview
This class covers the foundational visual scripting concepts of **Branches** (the Blueprint equivalent of "if" statements) and **Boolean logic** (AND, OR, NOT). These tools enable decision-making in game logic, such as whether a character can attack, run, or pick up an item.

## Branches: The "If" Statement
A **Branch** is the primary control flow node that executes different paths based on whether a condition is **true** or **false**.

### Anatomy of a Branch Node
*   **Condition Input:** A boolean value (`true`/`false`).
*   **True Output (white):** Executes if the condition is `true`.
*   **False Output (white):** Executes if the condition is `false`.

### Creating a Branch
*   **Method 1:** Right-click, search `Branch`.
*   **Method 2 (Hotkey):** Hold the `B` key and left-click in the graph.

### Using Branches with Conditions
Branches become powerful when connected to **comparison nodes** (e.g., `Greater Than`).

```
// Conceptual flow: Check if ammo > 0.
Branch Condition: (Ammo > 0) → True: "Fire Weapon" | False: "Reload"
```

### Connecting Booleans Directly
You can connect a **Boolean variable** directly to a Branch's condition.
> **Example:** Using a `Is In Air` boolean to prevent double-jumping if the character is already airborne.

## Boolean Addendum & Logic
**Booleans** are variables that can only be `true` or `false`. Boolean **operators** allow you to combine multiple conditions.

### Key Operators
1.  **AND:** `true` **only if all** connected inputs are `true`.
    *   *Use Case:* "Can the enemy attack?" Requires: `Is Healthy` AND `Has Weapon` AND `Has Ammo`.
2.  **OR:** `true` **if any** connected input is `true`.
    *   *Use Case:* "Can the enemy attack?" Requires: `Is Healthy` OR `Has Weapon`.
3.  **NOT:** **Inverts** the incoming boolean value (`true` → `false`, `false` → `true`).
    *   *Use Case:* "If the character is NOT wounded, then attack."

### Finding Boolean Operators
Located in **Math → Boolean Math**.

### Best Practices for Readability
*   **Name variables clearly:** Use prefixes like `Is`, `Has`, `Can` (e.g., `Is Grounded`, `Has Weapon`). This makes logic easier to follow.
*   **Prefer connecting to True paths:** It's often cleaner to structure logic so you connect to the Branch's **True** pin. Use the **NOT** operator to flip a condition if needed.

> **Instructor's Tip:** "Don't be surprised if you have to write down the different options... especially if you have more than one thing." Complex boolean logic (combining AND, OR, NOT) can be mentally challenging—plan it out.

## Common Pitfalls & Wrap-Up
*   **Overcomplicating Logic:** Combining many boolean operations can become confusing. Keep variable names explicit.
*   **Branch vs. If Statement:** In traditional programming, this is an `if/else` statement. In Blueprints, it's a **Branch** node.
*   **Core Concept:** Branches allow your scripts to **make decisions** based on the state of your game (variables, world conditions).

**Final Takeaway:** Mastering Branches and Boolean logic is essential for creating dynamic, responsive game mechanics in Unreal Engine Blueprints.

---

## Related

- ← Previous: [[BP_Class_3_Events_and_Functions]]
- → Next: [[BP_Class_5-1_Loops_Arrays_Applied_1]]
- 📚 Series: [[_MOC_Blueprint_Fundamentals]]
