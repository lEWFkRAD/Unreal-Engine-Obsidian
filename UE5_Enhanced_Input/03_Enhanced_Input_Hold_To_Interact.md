---
title: "Enhanced Input Part 2: Hold to Interact"
source: "https://www.youtube.com/watch?v=8Dnc9KtMkss"
video_id: "8Dnc9KtMkss"
type: "youtube-summary"
series: "UE5 Enhanced Input"
episode: 3
tags: [ue5, enhanced-input, hold-interact, triggers, modifiers]
---

# Enhanced Input Part 2: Hold to Interact

**Duration:** 9:45 | **Creator:** Ryan Laley | **Published:** January 31, 2024

## Overview

This tutorial is Part 2 of Ryan Laley's Enhanced Input series. It focuses on implementing a **"Hold to Interact"** mechanic — where the player must hold a button for a duration to trigger an interaction (e.g., opening a chest, picking up an item, hacking a terminal).

## Series Context

- **Part 1:** [Enhanced Input Action Part 1: Getting Started](https://www.youtube.com/watch?v=LEMvJBzjnxI) — Overview of Input Actions, Mappings, and Contexts
- **Part 2:** This video — Hold to Interact
- **Part 3:** [Chorded Action](https://www.youtube.com/watch?v=TeVteh8Xmjk) — Combining multiple inputs

## Implementation: Hold to Interact

### Step 1: Create the Input Action

```
Content Browser → Right-click → Input → Input Action
Name: IA_Interact
Value Type: Bool
```

### Step 2: Configure the Hold Trigger in Mapping Context

Open your Input Mapping Context (e.g., `IMC_Default`):

1. Add `IA_Interact` and map it to the **E key**
2. In the **Triggers** array for this mapping, add `UInputTriggerHold`
3. Configure the Hold trigger:
   - **Hold Time Threshold:** 1.5 seconds (adjust as needed)
   - **Is One Shot:** true (fires once after duration, not repeatedly)

### Step 3: Handle Trigger Events in Blueprint

The Hold trigger fires different event types:

```
ETriggerEvent::Started    → Player started holding (show progress bar)
ETriggerEvent::Ongoing    → Still holding (update progress bar)
ETriggerEvent::Triggered  → Hold complete! (perform interaction)
ETriggerEvent::Canceled   → Released too early (hide progress bar)
```

**Blueprint Setup:**
1. In Character Blueprint Event Graph
2. Right-click → "Enhanced Input Action IA_Interact"
3. For **Started** event: Show interaction widget / start progress animation
4. For **Ongoing** event: Update progress bar (use `GetTriggeredTime` or elapsed)
5. For **Triggered** event: Execute the interaction logic
6. For **Canceled** event: Hide widget / reset progress

### Step 4: C++ Implementation

```cpp
// In SetupPlayerInputComponent
EIC->BindAction(IA_Interact, ETriggerEvent::Started, this, &AMyCharacter::InteractStarted);
EIC->BindAction(IA_Interact, ETriggerEvent::Ongoing, this, &AMyCharacter::InteractOngoing);
EIC->BindAction(IA_Interact, ETriggerEvent::Triggered, this, &AMyCharacter::InteractComplete);
EIC->BindAction(IA_Interact, ETriggerEvent::Canceled, this, &AMyCharacter::InteractCanceled);

void AMyCharacter::InteractStarted(const FInputActionValue& Value)
{
    // Show interaction UI widget
    InteractionWidget->SetVisibility(ESlateVisibility::Visible);
    InteractionWidget->SetProgress(0.0f);
}

void AMyCharacter::InteractOngoing(const FInputActionValue& Value)
{
    // Update progress bar
    // The trigger's elapsed time / hold time = progress percentage
    float Progress = GetElapsedTime() / HoldDuration;
    InteractionWidget->SetProgress(Progress);
}

void AMyCharacter::InteractComplete(const FInputActionValue& Value)
{
    // Perform the interaction
    InteractionWidget->SetVisibility(ESlateVisibility::Hidden);
    if (CurrentInteractable)
    {
        CurrentInteractable->Interact(this);
    }
}

void AMyCharacter::InteractCanceled(const FInputActionValue& Value)
{
    // Released too early — hide widget
    InteractionWidget->SetVisibility(ESlateVisibility::Hidden);
    InteractionWidget->SetProgress(0.0f);
}
```

### Step 5: Interaction Widget (Optional UI)

Create a Widget Blueprint (`WBP_InteractProgress`) with:
- A Text block: "Hold [E] to Interact"
- A Progress Bar bound to a float variable `Progress`
- A Canvas Panel for positioning above the interactable

## Advanced Extensions

### Dynamic Hold Duration
Different interactables may require different hold times:

```cpp
// Approach: Use a custom trigger that reads from the interactable
// Or: Set the trigger's HoldTimeThreshold dynamically
UInputTriggerHold* HoldTrigger = /* get reference to trigger */;
HoldTrigger->HoldTimeThreshold = CurrentInteractable->GetHoldDuration();
```

### Dual-Binding (Tap vs Hold)
One button performing different actions based on hold duration:
- Use **Tap** trigger for quick press action
- Use **Hold** trigger for held action
- Both map to the same key but different Input Actions

### Combining with Chorded Actions
Require holding one button while pressing another (covered in Part 3).

## Common Issues

1. **UE 5.7 compatibility:** The `BP_ThirdPersonCharacter` Event Graph differs — may need to adjust widget visibility setup
2. **Widget not appearing:** Ensure the widget is added to viewport in the correct event
3. **Hold not firing:** Check that the Hold trigger is added in the Mapping Context, not the Input Action

## Related Resources

- [Input Combos Tutorial](https://www.youtube.com/watch?v=wa2JbNYjC0w) (Haez)
- [Why Use Interfaces & Event Dispatchers](https://www.youtube.com/watch?v=EQfml2D9hwE) (Ali Elzoheiry)
- [Ryan Laley's Discord](https://discord.gg/TcPtCBp)


---

## Related

- ← Previous: [[02_Enhanced_Input_Masterclass]]
- 📚 Series: [[_MOC_UE5_Enhanced_Input]]
