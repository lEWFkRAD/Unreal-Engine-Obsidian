---
title: "UPROPERTY and UFUNCTION Macros - Specifiers Deep Dive"
source: "https://www.youtube.com/watch?v=T2_AaJqR2uk"
video_id: "T2_AaJqR2uk"
type: "youtube-summary"
series: "UE5 C++"
episode: 3
tags: [ue5, cpp, uproperty, ufunction, specifiers, macros, blueprint, networking]
---

# UPROPERTY and UFUNCTION Macros - Specifiers Deep Dive

**Channel:** (UE5 Learning) | **Duration:** ~12:00

## Overview

A deep dive into `UPROPERTY` and `UFUNCTION` specifiers — the brackets inside the macros that control how your variables and functions behave in the editor, blueprints, and networking.

---

## UPROPERTY Specifiers

`UPROPERTY()` exposes variables to Unreal's reflection system. The specifiers you pass control *how* they're exposed.

### Basic Visibility

```cpp
// Editable in the Details panel (both class defaults and placed instances)
UPROPERTY(EditAnywhere)
float MyFloat;

// Visible in Details panel but NOT editable
UPROPERTY(VisibleAnywhere)
float DebugValue;
```

### Blueprint Access

```cpp
// Read-only in blueprints (can GET but not SET)
UPROPERTY(EditAnywhere, BlueprintReadOnly)
float MaxHealth;

// Read-write in blueprints (can GET and SET)
UPROPERTY(EditAnywhere, BlueprintReadWrite)
float CurrentHealth;
```

### Edit Scope

```cpp
// Editable ONLY in the class defaults (Blueprint editor), NOT on placed instances
UPROPERTY(EditDefaultsOnly)
float MaxSpeed;

// Editable ONLY on placed instances in the level, NOT in class defaults
UPROPERTY(EditInstanceOnly)
float Speed;
```

**Use case:**
- `EditDefaultsOnly` — values that should be the same for all instances (e.g., max health)
- `EditInstanceOnly` — values unique per instance (e.g., patrol speed for a specific enemy)

### Category (Organization)

```cpp
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
float MaxHealth;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
float CurrentHealth;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
float AttackDamage;
```

This creates collapsible sections in the Details panel:
```
▼ Health
    Max Health:     [100.0]
    Current Health: [100.0]
▼ Combat
    Attack Damage:  [25.0]
```

### Combining Specifiers

You can combine multiple specifiers freely:

```cpp
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
float CurrentHealth;

UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug")
int32 DebugCounter;
```

### Networking

```cpp
// Replicated across network (server → client)
UPROPERTY(Replicated)
float Health;

// Replicated with a callback when value changes
UPROPERTY(ReplicatedUsing = OnRep_Health)
float Health;

UFUNCTION()
void OnRep_Health();
```

### Full Example — Health Component

```cpp
UCLASS()
class AMyCharacter : public ACharacter
{
    GENERATED_BODY()

protected:
    // Editable in defaults only, read-only in blueprints
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
    float MaxHealth = 100.0f;

    // Editable anywhere, full blueprint access
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    float CurrentHealth;

    // Visible for debugging, cannot be changed
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
    bool bIsDead = false;
};
```

---

## UFUNCTION Specifiers

`UFUNCTION()` exposes functions to Unreal's reflection system.

### BlueprintCallable

Makes the function callable from blueprints. It appears as a node with execution pins.

```cpp
UFUNCTION(BlueprintCallable, Category = "Actions")
void Attack();

UFUNCTION(BlueprintCallable, Category = "Actions")
void Heal(float Amount);
```

### BlueprintPure

Makes the function callable from blueprints **without execution pins**. Ideal for getters and calculations that don't have side effects.

```cpp
UFUNCTION(BlueprintPure, Category = "Stats")
float GetHealthPercent() const
{
    return CurrentHealth / MaxHealth;
}
```

In blueprints, this appears as a compact node you can drag into any pin — no execution wire needed.

**Difference in behavior:**
- `BlueprintCallable` — has execution flow; won't run unless connected to the execution chain
- `BlueprintPure` — no execution flow; evaluates whenever its output is needed

### BlueprintNativeEvent

Allows the function to be **implemented in both C++ and Blueprints**. The C++ version is the default; blueprints can override it.

```cpp
// Header
UFUNCTION(BlueprintNativeEvent, Category = "Combat")
void OnDeath();

// CPP — rename to _implementation
void AMyCharacter::OnDeath_Implementation()
{
    // Default C++ behavior
    UE_LOG(LogTemp, Warning, TEXT("Character died in C++"));
    Destroy();
}
```

In a Blueprint child:
1. Open the Blueprint → Functions → Override → select `OnDeath`
2. Add your custom logic
3. Right-click → "Add Call to Parent Function" to also run the C++ code

