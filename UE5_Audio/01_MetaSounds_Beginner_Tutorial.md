---
title: "MetaSounds Beginner Tutorial"
source: "https://www.youtube.com/watch?v=0H7PiqIl0Io"
video_id: "0H7PiqIl0Io"
type: "youtube-summary"
series: "UE5 Audio"
episode: 1
tags: [ue5, audio, metasounds]
---

# MetaSounds Beginner Tutorial

**Source:** https://www.youtube.com/watch?v=0H7PiqIl0Io

## Overview

UE5 MetaSounds introduction covering sound attenuation, 2D/3D audio, Blueprint integration, and basic MetaSound source setup.

## Key Concepts

### MetaSounds vs Sound Cues
- MetaSounds are node-based audio graphs (like Blueprints for sound)
- Replace Sound Cues for procedural audio
- Support DSP processing, parameter-driven modulation, and real-time control

### Setting Up MetaSounds
1. Enable MetaSounds plugin (Edit > Plugins > MetaSounds)
2. Right-click Content Browser > Sounds > MetaSound Source
3. MetaSound Editor opens with a node graph

### Core Nodes
- **Wave Player**: Plays audio samples
- **Trigger**: Fires events on demand
- **Random**: Randomizes parameters
- **Filter**: Applies audio filters
- **Envelope**: Controls volume over time

### Sound Attenuation
- 3D sounds use Attenuation shapes (sphere, box)
- Falloff types: Linear, Logarithmic, Inverse
- Set in MetaSound Source properties

### Blueprint Integration
- Expose parameters as inputs
- Use "Set MetaSound Parameter" node
- Trigger sounds via "Play Sound at Location" or "Spawn Sound 2D"

---

## Related

- → Next: [[02_PrismaticaDev_MetaSounds]]
- 📚 Series: [[_MOC_UE5_Audio]]
