# Dragonfly Game Engine

Modernized version of the Dragonfly C++ Text-Based Game Engine.

Ports Dragonfly library and example games to use C++20, CMake, Clang, and GoogleTest.

> Mark Claypool. Dragonfly - Program a Game Engine from Scratch, Interactive Media and Game Development, Worcester Polytechnic Institute, 2014. Online at: http://dragonfly.wpi.edu/book/

---

- [Structure](#structure)
- [Gameplay Examples](#gameplay-examples)
- [TODOs](#todos)
- [Development Workflows](#development-workflows)
    - [Dragonfly Game Engine Library](#dragonfly-game-engine-library)
        - [Build](#1-build)
        - [Run Tests](#2-run-tests)
        - [Format & Lint](#3-format--lint)
    - [Saucer Shoot Game](#saucer-shoot-game)

## Structure

```
/dragonfly <- dragonfly library
/saucer_shoot <- intro 2d shooter game utilizing the dragonfly library
/bongo_bear <- bongo cat but it's a bear using the dragonfly library and ascii shader
```

## Gameplay Examples

[Saucer Shoot](https://github.com/fishrcat/dragonfly-cpp-engine-course/pull/1)

## TODOs

- [x] [**Saucer Shoot Tutorial**](https://dragonfly.wpi.edu/book/pdfs/3-tutorial.pdf) - Build the example game using the existing dragonfly library
- [x] **Development Environment v1** - Initialize dragonfly library development workflows
    - [x] Migrate to CMake
    - [x] Integrate Clang and GoogleTest
    - [x] Initialize GitHub actions to lint/build/test PR commits
- [ ] **Dragopfly** - Recreate dragonfly library following the [Program a Game Engine from Scratch Book](https://dragonfly.wpi.edu/book/index.html) development checkpoints
    - [ ] DC1: Manager & LogManager
    - [ ] DC2: Clock & GameManager
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

## Development Workflows

### Dragonfly Game Engine Library

#### 1) Build

```bash
cd dragonfly
mkdir -p build  # Run once
cmake -S . -B build -DDRAGONFLY_BUILD_TESTS=ON  # Run once
cmake --build build
```

#### 2) Run Tests
```bash
ctest --test-dir build --output-on-failure
```

#### 3) Format & Lint

```bash
pipx install pre-commit  # Run once
pre-commit run --all-files
```

### Saucer Shoot Game
