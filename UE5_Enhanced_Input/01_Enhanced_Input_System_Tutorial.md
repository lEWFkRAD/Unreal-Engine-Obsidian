---
title: "Enhanced Input System Tutorial - Unreal Engine 5"
source: "https://www.youtube.com/watch?v=YFEqdi-9mD8"
video_id: "YFEqdi-9mD8"
type: "youtube-summary"
series: "UE5 Enhanced Input"
episode: 1
tags: [ue5, enhanced-input, input-system, blueprint]
---

# Enhanced Input System Tutorial - Unreal Engine 5

**Duration:** 29:57 | **Source:** YouTube

## Overview

This tutorial covers the fundamentals of UE5's Enhanced Input System, which replaced the legacy Action/Axis Mapping system. Enhanced Input provides a flexible, asset-driven approach to handling player input with support for complex input processing, runtime remapping, and contextual input states.

## Core Concepts

### 1. Input Actions (IA)

Input Actions are data assets that represent a single player capability (e.g., "Jump", "Fire", "Move"). Each action has a value type:

- **Bool** — Simple on/off (e.g., "Pick up item")
- **Axis1D (Float)** — Single-axis value
- **Axis2D (FVector2D)** — Two-axis (e.g., gamepad thumbstick)
- **Axis3D (FVector)** — Three-axis (e.g., motion controller)

**How to create:**
1. Content Browser → Right-click → Input → Input Action
2. Name it `IA_Move`, `IA_Jump`, `IA_Look`, etc.
3. Set the **Value Type** (Bool for buttons, Axis2D for movement sticks)

### 2. Input Mapping Contexts (IMC)

Mapping Contexts are collections of Input Actions that define which physical keys trigger which actions. You can have multiple contexts and swap them at runtime.

**How to create:**
1. Content Browser → Right-click → Input → Input Mapping Context
2. Name it `IMC_Default` (or similar)
3. Open it and add your Input Actions
4. For each action, map physical keys (e.g., W/A/S/D → IA_Move)
5. Optionally add **Modifiers** and **Triggers** per key mapping

**Key feature:** Different CTRL key actions depending on context — crouch when walking, slide when sprinting, stand when prone.

### 3. Input Modifiers

Pre-processors that alter raw input values before they reach triggers. Common uses:

- **Dead Zone** — Ignore small input values
- **Negate** — Invert an axis
- **Swizzle** — Remap axes (e.g., Y→X for WASD)
- **Scalar** — Multiply input by a factor

**WASD Mapping Example with Modifiers:**

| Key | Action | Modifiers |
|-----|--------|-----------|
| W | Positive Y | Swizzle (YXZ) |
| A | Negative X | Negate |
| S | Negative Y | Negate + Swizzle |
| D | Positive X | None |

### 4. Input Triggers

Determine when processed input activates an action:

- **Down** — Active while held
- **Pressed** — Fires once on press
- **Released** — Fires once on release
- **Hold** — Fires after holding for a duration
- **Combo** — Fires on key combinations

## Implementation Steps

### Step 1: Enable Enhanced Input Plugin
- Edit → Plugins → Search "Enhanced Input" → Enable (usually enabled by default in UE5)

### Step 2: Create Input Actions
```
Content Browser → Add → Input → Input Action
Create: IA_Move (Axis2D), IA_Look (Axis2D), IA_Jump (Bool), IA_Fire (Bool)
```

### Step 3: Create Input Mapping Context
```
Content Browser → Add → Input → Input Mapping Context
Open IMC_Default:
  - IA_Move → W/A/S/D keys (with Swizzle/Negate modifiers for 2D)
  - IA_Look → Mouse XY 2D-Axis
  - IA_Jump → Space Bar
  - IA_Fire → Left Mouse Button
```

### Step 4: Add Mapping Context to Character
In your Character Blueprint's BeginPlay:
```
Get Player Controller → Get Enhanced Input Local Player Subsystem → Add Mapping Context
  - Mapping Context: IMC_Default
  - Priority: 0
```

### Step 5: Bind Input Actions
In the Character Blueprint Event Graph:
- Right-click → type the action name (e.g., "IA_Jump")
- Choose "Enhanced Input Action IA_Jump"
- Select event type (Triggered, Completed, etc.)
- Connect to your gameplay logic

### C++ Binding Example
```cpp
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    Input->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &AMyCharacter::Jump);
    Input->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &AMyCharacter::Fire);
}
```

## Debug Commands

- `showdebug enhancedinput` — Display active input action mappings
- `showdebug devices` — Show connected input devices

## Key Takeaways

1. Enhanced Input is **asset-based** — clean separation of input logic from code
2. **Mapping Contexts** can be swapped at runtime for different gameplay states
3. **Prioritization** prevents input collisions when multiple contexts are active
4. **Modifiers and Triggers** provide powerful input processing without custom code
5. Backward compatible with UE4's input system


---

## Related

- → Next: [[02_Enhanced_Input_Masterclass]]
- 📚 Series: [[_MOC_UE5_Enhanced_Input]]
