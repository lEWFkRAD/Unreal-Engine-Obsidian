---
title: "RPG Tutorial #9: Combat"
source: "https://www.youtube.com/watch?v=sWpENaVGj2M"
video_id: "sWpENaVGj2M"
type: "step-by-step-guide"
series: "Step-by-Step Guides"
episode: 12
tags: [ue5, rpg, combat, combos, melee, guide]
---

# Unreal Engine 5 RPG Tutorial Series — #9: Combat

**Source:** https://www.youtube.com/watch?v=sWpENaVGj2M
**Duration:** 37:13
**Extracted from:** `Unreal_Engine_5_RPG_Tutorial_Series_-_#9_Combat.md`

---

## Prerequisites

- Completed Episode #8 (Sounds and UI)
- Combat animations from video description (3 sword attacks + 1 kick, from Epic's RPG template)

---

## Part 1: Bug Fix — Stamina Drain During Vaulting

### Step 1: Prevent Stamina Drain While Not Walking
1. In `ThirdPersonCharacter` → `DrainStamina` event → branch condition:
   - Add an **AND** condition: check **Movement Mode** == **Walking**
   - This prevents stamina drain while vaulting, falling, or flying.

---

## Part 2: Import Combat Animations

### Step 2: Import Sword Attack Animations
1. Navigate to `Characters/RPG_Character/Animations/`.
2. Create folder: `Sword_Attacks`.
3. Import the 4 animations from the video description:
   - Attack 1, Attack 2, Attack 3, Kick
4. Skeleton: `SK_Mannequin` (UE5).
5. Preview each to verify they look correct.

---

## Part 3: Attack System Component

### Step 3: Create the Attack System Component
1. In `Blueprints/`, create an **Actor Component**: `BPC_AttackSystem`.
2. Open it. Delete the default BeginPlay.

### Step 4: Define Attack Variables
| Variable | Type | Default | Purpose |
|----------|------|---------|---------|
| `CanAttack` | Boolean | true | Future: disable when out of stamina, swimming, etc. |
| `IsAttacking` | Boolean | false | Prevents overlapping attacks |
| `SaveAttack` | Boolean | false | Buffered input for combo transitions |
| `AttackIndex` | Integer | 0 | Current attack in the combo sequence |
| `CharacterMesh` | Skeletal Mesh | — | Set at BeginPlay via cast |

### Step 5: Create Attack Input
1. Create Input Action `IA_Attack` → bind to **Left Mouse Button** in IMC_Default.

---

## Part 4: Attack Logic

### Step 6: Sword Attack Event
1. On `IA_Attack` **Started**:
   - **Branch:** `CanAttack` == true
   - If true → call custom event `SwordAttack`

2. In `SwordAttack`:
   - **Branch:** `IsAttacking` == false (not already attacking)
   - If **false** (first attack):
     - Set `SaveAttack` = true
     - Set `IsAttacking` = true
     - Use **Switch on Integer** with `AttackIndex` (0-3)
     - Each case plays a different attack montage (see Step 8)
   - If **true** (already attacking — combo input):
     - Set `SaveAttack` = true (buffer the next attack)

### Step 7: Sword Attack Combo Event
1. Create custom event `SwordAttackCombo` (called from animation montage notifies).
2. **Branch:** `SaveAttack` == true?
   - **True:**
     - Set `SaveAttack` = false
     - Increment `AttackIndex` (wrap around or cap at max)
     - Play next attack montage via Switch on Integer
   - **False:**
     - Call `StopCombo` event (reset state)

### Step 8: Stop Combo Event
1. Create custom event `StopCombo`.
2. Set `IsAttacking` = false
3. Set `AttackIndex` = 0

### Step 9: Create Attack Montages
For each of the 4 attack animations:
1. Right-click the animation → **Create Animation Montage**.
2. Open the montage:
   - Adjust **Blend In** time: ~0.3s
   - Adjust **Blend Out** time: ~0.4s
3. Add an **Anim Notify** at the end of the montage → call `SwordAttackCombo`
   - This triggers the combo check when the animation finishes.

### Step 10: Create Attack Functions
For each attack (Attack 1-4):
1. Create a custom event: `Attack1`, `Attack2`, `Attack3`, `Attack4`
2. Each event:
   - Gets `CharacterMesh` → **Play Montage** → select the corresponding montage
   - Sets `AttackIndex` to the next value (1→2→3→0)

### Step 11: Initialize Character Mesh
1. In `BPC_AttackSystem` → Event Graph → BeginPlay:
   - Get **Owner** → **Cast to ThirdPersonCharacter** → get **Mesh**
   - Promote to variable `CharacterMesh`

### Step 12: Add Component to Player
1. In `ThirdPersonCharacter`, add component: `BPC_AttackSystem`.

---

## Part 5: Animation Montage Setup

### Step 13: Montage Notify for Combo
1. In each attack montage, add an **Anim Notify** near the end (before blend out):
   - This calls `SwordAttackCombo` to check if the player clicked again.
2. The notify timing defines the **combo window** — the period during which the player can queue the next attack.

### Step 14: Montage Blend Settings
- **Blend In:** 0.3 seconds (smooth transition from previous animation)
- **Blend Out:** 0.4 seconds (smooth transition back to locomotion)
- Adjust if attacks feel too snappy or too sluggish.

---

## Quick Reference — Key Values

| Setting | Value | Notes |
|---------|-------|-------|
| Attack animations | 4 (3 swords + 1 kick) | Combo sequence |
| Combo sequence | Attack1 → Attack2 → Kick → Attack3 | Custom order for cool feel |
| Blend In time | 0.3s | Montage transition |
| Blend Out time | 0.4s | Montage transition |
| Combo window | End of montage notify | When SwordAttackCombo fires |
| CanAttack default | true | Future: stamina/condition checks |

---

## Combo Flow

```
Left Click → SwordAttack
  ├─ Not attacking → IsAttacking=true, Play Attack1, AttackIndex=1
  ├─ Attack1 playing → SaveAttack=true (buffer)
  │   └─ Attack1 ends → SwordAttackCombo
  │       ├─ SaveAttack=true → Play Attack2, AttackIndex=2
  │       └─ SaveAttack=false → StopCombo
  ├─ Attack2 playing → SaveAttack=true (buffer)
  │   └─ Attack2 ends → SwordAttackCombo
  │       ├─ SaveAttack=true → Play Kick, AttackIndex=3
  │       └─ SaveAttack=false → StopCombo
  └─ ... and so on through the full combo chain
```

---

## Pro Tips

- **SaveAttack** is an input buffer — it lets the player click slightly before the current attack finishes and still chain into the next one. Without it, the player would need frame-perfect timing.
- **Switch on Integer** scales easily — add more attacks by adding more cases.
- **AttackIndex** wraps or resets — the combo loops back to the start after the last attack.
- **Blend times matter.** Too fast = jarring snap. Too slow = sluggish feel. 0.3-0.4s is a good starting range.
- **The combo notify timing** defines how forgiving the combo window is. Earlier = tighter timing required. Later = more forgiving.

---

## Related

- 📄 Full Transcript: [[09_Combat]]
- ← Previous: [[11_RPG_Tutorial_08_Sounds_and_UI]]
- → Next: [[13_RPG_Tutorial_10_Sword_Trace_Damage]]
- 📚 Series: [[_MOC_Step_by_Step_Guides]]
