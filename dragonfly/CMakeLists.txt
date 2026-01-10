add_library(dragonfly)
add_library(dragonfly::dragonfly ALIAS dragonfly)

target_sources(dragonfly
    PRIVATE
    src/clock.cpp
    src/game_manager.cpp
    src/log_manager.cpp
    src/manager.cpp
    src/vector.cpp
    PUBLIC
    FILE_SET HEADERS
    BASE_DIRS include
    FILES
    include/config.h
    include/clock.h
    include/game_manager.h
    include/log_manager.h
    include/manager.h
    include/vector.h
)

target_compile_features(dragonfly PUBLIC cxx_std_20)

target_include_directories(dragonfly
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(dragonfly PRIVATE -Wall -Wextra -Wpedantic)
elseif (MSVC)
  target_compile_options(dragonfly PRIVATE /W4 /permissive- /WX)
endif()

option(DRAGONFLY_BUILD_TESTS "Build Dragonfly tests" ON)

if (DRAGONFLY_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

# Build the test game executable
add_executable(dragonfly_test_game
    test_game.cpp
)

target_link_libraries(dragonfly_test_game
    PRIVATE dragonfly::dragonfly
)

target_compile_features(dragonfly_test_game
    PRIVATE cxx_std_20
)
