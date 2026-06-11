---
title: "UE Blueprint Fundamentals | Class #4 | Branches & Booleans"
source: "https://www.youtube.com/watch?v=1UzBq36_54c"
video_id: "1UzBq36_54c"
type: "youtube-summary"
series: "Blueprint Fundamentals"
episode: 4
tags: [ue5, tutorial, blueprint, fundamentals, gamedev, visual-scripting]
---

# UE Blueprint Fundamentals: Branches & Booleans

## Overview
- **Channel**: Ask A Dev
- **Duration**: 27:53
- **Focus**: Decision-making logic in UE Blueprints — Branch statements and Boolean operations

## Branch Statements
The visual scripting equivalent of `if` statements in traditional programming.

### How Branches Work:
- A **Boolean condition** connects to a **Branch node**
- Branch has two execution pins: **True** and **False**
- Different code paths execute depending on the condition

## Boolean Logic

### Boolean Variables
- Store `True` or `False` values
- Use cases: `IsJumping`, `IsDying`, `OutOfAmmo`, `HasKey`

### Boolean Operations

#### AND Operator
- Both conditions must be true
- Example: `HasAmmo AND IsAlive` → Can shoot

#### OR Operator
- At least one condition must be true
- Example: `HasKey OR HasLockpick` → Can open door

#### NOT Operator
- Inverts a Boolean value
- Example: `NOT IsDead` → Character is alive

### Combining Operations
Multiple Boolean conditions can be combined for complex decision-making:
```blueprint
(HasAmmo AND IsAlive) AND NOT IsReloading → CanShoot
```

## Practical Applications
- **Character behavior**: Decide whether to attack, run, or pick up health
- **Game state**: Check multiple conditions before allowing actions
- **UI logic**: Show/hide elements based on game state

## Common Pitfalls
1. Forgetting to connect both True and False paths
2. Not accounting for all possible states
3. Over-complicating Boolean expressions when simpler logic would work

## Key Takeaways
- Branches are the fundamental decision-making tool in Blueprints
- Boolean logic (AND, OR, NOT) forms the basis of all game logic
- Combining conditions creates complex, realistic character behavior

---

## Related

- ← Previous: [[BP_Class_3_Events_and_Functions]]
- → Next: [[BP_Class_4_Branches_and_Booleans]]
- 📚 Series: [[_MOC_Blueprint_Fundamentals]]
