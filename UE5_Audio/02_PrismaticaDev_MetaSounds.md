---
title: "PrismaticaDev MetaSounds"
source: "https://www.youtube.com/watch?v=92RIT7tObDg"
video_id: "92RIT7tObDg"
type: "youtube-summary"
series: "UE5 Audio"
episode: 2
tags: [ue5, audio, metasounds, prismatica]
---

# PrismaticaDev MetaSounds

**Source:** https://www.youtube.com/watch?v=92RIT7tObDg

## Overview

- **Creator:** PrismaticaDev (78.4K subscribers)
- **Duration:** 15:40
- **Series:** "5-Minute Materials" / UE5 Audio series
- **Focus:** Introduction to MetaSounds in Unreal Engine 5

PrismaticaDev is run from Melbourne, Australia, focused on material, particles, animation and game dev guides for Unreal Engine. The channel's project, Prismatica, is an indie top-down RPG inspired by Mordhau, Mount & Blade, and Dark Souls.

## Content

### What are MetaSounds?

MetaSounds are Unreal Engine 5's new audio system that replaces traditional Sound Cues. They provide a node-based graph system for creating procedural and reactive audio. Key advantages include:

- **Procedural audio generation** — synthesize sounds from scratch using oscillators and signal processors
- **Real-time parameter control** — drive audio properties via gameplay parameters (speed, health, distance, etc.)
- **Sample-accurate processing** — no latency overhead from blueprint tick rates
- **GPU-accelerated** — MetaSound graphs are compiled and run efficiently

### Getting Started with MetaSounds

1. **Create a MetaSound asset:** Right-click in Content Browser → Audio → MetaSound
2. **Understand the graph:** MetaSounds use a dataflow graph where audio signals flow from left to right
3. **Key node types:**
   - **Generators:** Sine wave, saw wave, square wave, noise generators
   - **Filters:** Low-pass, high-pass, band-pass
   - **Envelopes:** ADSR (Attack, Decay, Sustain, Release) for shaping sound
   - **Mixers:** Combine multiple audio signals
   - **Triggers:** Events that start/stop sounds or trigger envelopes
   - **Parameters:** Expose values that can be driven from Blueprints

### Basic MetaSound Setup

1. Add an **On Play** trigger node connected to an envelope
2. Connect a **Sine Generator** to the envelope input
3. Route the envelope output through a **Filter** node
4. Connect to the **Output** node
5. Adjust frequency, filter cutoff, and ADSR values for the desired sound

### Driving MetaSounds from Blueprints

- Use **Set MetaSound Parameter** nodes in Blueprints
- Common use cases:
  - Vehicle engine RPM → oscillator frequency
  - Player speed → wind sound intensity
  - Proximity to water → ambient water volume
  - Health percentage → heartbeat rate

### Best Practices

- Start with simple graphs and add complexity incrementally
- Use parameter names that are descriptive and consistent
- Test with the MetaSound editor's built-in preview before integrating
- Combine MetaSounds with traditional Sound Cues when MetaSounds are overkill for simple one-shot sounds

## Related

- Previous: [[01_Intro_to_Audio|Intro to Audio]] (Episode 1)
- Next: [[03_Advanced_MetaSounds|Advanced MetaSounds]] (Episode 3)
- Series MOC: [[UE5_Audio_MOC|UE5 Audio MOC]]
