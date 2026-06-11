---
title: "Replication Basics"
source: "https://www.youtube.com/watch?v=bBK8A-mFH-s"
video_id: "bBK8A-mFH-s"
type: "youtube-summary"
series: "UE5 Multiplayer"
episode: 1
tags: [ue5, multiplayer, replication]
---

# Replication Basics

**Source:** https://www.youtube.com/watch?v=bBK8A-mFH-s

## Overview

- **Creator:** Pitchfork Academy
- **Duration:** 44:49
- **Focus:** Introduction to the basics of replication and how to make a multiplayer game in Unreal Engine 5

## Content

### What is Replication?

Replication is Unreal Engine's system for synchronizing game state between a **server** and connected **clients**. In UE5's client-server architecture:

- The **Server** is the authoritative source of truth for all game state
- **Clients** receive replicated data from the server to keep their local world in sync
- Only the server can authoritatively change replicated state

### Core Concepts

#### Authority
- **Has Authority:** Code runs on the server
- **Is Locally Controlled:** Code runs on the owning client (the player who owns this pawn)
- Use **Switch Has Authority** nodes to branch server vs. client logic

#### Replicated Properties
- Mark properties as **Replicated** in the variable details panel
- The server sets the value, and it automatically propagates to all clients
- Use **RepNotify** to fire a function on clients whenever the value changes

#### Net Ownership
- Each Actor can have an **Owner** — typically the PlayerController
- Ownership determines which client receives certain replicated data
- Use `Set Owner` or `Set Owner Controller` to manage ownership

### Setting Up a Replicated Actor

1. **Create an Actor Blueprint**
2. In **Class Defaults**, check **Replicates** — this enables network replication
3. For variables you want synced:
   - Select the variable
   - In Details panel, check **Replicated**
   - Optionally set to **RepNotify** to trigger a callback on change

### Example: Replicated Health

```
Variable: Health (Float)
- Replicated: Yes
- RepNotify: Yes

Event Graph:
  OnRep_Health:
    → Update Health Bar UI
    → Play damage/heal effects
```

### Net Relevancy

- Actors are only replicated to clients where they are **relevant**
- Default relevancy is based on:
  - Actor's net relevancy distance
  - Whether the actor is always relevant (e.g., GameState)
  - Whether the actor is relevant to its owner only
- Use `Set Net Relevancy` and `Always Relevant` flags to control this

### Replication Flow

1. Server modifies a replicated variable
2. Engine detects the change during the next net update
3. Server sends the delta to relevant clients
4. Clients receive and apply the update
5. If RepNotify, the callback function fires on the client

### Best Practices

- **Minimize replicated variables** — only replicate what clients need
- **Use Net Relevancy** to avoid sending data to distant players
- **Replicate from server only** — client-side changes to replicated vars are ignored
- **Use RPCs** for one-shot events (sounds, particles, UI notifications)
- **Test with 2+ instances** using PIE with multiple players (`Play → Net Mode → Play As Client`)

## Related

- Next: [[02_Multiplayer_Replication_Basics|Multiplayer Replication Basics]] (Episode 2)
- Series MOC: [[_MOC_UE5_Multiplayer]]
