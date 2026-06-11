---
title: "Blueprints to C++ - Building a Pressure Plate Door System"
source: "https://www.youtube.com/watch?v=4AdGIPV1Yw4"
video_id: "4AdGIPV1Yw4"
type: "youtube-summary"
series: "UE5 C++"
episode: 1
tags: [ue5, cpp, blueprints, actor, components, uproperty, ufunction, beginner]
---

# Blueprints to C++ - Building a Pressure Plate Door System

**Channel:** Ali Elzoheiry | **Duration:** ~30:00

## Overview

This tutorial builds the same feature twice — a pressure plate that opens a door when the player steps on it. First in Blueprints, then in C++. Along the way you learn the key differences between the two systems and how they work together.

---

## Part 1: Blueprint Implementation

### Step 1: Create the Door Actor (BP_Door)

1. Create a new Blueprint class based on Actor → name it `BP_Door`
2. Add a **Static Mesh** component → make it the root (drag onto DefaultSceneRoot)
3. Assign the door mesh from Starter Content
4. Add collision: select the mesh → Collision → Add Box Simplified

### Step 2: Door Logic (Blueprints)

Create two custom events: `OpenDoor` and `CloseDoor`

- Add a Boolean variable `ShouldOpenOrClose` (default: false)
- `OpenDoor` sets `ShouldOpenOrClose = true` and `YawIncrement = 2`
- `CloseDoor` sets `ShouldOpenOrClose = true` and `YawIncrement = -2`

**Tick function logic:**
```
Branch: ShouldOpenOrClose?
  True →
    Get Actor Rotation → Split → Get Z (Yaw)
    Add YawIncrement to Z
    Set Actor Rotation (keep X, Y the same, use new Z)

    // Stopping condition:
    Branch: YawIncrement > 0 AND ActorRotation.Yaw >= 90?
      → Set ShouldOpenOrClose = false
    OR
    Branch: YawIncrement < 0 AND ActorRotation.Yaw <= 0?
      → Set ShouldOpenOrClose = false
```

Add guards in OpenDoor/CloseDoor to prevent re-opening when already open:
- OpenDoor: only proceed if ActorRotation.Yaw < 90
- CloseDoor: only proceed if ActorRotation.Yaw >= 90

### Step 3: Create the Pressure Plate (BP_PressurePlate)

1. Create a new Blueprint Actor → name it `BP_PressurePlate`
2. Add a **Static Mesh** component (plate mesh — create a cylinder via Modeling Tools: radius 100, height 5, ~70 slices)
3. Add a **Sphere Collision** component with radius 100

### Step 4: Link Pressure Plate to Door

- Add a variable `DoorRef` of type `BP_Door` (Object Reference)
- Mark it **Instance Editable** (the eye icon)
- In the level, use the picker to assign which door this plate controls

### Step 5: Overlap Logic

On the Sphere Collision component:
- **OnComponentBeginOverlap**: check if OtherActor is a ThirdPersonCharacter AND DoorRef is valid → call `OpenDoor` on DoorRef
- **OnComponentEndOverlap**: same checks → call `CloseDoor` on DoorRef

### Step 6: Visual Feedback (Material Swap)

- Add variables: `DefaultPlateMeshMaterial` and `PressedPlateMeshMaterial` (type: Material Interface)
- On begin overlap: Set Plate Mesh material to `PressedPlateMeshMaterial`
- On end overlap: Set Plate Mesh material to `DefaultPlateMeshMaterial`

---

## Part 2: C++ Implementation

### Step 7: Create the C++ Door Class

Tools → New C++ Class → Actor → name it `CPP_Door`

**CPP_Door.h (Header — class definition):**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Door.generated.h"

UCLASS()
class YOURPROJECT_API ACPP_Door : public AActor
{
    GENERATED_BODY()

public:
    ACPP_Door();

protected:
    virtual void BeginPlay() override;

    // Component — visible in details panel, reference cannot be changed
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UStaticMeshComponent* DoorMesh;

    // Internal state — not exposed to editor
    bool bShouldOpenOrClose;
    float YawIncrement;

public:
    virtual void Tick(float DeltaTime) override;

    // Exposed to blueprints as callable functions
    UFUNCTION(BlueprintCallable, Category = "Actions")
    void OpenDoor();

    UFUNCTION(BlueprintCallable, Category = "Actions")
    void CloseDoor();
};
```

**CPP_Door.cpp (Implementation):**

```cpp
#include "CPP_Door.h"

ACPP_Door::ACPP_Door()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create the mesh component and make it the root
    DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
    RootComponent = DoorMesh;

    bShouldOpenOrClose = false;
    YawIncrement = 0.0f;
}

void ACPP_Door::BeginPlay()
{
    Super::BeginPlay();
}

void ACPP_Door::OpenDoor()
{
    // Guard: don't open if already open
    if (GetActorRotation().Yaw < 90.0f)
    {
        YawIncrement = 2.0f;
        bShouldOpenOrClose = true;
    }
}

void ACPP_Door::CloseDoor()
{
    // Guard: don't close if already closed
    if (GetActorRotation().Yaw >= 90.0f)
    {
        YawIncrement = -2.0f;
        bShouldOpenOrClose = true;
    }
}

