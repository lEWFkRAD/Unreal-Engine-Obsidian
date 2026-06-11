---
title: "RPG Tutorial #5: Player Stats — Health, Stamina, XP"
source: "https://www.youtube.com/watch?v=2YEZpSrdHfk"
video_id: "2YEZpSrdHfk"
type: "step-by-step-guide"
series: "Step-by-Step Guides"
episode: 8
tags: [ue5, rpg, player-stats, health, stamina, xp, guide]
---

# Unreal Engine 5 RPG Tutorial Series — #5: Player Stats (Health, Stamina, XP)

**Source:** https://www.youtube.com/watch?v=2YEZpSrdHfk
**Duration:** 33:50
**Extracted from:** `Unreal_Engine_5_RPG_Tutorial_Series_-_#5_Player_Stats_-_Health,_Stamina_and_XP.md`

---

## Prerequisites

- Completed Episode #4 (Assassinations)
- Understanding of Blueprint components and functions

---

## Part 1: Create the Player Stats Component

### Step 1: Create the Component Blueprint
1. In `Blueprints/`, create a new **Actor Component** Blueprint: `BPC_PlayerStats`.
2. Open it.

### Step 2: Define Variables
Create these variables with default values:

| Variable | Type | Default | Category |
|----------|------|---------|----------|
| `CurrentHealth` | Float | 100 | Health |
| `MaxHealth` | Float | 100 | Health |
| `CurrentStamina` | Float | 100 | Stamina |
| `MaxStamina` | Float | 100 | Stamina |
| `XP` | Float | 0 | XP |
| `MaxXP` | Float | 100 | XP |
| `Level` | Integer | 1 | XP |

Organize each variable into its category for cleanliness.

---

## Part 2: Health Functions

### Step 3: Decrease Health
1. Create function `DecreaseHealth`.
2. Add input: `Damage` (Float).
3. Add output: `IsPlayerDead` (Boolean).
4. Logic:
   - Set `CurrentHealth` = `CurrentHealth - Damage`
   - **Branch:** Is `CurrentHealth <= 0`?
     - **True:** Set `IsPlayerDead` = true (player died)
     - **False:** Set `IsPlayerDead` = false
5. Update the HUD health bar: `HealthBar->SetPercent(CurrentHealth / MaxHealth)`
6. Update the HUD health text: `HealthText->SetText(CurrentHealth)`

> **Important:** Divide `CurrentHealth` by `MaxHealth` before setting the percent — progress bars use 0-1 range, not raw values.

### Step 4: Increase Health (Heal)
1. Create function `IncreaseHealth`.
2. Add input: `AddedHealth` (Float).
3. Logic:
   - Set `CurrentHealth` = `CurrentHealth + AddedHealth`
   - **Branch:** Is `CurrentHealth >= MaxHealth`?
     - **True:** Set `CurrentHealth` = `MaxHealth` (cap at max)
     - **False:** Keep the calculated value
4. Update HUD (same as DecreaseHealth).

### Step 5: Increase Max Health (Level Up)
1. Create function `IncreaseMaxHealth`.
2. Add input: `HealthIncrement` (Float).
3. Logic:
   - Set `MaxHealth` = `MaxHealth + HealthIncrement`
   - Optionally set `CurrentHealth` = `MaxHealth` (full heal on level up)
   - Or leave `CurrentHealth` unchanged (player must heal naturally)
4. Update HUD.

---

## Part 3: Stamina Functions

