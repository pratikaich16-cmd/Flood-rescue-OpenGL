# 🌊 Flood Rescue Mission

### A Story-Based 2D Computer Graphics Animation using OpenGL & GLUT

<p align="center">

**Flood Rescue Mission** is a story-driven 2D computer graphics project developed using **C/C++, OpenGL and GLUT**.
The project visually presents the journey of a peaceful village through a severe storm and flood, followed by rescue operations, recovery, rebuilding, community remembrance, and a flood-preparedness finale.

</p>

---

## 📖 Project Overview

The **Flood Rescue Mission** is designed as a sequence of **10 animated scenes** that together tell a complete story.

The story begins with a peaceful village surrounded by houses, trees, hills, a river, villagers and natural scenery. A severe storm then arrives with rain, lightning and strong environmental movement. The flood gradually rises and covers the road and surrounding areas.

Rescue operations are then carried out using a **helicopter and rescue boats**. After the water recedes, the damaged village begins its recovery. Villagers repair the damaged houses, plant a memorial tree, raise a flag, and finally prepare the village for possible future floods.

The project contains **10 scenes**, corresponding to the project requirement of **5 group members × 2 scenes each**. The scene system is controlled by the keyboard instead of automatically switching scenes through a timer.

---

# 🎯 Project Objectives

The main objectives of this project are:

* To create a complete story using 2D computer graphics.
* To demonstrate fundamental OpenGL drawing techniques.
* To demonstrate **Translation, Rotation and Scaling**.
* To implement real-time object animation.
* To create realistic environmental effects such as:

  * Rain
  * Lightning
  * Flood water
  * Moving waves
  * Wind
  * Floating debris
  * Helicopter movement
  * Boat movement
* To demonstrate character animation.
* To implement a multi-stage helicopter rescue.
* To implement boat-based rescue.
* To add scene-specific background audio.
* To provide keyboard-based scene navigation.
* To create a meaningful story rather than only demonstrating isolated graphical objects.
* To show how computer graphics can be used for storytelling and simulation.

---

# 🛠️ Technologies Used

| Technology                 | Purpose                                                 |
| -------------------------- | ------------------------------------------------------- |
| **C/C++**                  | Main programming language                               |
| **OpenGL**                 | 2D graphics rendering                                   |
| **GLUT**                   | Window management, keyboard input and rendering support |
| **GLU**                    | 2D orthographic projection                              |
| **Math Library**           | Trigonometric calculations and animation                |
| **Windows Multimedia API** | Scene-specific WAV audio                                |
| **GitHub**                 | Project version control and repository hosting          |

The program uses OpenGL/GLUT headers together with the Windows multimedia library for audio playback.

---

# 🏗️ Project Structure

A typical repository structure is:

```text
Flood-Rescue-Mission/
│
├── main.cpp
│
├── audio/
│   ├── village.wav
│   ├── storm.wav
│   ├── flood.wav
│   ├── helicopter.wav
│   ├── boat.wav
│   ├── calm.wav
│   ├── hope.wav
│   ├── repair.wav
│   ├── memorial.wav
│   └── finale.wav
│
└── README.md
```

### Main Source File

`main.cpp`

Contains:

* Global animation variables
* Drawing functions
* Object functions
* Scene functions
* Animation/update logic
* Keyboard controls
* Audio system
* OpenGL initialization
* Main program

---

# 🎬 Story / Scene Description

## 🌳 Scene 1 – Peaceful Village

The first scene introduces a peaceful village before the disaster.

### Main objects

* Blue sky
* Sun
* Clouds
* Hills
* Waterfall
* Grass
* River
* Road
* Two houses
* Forest
* Villagers
* Windmill
* Flying birds
* Flowers

The scene establishes the normal life of the village before the flood.

### Main functions

```cpp
scene1()
drawSky()
drawHills()
drawWaterfall()
drawGrass()
drawSun()
drawCloud()
drawRiver()
drawRoad()
drawHouse1()
drawHouse2()
drawForest()
drawPerson()
drawPersonAt()
drawWindmill()
drawBird()
drawPulsingFlower()
```

