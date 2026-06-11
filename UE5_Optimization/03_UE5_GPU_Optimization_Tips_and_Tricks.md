---
title: "1-Hour of Unreal GPU Optimization Tips & Tricks"
source: "https://www.youtube.com/watch?v=c2MH20OPSw0"
video_id: "c2MH20OPSw0"
type: "youtube-summary"
series: "UE5 Optimization"
episode: 3
tags: [ue5, optimization, gpu, nanite, vsm, niagara, lighting, shaders, wpo, megascans]
---

# 1-Hour of Unreal GPU Optimization Tips & Tricks

**Creator:** Tom Looman
**Duration:** 1:02:05 | **Published:** 2024

## Overview

A comprehensive, hands-on GPU optimization walkthrough using the **Megascans Dark Ruins** example project. Tom Looman demonstrates how to identify and fix the most common GPU performance bottlenecks in UE5, targeting both high-end (RTX 4080) and lower-spec hardware (2080 Ti, Steam Deck).

## Optimization Workflow Summary

The video follows this systematic approach:
1. Baseline measurement with `stat GPU`
2. Identify the most expensive render pass
3. Diagnose the root cause with visualization modes
4. Apply targeted fixes
5. Re-measure to verify improvement
6. Repeat for the next most expensive pass

---

## Key Optimization Areas

### 1. Nanite WPO & Virtual Shadow Map Invalidation

**The Problem:**
Many Nanite meshes have materials that evaluate **World Position Offset (WPO)** — often triggered by Contact Shadow functions — without distance limits. This causes Virtual Shadow Map pages to be **dynamically invalidated every frame**, destroying the caching benefit.

**Diagnosis:**
```
# Check VSM cache status
# Viewport > View Mode > Virtual Shadow Map Cached Page
# Blue = dynamically invalidated (bad), Green = cached (good)

# Check which meshes evaluate WPO
# Viewport > View Mode > Nanite > Evaluate WPO
# Green = WPO evaluated (costly), Red = not evaluated (ideal)

r.shadow.virtual.showstats    # Shows dynamic cached shadow page count
```

**Fix:**
- In materials: **disable unnecessary Contact Shadow functions**
- Set **WPO evaluation max distance** in material details
- **Result:** Shadow Depth cost dropped from **1.7ms to 1.0ms**

### 2. Niagara Particle System Culling

**The Problem:**
59 Niagara particle systems were active even when off-screen or far away, consuming CPU and GPU resources with no culling configured.

**Diagnosis:**
```
stat niagara system counts    # See active system count
stat niagara                  # Detailed CPU/GPU costs
```

**Fix — Create and apply Effect Type assets:**
- Create an **Effect Type** asset (Content Browser > Niagara > Effect Type)
- Configure:
  - `Max Time Without Render = 0.5` — stop simulating after 0.5s invisible
  - `Allow Pre-Culling by View Frustum = true` — cull off-screen particles
  - `Update Frequency = Low` — for ambient effects, check ~1/second
- Apply the Effect Type to all Niagara systems

**Result:** Active systems dropped from **59 to 2**. GPU simulation cost dropped from 0.6-0.7ms to **0.02ms**.

### 3. Asset Audit & Nanite Enablement

**Find meshes not using Nanite:**
```
# Disable Nanite visualization to see non-Nanite meshes
showflag.nanite_meshes 0
```

**Fix high-poly non-Nanite assets:**
- Enable Nanite on the mesh
- Change **Fallback Target** from `Percent Triangles (100%)` to `Auto`
- **Result:** A vine asset dropped from ~90MB to **1.2MB**; fallback triangles from 1M to 10K

**Reduce draw calls:**
- Use **Audit > Statistics** to find assets with instance count of 1 (candidates for removal)
- Avoid **Material Instance Dynamic** (breaks Nanite batching)
- Use **Custom Primitive Data** instead for per-instance variation

### 4. Light Optimization

**Attenuation Radius:**
- Ensure each light's attenuation radius is as small as possible
- Larger radius = more pixels to shade + more shadow map coverage

**Max Draw Distance:**
```
# Example settings for environment lights:
Max Draw Distance = 1000
Max Fade Range = 750
```

**Light Count:**
- The scene had 100+ lights — even "not affecting world" lights consume resources
- `stat drawcount` and `stat GPU` > Lights section help quantify impact
- Consider converting dynamic lights to static where possible

### 5. Nanite Max Pixels Per Edge

A powerful quality/performance tradeoff lever:

```
r.Nanite.MaxPixelsPerEdge 4    # Default is 1 (highest quality)
```

- Visually minimal difference at value 4
- **Nanite Vis Buffer** cost dropped from 2.3ms to <2ms
- **Not included in default scalability groups** — must set manually

### 6. Lens Flares & Post-Processing

```
r.lensflarequality 0    # Saves ~0.7ms — consider disabling on low-spec platforms
```

**Tone Mapper Sharpen:**
- Project Settings > `Tone Mapper Sharpen = 2` significantly affects final image clarity
- Disabling it makes the image noticeably blurry — **always enable and test**

### 7. Scalability for Low-Spec Hardware

- Use **Detail Mode** or scalability settings to hide/disable specific meshes, lights, or particles on lower hardware
- For effects using subsurface scattering, consider material-based fakes on low-spec platforms
- Configure `DefaultScalability.ini` with appropriate `PerfIndexThresholds`

## Diagnostic Command Reference

```
stat GPU                              # GPU pass timing breakdown
stat drawcount                        # Draw call counts
stat niagara system counts            # Active particle systems
r.shadow.virtual.showstats            # VSM cache stats
showflag.nanite_meshes 0              # Reveal non-Nanite meshes
r.Nanite.MaxPixelsPerEdge [value]     # Nanite quality tradeoff
r.lensflarequality 0                  # Disable lens flares
```

## Related Resources

- [Tom Looman's Optimization Course](https://courses.tomlooman.com/p/unrealperformance)
- [Tom Looman's Blog](https://tomlooman.com/blog/)
- [Dallas Drapeau: UE5 Optimization Fundamentals](https://www.youtube.com/watch?v=zVNViTNHHdA)


---

## Related

- ← Previous: [[02_How_to_Optimize_Performance_with_Unreal_Insights]]
- 📚 Series: [[_MOC_UE5_Optimization]]