### Step 6: Decrease Stamina
1. Create function `DecreaseStamina`.
2. Add input: `StaminaDepleted` (Float).
3. Add output: `StaminaLeft` (Boolean).
4. Logic:
   - Set `CurrentStamina` = `CurrentStamina - StaminaDepleted`
   - **Branch:** Is `CurrentStamina <= 0`?
     - **True:** Set `StaminaLeft` = false (can't run/attack)
     - **False:** Set `StaminaLeft` = true
5. Update HUD stamina bar: `StaminaBar->SetPercent(CurrentStamina / MaxStamina)`

### Step 7: Increase Stamina (Recover)
1. Create function `IncreaseStamina`.
2. Add input: `AddedStamina` (Float).
3. Logic:
   - Set `CurrentStamina` = `CurrentStamina + AddedStamina`
   - **Branch:** Is `CurrentStamina >= MaxStamina`?
     - **True:** Set `CurrentStamina` = `MaxStamina`
     - **False:** Keep calculated value
4. Update HUD.

### Step 8: Increase Max Stamina (Level Up)
1. Create function `IncreaseMaxStamina`.
2. Add input: `AddedStamina` (Float).
3. Logic:
   - Set `MaxStamina` = `MaxStamina + AddedStamina`
4. Update HUD.

---

## Part 4: HUD Widget

### Step 9: Create the HUD Widget
1. In `UI/`, create a Widget Blueprint: `WGWB_MainHUD`.
2. Open it. Add a **Canvas Panel**.

#### Health Bar
1. Drag a **Progress Bar** onto the canvas.
2. Settings:
   - Anchors: Bottom center
   - Position: X=0, Y offset = `-100` (above bottom edge)
   - Size: X=`500`, Y=`20`
   - Alignment: X=0.5, Y=0.5 (centered)
3. Set **Fill Color** to red.
4. Set preview **Percent** to `0.7` for visualization.
5. Rename to `HealthBar`. Check **Is Variable**.

#### Stamina Bar
1. Duplicate `HealthBar` → rename to `StaminaBar`.
2. Adjust:
   - Position Y offset: `-70` (below health bar)
   - Size Y: `10` (thinner than health)
   - Fill Color: yellow/gold
3. Check **Is Variable**.

#### Health Text
1. Add a **Text** block on top of the health bar.
2. Settings:
   - Anchors: Bottom center
   - Alignment: 0.5, 0.5
   - Font size: 10
   - Justification: Center
3. Set preview text to `70` (shows how it'll look).
4. Rename to `HealthText`. Check **Is Variable**.

### Step 10: Display the HUD
1. In `ThirdPersonCharacter` → **Event BeginPlay**:
   - **Create Widget** → select `WGWB_MainHUD`
   - **Owning Player** = Get Player Controller
   - Promote return to variable `HUDWidget`
   - **Add to Viewport**
2. Comment: `Create Widget`

### Step 11: Add the Component to the Player
1. In `ThirdPersonCharacter`, add component: `BPC_PlayerStats`.
2. You'll see all the variables in the Details panel.

---

## Part 5: Wire Up UI Updates

### Step 12: Update HUD from Component Functions
In each function of `BPC_PlayerStats`, after modifying values:

1. Get **Owner** → **Cast to ThirdPersonCharacter** → get `HUDWidget`
2. From the HUD widget, get the appropriate bar/text and set the new value.

**Optimization:** Do the cast once in **Event Graph** → **BeginPlay**:
- Get Owner → Cast to ThirdPersonCharacter → promote to variable `PlayerCharacter`
- This avoids casting in every function.

### Step 13: Initialize HUD on Game Start
In `BPC_PlayerStats` → Event Graph → BeginPlay:
1. Get `PlayerCharacter` → get `HUDWidget`
2. Set `HealthBar->SetPercent(CurrentHealth / MaxHealth)`
3. Set `HealthText->SetText(CurrentHealth)`
4. Set `StaminaBar->SetPercent(CurrentStamina / MaxStamina)`

This ensures the HUD shows correct values from the start.

---

## Part 6: Debug Testing

### Step 14: Add Debug Keys
In `ThirdPersonCharacter` Event Graph, add **Debug Key** nodes:
- **Key 1:** Call `DecreaseHealth(10)` — test damage
- **Key 2:** Call `IncreaseHealth(10)` — test healing
- **Key 3:** Call `IncreaseMaxHealth(10)` — test level up health
- **Key 4:** Call `DecreaseStamina(10)` — test stamina drain
- **Key 5:** Call `IncreaseStamina(10)` — test stamina recovery

Remove these when done testing.

---

## Quick Reference — Key Values

| Setting | Value | Notes |
|---------|-------|-------|
| Health/MaxHealth default | 100 | Customizable |
| Stamina/MaxStamina default | 100 | Customizable |
| MaxXP default | 100 | XP needed to level up |
| Level default | 1 | Starting level |
| Health bar width | 500 | Assassin's Creed style |
| Health bar height | 20 | |
| Stamina bar height | 10 | Thinner than health |
| Progress bar range | 0-1 | Divide value by max |

---

## Pro Tips

- **Progress bars use 0-1 range.** Always divide your value by the max value before setting percent.
- **Components keep Blueprints clean.** Player stats in a separate component = organized main character Blueprint.
- **Cast once, use many.** Do the Owner → Cast in BeginPlay and store as a variable. Don't cast in every function.
- **Don't bind widget values.** Instead of tick-based bindings, update the HUD only when values change — more performant and more control.
- **Debug keys** are essential during development. Add them, test, remove them.
- **Negative health edge case:** The decrease health function can go negative. Fix by clamping or checking before subtracting (addressed in next episode).

---

## Related

- 📄 Full Transcript: [[05_Player_Stats_Health_Stamina_and_XP]]
- ← Previous: [[07_RPG_Tutorial_04_Assassinations]]
- → Next: [[09_RPG_Tutorial_06_Damage_and_Stamina]]
- 📚 Series: [[_MOC_Step_by_Step_Guides]]
- 📄 Full Transcript: [[08_Sounds_and_UI]]
