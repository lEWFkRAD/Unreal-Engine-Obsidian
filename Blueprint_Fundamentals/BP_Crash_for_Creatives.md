---
title: "Unreal Blueprints Crash Course for Creatives: Learn Classes, Inheritance & Blueprint Relationships!"
source: "https://www.youtube.com/watch?v=w9d2aVRjBrU"
video_id: "w9d2aVRjBrU"
type: "youtube-summary"
series: "Blueprint Fundamentals"
episode: 0
tags: [ue5, tutorial, blueprint, fundamentals, gamedev, visual-scripting]
---

# Unreal Blueprints Crash Course: Classes, Inheritance & Relationships

## Overview
- **Channel**: Ask A Dev
- **Duration**: 1:01:04
- **Focus**: Creating a weapon actor system to demonstrate core blueprint concepts
- **Philosophy**: Learn by doing, making intentional mistakes to understand why certain approaches are better

## Key Foundational Concepts

### 1. Classes as Classifications
> "Think of class as short for **classification**. When we create a blueprint, we have to give it a classification... is it an actor? A weapon? A player controller?"

### 2. Variables as Buckets
> "A variable... think of a variable as a **bucket that you can store a value in**."

### 3. Visual Scripting Flow
Logic can be understood by reading nodes aloud: "Begin Play, print string, delay for 2 seconds, hide the sword."

## Step-by-Step Weapon Actor Creation

### 1. Initial Setup
- Create Blueprint Class → Actor → `Weapon Actor`
- Add Static Mesh Component (e.g., a sword)

### 2. Events & Variables
- **Begin Play**: Runs when level starts
- **Custom Events**: `Event Show Weapon Actor`, `Event Hide Weapon Actor`
- **Variables**: `Attack Range` (Float, default 100)

### 3. The Problem with Duplication
Duplicating blueprints means changes to the parent **do not propagate** to duplicates.

## Core Concept: Parent-Child Inheritance

### Creating Children
- Right-click parent → **Create Child Blueprint Class**
- Children **inherit all variables, events, and components** from parent
- Changes to parent propagate to children; changes to children do NOT go back to parent

### Overriding in Children
- Override **visuals** (mesh), **variables** (default values), and **events**
- **Critical**: If you override an event and don't call the parent function, the parent's code won't execute
- **Solution**: Right-click → `Add Call to Parent Function`

## Advanced: Casting

### The Problem
When iterating over parent class, you **cannot access child-specific variables**.

### The Solution: Casting
- Use `Cast To` node (e.g., `Cast To Ranged Child`) to convert parent reference to child type
- **Success Path**: Access child-specific variables
- **Failure Path**: Fall back to parent variables

### Analogy
> "Casting asks, 'Can this weapon be understood as a ranged child?'"

## Final Blueprint Structure
- **Weapon Actor** (Parent): Base features (Show/Hide, Attack Range)
- **Great Sword** (Child): Melee weapon, overrides mesh, `Is Melee = true`
- **Katana** (Child): Melee weapon, overrides mesh and `Attack Range`
- **Ranged Child**: Adds `Number Of Bullets` variable, `Event Check Num Bullets`

## Key Takeaways
1. Use inheritance instead of duplication
2. Always call parent function when overriding events
3. Casting enables access to child-specific features
4. `Get All Actors Of Class` finds all instances of a class and its children

---

## Related

- ← Previous: [[BP_Crash_Classes_Inheritance]]
- → Next: [[BP_Interface_Demystified]]
- 📚 Series: [[_MOC_Blueprint_Fundamentals]]
