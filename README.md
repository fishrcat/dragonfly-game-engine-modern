# Dragonfly Course

Artifacts from following the Dragonfly C++ Text-Based Game Engine Course

---

Mark Claypool. Dragonfly - Program a Game Engine from Scratch, Interactive Media and Game Development, Worcester Polytechnic Institute, 2014. Online at: http://dragonfly.wpi.edu/book/

## Structure

```
/dragonfly <- dragonfly library
/saucer_shoot <- intro 2d shooter game utilizing the dragonfly library
```

## Development Workflows

### Dragonfly Library

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

#### 4) PR

Github workflows will run on commit:

1. Run pre-commit checks
2. Linux build and tests (req. 1 passing)
3. Multi-platform builds (req. 2 passing)

### Saucer Shoot Game

## Gameplay Examples

[Saucer Shoot](https://github.com/fishrcat/dragonfly-cpp-engine-course/pull/1)
