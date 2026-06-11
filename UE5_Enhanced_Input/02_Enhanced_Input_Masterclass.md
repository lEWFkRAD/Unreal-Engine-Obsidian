---
title: "Unreal Engine 5 Enhanced Input Tutorial Masterclass for Beginners"
source: "https://www.youtube.com/watch?v=RBCLAWMWyDw"
video_id: "RBCLAWMWyDw"
type: "youtube-summary"
series: "UE5 Enhanced Input"
episode: 2
tags: [ue5, enhanced-input, beginner, masterclass, input-mapping]
---

# UE5 Enhanced Input Tutorial Masterclass for Beginners

**Duration:** 2:20:53 | **Creator:** UNF Games | **Source:** YouTube

## Overview

This comprehensive masterclass covers the Enhanced Input system from scratch, aimed at beginners who want a thorough understanding of UE5's input handling. The tutorial walks through the full workflow from creating input assets to binding them in gameplay.

## What is Enhanced Input?

Enhanced Input is UE5's replacement for the legacy input system. It provides:
- **Asset-driven** input configuration (no more Project Settings > Input)
- **Runtime remapping** — change what keys do based on game state
- **Input processing pipeline** — modifiers and triggers for complex behavior
- **Multiple value types** — bool, float, 2D, 3D vectors

## Step-by-Step Implementation

### Phase 1: Project Setup

1. Create a new UE5 project (Third Person template recommended)
2. Verify Enhanced Input is enabled: Edit → Plugins → "Enhanced Input"
3. In Project Settings → Input → Default Classes:
   - Default Player Input Class: `EnhancedPlayerInput`
   - Default Input Component Class: `EnhancedInputComponent`

### Phase 2: Creating Input Actions

For each player action, create an Input Action asset:

```
Content Browser → Right-click → Input → Input Action

Create these actions:
  IA_Move      (Value Type: Axis2D)  — WASD / Left Stick
  IA_Look      (Value Type: Axis2D)  — Mouse / Right Stick
  IA_Jump      (Value Type: Bool)    — Space / Gamepad A
  IA_Fire      (Value Type: Bool)    — LMB / Right Trigger
  IA_Sprint    (Value Type: Bool)    — Left Shift / Left Stick Button
  IA_Interact  (Value Type: Bool)    — E / Gamepad X
```

### Phase 3: Creating Input Mapping Context

```
Content Browser → Right-click → Input → Input Mapping Context
Name: IMC_Default

Add mappings:
  IA_Move:
    - W key → Modifiers: Swizzle YXZ (maps W to positive Y)
    - S key → Modifiers: Negate + Swizzle YXZ (maps S to negative Y)
    - A key → Modifiers: Negate (maps A to negative X)
    - D key → no modifiers (maps D to positive X)
    - Gamepad Left Thumbstick 2D → no modifiers

  IA_Look:
    - Mouse XY 2D-Axis → no modifiers
    - Gamepad Right Thumbstick 2D → Scalar (sensitivity)

  IA_Jump:
    - Space Bar → no modifiers
    - Gamepad Face Button Bottom (A)

  IA_Fire:
    - Left Mouse Button
    - Gamepad Right Trigger

  IA_Sprint:
    - Left Shift
    - Gamepad Left Thumbstick Button
```

### Phase 4: Adding Context to Character

In your Character Blueprint (or C++):

**Blueprint approach:**
1. Event BeginPlay
2. Get Player Controller
3. Get Enhanced Input Local Player Subsystem
4. Call "Add Mapping Context"
   - Mapping Context: IMC_Default
   - Priority: 0

**C++ approach:**
```cpp
void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    if (APlayerController* PC = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = 
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }
}
```

### Phase 5: Binding Actions

**Blueprint:**
- In Event Graph, right-click and type the action name
- Select "Enhanced Input Action [ActionName]"
- Choose event: Triggered, Ongoing, Completed, Canceled
- Wire up your logic

**C++:**
```cpp
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    
    EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
    EIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
    EIC->BindAction(IA_Jump, ETriggerEvent::Started, this, &ACharacter::Jump);
    EIC->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &AMyCharacter::Fire);
}

void AMyCharacter::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();
    
    FRotator Rotation = Controller->GetControlRotation();
    FRotator YawRotation(0, Rotation.Yaw, 0);
    
    FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
    
    AddMovementInput(ForwardDirection, MovementVector.Y);
    AddMovementInput(RightDirection, MovementVector.X);
}
```

### Phase 6: Dynamic Context Swapping

A key advantage of Enhanced Input — change inputs based on gameplay state:

```cpp
// When entering a vehicle
Subsystem->RemoveMappingContext(OnFootMappingContext);
Subsystem->AddMappingContext(DrivingMappingContext, 0);

// When entering a menu
Subsystem->AddMappingContext(MenuMappingContext, 1); // Higher priority
```

## Trigger Types Reference

| Trigger | Behavior |
|---------|----------|
| Down | Active every frame while held |
| Pressed | Fires once on initial press |
| Released | Fires once on release |
| Hold | Fires after holding for specified duration |
| Tap | Fires if released before hold threshold |
| Chorded | Fires only when another action is also active |

## Common Pitfalls

1. **Forgetting to add Mapping Context** — Actions won't fire without it
2. **Wrong Value Type** — Axis2D actions need proper modifiers for WASD
3. **Priority conflicts** — Higher priority contexts override lower ones for same keys
4. **Not enabling the plugin** — Enhanced Input must be enabled in Plugins

## Additional Resources

- [UNF Games Action Game Course](https://www.unfgames.com/action-game)
- [Epic's Enhanced Input Documentation](https://dev.epicgames.com/documentation/unreal-engine/enhanced-input-in-unreal-engine)


---

## Related

- ← Previous: [[01_Enhanced_Input_System_Tutorial]]
- → Next: [[03_Enhanced_Input_Hold_To_Interact]]
- 📚 Series: [[_MOC_UE5_Enhanced_Input]]
