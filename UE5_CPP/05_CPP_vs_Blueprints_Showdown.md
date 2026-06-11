---
title: "C++ vs Blueprints Showdown - Performance Test Results"
source: "https://www.youtube.com/watch?v=XCn_6Ifwhfg"
video_id: "XCn_6Ifwhfg"
type: "youtube-summary"
series: "UE5 C++"
episode: 5
tags: [ue5, cpp, blueprints, performance, testing, benchmarks, comparison]
---

# C++ vs Blueprints Showdown - Performance Test Results

**Channel:** (UE5 C++ Showdown) | **Duration:** ~15:00

## Overview

This video puts the "C++ is faster than Blueprints" claim to the test with controlled benchmarks. The creator builds an identical math-heavy workload in both C++ and Blueprints, runs it at various frame rates, and compares the results across multiple machines.

---

## The Claim to Test

> "You need to convert all Blueprint classes to C++ to keep performance usable."

Is this actually true? The video designs a fair test to find out.

---

## Test Design Principles

1. **Identical work** — same algorithm, same number of iterations in both C++ and Blueprint
2. **Simple and focused** — isolate math/logic performance from other systems
3. **Measurable** — precise timing before and after the workload
4. **Repeatable** — run multiple times and average the results

### The Workload

For each tick:
1. Generate 1,000 random floats between 0 and 1
2. Sum all the floats
3. Divide by 1,000 to get an average
4. Repeat this 100 times per tick (100,000 random numbers per tick)

Run for 100 ticks total, time the entire batch, repeat 10 times and average.

---

## C++ Implementation

### Test Actor Header

```cpp
// PerformanceTestActor.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PerformanceTestActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTestComplete);

UCLASS()
class APerformanceTestActor : public AActor
{
    GENERATED_BODY()

public:
    APerformanceTestActor();

    // Event broadcast when test finishes
    UPROPERTY(BlueprintAssignable, Category = "Test")
    FOnTestComplete OnTestComplete;

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

private:
    // Timer
    FTimerHandle TestTimerHandle;
    double StartTime = 0.0;
    double EndTime = 0.0;

    // Test parameters
    int32 RunsRemaining = 10;
    int32 CyclesRemaining = 100;
    const int32 NumFloats = 1000;
    const int32 CyclesPerRun = 100;
    const int32 TotalRuns = 10;

    // Results
    TArray<double> RunDurations;

    // Working data
    TArray<float> RandomFloats;

    // Functions
    void StartTimer();
    void StopTimer();
    void OnTimerExpired();
    void RunMathWork();
};
```

### Test Actor Implementation

```cpp
// PerformanceTestActor.cpp
#include "PerformanceTestActor.h"
#include "Engine/World.h"
#include "TimerManager.h"

APerformanceTestActor::APerformanceTestActor()
{
    PrimaryActorTick.bCanEverTick = true;
}

void APerformanceTestActor::BeginPlay()
{
    Super::BeginPlay();
    RunsRemaining = TotalRuns;
    CyclesRemaining = CyclesPerRun;
    RunDurations.Empty();
    StartTimer();
}

void APerformanceTestActor::StartTimer()
{
    if (!GetWorld()) return;

    FTimerManager& TimerManager = GetWorld()->GetTimerManager();

    // Safety timeout (should never hit this)
    TimerManager.SetTimer(TestTimerHandle, this,
        &APerformanceTestActor::OnTimerExpired,
        100.0f, false);

    StartTime = FPlatformTime::Seconds();
}

void APerformanceTestActor::StopTimer()
{
    EndTime = FPlatformTime::Seconds();
    double Duration = EndTime - StartTime;

    GetWorld()->GetTimerManager().ClearTimer(TestTimerHandle);
    RunDurations.Add(Duration);

    RunsRemaining--;
    if (RunsRemaining > 0)
    {
        CyclesRemaining = CyclesPerRun;
        StartTimer();
    }
    else
    {
        // Calculate average
        double Total = 0.0;
        for (double D : RunDurations) Total += D;
        double Average = Total / RunDurations.Num();

        UE_LOG(LogTemp, Warning, TEXT("C++ Average: %f seconds"), Average);
        OnTestComplete.Broadcast();
    }
}

void APerformanceTestActor::OnTimerExpired()
{
    UE_LOG(LogTemp, Error, TEXT("Test timed out!"));
}

void APerformanceTestActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (CyclesRemaining <= 0) return;

    // The actual workload
    RunMathWork();
    CyclesRemaining--;

    if (CyclesRemaining <= 0)
    {
        StopTimer();
    }
}

void APerformanceTestActor::RunMathWork()
{
    RandomFloats.SetNumUninitialized(NumFloats);

    // Generate random floats
    for (int32 i = 0; i < NumFloats; i++)
    {
        RandomFloats[i] = FMath::FRandRange(0.0f, 1.0f);
    }

    // Sum and average
    float Total = 0.0f;
    for (float F : RandomFloats)
    {
        Total += F;
    }
    float Average = Total / NumFloats;

    // Use the result to prevent optimization from removing it
    if (Average < 0)  // Never true, but compiler doesn't know that
    {
        UE_LOG(LogTemp, Warning, TEXT("Impossible: %f"), Average);
    }
}
```

