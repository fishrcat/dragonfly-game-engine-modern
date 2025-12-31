# Dragonfly Course

Artifacts from following the Dragonfly C++ Text-Based Game Engine Course

---

Mark Claypool. Dragonfly - Program a Game Engine from Scratch, Interactive Media and Game Development, Worcester Polytechnic Institute, 2014. Online at: http://dragonfly.wpi.edu/book/

## Structure

```
/dragonfly <- dragonfly library
/saucer_shoot <- intro 2d shooter game
```

## Development Workflow

```bash
# Configure and build
mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .

# Build specific project
cmake --build . --target saucer_shoot

# Run executable
cd saucer_shoot
./saucer_shoot

# Checks
clang-format -i saucer_shoot/**/*.cpp saucer_shoot/**/*.h
clang-tidy saucer_shoot/**/*.cpp -- -std=c++17 -Idragonfly/include
g++ -std=c++17 -Wextra -Wpedantic -Werror -c saucer_shoot/*.cpp -Idragonfly/include
```
