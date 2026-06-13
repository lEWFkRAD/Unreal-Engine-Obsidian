# UE5 Engine Source Code Access

#ue5 #cpp #engine #reference

> Reference for when we need to build Unreal Engine from source. Not needed for daily development — binary build from Epic Games Launcher is fine.

## Why Source Access?
- Step into engine code when debugging (breakpoints in `ACharacter::Tick`, GAS internals, etc.)
- Read actual implementation instead of guessing from docs
- Patch critical engine bugs to unblock the project
- Understand GAS internals deeply (important for EOA)

## Prerequisites
1. **Epic Games account**
2. **GitHub account**
3. **Link them** at [unrealengine.com/ue-on-github](https://www.unrealengine.com/ue-on-github)
   - Accept EULA → Authorize OAuth → Accept org invitation email (within 7 days)

## Branches
| Branch | Use |
|--------|-----|
| **Release** (e.g. `5.7`) | Stable, QA-tested. Use this. |
| `ue5-main` | Bleeding edge. May not compile. |
| dev/staging/test | Internal Epic. Not useful. |

## Setup (Windows)

```bash
# 1. Fork github.com/EpicGames/UnrealEngine to your account
# 2. Clone your fork
git clone https://github.com/YOUR-NAME/UnrealEngine.git C:\UnrealEngine

# 3. Run setup (downloads binary content, prerequisites)
cd C:\UnrealEngine
Setup.bat

# 4. Generate VS project files
GenerateProjectFiles.bat

# 5. Open UE5.sln in Visual Studio
#    Configuration: Development Editor | Win64
#    Right-click UE target → Build (10-40 min)
#    Set UE5 as startup → F5 to debug
```

## Tools Required
- **Visual Studio** (Community is fine) with [UE required components](https://dev.epicgames.com/documentation/unreal-engine/setting-up-visual-studio-development-environment-for-cplusplus-projects-in-unreal-engine)
- **Git** (GitHub Desktop or CLI)

## Workflow: Binary + Source Side by Side

```
C:\Epic\UE_5.7\          ← Binary build (daily work, faster iteration)
C:\UnrealEngine\         ← Source build (debugging, stepping into engine code)
```

- **Don't** switch your whole project to source build
- Keep binary build for normal development
- Use source build only when you need to step into engine code or patch something

## Debugging With Source Build
1. Open your project with the **source build** engine
2. Open UE5.sln alongside your project
3. Set breakpoints in engine source
4. Attach debugger or launch through VS
5. Step through actual engine code to find root cause

## Key Gotchas
- Forks are tied to your GitHub account — change username or unlink = lose access
- First editor launch from source is slow (one-time content optimization)
- ZIP download: right-click → Properties → **Unblock** before extracting
- `Setup.bat` may trigger SmartScreen → More info → Run anyway

## Links
- [Source code repo](https://github.com/EpicGames/UnrealEngine)
- [Account linking](https://www.unrealengine.com/ue-on-github)
- [Building from source docs](https://dev.epicgames.com/documentation/unreal-engine/building-unreal-engine-from-source)
- [VS setup for UE C++](https://dev.epicgames.com/documentation/unreal-engine/setting-up-visual-studio-development-environment-for-cplusplus-projects-in-unreal-engine)