The scene also demonstrates the three required transformations through moving birds, a rotating windmill and pulsing flowers.

---

# ⛈️ Scene 2 – Storm Begins

The peaceful environment changes into a dangerous storm.

### Effects

* Dark sky
* Dark clouds
* Heavy rain
* Lightning
* Flooded river
* Running villagers
* Moving debris
* Swinging street lamp
* Flowers reacting to the storm

### Animation

Rain continuously falls, clouds move across the sky, villagers run, lightning flashes periodically and debris moves in different directions.

### Main functions

```cpp
scene2()
drawDarkSky()
drawDarkCloud()
drawRain()
drawLightning()
drawFloodRiver()
drawRunningPerson()
drawRunningPersonAt()
drawStreetLamp()
drawBird()
drawPulsingFlower()
```

---

# 🌊 Scene 3 – Flood Rises

The storm becomes a serious flood.

The flood water gradually rises and covers the road.

A helicopter searches the area while a rescue boat moves through the flooded village.

### Important feature

The road is rendered first and the rising flood is rendered over it. Therefore, as the flood level increases, the road visually disappears beneath the water.

### Helicopter animation

* Horizontal movement
* Hovering movement
* Rotating main rotor
* Rotating tail rotor
* Search-light movement

### Flood animation

```cpp
floodLevel += 0.0014;
```

The flood level is limited using:

```cpp
FLOOD_MAX
```

so that the water does not rise beyond the intended level.

---

# 🚁 Scene 4 – Helicopter Rescue

This scene presents the first major rescue operation.

A helicopter approaches a flooded house where a villager is safely waiting on the rooftop.

### Rescue stages

The helicopter rescue is divided into multiple stages:

1. Helicopter approaches the village.
2. Helicopter stops at the rescue position.
3. Rescue rope is lowered.
4. Villager attaches to the rope.
5. Rope is raised.
6. Villager is taken inside the helicopter.
7. Helicopter leaves the area.
8. A rescue boat begins moving toward the village.

The staged animation is controlled using:

```cpp
rescueStage
```

The rotor continuously rotates while the rescue sequence progresses.

### Main functions

```cpp
scene4()
drawHelicopter()
drawScene4Villager()
drawRescueBoat()
drawFloatingDebris()
```

---

# 🚤 Scene 5 – Boat Rescue

The second major rescue operation is performed using a rescue boat.

Two villagers are waiting safely on a raised area above the flood level.

The rescue boat approaches them and both villagers are picked up together.

### Rescue stages

``text
Boat approaches
      ↓
Boat reaches villagers
      ↓
Villagers attach to boat
      ↓
Villagers become seated
      ↓
Boat carries them away
      ↓
Rescue completed
```

The two villagers are represented using separate states:

```cpp
villager2Attached
villager2Rescued