### BlueprintImplementableEvent

Function **must be implemented in Blueprints** — no C++ body needed.

```cpp
// Header only — no CPP implementation
UFUNCTION(BlueprintImplementableEvent, Category = "Events")
void OnLevelUp(int32 NewLevel);
```

In Blueprint, you implement this as an event. C++ code can call it:

```cpp
void AMyCharacter::AddExperience(int32 XP)
{
    CurrentXP += XP;
    if (CurrentXP >= NextLevelXP)
    {
        CurrentLevel++;
        OnLevelUp(CurrentLevel);  // Calls the Blueprint implementation
    }
}
```

### Networking Specifiers

```cpp
// Only executes on the server
UFUNCTION(Server, Reliable, WithValidation)
void ServerFire();

// Only executes on the owning client
UFUNCTION(Client, Reliable)
void ClientUpdateHUD();

// Executes on all clients
UFUNCTION(NetMulticast, Unreliable)
void MulticastPlayEffect();
```

---

## Quick Reference Table

### UPROPERTY Specifiers

| Specifier | Effect |
|-----------|--------|
| `EditAnywhere` | Editable in defaults AND instances |
| `EditDefaultsOnly` | Editable only in class defaults |
| `EditInstanceOnly` | Editable only on placed instances |
| `VisibleAnywhere` | Visible but not editable |
| `BlueprintReadOnly` | Can read in BP, cannot set |
| `BlueprintReadWrite` | Can read and write in BP |
| `Category = "Name"` | Organize in Details panel |
| `Replicated` | Sync across network |
| `meta = (AllowPrivateAccess = "true")` | Expose private members |

### UFUNCTION Specifiers

| Specifier | Effect |
|-----------|--------|
| `BlueprintCallable` | Call from blueprints (has execution pins) |
| `BlueprintPure` | Call from blueprints (no execution pins) |
| `BlueprintNativeEvent` | C++ default + BP override |
| `BlueprintImplementableEvent` | BP-only implementation |
| `Server` | Execute on server only |
| `Client` | Execute on owning client only |
| `NetMulticast` | Execute on all clients |
| `Reliable` | Guaranteed delivery (networking) |
| `Unreliable` | May be dropped (networking) |
| `Category = "Name"` | Organize in Blueprint palette |

---

## Practical Example — Complete Actor

```cpp
// MyEnemy.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyEnemy.generated.h"

UCLASS()
class AMyEnemy : public AActor
{
    GENERATED_BODY()

public:
    AMyEnemy();

    // --- UPROPERTY examples ---

    // Editable anywhere, organized under "Stats"
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float Health = 100.0f;

    // Only editable in class defaults (not per-instance)
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
    float MaxHealth = 100.0f;

    // Visible for debugging, not editable
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug")
    bool bIsAlive = true;

    // Editable only on placed instances
    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI")
    float PatrolSpeed = 300.0f;

    // --- UFUNCTION examples ---

    // Callable from blueprints with execution pins
    UFUNCTION(BlueprintCallable, Category = "Combat")
    void TakeDamage(float Amount);

    // Pure function — no execution pins (getter)
    UFUNCTION(BlueprintPure, Category = "Stats")
    float GetHealthPercent() const;

    // C++ default implementation, overridable in blueprints
    UFUNCTION(BlueprintNativeEvent, Category = "Events")
    void OnDeath();

    // Must be implemented in blueprints
    UFUNCTION(BlueprintImplementableEvent, Category = "Events")
    void OnDamageReceived(float DamageAmount);

protected:
    virtual void BeginPlay() override;

    // Private but exposed to editor via meta
    UPROPERTY(EditAnywhere, Category = "Config",
        meta = (AllowPrivateAccess = "true"))
    float DetectionRange = 500.0f;
};
```

```cpp
// MyEnemy.cpp
#include "MyEnemy.h"

AMyEnemy::AMyEnemy()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMyEnemy::BeginPlay()
{
    Super::BeginPlay();
    Health = MaxHealth;
}

void AMyEnemy::TakeDamage(float Amount)
{
    Health -= Amount;
    OnDamageReceived(Amount);  // Call Blueprint event

    if (Health <= 0.0f)
    {
        Health = 0.0f;
        bIsAlive = false;
        OnDeath();  // Call BlueprintNativeEvent
    }
}

float AMyEnemy::GetHealthPercent() const
{
    return (MaxHealth > 0.0f) ? Health / MaxHealth : 0.0f;
}

void AMyEnemy::OnDeath_Implementation()
{
    // Default: destroy after a short delay
    SetLifeSpan(2.0f);
}
```


---

## Related

- ← Previous: [[02_CPP_Project_Setup_and_Basics]]
- → Next: [[04_Blueprint_CPP_Communication]]
- 📚 Series: [[_MOC_UE5_CPP]]
