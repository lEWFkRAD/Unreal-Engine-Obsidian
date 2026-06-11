---
title: "RPG Tutorial #10: Sword Trace Damage and Hit Reactions"
source: "https://www.youtube.com/watch?v=zbbWk851IXk"
video_id: "zbbWk851IXk"
type: "step-by-step-guide"
series: "Step-by-Step Guides"
episode: 13
tags: [ue5, rpg, combat, sword, damage, hit-reactions, guide]
---

# Unreal Engine 5 RPG Tutorial Series — #10: Sword Trace Damage and Hit Reactions

**Source:** https://www.youtube.com/watch?v=zbbWk851IXk
**Duration:** 49:45
**Extracted from:** `Unreal_Engine_5_RPG_Tutorial_Series_-_#10_Sword_Trace_Damage_and_Hit_Reactions.md`

---

## Prerequisites

- Completed Episode #9 (Combat system with combo attacks)
- Hit reaction animations from video description (from Epic's RPG template)
- `BPC_AttackSystem` component with sword trace functionality

---

## Part 1: Setup Changes

### Step 1: Change Assassination Input to Right Mouse Button
1. Open IMC_Default → change `IA_Assassinate` binding from Left Mouse to **Right Mouse Button**.
2. Update the assassination prompt widget text: change "Left Mouse" to "Right Mouse".

### Step 2: Shrink Assassination Radius
1. In `BP_Dummy` → select `AssassinationRadius` sphere collision.
2. Reduce radius to ~35 (smaller, more precise — must be directly behind the enemy).

### Step 3: Fix Crouch Camera Timeline
1. In the crouch camera timeline, change the Reverse connection from "Reverse from End" to **Reverse** (normal).
   - This prevents snapping if the player taps crouch quickly.

---

## Part 2: Sword Trace System

### Step 4: Create Socket Points on the Sword
1. In `ThirdPersonCharacter` → Mesh component:
   - Add two **socket** points on the sword bone:
     - `SwordTopPoint` — at the tip of the sword
     - `SwordBottomPoint` — at the base of the sword
   - These define the sword's sweep path.

### Step 5: Create Sword Trace Function
1. In `BPC_AttackSystem`, create function `StartSwordTrace`.
2. Add a **Set Timer by Event** (looping, 0.01s) → custom event `SwordTraceLoop`.
3. In `SwordTraceLoop`:
   - Get `CharacterMesh` → get `SwordTopPoint` world location → **Start**
   - Get `CharacterMesh` → get `SwordBottomPoint` world location → **End**
   - **Sphere Trace by Channel** between the two points
   - Radius: appropriate for sword width
4. Promote timer return to variable `SwordTraceLoop`.

### Step 6: Create Stop Sword Trace Function
1. Create function `StopSwordTrace`.
2. Get `SwordTraceLoop` → **Clear and Invalidate Timer by Handle**.

### Step 7: Create Anim Notify State Blueprint
1. In `Blueprints/`, create a new **Anim Notify State** Blueprint: `BP_Notify_SwordTraceLoop`.
2. Override **Received Notify Begin**:
   - Get Mesh Owner → Cast to ThirdPersonCharacter → get `BPC_AttackSystem`
   - Call `StartSwordTrace`
3. Override **Received Notify End**:
   - Same cast chain → call `StopSwordTrace`

### Step 8: Add Trace Notify to Attack Montages
1. Open each attack montage (Attack 1-4).
2. In the Notifies section, add `BP_Notify_SwordTraceLoop`:
   - Start: where the sword begins its swing
   - End: where the sword finishes its swing
3. This creates a trace that follows the sword during the entire swing animation.

---

## Part 3: Damage Application

### Step 9: Apply Damage on Trace Hit
1. In `SwordTraceLoop` event, after the sphere trace:
   - **Branch:** Did we hit something?
   - If yes → **Branch:** Does the hit actor have tag `Damageable`?
     - (Check: Get Hit Actor → Actor Has Tag → `Damageable`)
   - If yes → **Apply Damage** to the hit actor (base damage: 10)
   - Use **Do Once** node to prevent multiple damage per swing
   - After 0.5s **Delay** → reset the Do Once (allows damage on next swing)

### Step 10: Tag Enemies as Damageable
1. In `BP_Dummy` → Class Defaults → **Actor Tags** → add `Damageable`.
2. This tag marks any actor that can be damaged by sword attacks.
3. Future enemies/objects also get this tag to be damageable.

---

## Part 4: Hit Reactions

### Step 11: Import Hit Reaction Animations
1. Create folder: `Hit_React` in animations.
2. Import hit reaction animations from the video description.
3. Skeleton: `SK_Mannequin`.

### Step 12: Create Hit Reaction Montages
1. Select both hit reaction animations → right-click → **Create Animation Montage**.
2. In the dummy's `Event Any Damage`:
   - Play a random hit reaction montage on the dummy's mesh.

### Step 13: Camera Shake on Hit
1. Create a **Camera Shake** Blueprint (or use a built-in one).
2. In the player's attack system, after applying damage:
   - Get Player Camera Manager → **Start Camera Shake**.

### Step 14: Hit Sounds
1. In the hit reaction montage or the damage event:
   - **Play Sound at Location** → select a hit/grunt sound
   - Location: hit actor's location
   - Attenuation: `SA_CharacterGeneral`

---

## Quick Reference — Key Values

| Setting | Value | Notes |
|---------|-------|-------|
| Sword trace loop rate | 0.01s | Very frequent for accuracy |
| Sword trace radius | Appropriate for blade width | Adjust for feel |
| Damage per hit | 10 | Base damage (future: weapon data) |
| Do Once reset delay | 0.5s | Prevents multi-hit per swing |
| Assassination radius | ~35 | Must be behind enemy |
| Damageable tag | `Damageable` | Actor tag on damageable actors |

---

## Sword Trace Flow

```
Attack Montage Plays
  └─ Notify State: BP_Notify_SwordTraceLoop
      ├─ Begin → StartSwordTrace (starts loop timer)
      │   └─ Every 0.01s: Sphere Trace Top→Bottom
      │       ├─ Hit something?
      │       │   ├─ Has tag "Damageable"?
      │       │   │   ├─ Yes → Apply Damage (Do Once)
      │       │   │   └─ No → Ignore
      │       │   └─ No → Continue tracing
      │       └─ Loop continues...
      └─ End → StopSwordTrace (clears timer)
```

---

## Pro Tips

- **Do Once + Delay** prevents the looping trace from applying damage 100 times per swing. The 0.5s delay resets it for the next attack.
- **Two separate branches** for hit detection and tag checking — don't use AND directly because accessing the hit actor when nothing was hit causes errors.
- **Actor Tags** (`Damageable`) are a simple, extensible way to mark damageable objects. Add the tag to any new enemy or destructible.
- **Anim Notify States** (with Begin/End) are better than single notifies for duration-based actions like traces. Single notifies fire once; states fire for a range.
- **Socket points** on the sword bone give precise trace endpoints that follow the animation perfectly.

---

## Related

- 📄 Full Transcript: [[10_Sword_Trace_Damage_and_Hit_Reactions]]
- ← Previous: [[12_RPG_Tutorial_09_Combat]]
- → Next: [[14_Blueprint_Fundamentals_Class_01]]
- 📚 Series: [[_MOC_Step_by_Step_Guides]]
