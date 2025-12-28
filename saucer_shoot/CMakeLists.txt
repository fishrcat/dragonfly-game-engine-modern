project(saucer_shoot LANGUAGES CXX)

file(GLOB SOURCES
        "*.cpp"
        "src/*.cpp"
)
add_executable(saucer_shoot ${SOURCES})

target_include_directories(saucer_shoot PRIVATE ${DRAGONFLY_INCLUDE_DIR})
target_link_libraries(saucer_shoot PRIVATE
    ${DRAGONFLY_LIBRARY}
    SFML::Graphics SFML::Window SFML::System SFML::Audio
    ${PLATFORM_LINK_LIBS}
)

set_target_properties(saucer_shoot PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/${PROJECT_DIR}"
)
