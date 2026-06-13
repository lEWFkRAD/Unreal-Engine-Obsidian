---
title: "How to Start Optimizing Your Unreal Engine Game"
source: "https://www.youtube.com/watch?v=4lARfWIGU68"
video_id: "4lARfWIGU68"
type: "step-by-step-guide"
series: "Step-by-Step Guides"
episode: 3
tags: [ue5, optimization, performance, profiling, guide]
---

# How to Start Optimizing Your Unreal Engine Game

**Source:** https://www.youtube.com/watch?v=4lARfWIGU68
**Channel:** UNF Games
**Duration:** 17:54
**Extracted from:** `How_to_start_optimizing_your_Unreal_Engine_Game.md`

---

## Prerequisites

- An Unreal Engine project with content in the level
- Basic familiarity with the UE5 editor viewport

---

## Step-by-Step

### Step 1: Monitor Your Frame Rate
1. Look at the **frame rate counter** in the viewport (the small number in the corner).
2. This shows your current FPS — keep an eye on it every time you make a change.
3. **Note:** If you're above 60 FPS, you're fine. Problems become noticeable when you drop below 60.
4. **Important:** Testing in the editor is NOT a real representation of final performance. The editor loads everything into memory; a packaged game loads/unloads assets on demand. Your editor FPS is typically the *worst case* baseline.

### Step 2: Profile with `stat unit`
1. Open the **console command** bar (usually at the top of the viewport or via `~` key).
2. Type `start stat unit` and press **Enter**.
3. You'll see new on-screen data showing:
   - **Frame** — milliseconds to render one frame
   - **Game thread** — processing time for Blueprints/C++ logic
   - **Draw thread** — rendering primitives, triangles, materials
   - **GPU time** — visual effects, simulations, post-processing

### Step 3: Understand the Three Threads
1. **Game Thread (if red):** You have a programming/logic issue.
   - Common culprits: heavy `for` loops, spawning/destroying actors on `Tick`
   - Fix: Optimize Blueprints or C++ code
2. **Draw Thread (if red):** Too many objects/primitives in the level.
   - Related to: triangle count, material count, number of meshes
   - Fix: Reduce object density or simplify meshes
3. **GPU Time (if red):** Heavy visual effects, complex materials, or post-processing.
   - Fix: Simplify VFX, reduce post-process effects
4. **Key concept:** All three threads must finish before a frame can render. The *slowest* thread determines your actual FPS. Optimize whichever is the bottleneck.

### Step 4: Use View Modes to Diagnose
1. Switch between **View Modes** in the viewport to identify issues:
   - **Unlit** — removes lighting; if FPS improves significantly, lighting is expensive
   - **Shader Complexity** — shows material cost per pixel
     - 🟢 Green = good
     - 🔴 Red = acceptable
     - ⚪ White = **bad** — avoid white shader complexity
     - Don't cluster many expensive materials in the same area
   - **Nanite Visualization** — check overdraw if using Nanite

### Step 5: Use Freeze Rendering to Isolate
1. Type `freeze rendering` in the console to freeze the current view.
2. Rotate the camera — objects behind you are NOT being rendered.
3. This shows you exactly what Unreal is drawing and helps identify expensive areas.
4. Type `freeze rendering` again to unfreeze.

### Step 6: Understand LODs (Level of Detail)
1. Unreal automatically reduces mesh detail based on distance (LODs).
2. Objects far away use fewer triangles — this is automatic, no setup needed.
3. If performance drops when looking at a specific area, check if dense meshes are clustered there.

### Step 7: Enable Nanite (When Appropriate)
1. Right-click a mesh in the **Content Browser** → select **Nanite** → **Enable**.
2. **When to use Nanite:**
   - Meshes with **millions of triangles**
   - Large maps with high-detail geometry
3. **When NOT to use Nanite:**
   - Small meshes with low triangle counts (e.g., <500K triangles)
   - Enabling Nanite on simple meshes adds overhead and *costs* frames
4. Check Nanite overdraw in **View Modes → Nanite Visualization** — avoid overlapping bright-colored areas.

### Step 8: Adjust Scalability Settings
1. If frames are low, go to **Viewport → Scalability Settings**.
2. Lower quality presets to regain frames.
3. Alternatively, close and reopen the project — the editor sometimes holds onto loaded assets.

---

## Quick Reference — Bottleneck Identification

| Symptom | Bottleneck | Likely Cause |
|---------|-----------|--------------|
| Game thread is red | CPU (logic) | Blueprint loops, Tick spawning/destroying |
| Draw thread is red | CPU (rendering) | Too many meshes/primitives in view |
| GPU time is red | GPU | Complex materials, VFX, post-processing |
| All fine but low FPS | Editor overhead | Test in standalone/packaged build |

---

## Pro Tips

- **Always profile before optimizing.** Don't guess — use `stat unit` to find the actual bottleneck.
- **Editor vs. Standalone:** Your packaged game will almost always run better than the editor. Don't panic about editor FPS.
- **Shader complexity:** Red is acceptable; white is the danger zone. Avoid stacking multiple red-complexity materials in one spot.
- **Nanite is not free.** Only enable it on high-poly meshes. Using it on everything will hurt performance.
- **Ask for help smartly:** When posting on forums, report which thread (Game/Draw/GPU) is the bottleneck — it helps others diagnose your issue faster.
- **UE5 Optimization Learning Path:** Check the official Unreal Engine documentation for a comprehensive optimization guide.

---

## Related

- ← Previous: [[02_Packaging_Project]]
- → Next: [[04_RPG_Tutorial_02_Locomotion_Blendspace]]
- 📚 Series: [[_MOC_Step_by_Step_Guides]]
- 📄 Full Transcript: [[03_Vaulting_with_Motion_Warping]]
