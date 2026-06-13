---
title: "UE Blueprint Fundamentals | Class #3 | Events & Functions"
source: "https://www.youtube.com/watch?v=Wc9pdjJysi4"
video_id: "Wc9pdjJysi4"
type: "youtube-summary"
series: "Blueprint Fundamentals"
episode: 3
tags: [ue5, tutorial, blueprint, fundamentals, gamedev, visual-scripting]
---

# UE Blueprint Fundamentals: Events & Functions Summary

## Core Concepts
*   **Purpose:** Events and functions are mechanisms to **reuse and organize chunks of Blueprint logic**, preventing clutter and duplication.
*   **Key Benefit:** They allow you to call complex sequences of nodes from a single point, making Blueprints cleaner and more manageable.

## Custom Events
*   **Creation & Use:**
    1.  Right-click in the **Event Graph** -> **Add Event** -> **Custom Event**.
    2.  Name it descriptively (e.g., `Event_DoStuff`).
    3.  Connect the execution logic after the event node.
    4.  To call it: Right-click -> **Add Event** -> select your custom event. This spawns a **blue call node**.
*   **Execution Flow:**
    *   When called, execution enters the custom event, runs its logic, then **returns to the point in the original graph where it was called**.
    *   Example:
        ```
        Begin Play -> Event_DoStuff -> Print String: "Returning to original begin play"
        Event_DoStuff: -> Print String: "Doing stuff"
        ```
        *Output: "Doing stuff" then "Returning to original begin play".*

### Practical Example: House Animation
*   **Organization:** Used custom events to split house construction logic:
    *   `Event_ConstructHouse`: Builds static meshes (walls, roof).
    *   `Event_AnimateHouse`: Handles scaling/delay logic.
    *   **Begin Play** calls `Event_ConstructHouse`, then `Event_AnimateHouse`.

## Functions
*   **Creation & Use:**
    1.  In the **My Blueprint** panel, under **Functions**, click the **+**.
    2.  Name the function (e.g., `AddTwoNumbers`).
    3.  Define its logic in the new graph window.
    4.  To call it: Drag from an execution pin and select the function, or right-click and search for "call function". This spawns a **purple call node**.
*   **Inputs (Arguments):**
    *   Define parameters the function needs to work. In the function's **Details** panel, under **Inputs**, click **+**.
    *   Each input becomes an entry pin on the purple call node and the function's entry node.
    *   Example: For `AddTwoNumbers`, create inputs `FirstNumber` and `SecondNumber` (both `float`).
*   **Outputs (Return Values):**
    *   Define data the function sends back. In the **Details** panel, under **Outputs**, click **+**.
    *   Use a **Return Node** inside the function to set the output value.
    *   The output becomes an exit pin on the purple call node, usable for subsequent logic.
    *   Example: For `AddTwoNumbers`, create output `FinalNumber`. Connect the addition result to the `ReturnNode`.
*   **Local Variables:**
    *   Functions can have variables **only accessible within that function**.
    *   Found in the **Details** panel under **Local Variables**.
    *   Useful for temporary calculations without cluttering the main Blueprint's variables.

### Practical Example: Add Two Numbers
```
Begin Play -> AddTwoNumbers(FirstNumber: 10, SecondNumber: 11) -> Print String (FinalNumber)
```
*Output: "21.0".*

## Key Differences: Events vs. Functions

| Feature | Events (Red Nodes) | Functions (Purple Nodes) |
| :--- | :--- | :--- |
| **Input Parameters** | Yes | Yes |
| **Output/Return Values** | No | Yes |
| **Use Time Nodes (Delay, Timelines)** | Yes | No |
| **Asynchronous** | Yes (Can run in background) | No (Synchronous, runs to completion) |
| **Replication (Multiplayer)** | Yes (Only events can be replicated) | No |
| **Local Variables** | No | Yes |
| **Primary Use Case** | **Triggering** sequences, reacting to game occurrences (BeginPlay, input, collisions). | **Performing calculations**, reusable logic that returns a result. |

## Important Takeaways
1.  **Reusability:** Both allow packaging logic for reuse, preventing duplication and enabling cleaner Blueprints.
2.  **Organization:** Break down complex graphs (like the house animation) into manageable, named chunks.
3.  **Custom Events:** Best for **"do this"** actions, especially those needing delays or replication.
4.  **Functions:** Best for **"calculate this"** tasks that should return a value (e.g., `GetDamage`, `CalculateDistance`).
5.  **Flow:** After calling either an event or function, execution returns to the point in the graph where the call was made.

---

## Related

← Previous: [[BP_Class_2_Variables]]
→ Next: [[BP_Class_4_Branches_and_Booleans]]
- 📚 Series: [[_MOC_Blueprint_Fundamentals]]
