---
title: "RPG Tutorial #3: Vaulting with Motion Warping"
source: "https://www.youtube.com/watch?v=HVhH2qi2B5Q"
video_id: "HVhH2qi2B5Q"
type: "step-by-step-guide"
series: "Step-by-Step Guides"
episode: 6
tags: [ue5, rpg, vaulting, motion-warping, parkour, guide]
---

# Unreal Engine 5 RPG Tutorial Series — #3: Vaulting with Motion Warping

**Source:** https://www.youtube.com/watch?v=HVhH2qi2B5Q
**Duration:** 42:57
**Extracted from:** `Unreal_Engine_5_RPG_Tutorial_Series_-_#3_Vaulting_with_Motion_Warping.md`

---

## Prerequisites

- Completed Episode #2 (Locomotion system)
- Vaulting animation (free from video description — exported from Echo template)
- Motion Warping plugin (built into UE5)

---

## Part 1: Setup

### Step 1: Enable the Motion Warping Plugin
1. Go to **Edit → Plugins**.
2. Search for **Motion Warping**.
3. Enable it → click **Yes** on the popup → **Restart** the editor.
4. After restart, verify it's enabled (search again in Plugins).

### Step 2: Import the Vault Animation
1. Navigate to `Characters/RPG_Character/Animations/`.
2. Create a new folder: `Vaulting`.
3. Download the vault animation from the video description (Echo template).
4. Drag it into the Content Browser → **Reset to Default** → set **Skeleton** to `SK_Mannequin` → **Import**.
5. Open the animation to verify it looks correct. Save.

### Step 3: Enable Root Motion on the Animation
1. Open the vault animation → go to **Asset Details**.
2. Under **Root Motion**, enable **Root Motion**.
3. Leave settings as default: **Reference Pose** disabled, **Root Lock** default, **Normalize** checked.
4. Save and close.

### Step 4: Create an Animation Montage
1. Select the vault animation → right-click → **Create → Animation Montage**.
2. Open the montage.

---

## Part 2: Set Up Motion Warping Notify States

### Step 5: Add Three Motion Warping Notify States
The vault animation has three phases: **start**, **middle**, and **landing**. Each needs a motion warping notify state.