villager3Attached
villager3Rescued
```

The boat rescue animation is controlled by:

```cpp
boatRescueStage
```

The boat moves toward the villagers and then continues toward the safe side of the scene.

---

# 🌤️ Scene 6 – Flood Recedes

After the rescue operations, the flood begins to decrease.

This scene represents the transition from disaster to recovery.

### Main animation

* Flood water goes down.
* Dark sky gradually becomes brighter.
* Damaged houses become visible.
* Floating debris remains.
* The environment starts becoming peaceful again.

The sky transition is controlled using:

```cpp
skyT
```

while the flood level gradually decreases.

### Function

```cpp
drawSkyBlend()
```

interpolates between the dark storm color and the normal bright sky.

---

# 🌈 Scene 7 – Hope After the Flood

Scene 7 represents hope after the disaster.

A beautiful double rainbow appears over the village while the houses still show storm damage.

### Main elements

* Bright sky
* Double rainbow
* Hills
* Waterfall
* River
* Damaged houses
* Trees
* Villagers
* Windmill
* Birds
* Flowers

The rainbow consists of a primary vivid arc and a larger pale secondary arc.

### Main functions

```cpp
scene7()
drawRainbow()
drawRainbowArc()
drawHouse1Damaged()
drawHouse2Damaged()
```

---

# 🔨 Scene 8 – Rebuilding the Village

The villagers begin rebuilding their damaged homes.

Three villagers participate in the reconstruction process.

### Activities

* One villager repairs House 1.
* Another villager carries a wooden plank.
* Another villager repairs House 2.
* Hammers move continuously.
* Houses are restored after the rebuilding process.

The hammer animation uses **rotation transformation** through:

```cpp
glRotatef()
```

and the animation angle is controlled by:

```cpp
hammerAngle
```

The houses change from damaged versions to normal versions when:

```cpp
housesRepaired = true;
```

---

# 🔔 Scene 9 – Community Memorial

After rebuilding the village, the community gathers for a memorial.

The purpose of this scene is to remember the flood and celebrate the strength and unity of the villagers.

### Main elements

* Memorial bell
* Growing sapling
* Rising flag
* Villagers
* Rebuilt houses
* Trees
* Windmill
* Birds
* Flowers

### Transformations

The memorial bell swings using **rotation**.

The sapling grows using **scaling**.

The flag moves upward using **translation**.

## The flag cloth also changes its width using scaling to create a waving effect.

# 🚨 Scene 10 – Flood-Ready Village / Finale

The final scene represents a stronger and better-prepared village.

Instead of ending immediately after the flood, the project shows what the community has learned from the disaster.

### Main elements

* Rebuilt houses
* Calm river
* Rainbow
* Trees
* Villagers
* Warning/siren tower
* Water-level warning sign
* Patrol boat
* Windmill
* Flying birds
* Flowers
* Final message banner

### Flood-preparedness features

The village now has:

* A warning siren
* Water-level monitoring
* Patrol/rescue boat
* Prepared community
* Rebuilt infrastructure

The final scene displays the message:

> **TOGETHER WE REBUILD, TOGETHER WE STAND**

The final scene combines the rebuilt village with flood-preparedness elements and the closing banner.

---

# 🎨 Graphics Functions

## `circle()`

The `circle()` function creates circular objects using `GL_POLYGON`.

It calculates points around a circle using:

```cpp
x + r*cos(angle)
y + r*sin(angle)
```

This reusable function is used for:

* Sun
* Heads
* Flowers
* Smoke
* Life rings
* Water splashes
* Leaves
* Other circular objects

The circle is generated using 360 angular positions.

---

## `drawSky()`

Creates the normal blue daytime sky using a rectangular `GL_QUADS`.

---

## `drawDarkSky()`

Creates the dark storm environment.

---

## `drawSkyBlend()`

Gradually transitions the sky from storm-dark to bright daytime during the flood recovery scene.

---

## `drawHills()`

Creates the background mountain/hill environment.

It uses:

```cpp
drawHillShape()
```

to generate curved hill shapes.

---

## `drawWaterfall()`

Creates a waterfall flowing from the distant hill.

It includes:

* Main water body
* White flowing streaks
* Splash pool
* Animated water movement

---

## `drawGrass()`

Creates the green ground area.

---

## `drawRoad()`

Creates the village road and its lane divider.

The road is intentionally drawn before the flood layer in flood scenes so the rising water can cover it.

---

## `drawRiver()`

Creates the normal river with:

* Deep water band
* Light surface band
* Moving wave lines
* Sparkle effects

---

## `drawRisingFlood()`

Creates dynamically increasing flood water.

It uses the variable:

```cpp
floodLevel
```

and generates animated surface ripples.

---

# 🏠 House Functions

## `drawHouse1()`

Draws the first normal village house.

Includes:

* House body
* Roof
* Chimney
* Smoke
* Door
* Door knob
* Window
* Flower box

The window can change its light state using:

```cpp
houseLight
```

---

## `drawHouse2()`

Draws the second normal village house with similar architectural components.

---

## `drawHouse1Damaged()`

Displays the storm-damaged version of House 1.

Features include:

* Damaged roof
* Broken door
* Cracked window
* Wall cracks
* Debris

---

## `drawHouse2Damaged()`

Displays the storm-damaged version of House 2.

It similarly includes:

* Partial roof
* Broken door
* Cracked window
* Wall damage
* Debris

---

# 🌳 Tree & Nature Functions

## `drawTree()`

Creates a detailed broad-leaf tree with:

* Trunk
* Bark highlight
* Multiple foliage layers
* Highlights
* Flowers/fruits

The leaves gently sway using rotation transformation.

---

## `drawPineTree()`

Creates a layered pine tree.

Its foliage also uses rotation to simulate wind movement.

---

## `drawForest()`

Combines multiple trees and a flower bush to create the village forest.

---

## `drawFlowerBush()`

Creates a small decorative bush containing flowers.

---

# 👨‍👩‍👧 Villager Functions

## `drawPerson()`

Draws the main animated villager.

The villager contains:

* Head
* Body
* Arms
* Legs

The `personX` variable controls horizontal movement.

---

## `drawPersonAt()`

Draws a villager at a specified x-coordinate.

This allows multiple villagers to be placed in the same scene.

---

## `drawRunningPerson()`

Creates a running pose for villagers during the storm.

---

## `drawRunningPersonAt()`

Creates additional running villagers at specific positions.

---

## `drawSeatedVillager()`

Represents a villager after being rescued onto the boat.

The character is drawn in a sitting position.

---

## `drawSafeWaitingVillager()`

Represents villagers waiting for rescue from safe elevated locations such as rooftops or raised platforms.

This avoids showing villagers unrealistically standing inside the flood water.

---

# 🚁 Helicopter Function

## `drawHelicopter()`

Creates the main rescue helicopter.

It includes:

* Main body
* Belly shading
* Cockpit
* Side window
* Nose light
* Tail boom
* Tail fin
* Landing skids
* Main rotor
* Tail rotor
* Rescue rope

### Transformations

The helicopter demonstrates:

**Translation**

```cpp
glTranslatef()
```

**Rotation**

```cpp
glRotatef()
```

The main rotor rotates continuously using `rotorAngle`.

The tail rotor rotates at a faster rate.

The rescue rope is drawn dynamically when:

```cpp
rescue == true
```

---

# 🚤 Rescue Boat Function

## `drawRescueBoat()`

Creates a detailed rescue boat.

It includes:

* Curved hull
* Hull trim
* Deck
* Cabin
* Cabin roof
* Porthole
* Life ring
* Mast
* Flag
* Rescue beacon
* Wake/ripples

The boat automatically follows the current flood surface using:

```cpp
float waterY = floodLevel;
```

The rescue beacon rotates using:

```cpp
glRotatef(beaconAngle, 0, 0, 1);
```

---

# 🌧️ Weather Effects

## `drawRain()`

Generates many animated rain streaks across the screen.

The rain position is controlled by:

```cpp
rainY
```

---

## `drawLightning()`

Creates a lightning bolt using `GL_LINES`.

Lightning is periodically enabled during the storm.

---

## `drawFloodRiver()`

Creates a more intense flooded river with animated wave lines.

---

# 🌈 Rainbow Functions

## `drawRainbowArc()`

Generates individual rainbow arcs using trigonometric calculations.

Seven colors are used:

1. Red
2. Orange
3. Yellow
4. Green
5. Blue
6. Indigo
7. Violet

---

## `drawRainbow()`

Creates a double rainbow by drawing:

* A pale secondary rainbow
* A vivid primary rainbow

---

# 🔨 Rebuilding Functions

## `drawRebuildVillagers()`

Creates the villagers participating in reconstruction.

It includes:

* Hammering villagers
* Villager carrying a plank
* Multiple repair activities

The hammer uses rotation animation to demonstrate a meaningful transformation.

---

# 🔔 Memorial Functions

## `drawMemorialBell()`

Creates the memorial bell and animates its swinging motion.

Uses:

```cpp
glTranslatef()
glRotatef()
```

---

## `drawMemorialSapling()`

Creates a memorial tree sapling.

Uses:

```cpp
glTranslatef()
glScalef()
```

The sapling gradually grows during the scene.

---

## `drawRisingFlag()`

Creates a flag pole and animated flag.

The flag:

* Moves upward
* Remains attached to the pole
* Changes width to simulate waving

---

# 🌬️ Transformation Demonstration Objects

The project intentionally includes animated objects that demonstrate the three fundamental 2D transformations required by the project.

## 🔄 Rotation

Examples:

* Windmill
* Tree leaves
* Pine trees
* Street lamp
* Helicopter rotor
* Boat beacon
* Rescue hammer
* Memorial bell
* Warning siren

---

## ➡️ Translation

Examples:

* Moving birds
* Moving villagers
* Helicopters
* Rescue boats
* Floating debris
* Rising flag
* Patrol boat
* Moving clouds

---

## 🔍 Scaling

Examples:

* Sun glow
* Pulsing flowers
* Floating debris
* Growing memorial sapling
* Waving flag
* Warning sign

The project maintains shared animation variables for these transformation demonstrations, including `windmillAngle`, `birdX`, `flowerPulse`, `lampSwing`, `buoyBob` and `beaconAngle`.

---

# 🌪️ Shared Animation Objects

## `drawWindmill()`

Creates a windmill with rotating sails.

Demonstrates:

* Rotation
* Translation of the rotation pivot

---

## `drawBird()`

Creates a moving bird.

Demonstrates translation.

---

## `drawPulsingFlower()`

Creates a flower that continuously changes size.

Demonstrates scaling.

---

## `drawStreetLamp()`

Creates a street lamp whose head swings during the storm.

Demonstrates translation and rotation.

---

## `drawFloatingDebris()`

Creates floating objects on the flood surface.

The debris:

* Drifts horizontally
* Bobs vertically
* Changes size slightly

Therefore it demonstrates both translation and scaling.

---

# 🔊 Audio System

The project contains **scene-specific background audio**.

The audio system uses the Windows Multimedia API:

```cpp
#include <windows.h>
#include <mmsystem.h>
```

The function:

```cpp
playSceneAudio(int s)
```

selects the appropriate audio based on the current scene.

| Scene    | Audio            |
| -------- | ---------------- |
| Scene 1  | `village.wav`    |
| Scene 2  | `storm.wav`      |
| Scene 3  | `flood.wav`      |
| Scene 4  | `helicopter.wav` |
| Scene 5  | `boat.wav`       |
| Scene 6  | `calm.wav`       |
| Scene 7  | `hope.wav`       |
| Scene 8  | `repair.wav`     |
| Scene 9  | `memorial.wav`   |
| Scene 10 | `finale.wav`     |

Each audio file is played asynchronously and looped while its corresponding scene is active.

### `stopAudio()`

Stops the currently playing scene audio.

### `playSceneAudio()`

Stops the previous audio and starts the audio associated with the new scene.

### `changeScene()`

Changes the scene and automatically updates the audio.

---

# ⌨️ Keyboard Controls

The project uses keyboard input for scene navigation.

| Key       | Function                                |
| --------- | --------------------------------------- |
| **N / n** | Go to next scene                        |
| **P / p** | Go to previous scene                    |
| **R / r** | Restart the complete story from Scene 1 |
| **ESC**   | Exit the application                    |

The story no longer automatically jumps to the next scene. Instead, the user controls scene progression using the keyboard.

---

# 🔁 Reset System

## `resetAll()`

The `resetAll()` function resets the complete animation state.

It resets:

* Sun position
* Cloud position
* Villager position
* Rain
* Lightning
* Helicopter
* Flood level
* Rescue states
* Boat positions
* Sky transition
* Hammer animation
* House repair state
* Memorial animation
* Flag animation
* Siren animation
* Patrol boat
* Shared transformation objects

This allows the complete story to start again from a clean state.

---

# ⚙️ Animation / Update System

## `update(int value)`

The `update()` function is the main real-time animation loop.

It updates:

* Sun
* Clouds
* Villagers
* Water waves
* Background boat
* Tree sway
* Windmill rotation
* Birds
* Flowers
* Street lamp
* Floating debris
* Rescue beacon
* Rain
* Lightning
* Flood level
* Helicopter
* Rescue stages
* Boat rescue
* Flood recession
* Hammer
* Memorial bell
* Sapling
* Flag
* Warning siren
* Patrol boat

The function requests another redraw and schedules itself again after approximately 16 milliseconds:

```cpp
glutPostRedisplay();
glutTimerFunc(16, update, 0);
```

This provides continuous animation while keeping scene progression under keyboard control.

---

# 🖥️ Display System

## `display()`

The `display()` function determines which scene should be rendered.

It checks:

```cpp
scene
```

and calls:

```cpp
scene1()
scene2()
scene3()
scene4()
scene5()
scene6()
scene7()
scene8()
scene9()
scene10()
```

After drawing the selected scene, OpenGL flushes the rendering pipeline.

---

# 📐 OpenGL Coordinate System

The project uses a 2D orthographic coordinate system:

```cpp
gluOrtho2D(-1, 1, -1, 1);
```

Therefore:

```text
          +Y
           ↑
           |
 -X ←------+------→ +X
           |
           ↓
          -Y
