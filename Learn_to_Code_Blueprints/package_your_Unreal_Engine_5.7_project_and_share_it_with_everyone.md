---
title: "How to package your Unreal Engine 5.7 project and share it with everyone!"
source: "https://www.youtube.com/watch?v=AWzhZnSq9u0"
video_id: "AWzhZnSq9u0"
type: "youtube-summary"
series: "Learn to Code Blueprints"
episode: 0
tags: [ue5, tutorial, blueprint, gamedev, packaging, coding]
---

# How to package your Unreal Engine 5.7 project and share it with everyone!

## Initial Project Settings
Before packaging, define game rules and set the starting map/mode:
1. **Edit Project Settings** → **Maps and Modes**.
2. Set your **Startup Map** and **Game Default Map**.
3. Set the **Default Game Mode**.

## Using the Project Launcher
Access via **Platforms** → **Project Launcher**. This allows for creating reusable launch profiles.

### Creating a Launch Profile
Configure a profile (e.g., "Development Build") with these key settings:
- **Project**: Select your project.
- **Platform**: Windows (requires installed SDKs for other platforms).
- **Build Configuration**:
  - `Development`: For testing. Includes debugging features.
  - `Shipping`: For release. Strips debugging info and console commands.
- **Packaging**:
  - **Package Files**: Use **Packaged files** (`.pak` files) to bundle assets. This makes it harder to steal assets and can reduce project size.
  - **Compress Content**: Enables, which reduces file size but may slightly slow loading.
- **Cooking**:
  - **Content Scheme**: Use **By the Book** for final release to include only selected maps.
  - **Maps to Cook**: For reusing the profile across projects, select **Use startup maps**. For a final release build, **Select maps** to include only necessary ones.
- **Build & Archive**:
  - **Build Game**: Yes.
  - **Archive Build**: Yes, and specify an output directory. **Best practice**: Place the build folder close to the drive root (e.g., `C:\Builds`) to avoid long path issues.
  - **Deploy** and **Launch**: Set to No for just building.

## The Packaging Process Steps
The launch profile will execute these steps:
1. **Building**: Compiles code and verifies all assets/references are valid. Errors here are often due to missing textures or null references.
2. **Cooking**: Converts and strips editor-specific data from assets (e.g., converting `.uasset` files into platform-optimized formats). This is the most time-consuming step, especially on the first cook.
   - **First Cook**: Can take 10-30+ minutes. Subsequent cooks are faster.
3. **Packaging**: Packages the cooked assets into the final folder structure.

## Sharing the Packaged Project
1. The output is a folder containing the game executable and necessary folders (`Engine`, `Content` with `.pak` files, `Binaries`).
2. To share, **zip the entire build folder** and send the archive.
3. **Critical for non-developer users**: Ensure **prerequisite installers** are included.
   - In the Project Launcher, go to **Platforms** → **Packaging Settings**.
   - Enable **Include prerequisites installer**. This adds dependencies (e.g., Visual C++ Redistributables) so the game runs on end-user machines.
   - *Note: For Steam releases, this can be managed by Steam itself.*

## Key Notes & Tips
- **Launch Profiles**: Use the Project Launcher to save different configurations (e.g., Development, Shipping) for efficiency.
- **Pack Files**: Using packaged `.pak` files protects assets from being easily extracted.
- **Path Length**: Keep the output build directory path short to avoid OS character limits and build failures.
- **PSO Precaching/Bundles**: For preloading assets to reduce in-game hitching (mentioned as a potential advanced topic).
- **Debugging a Development Build**: Press the apostrophe key (`'`) and enter `stat unit` to see frame rate.

---

## Related

- ← Previous: [[Using_a_Paragon_asset_for_our_main_character]]
- → Next: [[start_optimizing_your_Unreal_Engine_Game]]
- 📚 Series: [[_MOC_Learn_to_Code_Blueprints]]
