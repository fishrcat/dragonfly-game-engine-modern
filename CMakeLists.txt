cmake_minimum_required(VERSION 3.24)
project(dragonfly_course LANGUAGES CXX)

add_subdirectory(dragonfly)
# TODO: Re-enable saucer shoot builds when dragonfly library is re-implemented.
# The current `saucer_shoot/.saucer_shoot` executable was built with the complete library example and is playable.
# add_subdirectory(saucer_shoot)

enable_testing()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_custom_target(build-dragonfly
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}/dragonfly --parallel
    COMMENT "Building Dragonfly library..."
    VERBATIM
)

add_custom_target(all-dragonfly
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}/dragonfly --parallel
    COMMAND ${CMAKE_CTEST_COMMAND} --test-dir ${CMAKE_BINARY_DIR}/dragonfly --output-on-failure
    COMMENT "Building Dragonfly library and running all tests..."
    VERBATIM
)
