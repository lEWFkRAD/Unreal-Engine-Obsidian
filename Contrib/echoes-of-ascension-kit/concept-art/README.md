# Concept Art — visual identity starters

Four 1024×1024 mood/identity pieces for *Echoes of Ascension*, generated to give the project a face early. These are **style/mood references, not final assets** — UE5 needs 3D meshes; this is direction, marketing, and morale.

> **The PNGs aren't committed here** (keeping the vault light — binaries don't belong in a knowledge base). They're shared with you directly; this README documents what was generated and how to reproduce them.

Generated on a local ComfyUI pipeline (animagine-xl-4.0, SDXL) — the same kind of setup you're running on TurboHaul, so you can iterate these yourself by re-prompting.

| File | What it explores |
|------|------------------|
| `01_tower_biome.png` | Interior of the Tower of Ascension — arcane gothic hall, glowing runic circles, blue aether energy. A biome mood ref. |
| `02_faction_flame.png` | A flame-aligned kingdom — obsidian spires, embers, molten light. One of the 8 Aetheric factions. |
| `03_echo_fragment.png` | An Echo (Arcanthi power fragment) — violet arcane energy burst. Item/pickup mood. |
| `04_ui_mockup.png` | HUD direction — ornate arcane frame, gold filigree + deep blue, runic bars. |

## Reproduce / iterate
Prompts and the ComfyUI workflow are in the kit's generator (`tools`-style script). To re-roll: change the seed or prompt and resubmit to your ComfyUI `/prompt` endpoint. animagine-xl responds well to `masterpiece, best quality, dark fantasy concept art, dramatic cinematic lighting` plus the subject.

> Style note: animagine is illustration-leaning. For a grittier Witcher/Skyrim render target, a photoreal SDXL checkpoint (or a LoRA) would push closer — but for early identity and morale these set the tone.
