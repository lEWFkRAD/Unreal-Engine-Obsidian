---
title: Unreal Engine C++ Foundations
created: 2026-05-19
updated: 2026-05-19
type: concept
tags: [unreal-engine, cpp, game-development, uobject, reflection, garbage-collection]
composes: [unreal-engine-gameplay-ability-system, unreal-engine-rpg-systems]
topics: [unreal-engine, game-development, cpp]
workflow: developing
confidence: high
sources: [raw/articles/unreal-engine-skills, raw/articles/GASDocumentation]
---

# Unreal Engine C++ Foundations

The UObject system is the root of everything in Unreal Engine C++. Every gameplay class inherits from it (directly or through `AActor`).

## The Three Pillars of UE C++

### 1. Reflection System (`UCLASS` / `UPROPERTY` / `UFUNCTION`)

These macros expose C++ to the engine — enabling editor integration, Blueprint exposure, serialization, garbage collection, and network replication.

| Macro | Purpose |
|-------|---------|
| `UCLASS()` | Declares a UObject subclass |
| `USTRUCT()` | Declares a lightweight struct |
| `UENUM()` | Declares a reflected enum |
| `UPROPERTY()` | GC tracking, serialization, editor, BP exposure |
| `UFUNCTION()` | Reflection, BP callable, RPC support |
| `GENERATED_BODY()` | Required in every UCLASS/USTRUCT/UENUM body |

### 2. Garbage Collection (Reference Graph)

Unreal's GC is **tracing, not reference-counted**. It walks a reference graph starting from a root set and collects unreachable objects.

**Critical rules:**
- Every UObject pointer member must have `UPROPERTY()` — without it, GC can collect the object while you still hold the pointer
- Never `new` / `delete` a UObject — use `NewObject<T>()`, `SpawnActor<T>()`, `CreateDefaultSubobject<T>()`, and `->Destroy()`
- `UPROPERTY()` pointers to destroyed Actors/Components are **automatically nulled**

### 3. Composition over Inheritance

The engine is built around `AActor` (a container) owning `UActorComponent` subclasses (reusable behavior units).

```
UObject
  └── AActor                     (placeable world entity)
        └── UActorComponent      (logic — health, inventory, AI)
              └── USceneComponent    (adds transform)
                    └── UPrimitiveComponent (adds collision + rendering)
```

## Pointer Type Cheat Sheet

| Type | When to Use |
|------|-------------|
| `TObjectPtr<T>` (UE5) | In headers for UProperties |
| `T*` raw pointer | In `.cpp` files, locals, function params |
| `TSoftObjectPtr<T>` | Reference assets without loading |
| `TWeakObjectPtr<T>` | Non-owning reference, auto-nulled |
| `TSharedPtr<T>` / `TUniquePtr<T>` | Non-UObject C++ objects |

## Key Patterns for Solo RPG Dev

- `TObjectPtr<T>` in headers, `T*` in `.cpp`
- Every UObject member needs `UPROPERTY()`
- Never touch `GetWorld()` in constructors (CDO has no world)
- Always call `Super::` in lifecycle overrides
- Prefer `UActorComponent` over deep inheritance hierarchies
- Use `TSoftObjectPtr` for any asset not loaded at startup

## Related

- [[unreal-engine-gameplay-ability-system]] — built on these foundations
- [[unreal-engine-rpg-systems]] — uses these patterns for inventory, quests, dialogue
- [[unreal-engine-blueprint-hybrid-workflow]] — C++/BP boundary decisions
- AI-assisted coding — LLM patterns that apply to UE C++

## External Source

The definitive reference is the cloned `tranek/GASDocumentation` at `github.com/tranek/GASDocumentation`. For quick reference, the `quodsoler/unreal-engine-skills` repo provides 27 audited skill files covering every UE subsystem — installable via the agentskills.io spec.
