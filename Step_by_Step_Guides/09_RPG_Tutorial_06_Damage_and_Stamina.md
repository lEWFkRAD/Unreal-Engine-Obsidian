---
title: "RPG Tutorial #6: Damage and Stamina"
source: "https://www.youtube.com/watch?v=7P4U5wmONKI"
video_id: "7P4U5wmONKI"
type: "step-by-step-guide"
series: "Step-by-Step Guides"
episode: 9
tags: [ue5, rpg, damage, stamina, combat, guide]
---

# Unreal Engine 5 RPG Tutorial Series — #6: Damage and Stamina

**Source:** https://www.youtube.com/watch?v=7P4U5wmONKI
**Duration:** 22:09
**Extracted from:** `Unreal_Engine_5_RPG_Tutorial_Series_-_#6_Damage_and_Stamina.md`

---

## Prerequisites

- Completed Episode #5 (Player Stats)
- `BPC_PlayerStats` component with health/stamina functions
- `WGWB_MainHUD` widget with health/stamina bars

---

## Part 1: Fix Bugs from Episode #5

### Step 1: Fix HUD Initialization Error
The HUD variable isn't assigned when `BPC_PlayerStats` BeginPlay tries to access it.
1. In `BPC_PlayerStats` → Event Graph → BeginPlay:
   - Add a **Delay Until Next Tick** node before any HUD access.
   - This waits one frame so the player's HUD widget is created first.

### Step 2: Fix Negative Health Bug
The player could take damage after already being dead (health goes negative).
1. In `DecreaseHealth` function:
   - Before subtracting damage, add a **Branch**:
     - Condition: `CurrentHealth > 0` (player is still alive) — use a **NOT** gate
     - If **false** (already dead): Skip damage, return `IsPlayerDead = true`
     - If **true** (alive): Apply damage as normal
   - Keep the existing `CurrentHealth <= 0` check after subtraction as well.
2. Copy the same fix to `DecreaseStamina` — check `CurrentStamina > 0` before subtracting.

### Step 3: Fix DecreaseStamina Variable Bug
The `DecreaseStamina` function was using `CurrentHealth` instead of `CurrentStamina` in its comparison.
1. Open `DecreaseStamina` → find the branch condition.
2. Make sure it references `CurrentStamina`, not `CurrentHealth`.
3. Drag `CurrentStamina` on top of the erroneous reference to replace it.

---

## Part 2: Implement Damage System

### Step 4: Set Up Event AnyDamage
1. In `ThirdPersonCharacter` → Event Graph:
   - Add **Event AnyDamage** node (fires when the actor receives damage).
   - Get `BPC_PlayerStats` → call `DecreaseHealth(Damage)`.

