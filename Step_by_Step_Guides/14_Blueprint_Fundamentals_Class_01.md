---
title: "Blueprint Fundamentals — Class #1"
source: "https://www.youtube.com/watch?v=IipvT6aGinM"
video_id: "IipvT6aGinM"
type: "step-by-step-guide"
series: "Step-by-Step Guides"
episode: 14
tags: [ue5, blueprint, fundamentals, visual-scripting, guide]
---

# Unreal Engine Blueprint Fundamentals — Class #1

**Source:** https://www.youtube.com/watch?v=IipvT6aGinM
**Instructor:** Kevin (Tech Artist at Riot Games, 20+ years teaching scripting)
**Extracted from:** `Unreal_Engine_Blueprint_Fundamentals___Class_#1.md`

---

## Overview

This is a crash course in visual scripting for complete beginners — no programming background required. It covers the fundamental concepts of Blueprints in Unreal Engine 5.

---

## Core Concepts

### What is a Blueprint?
- An object in Unreal Engine that **does something** in the world
- A container for visual scripting logic
- Not the same as a coding blueprint/design doc — in UE, "Blueprint" = visual script

### What is Visual Scripting?
- A way to create logic using **nodes** (boxes) instead of text code
- Developers have pre-built programmer-friendly workflows into visual, artist-friendly nodes
- Easier than text coding, but still requires understanding of logic and flow

---

## Key Terminology

### Nodes
- The **boxes** in the visual scripting graph
- Different types: Events, Functions, Variables, Flow Control
- Named descriptively so you can guess their purpose

### Events
- Nodes that **fire when something happens**
- Examples:
  - **Begin Play** — fires when the game/experience starts
  - **Event Tick** — fires every frame (the "clock is ticking")
  - **Actor Begin Overlap** — fires when something overlaps the actor

### Execution Pins (White Triangles)
- The **white triangle pins** on the bottom/top of nodes
- Determine the **order of operations** — flow goes left to right
- Drag from one to another to connect the execution flow

### Data Pins (Colored Circles)
- The **colored pins** on the sides of nodes
- Carry **data** (numbers, text, objects) between nodes
- Colors indicate data type:
  - **Blue** = Boolean (true/false)
  - **Green** = Float (decimal number)
  - **Integer** = Whole number
  - **String** = Text
  - **Object reference** = Reference to another object

### Functions/Commands
- Nodes that **do something** (actions)
- Examples: Print String, Spawn Emitter, Set Location, Delay

---

## Step-by-Step: Your First Blueprint

### Step 1: Create a Project
1. Open UE5 → select **Third Person** template.
2. Name it (e.g., `Visual_Scripting_Intro`).
3. Create the project.

### Step 2: Create a Blueprint Class
1. In the Content Browser, create a folder: `Visual_Scripting`.
2. Right-click in the folder → **Blueprint Class** → select **Actor**.
3. Name it (e.g., `BP_ClassOne`).
4. Double-click to open the Blueprint Editor.

### Step 3: Understand the Interface
- **Top:** Viewport (3D preview)
- **Right:** Outliner (list of components)
- **Bottom:** Content Browser (file system)
- **Center:** Event Graph (where you write visual scripts)

### Step 4: Your First Script — Print String
1. In the Event Graph, find **Event Begin Play** (auto-created).
2. Drag from the **execution pin** (white triangle) → search for **Print String**.
3. In the Print String node, type `Hello` in the string field.
4. Click **Compile** (top toolbar) — green checkmark = success.
5. **Save** the Blueprint.

### Step 5: Place the Blueprint in the Level
1. Drag the Blueprint from Content Browser into the level.
2. Press **Play** → "Hello" appears on screen.
3. Press **Shift+Escape** or click the red square to stop.

> **Key lesson:** The Blueprint must exist in the level for its events to fire. Creating a Blueprint doesn't automatically add it to the game.

---

## Working with Nodes

### Creating Nodes
- **Drag from a pin** → search menu appears
- **Right-click** in empty space → search for a node
- **Hotkeys:** Type the node name while selected

### Connecting Nodes
- **Execution flow:** Connect white triangle pins left-to-right
- **Data flow:** Connect colored pins to pass values between nodes
- **One output → Many inputs:** A single output pin can connect to multiple input pins

