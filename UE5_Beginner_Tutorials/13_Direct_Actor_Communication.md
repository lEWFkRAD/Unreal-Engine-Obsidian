---
title: "Learn to Code in UE5 - 13 - Direct Actor Communication"
source: "https://www.youtube.com/watch?v=0IOGiyeXP5Y"
video_id: "0IOGiyeXP5Y"
type: "youtube-summary"
series: "UE5 Beginner Tutorials"
episode: 13
tags: [ue5, tutorial, blueprint, gamedev, coding, beginner]
---

# Learn to Code in UE5 - 13 - Direct Actor Communication

## Key Concepts
**Actor Communication** refers to the ability of one actor instance to share information with other actors in a level. There are four main methods:
1. Direct Communication
2. Casting
3. Interfaces
4. Event Dispatchers (covered in future lessons)

## Direct Communication
The simplest and most common method. Uses a **reference** to the target actor to:
- Get/set the target actor's variables
- Call functions or custom events on the target actor

### Class Hierarchy & References
> When you create a reference to a blueprint instance, the reference can be used for the blueprint class but also for all its children.

**Important Insight:** A reference to a parent class can access all child instances, but a reference to a child class **cannot** access parent or sibling instances.

## Practical Implementation Examples

### 1. Creating Class Hierarchy
**Parent Blueprint:** `BP_PlatformBase`
- Contains shared variables (e.g., `Active` boolean)
- Contains custom events (e.g., `EV_Activate`)

**Child Blueprints:** `BP_PlatformA` and `BP_PlatformB`
- Inherit from `BP_PlatformBase`
- Override `EV_Activate` with platform-specific logic

### 2. Activation Blueprint with Single Reference
**`BP_Activation`** actor that activates platforms on player overlap.

**Key Steps:**
1. Create a variable of type `BP_PlatformBase` object reference
2. Make the variable **public** (editable in level)
3. Use overlap event to call `EV_Activate` on the referenced platform

### 3. Using Arrays to Activate Multiple Platforms
Convert single reference to an **array** to activate multiple platforms simultaneously.

**Performance Note:** Use `Get All Actors of Class` cautiously as it's expensive. Prefer pre-populating arrays in `BeginPlay`.

### 4. Filtering with Actor Tags
**Actor Tags** allow selective activation without manual array setup.

**Implementation:**
1. Add tags to actors in the level (e.g., "Room1", "Room2")
2. In the activation blueprint, check `Has Tag` before activating

### 5. Casting for Type-Specific Communication
**Casting** converts a reference to a different class to access class-specific functionality.

**Key Insight:** Casting validates the actor's class before allowing access to its data.

**Practical Tip:** Always use casting when you need to verify the actor type or access class-specific properties.

## Recap & Key Takeaways
1. **Direct Communication** uses references to access target actor properties and functions
2. **Class Hierarchy Matters:** Parent references work for all children; child references do not
3. **Efficient Patterns:**
   - Use **public variables** for level editor configuration
   - Use **arrays** to handle multiple actors
   - Use **actor tags** for selective filtering
   - Use **Get All Actors of Class** sparingly (performance impact)
4. **Casting** enables type-safe communication and class-specific data access
5. **Practical Insight:** Combine casting with direct communication for robust, type-checked interactions

**Challenge Exercise:** Think of three examples where you would use casting in your own projects.

---

## Related

- ← Previous: [[12_Collisions_and_Overlaps]]
- → Next: [[14_Interfaces]]
- 📚 Series: [[_MOC_UE5_Beginner_Tutorials]]
