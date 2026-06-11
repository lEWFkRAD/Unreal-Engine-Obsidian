---
title: "Replication Instances RepNotify RPCs"
source: "https://www.youtube.com/watch?v=OVeo3cVTIcU"
video_id: "OVeo3cVTIcU"
type: "youtube-summary"
series: "UE5 Multiplayer"
episode: 3
tags: [ue5, multiplayer, replication, repnotify]
---

# Replication Instances RepNotify RPCs

**Source:** https://www.youtube.com/watch?v=OVeo3cVTIcU

## Overview

- **Creator:** Kekdot (two-person game studio focused on multiplayer games)
- **Published:** May 24, 2022
- **Duration:** 22:40
- **Views:** 70,651
- **Focus:** Fundamentals of UE5 multiplayer networking — replication, RepNotify variables, and RPCs
- **Project Files:** Available on [Kekdot's Patreon](https://www.patreon.com/kekdot)
- **Commercial Game:** [The Anomaly Project on Steam](https://store.steampowered.com/app/2960770/The_Anomaly_Project/)

## Content

### Video Chapters

1. **Intro** (0:00)
2. **What is replication?** (0:40)
3. **Applied replication example (Instances)** (1:47)
4. **Replication, Replicated Variables/RepNotify, RPC's** (6:31)
5. **Replicated and RepNotify variables** (10:07)
6. **RPC's** (13:20)
7. **Replicated actor example** (17:10)
8. **Outro** (21:20)

### What is Replication? (0:40)

Replication is the process of **synchronizing the server's instance of the game world to all client instances**. The server maintains the authoritative game state, and the networking system automatically replicates relevant data to connected clients.

Key architectural points:
- The **server** owns the truth
- **clients** receive a filtered, relevant subset of the server's state
- Changes flow: **Server → Clients** (never the reverse for replicated properties)

### Applied Replication Example (1:47)

Demonstrated with instances of replicated actors:

1. Create an Actor with **Replicates** enabled in Class Defaults
2. Place multiple instances in the level
3. Each instance independently replicates its state
4. Show how a change on the server propagates to all clients simultaneously
5. Demonstrate **Relevancy** — only nearby/important actors are replicated to each client

### Three Core Networking Concepts (6:31)

Kekdot breaks down the three pillars of UE5 multiplayer:

#### 1. Replicated Variables
- Properties marked as **Replicated** are automatically synced from server to clients
- Set in variable Details panel: check **Replicated**
- The server sets the value; clients receive it passively
- Example: Health, Ammo, Score, Actor Location

#### 2. RepNotify Variables
- A **Replicated** variable with the **RepNotify** flag enabled
- When the value changes and is received by a client, an `OnRep_VariableName` function fires
- Use this to trigger **client-side reactions** to state changes:
  - UI updates (health bar, ammo counter)
  - Visual effects (damage flash, healing glow)
  - Sound effects (hit marker, pickup sound)

```
Variable: CurrentHealth (Float)
  - Replicated: Yes
  - RepNotify: Yes

// Auto-generated callback:
Event OnRep_CurrentHealth
  → Update Health Bar Widget
  → Play Damage VFX if health decreased
  → Play Healing VFX if health increased
```

**Key insight:** RepNotify fires on clients when the replicated value changes. It does NOT fire on the server. The server must handle the same logic separately if needed.

#### 3. Remote Procedure Calls (RPCs)

RPCs are functions called on one machine that execute on another:

| RPC Type | Caller | Executor | Example |
|----------|--------|----------|---------|
| **Server RPC** | Client | Server | Player presses "Fire" → server validates and applies damage |
| **Client RPC** | Server | Specific Client | Server tells one player "You leveled up" → client shows UI |
| **Multicast RPC** | Server | Server + All Clients | Server triggers explosion → everyone sees/hears it |

**Creating an RPC in Blueprints:**

1. Create a function in the Actor Blueprint
2. Open function Details:
   - **Replicates:** Set to `Run on Server`, `Run on Owning Client`, or `Multicast`
   - **Reliable:** Check for guaranteed delivery (gameplay-critical)
   - **Unreliable:** Leave unchecked for cosmetic events (can be dropped)
3. Call the function — the engine handles routing

### Replicated Actor Example (17:10)

End-to-end walkthrough of a fully replicated actor:

1. **Actor Setup:**
   - Enable **Replicates** in Class Defaults
   - Set **Replicates Movement** if the actor moves

2. **Variables:**
   - `bIsActive` (Bool, Replicated, RepNotify) — tracks actor state
   - `OwnerPlayer` (Actor Reference, Replicated) — who owns this actor

3. **Functions:**
   - `ActivateOnServer` (Server RPC, Reliable) — client requests activation
   - `PlayActivationFX` (Multicast RPC, Unreliable) — visual effect for everyone
   - `OnRep_bIsActive` (RepNotify callback) — client reacts to state change

4. **Flow:**
   ```
   Client presses Interact
     → Calls Server RPC "ActivateOnServer"
     → Server validates and sets bIsActive = true
     → RepNotify fires on all clients → UI updates
     → Server calls Multicast "PlayActivationFX" → everyone sees particle effect
   ```

### Kekdot Series & Resources

- **Multiplayer Blueprint Lobby Solution** (4 videos): [Playlist](https://www.youtube.com/playlist?list=PLNb7FZ2Nw2HSEc5dXQn6V5atONwkuyGOo)
- **Multiplayer Tutorials** (11 videos): [Playlist](https://www.youtube.com/playlist?list=PLNb7FZ2Nw2HTcJ9Qvy8n2Ou-ZVbsDOMFh)
- **UE Marketplace Templates:** [Kekdot on UE Marketplace](https://www.unrealengine.com/marketplace/en-US/profile/KekdotYoutube)
- **Discord:** [Kekdot Discord](https://discord.gg/KfVEGKtrkG)

### Recommended Related Videos

- [Unreal Engine Multiplayer Framework](https://www.youtube.com/watch?v=Hsr6mbNKBLU) — Kekdot (99K views)
- [Multiplayer in UE: How to Understand Network Replication](https://www.youtube.com/watch?v=JOJP0CvpB8w) — Alex Forsythe (217K views)
- [Managing Connected Players](https://www.youtube.com/watch?v=pvDgmnxewuk) — Kekdot (42K views)
- [Hosting and Joining Multiplayer Games](https://www.youtube.com/watch?v=dQD_sPFXcBg) — Kekdot (181K views)
- [RepNotify Explained | Part 1](https://www.youtube.com/watch?v=jtWhd4ugPW0) — Kekdot (19K views)

## Related

- Previous: [[02_Multiplayer_Replication_Basics|Multiplayer Replication Basics]] (Episode 2)
- Series MOC: [[_MOC_UE5_Multiplayer]]
