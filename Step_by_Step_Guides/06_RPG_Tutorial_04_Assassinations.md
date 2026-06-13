---
title: "RPG Tutorial #4: Assassinations"
source: "https://www.youtube.com/watch?v=TuiDgXCarP0"
video_id: "TuiDgXCarP0"
type: "step-by-step-guide"
series: "Step-by-Step Guides"
episode: 6
tags: [ue5, rpg, assassinations, stealth, combat, guide]
---

# Unreal Engine 5 RPG Tutorial Series — #4: Assassinations

**Source:** https://www.youtube.com/watch?v=TuiDgXCarP0
**Duration:** 32:47
**Extracted from:** `Unreal_Engine_5_RPG_Tutorial_Series_-_#4_Assassinations.md`

---

## Prerequisites

- Completed Episode #3 (Vaulting with Motion Warping)
- Free combat animation pack (video description — use discount code `SAMPLE` at checkout to get it free)
- Motion Warping plugin enabled

---

## Part 1: Import & Retarget Animations

### Step 1: Import Assassination Animations
1. Navigate to `Characters/RPG_Character/Animations/`.
2. Create folder: `Assassinations`.
3. From the downloaded pack, select these two paired animations:
   - `Paired_Knife_Stealth_Kidney_and_Neck_Attack` (attacker)
   - `Paired_Knife_Stealth_Kidney_and_Neck_Victim` (victim)
4. Drag into Content Browser.
5. **Important:** Set skeleton to the **UE4 skeleton** (these animations use the old skeleton, not UE5).
6. Import all.

### Step 2: Retarget to UE5
1. Create a `ue4` folder → move both animations into it.
2. Select both → right-click → **Retarget Animation Assets → Duplicate and Retarget**.
3. Set **Source** = UE4 skeleton, **Target** = UE5 `SK_Mannequin`.
4. Select the output folder: `Characters/RPG_Character/Animations/Assassinations/`.
5. Retarget. Now you have UE5-compatible versions.

### Step 3: Enable Root Motion on Both Animations
1. Open each retargeted animation.
2. Enable **Root Motion** in Asset Details. Leave defaults.
3. Save.

### Step 4: Create Animation Montages
1. Select the **attacker** animation → right-click → **Create Animation Montage**.
2. Open it → add a **Motion Warping Notify State**:
   - Start at the beginning of the montage
   - End at ~frame **13** (where the attacker reaches the victim)
   - Settings: **Skew Warp**, name = `assassination_warp`
