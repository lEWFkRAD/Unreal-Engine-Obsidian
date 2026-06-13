---
title: "Multiplayer From Day One (Even If You Ship Single-Player First)"
created: 2026-06-13
updated: 2026-06-13
type: concept
tags: [unreal-engine, multiplayer, replication, networking, co-op, architecture, gotchas]
composes: []
composed_by: []
topics: [unreal-engine, game-development, rpg, networking]
workflow: developing
confidence: high
sources: ["https://cedric-neukirchen.net/docs/category/multiplayer-network-compendium/", "https://dev.epicgames.com/documentation/en-us/unreal-engine/networking-and-multiplayer-in-unreal-engine"]
---

# Multiplayer From Day One

The single most expensive mistake in an RPG roadmap that lists co-op as "future": building the whole game single-player-first with no authority discipline, then discovering that bolting on co-op is a rewrite, not a feature.

## Overview

Retrofitting networked co-op into a mature single-player codebase is effectively a rewrite — every direct state mutation becomes a potential desync or exploit. The good news: in Unreal, **single-player already runs as a listen server with one player**. If you respect authority from day one, co-op later becomes closer to a configuration change than a logic overhaul. You do *not* have to build the netcode now — you have to avoid the patterns that make netcode impossible later.

## The blunt truth: authority is non-negotiable

The engine already replicates, runs RPCs, and tracks authority even in single-player. Code that "just mutates `Health` locally" is making a single-player assumption that becomes a race condition the day a second client connects.

```cpp
// BAD — single-player assumption, mutates state anywhere
void AMyCharacter::ApplyHit(float Amount)
{
    Health -= Amount;            // runs on whoever called it; no authority
}

// GOOD — request on client, apply on server
void AMyCharacter::ApplyHit(float Amount)
{
    if (!HasAuthority())         // a client: ask the server, then return
    {
        Server_ApplyHit(Amount);
        return;
    }
    Health -= Amount;            // server is authoritative; replication + OnRep_Health update clients
}
```

(In a GAS project this flows through GameplayEffects instead — see [[01_GAS_Replication_Gotchas]] — but the authority rule is identical: the server owns the change.)

## Day-one habits (cheap now, priceless later)

- **Route gameplay mutations through the server.** Clients *request* via `Server_` RPCs; the server validates and applies. Never trust a client to mutate authoritative state.
- **Mark gameplay-critical `UPROPERTY`s `Replicated`**, and drive UI from `OnRep_` handlers — not from `Tick` reading local state.
- **Know your RPCs:**
  - `Server_` — client → server (authoritative request; mark `WithValidation`).
  - `Client_` — server → one owning client (UI, personal feedback).
  - `NetMulticast` — server → all clients (shared VFX/SFX, cosmetic).
- **No gameplay logic in client-only places.** UI and client Tick *react* to replicated state; they don't decide it.

## Lean on systems that are already network-aware

Don't hand-roll replicated state machines for things the engine already nets for you:

- **GAS** — abilities, cooldowns, effects, and tags are built for replication and prediction.
- **CharacterMovementComponent** — client prediction, server reconciliation, and smoothing are solved; custom movement frequently breaks all three.
- If you must write custom shared state, design its `GetLifetimeReplicatedProps` from the start — an un-replicated bespoke struct is a liability you'll pay for at co-op time.

## Scope warning: open-world co-op is a trap

Full **open-world shared** co-op (streaming sync, distributed AI, world state across clients, session management, bandwidth) is one of the hardest problems in the medium and rare even in shipped AAA RPGs. Most "co-op" in big RPGs is **instanced or bounded**, not a shared seamless open world. Don't attempt open-world co-op without a dedicated networking specialist.

## Recommendation: scope co-op to the Tower

```text
+----------------------+        +----------------------+
|   Open World (SP)    |        |     Tower (Co-op)    |
|   - WP streaming     |  portal|   - instanced level  |
|   - persistent state | -----> |   - bounded geometry |
|   - single player    |        |   - replicated state |
+----------------------+        +----------------------+
```

*Echoes of Ascension* already plans "Co-op Tower ascent" — that instinct is correct. The Tower is **instanced, bounded, and self-contained**, which removes the worst networking problems (open-world streaming sync, persistent shared world state). Keep the open world single-player; make the Tower the co-op sandbox. This is the difference between "achievable for a solo dev" and "never ships."

## Cost reality

Replication roughly **doubles** your testing and debugging surface. Budget for it explicitly and test networked early:

- Run PIE with **Number of Players = 2** (and "Run Under One Process" off, occasionally, to catch true network paths).
- Test client join/disconnect, lag (use net emulation / `Net PktLag`), and authority edge cases.

| Aspect | SP-only, no discipline | Network-aware from day one |
|--------|------------------------|----------------------------|
| Early dev speed | Faster | Slightly slower (authority checks) |
| Cost to add co-op later | Effectively a rewrite | Add netcode to a clean base |
| Testing surface | Low | Higher (net PIE, lag, joins) |
| Co-op feasibility | Near zero | High, if scoped to the Tower |

The cost of writing `HasAuthority()` and a `Server_` RPC today is negligible. The cost of re-architecting combat, inventory, and abilities for replication after the fact is the project.

---

- ← Previous: [[02_OpenWorld_Save_Architecture]]
- → Next: [[04_Procedural_Tower_Generation]]
- 📚 Series: [[_MOC_UE5_Gotchas]]
- 🔗 Related: [[01_GAS_Replication_Gotchas]]
