---
title: "How to Package Your UE5.7 Project and Share It"
source: "https://www.youtube.com/watch?v=AWzhZnSq9u0"
video_id: "AWzhZnSq9u0"
type: "step-by-step-guide"
series: "Step-by-Step Guides"
episode: 2
tags: [ue5, packaging, distribution, project-settings, guide]
---

# How to Package Your Unreal Engine 5.7 Project and Share It

**Source:** https://www.youtube.com/watch?v=AWzhZnSq9u0
**Duration:** ~19 minutes
**Extracted from:** `How_to_package_your_Unreal_Engine_5.7_project_and_share_it_with_everyone!.md`

---

## Overview

Packaging a UE5 project means building it into a standalone executable that can be shared with others. The process has three phases: **Build** → **Cook** → **Package**.

---

## Step 1: Set Your Startup Map and Game Mode

1. Go to **Edit → Project Settings → Maps & Modes**.
2. Set **Game Default Map** to your starting/arena map.
3. Set **Default Game Mode** to your custom game mode (e.g., Shooter Game Mode).
4. This ensures the packaged game knows which map to load and which rules to use.

---

## Step 2: Create a Launch Profile

1. Go to **Platforms** (top toolbar) → **Project Launcher** (or Quick Launch → Project Launcher).
2. Click **+** to create a new **Launch Profile**.
3. Configure the profile:
   - **Project:** Your current project (default).
   - **Platform:** Windows (only shows platforms with installed SDKs).
   - **Configuration:** Development (for testing/debugging) or Shipping (for release — strips debug info and console commands).
   - **Content Scheme:** Use "Pak files" (packages assets into .pak files — prevents easy asset theft).
   - **Compress Pak Files:** Enable this to reduce file size (slightly slower build).
   - **Cook Content:** Enable (converts assets to platform-specific formats).
   - **Incremental Cook:** "Modify and dependencies" (recommended).
   - **Maps to Cook:** Use "Startup Maps" for development (reusable across projects). For shipping, select only the maps players will use.
   - **Build the Game:** Enable.
   - **Archive Build:** Enable (saves to a directory instead of deploying).
   - **Deploy:** Disable (we want to run locally, not deploy to a device).

---

## Step 3: Choose an Output Directory

1. Set the archive path to a location **close to the root of your drive** (e.g., `C:\Builds\`).
2. **Why?** Deeply nested folder paths can exceed Windows' character limit and cause build failures.
3. Create a new folder for your build output.

---

## Step 4: Launch the Build

1. Click **Launch** on your Development build profile.
2. The packaging process begins in three phases:

### Phase 1: Build
- Compiles all C++ code and Blueprint classes.
- **If this fails:** You have a programming error (missing texture, null reference, etc.). Warnings are non-fatal.

### Phase 2: Cook
- Converts all assets (meshes, textures, audio, video) to platform-specific formats.
- Strips editor-only data (collision editing properties, etc.) that isn't needed at runtime.
- **First-time cooking takes 10-30 minutes.** Subsequent cooks are much faster.
- **If this fails:** Usually a missing reference or a problematic asset.

### Phase 3: Package
- Wraps cooked assets into .pak files and creates the final executable.
- Creates the `.exe`, engine binaries, and a `Content` folder with your packaged assets.

---

## Step 5: Test the Build

1. Navigate to your output folder (e.g., `C:\Builds\MyProject\`).
2. Find the `.exe` file and double-click to run it.
3. In a Development build, press **`** (apostrophe) to open the console. Type `stat unit` to see FPS.
4. Test gameplay, collisions, and all features.

---

## Step 6: Share the Build

1. **Right-click** the build folder → **Compress to ZIP**.
2. Share the ZIP file with others.
3. Recipients extract and run the `.exe`.

---

## Step 7: Include Prerequisites (Optional)

1. Go to **Platforms → Packaging Settings**.
2. Enable **"Include prerequisite installer"**.
3. This adds ~extra MB but ensures non-developer players get required runtime libraries.
4. **Exception:** If uploading to Steam, Steam handles prerequisites automatically — you can leave this off.

---

## Key Differences: Development vs Shipping

| Setting | Development | Shipping |
|---|---|---|
| Console commands | Available (`stat unit`, etc.) | Stripped out |
| Debug symbols | Included | Stripped |
| File size | Larger | Smaller |
| Use case | Testing/debugging | Final release |

---

## Pro Tips

- **PSO Precaching:** To reduce loading stutters, search for "PSO precaching" or "PSO bundles" in UE5 docs.
- **Chunking:** For large games, split .pak files into chunks so players don't need to download everything at once.
- **First cook is slow:** Be patient. Subsequent incremental cooks are fast.
- **Shipping builds strip console:** If you need the console, use Development configuration.

---

## Related

- ← Previous: [[01_Git_Repository_Setup]]
- → Next: [[03_Optimizing_Your_Unreal_Engine_Game]]
- 📚 Series: [[_MOC_Step_by_Step_Guides]]
- 📄 Full Transcript: [[02_Locomotion_Blendspace_Crouching_and_Procedural_Leaning]]