```

This makes it easy to position and animate 2D objects using world coordinates.

---

# 🎞️ Scene Rendering Pipeline

Each scene is built by calling reusable drawing functions.

For example:

```text
Scene
 ↓
Sky
 ↓
Background scenery
 ↓
Ground / River / Road
 ↓
Buildings
 ↓
Trees
 ↓
Characters
 ↓
Animated objects
 ↓
Special scene effects
```

This modular structure makes the program easier to understand, maintain and modify.

---

# 🧩 Transformation Technique

The project uses OpenGL matrix transformations:

### Translation

```cpp
glTranslatef(x, y, 0);
```

Used to move an object or establish an animation pivot.

### Rotation

```cpp
glRotatef(angle, 0, 0, 1);
```

Used for rotating objects around the Z-axis.

### Scaling

```cpp
glScalef(scaleX, scaleY, 1.0f);
```

Used for growing, shrinking or pulsing objects.

### Matrix Management

```cpp
glPushMatrix();
...
glPopMatrix();
```

is used to isolate transformations so that one object's transformation does not affect other objects.

---

# 🧠 Animation State Management

Many animations use state variables to control their behavior.

Examples:

cpp
rescueStage
boatRescueStage
hammerUp
saplingGrowing
warnGrow
bellSwingRight
lampSwingRight
lightDirection
`

