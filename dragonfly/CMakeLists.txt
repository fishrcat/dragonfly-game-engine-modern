add_library(dragonfly)
add_library(dragonfly::dragonfly ALIAS dragonfly)

target_sources(dragonfly
    PRIVATE
    src/vector.cpp
    PUBLIC
    FILE_SET HEADERS
    BASE_DIRS include
    FILES
    include/df/vector.h
)

target_compile_features(dragonfly PUBLIC cxx_std_20)

target_include_directories(dragonfly
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_compile_options(dragonfly PRIVATE
    -Wall -Wextra -Wpedantic
)

option(DRAGONFLY_BUILD_TESTS "Build Dragonfly tests" ON)

if (DRAGONFLY_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
