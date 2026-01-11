cmake_minimum_required(VERSION 3.24)
project(dragonfly_course LANGUAGES CXX)

add_subdirectory(dragonfly)
# TODO: Re-enable saucer shoot builds when dragonfly library is re-implemented.
# The current `saucer_shoot/.saucer_shoot` executable was built with the complete library example and is playable.
# add_subdirectory(saucer_shoot)

enable_testing()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_custom_target(build-dragonfly
    COMMENT "Building Dragonfly library and test executable..."
)
add_dependencies(build-dragonfly
    dragonfly
    dragonfly_test_game
)

add_custom_target(test-dragonfly
    COMMAND ${CMAKE_CTEST_COMMAND} --test-dir ${CMAKE_BINARY_DIR}/dragonfly --output-on-failure
    COMMENT "Building Dragonfly library and running all tests..."
)
add_dependencies(test-dragonfly
    dragonfly
    dragonfly_test_game
)

add_custom_target(profile-dragonfly
    perf record -e cpu-clock -F 10000 -g -- $<TARGET_FILE:dragonfly_test_game_profile>
    COMMAND perf script > perf.out
    COMMAND stackcollapse-perf.pl perf.out > perf.folded
    COMMAND flamegraph.pl perf.folded > flamegraph.svg
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Profiling Dragonfly test game and generating flamegraph.svg"
    VERBATIM
)
add_dependencies(profile-dragonfly
    dragonfly
    dragonfly_test_game_profile
)
