---
title: "How to Optimize Performance in Unreal Engine 5"
source: "https://www.youtube.com/watch?v=lfjG3z5VVIw"
video_id: "lfjG3z5VVIw"
type: "youtube-summary"
series: "UE5 Optimization"
episode: 2
tags: [ue5, optimization, unreal-insights, profiling, cpu, gpu, tracing, debugging]
---

# How to Optimize Performance in Unreal Engine 5

**Creator:** Nu Makes Games (Riot Games engineer) | **Duration:** 17:39 | **Published:** January 28, 2024

## Overview

A practical tutorial on using **Unreal Insights**, Unreal Engine's built-in performance profiling tool. The video demonstrates the full workflow: setting up tracing sessions, reading profiler data, identifying bottlenecks, and applying fixes — all using a real time-rewinding gameplay prototype.

## What is Unreal Insights?

Unreal Insights is UE5's primary profiling suite. It uses the **Trace framework** to record detailed performance data from your game, including:
- CPU thread timing (Game Thread, Render Thread, etc.)
- GPU frame timing
- Memory allocations
- Asset loading times
- Task/thread scheduling

## Step-by-Step Profiling Workflow

### Step 1: Launch with Tracing Enabled

Add these command-line arguments when launching your game:

```
-trace=default,task,file,loadtime
-statnamedevents
```

- `-statnamedevents` enables detailed CPU timing events (adds slight overhead — use for profiling only)
- `-trace=default,task` captures CPU and task scheduling data
- Add `-nosound -noverifygc -noailogging -novsync` to reduce noise during profiling

### Step 2: Open Unreal Insights

1. Launch your game with tracing arguments
2. Open **Unreal Insights** from: `Engine/Binaries/Win64/UnrealInsights.exe`
3. Or connect live: Window > Developer Tools > Session Frontend > Unreal Insights

### Step 3: Analyze the Trace

**Key tabs to examine:**

- **Timing Insights**: Shows per-frame CPU/GPU timing with thread activity
  - Look for the **Game Thread** and **Render Thread** — which is the bottleneck?
  - Long bars = expensive operations; drill into them to find the specific function
- **Counters**: Track stat values over time (frame time, draw calls, memory)
- **Loading**: Identify slow asset loads causing hitches

### Step 4: Identify the Bottleneck

**CPU-Bound indicators:**
- Game Thread or Render Thread is consistently at the frame budget limit
- GPU has idle time (shorter bars)
- `stat UNIT` shows Game/Render time > GPU time

**GPU-Bound indicators:**
- GPU time exceeds CPU time
- `stat GPU` shows specific passes consuming most time
- Increasing resolution (`r.SetRes`) drops FPS further

### Step 5: Fix and Re-Profile

In the video's example (time-rewinding prototype):
- Used Insights to find that the rewind system was doing expensive per-frame operations
- Moved computation to be **tick-rate independent** and batched operations
- Verified improvement by comparing before/after traces

## Essential Console Commands for Profiling

```
stat UNIT                   # Shows Game, Draw, GPU, RHIT thread times
stat FPS                    # Frames per second
stat detailed               # Comprehensive breakdown
stat DumpHitches            # Log hitch frames to output
stat Hitches                # Set hitch threshold
profilegpuhitches           # Open profiler on hitch detection
```

## Build Configuration Tips

- **Profile in Test builds**, not Development — Development has heavy GPU debugging (DRED) enabled by default, adding up to 30% overhead
- To disable DRED in Development:
  ```
  -dpcvars=r.D3D12.DRED=0,r.D3D12.LightweightDRED=0,r.GPUCrashDebugging.Breadcrumbs=0
  ```
- **Use packaged builds** for accurate profiling — editor overhead skews results

## Key Takeaways

1. **Unreal Insights is the primary tool** — learn it before relying on `stat` commands alone
2. **Always determine CPU-bound vs GPU-bound first** — this dictates where to focus optimization
3. **Profile on target hardware** with a reproducible scenario
4. **The trace framework** captures far more data than simple stat commands
5. **Compare before/after traces** to validate optimization changes

## Related Resources

- [Unreal Insights Official Docs](https://docs.unrealengine.com/en-US/TestingAndOptimization/PerformanceAndProfiling/UnrealInsights/)
- [Intel: UE Optimization Profiling Fundamentals](https://www.intel.com/content/www/us/en/developer/articles/technical/unreal-engine-optimization-profiling-fundamentals.html)
- [Nu Makes Games GitHub — Rewind Prototype](https://github.com/NuMakesGames/ue5-rewind)


---

## Related

- ← Previous: [[01_UE5_Optimization_Made_Easy_Fundamentals]]
- → Next: [[03_UE5_GPU_Optimization_Tips_and_Tricks]]
- 📚 Series: [[_MOC_UE5_Optimization]]
