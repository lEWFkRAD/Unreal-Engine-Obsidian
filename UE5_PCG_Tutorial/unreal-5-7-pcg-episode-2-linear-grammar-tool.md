---
title: "Unreal 5.7 PCG (Episode 2): Linear Grammar Tool Explained"
source: "https://www.youtube.com/watch?v=kOEwIIWkv3c"
video_id: "kOEwIIWkv3c"
type: "youtube-summary"
series: "UE5 PCG Tutorial"
episode: 0
tags: [ue5, tutorial, pcg, procedural, grammar, gamedev]
---

# Unreal 5.7 PCG: Linear Grammar Tool Explained

**Channel:** PolyBoost | **Published:** 2025-12-06 | **Length:** 17:19

## Overview
The Linear Grammar Tool in UE5.7 is a rule-based procedural generation system for creating structured environments. This tutorial demonstrates using grammar rules to control object placement, repetition, patterns, and variation along splines.

## Core Grammar Syntax

### Key Operators
| Operator | Function | Example | Effect |
|----------|----------|---------|--------|
| `*` | **Repetition** | `A*` | Repeats symbol along spline length |
| `,` | **Sequence** | `A*,B` | Places A repeatedly, then B at the end |
| `( )` | **Block Grouping** | `(AB)*` | Groups A and B, repeats entire block |
| `{ }` | **Weighted Random** | `{A*50}{B*25}{C*25}` | Weighted random selection |

### Tool Features
- **Scalable**: Disable to prevent mesh stretching along spline.
- **Size**: Adjusts spacing between repeated meshes.
- **Forward Axis**: Rotates objects to align with spline direction.
- **Local Offset**: Repositions meshes (e.g., lifting windows onto surfaces).

## Practical Example: Procedural Building Row
1. Import 6 building meshes, assign each to a symbol (A, B, C...).
2. Grammar rule: `(A,B,C,D,E,F)*` to repeat a pattern.
3. Fine-tune scaling, offsets, spacing.
4. Result: Procedurally generated building row with controlled variation.

## Key Takeaways
- Block grouping with `( )` is essential for multi-object patterns.
- Weighted randomness enables controlled variation (e.g., 50% offices, 25% shops, 25% houses).
- Scales to generate city blocks, fences, walls, roads, and modular layouts.

---

## Related

- ← Previous: [[ue5-pcg-tutorial-beginners-episode-2-full]]
- 📚 Series: [[_MOC_UE5_PCG_Tutorial]]
