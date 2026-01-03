project(saucer_shoot LANGUAGES CXX)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "src/*.cpp"
)
add_executable(saucer_shoot
    game.cpp
    ${SOURCES}
)

target_link_libraries(saucer_shoot
    PRIVATE
    dragonfly::dragonfly
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

set_target_properties(saucer_shoot PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/saucer_shoot"
)