3. Select the **victim** animation → right-click → **Create Animation Montage**.
   - No motion warping needed (victim doesn't move).

---

## Part 2: Blueprint Interface for Enemy Communication

### Step 5: Create a Blueprint Interface
1. In the `Blueprints` folder, create a **Blueprint Interface**: `BPI_Assassination`.
2. Open it. Rename the default function to `StealthBackAssassination`.
3. Add two **Outputs**:
   - `Location` (Vector) — where the player should warp to
   - `Rotation` (Rotator) — which way the player should face

### Step 6: Create the Dummy Enemy
1. Create a new Blueprint class → **Character** → `BP_Dummy`.
2. Set the mesh to `Manny`:
   - Location: `(-89, 0, 0)`
   - Rotation: `(0, -90, 0)`
3. Set **Anim Class** to `ABP_Manny`.
4. Add the **BPI_Assassination** interface: Class Settings → Implemented Interfaces → add it.

### Step 7: Set Up the Assassination Radius
1. In `BP_Dummy`, add a **Sphere Collision** component:
   - Name: `AssassinationRadius`
   - Position it slightly behind the dummy
   - Set radius to cover the area behind the enemy
   - Collision Preset: **OverlapAllDynamic**
2. Set the **widget visibility** (see Part 4) to hidden by default.

### Step 8: Create the Assassination Reference Point
1. In `BP_Dummy`, duplicate the mesh → name it `AssassinationRef`.
2. Open **Animation Mode** on the reference mesh → preview the attack animation at frame 1.
3. Position the reference mesh where the player should stand during the assassination:
   - Example: `(-40, 0, -89)`, rotation `(0, 0, 90)`
4. In Details: enable **Hidden in Game**, set collision to **No Collision**.

### Step 9: Implement the Interface in the Dummy
1. In `BP_Dummy`, the `StealthBackAssassination` function auto-generates from the interface.
2. Implement it:
   - **Output Location:** Get `AssassinationRef` → **Get World Location**
   - **Output Rotation:** Get **Actor Rotation** (the dummy's rotation — use the dummy's, not the reference's)
3. Also add: Play the **victim montage** on the dummy's mesh.

---

## Part 3: Player Blueprint — Assassination Logic

### Step 10: Fix Crouch + Jump Interaction
Before the assassination system, fix the crouch/jump issue:
1. In `ThirdPersonCharacter`, replace the FlipFlop with a **Branch**:
   - Condition: `Is Crouched` (NOT Boolean)
   - If **not crouched** → set crouched = true, max walk speed = 350
   - If **already crouched** → set crouched = false, max walk speed = 500
2. On **Jump input**: add a Branch checking `Is Crouched`:
   - If crouched → first uncrouch, then jump
   - If not crouched → jump directly

### Step 11: Create Input Actions
1. Create Input Action `IA_Vault` → bind to **Left Shift** in IMC_Default.
2. Create Input Action `IA_Assassinate` → bind to **Left Mouse Button** in IMC_Default.
3. Wire `IA_Vault` → call the `Vault` function.
4. Wire `IA_Assassinate` → the assassination logic (below).

### Step 12: Assassination Logic in ThirdPersonCharacter
1. On `IA_Assassinate` pressed:
2. **For Each Loop** on `Get Overlapping Actors` (no class filter).
3. For each overlapping actor:
   - **Does Implement Interface** → check for `BPI_Assassination`
   - If yes → call `StealthBackAssassination` → get `Location` and `Rotation`
4. **Play Montage** on player mesh → select the attacker montage.
5. **Add or Update Warp Target:**
   - Name: `assassination_warp` (must match the montage notify EXACTLY)
   - Location: from interface output
   - Rotation: from interface output
6. Comment this section: `Stealth Assassination`.

### Step 13: Ragdoll the Enemy After Assassination
1. In `BP_Dummy`, create a custom event `Ragdoll`.
2. Add a **Delay** of `2.5` seconds.
3. Get the mesh → **Set Simulate Physics** = true.
4. In the dummy's mesh component:
   - Set **Collision Complexity** to **Physics Actor**
   - Set camera collision to **Ignore**
5. In the **Capsule Component**: set Collision Preset to **IgnoreOnlyPawn** (so physics ragdoll doesn't interfere with the player).
6. Call `Ragdoll` from the `StealthBackAssassination` interface implementation.
   - **Note:** Can't use a Delay in a function — must use a Custom Event.

> **Why the delay?** If you apply physics on the same frame as the animation, the animation won't play — the ragdoll falls immediately. The 2.5s delay lets the victim animation finish first.

---

## Part 4: Assassination Prompt Widget

### Step 14: Create the Widget
1. Create folder `UI/`.
2. Right-click → **User Interface → Widget Blueprint** → name it `WB_AssassinatePrompt`.
3. Add a **Canvas Panel** → add a **Text** block:
   - Text: `Left Mouse - Assassinate`
   - Anchors: Middle center
   - Position X/Y: 0
   - Alignment X: 0.5
   - Font size: appropriate for readability
4. Compile and save.

### Step 15: Add Widget to the Dummy
1. In `BP_Dummy`, add a **Widget** component (not Interaction Widget).
2. Set the widget class to `WB_AssassinatePrompt`.
3. Position it above the enemy's head.
4. Scale it down (e.g., 0.25) so it's not too large.
5. Set **Visibility** to **false** by default.

### Step 16: Show/Hide Widget on Overlap
1. In `BP_Dummy`, go to `AssassinationRadius`:
   - **On Component Begin Overlap:**
     - Cast to ThirdPersonCharacter → if successful, set widget **Visibility** = true
   - **On Component End Overlap:**
     - Cast to ThirdPersonCharacter → if successful, set widget **Visibility** = false
2. Also hide the widget when the assassination starts (in the `StealthBackAssassination` function → set visibility = false).

### Step 17: Make Widget Face the Camera
1. In `BP_Dummy` Event Graph, on **Event Tick**:
   - Get the widget component → **Set World Rotation**
   - Use **Find Look at Rotation**:
     - Start: Widget world location
     - End: **Player Camera Manager** → Get World Location
   - This makes the text always face the player's camera.

---

## Quick Reference — Key Values

| Setting | Value | Location |
|---------|-------|----------|
| Assassination warp name | `assassination_warp` | Montage notify + Blueprint |
| Ragdoll delay | 2.5 seconds | BP_Dummy custom event |
| Reference position (example) | (-40, 0, -89) | AssassinationRef mesh |
| Reference rotation (example) | (0, 0, 90) | AssassinationRef mesh |
| Widget scale | 0.25 | Widget component |
| Widget visibility default | false | Widget component |

---

## Pro Tips

- **Blueprint Interfaces** let you communicate with any enemy class without casting. Add the interface to new enemy types and they'll automatically support assassinations.
- **Motion warping names are case-sensitive.** Copy-paste directly from the montage.
- **The reference mesh** is your positioning tool — preview both animations at frame 1, align the reference where the attacker should stand, then hide it in-game.
- **Ragdoll collision:** Set the capsule to IgnoreOnlyPawn so the ragdolled body doesn't push the player around.
- **Functions can't use delays.** If you need a delay, use a Custom Event instead.
- **Temporary systems:** The widget and dummy are placeholders. The AI system (future episode) will replace the overlap detection with proper awareness checks.

---

## Related

- 📄 Full Transcript: [[04_Assassinations]]
- ← Previous: [[05_RPG_Tutorial_03_Vaulting_Motion_Warping]]
- → Next: [[07_RPG_Tutorial_05_Player_Stats]]
- 📚 Series: [[_MOC_Step_by_Step_Guides]]
- 📄 Full Transcript: [[07_Levels_and_XP]]
