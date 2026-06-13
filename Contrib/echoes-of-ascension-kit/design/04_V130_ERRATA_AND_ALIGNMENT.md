# v1.3.0 Errata & Alignment Note

A friendly cross-check of the new `UE5_CPP/` references (v1.3.0) against current **UE 5.7** and the starter kit. **The references are strong and faithful to Epic's material** — the items below are spots where the source pages included **legacy (UE3/UE4-era) patterns** that changed in UE5. Modernizing them saves you from dead-end rabbit holes (following the old module-setup steps in particular would cost you a day).

Everything here is verified against current 5.7, and the starter kit (`StarterCode/EchoesCore`) already does it the modern way — so the code and the docs agree once these are fixed.

---

## `UE5_Gameplay_Framework_Reference.md`

| Doc says | Current UE 5.7 | Why it matters |
|---|---|---|
| `DisplaySphere->AttachTo(RootComponent)` | **`SetupAttachment(RootComponent)`** in constructors (`AttachToComponent(...)` at runtime) | `AttachTo` has been deprecated since ~UE4.12; it compiles with warnings or fails under strict builds. |
| Module header: `#include "Engine.h"` / `"EnginePrivate.h"` / `"<ModuleName>Classes.h"` | None of these. A UE5 module needs no such header; classes are discovered by UHT. Use per-file includes + `CoreMinimal.h`. | This is UE3/early-UE4 module style. Following it produces missing-header errors. |
| `IMPLEMENT_PRIMARY_GAME_MODULE(<ModuleName>, "<GameName>")` | **3 args:** `IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, ModuleName, "GameName")` | The first arg (the module-impl class) is missing in the doc. The kit's `EchoesCore.cpp` shows the correct form. |
| `public <ModuleName>(TargetInfo Target)` in Build.cs | **`public <ModuleName>(ReadOnlyTargetRules Target) : base(Target)`** | `TargetInfo` is UE4-era; modern Build.cs requires `ReadOnlyTargetRules` + the `: base(Target)` call. See the kit's `EchoesCore.Build.cs`. |
| INI module registration: `[UnrealEd.EditorEngine] +EditPackages=`, `[Launch] Module=`, `[/Script/Engine.UObjectPackages] +NativePackages=` | **Obsolete.** Register modules in the **`.uproject`** `Modules` array + **`*.Target.cs`** `ExtraModuleNames`. | This is the big one — these INI keys do nothing in UE5. The kit's `StarterCode/README.md` has the correct registration steps. |
| `OutExtraModuleNames` | **`ExtraModuleNames`** (no `Out` prefix) | Minor naming. |
| `static FClassFinder<...>` | **`ConstructorHelpers::FClassFinder<...>`** | Needs the `ConstructorHelpers::` scope (the `FObjectFinder` example in the same doc has it; the class one dropped it). |

## `UE5_GAS_Reference.md`

This one is in good shape. One modernization note:

- **Instancing Policy:** the doc lists `Instanced per Execution` and `Non-Instanced`. Both are **deprecated as of UE 5.5**; 5.7 expects **`InstancedPerActor`** for essentially all abilities. Treat `InstancedPerActor` as the default and ignore the other two unless maintaining old content. (The kit's `EchoesGameplayAbility` sets `InstancedPerActor` in its constructor.)

Otherwise the GAS reference is accurate and current (the component-based GameplayEffect system, the NetExecutionPolicy table, the meta-attribute setter pattern all check out).

---

## How the v1.3.0 references and this kit fit together

They're **complementary layers** — keep both:

```
Epic-faithful REFERENCE  →  WHAT-BREAKS gotchas  →  WORKING starter code
(your UE5_CPP/ v1.3.0)      (UE5_Gotchas/ docs)     (EchoesCore module)
 "what the API is"          "what bites you"         "a correct example"
```

Suggested cross-links to add in your vault (so the graph connects the layers):

- In `UE5_CPP/UE5_GAS_Reference.md` → link to `[[01_GAS_Replication_Gotchas]]` (it covers the replication modes / ASC-placement / init-timing that a pure API reference doesn't).
- In `UE5_CPP/UE5_Gameplay_Framework_Reference.md` → link to `[[02_OpenWorld_Save_Architecture]]` and the kit's module setup.
- In `UE5_Gotchas/_MOC_UE5_Gotchas.md` → already links to `[[ue5-canonical-references]]`; add a pointer to `UE5_CPP/_MOC_UE5_CPP`.

Net: your reference tells you the API, the gotchas tell you where it bites, and the kit hands you a compiling example. Three layers, one path from "what is this" to "shipped."
