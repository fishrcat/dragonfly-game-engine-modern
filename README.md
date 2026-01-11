# Dragonfly Game Engine

Modernized version of the Dragonfly C++ Text-Based Game Engine.

Ports Dragonfly library and example games to use C++20, CMake, Clang, GoogleTest, Perf, etc.

> Mark Claypool. Dragonfly - Program a Game Engine from Scratch, Interactive Media and Game Development, Worcester Polytechnic Institute, 2014. Online at: http://dragonfly.wpi.edu/book/

---

- [Structure](#structure)
- [Gameplay Examples](#gameplay-examples)
- [TODOs](#todos)
- [Development Workflows](#development-workflows)
  - [Dragonfly Game Engine Library](#dragonfly-game-engine-library)
    - [0) Build Root Targets](#0-build-root-targets)
    - [1) Build Library and test_game Executable](#1-build-library-and-test_game-executable)
    - [2) Run Tests](#2-run-tests)
    - [3) Format & Lint](#3-format--lint)
    - [4) Profile Performance](#4-profile-performance)
  - [Saucer Shoot Game](#saucer-shoot-game)
  - [Bongo Bear Game](#bongo-bear-game)
- [Dragonfly Engine Class Structure](#dragonfly-engine-class-structure)

---

## Structure

- `/dragonfly` <- dragonfly library
- `/saucer_shoot` <- intro 2d shooter game utilizing the dragonfly library
- `/bongo_bear` <- bongo cat but it's a bear using the dragonfly library and ascii shader

---

## Gameplay Examples

[Saucer Shoot](https://github.com/fishrcat/dragonfly-cpp-engine-course/pull/1)

## TODOs

- [x] [**Saucer Shoot Tutorial**](https://dragonfly.wpi.edu/book/pdfs/3-tutorial.pdf) - Build the example game using the existing dragonfly library
- [x] **Development Environment v1** - Initialize dragonfly library development workflows
    - [x] Migrate to CMake
    - [x] Integrate Clang and GoogleTest
    - [x] Initialize GitHub actions to lint/build/test PR commits
- [ ] **Dragonfly** - Recreate dragonfly library following the [Program a Game Engine from Scratch Book](https://dragonfly.wpi.edu/book/index.html) development checkpoints
    - [x] DC1: Manager & LogManager
    - [x] DC2: Clock & GameManager
    - [ ] DC3: Vector & Object
    - [ ] DC4: Dragonfly Egg
    - [ ] DC5: Display Manager
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
