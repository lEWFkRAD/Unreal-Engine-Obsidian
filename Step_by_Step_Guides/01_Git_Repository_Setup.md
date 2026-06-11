---
title: "How to Set Up an Unreal Engine 5 Git Repository — SourceTree Source Control"
source: "https://www.youtube.com/watch?v=zIllLXkkHB0"
video_id: "zIllLXkkHB0"
type: "step-by-step-guide"
series: "Step-by-Step Guides"
episode: 1
tags: [ue5, git, sourcetree, version-control, setup, guide]
---

# How to Set Up an Unreal Engine 5 Git Repository — SourceTree Source Control

**Source:** https://www.youtube.com/watch?v=zIllLXkkHB0
**Duration:** 14:47
**Extracted from:** `How_to_Set_Up_an_Unreal_Engine_5_Git_Repository_-_SourceTree_Source_Control.md`

---

## Prerequisites

- GitHub account (free)
- SourceTree (free, by Atlassian)
- Git and Mercurial (installed with SourceTree)
- An existing UE5 project

---

## Step-by-Step

### Step 1: Create a GitHub Account
1. Go to [github.com](https://github.com) and sign up (or log in if you already have an account).

### Step 2: Download and Install SourceTree
1. Go to [sourcetreeapp.com](https://www.sourcetreeapp.com) and download it.
2. Run the installer. When the wizard appears:
   - **Agree** to the terms.
   - When asked to create a Bitbucket or Atlassian account → select **Atlassian account** (this is the company behind SourceTree and Trello).
   - When asked to install **Git and Mercurial** → select **both** and install.
   - When asked to create a global git config file → select **No** (we'll create a custom one for UE5).
   - When asked to create an SSH key → select **No** (too complex for basic use; HTTPS is fine).

### Step 3: Add Your GitHub Account to SourceTree
1. Open SourceTree. Go to **Remote** tab.
2. Click **Add a new account**.
3. For hosting service, select **GitHub** (not Bitbucket).
4. Leave authentication on **Basic** (not SSH).
5. Enter your GitHub **username** and **password**.
6. Click **OK** — you should now be logged in.

### Step 4: Create a New Empty Folder for Your Repository
1. Create a new empty folder on your computer (e.g., `RPG_Tutorial_Series_Git`).
2. **Important:** This must be an empty folder — you cannot point SourceTree at an existing project folder.
3. If you already have a project, you'll copy files into this folder in the next step.

### Step 5: Create the Repository in SourceTree
1. In SourceTree, go to the **Create** tab.
2. Set the **Destination Path** to your new empty folder.
3. Enter a **Name** for your repository (e.g., `GorkaGames_RPG_Tutorial_Series`).
4. Check **"Create repository in account"** — this auto-creates the repo on GitHub.
5. Select your GitHub account.
6. Optionally add a description.
7. Set visibility: **Private** (recommended starting point — you can go public later).
8. Click **Create** and wait for it to initialize.

### Step 6: Set Up Your .gitignore File
1. After creation, open the repository folder in File Explorer.
2. You should see a `.git` folder (may be hidden — enable "Show hidden files").
3. Download a UE5-appropriate `.gitignore` file (link typically in video description).
4. Place the `.gitignore` file in the root of your repository folder.
5. This file acts as a filter — it tells Git which files to track (Blueprints, Levels, Assets) and which to ignore (temporary files, binaries).

### Step 7: Copy Your Project Files
1. Open your existing UE5 project folder in another File Explorer window.
2. **Copy** (Ctrl+C) all project files — do NOT cut, in case something goes wrong.
3. **Paste** (Ctrl+V) into the repository folder.
4. Wait for the copy to complete (may take a while for large projects).

### Step 8: Stage, Commit, and Push
1. Back in SourceTree, go to **File Status** → click **Commit**.
2. You should see all your files listed (filtered by .gitignore).
3. Click **Stage All** to mark all files for the commit.
4. If warned about large files (>10MB textures, etc.) → click **OK** for now. (For long-term, look into Git LFS — Large File Storage.)
5. Enter a commit message (e.g., `"Initial commit — Locomotion, vaulting, assassinations, crouching, leaning"`).
6. Click **Commit**.
7. Click **Push** → select **master** branch → **OK**.
8. Wait for the upload to complete.

### Step 9: Verify on GitHub
1. Go to github.com → your repositories.
2. You should see your repository with all files and the commit message.

---

## Daily Workflow (After Setup)

1. Make changes in UE5 editor.
2. Open SourceTree → **File Status** → **Commit**.
3. **Stage All** → write a descriptive commit message → **Commit**.
4. **Push** to upload changes to GitHub.
5. **Pull** to download changes if working with a team.

---

## Pro Tips

- **Branches:** For big features (e.g., multiplayer), create a separate branch. If it works, merge it into master. If it breaks, just switch back to master.
- **Commit messages:** Be descriptive. "Added vaulting with motion warping" is better than "updated stuff."
- **Private → Public:** Start private. When your project is ready, add a license and make it public.
- **Git LFS:** For projects with many large assets, set up Git Large File Storage to avoid repo bloat.

---

## Related

- → Next: [[02_Packaging_Project]]