### Step 5: Handle Player Death
1. After `DecreaseHealth`, check the `IsPlayerDead` output with a **Branch**.
2. If **dead** → call a custom event `Die`:
   - **Disable Input** (player can't move)
   - Get **Mesh** → **Set Simulate Physics** = true (ragdoll)
3. If **alive** → continue (future: hit reactions, sounds, etc.)
4. Comment: `Damage → Apply Damage`, `Die`

### Step 6: Configure Ragdoll Collision
1. In `ThirdPersonCharacter` → **Mesh** component:
   - Set **Collision Preset** → **Custom**
   - **Collision Enabled:** Collision Enabled (Query and Physics)
2. In **Capsule Component**:
   - Set **Collision Preset** → **IgnoreOnlyPawn** (ragdoll body won't collide with the capsule)

### Step 7: Wire Up Debug Key to Apply Damage
1. Replace the direct `DecreaseHealth` debug call with **Apply Damage**:
   - Node: `Apply Damage`
   - **Damaged Actor:** Self
   - **Base Damage:** 10
   - This triggers the `Event AnyDamage` properly.
2. Test: Press debug key → player takes damage → at 0 HP → ragdoll.

### Step 8: Create Comment Color Presets
Instead of copying hex colors every time:
1. Select a comment block → open the color picker.
2. Find the **Presets** section → save current color as a preset (e.g., `Dark`).
3. Apply the preset to future comments with one click.

---

## Part 3: Sprint & Stamina Drain

### Step 9: Create Sprint Input
1. Create Input Action `IA_Sprint` → bind to **Left Alt** key in IMC_Default.
   - (Left Ctrl conflicts with crouch; Left Shift is used for vault.)

### Step 10: Implement Sprint Loop
1. On `IA_Sprint` **Started**:
   - **Set Timer by Event** → looping, time = `0.1` seconds
   - Event: Custom event `DrainStamina`
   - Promote the timer return value to variable `SprintLoop`
2. In `DrainStamina`:
   - Get `BPC_PlayerStats` → call `DecreaseStamina(1)`
   - Get **Character Movement** → **Set Max Walk Speed** = `750`
   - Create variable `CanSprint` (Boolean, default: true)
   - **Branch:** If `CanSprint` is false → set max walk speed back to `500`, don't drain
3. Check the `StaminaLeft` output from `DecreaseStamina`:
   - If **false** (stamina depleted) → set `CanSprint` = false
   - If **true** → continue sprinting

### Step 11: Stop Sprinting
1. On `IA_Sprint` **Completed**:
   - Set max walk speed back to `500`
   - Set `CanSprint` = true (reset for next sprint)
   - Set `IsSprinting` = false
   - Get `SprintLoop` → **Clear and Invalidate Timer by Handle** (stops the drain loop)

### Step 12: Stamina Recovery
1. On **Event Tick**:
   - Get **Velocity** → **Vector Length** → check if **<= 0** (standing still)
   - Add **Delay** = `0.1` seconds (throttle recovery to once per 0.1s)
   - Get `BPC_PlayerStats` → call `IncreaseStamina(1)`
   - **Important:** Only recover if **not sprinting** — check `IsSprinting` Boolean
   - Create variable `IsSprinting` (Boolean):
     - Set to **true** when sprint starts
     - Set to **false** when sprint stops (both on completed AND when stamina runs out)

---

## Quick Reference — Key Values

| Setting | Value | Notes |
|---------|-------|-------|
| Sprint speed | 750 | Max walk speed while sprinting |
| Normal walk speed | 500 | Default max walk speed |
| Stamina drain rate | 1 per 0.1s | = 10 stamina/second |
| Stamina recovery rate | 1 per 0.1s | = 10 stamina/second (when standing still) |
| Sprint key | Left Alt | Avoids conflict with crouch (LCtrl) and vault (LShift) |
| Ragdoll mesh collision | Query and Physics | Required for physics simulation |
| Capsule collision (dead) | IgnoreOnlyPawn | Prevents ragdoll from flying around |

---

## Pro Tips

- **Use `Apply Damage` instead of calling `DecreaseHealth` directly.** This goes through UE5's damage event system, which is cleaner and extensible.
- **`Delay Until Next Tick`** solves race conditions where one Blueprint's BeginPlay runs before another's.
- **Comment color presets** save time — create them once, reuse everywhere.
- **Clear timer handles** when stopping loops — otherwise the timer keeps running in the background.
- **`IsSprinting` flag** prevents stamina from recovering while the player is still holding the sprint key but has no stamina.
- **The stamina bar animation looks choppy at 0.1s intervals.** For smoother drain, use `FInterp To` (lerp) on the bar percent instead of direct value updates.

---

## Related

- 📄 Full Transcript: [[06_Damage_and_Stamina]]
- ← Previous: [[08_RPG_Tutorial_05_Player_Stats]]
- → Next: [[10_RPG_Tutorial_07_Levels_and_XP]]
- 📚 Series: [[_MOC_Step_by_Step_Guides]]
- 📄 Full Transcript: [[09_Combat]]