These variables allow the program to create multi-step and reversible animations.

For example, the memorial bell changes its direction when its rotation reaches its limits, while the sapling stops growing after reaching its maximum scale.

---

# 📊 Major OpenGL Concepts Demonstrated

This project demonstrates the following Computer Graphics concepts:

* 2D geometric primitives
* `GL_POINTS`
* `GL_LINES`
* `GL_TRIANGLES`
* `GL_QUADS`
* `GL_POLYGON`
* Coordinate systems
* Orthographic projection
* Matrix transformations
* Translation
* Rotation
* Scaling
* Animation
* Object composition
* Layered rendering
* Trigonometric animation
* Real-time rendering
* Keyboard interaction
* Scene management
* Audio integration
* State-based animation

---

# ✨ Highlights of the Project

### 🌊 Realistic Flood Effect

The flood level dynamically changes and eventually covers the road.

### 🚁 Multi-Stage Helicopter Rescue

The helicopter approaches, lowers the rope, rescues the villager and leaves.

### 🚤 Boat Rescue

Two villagers are rescued together using a moving rescue boat.

### 🌧️ Weather Animation

Rain, lightning, moving clouds and storm effects make the disaster visually meaningful.

### 🌈 Recovery Story

The flood recedes and the environment gradually becomes brighter.

