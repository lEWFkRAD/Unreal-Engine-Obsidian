---
title: "UE5 Gotchas & Hard-Won Patterns — Map of Content"
type: "moc"
tags: [ue5, moc, index, gotchas, architecture]
---

# UE5 Gotchas & Hard-Won Patterns

The things tutorials skip — the architecture decisions and engine traps that only show up after you've shipped a bug. Each note pairs a general UE5 pattern with a concrete mapping onto an open-world RPG (the *Echoes of Ascension* stack: GAS, open world, a procedural co-op tower, 60 FPS with Nanite/Lumen/Niagara/Chaos).

These complement the tutorial folders (which teach *how*) and the [[_MOC_Architecture]] docs (which teach *how to think*) by focusing on *what will break and why*.

**Files:** 5

## Notes

- [[01_GAS_Replication_Gotchas]] — replication modes, ASC on PlayerState vs Pawn, the Mixed-mode Owner trap, InitAbilityActorInfo timing
- [[02_OpenWorld_Save_Architecture]] — persistence under World Partition, GUID identity, profile-vs-run saves, versioning
- [[03_Multiplayer_From_Day_One]] — why retrofitting co-op is a rewrite, authority discipline, scoping co-op to the instanced Tower
- [[04_Procedural_Tower_Generation]] — deterministic seeding, PCG for decoration not layout, the runtime-NavMesh gotcha, connectivity validation
- [[05_Performance_Budget_Reality]] — the 16.6 ms budget, software vs hardware Lumen, async loading, Niagara/Chaos budgets

## See also

- [[ue5-canonical-references]] — stable, authoritative external references (Epic docs, tranek, vorixo, Cedric's Network Compendium, Tom Looman, Lyra)
