# EchoesCore — UE 5.7 Starter Module

A small, **reviewed** C++ scaffold for the *Echoes of Ascension* vertical slice. It gives you the boilerplate that's easy to get subtly wrong — the GAS triad, an async save system, and a deterministic floor planner — so you can spend your time on the game-specific parts (abilities, Echo modifiers, room art).

> ⚠️ **Honest status:** this is **scaffolding, reviewed for API correctness against UE 5.7 — but not yet compiled against the engine** (it was authored outside an engine install). Treat the first build as a "fix the include/UFUNCTION nits" pass, not plug-and-play. Every file is small and commented so that pass is quick. It was drafted on a local model and corrected by hand; the known first-draft errors that were fixed are listed at the bottom.

## What's in it

| File(s) | Role | Gotcha doc |
|---|---|---|
| `EchoesPlayerState` | Owns the ASC + AttributeSet (ASC-on-PlayerState, Mixed replication, 100Hz) | `UE5_Gotchas/01` |
| `EchoesAbilitySystemComponent` | Project ASC subclass (empty hook point) | `01` |
| `EchoesAttributeSet` | Health / MaxHealth / Aether / MaxAether / AttackPower, replicated + clamped | `01` |
| `EchoesCharacter` | Avatar; correct `InitAbilityActorInfo` timing (server + owning client) | `01` |
| `EchoesGameplayAbility` | Base ability (InstancedPerActor, InputTag) | `01` |
| `EchoesSaveGame` | Profile + Run save objects (`UPROPERTY(SaveGame)`) | `02` |
| `EchoesSaveSubsystem` | Async save/load, profile-vs-run, versioning hook | `02` |
| `EchoesPersistentIdComponent` | Stable GUID identity for persistable actors | `02` |
| `EchoesBiomeDataAsset` | Data-driven biome (soft level ref, weight) | `04` |
| `EchoesFloorGenerator` | Deterministic floor plan (seed, no-repeat biome, boss cadence) | `04` |

(The `UE5_Gotchas/` docs live in the Unreal-Engine-Obsidian vault — read the matching one before you touch each system.)

## Slice scaffold (combat / enemy / echoes loop)

A second wave that takes the core from "systems" toward a *playable* vertical slice:

| File(s) | Role |
|---|---|
| `EchoesGameplayTags` | Native gameplay tags (`InputTag.*`, `Ability.*`, `Data.Damage`, `State.Dead`). |
| `EchoesDamageExecution` | A GAS Execution Calc: source AttackPower (+ SetByCaller) → the target's `Damage` meta-attribute. Assign as the Execution on your `GE_Damage`. |
| `EchoesAttributeSet` (extended) | Added a transient `Damage` meta-attribute; `PostGameplayEffectExecute` drains it into a Health loss (death TODO marked). |
| `EchoesAbilitySystemComponent` (extended) | `AbilityInputTagPressed(Tag)` — fires granted abilities whose `InputTag` matches. Bind your Enhanced Input actions to this. |
| `EchoesEnemyCharacter` + `EchoesAIController` | An AI enemy (ASC-on-pawn, Full replication) that runs a Behavior Tree. |
| `EchoesGameMode` | Wires `AEchoesCharacter` + `AEchoesPlayerState`. |
| `EchoesEchoDataAsset` + `EchoesEchoLibrary` | The Echoes hook: an Echo is a data asset holding an infinite GameplayEffect; `BindEcho`/`UnbindEcho` apply/remove it on an ASC. |

**Wiring these (after it compiles):**
1. **Damage:** make a `GE_Damage` (instant) GameplayEffect, add `UEchoesDamageExecution` as its Execution. Apply it from your attack ability.
2. **Input:** create Enhanced Input `InputAction`s, add a Mapping Context, and in your player controller/character `BindAction(...)` → `ASC->AbilityInputTagPressed(EchoesTags::InputTag_Attack)` etc. Set the matching `InputTag` on each ability Blueprint.
3. **Enemy:** Blueprint-child `AEchoesEnemyCharacter`, set its `AIControllerClass` to `AEchoesAIController`, give the controller a Behavior Tree, assign a `GE_InitStats` to `DefaultAttributesEffect`.
4. **Echoes:** make `UEchoesEchoDataAsset` assets (each pointing at an infinite `GE_*` modifier), and call `UEchoesEchoLibrary::BindEcho` from your shrine's bind UI.

See `design/02_MILESTONE_BACKLOG.md` — this scaffold covers the C++ spine of M1–M4.

## How to drop it into a project

1. Create (or open) a UE **5.7 C++** project.
2. Copy `Source/EchoesCore/` into your project's `Source/` folder.
3. Register the module in your `.uproject` `Modules` array:
   ```json
   { "Name": "EchoesCore", "Type": "Runtime", "LoadingPhase": "Default" }
   ```
4. Add `"EchoesCore"` to `ExtraModuleNames` in your `Source/<Project>.Target.cs` and `<Project>Editor.Target.cs`.
5. Enable the **Gameplay Abilities** plugin (Edit → Plugins), restart.
6. Right-click the `.uproject` → **Generate Visual Studio project files**, then build.
7. Wire your GameMode to use `AEchoesCharacter` + `AEchoesPlayerState`, author a `GE_InitStats` GameplayEffect and assign it to the character's `DefaultAttributesEffect`, and add one ability to `DefaultAbilities`.

Then follow `design/02_MILESTONE_BACKLOG.md` from **M1**.

## What you still write (it's intentionally not here)
The *game*: the actual ability Blueprints, the GameplayEffect/DataAsset *assets* (the C++ Execution and data classes are provided — you author the GE/Echo assets that use them), the Behavior Tree, the room modules, and the UI. The scaffold ends where your design begins.

## First-draft errors corrected during review (transparency)
Core module:
- `Data.EvaluatedAttributes.ContainsAttribute(...)` → `Data.EvaluatedData.Attribute == ...` (real API) in the AttributeSet.
- `ASC->GetLevel()` → literal `1.f` in `MakeOutgoingSpec` (ASC has no reliable `GetLevel`).
- A hallucinated `ActivateAbility` override signature on the base ability → removed.
- Non-idiomatic `#include "EchoesCore/Public/..."` paths → bare header names.
- The save subsystem + persistent-id component were dropped by a truncated generation → hand-authored.
- Boss-floor cadence guarded so floor 0 isn't a boss.

Slice scaffold:
- `EchoesGameMode` — the generator melted into a `GENERATED_BODYONLY…` loop; rewritten from scratch.
- `EchoesEchoDataAsset`/`Library` — fake `#include "CoreObject.h"` → `CoreMinimal.h` + `Engine/DataAsset.h`; a garbage `Text DisplayName;` line removed; `GameplayEffectTypes.h` added so `FActiveGameplayEffectHandle` is complete for UHT.
- `EchoesEnemyCharacter` — `MakeOutgoingSpec` was passed a CDO pointer → now the `TSubclassOf`; removed a non-existent `Context.AddSourceActor`.
- `EchoesDamageExecution` — `Execute_Implementation` missing `const` (wouldn't override) → fixed; `Spec.SetByCallerTagMap.Contains` (wrong member) → `GetSetByCallerMagnitude(tag, false, 0)`.
