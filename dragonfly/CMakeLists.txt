add_library(dragonfly)
add_library(dragonfly::dragonfly ALIAS dragonfly)

target_sources(dragonfly
    PRIVATE
    src/clock.cpp
    src/display_manager.cpp
    src/event.cpp
    src/event_step.cpp
    src/game_manager.cpp
    src/log_manager.cpp
    src/manager.cpp
    src/object.cpp
    src/object_list.cpp
    src/vector.cpp
    src/world_manager.cpp
    PUBLIC
    FILE_SET HEADERS
    BASE_DIRS include
    FILES
    include/config.h
    include/clock.h
    include/color.h
    include/display_manager.h
    include/event.h
    include/event_step.h
    include/game_manager.h
    include/log_manager.h
    include/manager.h
    include/object.h
    include/object_list.h
    include/vector.h
    include/world_manager.h
)

target_compile_features(dragonfly PUBLIC cxx_std_20)

target_include_directories(dragonfly
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_compile_options(dragonfly PRIVATE -Wall -Wextra -Wpedantic)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

target_link_libraries(dragonfly
    PUBLIC
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
)

option(DRAGONFLY_BUILD_TESTS "Build Dragonfly tests" ON)

if (DRAGONFLY_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

# ----- Test game executable
add_executable(dragonfly_test_game
    test_game.cpp
)

target_link_libraries(dragonfly_test_game
    PRIVATE dragonfly::dragonfly
)

target_compile_features(dragonfly_test_game
    PRIVATE cxx_std_20
)

# ----- Profileable test game executable

add_executable(dragonfly_test_game_profile
    test_game.cpp
)

target_link_libraries(dragonfly_test_game_profile
    PRIVATE dragonfly::dragonfly
)

target_compile_features(dragonfly_test_game_profile
    PRIVATE cxx_std_20
)

target_compile_options(dragonfly_test_game_profile PRIVATE
    -O2
    -g
    -fno-omit-frame-pointer
)

target_link_options(dragonfly_test_game_profile PRIVATE
    -fno-omit-frame-pointer
)
