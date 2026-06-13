---
title: "RPG Tutorial #2: Locomotion — Blendspace, Crouching, Procedural Leaning"
source: "https://www.youtube.com/watch?v=WcDj4uZygyE"
video_id: "WcDj4uZygyE"
type: "step-by-step-guide"
series: "Step-by-Step Guides"
episode: 4
tags: [ue5, rpg, locomotion, blendspace, crouching, animation, guide]
---

# Unreal Engine 5 RPG Tutorial Series — #2: Locomotion (Blendspace, Crouching, Procedural Leaning)

**Source:** https://www.youtube.com/watch?v=WcDj4uZygyE
**Duration:** 47:52
**Extracted from:** `Unreal_Engine_5_RPG_Tutorial_Series_-_#2_Locomotion_-_Blendspace,_Crouching_and_Procedural_Leaning!.md`

---

## Prerequisites

- Unreal Engine 5.1+ (third person template, Blueprints only)
- Locomotion animation pack (free from the video description — exported from Lyra template)

---

## Part 1: Project Setup & Import Animations

### Step 1: Create a New UE5 Project
1. Open UE5 → select **Third Person** template.
2. Make sure **Blueprints** is selected (not C++).
3. Set **Content** to Desktop Maximum, **Ray Tracing** off (can change later).
4. Name your project (e.g., `RPG_Tutorial_Series`).

### Step 2: Import Locomotion Animations
1. Download the animation pack from the video description (free Lyra locomotion animations).
2. In the Content Browser, navigate to `Characters/`.
3. Create folder: `RPG_Character` → inside it, create: `Animations`.
4. Drag and drop all downloaded animation files into the Content Browser.
5. In the import dialog:
   - Click **Reset to Default** at the top.
   - Set **Skeleton** to `SK_Mannequin` (the default UE5 mannequin — NOT the UE4 one).
   - Click **Import All**.
6. Save all (`Ctrl+Shift+S`).

### Step 3: Organize Animations
1. Inside the `Animations` folder, create two subfolders:
   - `Locomotion` — move `idle_break` and `unbox_stop` into here
   - `Crouch` — for crouching animations (will use template defaults)

---

## Part 2: Create Locomotion Blendspace

