---
title: "Introduction to AI Perception - Unreal Engine 5 Tutorial"
source: "https://www.youtube.com/watch?v=ol0_73lwCXU"
video_id: "ol0_73lwCXU"
type: "youtube-summary"
series: "UE5 AI"
episode: 3
tags: [ue5, ai, perception, sight, hearing, stimuli, senses]
---

# Introduction to AI Perception - Unreal Engine 5 Tutorial

**Duration:** 13:30 | **Published:** UE5 Tutorial

## Overview

The AI Perception System is Unreal Engine's built-in framework for giving AI agents sensory capabilities. It works alongside Behavior Trees and the Environmental Query System (EQS) to create intelligent, responsive AI. This tutorial introduces the core concepts and setup.

## Core Components

### AI Perception Component
- Added to your **AIController Blueprint**
- Click +Add in Components > select AIPerception
- Configures what senses the AI has and their parameters

### Available Senses

| Sense | Class | Key Properties |
|-------|-------|----------------|
| **Sight** | AISense_Sight | Sight Radius, Lose Sight Radius, Peripheral Vision Half Angle |
| **Hearing** | AISense_Hearing | Hearing Range, LoS Hearing Range |
| **Damage** | AISense_Damage | Detects damage events (Point, Radial) |
| **Touch** | AISense_Touch | Physical collisions/bumps |
| **Team** | AISense_Team | Nearby team member detection |
| **Prediction** | AISense_Prediction | Predicts future actor positions |

### Stimuli Source Component
- Added to actors that should be detectable (e.g., the player)
- Automatically registers the actor as a stimuli source
- Without this, the AI cannot perceive the actor

## Implementation Steps

### 1. Set Up AI Perception on the Controller
1. Open your AIController Blueprint
2. Add AIPerception Component
3. In Details > Senses Config, add a new element
4. Select AI Sight as the Implementation
5. Configure:
   - Sight Radius: 1500.0
   - Lose Sight Radius: 1800.0 (should be larger than Sight Radius)
   - Peripheral Vision Half Angle Degrees: 45.0 (90-degree cone)
   - Detection by Affiliation: check Detect Neutrals (for Blueprint use)
   - Max Age: 5.0 (seconds before forgetting)

### 2. Register the Player as a Stimuli Source
1. Open the Player Character Blueprint
2. Add AIPerceptionStimuliSource component
3. Register the AI Sense: Sight
4. Tag the player character with "Player" tag

### 3. React to Perception Events
On the AIController Blueprint:
1. Select the AIPerception component
2. Add Event: On Target Perception Updated
3. In the event handler:
   - Check if the Actor has the "Player" tag
   - Branch: if successfully sensed, set HasLineOfSight = true on Blackboard
   - Branch: if not sensed, start a timer before setting HasLineOfSight = false

### 4. Connect to Behavior Tree
- The Behavior Tree uses a Blackboard Decorator on the chase branch
- Decorator checks HasLineOfSight key
- When true: chase branch activates
- When false: patrol branch takes over

### 5. AI Perception Sense Configuration Details

**Sight Sense:**
- Sight Radius: maximum detection distance
- Lose Sight Radius: distance at which a seen target is forgotten (should be > Sight Radius to prevent flickering)
- Peripheral Vision Half Angle: half-angle of vision cone (45 = 90-degree FOV)
- Auto Success Range from Last Seen Location: if > 0, AI always sees target within this range
- Point of View Backward Offset: adjusts view cone origin
- Near Clipping Radius: close-range awareness

**Hearing Sense:**
- Use Report Noise Event from gameplay code to trigger
- Configure Hearing Range for detection distance
- Detection by Affiliation for team-based filtering

### 6. Useful Functions

| Function | Purpose |
|----------|---------|
| Get Currently Perceived Actors | All actors currently sensed |
| Get Known Perceived Actors | Sensed and not yet forgotten |
| Get Perceived Hostile Actors | Hostile actors with active stimuli |
| Set Sense Enabled | Enable/disable sense at runtime |
| Forget All | Clear all perception data |

### 7. Project Settings for Forgetting
- Project Settings > Engine > AI System
- Set "Forget Stale Actors" to true
- The system forgets actors not perceived for Max Age duration

## Key Takeaways
- AIPerception is more powerful and flexible than PawnSensing
- Always set Lose Sight Radius > Sight Radius to prevent flickering
- Use "Detection by Affiliation: Detect Neutrals" with Tags for Blueprint filtering
- Max Age = 0 means the stimulus is never forgotten
- Debug visualization shows perception cones in the viewport (AI > Show Perception)

## Resources
- Epic Documentation: https://dev.epicgames.com/documentation/unreal-engine/ai-perception-in-unreal-engine
- Ali Elzoheiry's Perception Tutorial (Part 3): https://www.youtube.com/watch?v=gsyZdKYAT_4
- Ryan Laley's Perception Tutorial: https://www.youtube.com/watch?v=bx7taRBjJgM


---

## Related

- ← Previous: [[02_Simple_Behavior_Tree]]
- 📚 Series: [[_MOC_UE5_AI]]