### 🔨 Reconstruction

Villagers actively repair the damaged houses.

### 🌱 Memorial

A sapling grows while the community remembers the disaster.

### 🚨 Flood Preparedness

The final scene shows warning systems and a patrol boat to represent future disaster preparedness.

### 🔊 Scene-Based Audio

Every scene has its own environmental or thematic sound.

### ⌨️ Interactive Scene Control

The user can control the story using keyboard commands.



# 🧑‍💻 How to Run the Project

## Requirements

Install/configure:

* Windows
* C/C++ compiler
* OpenGL
* GLUT / FreeGLUT
* Required OpenGL libraries
* Audio files in the correct directory

---

## Step 1 – Clone the Repository

Clone this repository from GitHub:

```bash
git clone YOUR_GITHUB_REPOSITORY_URL
```

Then open the project in your preferred C/C++ development environment.

---

## Step 2 – Keep the Audio Folder

The `audio` folder should remain in the expected location relative to the executable/source project.

The program expects files such as:

```text
audio/village.wav
audio/storm.wav
audio/flood.wav
audio/helicopter.wav
audio/boat.wav
audio/calm.wav
audio/hope.wav
audio/repair.wav
audio/memorial.wav
audio/finale.wav
```

If the audio files cannot be found, the graphics can still be understood, but the scene-specific sound will not play.