void ACPP_Door::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bShouldOpenOrClose)
    {
        // Get current rotation, modify Yaw, set new rotation
        FRotator CurrentRotation = GetActorRotation();
        FRotator NewRotation;
        NewRotation.Roll = CurrentRotation.Roll;
        NewRotation.Pitch = CurrentRotation.Pitch;
        NewRotation.Yaw = CurrentRotation.Yaw + YawIncrement;

        SetActorRotation(NewRotation);

        // Check stopping conditions
        if ((YawIncrement > 0 && NewRotation.Yaw >= 90.0f) ||
            (YawIncrement < 0 && NewRotation.Yaw <= 0.0f))
        {
            bShouldOpenOrClose = false;
        }
    }
}
```

### Step 8: Create the C++ Pressure Plate Class

Tools → New C++ Class → Actor → name it `CPP_PressurePlate`

**CPP_PressurePlate.h:**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "CPP_PressurePlate.generated.h"

UCLASS()
class YOURPROJECT_API ACPP_PressurePlate : public AActor
{
    GENERATED_BODY()

public:
    ACPP_PressurePlate();

protected:
    virtual void BeginPlay() override;

    // Components
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UStaticMeshComponent* PlateMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USphereComponent* SphereCollision;

    // Materials — edit anywhere so we can assign in blueprint child
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
    UMaterialInterface* DefaultPlateMeshMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
    UMaterialInterface* PressedPlateMeshMaterial;

    // Overlap handlers with matching signature
    UFUNCTION()
    void OnPressurePlatePressed(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);

    UFUNCTION()
    void OnPressurePlateReleased(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex);

public:
    virtual void Tick(float DeltaTime) override;

    // EditAnywhere — we want to assign the actual door reference in editor
    UPROPERTY(EditAnywhere, Category = "Config")
    ACPP_Door* DoorRef;
};
```

**CPP_PressurePlate.cpp:**

```cpp
#include "CPP_PressurePlate.h"
#include "CPP_Door.h"
#include "PressurePlateDemoCharacter.h"  // Your character class
#include "Components/SphereComponent.h"

ACPP_PressurePlate::ACPP_PressurePlate()
{
    PrimaryActorTick.bCanEverTick = true;

    // Default scene root
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));

    // Plate mesh attached to root
    PlateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlateMesh"));
    PlateMesh->SetupAttachment(RootComponent);

    // Sphere collision attached to plate mesh
    SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
    SphereCollision->SetupAttachment(PlateMesh);
    SphereCollision->SetSphereRadius(100.0f);
}

void ACPP_PressurePlate::BeginPlay()
{
    Super::BeginPlay();

    // Bind overlap events
    SphereCollision->OnComponentBeginOverlap.AddDynamic(
        this, &ACPP_PressurePlate::OnPressurePlatePressed);
    SphereCollision->OnComponentEndOverlap.AddDynamic(
        this, &ACPP_PressurePlate::OnPressurePlateReleased);
}

void ACPP_PressurePlate::OnPressurePlatePressed(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    // Check if overlapping actor is the player AND door ref is valid
    if (OtherActor->IsA(APressurePlateDemoCharacter::StaticClass()) && DoorRef)
    {
        DoorRef->OpenDoor();
        PlateMesh->SetMaterial(0, PressedPlateMeshMaterial);
    }
}

void ACPP_PressurePlate::OnPressurePlateReleased(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex)
{
    if (OtherActor->IsA(APressurePlateDemoCharacter::StaticClass()) && DoorRef)
    {
        DoorRef->CloseDoor();
        PlateMesh->SetMaterial(0, DefaultPlateMeshMaterial);
    }
}

void ACPP_PressurePlate::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
```

### Step 9: Create Blueprint Children from C++ Classes

1. In Content Browser → right-click → Blueprint Class → expand "All Classes" → search for `CPP_Door`
2. Name it (e.g., `BP_CPP_Door`) and assign the door static mesh in its details panel
3. Repeat for `CPP_PressurePlate` → assign plate mesh, materials, and door reference

### Step 10: Using BlueprintNativeEvent for Extensibility

To allow blueprints to extend C++ behavior, change the function declaration:

```cpp
// In header — add BlueprintNativeEvent
UFUNCTION(BlueprintNativeEvent, Category = "Actions")
void OnPressurePlatePressed(...);

// In .cpp — rename to _Implementation
void ACPP_PressurePlate::OnPressurePlatePressed_Implementation(...)
{
    // Default C++ behavior
}
```

This lets you override the function in the Blueprint child and call the parent function to keep the C++ logic running alongside additional Blueprint logic.

---

## Key Takeaways

| Concept | Header (.h) | Implementation (.cpp) |
|---------|------------|----------------------|
| Variables | Type + name + UPROPERTY | Initialize in constructor |
| Components | Declare pointer + UPROPERTY | CreateDefaultSubobject + SetupAttachment |
| Functions | Return type + name + UFUNCTION | ClassName::FunctionName() { } |
| Overlap binding | Declare UFUNCTION | .AddDynamic(this, &Class::Func) |

- **Header file** = class definition (structure, declarations)
- **CPP file** = implementation (logic, behavior)
- `UPROPERTY` exposes variables to the editor/blueprints
- `UFUNCTION(BlueprintCallable)` exposes functions to blueprints
- `UFUNCTION(BlueprintNativeEvent)` allows C++ + Blueprint dual implementation
- `BlueprintReadWrite` = get and set; `BlueprintReadOnly` = get only
- `EditAnywhere` = editable in defaults AND instances; `VisibleAnywhere` = read-only in details
- C++ classes prefixed: `A` for Actor, `U` for UObject components
- Always include required headers when using types (e.g., `#include "Components/SphereComponent.h"`)


---

## Related

- → Next: [[02_CPP_Project_Setup_and_Basics]]
- 📚 Series: [[_MOC_UE5_CPP]]