#### Notify State 1: Vault Start
1. In the montage timeline, find the frame where the character begins to jump (~frame 5).
2. In the **Notifies** section, right-click on **Track 1** → **Add Notify State → Motion Warping**.
3. Hold **Shift** and drag the end of the notify to around frame **17-18**.
4. Select the notify → in **Details**:
   - **Root Motion Modifier:** Skew Warp
   - **Name:** `vault_start`
   - Enable **Ignore Z-Axis** (don't warp vertically on start)
   - Leave **Warp Rotation** enabled

#### Notify State 2: Vault Middle
1. On **Track 2** (add a new notify track if needed), place a new Motion Warping notify at ~frame **26**.
2. Drag to ~frame **40-41**.
3. In Details:
   - **Root Motion Modifier:** Skew Warp
   - **Name:** `vault_middle`
   - Enable **Ignore Z-Axis**
   - **Disable Warp Rotation**

#### Notify State 3: Vault Landing
1. On **Track 1** (above the first notify), place a new Motion Warping notify at ~frame **37**.
2. Drag to frame **~50** (end of animation).
3. In Details:
   - **Root Motion Modifier:** Skew Warp
   - **Name:** `vault_land`
   - **Disable Warp Rotation**
   - Enable **Ignore Z-Axis**

> **Layout tip:** Use separate notify tracks to avoid overlapping notify states visually.

---

## Part 3: Blueprint — Vault Detection (Trace System)

### Step 6: Add Motion Warping Component
1. Open `ThirdPersonCharacter` Blueprint.
2. **Add Component → Motion Warping**. No settings needed.

### Step 7: Create the Vault Function (Trace Logic)
1. In `ThirdPersonCharacter`, create a new function called `Vault`.

#### Phase 1: Height Detection (Forward Traces)
1. Add a **For Loop with Break** node. Set **Last Index** = `2` (3 iterations).
2. Add a **Sphere Trace by Channel** node.
3. Set the **Start**:
   - Get **Actor Location** → split to get individual axes.
   - Add `(Index * 30)` to the **Z** axis (creates 3 traces at different heights: 0, 30, 60).
4. Set the **End**:
   - Get **Actor Rotation** → **Get Forward Vector** → multiply by `180` (detection distance).
   - Add this to the start location.
5. Set **Radius** = `5` (thin traces for precision).
6. Add a **Branch** after the trace:
   - Condition: **Hit Result → Break Hit Result** (get the hit location).
   - If hit: **Break** the loop (we found the wall height).

#### Phase 2: Distance Detection (Downward Traces)
1. After the first loop, add another **For Loop with Break**. Set **Last Index** = `5` (6 iterations).
2. Add another **Sphere Trace by Channel**.
3. Set the **Start**:
   - Use the hit location from Phase 1 + offset of `100` on Z (start above the wall).
   - Add `(Index * 50)` to get separated traces along the wall.
   - Get **Actor Rotation** → **Get Forward Vector** → multiply by `50` → add to start.
4. Set the **End**: Subtract `100` from Z (trace downward to find where the wall ends).
5. Add a **Branch**:
   - If **not hitting** → the wall has ended → this is where we land.
6. If first index (`Index == 0`): Store the hit location as `VaultStartPos` (Vector variable, category: `Vault`).
7. If not first index: Store as `VaultMiddlePath` (Vector variable, category: `Vault`).
8. After the wall ends, do a **Line Trace by Channel** downward to find the ground:
   - Start: last trace position + forward offset of `80`
   - End: start - `1000` on Z (trace to ground)
   - Store hit location as `VaultLandPos` (Vector variable, category: `Vault`).

#### Phase 3: Validation
1. In the `Vault` function, after the middle path is found:
   - Set `CanWarp` (Boolean) = true **only if** `VaultMiddlePath` has a valid value.
   - (If the middle trace missed, warping will break the animation.)
2. Organize variables into a **Vault** category for cleanliness.

### Step 8: Add Debug Visualization (Optional)
- Use **Draw Debug Sphere** nodes to visualize the three vault points:
  - **Purple:** Start position
  - **Yellow:** Middle path
  - **Blue:** Landing position
- Set duration to `10` for testing. Remove when done.

---

## Part 4: Blueprint — Motion Warping Execution

### Step 9: Create Vault Motion Warp (Custom Event)
1. In `ThirdPersonCharacter` Event Graph, create a **Custom Event** called `VaultMotionWarp`.
   - (Can't use a function because `Play Montage` has a latent/async `On Completed` pin.)

#### Pre-Warp Setup:
1. Check `CanWarp` with a **Branch**. Only proceed if true.
2. Set **Character Movement → Movement Mode** to **Flying** (prevents gravity during vault).
3. Set **Actor Collision** to **false** (prevents colliding with the obstacle mid-vault).

#### Set Motion Warping Targets:
For each of the three warping points, use **Add or Update Warp Target**:

1. **vault_start:**
   - Name: `vault_start` (must match the montage notify name EXACTLY — case-sensitive, no trailing spaces)
   - Location: `VaultStartPos`
   - Rotation: **Get Actor Rotation**

2. **vault_middle:**
   - Name: `vault_middle`
   - Location: `VaultMiddlePath`
   - Rotation: **Get Actor Rotation**

3. **vault_land:**
   - Name: `vault_land`
   - Location: `VaultLandPos`
   - Rotation: **Get Actor Rotation**

> **Critical:** Copy the names directly from the montage notify states. Any mismatch (extra space, wrong case) will silently fail.

#### Play the Montage:
1. Get **Mesh** → **Play Montage** → select the vault montage.
2. On **On Completed**:
   - Set **Movement Mode** back to **Walking**.
   - Re-enable **Actor Collision**.
   - Set `CanWarp` to **false**.
   - Reset `VaultLandPos.Z` to `2000` (prevents stale landing position from being reused if the world changes).

### Step 10: Wire Up the Input
1. In `ThirdPersonCharacter` Event Graph:
   - On **Left Shift** pressed → call the `Vault` function.
   - At the end of the `Vault` function, call `VaultMotionWarp` custom event.
2. Add a **Range Check** before warping:
   - Check that `VaultLandPos.Z` is within `Mesh Location.Z ± 50`.
   - If outside range → don't warp (prevents climbing walls that are too tall or landing underground).

---

## Quick Reference — Key Values

| Setting | Value | Purpose |
|---------|-------|---------|
| Height trace separation | 30 units | Vertical spacing between forward traces |
| Height trace distance | 180 units | How far forward to detect walls |
| Height trace radius | 5 | Thin sphere for precision |
| Distance trace separation | 50 units | Spacing between downward traces |
| Distance trace offset | 100 units (Z) | Start height above the wall |
| Landing trace distance | 80 units forward | How far past the wall to find landing |
| Landing trace depth | 1000 units (Z) | How far down to search for ground |
| Land position reset | 2000 (Z) | Prevents stale data reuse |
| Valid landing range | Mesh.Z ± 50 | Prevents too-tall wall climbs |

---

## Safety Checks (Built Into the System)

1. **Middle path validation:** If the middle trace misses, `CanWarp` stays false → no vault attempt.
2. **Landing range check:** Landing position must be within ±50 units of the player's height → prevents teleporting underground or climbing skyscrapers.
3. **Stale position reset:** Landing position is reset to Z=2000 after each vault → prevents reusing old data if the world changes (e.g., open world streaming).
4. **Collision disabled during vault:** Prevents the character from getting stuck in the obstacle.
5. **Movement mode set to Flying:** Prevents gravity from pulling the character down mid-animation.

---

## Pro Tips

- **Motion Warping names are case-sensitive.** Copy-paste them from the montage notify states to avoid typos.
- **Functions can't use latent nodes** (like Play Montage's On Completed). Use a Custom Event instead for the motion warp execution.
- **Debug visualization** (Draw Debug Sphere) is invaluable during development — enable it, test, then remove.
- **The vault only works for objects the animation goes over and back down.** For walls that are just up (no down slope), you'll need a different vault animation in the future.
- **The three-point system** (start, middle, land) gives smooth interpolation. If you skip the middle point, the character may teleport or fly erratically.

---

## Related

- 📄 Full Transcript: [[03_Vaulting_with_Motion_Warping]]
- ← Previous: [[05_RPG_Tutorial_02_Locomotion_Blendspace]]
- → Next: [[07_RPG_Tutorial_04_Assassinations]]
- 📚 Series: [[_MOC_Step_by_Step_Guides]]
- 📄 Full Transcript: [[06_Damage_and_Stamina]]