---

## Step 3 – Build and Run

Compile the C/C++ source with the required OpenGL and GLUT libraries.

Run the application.

The project starts at **Scene 1** and its corresponding village audio.

---

# 🎮 How to Use the Application

After starting the application:

### Press `N`

Moves to the next scene.

### Press `P`

Returns to the previous scene.

### Press `R`

Restarts the complete story from Scene 1.

### Press `ESC`

Stops the audio and exits the application.

---

# 🗺️ Complete Story Flow
Scene 1
Peaceful Village
      ↓
Scene 2
Storm Begins
      ↓
Scene 3
Flood Rises
      ↓
Scene 4
Helicopter Rescue
      ↓
Scene 5
Boat Rescue
      ↓
Scene 6
Flood Recedes
      ↓
Scene 7
Hope / Rainbow
      ↓
Scene 8
Village Rebuilding
      ↓
Scene 9
Community Memorial
      ↓
Scene 10
Flood-Ready Village
      ↓
"TOGETHER WE REBUILD,
 TOGETHER WE STAND"


🎓 Academic Purpose

This project was developed as a **Computer Graphics project** to demonstrate how theoretical concepts can be converted into an interactive visual application.

Instead of demonstrating transformations through isolated shapes, the project integrates them into a meaningful story.

For example:

| Graphics Concept  | Project Example                          |
| ----------------- | ---------------------------------------- |
| Translation       | Birds, boats, helicopter, flag           |
| Rotation          | Helicopter rotor, windmill, hammer, bell |
| Scaling           | Sun glow, flowers, sapling, warning sign |
| Animation         | Rain, flood, rescue, rebuilding          |
| Primitive drawing | Houses, trees, villagers, boats          |
| Projection        | 2D orthographic village environment      |
| Interaction       | Keyboard-controlled scene navigation     |
| Audio             | Scene-specific environmental sounds      |

---

# 🌟 Conclusion

**Flood Rescue Mission** demonstrates how 2D computer graphics can be used to create an engaging story-based animation.

The project combines:

**Graphics + Animation + Transformation + Interaction + Audio + Storytelling**

to represent the complete journey of a village from peace, through disaster and rescue, toward recovery, unity and future preparedness.

The final message of the project summarizes its central idea:

> ## **TOGETHER WE REBUILD, TOGETHER WE STAND**

---

# 👥 Project Team

**Course:** Computer Graphics
**Project:** Flood Rescue Mission
**Number of Scenes:** 10
**Platform:** Windows
**Graphics Library:** OpenGL / GLUT

### Team Members

1. **Member 1** – Scene 1 & Scene 2
2. **Member 2** – Scene 3 & Scene 4
3. **Member 3** – Scene 5 & Scene 6
4. **Member 4** – Scene 7 & Scene 8
5. **Member 5** – Scene 9 & Scene 10

---

# 📜 License

This project was created for **academic and educational purposes** as part of a Computer Graphics course project.

---

## ❤️ Project Theme

> **Disaster can destroy buildings, but unity, courage and cooperation can rebuild a community.**

---
