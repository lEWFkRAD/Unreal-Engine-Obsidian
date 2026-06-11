---
title: "RPG Tutorial #7: Levels and XP"
source: "https://www.youtube.com/watch?v=3cf4T-B53SM"
video_id: "3cf4T-B53SM"
type: "step-by-step-guide"
series: "Step-by-Step Guides"
episode: 10
tags: [ue5, rpg, levels, xp, progression, guide]
---

# Unreal Engine 5 RPG Tutorial Series — #7: Levels and XP

**Source:** https://www.youtube.com/watch?v=3cf4T-B53SM
**Duration:** 25:31
**Extracted from:** `Unreal_Engine_5_RPG_Tutorial_Series_-_#7_Levels_and_XP.md`

---

## Prerequisites

- Completed Episode #6 (Damage and Stamina)
- `BPC_PlayerStats` component with health/stamina functions
- Sprint system with stamina drain

---

## Part 1: Fix Sprint + Crouch Conflict

### Step 1: Prevent Sprinting While Crouched
1. In `ThirdPersonCharacter` → Sprint logic:
   - Add an **AND** condition to the sprint branch:
     - `CanSprint == true` **AND** `IsCrouched == false` (use **NOT** gate)
   - Only start sprinting if both conditions are met.

### Step 2: Prevent Crouching While Sprinting
1. In the crouch logic:
   - Add a check: `IsSprinting == false` (use **NOT** gate)
   - Only allow crouch if not sprinting.
   - Also add this check in both the **Play** and **Reverse** branches of the crouch camera timeline.

---

## Part 2: Sprint Animation

### Step 3: Create a Faster Run Animation
1. Navigate to `Mannequins/Animations/Manny/`.
2. Duplicate `MM_Run_Forward` → rename to `MM_Sprint`.
3. Open it → increase the **Rate Scale** to `1.3` (adjust to taste — 1.5 may be too fast).
4. Save.

### Step 4: Update the Locomotion Blendspace
1. Open `BS_Locomotion`.
2. Change the **Max** axis value from `500` to `750` (matches sprint speed).
3. At position **750** (right end), drag in the new `MM_Sprint` animation.
4. Now the blendspace transitions: idle → walk → jog → sprint.
5. Save.

---

## Part 3: XP and Level Functions

### Step 5: Create IncreaseXP Function
1. In `BPC_PlayerStats`, create function `IncreaseXP`.
2. Add input: `AddedXP` (Float).
3. Category: `Level and XP`.
4. Logic:
   - Set `XP` = `XP + AddedXP`
   - **Branch:** Is `XP >= MaxXP`?
     - **True:** Call `IncreaseLevel(1)`
     - **False:** Update XP bar UI (see Step 7)

### Step 6: Create IncreaseLevel Function
1. Create function `IncreaseLevel`.
2. Add input: `AddedLevel` (Integer — default 1, but flexible for bonus levels).
3. Category: `Level and XP`.
4. Logic:
   - Set `Level` = `Level + AddedLevel`
   - Set `MaxXP` = `MaxXP + 150` (increases XP needed for next level)
   - Set `XP` = `0` (reset XP bar)
   - Update level text UI
   - Update XP bar UI

> **Future improvement:** Replace the flat +150 with a data table lookup for level-specific XP requirements.

---

## Part 4: XP and Level UI

### Step 7: Add Level Display to HUD
1. Open `WGWB_MainHUD`.
2. Add a **Text** block (top-right area):
   - Placeholder: `Level 15`
   - Font size: ~12
   - Alignment: center
   - Rename to `LevelText` → **Is Variable** = true
3. Add an **Image** (temporary shield icon) behind the text:
   - Size: 70×70
   - Rename to `LevelIcon`
4. Add an **XP Progress Bar** (top-right, below the level):
   - Thin bar (height: ~3, width: ~140)
   - Fill color: green (temporary)
   - Rename to `XPBar` → **Is Variable** = true
5. Add **XP Text** below the bar:
   - Placeholder: `0 / 100`
   - Font size: ~7-10
   - Rename to `XPText` → **Is Variable** = true

### Step 8: Wire Up XP UI Updates
In `IncreaseXP` function:
1. Get `PlayerCharacter` → `HUDWidget` → `XPBar`
2. Set Percent = `XP / MaxXP`
3. Get `XPText` → Set Text using **Format Text**:
   - Pattern: `{0} / {1}`
   - `{0}` = current XP
   - `{1}` = MaxXP
4. In **BeginPlay**, also initialize: set XP bar percent and text to default values.

In `IncreaseLevel` function:
1. Get `LevelText` → Set Text = `Level` (convert integer to text)
2. Update `XPBar` percent = `0 / new MaxXP`
3. Update `XPText` = `0 / new MaxXP`

### Step 9: Fix UI Update Order
- The XP bar update must happen on the **False** branch (XP didn't reach max).
- On the **True** branch, `IncreaseLevel` handles the UI reset.
- Make sure both paths update the UI.

---

## Part 5: Debug Testing

### Step 10: Add XP Debug Key
1. In `ThirdPersonCharacter` → add **Debug Key** (Key 2):
   - Call `IncreaseXP(10)`
2. Test: Press 2 repeatedly → XP bar fills → at 100 → level up → resets to 0/250 → continues.

---

## Quick Reference — Key Values

| Setting | Value | Notes |
|---------|-------|-------|
| Sprint animation rate | 1.3 | Adjust to taste |
| Blendspace max speed | 750 | Matches sprint speed |
| MaxXP initial | 100 | XP needed for level 2 |
| MaxXP increase per level | +150 | Level 3 needs 250, level 4 needs 400, etc. |
| Level default | 1 | Starting level |
| XP added per debug press | 10 | For testing |

---

## XP Progression Table (Default)

| Level | MaxXP Needed | Cumulative XP |
|-------|-------------|---------------|
| 1 → 2 | 100 | 100 |
| 2 → 3 | 250 | 350 |
| 3 → 4 | 400 | 750 |
| 4 → 5 | 550 | 1300 |

---

## Pro Tips

- **Sprint + Crouch:** Block both directions — can't sprint while crouched, can't crouch while sprinting.
- **Animation Rate Scale** is a quick way to simulate faster movement without new animations. Replace with proper sprint animations later.
- **Format Text** (`{0} / {1}`) is cleaner than concatenating strings with Append nodes.
- **Both branches must update the UI** — the True branch (level up) resets the bar, the False branch updates progress.
- **Data tables** are the proper way to store level XP requirements. The flat +150 is a placeholder until the system matures.

---

## Related

- 📄 Full Transcript: [[07_Levels_and_XP]]
- ← Previous: [[09_RPG_Tutorial_06_Damage_and_Stamina]]
- → Next: [[11_RPG_Tutorial_08_Sounds_and_UI]]
- 📚 Series: [[_MOC_Step_by_Step_Guides]]
- 📄 Full Transcript: [[10_Sword_Trace_Damage_and_Hit_Reactions]]