---

## Blueprint Implementation

Recreate the same logic in a Blueprint Actor:

### Variables
```
Integer: RunsRemaining (default: 10)
Integer: CyclesRemaining (default: 100)
Float Array: RandomFloats
Float Array: RunDurations
Timer Handle: TestTimerHandle
Double: StartTime
Double: EndTime
```

### Event Graph Flow

```
Event BeginPlay →
    Set RunsRemaining = 10
    Set CyclesRemaining = 100
    Clear RunDurations
    → Call StartTimer

StartTimer:
    Set Timer by Function Name → "RunMathWork" → Looping
    Get Platform Time in Seconds → Set StartTime

Event Tick →
    Branch: CyclesRemaining > 0?
        True →
            For Loop (0 to 999):
                Random Float in Range (0, 1) → Add to RandomFloats
            For Each Loop RandomFloats:
                Add to running Total
            Total / 1000 = Average
            Set CyclesRemaining -= 1
            Branch: CyclesRemaining <= 0?
                True → Call StopTimer
```

---

## Test Results

### Editor Viewport (Development)

| Frame Rate Limit | C++ vs Blueprint Difference |
|-----------------|---------------------------|
| 120 FPS | Blueprint 5% slower |
| 60 FPS | No measurable difference |
| 240 FPS | C++ 33% faster |
| 1000 FPS (uncapped) | C++ 32% faster |

### PIE (Play In Editor) Window

| Frame Rate Limit | C++ vs Blueprint Difference |
|-----------------|---------------------------|
| 30 FPS | C++ slightly faster |
| 60-120 FPS | No measurable difference |
| 240-1000 FPS | C++ 15% faster |

### Standalone (with recording overlay)

| Frame Rate Limit | C++ vs Blueprint Difference |
|-----------------|---------------------------|
| 30-240 FPS | No measurable difference |
| 400 FPS | C++ 5% faster |
| 1000 FPS | Within 1% of each other |

### Shipping Build (What Players Actually Get)

| Frame Rate Limit | C++ vs Blueprint Difference |
|-----------------|---------------------------|
| 30-400 FPS | Within 1% of each other |
| 1000 FPS | C++ 3% faster to 3% slower (variance) |

**Overall shipping build average: C++ ~1% faster**

### Multi-Machine Results

- **Powerful desktop** — virtually identical
- **Moderate laptop** — virtually identical
- **Low-end laptop** (2-3 FPS) — equally slow, within 1% of each other

---

## Key Findings

1. **In the shipping build, there is virtually no performance difference** between C++ and Blueprints for math/logic operations
2. **In the editor during development**, C++ can be 15-33% faster when the frame rate isn't capped
3. **The performance difference only appears when the CPU is the bottleneck** — when the GPU or frame rate limiter caps performance, both run identically
4. **Bad coding practices in either system will cause slowdown** — the difference is in the code quality, not the language

---

## When to Use C++

Despite minimal performance differences in shipping builds, C++ is still valuable for:

1. **Accessing engine internals** that Blueprints can't reach
2. **Complex algorithms** that are hard to visualize as node graphs
3. **Third-party library integration** (networking, databases, etc.)
4. **Version control** — C++ files merge better than Blueprint `.uasset` files
5. **Team workflow** — programmers may prefer text-based code

## When to Use Blueprints

1. **Rapid prototyping** — iterate much faster
2. **Visual logic** — easier to understand flow for designers
3. **UI and gameplay scripting** — where visual clarity matters
4. **Small teams** — designers can work independently
5. **No measurable perf difference** in shipping builds for most use cases

---

## Recommendation

> Use Blueprints if you're comfortable with them. Get comfortable with C++ eventually for its broader capabilities — but **not for performance reasons**. In the shipping build, it doesn't matter.

The performance myth is busted: unless you're doing extreme per-frame computation with uncapped frame rates in the editor, **Blueprints and C++ perform equally in the final game**.


---

## Related

- ← Previous: [[04_Blueprint_CPP_Communication]]
- 📚 Series: [[_MOC_UE5_CPP]]
