---
title: "Blueprint and C++ Class Communication"
source: "https://www.youtube.com/watch?v=CTiidefyPAI"
video_id: "CTiidefyPAI"
type: "youtube-summary"
series: "UE5 C++"
episode: 4
tags: [ue5, cpp, blueprint, communication, uproperty, ufunction, blueprint-native-event]
---

# Blueprint and C++ Class Communication

**Channel:** (Quick Mediums) | **Duration:** ~10:00

## Overview

This tutorial covers three key communication patterns between C++ and Blueprints:
1. Exposing C++ variables to Blueprints
2. Calling C++ functions from Blueprints
3. Calling Blueprint functions from C++

---

## Setup: Create a Blueprint Child from a C++ Class

Starting with a C++ character class (e.g., `AFPSCharacter` derived from `ACharacter`):

1. In the Content Browser → right-click → **Blueprint Class**
2. Search for your C++ class (`FPSCharacter`) and select it
3. Name it `BP_FPSCharacter`
4. In **Game Mode**, set `Default Pawn Class` to `BP_FPSCharacter`

Now the game spawns the Blueprint child instead of the raw C++ class. All C++ functionality works the same, but you can add Blueprint logic on top.

**Tip:** If your Blueprint derived from a C++ class acts buggy after code changes, close and reopen the Blueprint editor — Unreal sometimes struggles with live updates.

---

## Pattern 1: C++ Variable → Blueprint (Get/Set)

### Read-Only Access

```cpp
// FPSCharacter.h
UCLASS()
class AFPSCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Blueprint can READ this but not SET it
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
    float Speed = 10.0f;
};
```

In Blueprint:
- Right-click → search "Get Speed" → it appears as a getter node
- There is NO "Set Speed" node because it's read-only

### Read-Write Access

```cpp
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
float Speed = 10.0f;
```

Now in Blueprint you get both "Get Speed" and "Set Speed" nodes.

### Practical Example — Print Variable from Blueprint

```cpp
// FPSCharacter.h
UCLASS()
class AFPSCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float Speed = 10.0f;
};
```

In `BP_FPSCharacter` Event Graph:
```
Event BeginPlay →
    Get Speed → Convert to String →
    Print String (Duration: 10.0)
```

Output: `10`

You can also modify it:
```
Get Speed → Add (20.0) → Convert to String → Print String
```

Output: `30`

**Important:** Setting a variable in Blueprint also changes it in C++. Any C++ code reading that variable will see the Blueprint-modified value.

---

## Pattern 2: C++ Function → Blueprint (Call C++ from BP)

Use `UFUNCTION(BlueprintCallable)` to expose a C++ function to Blueprints.

```cpp
// FPSCharacter.h
public:
    UFUNCTION(BlueprintCallable, Category = "Debug")
    void PrintString();
```

```cpp
// FPSCharacter.cpp
void AFPSCharacter::PrintString()
{
    UE_LOG(LogTemp, Warning, TEXT("We are printing from C++"));
}
```

In `BP_FPSCharacter`:
```
Event BeginPlay →
    Print String (target: self)
```

The C++ function appears in the Blueprint palette. When you call it, the target is your FPS character. The output log shows: `We are printing from C++`

**The function is NOT called anywhere in C++ — it's called entirely from Blueprint.**

---

## Pattern 3: Blueprint Function → C++ (Call BP from C++)

This is the trickier pattern. You **cannot** just invent a function name in C++ and expect Blueprint to implement it. Instead, you declare a `BlueprintNativeEvent` — C++ provides the declaration and optionally a default implementation, and Blueprint overrides it.

### Step 1: Declare in C++ Header

```cpp
// FPSCharacter.h
public:
    // This will be implemented in Blueprint
    UFUNCTION(BlueprintNativeEvent, Category = "Events")
    void PrintLine();

    // C++ must also provide the _Implementation
    void PrintLine_Implementation();
```

### Step 2: Provide Default (Empty) Implementation in C++

