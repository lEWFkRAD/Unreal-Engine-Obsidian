---
title: "Learn to Code in UE5 - 2 - Your First Class"
source: "https://www.youtube.com/watch?v=Xc2Xr7Csebc"
video_id: "Xc2Xr7Csebc"
type: "youtube-summary"
series: "UE5 Beginner Tutorials"
episode: 2
tags: [ue5, tutorial, blueprint, gamedev, coding, beginner]
---

# Learn to Code in UE5 - 2 - Your First Class

**Source:** YouTube - Coqui Games
**Duration:** 14:00 | **Published:** 2022-07-29

## Core Concepts
- **Blueprint Editor:** The custom visual scripting/code editor in Unreal Engine.
- **Class Definition:** A blueprint file in the Content Browser, defining properties and components.
- **Class Instance:** A copy of that class placed in a level, which can be individually customized.

## Creating a New Project (Steps)
1. Launch **Unreal Engine 5** from the Epic Games Launcher.
2. Select **Games > Third Person** template.
3. Ensure settings: **Blueprint**, Desktop platform, **Maximum** quality, **Starter Content** enabled.
4. Name and create the project.

## Blueprint Editor Overview
**Main Editor Tabs:**
- **Event Graph:** Where most gameplay code is created. (Future lesson topic)
- **Construction Script:** Another area for code, executed when a class is built. (Future lesson topic)
- **Viewport:** Visual preview of the class.

**Toolbar (Top):**
- **Compile:** Converts source code to machine code. Green checkmark = successful compile (no errors).
- **Save:** Saves the asset to disk.
- **Browse:** Locates the asset in the Content Browser.
- **Find:** Searches within the blueprint.

**Core Panels:**
- **Components Window (Left):** Shows the hierarchy of components that make up the class.
- **Details Panel (Right):** Displays customizable properties for the selected component or class.
- **My Blueprint (Bottom):** Add **Variables** (data attributes) and **Functions/Event Dispatchers** (functionality). (Future lesson topic)

## Class Components
A class is composed of one or more **components**, which provide specific data or functionality.
- **Common Components:** Visual mesh, collision volumes, camera, movement component.
- **Custom Actor Components:** You can create your own to add reusable functionality to multiple classes.
- **Benefit:** Promotes **modular class design** and organized code.

## Creating Your First Custom Class
1. In the Content Browser, create a new folder structure: `Content/_Course/Blueprints`.
2. Right-click > **Blueprint Class**.
3. Select a **Parent Class** (e.g., `Actor`).
4. Name it (e.g., `BP_GenericActor`) and open it.
5. In the Components window, **add a component** (e.g., **Point Light**).
6. **Compile** and **Save**.

## Class Definition vs. Class Instance
> "A class definition is a class you define by creating a child class... The class definition lives inside the content browser... An instance of a class is an occurrence or copy of that class in the level."

- **Definition:** The blueprint file (`BP_GenericActor`). Modify it to change **all** instances.
- **Instance:** A copy placed in the level. Drag the definition from the Content Browser to create multiple instances.
- **Propagation:** Changes to the **class definition** (e.g., changing the light color to red) automatically update **all instances** across all levels.
- **Future Concept:** Instances can be individually customized (e.g., different light colors per instance).

## Lesson Recap & Practice
**Key takeaways:**
1. Blueprint Editor interface and its major sections.
2. Class composition using **actor components** for modularity.
3. Process of creating a custom blueprint class.
4. Critical distinction between **class definitions** and **instances**.

**Practice Task:**
> "Go back to the third person character blueprint class and explore the available options for each of its components."

---

## Related

- ← Previous: [[01_Programming_Basics]]
- → Next: [[03_Data_Attributes]]
- 📚 Series: [[_MOC_UE5_Beginner_Tutorials]]
