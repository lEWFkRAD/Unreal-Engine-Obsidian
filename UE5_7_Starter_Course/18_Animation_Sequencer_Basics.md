---
title: "Unreal Engine 5 Beginner Tutorial Part 17: Animation & Sequencer Basics"
source: "https://www.youtube.com/watch?v=-EfwF0WgKbs"
video_id: "-EfwF0WgKbs"
type: "youtube-summary"
series: "UE5 Starter Course"
episode: 18
tags: [ue5, tutorial, beginner, animation, sequencer, keyframes, graph-editor, timeline]
---

# UE5 Beginner Tutorial Part 17: Animation & Sequencer Basics

**Instructor:** Bad Decisions Studio

## Overview
UE5's Sequencer timeline tool for creating animations. Covers keyframes, graph editor, object animation, and practical examples with spaceship doors and Stormtrooper walk cycles.

## Core Concepts
- **Sequencer:** Timeline tool for animations (like a video editor)
- **Keyframes:** Snapshots defining object properties at specific points
- **Graph Editor:** Precise control over animation curves and speed

## Step-by-Step: Basic Object Animation

### 1. Creating & Setting Up a Sequencer
- Access: Dropdown menu → Add Level Sequence
- Save to dedicated folder (e.g., `Sequencers`)

### 2. Adding Objects
- Method 1: Track (+) → Actor to Sequencer → Select object
- Method 2: Drag from Outliner into Sequencer

### 3. Keyframing Movement
- Navigate to Frame 0, set initial position
- Add Keyframe: **+** icon next to Location (shortcut: **Enter**)
- Navigate to end frame, set final position
- Press **Space** to preview

### 4. Adding Scale Animation
- Keyframe scale at start (0.1) and end (1.0)
- Result: Object grows while moving

## Graph Editor
- Click **Graph** button in Sequencer
- Expand Transform → Location → Select axis curves
- **Weighted Tangents:** Right-click → Key Interpolation → Weighted Tangents
- Adjust handle length for ease-in/ease-out

## Practical Examples

### Spaceship Door Animation
- Use pre-rigged spaceship mesh (skeletal mesh)
- Add animation via Sequencer + button
- Drag animation track to start before Frame 0 to hide pre-animation movement

### Stormtrooper Walk Cycle
- Import skeletal mesh with animations
- Add walk animation, drag edge to extend/loop
- Rotate trooper to face destination, keyframe location
- **Fix Sliding:** Adjust keyframes to match walk cycle speed
- **Uniform Motion:** Right-click → Key Interpolation → Linear

### Duplicating & Offsetting
- Copy animation tracks → paste to new object
- Offset timing for natural variation
- Adjust Y-axis to space objects apart

## Console Command
```
r.RayTracing.Nanite.Mode 1
```

---

## Related

- ← Previous: [[17_Cameras_Rig_Rail_Crane]]
- → Next: [[19_Animation_Sequencer_Advanced]]
- 📚 Series: [[_MOC_UE5_7_Starter_Course]]