```cpp
// FPSCharacter.cpp
void AFPSCharacter::PrintLine_Implementation()
{
    // Default implementation — can be empty or have fallback logic
    // Blueprints will override this
}
```

### Step 3: Override in Blueprint

1. Open `BP_FPSCharacter`
2. Go to **Functions** → click **Override** button
3. Select **PrintLine** from the list
4. It appears as an Event node
5. Right-click the event node → **Convert Event to Function**
6. The function now has an "Override" badge
7. Implement it:

```
Print Line (Override) →
    Print String: "Printing from BP"
```

### Step 4: Call from C++

```cpp
// FPSCharacter.cpp
void AFPSCharacter::BeginPlay()
{
    Super::BeginPlay();
    PrintLine();  // Calls the Blueprint override!
}
```

**Result:** When the game runs, the Blueprint implementation executes. Output: `Printing from BP`

**The call originates in C++ (`BeginPlay`), but the implementation lives in Blueprint.**

---

## Communication Summary

```
┌─────────────────────────────────────────────────────────┐
│                    COMMUNICATION FLOW                     │
├─────────────────────────────────────────────────────────┤
│                                                          │
│  C++ Variable → Blueprint                                │
│  ┌──────────┐    ┌──────────────┐                        │
│  │ UPROPERTY │───→│ Get/Set node │                       │
│  │ ReadWrite │    │ in Blueprint │                       │
│  └──────────┘    └──────────────┘                        │
│                                                          │
│  C++ Function → Blueprint                                │
│  ┌──────────────┐    ┌──────────────────┐               │
│  │ UFUNCTION     │───→│ Callable node    │              │
│  │ BlueprintCall │    │ in Blueprint     │              │
│  └──────────────┘    └──────────────────┘               │
│                                                          │
│  Blueprint Function → C++                                │
│  ┌───────────────────┐    ┌─────────────────────┐      │
│  │ BlueprintNative   │───→│ Override in Blueprint│      │
│  │ Event in C++      │    │ C++ calls it         │      │
│  └───────────────────┘    └─────────────────────┘      │
│                                                          │
└─────────────────────────────────────────────────────────┘
```

---

## When to Use Each Pattern

| Pattern | Use Case |
|---------|----------|
| `BlueprintReadWrite` variable | Expose config/data that designers need to tweak |
| `BlueprintCallable` function | Call core C++ logic from Blueprint events |
| `BlueprintNativeEvent` | Core logic in C++, allow Blueprint to extend/override |
| `BlueprintImplementableEvent` | Define interface in C++, implementation only in Blueprint |

---

## Complete Working Example

```cpp
// FPSCharacter.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

UCLASS()
class AFPSCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AFPSCharacter();

    // Pattern 1: Variable exposed to Blueprint
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float Speed = 10.0f;

    // Pattern 2: C++ function callable from Blueprint
    UFUNCTION(BlueprintCallable, Category = "Debug")
    void PrintString();

    // Pattern 3: Blueprint implements this, C++ calls it
    UFUNCTION(BlueprintNativeEvent, Category = "Events")
    void PrintLine();
    void PrintLine_Implementation();

protected:
    virtual void BeginPlay() override;
};
```

```cpp
// FPSCharacter.cpp
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"

AFPSCharacter::AFPSCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AFPSCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Call the Blueprint-implemented function
    PrintLine();
}

void AFPSCharacter::PrintString()
{
    UE_LOG(LogTemp, Warning, TEXT("We are printing from C++"));
}

void AFPSCharacter::PrintLine_Implementation()
{
    // Default behavior (empty or fallback)
    UE_LOG(LogTemp, Warning, TEXT("Default C++ PrintLine - override in BP"));
}
```


---

## Related

- ← Previous: [[03_UPROPERTY_UFUNCTION_Macros]]
- → Next: [[05_CPP_vs_Blueprints_Showdown]]
- 📚 Series: [[_MOC_UE5_CPP]]
