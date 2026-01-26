# Dragonfly Game Engine

Modernized version of the Dragonfly C++ Text-Based Game Engine.

Ports Dragonfly library and example games to use C++20, CMake, Clang, GoogleTest, Perf, etc.

> Mark Claypool. Dragonfly - Program a Game Engine from Scratch, Interactive Media and Game Development, Worcester Polytechnic Institute, 2014. Online at: http://dragonfly.wpi.edu/book/

---

- [Structure](#structure)
- [Gameplay Examples](#gameplay-examples)
- [Development Workflows](#development-workflows)
  - [Dragonfly Game Engine Library](#dragonfly-game-engine-library)
    - [0) Build Root Targets](#0-build-root-targets)
    - [1) Build Library and test_game Executable](#1-build-library-and-test_game-executable)
    - [2) Run Tests](#2-run-tests)
    - [3) Format & Lint](#3-format--lint)
    - [4) Profile Performance](#4-profile-performance)
  - [Saucer Shoot Game](#saucer-shoot-game)
  - [Bongo Bear Game](#bongo-bear-game)
- [TODOs](#todos)
- [Dragonfly Engine Class Structure](#dragonfly-engine-class-structure)
- [Resources Collection](#resource-collection)

---

## Structure

- `/dragonfly` <- dragonfly library
- `/saucer_shoot` <- intro 2d shooter game utilizing the dragonfly library
- `/bongo_bear` <- bongo cat game but it's a bear using the dragonfly library and ascii shader

---

## Gameplay Examples

[Saucer Shoot](https://github.com/fishrcat/dragonfly-cpp-engine-course/pull/1)

---

## Development Workflows

### --- Dragonfly Game Engine Library ---

See root CMakeList for all convenience targets.  Build and test workflows are also run on commit, see `.github/workflows`.

### 0) Build root targets

```bash
cd dragonfly
mkdir -p build  # Run once
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=RelWithDebInfo
```

### 1) Build library and test_game executable

```bash
cmake --build build --target build-dragonfly
```

Run the test game executable with

```bash
./build/dragonfly/dragonfly_test_game
```

### 2) Run tests

```bash
cmake --build build --target test-dragonfly
```

### 3) Format & Lint

```bash
pipx install pre-commit  # Run once
pre-commit run --all-files
```

### 4) Profile performance

```bash
cmake --build build --target profile-dragonfly
```

See `build/flamegraph.svg` for an interactive profile like the following example

![flamegraph-example.png](img/flamegraph-example.png)

### --- Saucer Shoot Game ---

### --- Bongo Bear Game ---

---

## TODOs

- [x] [**Saucer Shoot Tutorial**](https://dragonfly.wpi.edu/book/pdfs/3-tutorial.pdf) - Build the example game using the existing dragonfly library
- [x] **Development Environment v1** - Initialize dragonfly library development workflows
  - [x] Migrate to CMake
  - [x] Integrate Clang and GoogleTest
  - [x] Initialize GitHub actions to lint/build/test PR commits
- [ ] **Dragonfly** - Recreate dragonfly library following the [Program a Game Engine from Scratch Book](https://dragonfly.wpi.edu/book/index.html) development checkpoints
  - [x] DC1: Manager & LogManager
  - [x] DC2: Clock & GameManager
  - [x] DC3: Vector & Object
  - [x] DC4: Dragonfly Egg
  - [x] DC5: Display Manager
  - [ ] DC6: Input Manager
  - [ ] DC7: Dragonfly Naiad
  - [ ] DC8: Sprite & Resource Manager
  - [ ] DC9: Sprite Animation
  - [ ] DC10: Collisions & Views
  - [ ] DC11: Sound & Music
  - [ ] DC12: Event Filtering
  - [ ] DC13: View Objects
  - [ ] DC14: Scene Graph
  - [ ] DC15: Dragonfly
  - [ ] Rebuild Saucer Shoot game to test final version
- [ ] **Development Environment V2** - Update the development workflows for build matrix of library and example games
  - [ ] Enable multi-build of all example games and dragonfly library
  - [ ] Enable releases to GitHub page from action build files
- [ ] **Feature Extension** - Write an ASCII shader for the engine
- [ ] **Bongo Bear** - Create advanced game example using all library features

---

## Dragonfly Engine Class Structure

### Utility

| Class     | Description                           |
|-----------|---------------------------------------|
| Box       | 2D rectangle                          |
| Vector    | 2D vector                             |
| Clock     | Timing support                        |
| Music     | Store and play music                  |
| Sound     | Store and play sound effects          |
| Frame     | 2D character image                    |
| Sprite    | Sequence of frames for animated image |
| Animation | Control for animating Sprite          |

### Event

| Class           | Description                                    |
|-----------------|------------------------------------------------|
| Event           | Base class for engine events                   |
| EventCollision  | Event generated when solid objects collide     |
| EventKeyboard   | Event generated when keyboard has input        |
| EventMouse      | Event generated when mouse has input           |
| EventOut        | Event generated when object goes outside world |
| EventStep       | Event generated each game loop                 |
| EventView       | Event generated when updating ViewObjects      |

### Manager

| Class            | Description                                   |
|------------------|-----------------------------------------------|
| Manager          | Base class for engine managers                |
| DisplayManager   | Manager of the graphics display               |
| GameManager      | Manager of the game loop                      |
| InputManager     | Manager of player input (keyboard and mouse) |
| LogManager       | Manager of the logfile                        |
| ResourceManager  | Manager of resources (sprites, sounds, music)|
| WorldManager     | Manager of the game world                     |

### Object

| Class       | Description                                    |
|-------------|------------------------------------------------|
| Object      | Base class for game engine objects             |
| ViewObject  | View objects displayed on the Heads Up Display |
| ObjectList  | List container for Objects                     |

---

## Resource Collection

### Dragonfly Engine

* Mark Claypool. Dragonfly - Program a Game Engine from Scratch, Interactive Media and Game Development, Worcester Polytechnic Institute, 2014. Online at: http://dragonfly.wpi.edu/book/
* Engine reference repo with direct book transcription - https://github.com/Tate-Donnelly/ASCII-Game-Engine

### ASCII Shader Examples and Implementations

* [Image -> ASCII with Edge Detection](https://github.com/gouwsxander/ascii-view)
  * [Associated YouTube Video](https://www.youtube.com/watch?v=t8aSqlC_Duo)
* [ASCII Clouds](https://caidan.dev/portfolio/ascii_clouds/?cs=8&wa=0.7&ws=0.5&ni=0.05&vi=0.8&vr=0.75&ba=0.2&ca=1&ts=0.5&h=200&sa=0.3&t1=0.15&t2=0.28&t3=0.4&t4=0.52&t5=0.65&sd=fibylo)
* [WebGL ASCII Shader](https://tympanus.net/codrops/2026/01/04/efecto-building-real-time-ascii-and-dithering-effects-with-webgl-shaders/)
* [Unity ASCII Shader](https://github.com/StefanJo3107/ASCII-Rendering-Shader-in-Unity)

### ASCII and Mini Game Ideas

* TinyCity - a city simulation game inspired by SimCity for the Raspberry Pi RP2040 running MicroPython - https://github.com/chrisdiana/TinyCity
* [TUI Physics Simulator](https://github.com/minimaxir/ballin)