### Copy/Paste
- Select a node → `Ctrl+C` → `Ctrl+V` to duplicate
- Preserves node settings and connections

### Compiling
- **Must compile** after every change (green button or Ctrl+Alt+F7)
- Green checkmark = no errors
- Red circle with number = errors to fix
- UE highlights the problematic node and shows the error message on hover

---

## Step-by-Step: Debug Visualization

### Step 6: Draw Debug Shapes
1. From Begin Play → add **Draw Debug Sphere**:
   - Location: `(0, 0, 100)`
   - Color: Red
   - Duration: 10 seconds
2. Compile → Play → red sphere appears in the world.

### Step 7: Chain Multiple Actions
1. After the debug sphere, add **Draw Debug Cylinder**:
   - Same location
   - Different color
2. Compile → Play → both shapes appear sequentially.

### Step 8: Spawn a Particle Emitter
1. After the cylinder, add **Spawn Emitter at Location**:
   - Emitter Template: `TutorialParticleSystem`
   - Location: same as debug shapes
2. Compile → Play → particle effect spawns.

---

## Working with Data

### Step 9: Move the Emitter with World Offset
1. From the Spawn Emitter's **Return Value** → add **Add World Offset**:
   - Offset: `(0, 200, 0)` (2 meters on Y axis)
   - This uses the **data pin** (return value) to reference the spawned emitter.
2. Compile → Play → emitter spawns and immediately moves.

### Step 10: Add a Delay
1. Insert a **Delay** node before the World Offset:
   - Duration: `2` seconds
2. Compile → Play → emitter spawns, waits 2 seconds, then moves.

### Step 11: Chain Multiple Moves
1. Copy the Delay + World Offset nodes → paste after the first move.
2. Change the offset values for the second move.
3. Connect the **Return Value** from the first emitter to the second World Offset's Target pin.
4. Compile → Play → emitter moves twice with delays.

> **Key lesson:** The Return Value pin carries the reference to the spawned object. Multiple nodes can use the same return value as their target.

---

## Error Debugging

### Common Errors
- **"Target must have a connection"** — A node expecting an object reference doesn't have one connected.
- **Red circle on compile** — Fix the highlighted node before testing.
- **Nothing happens on Play** — Blueprint not placed in the level, or logic not connected.

### Reading Error Messages
- Hover over the red error indicator on the node
- The message tells you exactly what's wrong
- Focus on: "must have", "expected", "not connected"

---

## Clean Code Practices

### Layout
- Keep nodes flowing **left to right** (execution order)
- Avoid crossing wires — rearrange nodes to keep flow clear
- Use **Reroute Nodes** (double-click on a wire) to route connections cleanly

### Comments
- Select nodes → press **C** to create a comment box
- Name things descriptively
- Use comment colors to organize sections

### Naming
- Variables: descriptive names (e.g., `CurrentHealth`, not `CH`)
- Blueprints: prefix with type (`BP_`, `WB_`, `ABP_`)

---

## Quick Reference — Blueprint Editor Shortcuts

| Action | Shortcut |
|--------|----------|
| Compile | Toolbar button or Ctrl+Alt+F7 |
| Save | Ctrl+S |
| Play | Green button in viewport |
| Stop | Shift+Escape |
| Copy node | Ctrl+C |
| Paste node | Ctrl+V |
| Create comment | C (with nodes selected) |
| Reroute wire | Double-click on wire |
| Search for node | Right-click in graph |
| Delete node | Delete key |

---

## Pro Tips

- **Always compile after changes.** Unreal won't tell you about errors until you compile.
- **Always save after compiling.** Compile validates the logic; save persists it.
- **Start simple.** Print String → Debug Shapes → Spawn Objects → Move Objects.
- **Execution flow goes left to right.** If you can't follow your own graph, rearrange it.
- **Data pins (colored) carry values.** Execution pins (white) determine order. Don't mix them up.
- **One output can connect to many inputs.** A single Return Value can feed multiple operations.
- **Error messages are your friend.** Read them — they usually tell you exactly what's wrong.
- **Clean layout matters.** Your future self (and teammates) will thank you for organized graphs.

---

## Related

- ← Previous: [[13_RPG_Tutorial_10_Sword_Trace_Damage]]
- 📚 Series: [[_MOC_Step_by_Step_Guides]]
