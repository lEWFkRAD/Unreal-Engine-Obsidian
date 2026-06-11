---
title: "Multiplayer Replication Basics"
source: "https://www.youtube.com/watch?v=ef6SeknakeU"
video_id: "ef6SeknakeU"
type: "youtube-summary"
series: "UE5 Multiplayer"
episode: 2
tags: [ue5, multiplayer, replication, rpcs]
---

# Multiplayer Replication Basics

**Source:** https://www.youtube.com/watch?v=ef6SeknakeU

## Overview

- **Creator:** Gorka Games (173K subscribers)
- **Published:** January 22, 2023
- **Duration:** 17:17
- **Focus:** Quick and simple tutorial on multiplayer replication basics for UE5 online games
- **Creator Bio:** Game Developer with 7+ years of experience in Unity and Unreal Engine. Commercial project: Bromeliad (on Steam)

## Content

### Video Chapters

1. **Intro** (0:00)
2. **Replication Basics** (0:15)
3. **Replicating Objects** (5:00)
4. **Creating an RPC** (9:25)

### Replication Basics (0:15)

Key concepts for UE5 networking:

- **Server-Client Model:** UE5 uses a dedicated server (or listen server) model. The server is authoritative.
- **Network Authority:** Only the server has authority over game state. Clients are "simulated proxies" of the server's world.
- **Replication:** The process of the server sending updated state to clients automatically.

**Important nodes:**
- `Switch Has Authority` — branch logic between server and client
- `Is Locally Controlled` — check if the current machine owns this Pawn

### Replicating Objects (5:00)

Step-by-step to replicate an Actor:

1. **Create an Actor Blueprint**
2. Go to **Class Defaults** → check **Replicates**
3. For variables:
   - Select variable → Details panel → check **Replicated**
   - Optionally check **RepNotify** to get an `OnRep_` callback
4. **Modification must happen on the server** — client-side changes to replicated variables are ignored

**Demonstrated example:** A replicated variable that changes on the server and automatically updates on all clients.

### Creating an RPC (9:25)

**RPCs (Remote Procedure Calls)** allow calling functions across the network:

#### Types of RPCs

| Type | Callable From | Executes On | Use Case |
|------|--------------|-------------|----------|
| **Server** | Owning Client | Server | Request state change (fire weapon, pick up item) |
| **Client** | Server | Owning Client | Notify specific player (UI update, personal feedback) |
| **Multicast** | Server | Server + All Clients | Global events (explosions, game state changes) |

#### Creating a Server RPC

1. Create a function in the Actor Blueprint
2. In function Details panel:
   - Set **Replicates** to **Run on Server**
   - Check **Reliable** (guaranteed delivery) or **Unreliable** (can be dropped)
3. Call this function from the client — it executes on the server

#### Creating a Client RPC

1. Create a function
2. Set **Replicates** to **Run on Owning Client**
3. Call from server — it executes on the owning client only

#### Creating a Multicast RPC

1. Create a function
2. Set **Replicates** to **Multicast**
3. Call from server — it executes on the server AND all connected clients

### Reliability

- **Reliable:** Guaranteed to arrive, ordered. Use for critical events (damage, death, item pickup). Can cause issues if overused — fills the reliable buffer.
- **Unreliable:** May be dropped under network congestion. Use for cosmetic events (particles, sounds, cosmetic animations).

### Best Practices from Gorka Games

- Only replicate what's necessary — minimize bandwidth
- Use **Unreliable** RPCs for visuals; **Reliable** for gameplay-critical events
- Always validate on the server — never trust client input directly
- Test multiplayer early and often with `PIE → 2+ players`
- Use `Print String` with authority checks to debug replication flow

## Related

- Previous: [[01_Replication_Basics|Replication Basics]] (Episode 1)
- Next: [[03_Replication_Instances_RepNotify_RPCs|Replication Instances RepNotify RPCs]] (Episode 3)
- Series MOC: [[_MOC_UE5_Multiplayer]]