### Step 4: Create a 1D Blendspace for Walk/Run
1. Right-click in the `Locomotion` folder → **Animation → Legacy → Blend Space 1D**.
2. Set skeleton to `SK_Mannequin`. Name it `BS_Locomotion`.
3. Open it. Set the **horizontal axis**:
   - Name: `Speed`
   - Minimum: `0`
   - Maximum: `500` (matches the Character Movement Component's Max Walk Speed)
4. Drag animations from the **Asset Browser** (Window → Asset Browser if not visible):
   - At **0** (left): `In-Place` slow walk animation
   - At **250** (middle): `MM_Walk_Forward`
   - At **500** (right): `MM_Run_Forward`
5. Hold **Ctrl** and drag in the preview to see the speed transition.
6. Save and close.

> **Why not start at idle?** The idle → walk/run transition will be handled in the Animation Blueprint, not the blendspace. Starting with a small speed makes the transition smoother.

---

## Part 3: Animation Blueprint — Locomotion State Machine

### Step 5: Create the Animation Blueprint
1. Right-click in the `Animations` folder → **Animation Blueprint**.
2. Select `SK_Mannequin` skeleton. Name it `ABP_RPG_Character`.
3. Open it.

### Step 6: Create the Locomotion State Machine
1. Right-click in the **AnimGraph** → **State Machine**. Name it `Locomotion`.
2. Double-click to enter it. Create these states and transitions:

#### State: Idle
1. Add state → name it `Idle`.
2. Double-click → find `idle_break` animation → drag it in.
3. Add a **Loop Animation** node and connect it.

#### State: Walk/Run
1. Drag from Idle → create new state `Walk/Run`.
2. Double-click → find your `BS_Locomotion` blendspace → drag it in.
3. Right-click the **Speed** input → **Promote to Variable** (creates a `Speed` variable).

#### Transition: Idle → Walk/Run
1. Double-click the transition arrow.
2. Get the `Speed` variable → check if **Speed > 0**.

#### State: Stop Animation
1. Drag from Walk/Run → create new state `Stop`.
2. Double-click → find `walk_stop` animation → drag it in.
   - **Note:** Using `walk_stop` for both walking and running looks more natural than switching between walk_stop and run_stop.

#### Transition: Walk/Run → Stop
1. Condition: **Speed ≤ 0** (character stopped moving).

#### Transition: Stop → Idle
1. Set to **Automatic Rule Based on Sequence** (auto-transitions when stop animation finishes).

### Step 7: Tune Transition Blends
1. Select the **Idle → Walk/Run** transition:
   - Duration: `0.3`
   - Mode: **Cubic**
2. Select the **Stop → Idle** transition:
   - Duration: `0.4`
   - Mode: **Cubic**

### Step 8: Create Locomotion Cache
1. Go back to the **main AnimGraph**.
2. Drag the `Locomotion` state machine output → create an **Animation Cache** node.
3. Name the cache `Locomotion`. (This saves the animation data for reuse — like a "pen drive" of animation data.)

---

## Part 4: Main State Machine & Jump/Fall

### Step 9: Create the Main State Machine
1. In the main AnimGraph, create a new **State Machine** called `Main`.
2. Add a **Default Slot** to the output pose (this is where animation montages will play).
3. Enter the Main state machine.

#### State: Unarmed Locomotion
1. Create state `Unarmed Locomotion`.
2. Inside, drag in the `Locomotion` cache.
3. This passes the entire locomotion state machine as a single clean node.

### Step 10: Add Jump and Fall States

#### State: Jump
1. In the Main state machine, create state `Jump`.
2. Inside, find and drag in the `jump` animation.

#### State: Fall
1. Create state `Fall`.
2. Inside, find and drag in the `falling` animation.
3. Add **Loop Animation** node (fall loops until landing).

#### State Alias: To Fall
1. Create a **State Alias** called `To Fall` (acts as a shortcut/teleport).
2. Connect it to the Fall state.

#### Transitions from Unarmed Locomotion:
1. **Unarmed Locomotion → To Fall:**
   - Create variable `Is Falling` (Boolean).
   - Condition: `Is Falling == true`
2. **To Fall → Jump:**
   - Create variable `Velocity` (Vector) → split it to get individual axes.
   - Condition: `Is Falling == true AND Velocity.Z > 100`
   - (If moving upward while falling → play jump animation first)
3. **To Fall → Fall:**
   - Condition: `Is Falling == true AND Velocity.Z ≤ 100`
   - (If falling straight down or downward → go directly to fall animation)

#### Transitions back:
1. **Jump → Fall:** Set to **Automatic Rule** (auto-transitions when jump animation completes).
2. **Fall → Land:** Condition: `Is Falling == false`.
3. **Land → Unarmed Locomotion:** Set to **Automatic Rule**.

> **Priority:** Set the transition priority from Jump to Fall to **2** (higher than default) so it takes precedence.

### Step 11: Set Up the Land Animation as Additive
1. Open the **Land** state. Find the `land` animation.
2. The land animation is an **additive** animation (designed to play on top of locomotion).
3. In the Land state's AnimGraph:
   - Add **Apply Additive** node.
   - Set **Base** → the `Locomotion` cache.
   - Set **Additive** → the `land` animation.
   - Set **Alpha** → `1.0`.

### Step 12: Wire Up Variables in Event Graph
1. Go to the **Event Graph** tab in the Animation Blueprint.
2. On **Blueprint Initialization** (Begin Play equivalent):
   - Get **Owner** → **Cast to Third Person Character** → promote to variable `Character`.
   - (Do this once at init, not every frame — cleaner code.)
3. On **Update Animation** (every frame):
   - Get `Character` → **Get Velocity** → **Vector Length** → set `Speed` variable.
   - Get `Character` → **Character Movement** → **Is Falling** → set `Is Falling` variable.
   - Get `Character` → **Get Velocity** → set `Velocity` variable.
4. Add comments: `Get Speed and Velocity`, `Is Falling`.

### Step 13: Assign Animation Blueprint to Character
1. Open `ThirdPersonCharacter` Blueprint.
2. Select the **Mesh** component → in Details, set **Animation Class** to `ABP_RPG_Character`.
3. Compile and save.

---

## Part 5: Crouching

### Step 14: Create Crouch Blendspace
1. In the `Crouch` folder, right-click → **Animation → Legacy → Blend Space 1D**.
2. Name it `BS_Crouch`.
3. Set axis: Name `Speed`, Min `0`, Max `350` (crouch is slower than walking).
4. Drag animations:
   - At **0**: Crouch idle
   - At **350**: Crouch walk
5. **Important:** If the crouch walk animation has **root motion**, open the animation → enable **Root Motion** → set to **Force Root Lock** (keeps it in place).

### Step 15: Create Crouch State Machine
1. In the Animation Blueprint's main AnimGraph, create a new **State Machine** called `Crouch`.
2. Create a **Cache Pose** node called `Crouch`.
3. Enter the Crouch state machine:
   - Create state `Crouch Locomotion`.
   - Inside, drag in `BS_Crouch` and connect the `Speed` variable.

### Step 16: Add Crouch to Main State Machine
1. In the **Main** state machine, create state `Crouch Locomotion`.
2. Inside, drag in the `Crouch` cache.

#### Transitions:
1. **Unarmed Locomotion → Crouch Locomotion:**
   - Create variable `Is Crouched` (Boolean).
   - Condition: `Is Crouched == true`
2. **Crouch Locomotion → Unarmed Locomotion:**
   - Condition: `Is Crouched == false`

### Step 17: Set Up Crouch Input
1. Open `ThirdPersonCharacter` Blueprint → **Event Graph**.
2. Create Input Action: `IA_Crouch` (Content → Third Person → Input Actions).
3. Add to **IMC_Default** mapping context → bind to **Left Ctrl** key.
4. Add logic:
   - On `IA_Crouch` pressed → **FlipFlop** node:
     - **A:** Set `Is Crouched` = true, Set Max Walk Speed = `350`
     - **B:** Set `Is Crouched` = false, Set Max Walk Speed = `500`
5. In the Animation Blueprint's Event Graph, read `Character` → get `Is Crouched` variable → set the local `Is Crouched`.

### Step 18: Camera Pullback on Crouch
1. In `ThirdPersonCharacter` Blueprint:
   - On crouch: Set **Camera Boom Arm Length** to `550` (pulls camera further back)
   - On uncrouch: Set it back to `400`
2. To make it smooth, add a **Timeline** node:
   - Create `CrouchCamDistance` timeline.
   - Add a **Float Track** called `CamLength`.
   - Set duration: `1 second`.
   - Add key at time `0`, value `0` and time `1`, value `1`.
   - Connect **Play from Start** to the crouch action.
   - Connect **Reverse from Start** to the uncrouch action.
3. Use a **Lerp (Float)** node:
   - A: `400` (normal arm length)
   - B: `550` (crouched arm length)
   - Alpha: Timeline output
   - Result → Set Camera Boom Arm Length.

---

## Part 6: Procedural Leaning

### Step 19: Create Lean Animations
1. Copy (don't move) the `MM_Run_Forward` animation into a new `Lean` folder.
2. Duplicate it → name copies `Lean_Left` and `Lean_Right`.
3. Edit `Lean_Left`:
   - Open it → pause at frame 0.
   - Set **Additive** settings:
     - Additive Type: **Mesh Space**
     - Post Type: **Scaled**
     - Base Pose Animation: `MM_Run_Forward` (the original)
   - In the **Skeleton Tree**, select the **Pelvis** bone (not root).
   - Enable **Rotation Snapping** at **10 degrees**.
   - Rotate the pelvis **-10 degrees** on the roll axis (lean left).
   - Click the **+** button to add a keyframe. Save.
4. Edit `Lean_Right`:
   - Same process, but rotate **+10 degrees** (lean right).

### Step 20: Create Lean Blendspace
1. Right-click → **Animation → Legacy → Blend Space 1D**.
2. Name it `BS_Lean`.
3. Set axis: Name `LeanValue`, Min `-45`, Max `45`.
4. Drag animations:
   - At **-45** (left): `Lean_Left`
   - At **45** (right): `Lean_Right`
5. Hold **Ctrl** to preview the lean transition. Save.

### Step 21: Apply Lean in Animation Blueprint
1. In the **Locomotion** state machine, open the **Walk/Run** state.
2. Add **Apply Additive (Mesh Space)** node:
   - **Base:** The locomotion blendspace output
   - **Additive:** `BS_Lean` blendspace
   - **Alpha:** `1.0`
3. Right-click the `LeanValue` input → **Promote to Variable** → name it `YawDelta`.
4. **Important:** Multiply the `YawDelta` by **-1** before passing it in (inverts the lean direction to match the turn).

### Step 22: Calculate Lean Value in Event Graph
1. In the Animation Blueprint **Event Graph** (Update Animation):
2. Get `Character` → **Get Actor Rotation**.
3. Create variable `LastFrameRotation` (Rotator).
4. Calculate: `Delta Rotation = Current Rotation - Last Frame Rotation`.
5. Split the delta rotator → get the **Yaw** component.
6. Divide by **Delta Time** → then divide by **Lean Intensity** (value: `10`).
7. Use **FInterp To** to smooth the value:
   - Target: calculated lean value
   - Current: current `YawDelta`
   - Interp Speed: `10`
   - Delta Time: event delta time
8. Set the result to the `YawDelta` variable.
9. Update `LastFrameRotation` with the current rotation.
10. Comment this section: `Calculate Lean`.

### Step 23: Customize Character Appearance (Optional)
1. Duplicate the Manny materials → create `_blue` versions.
2. Enable **Tint** on the material → set a blue color → copy the hex value.
3. Apply the same tint to both material instances.
4. In the character Blueprint, assign the blue materials to the mesh.

---

## Quick Reference — Key Values

| Setting | Value | Location |
|---------|-------|----------|
| Max Walk Speed (normal) | 500 | Character Movement Component |
| Max Walk Speed (crouch) | 350 | Character Movement Component |
| Blendspace Max Speed | 500 | BS_Locomotion axis |
| Crouch Blendspace Max | 350 | BS_Crouch axis |
| Lean Intensity Divider | 10 | Animation Blueprint Event Graph |
| Lean Interp Speed | 10 | Animation Blueprint Event Graph |
| Camera Boom (normal) | 400 | Camera Boom Arm Length |
| Camera Boom (crouch) | 550 | Camera Boom Arm Length |
| Transition Duration (Idle→Walk) | 0.3s | Transition settings |
| Transition Duration (Stop→Idle) | 0.4s | Transition settings |
| Crouch Camera Timeline | 1s | Timeline node |

---

## Pro Tips

- **Save constantly** (`Ctrl+Shift+S`). UE5 can crash unexpectedly.
- **Cache Poses** keep your AnimGraph clean — use them to organize state machines into single nodes.
- **Automatic Rule transitions** fire when an animation completes — use them for one-shot animations like stop and land.
- **Root Motion:** If a crouch walk animation moves the character through root motion, enable **Root Motion** → **Force Root Lock** to keep it in place.
- **State Aliases** are shortcuts — they let you connect transitions to distant states without spaghetti wires.
- **Transition Priority:** If multiple transitions could fire simultaneously, higher priority numbers take precedence.
- **Additive Animations** play on top of base animations — use them for landing, leaning, and hit reactions.
- **Procedural Lean** values (intensity 10, interp speed 10) work well as defaults but feel free to tweak for your game's feel.

---

## Related

- 📄 Full Transcript: [[02_Locomotion_Blendspace_Crouching_and_Procedural_Leaning]]
- ← Previous: [[03_Optimizing_Your_Unreal_Engine_Game]]
- → Next: [[05_RPG_Tutorial_03_Vaulting_Motion_Warping]]
- 📚 Series: [[_MOC_Step_by_Step_Guides]]
- 📄 Full Transcript: [[05_Player_Stats_Health_Stamina_and_XP]]
