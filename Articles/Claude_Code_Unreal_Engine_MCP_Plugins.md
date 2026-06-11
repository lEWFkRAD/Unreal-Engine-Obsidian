---
title: "Claude Code + Unreal Engine 5: 2 Free MCP Plugins to Build Games with AI"
source: "https://www.top3d.ai/learn/claude-code-unreal-engine"
video_id: ""
type: "article-summary"
series: "Articles"
episode: 0
tags: [ue5, mcp, claude-code, ai-coding, blueprint, unrealclaude, vibeue, article]
---

# Claude Code + Unreal Engine 5: 2 Free MCP Plugins to Build Games with AI

**Source:** https://www.top3d.ai/learn/claude-code-unreal-engine

---

## Overview

Claude Code **can** drive Unreal Engine 5 — move objects, edit Blueprints, run the game, and review results. The proven setup uses **two free, open-source plugins together**:

- **[UnrealClaude](https://github.com/Natfii/UnrealClaude)** — viewport screenshots + actor manipulation over MCP
- **[VibeUE](https://www.vibeue.com/)** — Blueprint editing + Python over MCP (free API key required)

> *"Almost every 'AI for Unreal' plugin I tried either did not work or wanted money for the part that matters."*

**The only cost is Claude itself.**

---

## The Two Free Plugins

### UnrealClaude — Eyes and Hands in the Viewport
- **600+ GitHub stars**, MIT-licensed, targets **UE 5.7**
- Ships an **MCP server with 20+ editor tools**
- Core capabilities: **capture the viewport** (Claude sees what it built) and **move objects** around the scene
- Works independently with just your Claude auth

> *That "take a screenshot and review yourself" loop is the single most useful thing in the whole setup.*

### VibeUE — Blueprints and Python
- Open-source, but pairs with its own dashboard → needs a **free API key** (browser login at vibeue.com)
- Skip the paid agent — only the **MCP tools** are needed
- Capabilities: **edit Blueprints, run Python scripts, work with assets and materials**

---

## Setup & Installation

### Prerequisites
- **Unreal Engine 5.7** + **[Claude Code](https://www.claude.com/claude-code)**
- Open Claude Code **in the folder of your Unreal project**
- Install **Git** first; commit at every milestone

### Installation Steps

1. **Install both plugins** — Paste the two repo links and tell Claude to handle it. It pulls dependencies (Node.js, Microsoft C++ libraries). Use a good `CLAUDE.md` in the project root.

2. **Get the free VibeUE API key** — Sign in at vibeue.com, copy the key from the dashboard, paste into VibeUE settings (gear icon) inside Unreal Editor and save.

3. **Install MCPs and restart editor** — Ask Claude to *install all the MCPs*, then restart the Unreal project and sometimes Claude Code.

4. **Check both connections:**

```bash
# Quick confirmation both bridges are up:
curl http://localhost:3000/mcp/status   # UnrealClaude
curl http://127.0.0.1:8088/mcp          # VibeUE  (405/200 = alive)

# In Claude Code, the simplest check:
#   "check both mcp connections"
```

### CLAUDE.md — Critical Configuration File
A `CLAUDE.md` in the project root saves tokens and trial-and-error. It contains:
- `.mcp.json` wiring
- VibeUE skill library references
- ~20 hard-won UE 5.7 gotchas (Blueprint edits locking during Play, FBX-import crash fix, silent button OnClicked no-op, etc.)

> *Whenever Claude Code hits a real problem, spends time working it out, and lands a fix, ask it to **write that solution into CLAUDE.md**.*

---

## Stress Test: Building an Endless Runner from Prompts

### Methodology
- Started from a **third-person template** with an AI-generated modular fox character
- Described features one at a time, **committed after each working step**
- Used a consistent agentic loop: **edit via Python → run game → screenshot viewport → read result → fix**

### Build Milestones

| Step | What Was Built | Notes |
|------|---------------|-------|
| 1 | Infinite scrolling path on grey-box tiles | `BP_RunnerTile` with readable variables; Claude screenshots viewport to verify placement |
| 2 | Auto-run, top-down camera, three lanes (A/D) | Logic works but **Blueprint layout is spaghetti** — supervision needed |
| 3 | Obstacles, coins, rising speed | **~15 min, ~14k tokens of Opus 4.8**; coins don't avoid obstacles unless explicitly asked |
| 4 | Score, coin counter, Game Over + Retry UI | Functional rough HUD in a single pass |
| 5 | Swap grey-boxes for AI-generated 3D assets | Assets from ChatGPT concept → 3D models; Claude wires them in |
| 6 | Skybox, PBR materials, bug fixes | Claude used **line traces** to map bridge geometry and fix obstacle clipping |

> *Give it detailed logic and architecture — describe how a feature should work and how it should scale — and you get amazing results.*

### Asset Workflow
- **You** prepare/generate 3D assets (Claude is not a 3D generator)
- Export as FBX in a zip, drop into project, add a screenshot
- **Claude** figures out proper names and does placement logic

### Bug Fix Example
When obstacles clipped into bridge railings, Claude *"fired a batch of **line traces** to map the bridge's real geometry, then nudged the obstacles off the railings based on what the traces hit — measurement, not guesswork."*

---

## Honest Verdict

### Strengths
- ✅ Detailed, logical prompts → excellent results
- ✅ Self-reviewing agent (runs game, screenshots, reads, fixes)
- ✅ Massive boost for people who understand what they're asking for
- ✅ Works as a **learning partner** — ask it *why* a node is there and what patterns

### Weaknesses
- ⚠️ Without detailed prompts, results are mediocre
- ⚠️ Blueprint spaghetti needs human supervision
- ⚠️ You still need to understand game dev fundamentals

### Key Takeaway
The two-plugin combo (UnrealClaude + VibeUE) gives Claude Code full visibility into Unreal — viewport, Blueprints, Python, and assets. The screenshot-review loop is what makes it actually work.