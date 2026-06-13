---
title: "RPG Tutorial #8: Sounds and UI"
source: "https://www.youtube.com/watch?v=QmgXB9wAYRk"
video_id: "QmgXB9wAYRk"
type: "step-by-step-guide"
series: "Step-by-Step Guides"
episode: 10
tags: [ue5, rpg, sound, ui, audio, interface, guide]
---

# Unreal Engine 5 RPG Tutorial Series — #8: Sounds and UI

**Source:** https://www.youtube.com/watch?v=QmgXB9wAYRk
**Duration:** 33:00
**Extracted from:** `Unreal_Engine_5_RPG_Tutorial_Series_-_#8_Sounds_and_UI.md`

---

## Prerequisites

- Completed Episode #7 (Levels and XP)
- Sound files from video description (footsteps, knife stab, grunts, deaths, level up)

---

## Part 1: Sound Organization

### Step 1: Create Audio Folder Structure
1. Create folder: `Audio/`
2. Sub-folders:
   - `Footsteps/`
   - `Grunts_Hits/`
   - `UI/`
3. Import sounds into their respective folders:
   - Footstep → `Footsteps/`
   - Knife stab, grunts, deaths → `Grunts_Hits/`
   - Level up sound → `UI/`

---

## Part 2: MetaSounds for Dynamic Audio

### Step 2: Create Footstep MetaSound
1. Right-click in `Footsteps/` → **Sounds → MetaSound Source**.
2. Name it `MS_Footstep`.
3. Open it. Add a **Wave Player (Mono)** node.
4. Set the wave asset to the footstep sound.
5. Connect output → output node.
6. Add a **Random Float** node:
   - Min: `-3`, Max: `3`
   - Connect `On Play` → `Random Float` → `Next` → connect to pitch input
7. This randomly varies pitch each play → makes one footstep sound like many.
8. Save.

### Step 3: Create Sound Attenuation
1. Right-click in `Audio/` → **Sounds → Sound Attenuation**.
2. Name it `SA_CharacterGeneral`.
3. Settings:
   - **Inner Radius:** ~100
   - **Falloff Distance:** ~1000
   - (Adjust to taste — this controls how far sounds are heard)
4. Apply this attenuation to:
   - The MetaSound's **Source Attenuation Settings**
   - All raw sound assets used in notifies

### Step 4: Create Knife MetaSound
1. In `Grunts_Hits/`, create `MS_KnifeStab` from the knife stab sound.
2. Same MetaSound setup: Wave Player + Random Float for pitch variation.
3. Apply `SA_CharacterGeneral` attenuation.

---

## Part 3: Add Footstep Sounds to Animations

### Step 5: Add Footsteps to Run Animation
1. Open `MM_Run_Forward` animation.
2. In the **Notifies** section, add a new track: `Footsteps`.
3. At each frame where the foot touches the ground:
   - Right-click → **Add Notify → Play Sound**
   - Select `MS_Footstep` (the MetaSound, not the raw sound)
4. Copy-paste the notify for each footstep contact point.

### Step 6: Add Footsteps to Sprint Animation
1. Open `MM_Sprint` → add `Footsteps` track.
2. Copy-paste footstep notifies (timing may differ slightly due to rate scale).

### Step 7: Add Landing Sound
1. Open the `land` animation.
2. Add a **Play Sound** notify at the impact frame.
3. Use `MS_Footstep` with **volume multiplier** = `1.3` (louder for impacts).

### Step 8: Add Footsteps to Vault Animation
1. Open the vault animation sequence.
2. Add footstep notifies at each ground contact point during the vault.
3. Volume: `1.3` for impact moments.

---

## Part 4: Add Combat Sounds

### Step 9: Add Knife Sounds to Assassination Animation
1. Open the attacker assassination animation.
2. Add a notify track for knife sounds.
3. Place **Play Sound** notifies at the stab impact frames.
4. Use `MS_KnifeStab`.
5. **Important:** The sound file has a slight delay — place the notify slightly BEFORE the visual impact to sync.
6. Copy to all stab/neck contact points.

### Step 10: Add Death Grunt to Dummy
1. In `BP_Dummy` → after the ragdoll delay:
   - **Play Sound at Location** → select a death grunt sound
   - Location: `Get Actor Location`
   - Attenuation: `SA_CharacterGeneral`

---

## Part 5: Level Up Sound

### Step 11: Add Level Up Sound
1. In `BPC_PlayerStats` → `IncreaseLevel` function:
   - **Play Sound at Location** → select the level up sound
   - Location: Player's actor location
   - Attenuation: `SA_CharacterGeneral`

---

## Part 6: UI Improvements

### Step 12: Customize Health/Stamina Bars
- Replace default progress bar visuals with custom images/brushes
- Add background images behind bars
- Adjust colors, borders, and styling
- (Specific customization depends on the UI assets provided in the video description)

### Step 13: Add Level Shield Icon
- Replace the temporary image with a proper shield icon for the level display
- Adjust sizing and positioning

---

## Quick Reference — Key Values

| Setting | Value | Notes |
|---------|-------|-------|
| Pitch randomization range | -3 to 3 | Makes one sound feel like many |
| Sound attenuation inner radius | 100 | Full volume zone |
| Sound attenuation falloff | 1000 | Hearing range |
| Landing/impact volume | 1.3x | Louder for hard impacts |
| Knife sound timing | Slightly before visual impact | Compensates for sound file delay |

---

## Pro Tips

- **MetaSounds** with pitch randomization make a single footstep recording sound like many variations. One sound, many feels.
- **Always use MetaSounds** for repeated sounds (footsteps, hits) — raw sounds get repetitive fast.
- **Sound Attenuation** makes sounds 3D — without it, footstep audio plays globally as if it's everywhere.
- **Notify timing for sounds with delays:** Preview in the animation editor, then shift the notify earlier to compensate.
- **Volume multiplier on notifies** lets you reuse the same MetaSound at different intensities (soft walk vs. hard landing).

---

## Related

- 📄 Full Transcript: [[08_Sounds_and_UI]]
- ← Previous: [[09_RPG_Tutorial_07_Levels_and_XP]]
- → Next: [[11_RPG_Tutorial_09_Combat]]
- 📚 Series: [[_MOC_Step_by_Step_Guides]]
